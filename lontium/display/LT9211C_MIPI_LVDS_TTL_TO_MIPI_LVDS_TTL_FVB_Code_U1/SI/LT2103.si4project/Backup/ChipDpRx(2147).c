/******************************************************************************
  * @project: LT2101
  * @file: ChipDpRx.c
  * @author: qihan
  * @company: LONTIUM
  * @date: 2021.10.12
/******************************************************************************/
#include "include.h"

StructDpRx     g_stDpRx ;

void CHIP_DpRx_PowerOnInit(void)
{
    g_stDpRx.ucRxState = STATE_DPRX_POWER_ON;
    g_stDpRx.b1SourceDet =  LOW;
    g_stDpRx.b1DownstreamDeviceReady = FALSE;
    g_stDpRx.b1DownstreamEdidReady  =  FALSE;
    g_stDpRx.pDpRxNotify  = CHIP_DpRx_NotifyHandle;    
}

void Chip_Gpio_Init(void)
{
    #if LT8711UXC == ENABLED
    CHIP_CCGpio_Lt8711uxcInit();
    #endif
    #if LT8711UXD == ENABLED
    CHIP_CCGpio_Lt8711uxdInit();
    #endif
    #if LT8711UXE1 == ENABLED
    CHIP_CCGpio_Lt8711uxe1Init();
    #endif
    #if LT8711UXE2 == ENABLED
    CHIP_CCGpio_Lt8711uxe2Init();
    #endif  
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

void Chip_DpRx_VarInit(void)
{
    #if LT8711UXC == ENABLED
    CHIP_DpRx_Lt8711uxcVarInit();
    #endif
    #if LT8711UXD == ENABLED
    CHIP_DpRx_Lt8711uxdVarInit();
    #endif
    #if LT8711UXE1 == ENABLED
    CHIP_DpRx_Lt8711uxe1VarInit();
    #endif
    #if LT8711UXE2 == ENABLED
    CHIP_DpRx_Lt8711uxe2VarInit();
    #endif     
}

void Chip_DpRx_ColorSpaceUpdata(void)
{
    if((BKDC_EC_REG & BIT6_1)&&(BKDC_A9_REG == 0x07)&&(BKDC_AA_REG == 0x05)&&(BKDC_AB_REG == 0x13)&&((BKDC_BC_REG&0xF0)<= 0x30))//VSC
    {
        g_stDpRx.ucPixelEncoding  =   (BKDC_BC_REG>>4)&0x0f;//00 rgb 01 ycc444 10 ycc222 11 ycc420
        if(g_stDpRx.ucPixelEncoding == 0x02)
        {
            g_stDpRx.ucPixelEncoding = YCC422;
        }
        else  if(g_stDpRx.ucPixelEncoding == 0x01)
        {
            g_stDpRx.ucPixelEncoding = YCC444;
        }
        g_stDpRx.ucColorimetryFormat = BKDC_BC_REG &0x0f;//
        g_stDpRx.b1DynamicRange =     (BKDC_BD_REG>>7)&BIT0_1;// 1 cta range limit  0 vesa range full
        g_stDpRx.ucBitDepth =          BKDC_BD_REG &0x07;////1 8bit 2 10bit 3 12bit
        g_stDpRx.b1VscPkg =            TRUE;//indicate the vsc
    }
    else
    {
        g_stDpRx.ucPixelEncoding  =   (BKDC_EB_REG>>1)&0x03;//00 rgb 01 ycc422 10 ycc444  11 rgb wide
        if(g_stDpRx.ucPixelEncoding == 0x03)
        {
            g_stDpRx.ucPixelEncoding = RGB_WIDE;
        }
        g_stDpRx.ucColorimetryFormat =(BKDC_EB_REG>>3)&0X03;//
        g_stDpRx.b1DynamicRange =     (BKDC_EB_REG>>3)&BIT0_1;// 1 cta  RGB range limit  0 vesa  RGB range full
        g_stDpRx.ucBitDepth =         (BKDC_EB_REG>>5)&0x07;  //1 8bit 2 10bit 3 12bit
        g_stDpRx.b1VscPkg =            FALSE;//in dicate misc0
    }
    g_stDpRx.ulPixelFreqency = ((u32)(BKDA_F8_REG&0x0f)<<16) + ((u16)BKDA_F9_REG <<8) + BKDA_FA_REG;
    g_stDpRx.ulPixelFreqency <<= 1;
    if(g_stDpRx.b1VscPkg == TRUE)
    {
        if(g_stDpRx.ucPixelEncoding == YCC420)
        {
            BKDA_86_REG |= BIT7_1;    //Ycbcr420 enable.
        }
        else
        {
            BKDA_86_REG &= BIT7_0;    //Ycbcr420 enable.
        }
        if(g_stDpRx.ucPixelEncoding == YCC422)////YCC 422
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
    #if CSC_ENABLE == DISABLED
    if(((g_stDpRx.ucBitDepth >= VESA_10BIT)&&(g_stDpRx.ulPixelFreqency > 0x927c0)&&(g_stDpRx.ucPixelEncoding != YCC422))
        ||(BKDA_8F_REG&BIT6_1))// force 8bit enable
    {
        DRV_FreqForce_8BitOut(TRUE);
        g_stDpRx.ucBitDepth = VESA_8BIT;
    }
    else 
    {
        DRV_FreqForce_8BitOut(FALSE);
        if(g_stDpRx.ucBitDepth == VESA_10BIT)
        {
            g_stDpRx.ulPixelFreqency = (g_stDpRx.ulPixelFreqency*4)/5 ;
        }
        else if(g_stDpRx.ucBitDepth == VESA_10BIT)
        {
            g_stDpRx.ulPixelFreqency = (g_stDpRx.ulPixelFreqency*2)/3 ;
        }
    }
    #endif
}

u8 Chip_DpRx_MsaUpdate(u8 b1MsaSoftMode)
{
	u16 usHstart,usHtotal,usHactive,usHsync;
    u16 usHotal_Tmp;
	if(b1MsaSoftMode == SW_MODE)
	{
		BKDA_68_REG &= BIT7_0;
        return FALSE;
	}
	else
	{
        usHotal_Tmp = ((u16)BKDA_64_REG<<8) + BKDA_65_REG;
        usHtotal = ((u16)BKDC_DB_REG<<8) + BKDC_DC_REG;
        usHactive= ((u16)BKDC_E7_REG<<8) + BKDC_E8_REG;
        usHstart = ((u16)BKDC_E1_REG<<8) + BKDC_E2_REG;
        usHsync =  ((u16)BKDC_DF_REG<<8) + BKDC_E0_REG;
        if(g_stDpRx.ucPixelEncoding == YCC420)
        {
            usHtotal  >>= 1;
            usHactive >>= 1;
            usHstart  >>= 1;
            usHsync   >>= 1;
        }
		usHstart -= 4;
		BKDA_64_REG = usHtotal>>8 ;
		BKDA_65_REG = usHtotal ;//htotal
		BKDA_6A_REG = usHactive>>8 ;
		BKDA_6B_REG = usHactive ;//hactive
		BKDA_66_REG = usHstart>>8 ;
		BKDA_67_REG = usHstart ; //hstart
		BKDA_69_REG = usHsync  ;//hsync
		BKDA_68_REG = 0x80|((usHsync>>8)&0x7f);//soft msa enable
        if((usHtotal != usHotal_Tmp)&&((BKDA_DF_REG& BIT6_1) == 0x00))
        {
            return TRUE;
        }
        return FALSE;
	}
}


u8 CHIP_DpRx_DeSkewDet(void)//
{
    return FALSE;
}

u8 Chip_DpRx_PcrStableCheck(void)
{
    static u8 ucVidDoneDetCnt = 0;
    if((BKE7_8C_REG& BIT0_1) == 0x00)//pcrpll unlock
    {
        ucVidDoneDetCnt = 0;
        return UNSTABLE;
    }
    if((BKDA_DF_REG& BIT6_1) == 0x00)//de sync out is disable
    {
        ucVidDoneDetCnt = 0;
        return UNSTABLE;
    }
    if((ucVidDoneDetCnt++) == 10)
    {
        ucVidDoneDetCnt = 0;
        return STABLE;  
    } 
    return UNSTABLE;        
}

void CHIP_DpRx_HpdLowAction(void)
{
    if(g_stDpRx.b1Input_Type_Sel == DP_IN)
    {
        DRV_DpRx_HpdSet(HPD_LOW,IRQ_LOW);
    }
    else
    {
        #if TYPECRX_EN == ENABLED
        CHIP_Ucc_HpdIrqSend(HPD_LOW,IRQ_LOW);
        #endif
    }
    g_stDpRx.b1SourceDet  = LOW;
}

void Chip_DpRx_SetState(u8 ucState)
{
	if(ucState != g_stDpRx.ucRxState)
	{	
		g_stDpRx.ucRxState = ucState;
		g_stDpRx.b1RxStateChanged = TRUE;
//		printLT(PRINT_PRIO_HIG, "\nRxState = 0x%02bx",ucLastState);
	}
}

void Chip_DpRx_SourceDetProc(void)
{
    if(g_stDpRx.ucRxState >= STATE_DPRX_WAITE_SOURCE)//det the dp source device is IN
    {
        if(((g_stDpRx.b1Input_Type_Sel  ==  DP_IN)&&(DRV_DpRx_AuxDcDet()    == TRUE))
        ||((g_stDpRx.b1Input_Type_Sel == TYPEC_IN)&&(CHIP_Ucc_ComDoneFlag() == TRUE)))
        {
            g_stDpRx.b1SourceDet = HIGH;
            g_stDpRx.pDpRxNotify(DPRX_SOURECE_PLUG_EVENT);
        }
        else
        {
            if(g_stDpRx.ucRxState >= STATE_DPRX_DOWNSTREAM_READY)// det the dp source device is out
            {
                Chip_DpRx_SetState(STATE_DPRX_WAITE_SOURCE);
                g_stDpRx.pDpRxNotify(DPRX_SOURECE_UNPLUG_EVENT);
                CHIP_DpRx_HpdLowAction();
            }
        }
    }
}
void Chip_DpRx_StateJudge(void)
{
    if(g_stDpRx.ucRxState >= STATE_DPRX_SET_HPD) 
    {
    	if(g_stDpRx.b1DownstreamDeviceReady == FALSE) // hdmi tx is out
    	{
    		CHIP_DpRx_HpdLowAction(); //pull low hpd.
        	Chip_DpRx_SetState(STATE_DPRX_WAITE_SOURCE);
        }
    }
    if(g_stDpRx.ucRxState >= STATE_DPRX_EQ_FINE_TUNE) // det the dp source re training or MSA not equal vidchk
    {
        if(CHIP_Aux_HandingStauts() == FALSE)
        {
            printLT(PRINT_PRIO_HIG, "\nRetraining");
            Chip_DpRx_SetState(STATE_DPRX_WAITE_LINK_TRAIN);
            g_stDpRx.pDpRxNotify(DPRX_VIDEO_OFF_EVENT);
        }
    }
    if(g_stDpRx.ucRxState == STATE_DPRX_PLAY_BACK)  //det mas chg
    {
        if(Chip_DpRx_MsaUpdate(SW_MODE) == TRUE)
        {
            printLT(PRINT_PRIO_HIG, "\nPCR unstable");
            Chip_DpRx_SetState(STATE_DPRX_MSA_CHECK);
            g_stDpRx.pDpRxNotify(DPRX_VIDEO_OFF_EVENT);
        }
    }	
    if(g_stDpRx.ucRxState == STATE_DPRX_PLAY_BACK)
    {
        g_stDpRx.pDpRxNotify(DPRX_VIDEO_ON_EVENT);
    }
    #if DPRX_HDCP_DEC_MODE != NO_HDCP 
    if(g_stDpRx.ucRxState >= STATE_DPRX_WAITE_LINK_TRAIN) // det the hdcp status chg
    {
        if(g_stDpRx.b1HdcpDecIrqEvt == HPD_IRQ_EVENT)
        {
            g_stDpRx.b1HdcpDecIrqEvt = NONE_EVENT;       //update flag
            g_stAuxStatus.b1ReHdcpDecEvt = HPD_IRQ_EVENT;
            if ((BKE6_01_REG & BIT6_1) == 0x00)          //hdcp2.3 rx int
            {
                DRV_Interrupt_Set(IRQ_RXHDCP2X_INT,ON);//
            }
            KNL_Delay1us(100);
            if(g_stDpRx.b1Input_Type_Sel == DP_IN)
            {
                DRV_DpRx_HpdSet(HPD_HIGH, IRQ_HIGH);
            }
            else
            {
                #if TYPECRX_EN == ENABLED
                CHIP_Ucc_HpdIrqSend(HPD_HIGH,IRQ_HIGH);
                #endif
            }
        }
    }
    #endif   
}

void Chip_DpRx_StateHandler(void)
{ 
    static u32 ulCurrentTime = 0;
    switch(g_stDpRx.ucRxState)
    {
        case STATE_DPRX_POWER_ON: //01
            #if TYPECRX_EN == ENABLED
			Chip_Gpio_Init();
            CHIP_CC_VarInit(); 
            CHIP_Dcc_TmpIni();
            DRV_CCPHY_DigSet(); 
            DRV_DpRx_PhyShut();
            #endif
            Chip_DpRx_SetState(STATE_DPRX_INPUT_TYPE_DET);
            break;
        case STATE_DPRX_INPUT_TYPE_DET://02
            if(g_stDpRx.b1RxStateChanged == TRUE)
			{
				KNL_Timer_UpdLocalTime(&ulCurrentTime);
				g_stDpRx.b1RxStateChanged = FALSE;
			}
            if(KNL_Timer_IsOverFlow(&ulCurrentTime,MS_10) == TRUE)
            {
                Chip_DpRx_DpOrTypecDet();
                DRV_DpRx_1MResiEn();
                Chip_DpRx_SetState(STATE_DPRX_WAITE_SOURCE);
            } 
            break;
        case STATE_DPRX_WAITE_SOURCE: //03
            if(g_stDpRx.b1SourceDet == HIGH)
            {
                DRV_DpRx_PhyShut();
                Chip_DpRx_SetState(STATE_DPRX_DOWNSTREAM_READY);
                printLT(PRINT_PRIO_HIG,"\nRx Connect");
            }
            break;
        case STATE_DPRX_DOWNSTREAM_READY://04
            if(g_stDpRx.b1DownstreamEdidReady == TRUE) //hdmi tx edid read OK
            {
                Chip_DpRx_SetState(STATE_DPRX_SET_HPD);
            }
            break;
        case STATE_DPRX_SET_HPD://05
            if(g_stDpRx.b1RxStateChanged == TRUE)
			{
				KNL_Timer_UpdLocalTime(&ulCurrentTime);
				g_stDpRx.b1RxStateChanged = FALSE;
			}
            if(KNL_Timer_IsOverFlow(&ulCurrentTime,MS_50) == TRUE)
            {
                Chip_DpRx_VarInit();
                DRV_DpRx_SettingInit(); //including the dp rx hpd high attention
                #if DPRX_HDCP_DEC_MODE != NO_HDCP
                DRV_DpRx_HdcpInit(DPRX_HDCP_DEC_MODE);
                #endif
                CHIP_Aux_TrainigStatusClear();
                if(g_stDpRx.b1Input_Type_Sel == DP_IN)
                {
                    DRV_DpRx_HpdSet(HPD_HIGH,IRQ_LOW);
                }
                else
                {
                    #if TYPECRX_EN == ENABLED
                    CHIP_Ucc_HpdIrqSend(HPD_HIGH,IRQ_LOW);
                    #endif
                }
                Chip_DpRx_SetState(STATE_DPRX_WAITE_LINK_TRAIN);
            }
            break; 
        case STATE_DPRX_WAITE_LINK_TRAIN://06
            if(CHIP_Aux_HandingStauts() == TRUE) //rx trainig done
            {
                Chip_DpRx_SetState(STATE_DPRX_EQ_FINE_TUNE);
            }
            break;
        case STATE_DPRX_EQ_FINE_TUNE://07
            if(g_stDpRx.b1RxStateChanged == TRUE)
            {
                KNL_Timer_UpdLocalTime(&ulCurrentTime);
                g_stDpRx.b1RxStateChanged = FALSE;
            }
            if(KNL_Timer_IsOverFlow(&ulCurrentTime,MS_200) == TRUE)
            {
                printLT(PRINT_PRIO_TEST, "\nAux Done");
                CHIP_DpRx_EqScan();   
                Chip_DpRx_SetState(STATE_DPRX_HDCP_CHECK);
            }   
            break;
		case STATE_DPRX_HDCP_CHECK://08
			Chip_DpRx_SetState(STATE_DPRX_DEPACKET_CHECK);
			break;   
        case STATE_DPRX_DEPACKET_CHECK: //09
            Chip_DpRx_SetState(STATE_DPRX_MSA_CHECK);
        case STATE_DPRX_MSA_CHECK://0A
            if(g_stDpRx.b1RxStateChanged == TRUE)
			{
				KNL_Timer_UpdLocalTime(&ulCurrentTime);
				g_stDpRx.b1RxStateChanged = FALSE;
			}
            DRV_FreqForce_8BitOut(FALSE);
			Chip_DpRx_MsaUpdate(HW_MODE); 
            if(CHIP_DpRx_DeSkewDet() == TRUE)
            {
                if(KNL_Timer_IsOverFlow(&ulCurrentTime,MS_50) == TRUE)
                {
                    DRV_DpRx_MainLinkCtrlReset();//?
                    KNL_Timer_UpdLocalTime(&ulCurrentTime);
                }
            }
            else
            {
                Chip_DpRx_SetState(STATE_DPRX_PCR_CONFIG);
            }
            break;
        case  STATE_DPRX_PCR_CONFIG://0B
            if(g_stDpRx.b1RxStateChanged == TRUE)
			{
				KNL_Timer_UpdLocalTime(&ulCurrentTime);
				g_stDpRx.b1RxStateChanged = FALSE;
			}
            Chip_DpRx_ColorSpaceUpdata();
            CHIP_RxToTx_AviPkgCal();
            Chip_DpRx_MsaUpdate(SW_MODE);
            DRV_DeepColor_TenBitSet(g_stDpRx);
            if(KNL_Timer_IsOverFlow(&ulCurrentTime,MS_500) == TRUE)
            {
                DRV_DpRx_VidPcrReset();
                KNL_Timer_UpdLocalTime(&ulCurrentTime);
            }
            if(Chip_DpRx_PcrStableCheck() == TRUE)
            {          
                Chip_DpRx_SetState(STATE_DPRX_AUDIO_CONFIG);
            }
            break;
        case STATE_DPRX_AUDIO_CONFIG://0C
			Chip_DpRx_SetState(STATE_DPRX_PLAY_BACK);
			break;    
        case STATE_DPRX_PLAY_BACK://0D    
            Chip_DpRx_ColorSpaceUpdata(); 
            CHIP_RxToTx_AviPkgCal();
            break;
        default:   
            break;
    }
}

void CHIP_DpRx_Handler(void)
{
	Chip_DpRx_SourceDetProc();
	Chip_DpRx_StateJudge();
	Chip_DpRx_StateHandler();
}
