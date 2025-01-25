//////////////////////////////////////
//Project:   LT2101
//Filename:  BasicTypec.c
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#include "Include.h"

////====================================
//NOTE:BKFC_AF_REG--BKE5_D4_REG BIT4
//Dvbus on:E5D4 bit4
//Dvbus off:E5D4 bit5  D02F:bit5
//Uvbus on:E5D2 bit4
//Uvbus off:E5D2 bit5  D0AF:bit5

//=======================================

u8 code CC_Ctrl_Msg[][2]= {
{0x4A,0x0A},//PW_SWAP 0
{0x46,0x0F},//PS_RDY	1
{0x43,0x02},//ACCEPT  UFP SINK 2
{0x44,0x02},//reject upf sink  3
{0x4b,0x0f},//Vconn Swap 4
{0x49,0x03},//DR_Swap 5
{0x90,0x0f},//not support 6
{0x4d,0x01},//soft reset 7
};

u8 code CC_Data_Msg[][10]={
{0x41,0x11,0x96,0x90,0x01,0x3e},//0 Source Capabilities Message	
{0x42,0x10,0x5a,0x68,0x01,0x13},//1  Request Message	
{0x4F,0x26,0x42,0x80,0x00,0xFF,0x00,0x00,0x01,0xFF},//2 Discover SVID Responder ACK 2
{0x4F,0x28,0x43,0x80,0x01,0xFF,0X05,0x04,0X04,0x00},//3 Discover Modes Responder ACK	3 4lane
{0x4F,0x28,0x43,0x80,0x01,0xFF,0X05,0x0c,0X0C,0x00},//4 Discover Modes Responder ACK  4	2lane
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

{0x4F,0x28,0x83,0x80,0x01,0xFF,0X05,0x04,0X04,0x00},// Discover Modes Responder ACK	20 4lane
{0x4F,0x28,0x83,0x80,0x01,0xFF,0X05,0x0c,0X0C,0x00},// Discover Modes Responder ACK  21	2lane
};

u8 code Last_DataOrder_Buffer[2]={0x00,0x00};
u8 code CC_Discover_Id[22]= 
{0x4f,0x54,0x41,0x80,0x00,0xff,0x00,0x00,0x00,0x6c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00};//Discover Identity 0	
u8 CC_Source_Cap_Ext[30]= 
{0x81,0xfb,0x18,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x0b,0x00,0x00};
#if PD_PPS_EN == 1
u8 Loc_of_PPS[6]={0x00,0x00,0x00,0x00,0x00,0x00};
u8 AdapterTmp_PD[30] = {0x00};
#endif
u8 PDP_Value[2]={0x00,0x00};
u8 Chunked_Message[6]={0x00};	
u8 UCC_Mode_Msg[10]={0x00};
u8 AdapterTmp_Ori[30] = {0x00};
u8 AdapterTmp_PD30[30] = {0x00};
u8 Lane_Count_Ini;


#if TYPECRX_EN == ENABLED

void TR2_Set(void)//4ms
{
	TH2 = 0xd0;
	TL2 = 0x00;
}
//===========================================
//func  :used to indicate the typec communication is done ,when new cc communction must be cleared zero
//input :N/A
//output:1:meas cc is done , 0 means cc is on-going
//return:void
//Info  :N/A
//===========================================
bool CHIP_Ucc_ComDoneFlag(void)
{
    if(UCCStatus.IsCc_done == TRUE)
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
    UCCStatus.Attention_flag = IsAttentionHigh;
    if(IsAttentionHigh == FALSE)
    {
        UCCMSG.DataOrder = UCCMSG.DataOrder = CC_Data_Msg[10];
    }
    else
    {
        if(IsIrqHigh == FALSE)
        {
            UCCMSG.DataOrder = UCCMSG.DataOrder = CC_Data_Msg[11];
        }
        else
        {
            UCCMSG.DataOrder = UCCMSG.DataOrder = CC_Data_Msg[12]; 
        }
    } 
    Send_MessageUcc();
}

void Typec_Var_Init(void)
{
	UCCStatus.IsCc_done = FALSE;
	UCCStatus.DataRole = 0;
	UCCStatus.PowerRole = 0;
	UCCStatus.Lane_Count = DPRX_LINK_COUNT;
    #if LT8711UXC == ENABLED
	UCCStatus.CcInput_type = MALE;
	UCCStatus.IsFlip = FALSE;
    #endif
    #if LT8711UXD == ENABLED
	UCCStatus.CcInput_type = MALE;
	UCCStatus.IsFlip = FALSE;
    #endif
    #if LT8711UXE1 == ENABLED
	UCCStatus.CcInput_type = (BKE5_DB_REG>>2)&BIT0_1;
	if((UCCStatus.PowerRole==FALSE)&&(BKD0_B0_REG&0xc0))
	{
		UCCStatus.IsFlip = FALSE;
		BKD0_AF_REG &= BIT1_0;
	}
	else if((UCCStatus.PowerRole==FALSE)&&(BKD0_B0_REG&0x30))
	{
		UCCStatus.IsFlip = TRUE;
		BKD0_AF_REG |= BIT1_1;
	}
    #endif
    #if LT8711UXE2 == ENABLED
	UCCStatus.CcInput_type = (BKE5_DB_REG>>2)&BIT0_1;
	if((UCCStatus.PowerRole==FALSE)&&(BKD0_B0_REG&0xc0))
	{
		UCCStatus.IsFlip = FALSE;
		BKD0_AF_REG &= BIT1_0;
	}
	else if((UCCStatus.PowerRole==FALSE)&&(BKD0_B0_REG&0x30))
	{
		UCCStatus.IsFlip = TRUE;
		BKD0_AF_REG |= BIT1_1;
	}
    #endif    

	UCCStatus.Msg_ID_Change = 1;
	UCCMSG.MsgNum = 0;
	UCCMSG.CcVersion = 2;
	UCCStatus.source_stop =0;
	
	UCCStatus.Attention_flag = 0;
	UCCStatus.PRSended = 0;
	UCCStatus.ReadySendPR = 0;
	UCCStatus.PRSwaping = 0;
	UCCStatus.PRSwaped = 0;
	UCCStatus.FRSwaping= 0;
	UCCStatus.vconn_swap_en = 0;
	UCCStatus.dr_swap_en = 0;
	UCCStatus.PrDone = 0;
	UCCStatus.TypecInt= 0;
	UCCStatus.step = 0;
	UCCStatus.Wait_Receive = 0;
	UCCStatus.ps_rdy_send  = 0;
	UCCStatus.Toggle_enable = 1;
	UCCStatus.Swap_Sent = 0;
	UCCStatus.Usb30_Flag = 0;
	UCCStatus.source_stop =0;
	UCCMSG.MessageID_New  =0xfe;
	UCCMSG.MessageID_Tmp = 0xff;
	UCCMSG.MsgType_Tmp = 0xff;
	UCCMSG.LastMsg = 0xff;
	UCCMSG.MsgNum = 0;
	UCCMSG.ExtMsg = 0;
	UCCMSG.vdm_message =0;
	UCCMSG.RcvGoodCRC = 1;
	UCCStatus.Msg_Resend_Num = 0;
	UCCMSG.Buffer_Order = Last_DataOrder_Buffer;
	UCCMSG.Last_DataOrder = &Last_DataOrder_Buffer[1];
	UCCStatus.VDM_Step = 0;
    //DCC 	
	DCCStatus.DataRole = 0;
	DCCStatus.PowerRole = 0;
	DCCStatus.Msg_ID_Change = 1;
	DCCMSG.MsgNum = 0;
	DCCMSG.CcVersion = 2;
	
	DCCStatus.Msg_Resend_Num = 0;
	DCCStatus.FrTriggle = 0;
	DCCMSG.ExtMsg = 0;
	DCCMSG.RcvGoodCRC = 1;
	DCCMSG.vdm_message =0;
	DCCStatus.Msg_ID_Change = 1;
		
}
void Request_Ucc_Fix(void)
{
	u16 Max_Cur_5V = 0;
	Max_Cur_5V = (UCCMSG.RcvDate[1]&0x03);
	Max_Cur_5V <<= 8;
	Max_Cur_5V |= UCCMSG.RcvDate[0];
    UCCMSG.RequestBuf[0]= 0x42;
    UCCMSG.RequestBuf[1]= 0x10;
    UCCMSG.RequestBuf[2]=  UCCMSG.RcvDate[0];
    UCCMSG.RequestBuf[3]= (UCCMSG.RcvDate[1]&0x03)|((UCCMSG.RcvDate[0]&0x3f)<<2);
    UCCMSG.RequestBuf[4]= (((UCCMSG.RcvDate[0]&0xc0)>>6)|((UCCMSG.RcvDate[1]&0x03)<<2));
	UCCMSG.RequestBuf[4] &= 0x7f;//Unchunked Extended Messages Not Supported
    UCCMSG.RequestBuf[5]= 0x13;
	if(Max_Cur_5V<300)//mismatch
	{
	 	UCCMSG.RequestBuf[5] |= 0x04;		
	}
}
u8 Sum(u8 xsum)
{
	xsum = xsum+2;
	if(xsum > 0x0e)
	{
	 	xsum = 0;
	}
	else
	{;}
	return xsum;
}
void Send_MessageUcc(void)
{
    u8 SendData,SendMegSndDataOffset;
	static u8 Message_ID_Send = 0x00;
	UCCMSG.Buffer_Order = UCCMSG.DataOrder;
    UCCMSG.TotalData = 2;
    for(SendMegSndDataOffset=0; SendMegSndDataOffset<UCCMSG.TotalData; SendMegSndDataOffset++)
    {
        SendData = *UCCMSG.DataOrder;
        UCCMSG.DataOrder++;
        if(SendMegSndDataOffset==1)
        {		
            UCCMSG.TotalData = ((SendData & 0x70)>>2)+2;
            SendData &=0xF0;
			if(UCCStatus.Msg_ID_Change == 1)
			{
				Message_ID_Send = UCCMSG.MsgNum;
				UCCMSG.MsgNum = Sum(UCCMSG.MsgNum);			
			}
			else
			{
				;
			}
			SendData = (SendData|Message_ID_Send);
            (UCCStatus.PowerRole)?(SendData |= 0x01):(SendData &= 0xfe);
        }
        else if(SendMegSndDataOffset == 0)
        {
            SendData &= 0x1F;
			if(UCCMSG.CcVersion < 0x02)
            {
				SendData |=  0x40;
            }
            else
            {
				SendData |=  0x80;
            }
            (UCCStatus.DataRole)?(SendData|=0x20):(SendData &= 0xdf);
        }
		else if((UCCStatus.Usb30_Flag)&&(SendMegSndDataOffset== 6))
		{
			SendData |= 0x10; // Multifunction Prefered
			UCCStatus.Usb30_Flag =0;
		}
		else if((UCCMSG.vdm_message)&&(SendMegSndDataOffset== 3))
		{
			(UCCMSG.CcVersion >= 2)?(SendData |= 0x20):(SendData &= 0xdf);
		}
        BKD0_9A_REG	= SendData;
    }
	UCCMSG.RcvGoodCRC = 0;
	UCCStatus.Msg_ID_Change = 1;
	UCCStatus.Msg_Resend_Num++;
    BKD0_A3_REG = 0x01; //clr rx fifo
    BKD0_98_REG |= 0x08;	  //mark all data done
    KNL_Delay1us(1);
    BKD0_98_REG &=0xf7;
	BKD0_99_REG = 0x29;
	TR2_Set();
	if(UCCStatus.source_stop)
	{
		TR2 = 1;
	}		
}

void UFP_Vdm_Msg(void)
{
    if(UCCMSG.MsgType == Vendor_Defined)
    {
        if(UCCMSG.RcvDate[1] & 0x80)//Structured VDM
        {
            if((UCCMSG.RcvDate[2] <= DP_ALT_MODE_HBYTE)&&(UCCMSG.RcvDate[3] == DP_ALT_MODE_HBYTE))//UCCMSG.RcvDate[4][5]
            {
                switch(UCCMSG.RcvDate[0]&0x1F)  //Command
                {
					case Discover_Identity   :
							UCCStatus.VDM_Step |= 0x01;
							UCCMSG.DataOrder =  CC_Discover_Id;
							Send_MessageUcc();
							break;
					case Discover_SVIDs      :
							UCCMSG.DataOrder = CC_Data_Msg[2];
							UCCStatus.VDM_Step |= 0x02;
							Send_MessageUcc();
							break;
					case Discover_Modes      :	
							UCCStatus.VDM_Step |= 0x04;
							if(UCCStatus.VDM_Step &0x02)
							{							
								UCCMSG.DataOrder = (UCCStatus.Lane_Count == 4)?(CC_Data_Msg[3]):(CC_Data_Msg[4]);	//4LANE
								Send_MessageUcc();	
							}
							else
							{
								if(UCCStatus.Lane_Count ==4)
								{
									memcpy(UCC_Mode_Msg,CC_Data_Msg[3],10);
									UCC_Mode_Msg[2] = 0x83; //NACK
									//UCC_Mode_Msg[3] &= 0xf8;//Object position
									//UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position
									UCC_Mode_Msg[4] = UCCMSG.RcvDate[2];//SID&VID
									UCC_Mode_Msg[5] = UCCMSG.RcvDate[3];//SID&VID
									UCCMSG.DataOrder = UCC_Mode_Msg;
									Send_MessageUcc();	
								}
								else
								{
									memcpy(UCC_Mode_Msg,CC_Data_Msg[4],10);
									UCC_Mode_Msg[2] = 0x83; //NACK
									//UCC_Mode_Msg[3] &= 0xf8;//Object position
									//UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position
									UCC_Mode_Msg[4] = UCCMSG.RcvDate[2];//SID&VID
									UCC_Mode_Msg[5] = UCCMSG.RcvDate[3];//SID&VID
									UCCMSG.DataOrder = UCC_Mode_Msg;
									Send_MessageUcc();	
								}						
							}													
							break;
					case Enter_Mode          :
							UCCStatus.VDM_Step |= 0x08;
							if(UCCStatus.VDM_Step &0x02)
							{							
								if(((UCCStatus.DataRole)&&(UCCStatus.Swap_Sent&DR_Sent_Accept))||(UCCStatus.DataRole==0))
								{
									memcpy(UCC_Mode_Msg,CC_Data_Msg[5],6);
									if((UCCMSG.RcvDate[1]&0x07)==0x01)
									{
										UCC_Mode_Msg[2] = 0x44; //ACK
										
									}
									else
									{
										UCC_Mode_Msg[2] = 0x84; //NACK
									}
									UCC_Mode_Msg[3] &= 0xf8;//Object position
									UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position
									UCC_Mode_Msg[4] = UCCMSG.RcvDate[2];//SID&VID
									UCC_Mode_Msg[5] = UCCMSG.RcvDate[3];//SID&VID
									UCCMSG.DataOrder = UCC_Mode_Msg;
									Send_MessageUcc();	
								}
							}
							else
							{
								memcpy(UCC_Mode_Msg,CC_Data_Msg[5],6);
								UCC_Mode_Msg[2] = 0x84; //NACK
								UCC_Mode_Msg[3] &= 0xf8;//Object position
								UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position
								UCC_Mode_Msg[4] = UCCMSG.RcvDate[2];//SID&VID
								UCC_Mode_Msg[5] = UCCMSG.RcvDate[3];//SID&VID
								UCCMSG.DataOrder = UCC_Mode_Msg;
								Send_MessageUcc();	
							}
							break;
					case Exit_Mode           :
							if(UCCStatus.VDM_Step &0x08)
							{
								memcpy(UCC_Mode_Msg,CC_Data_Msg[6],6);
								if((UCCMSG.RcvDate[1]&0x07)==0x01)
								{
									UCC_Mode_Msg[2] = 0x45; //ACK
								}
								else
								{		
									UCC_Mode_Msg[2] = 0x85; //NACK
								}							
								UCC_Mode_Msg[3] &= 0xf8;//Object position
								UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position
								UCC_Mode_Msg[4] = UCCMSG.RcvDate[2];//SID&VID
								UCC_Mode_Msg[5] = UCCMSG.RcvDate[3];//SID&VID
								UCCMSG.DataOrder = UCC_Mode_Msg;
								Send_MessageUcc();	
							}
							else
							{
								memcpy(UCC_Mode_Msg,CC_Data_Msg[6],6);
								UCC_Mode_Msg[2] = 0x85; //NACK		
								UCC_Mode_Msg[3] &= 0xf8;//Object position
								UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position								
								UCC_Mode_Msg[4] = UCCMSG.RcvDate[2];//SID&VID
								UCC_Mode_Msg[5] = UCCMSG.RcvDate[3];//SID&VID
								UCCMSG.DataOrder = UCC_Mode_Msg;
								Send_MessageUcc();	
							}	
							UCCStatus.VDM_Step &= 0xf7;
							break;
					case Attention           :
							break;
					case DP_Status_Updata:
							UCCStatus.VDM_Step |= 0x10;
							UCCStatus.Usb30_Flag = (UCCStatus.Lane_Count == 4)?(0):(1);
							UCCMSG.DataOrder = (!UCCStatus.Attention_flag)?(CC_Data_Msg[7]):(CC_Data_Msg[8]);
							Send_MessageUcc();	 //
							break;
					case DP_Config	         :
							UCCStatus.VDM_Step |= 0x20;
							UCCMSG.DataOrder = CC_Data_Msg[9];
							Send_MessageUcc();
//							UCCMSG.Dp_config = 1;
							UCCStatus.Toggle_enable = 0;
							#if TYPEC_PRSWAP_EN == ENABLED
							if(((BKE2_17_REG&0x04) == 0x04)&&((BKD0_30_REG&0xf0)||(BKE5_D4_REG&0x10))&&(!UCCStatus.PRSended)&&(!UCCStatus.PowerRole)) //DCC 已经在
							{
								UCCStatus.PRSended = 1;
								UCCStatus.ReadySendPR = 1; //先插电源
							}
							else
							#endif
							{
								if(UCCStatus.IsCc_done == FALSE)
								{
									UCCStatus.IsCc_done = TRUE;
								}
							}

							break;
					default               :
							break;
				}		
			}
			else if((UCCMSG.RcvDate[2] == 0x61)&&(UCCMSG.RcvDate[3]== 0x2f))// for lontium
			{
				switch(UCCMSG.RcvDate[0]&0x1F) //Command
				{
					case Discover_Modes  :
							UCCStatus.VDM_Step |= 0x04;
							if(UCCStatus.VDM_Step &0x02)
							{							
								UCCMSG.DataOrder = CC_Data_Msg[14];	//4LANE
								Send_MessageUcc();	
							}
							else
							{							
								memcpy(UCC_Mode_Msg,CC_Data_Msg[14],10);
								UCC_Mode_Msg[2] = 0x83; //ACK
								//UCC_Mode_Msg[3] &= 0xf8;//Object position
								//UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position
								UCC_Mode_Msg[4] = UCCMSG.RcvDate[2];//SID&VID
								UCC_Mode_Msg[5] = UCCMSG.RcvDate[3];//SID&VID
								UCCMSG.DataOrder = UCC_Mode_Msg;
								Send_MessageUcc();								
							}
							break;
					case Enter_Mode  :
							UCCStatus.VDM_Step |= 0x08;
							if(UCCStatus.VDM_Step &0x02)
							{							
								if(((UCCStatus.DataRole)&&(UCCStatus.Swap_Sent&DR_Sent_Accept))||(UCCStatus.DataRole==0))
								{								
									memcpy(UCC_Mode_Msg,CC_Data_Msg[5],6);
									if(((UCCMSG.RcvDate[1]&0x07)==0)||((UCCMSG.RcvDate[1]&0x07)==0x07))
									{
										UCC_Mode_Msg[3] &= 0xf8;//Object position
										UCC_Mode_Msg[3] |= 0x07;//Object position
										UCC_Mode_Msg[2] = 0x84; //NACK
									}
									else
									{
										UCC_Mode_Msg[3] &= 0xf8;//Object position
										UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position
										UCC_Mode_Msg[2] = 0x44; //ACK
									}
//									UCC_Mode_Msg[2] = 0x44; //ACK
//									UCC_Mode_Msg[3] &= 0xf8;//Object position
//									UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position
									UCC_Mode_Msg[4] = UCCMSG.RcvDate[2];//SID&VID
									UCC_Mode_Msg[5] = UCCMSG.RcvDate[3];//SID&VID
									UCCMSG.DataOrder = UCC_Mode_Msg;
									Send_MessageUcc();									
								}
							}
							else
							{
								memcpy(UCC_Mode_Msg,CC_Data_Msg[5],6);
								if(((UCCMSG.RcvDate[1]&0x07)==0)||((UCCMSG.RcvDate[1]&0x07)==0x07))
								{
									UCC_Mode_Msg[3] &= 0xf8;//Object position
									UCC_Mode_Msg[3] |= 0x07;//Object position
								}
								else
								{
									UCC_Mode_Msg[3] &= 0xf8;//Object position
									UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position
								}
								UCC_Mode_Msg[2] = 0x84; //NACK
//								UCC_Mode_Msg[3] &= 0xf8;//Object position
//								UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position
								UCC_Mode_Msg[4] = UCCMSG.RcvDate[2];//SID&VID
								UCC_Mode_Msg[5] = UCCMSG.RcvDate[3];//SID&VID
								UCCMSG.DataOrder = UCC_Mode_Msg;
								Send_MessageUcc();	
							}
					
							break;
					case Exit_Mode           :
							
							if(UCCStatus.VDM_Step &0x08)
							{
								memcpy(UCC_Mode_Msg,CC_Data_Msg[6],6);
								if(((UCCMSG.RcvDate[1]&0x07)==0)||((UCCMSG.RcvDate[1]&0x07)==0x07))
								{
									UCC_Mode_Msg[3] &= 0xf8;//Object position
									UCC_Mode_Msg[3] |= 0x07;//Object position
									UCC_Mode_Msg[2] = 0x85; //NACK
								}
								else
								{
									UCC_Mode_Msg[3] &= 0xf8;//Object position
									UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position
									UCC_Mode_Msg[2] = 0x45; //ACK
								}
								
//								UCC_Mode_Msg[3] &= 0xf8;//Object position
//								UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position
								UCC_Mode_Msg[4] = UCCMSG.RcvDate[2];//SID&VID
								UCC_Mode_Msg[5] = UCCMSG.RcvDate[3];//SID&VID
								UCCMSG.DataOrder = UCC_Mode_Msg;
								Send_MessageUcc();	
							}
							else
							{
								memcpy(UCC_Mode_Msg,CC_Data_Msg[6],6);
								if(((UCCMSG.RcvDate[1]&0x07)==0)||((UCCMSG.RcvDate[1]&0x07)==0x07))
								{
									UCC_Mode_Msg[3] &= 0xf8;//Object position
									UCC_Mode_Msg[3] |= 0x07;//Object position
								}
								else
								{
									UCC_Mode_Msg[3] &= 0xf8;//Object position
									UCC_Mode_Msg[3] |= (UCCMSG.RcvDate[1]&0x07);//Object position
								}
								UCC_Mode_Msg[2] = 0x85; //NACK								
								UCC_Mode_Msg[4] = UCCMSG.RcvDate[2];//SID&VID
								UCC_Mode_Msg[5] = UCCMSG.RcvDate[3];//SID&VID
								UCCMSG.DataOrder = UCC_Mode_Msg;
								Send_MessageUcc();	
							}	
							UCCStatus.VDM_Step &= 0xf7;
							break;
					default     :
							break;
				}
			}
			else if((UCCMSG.RcvDate[2]==Samsung_LByte)&&(UCCMSG.RcvDate[3]==Samsung_HByte))// for Samsung Dex
			{
				switch  (UCCMSG.RcvDate[0]&0x1F)  //Command
				{
					;
				}
			}
			else if((UCCMSG.RcvDate[2]==Switch_LByte)&&(UCCMSG.RcvDate[3]==Switch_HByte))	//Switch
			{
				switch(UCCMSG.RcvDate[0]&0x1F)
				{
					;
				}
			}
		 }
		 else //unstructure
		 {
			if(UCCMSG.CcVersion>=2)
			{
				UCCMSG.DataOrder = CC_Ctrl_Msg[6];
				Send_MessageUcc();	
			}
		 }
	}
}
void Chunk_Message_Handle(void)
{
	static u16 Data_Size = 0;
	static u8 Chunk_Num = 0;
	static u16 Num_Data_Obj = 0;
	static u16 Num_Data = 0;
	if(UCCMSG.Header[3]&0x80)
	{
		if((UCCMSG.Header[3]&0x04)==0x00)//request chunk =0;
		{
			if((UCCMSG.Header[3]&0x78)==0)//if chunk number equal 0
			{
				Num_Data_Obj = 0;
			}
			Data_Size = UCCMSG.Header[3]&0x01;
			Data_Size <<= 8;
			Data_Size |= UCCMSG.Header[2];//The total data
			Num_Data = ((UCCMSG.Header[1]&0x70)>>2)-2;//remove Externed Header;
			Num_Data_Obj += Num_Data;
			Chunk_Num = (UCCMSG.Header[3]&0x78)+8;//should less than 10

			if((Data_Size<=Num_Data_Obj)||(Chunk_Num>72))
			{
				Num_Data_Obj = 0;
				UCCMSG.DataOrder = CC_Ctrl_Msg[6];
				Send_MessageUcc();	
			}
			else
			{
				Chunked_Message[0]=UCCMSG.Header[0];
				Chunked_Message[1]=0x90;
				Chunked_Message[2]=0x00;
				Chunked_Message[3]=0x84|Chunk_Num;
				Chunked_Message[4]=0x00;
				Chunked_Message[5]=0x00;
				UCCMSG.DataOrder = Chunked_Message;
				Send_MessageUcc();	
			}			
		}
		else
		{
			;
		}		
	}
}
void UFP_Message(void)  //UFP message
{
    if(!UCCMSG.ExtMsg)
	{
		if(UCCMSG.Datalenth==0x00)   //NO data, header Only￡?
		{
			switch(UCCMSG.MsgType)
			{
				case GoodCRC  :
						break;
				case GotoMin        : 
						break;
				case Accept  :
						if(UCCStatus.step == 2)//receive source cap
						{
							UCCStatus.step = 3;
						}
						#if TYPEC_DRSWAP_EN == ENABLED			
						if(UCCMSG.LastMsg == DR_Swap)
						{
							UCCStatus.Swap_Sent &= DR_No_Sent;
							UCCStatus.Swap_Sent |= DR_Sent_Accept;
							UCCStatus.DataRole = 0;
						}
						else if(UCCMSG.LastMsg == VCONN_Swap)
						{
							if((UCCStatus.Swap_Sent&DR_Sent) == 0)
							{
								UCCStatus.dr_swap_en = 1;
//								Typec_Timer(30);							
							}
						}
						else if(UCCMSG.LastMsg == PR_Swap)
						{
//							Typec_Timer(60);
						}
						#endif
						break;
				case Reject         :
						if(UCCMSG.LastMsg == PR_Swap)
						{
//							Adapter_GPIO20_Ctrl(0);
							UCCStatus.PrDone = 1;
							UCCStatus.PRSwaping = 0;
							if(UCCStatus.IsCc_done == FALSE)
							{
								UCCStatus.IsCc_done = TRUE;
							}
						}
						else if(UCCMSG.LastMsg == VCONN_Swap)
						{
							if((UCCStatus.Swap_Sent&DR_Sent) == 0)
							{
								UCCStatus.dr_swap_en = 1;
//								Typec_Timer(30);
							}
						}
						else if(UCCMSG.LastMsg == DR_Swap)
						{						
							UCCStatus.Swap_Sent |= DR_Sent_Reject;
							UCCMSG.LastMsg = 0xff;																		
						}
						break;
				case Ping          	:	
						break; 
				case PS_RDY   :
						UCCStatus.step = 1;
						#if TYPEC_PRSWAP_EN == ENABLED
						if((UCCStatus.PRSwaping)&&((UCCStatus.PRSwaped)==1)) //SEND PS_RDY RECIEVE PS_RDY
						{
							if(UCCMSG.CcVersion >= 0x02)
							{
								BKE2_17_REG |= BIT0_1;
							}
							else
							{
								BKE2_17_REG &= BIT0_0;
							}
							BKD0_3E_REG = 0x01;//DFP
							UCCStatus.PowerRole = 1;
							if(UCCStatus.CcInput_type == FEMALE)
							{
								CC_Logic_Rst(UCC);
							}
							UCCStatus.ps_rdy_send  = 1;
							TR2_Set();
							TR2 = 1;   //enable Time0
						}
						#endif
						#if TYPEC_DRSWAP_EN == ENABLED
						if(UCCMSG.LastMsg == VCONN_Swap)
						{
							if((UCCStatus.Swap_Sent&DR_Sent) == 0)
							{
								UCCStatus.dr_swap_en = 1;
//								Typec_Timer(30);
							}
						}
						if((((BKE2_17_REG&0x04) == 0x04)&&(/*(BKD0_30_REG&0xf0)||*/(BKE5_D4_REG&0x10))&&(!UCCStatus.PRSended)&&(!UCCStatus.PowerRole))
							&&(UCCStatus.FRSwaping==0)) //DCC 				
						{
							UCCStatus.PRSended = 1;
							UCCStatus.ReadySendPR = 1; //adapter On
						}
						#endif
						break;
				case Get_Source_Cap ://20210728
						if(/*(BKD0_30_REG&0xf0)||*/(BKE5_D4_REG&0x10))
						{
							if(DCCStatus.sourcecap_flag)	
							{
								#if PD_PPS_EN == 1
								if(UCCMSG.CcVersion < 2)//PD2.0
								{
									UCCMSG.DataOrder = DCCMSG.AdapterTmp;
								}
								else//PD3.0
								{
									UCCMSG.DataOrder = AdapterTmp_PD30;
								}
								#else
								UCCMSG.DataOrder = DCCMSG.AdapterTmp;
								#endif
							}	
							else
							{
								UCCMSG.DataOrder = CC_Data_Msg[0];
							}	
						}
						else
						{
							UCCMSG.DataOrder = CC_Ctrl_Msg[3];
						}
						Send_MessageUcc();
				
						break;
				case Get_Sink_Cap   :
						if(UCCStatus.step == 2)	
						{
							UCCMSG.MsgNum = 0x00;
							UCCMSG.DataOrder = CC_Ctrl_Msg[7];
							Send_MessageUcc();
						}		
						else if(UCCStatus.step ==3)
						{
							BKD0_99_REG = 0x14;
							BKD0_99_REG = 0x20;
						}
						else
						{
							if(UCCMSG.CcVersion >= 2)
							{
								if(BKE5_D4_REG&0x10)
								{
									UCCMSG.DataOrder = CC_Data_Msg[16];
								}
								else
								{
									UCCMSG.DataOrder = CC_Data_Msg[19];
								}							
							}
							else
							{
								if(BKE5_D4_REG&0x10)
								{
									UCCMSG.DataOrder = CC_Data_Msg[13];
								}
								else
								{
									UCCMSG.DataOrder = CC_Data_Msg[18];
								}
							}
							Send_MessageUcc();
						}					
						break;
				case DR_Swap        :
						#if TYPEC_DRSWAP_EN == ENABLED
//						TR2 = 0;
						if(UCCStatus.VDM_Step&0xf8)
						{
							BKD0_99_REG = 0x14;
							BKD0_99_REG = 0x20;
						}
						else
						{
							UCCStatus.Wait_Receive = 0;
							UCCStatus.dr_swap_en = 2;
							if(UCCStatus.DataRole == 0)
							{
								UCCMSG.DataOrder = CC_Ctrl_Msg[3];
								Send_MessageUcc();
							}
							else
							{
								UCCMSG.DataOrder = CC_Ctrl_Msg[2];
								Send_MessageUcc();
								UCCMSG.LastMsg = DR_Swap;
							}					
							//UCCStatus.DataRole = 0;
							UCCStatus.Swap_Sent &= DR_No_Sent;
							UCCStatus.Swap_Sent |= DR_Sent_Accept;
						}
						#endif
						break;
				case PR_Swap :	
						if((UCCStatus.PRSwaped==1)||((BKE5_D4_REG&0x10)==0))
						{
							UCCMSG.DataOrder = CC_Ctrl_Msg[3];
							Send_MessageUcc();
						}
						else
						{
							UCCStatus.PRSwaped = 2;
							UCCMSG.DataOrder = CC_Ctrl_Msg[2];
							Send_MessageUcc();
						}
						
						break;
				case VCONN_Swap		://20210804
						#if TYPEC_DRSWAP_EN == ENABLED
//						TR2 = 0;
						UCCStatus.Wait_Receive = 0;
						UCCStatus.Swap_Sent |= Vconn_Sent;
						UCCStatus.vconn_swap_en = 0;
						if((BKE5_D4_REG&0x10)&&((UCCStatus.Swap_Sent&Vconn_Sent) == 0x00))
						{
							UCCMSG.DataOrder = CC_Ctrl_Msg[2];
						}
						else
						{
							if((UCCMSG.CcVersion)>=2)//not support
							{
								UCCMSG.DataOrder = CC_Ctrl_Msg[6];
							}
							else//reject
							{
								UCCMSG.DataOrder = CC_Ctrl_Msg[3];
							}						
						}					
						Send_MessageUcc();
						UCCMSG.LastMsg  = (~VCONN_Swap);
						if((UCCStatus.Swap_Sent&DR_Sent) == 0)
						{
							UCCStatus.dr_swap_en = 1;
//							Typec_Timer(30);
						}
						#endif
						break;
				case Wait           :	
						UCCStatus.Wait_Receive = 1;
						UCCMSG.Last_DataOrder = UCCMSG.Buffer_Order;
//						Typec_Timer(30);
						break;
				case Soft_Reset 	:
						UCCMSG.MsgNum = 0;
						UCCMSG.DataOrder = CC_Ctrl_Msg[2];//send ACCEPT
						Send_MessageUcc();
						break;
				case Not_Support    :
						if(UCCMSG.LastMsg == PR_Swap)
						{
//							Adapter_GPIO20_Ctrl(0);
							UCCStatus.PrDone = 1;
							UCCStatus.PRSwaping = 0;
							if(UCCStatus.IsCc_done == FALSE)
							{
								UCCStatus.IsCc_done = TRUE;
							}
						}
						else if(UCCMSG.LastMsg == VCONN_Swap)
						{
							if((UCCStatus.Swap_Sent&DR_Sent) == 0)
							{
								UCCStatus.dr_swap_en = 1;
							}
						}
						else if(UCCMSG.LastMsg == DR_Swap)
						{						
							UCCStatus.Swap_Sent |= DR_Sent_Reject;
							UCCMSG.LastMsg = 0xff;																		
						}
				        break;
				case Get_Source_Cap_Extended     : //20210728
						//if(UCCStatus.PowerRole)
						if((BKD0_30_REG&0xf0)||(BKE5_D4_REG&0x10))
						{					
							CC_Source_Cap_Ext[27] = PDP_Value[0];
							UCCMSG.DataOrder = CC_Source_Cap_Ext;
						}
						else
						{							
							UCCMSG.DataOrder = CC_Ctrl_Msg[6];			
						}	
						Send_MessageUcc();	
						break;
				case FR_Swap :
						#if TYPEC_FRSWAP_EN  == ENABLED
//						DCCStatus.charger_scan = 1;
						if(UCCStatus.PowerRole)
						{
							UCCMSG.DataOrder = CC_Ctrl_Msg[2];
							Send_MessageUcc();
							UCCStatus.PowerRole = 0;
							UCCMSG.LastMsg  = FR_Swap;
						}
						else
						{
							UCCMSG.DataOrder = CC_Ctrl_Msg[3];
							Send_MessageUcc();
						}
						#endif
						break;								
				case Get_Status     : 			
				case Get_PPS_Status     :
				case Get_Country_Codes  :
						UCCMSG.DataOrder = CC_Ctrl_Msg[6];
						Send_MessageUcc();	
						break;			
				default :
						if(UCCMSG.CcVersion>=2)
						{
							UCCMSG.DataOrder = CC_Ctrl_Msg[6];
						}
						else
						{
							UCCMSG.DataOrder = CC_Ctrl_Msg[3];
						}						
						Send_MessageUcc();	
						break;
			}
		}
		else
		{
			switch (UCCMSG.MsgType)
			{
					case Source_Capabilities   :
//							UCCStatus.CC_Connect_Cnt = 0;
							UCCStatus.step = 2;
							UCCStatus.source_stop = 1;
							if(UCCMSG.CcVersion == 1)
							{
								;
							}
							else
							{
								UCCMSG.CcVersion = (UCCMSG.Header[0]&0xc0)>>6;
							}
							
							UCCStatus.PowerRole = 0;
							Request_Ucc_Fix();
							UCCMSG.DataOrder = UCCMSG.RequestBuf; //UFP_SINK 1
							Send_MessageUcc();
							break;
					case Request :
							#if TYPEC_FRSWAP_EN  == ENABLED
							BKE5_1C_REG |= BIT4;  //ucc2_vbus_off_det important	
							BKE5_3C_REG = 0x10;	// clear interrupt 2
							
							UCCStatus.step = 4;
							if(UCCMSG.CcVersion == 1)
							{
								;
							}
							else
							{
								UCCMSG.CcVersion = (UCCMSG.Header[0]&0xc0)>>6;
							}
							if(UCCMSG.CcVersion >= 0x02)
							{
								BKE2_17_REG |= BIT0_1;
							}
							else
							{
								BKE2_17_REG &= BIT0_0;
							}
							UCCStatus.PowerRole = 1; 
							Request_Ucc_Cal(); //request DCC For the Power cal
							#endif
							#if PD_PPS_EN == 1
							if(UCCStatus.PPS_Request&&(UCCMSG.CcVersion<2))//PD2.0 request PPS,reject
							{
								UCCMSG.DataOrder = CC_Ctrl_Msg[3];
								Send_MessageUcc();//DFP_SOURCE 2//UFP_SINK 5
								UCCMSG.LastMsg = 0xff; //Accept time must less than 15ms
							}
							else
							#endif
							{
								UCCMSG.DataOrder = CC_Ctrl_Msg[2];
								Send_MessageUcc();//DFP_SOURCE 2//UFP_SINK 5
								UCCMSG.LastMsg = Accept; //Accept time must less than 15ms
							}							
							break;
					case BIST					:
							if(UCCMSG.RcvDate[3]== 0x50)
							{
								BKD0_97_REG |= 0x80;
								BKD0_9A_REG =  0x43;	 
								BKD0_99_REG =  0x09;
								KNL_Delay1ms(40);
								BKD0_97_REG &= 0x7F;	
							}
							break;
					case Sink_Capabilities  	:					  								
							break; 
					case Battery_Status     	:					  								
							break; 
					case Alert     				:											  													
					case Get_Country_Info   	:	
							UCCMSG.DataOrder = CC_Ctrl_Msg[6];
							Send_MessageUcc();				  								
							break; 
					case Vendor_Defined :
							
							UCCMSG.vdm_message = 1;
							UFP_Vdm_Msg();   //xxxmsg = Vendor Defined Msg
							break;
					default :
							break;
			}
		}
	}
	else
	{
		switch (UCCMSG.MsgType)
		{
			case Source_Cap_Extended   :  											
			//break;
			case Status            :								
			//break;
			case Get_Battery_Cap    : 
			//break; 
			case Get_Battery_Status :					  								
			//break; 
			case Battery_Capabilities:					  								
			//break; 
			case Get_Manufacturer_Info :											  	
			//break; 
			case Manufacturer_Info  :			  								
			//break; 
			case Security_Request   : 																	                            
			//break;
			case Security_Response  :			  								
			//break;
			case Firmware_Update_Request  :			  								
			//break;
			case Firmware_Update_Response  :			  								
			//break;
			case PPS_Status  		:			  								
			//break;
			case Country_Info  		:			  								
			//break;
			case Country_Codes  	:
				UCCMSG.DataOrder = CC_Ctrl_Msg[6];
				Send_MessageUcc();	  								
				break;
			default                 : 
				Chunk_Message_Handle();
				break;
		}	
	}
}
////===================================
//DFP message handle
void Request_Dcc_Fix(void)
{
    DCCMSG.RequestBuf[0]= 0x42;
    DCCMSG.RequestBuf[1]= 0x10;
    DCCMSG.RequestBuf[2]= DCCMSG.RcvDate[0];
    DCCMSG.RequestBuf[3]= (DCCMSG.RcvDate[1]&0x03)|((DCCMSG.RcvDate[0]&0x3f)<<2);
    DCCMSG.RequestBuf[4]= (((DCCMSG.RcvDate[0]&0xc0)>>6)|((DCCMSG.RcvDate[1]&0x03)<<2));
	DCCMSG.RequestBuf[4] &= 0x7f;//Unchunked Extended Messages Not Supported
    DCCMSG.RequestBuf[5]= 0x13;
}
//******always request max current Adapter supports******//
void Request_Ucc_Cal(void)	//FOR REQUEST ADAPTER
{
	u8 object;
    u16 Request_Cur = 0x00;
	object = (UCCMSG.RcvDate[3]&0x70)>>4;//get Object position
	#if PD_PPS_EN == 1
	if(object==Loc_of_PPS[0]||(object==Loc_of_PPS[1])||(object==Loc_of_PPS[2])||
		(object==Loc_of_PPS[3])||(object==Loc_of_PPS[4])||(object==Loc_of_PPS[5]))
	{
		UCCStatus.PPS_Request = 1;
		UCCMSG.RequestTmp[0] = UCCMSG.Header[0];
		UCCMSG.RequestTmp[1] = UCCMSG.Header[1];
		UCCMSG.RequestTmp[2] = UCCMSG.RcvDate[0];
		UCCMSG.RequestTmp[3] = UCCMSG.RcvDate[1];
		UCCMSG.RequestTmp[4] = UCCMSG.RcvDate[2];
		UCCMSG.RequestTmp[5] = UCCMSG.RcvDate[3];
	}
	else
	#endif
	{
		#if PD_PPS_EN == 1
		UCCStatus.PPS_Request = 0;
		#endif
		memcpy(&UCCMSG.RequestTmp[2],&AdapterTmp_Ori[object*4-2],4);
		Request_Cur = (UCCMSG.RequestTmp[3]&0x03);
		Request_Cur <<= 8;
		Request_Cur |= UCCMSG.RequestTmp[2];
		
		UCCMSG.RequestTmp[0] = 0x42;
		UCCMSG.RequestTmp[1] = 0x12;
		UCCMSG.RequestTmp[5] = UCCMSG.RcvDate[3];//needed
		
		UCCMSG.RequestTmp[3] &= 0x03;
		UCCMSG.RequestTmp[3] |= (Request_Cur<<2);
		Request_Cur >>= 6;
		UCCMSG.RequestTmp[4] = 0x00;//needed for Bit7(PD3.0)
		UCCMSG.RequestTmp[4] |= (Request_Cur & 0x0f);
	}
}

void Adapter_Source_Cal(void) 	//SOURCE CAP FOR THE SOURCE
{
    u8 Adtmp;
	u8 AdapterTmpLenth= 0;
    u8 loop_Adatper;
    u16 Adapter_Cur_Cap = 0x00;
    u16 Adapter_Vol_Cap = 0x00;
	u32 Adapter_Wat_Cap = 0x00;
	#if PD_PPS_EN == 1
	u8 Loop_PPS_Cnt;
	u8 PPS_Max_Vol = 0;
	u8 PPS_Max_Cur = 0;
	u16 PPS_Wat_Cap = 0;
	Loop_PPS_Cnt = 0;
	memset(Loc_of_PPS,0x00,6);
	#endif
	PDP_Value[0] = 0x07;
	PDP_Value[1] = 0x07;
	AdapterTmpLenth	= DCCMSG.Datalenth + 2;
    for(Adtmp = 0; Adtmp < AdapterTmpLenth; Adtmp++)
    {
		if(Adtmp == 0)
		{
			DCCMSG.AdapterTmp[0] = DCCMSG.Header[0];
		}
		else if(Adtmp == 1)
		{
			DCCMSG.AdapterTmp[1] = DCCMSG.Header[1];
		}
		else
		{
			DCCMSG.AdapterTmp[Adtmp]= DCCMSG.RcvDate[Adtmp-2];
		}
    }
    DCCMSG.AdapterTmp[0] &= 0x0F;
    DCCMSG.AdapterTmp[0] |= 0x40;
	memcpy(AdapterTmp_Ori,DCCMSG.AdapterTmp,30);
	#if PD_PPS_EN == 1
	memcpy(AdapterTmp_PD30,DCCMSG.AdapterTmp,30);
	#endif
	for(Adtmp = 2; Adtmp < AdapterTmpLenth ; Adtmp += 4)
	{
		if((DCCMSG.AdapterTmp[Adtmp+3]&0xc0) == 0xc0) //PPS Package
		{		
			for(loop_Adatper = Adtmp; (loop_Adatper+4) < AdapterTmpLenth; loop_Adatper++)
			{
				DCCMSG.AdapterTmp[loop_Adatper] = DCCMSG.AdapterTmp[loop_Adatper+4];
			}
			DCCMSG.AdapterTmp[1] -= 0x10;
			#if PD_PPS_EN == 1
			if(AdapterTmp_PD30[Adtmp]>8)//reduce 400mA
			{
				AdapterTmp_PD30[Adtmp] -= 8;
			}
			else
			{
				;
			}
			//[0-6]:Cur;[8-15]:min Vol;[17-24]:max vol;
			PPS_Max_Cur = AdapterTmp_PD30[Adtmp]; 
			PPS_Max_Vol = AdapterTmp_PD30[Adtmp+3];
			PPS_Max_Vol <<= 7;
			PPS_Max_Vol = PPS_Max_Vol|(AdapterTmp_PD30[Adtmp+2]>>1);
			PPS_Wat_Cap = (u16)PPS_Max_Vol*PPS_Max_Cur;
			PPS_Wat_Cap = PPS_Wat_Cap/200;
			if(PDP_Value[1]>PPS_Wat_Cap)
			{
				;
			}
			else
			{
				PDP_Value[1] = PPS_Wat_Cap;
			}
			Loc_of_PPS[Loop_PPS_Cnt] = (Adtmp>>2)+1;
			Loop_PPS_Cnt++;
			#else
			AdapterTmpLenth -=4;
			(Adtmp == 2)?(Adtmp = 0xfe):(Adtmp -= 4);
			#endif
		}
		else   //FIXED SUPPLY
		{
			Adapter_Cur_Cap	= DCCMSG.AdapterTmp[Adtmp+1]&0x03;
			Adapter_Cur_Cap <<= 8;
			Adapter_Cur_Cap |= DCCMSG.AdapterTmp[Adtmp];

			Adapter_Vol_Cap = DCCMSG.AdapterTmp[Adtmp+2]&0x0f;
			Adapter_Vol_Cap <<= 6;
			Adapter_Vol_Cap |= ((DCCMSG.AdapterTmp[Adtmp+1]&0xfc)>>2);
			
			Adapter_Wat_Cap = (u32)Adapter_Vol_Cap*Adapter_Cur_Cap;
			Adapter_Wat_Cap -= 16000;//8W in 0.5mW each divide
			Adapter_Cur_Cap = (Adapter_Wat_Cap/Adapter_Vol_Cap);
			
			DCCMSG.AdapterTmp[Adtmp] = Adapter_Cur_Cap;
			DCCMSG.AdapterTmp[Adtmp+1] &= 0xfc;
			DCCMSG.AdapterTmp[Adtmp+1] |= ((Adapter_Cur_Cap>>8)&0x03);
			DCCMSG.AdapterTmp[5] = ((DCCMSG.AdapterTmp[5]&0x08)|0x3e);//Externally Powered	
			DCCMSG.AdapterTmp[5] &= 0xfe;//Unchunked Extended Messages Not Supported
			#if PD_PPS_EN == 1
			AdapterTmp_PD30[Adtmp] = DCCMSG.AdapterTmp[Adtmp];
			AdapterTmp_PD30[Adtmp+1] = DCCMSG.AdapterTmp[Adtmp+1];
			AdapterTmp_PD30[5] = DCCMSG.AdapterTmp[5];//Externally Powered	
			AdapterTmp_PD30[5] &= 0xfe;//Unchunked Extended Messages Not Supported
			#endif
			Adapter_Wat_Cap = (Adapter_Wat_Cap/2000);
			if(PDP_Value[0]>Adapter_Wat_Cap)
			{
				;
			}
			else
			{
				PDP_Value[0] = Adapter_Wat_Cap;
			}
		}
	}
	#if PD_PPS_EN == 1
	if(PDP_Value[0] >= PDP_Value[1])
	{
		;
	}
	else
	{
		PDP_Value[0] = PDP_Value[1];
	}
	#endif
}
void Send_MessageDcc(void)
{
    u8 SendData,SendMegSndDataOffset;
	static u8 Message_ID_Send = 0x00;
	DCCMSG.Buffer_Order = DCCMSG.DataOrder;
    DCCMSG.TotalData = 2;
    for(SendMegSndDataOffset=0; SendMegSndDataOffset<DCCMSG.TotalData; SendMegSndDataOffset++)
    {
        SendData = *DCCMSG.DataOrder;
        DCCMSG.DataOrder++;
        if(SendMegSndDataOffset==1)
        {			
            DCCMSG.TotalData = ((SendData & 0x70)>>2)+2;
            SendData &=0xF0;
			if(DCCStatus.Msg_ID_Change == 1)
			{
				Message_ID_Send = DCCMSG.MsgNum;
				DCCMSG.MsgNum = Sum(DCCMSG.MsgNum);	
			}
			else
			{
				;
			}
			SendData=(SendData|DCCMSG.MsgNum);
            (DCCStatus.PowerRole)?(SendData |= 0x01):(SendData &= 0xfe);
        }
		
        else if(SendMegSndDataOffset == 0)
        {
            SendData &= 0x1F;//ufp pd2.0
			#if PD_PPS_EN == 1
			if(DCCMSG.CcVersion < 0x02)
            {
				SendData |=  0x40;
            }
            else
            {
				SendData |=  0x80;
            }
			#else
            SendData |= 0x40;
			#endif
            (DCCStatus.DataRole)?(SendData|=0x20):(SendData &= 0xdf);
        }
        BKD0_1A_REG	= SendData;
    }
	DCCMSG.RcvGoodCRC = 0;
	DCCStatus.Msg_Resend_Num ++;
	DCCStatus.Msg_ID_Change = 1;
    BKD0_23_REG = 0x01; //clr rx fifo
    BKD0_18_REG = 0x08;	  //mark all data done
    KNL_Delay1us(1);
    BKD0_18_REG = 0x00;
    BKD0_19_REG = 0x29;
	TR2_Set();
	TR2 = 1;	
}
void DFP_Vdm_Msg(void)
{
    switch(DCCMSG.RcvDate[0]&0x1F)  //Command
    {
		case Discover_Identity :
				DCCMSG.DataOrder = CC_Discover_Id;
				Send_MessageDcc();
				break;
		case Discover_SVIDs :
				DCCMSG.DataOrder = CC_Data_Msg[2];
				Send_MessageDcc();
				break;
		default :
				break;
    }
}
void DFP_Message(void)  //DFP message
{
    if(!DCCMSG.ExtMsg)
	{
		if(DCCMSG.Datalenth == 0x00)   //NO data, header Only
		{
			switch(DCCMSG.MsgType)
			{
				case GoodCRC      	:
						break;
				case PS_RDY         :
						if(((BKE2_27_REG&0x04)==0x00)&&((BKD0_30_REG&0xf0)||(BKE5_D4_REG&0x10))&&(!UCCStatus.PRSended)&&(!UCCStatus.PowerRole))//DCC IS IN
						{
							if((((BKE2_17_REG&0x04)==0x00)&&(BKD0_B0_REG&0xf0))||(((BKE2_17_REG&0x04)==0x04)&&(BKD0_B0_REG&0x50)))
							{
								UCCStatus.PRSended = 1;
								UCCStatus.ReadySendPR = 1; //后插电源，支持包
							}
						}
						if((!UCCStatus.ps_rdy_send)&&(UCCStatus.PrDone)) //DFP_SOURCE 4 UFP_SINK 7
						{
							if(UCCStatus.DataRole)
							{
								if((UCCStatus.Swap_Sent&Vconn_Sent) == 0)
								{
									UCCStatus.vconn_swap_en=1;
//									Typec_Timer(30);
								}
								else if((UCCStatus.Swap_Sent&DR_Sent)== 0)
								{
									UCCStatus.dr_swap_en = 1;
//									Typec_Timer(30);
								}
							}
							UCCStatus.ps_rdy_send = 1;
//							#if TYPEC_FRSWAP_EN == ENABLED
//							vbus_off_det();
//							#endif
							TR2_Set();
							TR2 = 1;    //enable Time0
						}
						break;
				case PR_Swap        :
						break;
				case DR_Swap        :
						break;
				case Get_Sink_Cap   :
						DCCMSG.DataOrder = CC_Data_Msg[13];
						Send_MessageDcc();
						break;
				case Soft_Reset     :
						DCCMSG.MsgNum = 0;
						DCCMSG.DataOrder = CC_Ctrl_Msg[2];
						Send_MessageDcc();
						break;
				default         :
						break;
			}
		}
		else
		{
			switch (DCCMSG.MsgType)
			{
				case Source_Capabilities   :
						#if PD_PPS_EN == 1
						DCCMSG.CcVersion = (DCCMSG.Header[0]&0xc0)>>6;
						#endif
						DCCStatus.sourcecap_flag = 1; //20210804
						Adapter_Source_Cal();
						Request_Dcc_Fix();
						DCCMSG.DataOrder = DCCMSG.RequestBuf; //send Request
						Send_MessageDcc();
						break;
				case Request               :
						#if PD_PPS_EN == 1
						DCCMSG.CcVersion = (DCCMSG.Header[0]&0xc0)>>6;
						#endif
						break;
				case Vendor_Defined        :
						DFP_Vdm_Msg();
						break;
				default                    :
						break;
			}
		}
	}
}

#endif