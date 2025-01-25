/******************************************************************************
  * @project: LT2101
  * @file: ChipDpRx.c
  * @author: qihan
  * @company: LONTIUM
  * @date: 2021.10.12
/******************************************************************************/
#include "include.h"

void CHIP_Var_PowerOn(void)
{
    g_stDpRx.ucRxStatus = 0xff;
    g_stHdmiTx.ucTxStatus = 0xff;  
}

void Chip_DpRx_DpOrTypecDet(void)
{
    #if LT8711UXC == ENABLED
    CHIP_DpRx_Lt8711uxcDpOrTypecDet();
    #endif
    #if LT8711UXD == ENABLED
    CHIP_DpRx_Lt8711uxdDpOrTypecDet();
    #endif
    #if LT8711UXE1 == ENABLED
    CHIP_DpRx_Lt8711uxe1DpOrTypecDet();
    #endif
    #if LT8711UXE2 == ENABLED
    CHIP_DpRx_Lt8711uxe2DpOrTypecDet();
    #endif      
}

void Chip_DpRx_VarIni(void)
{
    #if LT8711UXC == ENABLED
    CHIP_DpRx_Lt8711uxcVarIni();
    #endif
    #if LT8711UXD == ENABLED
    CHIP_DpRx_Lt8711uxdVarIni();
    #endif
    #if LT8711UXE1 == ENABLED
    CHIP_DpRx_Lt8711uxe1VarIni();
    #endif
    #if LT8711UXE2 == ENABLED
    CHIP_DpRx_Lt8711uxe2VarIni();
    #endif     
}

void Chip_DpRx_ColorSpaceGet(void)
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
        BKDA_16_REG = 0x00;       // default value
        BKDA_05_REG &= BIT7_0;    //The mode of pixel format control
        BKDA_0A_REG &= BIT7_0;    //The mode of pixel depth control
    }
}

bool DRV_DpRx_DeSkewDet(void)
{
    u32 ulMsa_Mvid0,ulMsa_Mvid1,ulMsa_Mvid2,ulMsa_Mvid3;
    ulMsa_Mvid0 =  BKDC_CC_REG;
    ulMsa_Mvid0 <<=8;
    ulMsa_Mvid0 |= BKDC_CD_REG;
    ulMsa_Mvid0 <<=8;
    ulMsa_Mvid0 |= BKDC_CE_REG;
    ulMsa_Mvid1 =  BKDC_CF_REG;
    ulMsa_Mvid1 <<=8;
    ulMsa_Mvid1 |= BKDC_D0_REG;
    ulMsa_Mvid1 <<=8;
    ulMsa_Mvid1 |= BKDC_D1_REG;
    ulMsa_Mvid2 =  BKDC_D2_REG;
    ulMsa_Mvid2 <<=8;
    ulMsa_Mvid2 |= BKDC_D3_REG;
    ulMsa_Mvid2 <<=8;
    ulMsa_Mvid2 |= BKDC_D4_REG;
    ulMsa_Mvid3 =  BKDC_D5_REG;
    ulMsa_Mvid3 <<=8;
    ulMsa_Mvid3 |= BKDC_D6_REG;
    ulMsa_Mvid3 <<=8;
    ulMsa_Mvid3 |= BKDC_D7_REG;    
    if(g_stAuxStatus.ucLink_Count== FOUR_LANE)
    {
        if((ulMsa_Mvid0 > 0)&&(ulMsa_Mvid0 == ulMsa_Mvid1)&&(ulMsa_Mvid1 == ulMsa_Mvid2)&&(ulMsa_Mvid2 == ulMsa_Mvid3))
        {
            ;
        }
        else
        {
            return TRUE;
        }
    }
    else if(g_stAuxStatus.ucLink_Count == TWO_LANE)
    {
        if((ulMsa_Mvid0 > 0)&&(ulMsa_Mvid0 == ulMsa_Mvid1))
        {
            ;
        }
        else
        {
             return TRUE;
        }
    }    
    return FALSE;
}

bool Chip_DpRx_VideoDoneCheck(void)
{
    static u8 ucVidDoneDetCnt = 0;
    if((BKDA_DF_REG& BIT6_1) == 0x00)
    {
        ucVidDoneDetCnt = 0;
        return FALSE;
    }
    if((ucVidDoneDetCnt++) == 10)
    {
        ucVidDoneDetCnt = 0;
        return TRUE;  
    } 
    return FALSE;        
}

void CHIP_DpRx_HpdLowAction(void)
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
    g_stDpRx.ubIsRxRdy = FALSE;
    g_stDpRx.ubIsRxVidRdy  = FALSE;
    g_stDpRx.ubIsRxPkgRdy = FALSE;
}

void Chip_DpRx_ErrorCheck(void)
{
    if(g_stDpRx.ucRxStatus <= 0x08)// 
    {
        if((g_stDpRx.ubInput_Type_Sel == DP_IN)&&(DRV_DpRx_AuxDcDet() == FALSE)) //dp rx dc det is low
        {
            g_stDpRx.ucRxStatus =   0x09;//Typec Rx CC is done or dp is ok cc is open 09
            g_stHdmiTx.ucTxStatus = 0x0a;
            CHIP_DpRx_HpdLowAction();
            g_stDpRx.pTxHpdLowAction();
        }
    }
    if(g_stDpRx.ucRxStatus <= 0x04)
    {
        if(CHIP_Aux_Handing_Stauts() == FALSE)//re training
        {
            g_stDpRx.ucRxStatus = 0x06;
            g_stHdmiTx.ucTxStatus = 0x09;
            g_stDpRx.pTxHpdLowAction(); 
        }
    }
}

void Chip_DpRx_StateDebug(void)
{
    #if 0
    static u8 ucLastState = 0;
	if(ucLastState != g_stDpRx.ucRxStatus)
	{
		ucLastState = g_stDpRx.ucRxStatus;
		printLT(PRINT_PRIO_HIG, "\nRxState = 0x%02bx",ucLastState);
	}
    #endif
}

void Chip_DpRx_StateHandler(void)
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
            g_stDpRx.ubIsRxRdy = FALSE;
            g_stDpRx.ubIsRxVidRdy = FALSE;
            g_stDpRx.ubIsRxPkgRdy = FALSE;
            if(((g_stDpRx.ubInput_Type_Sel == DP_IN)&&(DRV_DpRx_AuxDcDet() == TRUE))
             ||((g_stDpRx.ubInput_Type_Sel == TYPEC_IN)&&(CHIP_Ucc_ComDoneFlag() == TRUE)))
            {
                g_stDpRx.ucRxStatus = 0x08;
                g_stDpRx.ubIsRxRdy = TRUE;
                CHIP_RxHpd_TxCheckSet();
                printLT(PRINT_PRIO_HIG,"\ng_stDpRx.ucRxStatus = 0x%02bx",g_stDpRx.ucRxStatus);
            }
            break;
        case 0x08:
            if(CHIP_Tx_HdmiModeFlag() == TRUE)
            {
                if((CHIP_TxEdidRdy_GetFlag() == TRUE)) //hdmi tx edid read OK
                {
                    KNL_Timer_UpdLocalTime(&ulCurrentTime);
                    g_stDpRx.ucRxStatus = 0x07;
                }
            }
            else
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
                    printLT(PRINT_PRIO_HIG,"\nTypec Attention High");//need update 
                    CHIP_Ucc_HpdIrqSend(HPD_HIGH,IRQ_LOW);
                }
                g_stDpRx.ucRxStatus = 0x06;
            }
            break; 
        case 0x06:
            if(CHIP_Aux_Handing_Stauts() == TRUE) //rx trainig done
            {
                g_stDpRx.ubIsRxVidRdy = FALSE;
                g_stDpRx.ubIsRxPkgRdy = FALSE;
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
             KNL_Timer_UpdLocalTime(&ulCurrentTime);
             g_stDpRx.ucRxStatus = 0x03;
             break;
        case 0x03:
            if(DRV_DpRx_DeSkewDet() == TRUE)
            {
                if(KNL_Timer_IsOverFlow(&ulCurrentTime,MS_10) == TRUE)
                {
                    KNL_Timer_UpdLocalTime(&ulCurrentTime);
                    DRV_DpRx_MlcRest();
                    printLT(PRINT_PRIO_HIG,"\nRxMlc Reset");
                }
            }
            else
            {
                g_stDpRx.ucRxStatus = 0x02;
            }
             break;
        case 0x02: 
            DRV_DpRx_SoftMsaEn(TRUE);
            Chip_DpRx_ColorSpaceGet();
            CHIP_RxToTx_AviPkgCal();
            if(KNL_Timer_IsOverFlow(&ulCurrentTime,MS_300) == TRUE)
            {
                DRV_DpRx_VidPcrReset();
                KNL_Timer_UpdLocalTime(&ulCurrentTime);
                printLT(PRINT_PRIO_HIG,"\nRxPcr Reset");  
            }
            if(Chip_DpRx_VideoDoneCheck() == TRUE)
            {
                g_stDpRx.ubIsRxVidRdy  = TRUE;
                g_stDpRx.ucRxStatus = 0x01;
            }
             break;
        case 0x01:     
            Chip_DpRx_ColorSpaceGet(); 
            CHIP_RxToTx_AviPkgCal();
            g_stDpRx.ubIsRxPkgRdy = TRUE;
        default:   
        break;
    }
}

void CHIP_DpRx_Handler(void)
{
	Chip_DpRx_ErrorCheck();
    Chip_DpRx_StateDebug();
	Chip_DpRx_StateHandler();
}
