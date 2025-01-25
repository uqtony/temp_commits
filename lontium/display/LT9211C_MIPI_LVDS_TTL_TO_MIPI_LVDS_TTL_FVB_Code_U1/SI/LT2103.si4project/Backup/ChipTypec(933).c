//////////////////////////////////////
//Project:   LT2101
//Filename:  I2CMast.c
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#include "Include.h"
#if TYPECRX_EN == ENABLED

u8 code szCC_CtrlMsg[][2]= {
{0x4A,0x0A},//PR_SWAP           0
{0x46,0x0F},//PS_RDY	        1
{0x43,0x02},//ACCEPT  UFP SINK  2
{0x44,0x02},//reject upf sink   3
{0x4b,0x0f},//Vconn Swap        4
{0x49,0x03},//DR_Swap           5
{0x90,0x0f},//not support       6
{0x4d,0x01},//soft reset        7
{0x42,0x00},//gotomin           8
{0x45,0x00},//ping              9
{0x47,0x00},//get_source_cap
{0x48,0x00},//get_sink_cap
{0x4c,0x00},//wait
{0x4e,0x00},//data_reset
{0x4f,0x00},//data_reset_complete
{0x51,0x00},//get_source_cap_extended
{0x52,0x00},//get_status
{0x53,0x00},//fr_swap
{0x54,0x00},//get_pps_status
{0x55,0x00},//get_country_codes
{0x56,0x00},//get_sink_cap_extended
{0x57,0x00},//get_source_info
{0x58,0x00},//get_version
};

u8 code szCC_DataMsg[][10]={
{0x41,0x11,0x96,0x90,0x01,0x3e},//0 Source Capabilities Message	
{0x42,0x10,0x5a,0x68,0x01,0x13},//1  Request Message	
{0x4F,0x26,0x42,0x80,0x00,0xFF,0x00,0x00,0x01,0xFF},//2 Discover SVID Responder ACK 2
{0x4F,0x28,0x43,0x80,0x01,0xFF,0X05,0x14,0X14,0x00},//3 Discover Modes Responder ACK	3 4lane
{0x4F,0x28,0x43,0x80,0x01,0xFF,0X05,0x1c,0X1C,0x00},//4 Discover Modes Responder ACK    4	2lane
{0x4F,0x1A,0x44,0x81,0x01,0xFF},// Enter Mode  5
{0x4F,0x1A,0x45,0x81,0x01,0xFF},// Exit Mode   6
{0x4F,0x2C,0x50,0x81,0x01,0xFF,0x0a,0x00,0x00,0x00},//7 DP Status Updata  HPD Low ,No IRQ_HPD	  7
{0x4F,0x2C,0x50,0x81,0x01,0xFF,0x8a,0x00,0x00,0x00},//8 DP Status Updata  HPD HIGH ,No IRQ_HPD  8
{0x4F,0x1E,0x51,0x81,0x01,0xFF},                    //9 0x11 DP Config   9
{0x4F,0x22,0x06,0x81,0x01,0xFF,0x0a,0x00,0x00,0x00},//10 Attention HPD LOW,No IRQ_HPD 	  10
{0x4F,0x22,0x06,0x81,0x01,0xFF,0x8a,0x00,0x00,0x00},//11 Attention HPD High,No IRQ_HPD	  11
{0x4F,0x22,0x06,0x81,0x01,0xFF,0x8a,0x01,0x00,0x00},//12 Attention HPD HIGH,IRQ_HPD   12
{0x44,0x12,0x2c,0x91,0x01,0x2e},                   // 13 get sink cap	 13
{0x4F,0x24,0x43,0x80,0x61,0x2f,0x00,0x00,0x00,0x00}, //14 0x612f
{0x4F,0x16,0x44,0x82,0x61,0x2f}, // 15 0x612f
{0x44,0x12,0x2c,0x91,0x81,0x2f}, //get sink cap	16 
{0x4F,0x1A,0x45,0x81,0x81,0x2f},// Exit Mode   17

{0x44,0x12,0x2c,0x91,0x01,0x06}, // 18 get sink cap	 18
{0x44,0x12,0x2c,0x91,0x81,0x27}, //19 get sink cap	19 

{0x4F,0x28,0x83,0x80,0x01,0xFF,0X05,0x14,0X14,0x00},// Discover Modes Responder ACK	20 4lane
{0x4F,0x28,0x83,0x80,0x01,0xFF,0X05,0x1c,0X1C,0x00},// Discover Modes Responder ACK 21	2lane
};

u8 code szLast_DataOrder_Buffer[2]={0x00,0x00};
u8 szCC_DiscoverIDMsg[22]= 
{0x4f,0x54,0x41,0x80,0x00,0xff,0x00,0x00,0x00,0x6c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00};//Discover Identity 0	
 
u8 szCC_SourceCapExt[30]= 
{0x81,0xfb,0x18,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x0b,0x00,0x00};

StructAms StructAmsType;

StructCcStatus DCCStatus;
StructCcStatus UCCStatus;
StructCcMsg DCCMSG;
StructCcMsg UCCMSG;    
//===========================================
//func  :used to indicate the typec communication is done ,when new cc communction must be cleared zero
//input :N/A
//output:1:meas cc is done , 0 means cc is on-going
//return:void
//Info  :N/A
//===========================================
u8 CHIP_Ucc_ComDoneFlag(void)
{
    if(UCCStatus.u1IsCc_done == TRUE)
    {
		return TRUE;
    }
    return FALSE;
}

//=============================================
//func  :send the attetion flage for the hpd or irq
//input :N/A
//output:1:meas cc is done , 0 means cc is on-going
//return:void
//Info  :N/A
//==============================================

void CHIP_Ucc_HpdIrqSend(bool IsAttentionHigh, bool IsIrqHigh)
{
    UCCStatus.u1Multi_Function = (g_stDpRx.ucRxMaxLaneCount == 4)?(0):(1);
    if(IsAttentionHigh == FALSE)
    {
         UCCMSG.pDataOrder = szCC_DataMsg[10];
		 UCCStatus.ucVDM_Step &= BIT6_0;
         printLT(PRINT_PRIO_HIG,"\nAttention Low");   
    }
    else
    {
        if(IsIrqHigh == FALSE)
        {
             UCCMSG.pDataOrder = szCC_DataMsg[11];
        }
        else
        {
             UCCMSG.pDataOrder = szCC_DataMsg[12]; 
        }
		UCCStatus.ucVDM_Step |= BIT6_1;
        printLT(PRINT_PRIO_HIG,"\nAttention High");//need update 
    } 
    Chip_Send_MessageUcc();
}
    
    
void CHIP_Dcc_TmpIni(void)
{
	DCCMSG.ucCcVersion = 2;
	DCCStatus.u1AdapterWithPD =0;
	DCCMSG.ucMessageID = 0;
	DCCStatus.u1Charger_Scan = 1;
    UCCStatus.u1Flag_Source_Send = 0;
    DCCStatus.u1DataRole = 0;
	DCCStatus.u1PowerRole = 0;
	DCCStatus.u1Msg_ID_Change = 1;
	DCCStatus.ucRetryCounter = 0;
	DCCStatus.u1FrTriggle = 0;
	DCCMSG.u1RcvGoodCRC =  1;
}
void CHIP_Typec_VarInit(void)
{
	UCCStatus.u1IsCc_done = 0;
	UCCStatus.u1DataRole = 0;
	UCCStatus.u1PowerRole = 0;
	UCCStatus.u1Msg_ID_Change = 1;
	UCCStatus.ucPRSended = 0;
	UCCStatus.ucPRSwaping = 0;
	UCCStatus.ucPRSwaped = 0;
	UCCStatus.ucFRSwaping= 0;
	UCCStatus.u1VconnSwap_En = 0;
	UCCStatus.ucDrSwap_En = 0;
	UCCStatus.u1PrDone = 0;
	UCCStatus.ucFlow_Step = 0;
	UCCStatus.u1WaitMsg_Receive = 0;
	UCCStatus.u1PsRdy_Send  = 0;
	UCCStatus.u1Toggle_enable = 1;
	UCCStatus.ucSwap_Sent = 0;
	UCCStatus.u1Multi_Function = 0;
	UCCStatus.ucContract_Succeed =0;
    UCCStatus.ucRetryCounter = 0;
    UCCMSG.ucCcVersion = 2;	
	UCCMSG.ucMessageID_New  =0xfe;
	UCCMSG.ucMessageID_Tmp = 0xff;
	UCCMSG.ucMsgType_Tmp = 0xff;
	UCCMSG.ucLastMsgType = 0xff;
	UCCMSG.ucMessageID = 0;
	UCCMSG.u1Vdm_Msg =0;
	UCCMSG.u1RcvGoodCRC = 1;
	UCCMSG.pBuffer_Order = szLast_DataOrder_Buffer;
	UCCMSG.pLast_DataOrder = &szLast_DataOrder_Buffer[1];
	UCCStatus.ucVDM_Step = 0;
	
    UCCStatus.u1IsFlip = FALSE;
    UCCStatus.u1Flag_Source_Send = 0;
    UCCStatus.u1Toggle_DFP_EN = FALSE;
    StructAmsType.ucBist_Ams = 0;
    UCCStatus.u1Hardreset_Rec = 0;
    UCCStatus.ucnUccSourceCapCnt = 0;
	TR2 = 0;		
}

//=====================================//
//IN:
//ucCommandType:control,data,extend,vdm message
//ucMessageType:message type:reject,ps_rdy,request,status,get battery status,etc
//ucVdmType:structed vdm,unstruted vdm
//out:
//message type

u8 CHIP_MsgType_Cal(IN u8 ucCommandType,IN u8 ucMessageType,IN u8 ucVdmType)
{
    u8 ucMessageTypeCal = 0;
    ucMessageTypeCal = ucMessageType;//real message type copy to cal
    switch(ucCommandType)
    {
        case Ctrl_Msg:
        case Data_Msg:
        case Ext_Msg:
            ucMessageTypeCal |= (ucCommandType<<5);
            break;
        case Vdm_Msg:
            if(ucVdmType)
            {
                ucMessageTypeCal |= (ucCommandType<<5);	
            }
            else
            {
                ucMessageTypeCal = 0xff;
            }	
            break;
        default:
            ucMessageTypeCal = 0xff;
        break;
    }
    return	ucMessageTypeCal;
}

void Chip_Ucc_Flip(void)
{
	if(BKD0_B0_REG&0xf0)
	{
		if(CHIP_DccOn_Det(SINK) == TRUE)
		{
			;
		}
		else
		{
            #if DCC_DET_WithCC == 1
            if(((BKE2_27_REG & BIT2_1)== 0x00)&&((BKD0_30_REG&0xf0)||(BKE5_D4_REG&BIT4_1)))//DCC RD Mode
            #else
            if((BKE2_27_REG&BIT2_1)==0x00)&&(BKE5_D4_REG&BIT4_1))//DCC RD Mode
            #endif
			{
				;
			}
			else
			{
				Source_GPIO_Ctrl(IN HIGH); //1,ufP
			}		
		}
	}
	if(((BKE2_17_REG&BIT2_1) == 0x00)&&(UCCStatus.ucPRSwaping != 2)) //
	{
		if(BKD0_B0_REG&0xc0) //??
		{
			BKD0_AF_REG &= BIT1_0;//flip 1 soft
            UCCStatus.u1IsFlip = FALSE;
		}
		else if(BKD0_B0_REG&0x30)//??
		{
			BKD0_AF_REG |= BIT1_1;//flip 1 soft
            UCCStatus.u1IsFlip = TRUE;
		}
	}
}

#if TYPEC_DRSWAP_EN == ENABLED

u8 Chip_RpOn_Scan(void)
{
    u8 ucCC_Connect_State = 0;
    u8 ucCC_Connect_Loop;
    for(ucCC_Connect_Loop= 0;ucCC_Connect_Loop < 150;ucCC_Connect_Loop++)
    {		
        if(BKE2_17_REG&BIT2_1)
        {
            if(BKD0_B0_REG&0x50)
            {
                ucCC_Connect_State = 1;
                break;
            }
            else
            {
                KNL_Delay1us(10);
                ucCC_Connect_State = 0;
            }
        }
        else
        {
            ucCC_Connect_State = 0;
            break;			
        }
    }
    return ucCC_Connect_State;
}

u8 Chip_RdOn_Scan(void)
{
    u8 ucCC_Connect_State = 0;
    u8 ucCC_Connect_Loop;
    for(ucCC_Connect_Loop=0;ucCC_Connect_Loop<150;ucCC_Connect_Loop++)
    {
        if((BKE2_17_REG&BIT2_1)==0x00)
        {
            if(BKD0_B0_REG&0xF0)
            {
                ucCC_Connect_State = 1;
                break;
            }
            else
            {
                KNL_Delay1us(10);
                ucCC_Connect_State = 0;	
            }
        }
        else
        {
            ucCC_Connect_State = 0;
            break;		
        }
    }
    return ucCC_Connect_State;
}

void Chip_Toggle_Init(u8 vaule)
{
    TR2 = 0;
    Source_GPIO_Ctrl(IN LOW);	 
    UCCStatus.u1PrDone = FALSE;
    UCCStatus.ucnUccSourceCapCnt = 0;
    UCCStatus.u1Toggle_enable = TRUE;
    UCCStatus.ucFlow_Step = 0;
    UCCStatus.ucVDM_Step = 0;
    UCCStatus.u1PowerRole = FALSE;
    UCCStatus.u1DataRole =  FALSE;
    UCCStatus.ucPRSwaped  = 0;
    UCCStatus.ucContract_Succeed = 0;
    UCCStatus.u1VconnSwap_En = FALSE;
    UCCStatus.ucDrSwap_En = 0;
    if(vaule)
    {
        DRV_PowerRole_Set(UCC,SOURCE);
        UCCStatus.u1Toggle_DFP_EN = TRUE;
        BKD0_BE_REG |= BIT0_1;//
    }
    else
    {
        DRV_PowerRole_Set(UCC,SINK);
        UCCStatus.u1Toggle_DFP_EN = FALSE;
        BKD0_BE_REG &= BIT0_0;//
    }
}

u8 Chip_Ucc_Toggle(u8 ucFlag)
{
	u8 ucRtn = 0;
	static bool CC_Role = 0;
	static u8 ucStage= 0;
	static u32 ulLastTime= 0;
	if(ucFlag == 0)
	{
		ucStage = 0;
		return ucRtn;
	}
    if(DCCStatus.u1Charger_Scan)//after enter into DCCDET,then do CC_Toggle
    {
        ucStage = 0;
		return ucRtn;
    }
	switch(ucStage)
	{
        case 0:
            KNL_Timer_UpdLocalTime(INOUT &ulLastTime);
            ucStage++;
            break;
        case 1:
            if(UCCStatus.ucContract_Succeed == 0)
            {           
                if((CHIP_DccOn_Det(SINK) == TRUE)&&(UCCStatus.ucPRSwaping != 2)&&(UCCStatus.ucPRSwaped == 0x00))////
                {
                    if(Chip_RpOn_Scan() == 1)
                    {
                        if(UCCStatus.u1Toggle_DFP_EN == TRUE)
                        {
                            printLT(PRINT_PRIO_HIG,"\nDFP Mode");
                            UCCStatus.u1Toggle_DFP_EN = FALSE;
                            UCCStatus.ucnUccSourceCapCnt = 0;
                            UCCMSG.ucMessageID = 0;
                            UCCStatus.u1Toggle_enable = FALSE;
                            UCCStatus.u1PrDone = FALSE;
                            UCCStatus.ucContract_Succeed = 0;
                            UCCStatus.u1PowerRole = TRUE;
                            UCCStatus.u1DataRole = TRUE;	
                            TR2 = 0;
                            ucStage++;
                        }
                    }
                    else if(Chip_RdOn_Scan() == 1)
                    {
                        if(UCCStatus.u1Toggle_DFP_EN == FALSE)
                        {
                            printLT(PRINT_PRIO_HIG,"\nUFP Mode");
                            UCCStatus.u1Toggle_DFP_EN = TRUE;
                            UCCStatus.ucnUccSourceCapCnt = 0;
                            UCCMSG.ucMessageID = 0;
                            UCCStatus.u1Toggle_enable = FALSE;
                            UCCStatus.u1PrDone = FALSE;
                            UCCStatus.ucContract_Succeed = 0;
                            UCCStatus.u1PowerRole = FALSE;
                            UCCStatus.u1DataRole = FALSE;
                            Source_GPIO_Ctrl(IN LOW);			
                            TR2 = 0;
                            ucStage++;
                        }
                    }
                    else if(KNL_Timer_IsOverFlow(&ulLastTime,MS_50) == TRUE)
                    {
                        CC_Role = !CC_Role;
                        Chip_Toggle_Init(CC_Role);
                        KNL_Timer_UpdLocalTime(INOUT &ulLastTime);
                    }
                }
                else
                {
                    ucStage = 0;
                }
            }
            break;
        default:
            ucStage = 0;
            ucRtn = 1;
            break;			
	}
	return ucRtn;
}
#endif
//===============================================================end the toggle ini=========================================================

#if TYPEC_PRSWAP_EN == ENABLED
void Chip_PRSwap_Send(void)
{
    if((UCCStatus.ucPRSended == 1)&&(UCCStatus.u1DataRole == FALSE)&&(UCCStatus.ucPRSwaped==0))
	{
		if(CHIP_DccOn_Det(SINK) == TRUE)
		{
			Adapter_GPIO_Ctrl(IN HIGH);
			DRV_CC_LogicRst(UCC);	
            UCCStatus.ucPRSended = 2;
			Source_GPIO_Ctrl(IN LOW);
			if(Chip_UccOff_Det() == TRUE)
			{
				printLT(PRINT_PRIO_HIG,"\nUCC Off in PRSWAP");
				CHIP_Ucc_OffAction();
			}
			else
			{
                if(UCCStatus.ucPRSwaped == 0x00)
                {                   
                    printLT(PRINT_PRIO_HIG,"\nPrSwap Send");
                    UCCMSG.pDataOrder = szCC_CtrlMsg[0];	
                    UCCStatus.ucPRSwaping = 1;
                    UCCStatus.ucPRSwaped =  1;     
                    UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,PR_Swap,StrVdm);                    
                    Chip_Send_MessageUcc();//// PR_SWAP 1                                    
                }
                else
                {
                    ;
                }
			}		
		}
		else
		{	          
			printLT(PRINT_PRIO_HIG,"\nAda_Lost");            
            DCCStatus.u1Charger_Scan = TRUE;
			UCCStatus.ucPRSwaped = 0;
            UCCStatus.ucPRSended = 0;
			if(UCCStatus.u1IsCc_done == FALSE)
			{
				UCCStatus.u1IsCc_done = TRUE; // Hdmi_Edid = 0x02;
			}
		}		
	}
}

u8 Chip_PrSwap_Det(u8 ucFlag)
{
    u8 ucRtn = 0;
    static u8 ucStage_Change=0;
    static u8 ucStage=0;
    static u32 ulLastTime=0;
    if(ucFlag == 0)
    {	
        ucStage = 0;
        return ucRtn;
    }
    if((UCCStatus.ucFlow_Step >= 2)||(UCCStatus.u1Toggle_enable == TRUE))
    {
        KNL_Timer_UpdLocalTime(&ulLastTime);
        return ucRtn;
    }
    switch(ucStage)
    {
        case 0:
            KNL_Timer_UpdLocalTime(&ulLastTime);
            ucStage_Change = 1;
            ucStage++;
            break;
        case 1:
            if(ucStage_Change)
            {
                ucStage_Change = 0;
                KNL_Timer_UpdLocalTime(&ulLastTime);
            }
            if(KNL_Timer_IsOverFlow(&ulLastTime,SECOND_3) == TRUE)//do not receive source cap
            {
                if(UCCStatus.ucContract_Succeed == 0)
                {
                    if(Chip_UccOff_Det() == FALSE)
                    {
                        DRV_HardReset_Set(UCC);
                        CHIP_Ucc_OffAction();
                    }
                    KNL_Delay1ms(5);
                    ucStage = 0;
                }
                else
                {
                    ucStage_Change = 1;
                    ucStage++;
                }
            }
            else if(UCCStatus.ucContract_Succeed == 1)
            {
                ucStage_Change = 1;
                ucStage++;
            }		
            break;
        case 2:
            if(ucStage_Change)
            {
                ucStage_Change = 0;
                KNL_Timer_UpdLocalTime(&ulLastTime);
            }
            if(KNL_Timer_IsOverFlow(&ulLastTime,MS_1500) == TRUE)
            {      
                Adapter_GPIO_Ctrl(IN LOW);   
                KNL_Delay1ms(30);
                Chip_PRSwap_Send();	
                ucStage_Change = 1;
                ucStage++;
            }
            else if((UCCStatus.ucPRSended==0)||(UCCStatus.ucPRSwaped))
            {
                ucStage_Change = 1;
                ucStage = 0;
            }
            break;
        case 3:
            if(ucStage_Change)
            {
                ucStage_Change = 0;
                KNL_Timer_UpdLocalTime(&ulLastTime);
            }
            if(UCCStatus.ucPRSwaping == 1)
            {
                if(KNL_Timer_IsOverFlow(&ulLastTime,SECOND_3)== TRUE)//can not receive accept
                {						
                    if(Chip_UccOff_Det() == FALSE)
                    {
                        DRV_HardReset_Set(UCC);
                        CHIP_Ucc_OffAction();
                    }
                    KNL_Delay1ms(5);
                    ucStage_Change = 0;
                }
                else
                {
                    ;
                }
            }
            else
            {
                ucStage_Change = 1;
                ucStage++;
            }	
            break;   
        default:
            ucStage = 0;
            ucRtn=1;
            break;			
    }
    return ucRtn;	
}

#endif
#if TYPEC_DRSWAP_EN == ENABLED
void Chip_VconnSwap_Send(void)
{
    if((UCCStatus.u1VconnSwap_En == TRUE)&&(UCCStatus.ucFlow_Step < 2))
    {
        UCCStatus.u1WaitMsg_Receive = FALSE;
        UCCStatus.u1VconnSwap_En = FALSE;
        UCCStatus.ucSwap_Sent |= Vconn_Sent;
        UCCMSG.pDataOrder = szCC_CtrlMsg[4];
        Chip_Send_MessageUcc();//Vconn Swap
        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,VCONN_Swap,StrVdm);
    }		
}
void Chip_DrSwap_Send(void)
{
    if((UCCStatus.ucDrSwap_En == 1)&&(UCCStatus.ucFlow_Step < 2))
    {
        UCCStatus.u1WaitMsg_Receive = FALSE;
        UCCStatus.u1VconnSwap_En = FALSE;
        UCCStatus.ucSwap_Sent &= DR_No_Sent;
        UCCStatus.ucDrSwap_En = 0;
        UCCMSG.pDataOrder = szCC_CtrlMsg[5];	
        Chip_Send_MessageUcc();//DR_Swap
        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,DR_Swap,StrVdm);
    }		
}
void Chip_Wait_Send(void)//use Timer to do this
{
    if((UCCStatus.u1WaitMsg_Receive== TRUE)&&(UCCStatus.ucFlow_Step < 2))
    {
        UCCMSG.pDataOrder = UCCMSG.pLast_DataOrder;
        UCCStatus.u1WaitMsg_Receive = FALSE;
        Chip_Send_MessageUcc();	
    }
}
u8 CHIP_Swap_Scan(u8 ucFlag)
{
	u8 ucRtn = 0;
	static u8 ucStage=0;
	static u32 ulLastTime=0;
	if(ucFlag == 0)
	{
		ucStage = 0;
		return ucRtn;
	}
	if(UCCStatus.ucFlow_Step >= 2)
	{
		ucStage = 0;
		return ucRtn;
	}
	if((UCCStatus.u1VconnSwap_En== FALSE)||(UCCStatus.ucDrSwap_En != 1)||(UCCStatus.u1WaitMsg_Receive== FALSE))
	{
		ucStage = 0;
		return ucRtn;
	}
	switch(ucStage)
	{
		case 0:
			KNL_Timer_UpdLocalTime(&ulLastTime);
			ucStage++;
			break;
		case 1:
            if(KNL_Timer_IsOverFlow(&ulLastTime,MS_550) == TRUE)
            {
                Chip_VconnSwap_Send();
                Chip_DrSwap_Send();
                Chip_Wait_Send();
                KNL_Timer_UpdLocalTime(&ulLastTime);
                ucStage++;
            }
            else
            {
                ;
            }
			break;
		default:
			ucStage = 0;
			ucRtn=1;
			break;			
	}
	return ucRtn;	
}	
u8 CHIP_Ucc_SourceCapSend(u8 ucFlag)
{
	u8 ucRtn = 0;
	u8 ucSourceCapPerCycle = 0;
    static u8 ucStage_Change = 0;
	static u8 ucStage=0;
	static u32 ulLastTime=0;
	if(ucFlag == 0)
	{
		ucStage = 0;
		return ucRtn;
	}
	if(UCCStatus.u1Toggle_enable)
	{
		ucStage = 0;
		return ucRtn;
	}
    if(UCCStatus.ucContract_Succeed) //ource CAP
    {
        ucStage = 0;
		return ucRtn;
    }
	switch(ucStage)
	{
        case 0:
            KNL_Timer_UpdLocalTime(&ulLastTime);
            ucStage++;
            ucStage_Change = 1;
            break;
        case 1:
            if(KNL_Timer_IsOverFlow(&ulLastTime,MS_20) == TRUE)
            {
                KNL_Timer_UpdLocalTime(&ulLastTime);
                ucStage++;
                ucStage_Change = 1;
            }
            break;
        case 2:        
            if((UCCStatus.ucContract_Succeed == 0x00)&&(UCCStatus.u1PowerRole == TRUE)&&(UCCStatus.u1DataRole == TRUE))
            {
                if(BKD0_B0_REG&0x50) //??
                {
                    BKD0_AF_REG &= BIT1_0;//flip 1 soft
                    UCCStatus.u1IsFlip = FALSE;
                }
                else if(BKD0_B0_REG&0x10)//??
                {
                    BKD0_AF_REG |= BIT1_1;//flip 1 soft
                    UCCStatus.u1IsFlip = TRUE;
                }
                if(KNL_Timer_IsOverFlow(&ulLastTime,MS_120) == TRUE)
                {
                    if(UCCStatus.ucnUccSourceCapCnt < nCapsCount)
                    {    
                        UCCStatus.ucnUccSourceCapCnt++;
                        for(ucSourceCapPerCycle = 0; ucSourceCapPerCycle< 4; ucSourceCapPerCycle++)
                        {		
                            if(Chip_RpOn_Scan() == 0)
                            {
                                UCCStatus.u1PowerRole = FALSE;
                                UCCStatus.u1DataRole =  FALSE;
                                UCCStatus.ucPRSwaped  = 0;
                                UCCStatus.ucnUccSourceCapCnt = 0;
                                UCCStatus.u1Toggle_enable = TRUE;
                                UCCStatus.ucContract_Succeed = 0;
                                UCCStatus.u1VconnSwap_En = FALSE;
                                UCCStatus.ucDrSwap_En = 0;
                                Source_GPIO_Ctrl(IN LOW);
                                ucStage = 0;
                                break;
                            }
                            else				
                            {		
                                if(ucStage_Change == 1)
                                {
                                    ucStage_Change = 0;
                                    Adapter_GPIO_Ctrl(IN HIGH);
                                    Source_GPIO_Ctrl(IN HIGH);
                                    KNL_Timer_UpdLocalTime(&ulLastTime);
                                    break;
                                }
                                else
                                {
                                    Adapter_GPIO_Ctrl(IN HIGH);
                                    if(!UCCStatus.ucContract_Succeed) //source cap
                                    {
                                        KNL_Delay1ms(4);
                                        UCCStatus.ucPRSwaped  = 1;	//necessary for dr swap as the role of UFP
                                        UCCStatus.u1PowerRole = TRUE;
                                        UCCStatus.u1DataRole = TRUE;
                                        UCCStatus.u1VconnSwap_En = FALSE;	
                                        UCCStatus.ucDrSwap_En = 0;	
                                        UCCMSG.ucMessageID = 0;
                                        if(DCCStatus.u1AdapterWithPD)	
                                        {
                                            #if PD_PPS_EN == ENABLED
                                            if(UCCMSG.ucCcVersion < 2)//PD2.0
                                            {
                                                UCCMSG.pDataOrder = DCCMSG.szAdapterTmp;
                                            }
                                            else//PD3.0
                                            {
                                                UCCMSG.pDataOrder = DCCMSG.szAdapterCap_For_PD30;
                                            }
                                            #else
                                            UCCMSG.pDataOrder = DCCMSG.szAdapterTmp;
                                            #endif
                                        }	
                                        else
                                        {
                                            UCCMSG.pDataOrder = szCC_DataMsg[0];
                                        }		
                                        UCCStatus.ucFlow_Step = 6;
                                        Chip_Send_MessageUcc();
                                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Data_Msg,Source_Capabilities,StrVdm);	
                                        KNL_Delay1ms(2);
                                    }
                                    else
                                    {
                                        ucStage++;
                                    }	
                                }                                
                            }
                        }
                    }
                    else
                    {
                        UCCStatus.ucnUccSourceCapCnt = nCapsCount;
                    }
                    KNL_Timer_UpdLocalTime(&ulLastTime);
                }
                else                     
                {
                    if(Chip_RpOn_Scan() == 0)
                    {
                        UCCStatus.u1PowerRole = FALSE;
                        UCCStatus.u1DataRole =  FALSE;
                        UCCStatus.ucPRSwaped  = 0;
                        UCCStatus.ucnUccSourceCapCnt = 0;
                        UCCStatus.u1Toggle_enable = TRUE;
                        UCCStatus.ucContract_Succeed = 0;
                        UCCStatus.u1VconnSwap_En = FALSE;
                        UCCStatus.ucDrSwap_En = 0;
                        Source_GPIO_Ctrl(IN LOW);
                        ucStage = 0;
                    }
                }
            }
            else
            {
                ucStage = 0;
            }
            break;
        default:
            ucStage = 0;
            ucRtn = 1;
            break;					
	}	
	return ucRtn;
}
#endif
#if ((TYPEC_PRSWAP_EN == ENABLED)||(TYPEC_DRSWAP_EN == ENABLED))
void CHIP_Ucc_OffAction(void)
{
    KNL_Delay1ms(1);
    BKE2_12_REG &= BIT6_0;
    KNL_Delay1ms(26);//big than 25ms.less than 35ms 
    Source_GPIO_Ctrl(IN LOW);
    DiscSource_GPIO_Ctrl(IN HIGH);
    CHIP_Swap_Scan(0);
    CHIP_Ucc_SourceCapSend(0);
    DRV_CC_LogicRst(UCC);
    DRV_PowerRole_Set(UCC,SINK);
    BKD0_BE_REG &= BIT0_0; //rd
    BKE2_26_REG = 0x04;//DVBUS OFF VOLTAGE	
    if(DCCStatus.u1AdapterWithPD)	
    {
        DCCMSG.pDataOrder = szCC_DataMsg[1];//request 5v
        Chip_Send_MessageDcc();//request 5v
    }
    CHIP_Typec_VarInit();
    KNL_Delay1ms(100);
    DiscSource_GPIO_Ctrl(IN LOW);
    BKE2_12_REG |= BIT6_1;
    printLT(PRINT_PRIO_HIG,"\nUCC Det OFF");
}
//===============================
//detect ucc state
//1 stands for out,0 stands for in
u8 Chip_UccOff_Det(void)
{
	bool CC_Off_Line = FALSE;
	u8 ucCC_Count;	
	if(((BKD0_B0_REG&0xf0)==0x00)||((((BKD0_B0_REG&0xf0)==0x80)||((BKD0_B0_REG&0xf0)==0x20))&&(BKE2_17_REG&BIT2_1))) //UCC OUT
    {
		KNL_Delay1us(15);
		for(ucCC_Count=0;ucCC_Count < 100;ucCC_Count++)
		{
			if(((BKD0_B0_REG&0xf0)==0x00)||((((BKD0_B0_REG&0xf0)==0x80)||((BKD0_B0_REG&0xf0)==0x20))&&(BKE2_17_REG&BIT2_1)))//UCC OUT FOR 1.5MS
			{
				CC_Off_Line = TRUE;
				KNL_Delay1us(15);
			}
			else
			{
				CC_Off_Line = FALSE;
				break;
			}
		}
	}
	return CC_Off_Line;
}
u8 Chip_PSSourceOff_TimerSet(u8 ucFlag)// ps rdy off timer detect
{
    u8 ucRtn = 0;
	static u8 ucStage= 0;
	static u32 ulLastTime= 0;
	if(ucFlag == 0)
	{
		ucStage = 0;
		return ucRtn;
	}
	switch(ucStage)
	{
        case 0:
            KNL_Timer_UpdLocalTime(&ulLastTime);
            ucStage++;
        case 1:          
            if(UCCStatus.ucPRSwaping == 2)
            {
                if(KNL_Timer_IsOverFlow(&ulLastTime,MS_835) == TRUE)//tPSSourceOff
                {                            
                    if(Chip_UccOff_Det() == FALSE)
                    {
                        DRV_HardReset_Set(UCC);
                        CHIP_Ucc_OffAction();
                    }
                    ucStage++;   
                }
                else
                {
                    ;
                }				
            }
            else
            {
                KNL_Timer_UpdLocalTime(&ulLastTime);
                ucStage = 0;
            }
            break;
        default:
            ucStage = 0;
            ucRtn = 1;
            break;			
	}
	return ucRtn;	
}

#endif
#if ((TYPEC_PRSWAP_EN == ENABLED)||(TYPEC_DRSWAP_EN == ENABLED))
u8 CHIP_DccOn_Det(IN u8 ucPow_Role)
{
	if(ucPow_Role & SINK)
	{
        #if DCC_DET_WithCC == 1
        if(((BKE2_27_REG & BIT2_1)==0x00)&&((BKD0_30_REG&0xf0)||(BKE5_D4_REG&BIT4_1)))//DCC RD Mode
        #else
		if((BKE2_27_REG&BIT2_1)==0x00)&&(BKE5_D4_REG&BIT4_1))//DCC RD Mode
        #endif
		{
			return TRUE;
		}
	}
//	if(ucPow_Role & SOURCE)
//	{
//		if((BKE2_27_REG &BIT2_1)&&(BKD0_30_REG&0x50))//DCC RP Mode
//		{
//			return TRUE;
//		}
//	}
	return FALSE;
}
//u8 Chip_Dcc_LostDet(IN u8 ucPow_Role)
//{
//    u8 ucDccState = 0;
//    ucDccState = BKD0_1E_REG&0xf0; //DCC state
//    if(ucPow_Role & SINK)
//    {
//        if((UCCStatus.ucFRSwaping == 0)&&(DCCStatus.u1Charger_Scan == FALSE))
//        {
//            if((BKE2_27_REG & BIT2_1) == 0x00)//Sink Mode
//            {
//                if((ucDccState == 0)&&(DCCStatus.ucDccState_Tmp != 0))
//                {
//                    Adapter_GPIO_Ctrl(LOW);
//                    DCCMSG.ucCcVersion = 2;
//                    DCCStatus.u1Charger_Scan = TRUE;
//                    DCCStatus.u1AdapterWithPD = FALSE;
//                    DCCMSG.ucMessageID = 0;
//                    DCCStatus.u1Charger_Scan = TRUE;                 
//                    DCCStatus.u1DataRole = FALSE;
//                    DCCStatus.u1PowerRole = FALSE;
//                    DCCStatus.u1Msg_ID_Change = TRUE;                  
//                    DCCMSG.u1RcvGoodCRC = TRUE;
//                    UCCStatus.u1PrDone = FALSE;  
//                    UCCStatus.ucPRSended = 0;
//                    UCCStatus.ucPRSwaping = 0;
//                    UCCStatus.ucPRSwaped = 0;		
//                    UCCStatus.ucFlow_Step = 0;
//                    DCCStatus.ucDccState_Tmp = 0;
//                    return TRUE;
//                }
//            }
//        }       
//    }
//    return FALSE;
//}

void Chip_Dcc_CcDet(void)
{
    static u8 HardRst_Cnt;
	u16 ucLoopi;
	if(CHIP_DccOn_Det(SINK) == TRUE)
	{
		if(BKD0_30_REG&0xc0) //
		{
			BKD0_2F_REG &= BIT1_0;//flip 1 soft
		}
		else if(BKD0_30_REG&0x30)//
		{
			BKD0_2F_REG |= BIT1_1;//flip 1 soft
		}
	}
//	else if(CHIP_DccOn_Det(SOURCE) == TRUE)
//	{
//		if(BKD0_30_REG & BIT6_1) //
//		{
//			BKD0_2F_REG &= BIT1_0;//flip 1 soft
//		}
//		else if(BKD0_30_REG & BIT4_1)//
//		{
//			BKD0_2F_REG |= BIT1_1;//flip 1 soft
//		}
//	}
	if((CHIP_DccOn_Det(SINK) == TRUE)&&(DCCStatus.u1Charger_Scan == TRUE)&&(UCCStatus.ucFRSwaping == 0))
	{        
		UCCMSG.szPDP_Value[0] = 0x07;
		UCCMSG.szPDP_Value[1] = 0x07;
		Adapter_GPIO_Ctrl(IN LOW);
		Source_GPIO_Ctrl(IN LOW);
		DCCStatus.u1FrTriggle = FALSE;
		DCCStatus.u1Charger_Scan = FALSE;
		for(ucLoopi = 0; ucLoopi< 1000; ucLoopi++)	 //toggle
		{
			KNL_Delay1ms(1);			
			if(DCCStatus.u1AdapterWithPD)
			{
				break;
			}					
		}
        for(HardRst_Cnt= 0;HardRst_Cnt <= nHardResetCount;HardRst_Cnt++)
        {
            if(DCCStatus.u1AdapterWithPD == 0)
            {                   
                DRV_HardReset_Set(DCC);
                KNL_Delay1ms(500);
            }	
            else
            {
                break;
            }
        }
		#if TYPEC_PRSWAP_EN == ENABLED
		if(CHIP_DccOn_Det(SINK) == TRUE)
		{
            Adapter_GPIO_Ctrl(IN HIGH);
            DCCStatus.ucDccState_Tmp = BKD0_1E_REG&0xf0;
			if(DCCStatus.u1AdapterWithPD == FALSE)
			{
				if((Chip_UccOff_Det() == FALSE)&&(UCCStatus.ucPRSended == 0)&&(UCCStatus.u1PowerRole ==FALSE))	//
				{
					UCCStatus.ucPRSended = 1;
				}
			}
		}
		#endif
	}
}
#endif

void CHIP_CC_Loop(void)
{
	static u8 Discharge_Cnt = 0;
    if(g_stDpRx.u1Input_Type_Sel == DP_IN)
    {
        return;
    }
    if(StructAmsType.ucBist_Ams == 0)
    {
        ;
    }
	switch(UCCStatus.u1PrDone)
	{
        case 0:
            if(UCCStatus.ucFRSwaping == 2)
            {		
                DiscAdapter_GPIO_Ctrl(HIGH);
                for(Discharge_Cnt=0;Discharge_Cnt<100;Discharge_Cnt++)
                {
                    if(CHIP_DccOn_Det(SINK) == TRUE)
                    {
                        KNL_Delay1ms(20);
                    }
                    else
                    {
                        break;
                    }
                }			
                KNL_Delay1ms(100);
                DiscAdapter_GPIO_Ctrl(LOW);
                UCCStatus.ucFRSwaping = 0;
            }
            if(StructAmsType.ucBist_Ams == 0)
            {
                Chip_PSSourceOff_TimerSet(1);
            }
            Chip_Ucc_Flip();
            Chip_Dcc_CcDet();           
            Chip_Ucc_Toggle(1);
            if(StructAmsType.ucBist_Ams == 0)
            {
                CHIP_Ucc_SourceCapSend(1);
                Chip_PrSwap_Det(1);
            }
            if((UCCStatus.ucPRSwaping != 2)&&(UCCStatus.ucContract_Succeed))//det UCC all the time
            {
                if(Chip_UccOff_Det()==TRUE)
                {			
                    CHIP_Ucc_OffAction();
                }
            }           
            break;
        case 1:
            if(StructAmsType.ucBist_Ams == 0)
            {
                CHIP_Swap_Scan(1);
            }
            if(Chip_UccOff_Det() == TRUE)
            {
                CHIP_Ucc_OffAction();
            }
            break;
        default:
            break;			
	}
}

#endif


