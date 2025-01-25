//////////////////////////////////////
//Project:   LT2101
//Filename:  Lt8711uxd.c
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#include "Include.h"

#if LT8711UXD == ENABLED

StructDpRx     g_stDpRx ;
StructHdmiTx   g_stHdmiTx ;

void CHIP_Var_PowerOn(void)
{
    g_stDpRx.ucRxStatus = 0xff;
    g_stHdmiTx.ucTxStatus = 0xff;  
}

void Chip_DpRx_VarIni(void)
{
    g_stDpRx.ucRxLinkRate = DPRX_LINK_RATE;
    g_stDpRx.ucRxLinkCount = DPRX_LINK_COUNT;
    g_stDpRx.ubSsc_Support = DPRX_SSC_SUPPORT_EN;
    g_stDpRx.ubTps4_Support = DPRX_TPS4_SUPPORT_EN;
}

void Chip_DpRx_DpOrTypecDet(void)
{
    #if TYPECRX_EN == ENABLED
    if(((BKD0_AF_REG&0x20)==0x00)||(BKD0_B0_REG&0xf0)||((BKD0_2F_REG&0x20)==0x00)||(BKD0_30_REG&0xf0)) 
    {
        g_stDpRx.ubInput_Type_Sel = TYPEC_IN;
    }
    else
    #endif
    {
        g_stDpRx.ubInput_Type_Sel = DP_IN;;
    }
    if(g_stDpRx.ubInput_Type_Sel == DP_IN)
    {
        printLT(PRINT_PRIO_HIG,"\nDp In");
    }
    else
    {
        printLT(PRINT_PRIO_HIG,"\nTypeC In");
    }
}

void CHIP_DpRx_ColorSpaceGet(void)
{
    if((BKDC_EC_REG & BIT6_1)&&(BKDC_0D_REG == 0x07)&&(BKDC_0E_REG == 0x05)&&(BKDC_0F_REG == 0x13)&&((BKDC_BC_REG&0xF0)<= 0x30))//VSC
    {
        g_stDpRx.ucPixelEncoding  =   (BKDC_BC_REG>>4)&0x0f;//00 rgb 01 ycc444 10 ycc222 11 ycc420
        g_stDpRx.ucColorimetryFormat = BKDC_BC_REG &0x0f;//
        g_stDpRx.ubDynamicRange =     (BKDC_BD_REG>>7)&BIT0_1;// 1 cta range limit  0 vesa range full
        g_stDpRx.ucBitDepth =          BKDC_BD_REG &0x07;////1 8bit 2 10bit 3 12bit
        g_stDpRx.ubVscPkg =            TRUE;//indicate the vsc
    }
    else
    {
        g_stDpRx.ucPixelEncoding  =   (BKDC_EB_REG>>1)&0x03;//00 rgb 01 ycc422 10 ycc444  11 rgb wide
        g_stDpRx.ucColorimetryFormat =(BKDC_EB_REG>>3)&0X03;//
        g_stDpRx.ubDynamicRange =     (BKDC_EB_REG>>3)&BIT0_1;// 1 cta  RGB range limit  0 vesa  RGB range full
        g_stDpRx.ucBitDepth =         (BKDC_EB_REG>>5)&0x07;//1 8bit 2 10bit 3 12bit
        g_stDpRx.ubVscPkg =            FALSE;//in dicate misc0
    }
    if(g_stDpRx.ubVscPkg == TRUE)
    {
        if(g_stDpRx.ucPixelEncoding == VSC_YCC420)
        {
            BKDA_86_REG |= BIT7_1;    //Ycbcr420 enable.
        }
        else
        {
            BKDA_86_REG &= BIT7_0;    //Ycbcr420 enable.
        }
        if(g_stDpRx.ucPixelEncoding == VSC_YCC422)////YCC 422
        {
            BKDA_16_REG = (g_stDpRx.ucBitDepth <<2)|BIT0_1;//8BIT 0x04  10bit 0x08 12bit 0x0c 
        }
        else
        {
            BKDA_16_REG = (g_stDpRx.ucBitDepth <<2)&BIT0_0;//8BIT 0x04  10bit 0x08 12bit 0x0c
        }
        BKDA_05_REG |= BIT7_1;   //The mode of pixel format control
        BKDA_0A_REG |= BIT7_1;   //The mode of pixel depth control
    }
    else
    {
        BKDA_86_REG &= BIT7_0;    //Ycbcr420 enable.
        BKDA_16_REG = 0x04;       // default value
        BKDA_05_REG &= BIT7_0;    //The mode of pixel format control
        BKDA_0A_REG &= BIT7_0;    //The mode of pixel depth control
    }
}

void CHIP_HdmiTx_AviCal(void)
{
    u16 usMsaHtotal,usMsaHactive,usMsaVactive;
    u32 ulPixelFreqency;
    usMsaHtotal =  BKDC_DB_REG;
    usMsaHtotal <<= 8;
    usMsaHtotal |= BKDC_DC_REG;

    usMsaHactive =  BKDC_E7_REG;
    usMsaHactive <<= 8;
    usMsaHactive |= BKDC_E8_REG;

    usMsaVactive =  BKDC_E9_REG;
    usMsaVactive <<= 8;
    usMsaVactive |= BKDC_EA_REG;
    
    ulPixelFreqency =  BKDA_F8_REG&0x0f;
    ulPixelFreqency <<=8;
    ulPixelFreqency |= BKDA_F9_REG;
    ulPixelFreqency <<=8;
    ulPixelFreqency |= BKDA_FA_REG;
    ulPixelFreqency <<= 1;
    if((g_stDpRx.ubVscPkg == TRUE)&&(g_stDpRx.ucPixelEncoding == VSC_YCC420))
    {
        ulPixelFreqency <<= 1;
    }
    if(g_stDpRx.ubVscPkg == TRUE)
    {
        switch(g_stDpRx.ucPixelEncoding)
        {
            case VSC_RGB:
                g_stHdmiTx.ucszAviPkt[0] = 0x00;//bit7:5 :Y2Y1Y0
                break;
            case VSC_YCC444:
                g_stHdmiTx.ucszAviPkt[0] = 0x40;//bit7:5 :Y2Y1Y0
                break;
            case VSC_YCC422:
                g_stHdmiTx.ucszAviPkt[0] = 0x20;//bit7:5 :Y2Y1Y0
                break;
            case VSC_YCC420:
                g_stHdmiTx.ucszAviPkt[0] = 0x60;//bit7:5 :Y2Y1Y0
                break;
            default:
                break;
        }
    }
    else
    {
        switch(g_stDpRx.ucPixelEncoding)
        {
            case MISC_RGB:
                g_stHdmiTx.ucszAviPkt[0] = 0x00;//bit7:5 :Y2Y1Y0
                break;
            case MISC_YCC422:
                g_stHdmiTx.ucszAviPkt[0] = 0x20;//bit7:5 :Y2Y1Y0
                break;
            case MISC_YCC444:
                g_stHdmiTx.ucszAviPkt[0] = 0x40;//bit7:5 :Y2Y1Y0
                break;
            case MISC_RGB_WIDE:
                g_stHdmiTx.ucszAviPkt[0] = 0x00;//bit7:5 :Y2Y1Y0
                break;
            default:
                break;
        }
    }
    g_stHdmiTx.ucszAviPkt[0] |= 0x10;//bit4:A0 =1 stand for the R3-R0 is active
    if(g_stDpRx.ubVscPkg == TRUE)
    {
        switch(g_stDpRx.ucPixelEncoding) //rgb
        {
            case VSC_RGB://rgb
                switch(g_stDpRx.ucColorimetryFormat)
                {
                    case ITUR_BT2020RGB:
                    g_stHdmiTx.ucszAviPkt[1] = 0xc0;// bit7:6 C1_C0 = 11
                    g_stHdmiTx.ucszAviPkt[2] = 0x60;//bit6:4 EC2_EC1_EC0 = 110
                    break;
                    case DCI_P3:
                    g_stHdmiTx.ucszAviPkt[1] = 0xc0;// bit7:6 C1_C0 = 11
                    g_stHdmiTx.ucszAviPkt[2] = 0x70;//bit6:4 EC2_EC1_EC0 = 111
                    break;
                    default:
                    g_stHdmiTx.ucszAviPkt[1] = 0x00;//bit7:6 C1_C0 = 00
                    g_stHdmiTx.ucszAviPkt[2] = 0x00;//bit6:4 
                    break;
                }
                if(g_stDpRx.ubDynamicRange == FALSE)
                {
                    g_stHdmiTx.ucszAviPkt[2] |= 0x08;// bit3:2 Q1_Q0 = 10
                    g_stHdmiTx.ucszAviPkt[4] =  0x00;
                }
                else
                {
                    g_stHdmiTx.ucszAviPkt[2] |= 0x04;// bit3:2 Q1_Q0 = 01
                    g_stHdmiTx.ucszAviPkt[4] =  0x00;
                }
                break;
            default://YCC444 YCC422 YCC420
                switch(g_stDpRx.ucColorimetryFormat)
                {
                    case ITUR_BT601:
                        g_stHdmiTx.ucszAviPkt[1] = 0x40;// bit7:6 C1_C0 = 01
                        g_stHdmiTx.ucszAviPkt[2] = 0x00;//bit6:4 EC2_EC1_EC0 = 000
                        break;
                    case ITUR_BT709:
                        g_stHdmiTx.ucszAviPkt[1] = 0x80;// bit7:6 C1_C0 = 10
                        g_stHdmiTx.ucszAviPkt[2] = 0x00;//bit6:4 EC2_EC1_EC0 = 000
                        break;
                    case XVYCC601:
                        g_stHdmiTx.ucszAviPkt[1] = 0xc0;// bit7:6 C1_C0 = 11
                        g_stHdmiTx.ucszAviPkt[2] = 0x00;//bit6:4 EC2_EC1_EC0 = 000
                        break;
                    case XVYCC709:
                        g_stHdmiTx.ucszAviPkt[1] = 0xc0;// bit7:6 C1_C0 = 11
                        g_stHdmiTx.ucszAviPkt[2] = 0x10;//bit6:4 EC2_EC1_EC0 = 001                        
                        break;
                    case SYCC601:
                        g_stHdmiTx.ucszAviPkt[1] = 0xc0;// bit7:6 C1_C0 = 11
                        g_stHdmiTx.ucszAviPkt[2] = 0x20;//bit6:4 EC2_EC1_EC0 = 010                         
                        break;
                    case OPYCC601:
                        g_stHdmiTx.ucszAviPkt[1] = 0xc0;// bit7:6 C1_C0 = 11
                        g_stHdmiTx.ucszAviPkt[2] = 0x30;//bit6:4 EC2_EC1_EC0 = 011                          
                        break;     
                    case ITUR_BT2020YCYBCYRC:
                        g_stHdmiTx.ucszAviPkt[1] = 0xc0;// bit7:6 C1_C0 = 11
                        g_stHdmiTx.ucszAviPkt[2] = 0x50;//bit6:4 EC2_EC1_EC0 = 101                               
                        break;  
                    case ITUR_BT2020YCBCR:
                        g_stHdmiTx.ucszAviPkt[1] = 0xc0;// bit7:6 C1_C0 = 11
                        g_stHdmiTx.ucszAviPkt[2] = 0x60;//bit6:4 EC2_EC1_EC0 = 110                          
                        break;
                    default:
                        g_stHdmiTx.ucszAviPkt[1] = 0x00;// bit7:6 C1_C0 = 01
                        g_stHdmiTx.ucszAviPkt[2] = 0x00;//bit6:4 EC2_EC1_EC0 = 000                        
                        break;
                }
                if(g_stDpRx.ubDynamicRange == FALSE)
                {
                    g_stHdmiTx.ucszAviPkt[2] &=0xfc;// bit3:2 Q1_Q0 = 00
                    g_stHdmiTx.ucszAviPkt[4] = 0x40;
                }
                else
                {
                    g_stHdmiTx.ucszAviPkt[2] &=0xfc;// bit3:2 Q1_Q0 = 00
                    g_stHdmiTx.ucszAviPkt[4] = 0x00;
                }                
            break;
        }
    }
    else
    {
        switch(g_stDpRx.ucPixelEncoding) //rgb
        {
            case MISC_RGB://rgb
                g_stHdmiTx.ucszAviPkt[1] = 0x00;//bit7:6 C1_C0 = 00
                g_stHdmiTx.ucszAviPkt[2] = 0x00;//bit6:4 
                if(g_stDpRx.ubDynamicRange == FALSE)
                {
                    g_stHdmiTx.ucszAviPkt[2] |= 0x08;// bit3:2 Q1_Q0 = 10
                    g_stHdmiTx.ucszAviPkt[4] =  0x00;
                }
                else
                {
                    g_stHdmiTx.ucszAviPkt[2] |= 0x04;// bit3:2 Q1_Q0 = 01
                    g_stHdmiTx.ucszAviPkt[4] =  0x00;
                }            
                break;
            case MISC_YCC422:
            case MISC_YCC444:
                switch(g_stDpRx.ucColorimetryFormat)
                {
                    case XVYCC601_MISC:
                        g_stHdmiTx.ucszAviPkt[1] = 0xc0;// bit7:6 C1_C0 = 11
                        g_stHdmiTx.ucszAviPkt[2] = 0x00;//bit6:4 EC2_EC1_EC0 = 000                        
                        break;
                    case ITUR_BT601_MISC:
                        g_stHdmiTx.ucszAviPkt[1] = 0x40;// bit7:6 C1_C0 = 01
                        g_stHdmiTx.ucszAviPkt[2] = 0x00;//bit6:4 EC2_EC1_EC0 = 000                        
                        break;
                    case XVYCC709_MISC:
                        g_stHdmiTx.ucszAviPkt[1] = 0xc0;// bit7:6 C1_C0 = 11
                        g_stHdmiTx.ucszAviPkt[2] = 0x10;//bit6:4 EC2_EC1_EC0 = 001                           
                        break;
                    case ITUR_BT709_MISC:
                        g_stHdmiTx.ucszAviPkt[1] = 0x80;// bit7:6 C1_C0 = 10
                        g_stHdmiTx.ucszAviPkt[2] = 0x00;//bit6:4 EC2_EC1_EC0 = 000                        
                        break;
                    default:
                        break;
                }
                if(g_stDpRx.ubDynamicRange == FALSE)
                {
                    g_stHdmiTx.ucszAviPkt[2] &=0xfc;// bit3:2 Q1_Q0 = 00
                    g_stHdmiTx.ucszAviPkt[4] = 0x40;
                }
                else
                {
                    g_stHdmiTx.ucszAviPkt[2] &=0xfc;// bit3:2 Q1_Q0 = 00
                    g_stHdmiTx.ucszAviPkt[4] = 0x00;
                }                  
                break; 
            case MISC_RGB_WIDE://rgb
                switch(g_stDpRx.ucColorimetryFormat)
                {
                    case DCI_P3_MISC:
                        g_stHdmiTx.ucszAviPkt[1] = 0xc0;// bit7:6 C1_C0 = 11
                        g_stHdmiTx.ucszAviPkt[2] = 0x70;//bit6:4 EC2_EC1_EC0 = 111
                        break;
                    default:
                        g_stHdmiTx.ucszAviPkt[1] = 0x00;//bit7:6 C1_C0 = 00
                        g_stHdmiTx.ucszAviPkt[2] = 0x00;//bit6:4 EC2_EC1_EC0 = 000
                        break;
                }
                g_stHdmiTx.ucszAviPkt[4] =  0x00;               
            default:
                break;
        }
    }
    if((usMsaHactive*9) == (usMsaVactive*16))
    {
        g_stHdmiTx.ucszAviPkt[1] |= 0x28;// M1_M0 =  10 R3_R2_R1_R0 = 1000
    }
    else if((usMsaHactive*9) == (usMsaVactive*14))
    {
        g_stHdmiTx.ucszAviPkt[1] |= 0x0B;//// M1_M0 = 00 R3_R2_R1_R0 = 1011
    }
    else if((usMsaHactive*3) == (usMsaVactive*4))
    {
        g_stHdmiTx.ucszAviPkt[1] |= 0x19;//// M1_M0 = 01 R3_R2_R1_R0 = 1001
    }
    else
    {
        g_stHdmiTx.ucszAviPkt[1] |= 0x08;//// M1_M0 = 00 R3_R2_R1_R0 = 1000
    }
    g_stHdmiTx.ucszAviPkt[3] = 0x00;
    g_stHdmiTx.ucHdmiVic = 0x00;
    if((ulPixelFreqency > 0x0900b0)&&(ulPixelFreqency < 0x0927c0))//590-600M
    {
        if((usMsaHtotal ==0x1130)&&(usMsaHactive ==0x0f00))//3840X2160 60HZ
        {
            g_stHdmiTx.ucszAviPkt[3] = 0x61; //vic
        }
        else if ((usMsaHtotal ==0x1130)&&(usMsaHactive ==0x1000))//4096X2160 60HZ
        {
            g_stHdmiTx.ucszAviPkt[3] = 0x66; //vic
        }
        else if((usMsaHtotal ==0x14a0)&&(usMsaHactive ==0x0f00))//3840X2160 50HZ
        {
            g_stHdmiTx.ucszAviPkt[3] = 0x60; //vic
        }
        else if ((usMsaHtotal ==0x14a0)&&(usMsaHactive ==0x1000))//4096X2160 50HZ
        {
            g_stHdmiTx.ucszAviPkt[3] = 0x65; //vic
        }
    }
    else if((ulPixelFreqency > 0x081650)&&(ulPixelFreqency < 0x0829d0))//530-535 M
    {
        if((usMsaHtotal ==0x0fa0)&&(usMsaHactive ==0x0f00))//3840X2160 60HZ 533m
        {
            g_stHdmiTx.ucszAviPkt[3] = 0x61; //vic
        }
    }
    else if((ulPixelFreqency > 0x046cd0)&&(ulPixelFreqency < 0x0493e0)) //290-300M
    {
        if((usMsaHtotal ==0x157c)&&(usMsaHactive ==0x0f00))//3840X2160 24HZ
        {
            g_stHdmiTx.ucHdmiVic  = 0x03;
        }
        else if ((usMsaHtotal ==0x14a0)&&(usMsaHactive ==0x0f00))//3840X2160 25HZ
        {
            g_stHdmiTx.ucHdmiVic  = 0x02;
        }
        else if ((usMsaHtotal ==0x1130)&&(usMsaHactive ==0x0f00))//3840X2160 30HZ
        {
            g_stHdmiTx.ucHdmiVic  = 0x01;
        }
        else if((usMsaHtotal ==0x157c)&&(usMsaHactive ==0x1000))//4096 X2160 24HZ
        {
            g_stHdmiTx.ucHdmiVic = 0x04;
        }
        else if ((usMsaHtotal ==0x14a0)&&(usMsaHactive ==0x1000))//4096 X2160  25HZ
        {
            g_stHdmiTx.ucszAviPkt[3] = 0x63; //vic
        }
        else if ((usMsaHtotal ==0x1130)&&(usMsaHactive ==0x1000))//4096 X2160  30HZ
        {
            g_stHdmiTx.ucszAviPkt[3] = 0x64; //vic
        }
    }
    else if((ulPixelFreqency > 0x03f7a0)&&(ulPixelFreqency < 0x041eb0))//260- 270 M
    {
        if((usMsaHtotal ==0x0fa0)&&(usMsaHactive ==0x0f00))//3840X2160 30HZ 266m
        {
            g_stHdmiTx.ucszAviPkt[3] = 0x5f; //vic
        }
    }
    else if((ulPixelFreqency > 0x0222e0)&&(ulPixelFreqency < 0x0249f0)) //140-150M
    {
        if((usMsaHtotal ==0x0898)&&(usMsaHactive ==0x0780))//1920X1080 60HZ
        {
            g_stHdmiTx.ucszAviPkt[3] = 0x10; //vic
        }
    }
    else if((ulPixelFreqency > 0x011170)&&(ulPixelFreqency < 0x0128e0)) //70-76M
    {
        if((usMsaHtotal ==0x0672)&&(usMsaHactive ==0x0500))//1280X720P 60HZ
        {
            g_stHdmiTx.ucszAviPkt[3] = 0x04; //vic
        }
    }
    else if((ulPixelFreqency > 0x005DC0)&&(ulPixelFreqency < 0x006D60)) //24-28M
    {
        if((usMsaHtotal ==0x035A)&&(usMsaHactive ==0x02d0))//720X480P 60HZ
        {
            g_stHdmiTx.ucszAviPkt[3] = 0x02; //vic
        }
        else if((usMsaHtotal ==0x0320)&&(usMsaHactive ==0x0280))//640X480P 60HZ
        {
            g_stHdmiTx.ucszAviPkt[3] = 0x01; //vic
        }
    }
    switch(g_stDpRx.ucBitDepth)
    {
        case VESA_8BIT:
            g_stHdmiTx.ucBitDepth = DEEP_8BIT;
            break;
        case VESA_10BIT:
            g_stHdmiTx.ucBitDepth = DEEP_10BIT;
            break;        
        case VESA_12BIT:
            g_stHdmiTx.ucBitDepth = DEEP_12BIT;
            break;
        default:
            g_stHdmiTx.ucBitDepth = DEEP_8BIT;
            break;
    }
}

void Chip_DpRx_VideoDoneCheck(void)
{
    if((BKDA_DF_REG& BIT6_1)== 0x00)
    {
        return;
    }
    g_stDpRx.ucRxStatus = 0x02;
}

void Chip_DpRx_HpdLowAction(void)
{
    if(g_stDpRx.ubInput_Type_Sel == DP_IN)
    {
        printLT(PRINT_PRIO_HIG,"\nDpRx Hpd Low"); 
        DRV_DpRx_HpdSet(HPD_LOW,IRQ_LOW);
    }
    else
    {
        printLT(PRINT_PRIO_HIG,"\nTypec Attention Low");
        CHIP_Ucc_HpdIrqSend(HPD_LOW,IRQ_LOW);
    }    
    
}

void Chip_DpRx_Loop(void)
{ 
    static u32 ulCurrentTime = 0;
    switch(g_stDpRx.ucRxStatus)
    {
        case 0xff:    
            DrvUcc_Set_All(); 
            Typec_Var_Init();   
            g_stDpRx.ucRxStatus = 0x0a;
            KNL_Timer_UpdLocalTime(&ulCurrentTime);
            break;
        case 0x0a:
            if(KNL_Timer_IsOverFlow(&ulCurrentTime,MS_10) == TRUE)
            {
                Chip_DpRx_DpOrTypecDet();
                DRV_DpRx_1MResiEn();
                g_stDpRx.ucRxStatus = 0x09;
            } 
            break;
        case 0x09: //
            if(((g_stDpRx.ubInput_Type_Sel == DP_IN)&&(DRV_DpRx_AuxDcDet() == TRUE))
             ||((g_stDpRx.ubInput_Type_Sel == TYPEC_IN)&&(CHIP_Ucc_ComDoneFlag() == TRUE)))
            {
                g_stDpRx.ucRxStatus = 0x08;
                printLT(PRINT_PRIO_HIG,"\ng_stDpRx.ucRxStatus = 0x%02bx",g_stDpRx.ucRxStatus );
            }
            break;
        case 0x08:
            if(g_stHdmiTx.ucTxStatus == 0x09) //hdmi tx edid read OK
            {
                KNL_Timer_UpdLocalTime(&ulCurrentTime);
                g_stDpRx.ucRxStatus = 0x07;
            }
            break;
        case 0x07:
            if(KNL_Timer_IsOverFlow(&ulCurrentTime,MS_50) == TRUE)
            {
                Chip_DpRx_VarIni();
                DRV_DpRx_SettingIni(); //including the dp rx hpd high attention
                CHIP_Aux_TrainigStatusClear();
                if(g_stDpRx.ubInput_Type_Sel == DP_IN)
                {
                    printLT(PRINT_PRIO_HIG,"\nDpRx Hpd High"); 
                    DRV_DpRx_HpdSet(HPD_HIGH,IRQ_LOW);
                }
                else
                {
                    printLT(PRINT_PRIO_HIG,"\nTypec Attention High");
                    CHIP_Ucc_HpdIrqSend(HPD_HIGH,IRQ_LOW);
                }
                g_stDpRx.ucRxStatus = 0x06;
            }
            break; 
        case 0x06:
            if(CHIP_Aux_Handing_Stauts() == TRUE) //rx trainig done
            {
                g_stDpRx.ucRxStatus = 0x05;
                KNL_Timer_UpdLocalTime(&ulCurrentTime);
            }
            else
            {
                ;
            }
            break;
        case 0x05:
            if(CHIP_Aux_Handing_Stauts() == FALSE)
            {
                g_stDpRx.ucRxStatus = 0x06;
            }
            if(KNL_Timer_IsOverFlow(&ulCurrentTime,MS_200) == TRUE)
            {
                printLT(PRINT_PRIO_HIG,"\nAux Training Done");
                printLT(PRINT_PRIO_TEST, "\nLinkRate_Count = 0x%02bx,0x%02bx",g_stAuxStatus.ucLink_Rate,g_stAuxStatus.ucLink_Count);
                g_stDpRx.ucRxStatus = 0x04;
            }
        break;
        case 0x04:
             CHIP_DpRx_EqScan();
			 DRV_DpRx_SoftMsaEn(FALSE);
             g_stDpRx.ucRxStatus = 0x03;
             break;
        case 0x03:
			 DRV_DpRx_SoftMsaEn(TRUE);
             CHIP_DpRx_ColorSpaceGet();
             CHIP_HdmiTx_AviCal();
             Chip_DpRx_VideoDoneCheck();   
             break;
        break;
        case 0x02: 
            CHIP_DpRx_ColorSpaceGet(); 
            CHIP_HdmiTx_AviCal();
            g_stDpRx.ucRxStatus = 0x01;  
            break;
        case 0x01: 
            CHIP_DpRx_ColorSpaceGet(); 
            CHIP_HdmiTx_AviCal();
            break;
        default:   
        break;
    }
    if(g_stDpRx.ucRxStatus <= 0x08)
    {
        if((g_stDpRx.ubInput_Type_Sel == DP_IN)&&(DRV_DpRx_AuxDcDet() == FALSE)) //dp rx dc det is low
        {
            g_stDpRx.ucRxStatus =   0x08;//Typec Rx CC is done or dp is ok cc is open 09
            g_stHdmiTx.ucTxStatus = 0x0a;
            Chip_DpRx_HpdLowAction();
        }
    }
}
void Chip_HdmiTx_Loop(void)
{
    static u32 ulCurrentTime = 0;
    switch(g_stHdmiTx.ucTxStatus)
    {
        case 0xff:    
            DRV_HmdiTx_SettingIni();    
            g_stHdmiTx.ucTxStatus = 0x0a;
            break;
        case 0x0a:
            if(g_stDpRx.ucRxStatus != 0x08) //Typec Rx CC is done or dp is ok
            {
                return;
            }
            if(DRV_HdmiTx_HpdDet() == TRUE) //hdmi hpd is high
            {
                printLT(PRINT_PRIO_HIG,"\nHdmiTx Hpd High");
                DRV_HmdiTx_EdidRead(szEdid_Data);
                g_stHdmiTx.ucTxStatus = 0x09;
            }
            break;
        case 0x09: 
            if(g_stDpRx.ucRxStatus == 0x02)//rx vide is OK
            {
                g_stHdmiTx.ucTxStatus = 0x08;
            }
            break;
        case 0x08:
            g_stHdmiTx.ucTxStatus = 0x07;
            break;
        case 0x07:
            g_stHdmiTx.ucTxStatus = 0x06;
            break; 
        case 0x06:
            g_stHdmiTx.ucTxStatus = 0x05;
            break;
        case 0x05:
            if(g_stDpRx.ucRxStatus == 0x01)// dp rx color is ok and rx video ok
            {
                g_stHdmiTx.ucTxStatus = 0x04;
                DRV_HdmiTx_ColorSpaceSet(g_stHdmiTx.ucszAviPkt,g_stHdmiTx.ucBitDepth,g_stHdmiTx.ucHdmiVic);
                DRV_HdmiTx_Hdmi20Get(DRV_DpRx_PcrPllTbcr()== TRUE);
            }
            break;
        case 0x04:
            if(g_stHdmiTx.ucTxStatus == 0x04)
            {
                DRV_HdmiTx_OutSet();
                KNL_Timer_UpdLocalTime(&ulCurrentTime);
                g_stHdmiTx.ucTxStatus = 0x03;
            }
            break;
        case 0x03:
            DRV_HdmiTx_ColorSpaceSet(g_stHdmiTx.ucszAviPkt,g_stHdmiTx.ucBitDepth,g_stHdmiTx.ucHdmiVic);
            if(KNL_Timer_IsOverFlow(&ulCurrentTime,SECOND_2) == TRUE)
            {
                DRV_HdmiTx_HdcpSet();
                KNL_Timer_UpdLocalTime(&ulCurrentTime);
                g_stHdmiTx.ucTxStatus = 0x02;
            }
            break;
        case 0x02:
            DRV_HdmiTx_ColorSpaceSet(g_stHdmiTx.ucszAviPkt,g_stHdmiTx.ucBitDepth,g_stHdmiTx.ucHdmiVic);
            if(KNL_Timer_IsOverFlow(&ulCurrentTime,MS_200) == TRUE)
            {
                DRV_HdmiTx_Audio();
                g_stHdmiTx.ucTxStatus = 0x01;
            }
            break;
        case 0x01:  
            DRV_HdmiTx_ColorSpaceSet(g_stHdmiTx.ucszAviPkt,g_stHdmiTx.ucBitDepth,g_stHdmiTx.ucHdmiVic);
            break;         
        default:  
        break;
    }
    if(g_stHdmiTx.ucTxStatus <= 0x09)
    {
        if(DRV_HdmiTx_HpdDet() == FALSE) //hdmi hpd is low
        {
            g_stDpRx.ucRxStatus = 0x08;//Typec Rx CC is done or dp is ok
            g_stHdmiTx.ucTxStatus = 0x0a;
            Chip_DpRx_HpdLowAction();
        }
    }
}
void CHIP_Main_LT8711uxdScan(void)
{
    #if HDMITX_PATTEN_SEL == DISABLED
    Chip_DpRx_Loop();
    Chip_HdmiTx_Loop();
    #else
    DRV_HdmiTx_Pattern();
    #endif
}
#endif

