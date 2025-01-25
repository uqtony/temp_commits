/******************************************************************************
  * @project: LT2101
  * @file: ChipHdmiTx.c
  * @author: qihan
  * @company: LONTIUM
  * @date: 2021.10.12
/******************************************************************************/
#include "include.h"

void CHIP_HdmiTx_HpdLowAction(void)
{
    DRV_HdmiTx_PhyDis();
    g_stHdmiTx.ubIsTxEdidRdy = FALSE;
}

void Chip_HdmiTx_ErrorCheck(void)
{
    if(g_stHdmiTx.ucTxStatus <= 0x09)
    {
        if(DRV_HdmiTx_HpdDet() == FALSE) //hdmi hpd is low
        {
            g_stDpRx.ucRxStatus = 0x09;//Typec Rx CC is done or dp is ok
            g_stHdmiTx.ucTxStatus = 0x0a;
            CHIP_DpRx_HpdLowAction();
            CHIP_HdmiTx_HpdLowAction();
        }
    }	
}

void Chip_HdmiTx_StateDebug(void)
{
	static u8 ucLastState = 0;
	if(ucLastState != g_stHdmiTx.ucTxStatus)
	{
		ucLastState = g_stHdmiTx.ucTxStatus;
		printLT(PRINT_PRIO_HIG, "\n==========================TxState[0x%02bx]",ucLastState);
	}
}

void Chip_HdmiTx_StateHandler(void)
{
    static u32 ulCurrentTime = 0;
    switch(g_stHdmiTx.ucTxStatus)
    {
        case 0xff:    
            DRV_HmdiTx_SettingIni();    
            g_stHdmiTx.ucTxStatus = 0x0a;
            break;
        case 0x0a:
            g_stHdmiTx.ubIsTxEdidRdy = FALSE;
            if(g_stDpRx.ubIsRxRdy == FALSE) //Typec Rx CC is done or dp is ok
            {
                return;
            }
            if(DRV_HdmiTx_HpdDet() == TRUE) //hdmi hpd is high
            {
                printLT(PRINT_PRIO_HIG,"\nHdmiTx Hpd High");
                DRV_HmdiTx_EdidRead(szEdid_Data);
                g_stHdmiTx.ubIsTxEdidRdy = TRUE;
                g_stHdmiTx.ucTxStatus = 0x09;
            }
            break;
        case 0x09: 
            if(g_stDpRx.ubIsRxVidRdy  == TRUE)//rx vide is OK
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
            if(g_stDpRx.ubIsRxPkgRdy == TRUE)// dp rx color is ok and rx video ok
            {
                g_stHdmiTx.ucTxStatus = 0x04;
                DRV_HdmiTx_ColorSpaceSet(g_stHdmiTx.ucszAviPkt,g_stHdmiTx.ucBitDepth,g_stHdmiTx.ucHdmiVic);
                DRV_HdmiTx_Hdmi20Get(DRV_DpRx_PcrPllTbcr() == TRUE);
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
                printLT(PRINT_PRIO_HIG,"\nHdmiTx Hdcp Enable");
                DRV_HdmiTx_HdcpSet();
                KNL_Timer_UpdLocalTime(&ulCurrentTime);
                g_stHdmiTx.ucTxStatus = 0x02;
            }
            break;
        case 0x02:
            DRV_HdmiTx_ColorSpaceSet(g_stHdmiTx.ucszAviPkt,g_stHdmiTx.ucBitDepth,g_stHdmiTx.ucHdmiVic);
            if(KNL_Timer_IsOverFlow(&ulCurrentTime,MS_200) == TRUE)
            {
                printLT(PRINT_PRIO_HIG,"\nHdmiTx Audio Enable");
                DRV_HdmiTx_Audio();
                g_stHdmiTx.ucTxStatus = 0x01;
            }
            break;
        case 0x01:  
            DRV_HdmiTx_ColorSpaceSet(g_stHdmiTx.ucszAviPkt,g_stHdmiTx.ucBitDepth,g_stHdmiTx.ucHdmiVic);       
        default:  
        break;
    }
}

void Chip_HdmiTx_Handler(void)
{
	Chip_HdmiTx_ErrorCheck();
    Chip_HdmiTx_StateDebug();
	Chip_HdmiTx_StateHandler();
}