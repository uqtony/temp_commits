/******************************************************************************
  * @project: LT2101
  * @file: chipsystem.c
  * @author: qihan
  * @company: LONTIUM
  * @date: 2021.10.12
/******************************************************************************/
#include "include.h"

u8 CHIP_Rx_DpModeFlag(void)
{
    return TRUE;
}
u8 CHIP_Rx_EdidValidFlag(void)
{
    return TRUE;
}
u8 CHIP_RxRdy_GetFlag(void)
{
    return g_stDpRx.u1IsRxRdy;
}

u8 CHIP_RxVidRdy_GetFlag(void)
{
    return g_stDpRx.u1IsRxVidRdy;
}

u8 CHIP_RxPkgRdy_GetFlag(void)
{
    return g_stDpRx.u1IsRxPkgRdy;
}

u8 CHIP_TxEdidRdy_GetFlag(void)
{
    return g_stHdmiTx.u1IsTxEdidRdy;
}

void CHIP_RxHpd_TxCheckRegister(void)
{
    g_stDpRx.pTxHpdLowAction  = CHIP_HdmiTx_HpdLowAction;
}

void CHIP_TxHpd_RxCheckRegister(void)
{
    g_stHdmiTx.pRxHpdLowAction = CHIP_DpRx_HpdLowAction;
}
void CHIP_RxToTx_AviPkgCal(void)
{
    u16 usMsaHtotal,usMsaHactive,usMsaVactive;
    u32 ulPixelFreqency;
    usMsaHtotal =  ((u16)BKDC_DB_REG <<8) + BKDC_DC_REG;
    usMsaHactive = ((u16)BKDC_E7_REG <<8) + BKDC_E8_REG;
    usMsaVactive = ((u16)BKDC_E9_REG <<8) + BKDC_EA_REG;
    ulPixelFreqency = ((u32)(BKDA_F8_REG&0x0f)<<16) + ((u16)BKDA_F9_REG <<8) + BKDA_FA_REG;
    ulPixelFreqency <<= 1;
    #if CSC_ENABLE == ENABLED
    g_stHdmiTx.ucTxPixelEncoding = CSC_TX_MODE;
    if(g_stHdmiTx.ucTxPixelEncoding == RGB)
    {
        g_stHdmiTx.ucTxcolorRange = FULL_RANGE;
    }
    else
    {
        g_stHdmiTx.ucTxcolorRange = LIMIT_RANGE;
    }
    #endif
    if((g_stDpRx.u1VscPkg == TRUE)&&(g_stDpRx.ucPixelEncoding == VSC_YCC420))
    {
        #if CSC_ENABLE == ENABLED
        if(g_stHdmiTx.ucTxPixelEncoding == YCbCr420)
        #endif    
        {
            ulPixelFreqency <<= 1;
        }
    }
    if(g_stDpRx.u1VscPkg == TRUE)
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
    if(g_stDpRx.u1VscPkg == TRUE)
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
                if(g_stDpRx.u1DynamicRange == FULL_RANGE)
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
                if(g_stDpRx.u1DynamicRange == FULL_RANGE)
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
                if(g_stDpRx.u1DynamicRange == FULL_RANGE)
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
                if(g_stDpRx.u1DynamicRange == FULL_RANGE)
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
    #if CSC_ENABLE == ENABLED
    g_stHdmiTx.ucszAviPkt[0] &= 0x1f;
    g_stHdmiTx.ucszAviPkt[0] |= g_stHdmiTx.ucTxPixelEncoding <<5;
    g_stHdmiTx.ucszAviPkt[2] &=0xfc;// bit3:2 Q1_Q0 = 00
    g_stHdmiTx.ucszAviPkt[4] = 0x00;
    if(g_stHdmiTx.ucTxPixelEncoding == RGB)
    {
        if(g_stHdmiTx.ucTxcolorRange == FULL_RANGE)
        {
            g_stHdmiTx.ucszAviPkt[2] |= 0x08;// bit3:2 Q1_Q0 = 10
        }
        else
        {
            g_stHdmiTx.ucszAviPkt[2] |= 0x04;// bit3:2 Q1_Q0 = 01
        }
    }
    else
    {
        if(g_stDpRx.u1DynamicRange == FULL_RANGE)
        {
            
            g_stHdmiTx.ucszAviPkt[4] = 0x40;
        }
        else
        {
            g_stHdmiTx.ucszAviPkt[4] = 0x00;
        }    
    }
    #endif
}