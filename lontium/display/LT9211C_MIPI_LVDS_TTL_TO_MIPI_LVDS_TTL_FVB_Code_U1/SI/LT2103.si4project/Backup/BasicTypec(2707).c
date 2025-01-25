//////////////////////////////////////
//Project:   LT2101
//Filename:  BasicTypec.c
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#include "Include.h"
#if TYPECRX_EN == ENABLED

u8 Chip_Sum_Cal(u8 ucsum)
{
	ucsum = ucsum + 2;
	if(ucsum>0x0e)
	{
	 	ucsum = 0;
	}
	else
	{;}
	return ucsum;
}

//================================
//pucMessage:input ponitor,message got from cc fifo
//ucMismatch_Chunked_EN:input,bit0 stands for Mismatch,bit1 stands for chunked suppport
//pucRequestMsg:out,requesr message to be sent
//================================
void Chip_Request_Fix(u8 IN *pucMessage,u8 IN ucMismatch_Chunked_EN,u8 OUT *pucRequestMsg,u8 IN ucCC_Ver)
{
	u16 usMax_Cur_5V = 0;
	usMax_Cur_5V = ((u16)(pucMessage[1]&0x03)<<8) + pucMessage[0];
    pucRequestMsg[0]= 0x42;
    pucRequestMsg[1]= 0x10;
    pucRequestMsg[2]=  pucMessage[0];
    pucRequestMsg[3]= (pucMessage[1]&0x03)|((pucMessage[0]&0x3f)<<2);
    pucRequestMsg[4]= (((pucMessage[0]&0xc0)>>6)|((pucMessage[1]&0x03)<<2));
    if(ucCC_Ver >= 2)
    {
        if(ucMismatch_Chunked_EN & BIT1_1)//BIT1 stands for Chunked bit
        {
            pucRequestMsg[4] |= (pucMessage[3]&0x01)<<7; //chunked bit from source cap
        }
        else
        {
            pucRequestMsg[4] &= BIT7_0;//Unchunked Extended Messages Not Supported
        }	
        pucRequestMsg[4] &= BIT5_0;
    }
	else
    {
        pucRequestMsg[4] &= 0x0f;
    }
    pucRequestMsg[5] = 0x13;
	if(ucMismatch_Chunked_EN & BIT0_1)//Mismatch support 
	{
		if(usMax_Cur_5V < 300)//mismatch
		{
			pucRequestMsg[5] |= BIT2_1;		
		}
	}
	else
	{
		;
	}
}

void Chip_CCMessage_Resend(IN u8 ucCC_Port)
{
	if(ucCC_Port == UCC)
	{
		UCCStatus.u1CCDataMsg_Sent = FALSE;
		UCCMSG.u1RcvGoodCRC = FALSE;
		if(UCCStatus.u1Msg_ID_Change == TRUE)
		{
			;
		}
		else
		{
			UCCStatus.ucRetryCounter++;
		}
		if(UCCMSG.ucCcVersion >= 2)
		{
			UCCStatus.ucnRetryCount = nRetryCount_PD30;
		}
		else
		{
			UCCStatus.ucnRetryCount = nRetryCount_PD20;
		}
		UCCStatus.u1Msg_ID_Change = TRUE;	
		Knl_TR2ValueSet();
		if(UCCStatus.ucContract_Succeed)
		{
			UCCStatus.u1CCDataMsg_Sent = TRUE;
		}
	}
	else if(ucCC_Port == DCC)	
	{
        DCCStatus.u1CCDataMsg_Sent = FALSE;
		DCCMSG.u1RcvGoodCRC = FALSE;
		if(DCCStatus.u1Msg_ID_Change == TRUE)
		{
			;
		}
		else
		{
			DCCStatus.ucRetryCounter++;
		}
        if(DCCMSG.ucCcVersion >= 2)
		{
			DCCStatus.ucnRetryCount = nRetryCount_PD30;
		}
		else
		{
			DCCStatus.ucnRetryCount = nRetryCount_PD20;
		}
		DCCStatus.u1Msg_ID_Change = TRUE;
		Knl_TR2ValueSet();
        DCCStatus.u1CCDataMsg_Sent = TRUE;
	}
}
void Chip_Send_MessageUcc(void)
{
    u8 ucSendData;
	u8 ucSendMegSndDataOffset;
    static u8 ucUccTotalData;
	static u8 ucMessage_ID_Send = 0x00;
	UCCMSG.pBuffer_Order = UCCMSG.pDataOrder;
	ucUccTotalData = ((UCCMSG.pDataOrder[1] & 0x70)>>2) + 2;
    for(ucSendMegSndDataOffset=0; ucSendMegSndDataOffset < ucUccTotalData; ucSendMegSndDataOffset++)
    {
        ucSendData = *UCCMSG.pDataOrder;
        UCCMSG.pDataOrder++;
		if(ucSendMegSndDataOffset< 10)
		{
			if(ucSendMegSndDataOffset== 1)
			{		
				ucSendData &=0xF0;
				if(UCCStatus.u1Msg_ID_Change == 1)
				{
					ucMessage_ID_Send = UCCMSG.ucMessageID;
					UCCMSG.ucMessageID = Chip_Sum_Cal(UCCMSG.ucMessageID);			
				}
				else
				{
					;
				}
				ucSendData = (ucSendData|ucMessage_ID_Send);
				(UCCStatus.u1PowerRole)?(ucSendData |= BIT0_1):(ucSendData &= BIT0_0);
			}
			else if(ucSendMegSndDataOffset == 0)
			{
				ucSendData &= 0x1F;
				if(UCCMSG.ucCcVersion < 0x02)
				{
					ucSendData |=  BIT6_1;
				}
				else
				{
					ucSendData |=  BIT7_1;
				}
				(UCCStatus.u1DataRole)?(ucSendData |= BIT5_1):(ucSendData &= BIT5_0);
			}
			else if((UCCStatus.u1Multi_Function)&&(ucSendMegSndDataOffset== 6))
			{
				ucSendData |= BIT4_1; // Multifunction Prefered
				UCCStatus.u1Multi_Function =0;
			}
			else if((UCCMSG.u1Vdm_Msg)&&(ucSendMegSndDataOffset== 3))
			{
				(UCCMSG.ucCcVersion >= 2)?(ucSendData |= BIT5_1):(ucSendData &= BIT5_0);
			}
		}
        else if(ucSendMegSndDataOffset == 10)
        {        
            BKD0_99_REG = 0x09; 
        }
        BKD0_9A_REG	= ucSendData;      
    }
    if(ucSendMegSndDataOffset > 10)
    {
        ;
    }
    else
    {
        BKD0_99_REG = 0x09; 
    }
    BKD0_A3_REG =  0x01;       //clr rx fifo
    BKD0_98_REG |= BIT3_1;	  //mark all data done
    BKD0_98_REG &= BIT3_0;	
	Chip_CCMessage_Resend(UCC);	
}
//===================================//
//IN
//Com_Type:REQ,ACK,NACK,BUSY
//Command:enter_mode,exit mode,attention
void Chip_AltMode_Handle(IN u8 ucCom_Type,IN u8 ucCommand)
{
	UCCMSG.szCC_ModeMsg_Buffer[2] = (ucCom_Type<<6); //NACK
	UCCMSG.szCC_ModeMsg_Buffer[2] |= ucCommand;
    UCCMSG.szCC_ModeMsg_Buffer[3] &= 0xf8;//Object position
    if(ucCommand >= Enter_Mode)
    {
        if(((UCCMSG.szRcvDate[1]&0x07)==0)||((UCCMSG.szRcvDate[1]&0x07)==0x07))
        {
            UCCMSG.szCC_ModeMsg_Buffer[3] |= 0x07;//Object position
        }
        else
        {
            UCCMSG.szCC_ModeMsg_Buffer[3] |= (UCCMSG.szRcvDate[1]&0x07);//Object position
        }
    }
	UCCMSG.szCC_ModeMsg_Buffer[4] = UCCMSG.szRcvDate[2];//SID&VID
	UCCMSG.szCC_ModeMsg_Buffer[5] = UCCMSG.szRcvDate[3];//SID&VID
}

void Chip_Discover_Handle(u8 IN ucPD_Ver,u8 IN *pucData,u8 IN ucReply)
{
    if(ucPD_Ver >= 0x02)
    {
        szCC_DiscoverIDMsg[8] = 0x40;
    }
    else
    {
        szCC_DiscoverIDMsg[8] = 0x00;
    }
    szCC_DiscoverIDMsg[2] &= 0x3f;
    szCC_DiscoverIDMsg[2] |= ucReply;
    szCC_DiscoverIDMsg[4] = pucData[2];
    szCC_DiscoverIDMsg[5] = pucData[3];
}

void Chip_ChunkMessage_Handle(void)
{
	#if PD_CHUNK_EN  == ENABLED
    static u16 usData_Size = 0;
	static u8 ucChunk_Num = 0;
	static u16 ucNum_Data_Obj = 0;
	static u16 ucNum_Data = 0;
    u8 Chunked_Message[6];
	if(UCCMSG.szHeader[3] & BIT7_1)
	{
		if((UCCMSG.szHeader[3]& BIT2_1) == 0x00)//request chunk = 0;
		{
			if((UCCMSG.szHeader[3]&0x78)==0)//if chunk number equal 0
			{
				ucNum_Data_Obj = 0;
			}
			usData_Size = ((u16)(UCCMSG.szHeader[3]& BIT0_1)<<8) + UCCMSG.szHeader[2];
			ucNum_Data = ((UCCMSG.szHeader[1]&0x70)>>2)- 2;//remove Externed szHeader;
			ucNum_Data_Obj += ucNum_Data;
			ucChunk_Num = (UCCMSG.szHeader[3]&0x78) + 8;//should less than 10

			if((usData_Size <= ucNum_Data_Obj)||(ucChunk_Num > 72))
			{
				ucNum_Data_Obj = 0;
				UCCMSG.pDataOrder = szCC_CtrlMsg[6];
				Chip_Send_MessageUcc();	
			}
			else
			{
				Chunked_Message[0]=UCCMSG.szHeader[0];
				Chunked_Message[1]=0x90;
				Chunked_Message[2]=0x00;
				Chunked_Message[3]=0x84|ucChunk_Num;
				Chunked_Message[4]=0x00;
				Chunked_Message[5]=0x00;
				UCCMSG.pDataOrder = Chunked_Message;
				Chip_Send_MessageUcc();	
			}			
		}
		else
		{
			;
		}		
	}
    else
    #endif
    {
        UCCMSG.pDataOrder = szCC_CtrlMsg[6];//not support msg
        Chip_Send_MessageUcc();
    }
}

#if PD_PPS_EN == ENABLED

u8 Chip_Object_Compare(u8 IN *pucData)
{
    static u8 ucRequestObject;
    ucRequestObject = (pucData[1]&0x70)>>4;
    return ucRequestObject;
}
u16 Chip_RequestCur_Compare(u8 IN *pucData,u8 IN ucObject)
{
    static u16 Request_Cur;
    Request_Cur = ((u16)(pucData[(ucObject*4)-1]&0x03)<<8) + pucData[(ucObject*4)-2];
    return Request_Cur;
}

u8 Chip_Request_Compare(void)
{
    u8 ucRequestObject;
    u16 Request_Cur = 0x00;
    u16 Request_Cur_Ori = 0x00;
	ucRequestObject = (UCCMSG.szRcvDate[3]&0x70)>>4;//get Object position      
    Request_Cur = ((u16)(UCCMSG.szRcvDate[2]&0x0f)<<6) + ((UCCMSG.szRcvDate[1]&0xfc)>>2) ;//Request from UCC with operation current
    if(DCCStatus.u1AdapterWithPD == TRUE)	
    {
        if(UCCMSG.ucCcVersion < 2)//PD2.0
        {
            if(ucRequestObject <= Chip_Object_Compare(DCCMSG.szAdapterTmp))
            {
                ;
            }
            else
            {
                return 0;
            }
            Request_Cur_Ori = Chip_RequestCur_Compare(DCCMSG.szAdapterTmp,ucRequestObject);
        }
        else//PD3.0
        {
            if(ucRequestObject <= Chip_Object_Compare(DCCMSG.szAdapterCap_For_PD30))
            {
                ;
            }
            else
            {
                return 0;
            }
            Request_Cur_Ori = Chip_RequestCur_Compare(DCCMSG.szAdapterCap_For_PD30,ucRequestObject);
        }
    }	
    else
    {
        if(ucRequestObject <= Chip_Object_Compare(szCC_DataMsg[0]))
        {
            ;
        }
        else
        {
            return 0;
        }
        Request_Cur_Ori = Chip_RequestCur_Compare(szCC_DataMsg[0],1);
    }
    if(Request_Cur > Request_Cur_Ori)
    {
        return 0;
    }
    return 1;
}
#endif

u8 Chip_Ucc_RequestCal(void)	//FOR REQUEST ADAPTER
{
    u8 ucPPS_Request = 0;
	static u8 ucPPSPosition;
    static u16 usRequest_Cur = 0x00;
	ucPPSPosition = (UCCMSG.szRcvDate[3]&0x70)>>4;//get Object position
	#if PD_PPS_EN == ENABLED
	if(ucPPSPosition== DCCMSG.szPPS_Object[0]||(ucPPSPosition==DCCMSG.szPPS_Object[1])||(ucPPSPosition==DCCMSG.szPPS_Object[2])
    ||(ucPPSPosition==DCCMSG.szPPS_Object[3])||(ucPPSPosition==DCCMSG.szPPS_Object[4])||(ucPPSPosition==DCCMSG.szPPS_Object[5]))
	{
		ucPPS_Request = 1;
		UCCMSG.szRequestTmp[0] = UCCMSG.szHeader[0];
		UCCMSG.szRequestTmp[1] = UCCMSG.szHeader[1];
		UCCMSG.szRequestTmp[2] = UCCMSG.szRcvDate[0];
		UCCMSG.szRequestTmp[3] = UCCMSG.szRcvDate[1];
		UCCMSG.szRequestTmp[4] = UCCMSG.szRcvDate[2];
		UCCMSG.szRequestTmp[5] = UCCMSG.szRcvDate[3];
	}
	else
	#endif
	{
		ucPPS_Request = 0;
		memcpy(&UCCMSG.szRequestTmp[2],&DCCMSG.szAdapterCap_Ori[(ucPPSPosition*4)- 2],4);
		usRequest_Cur = ((u16)(UCCMSG.szRequestTmp[3]&0x03)<<8)+ UCCMSG.szRequestTmp[2];
		UCCMSG.szRequestTmp[0] = 0x42;
		UCCMSG.szRequestTmp[1] = 0x12;
		UCCMSG.szRequestTmp[5] = UCCMSG.szRcvDate[3];//needed
		
		UCCMSG.szRequestTmp[3] &= 0x03;
		UCCMSG.szRequestTmp[3] |= (usRequest_Cur<< 2);
		usRequest_Cur >>= 6;
		UCCMSG.szRequestTmp[4] = 0x00;//needed for Bit7(PD3.0)
		UCCMSG.szRequestTmp[4] |= (usRequest_Cur & 0x0f);
	}	
    return ucPPS_Request;
}


void Chip_UFP_VdmMsg(u8 ucMsg_Type)
{
    if(ucMsg_Type == Vendor_Defined)
    {
        if(UCCMSG.szRcvDate[1] & BIT7_1)//Structured VDM
        {
            if((UCCMSG.szRcvDate[2] <= DP_ALT_MODE_HBYTE)&&(UCCMSG.szRcvDate[3] == DP_ALT_MODE_HBYTE))//UCCMSG.szRcvDate[4][5]
            {
                switch(UCCMSG.szRcvDate[0]&0x1F)  //Command
                {
                    case Discover_Identity   :			
                        Chip_Discover_Handle(UCCMSG.ucCcVersion,UCCMSG.szRcvDate,ACK);
                        UCCMSG.pDataOrder =  szCC_DiscoverIDMsg;
                        if((UCCMSG.ucCcVersion <= PD20)&&((UCCMSG.szHeader[0] & BIT5_1)==0x00))//
                        {
                            ;
                        }
                        else
                        {
                            Chip_Send_MessageUcc();
                            UCCStatus.ucVDM_Step |= BIT0_1;
                            UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Vdm_Msg,Discover_Identity,StrVdm);
                        }
                        break;
                    case Discover_SVIDs      :
                        UCCMSG.pDataOrder = szCC_DataMsg[2];
                        UCCStatus.ucVDM_Step |= BIT1_1;
                        Chip_Send_MessageUcc();
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Vdm_Msg,Discover_SVIDs,StrVdm);
                        break;
                    case Discover_Modes      :	
                        UCCStatus.ucVDM_Step |= BIT2_1;
                        if(g_stDpRx.ucRxMaxLaneCount == 4)
                        {
                            memcpy(UCCMSG.szCC_ModeMsg_Buffer,szCC_DataMsg[3],10);                                 
                        }
                        else
                        {
                            memcpy(UCCMSG.szCC_ModeMsg_Buffer,szCC_DataMsg[4],10);
                        }	
                        if(UCCStatus.ucVDM_Step &BIT1_1)
                        {															
                        ;	//ACK
                        }
                        else
                        {								
                            Chip_AltMode_Handle(PDNACK,Discover_Modes);	//NACK							                             
                        }	
                        UCCMSG.pDataOrder = UCCMSG.szCC_ModeMsg_Buffer;
                        Chip_Send_MessageUcc();	
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Vdm_Msg,Discover_Modes,StrVdm);
                        break;
                    case Enter_Mode          :
                        UCCStatus.ucVDM_Step |= BIT3_1;
                        if(UCCStatus.ucVDM_Step & BIT1_1)
                        {							
                            if(((UCCStatus.u1DataRole == TRUE)&&(UCCStatus.ucSwap_Sent&DR_Sent_Accept))||(UCCStatus.u1DataRole == FALSE))
                            {
                                memcpy(UCCMSG.szCC_ModeMsg_Buffer,szCC_DataMsg[5],6);
                                if((UCCMSG.szRcvDate[1]&0x07)==0x01)//Object position=1
                                {
                                    Chip_AltMode_Handle(PDACK,Enter_Mode);
                                }
                                else   //Object position != 1
                                {
                                    Chip_AltMode_Handle(PDNACK,Enter_Mode);
                                }
                                UCCMSG.pDataOrder = UCCMSG.szCC_ModeMsg_Buffer;
                                Chip_Send_MessageUcc();	
                            }
                        }
                        else
                        {
                            memcpy(UCCMSG.szCC_ModeMsg_Buffer,szCC_DataMsg[5],6);
                            Chip_AltMode_Handle(PDNACK,Enter_Mode);
                            UCCMSG.pDataOrder = UCCMSG.szCC_ModeMsg_Buffer;
                            Chip_Send_MessageUcc();	
                        }
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Vdm_Msg,Enter_Mode,StrVdm);
                        break;
                    case Exit_Mode           :	
                        memcpy(UCCMSG.szCC_ModeMsg_Buffer,szCC_DataMsg[6],6);
                        if(UCCStatus.ucVDM_Step & BIT3_1)
                        {
                            if((UCCMSG.szRcvDate[1]&0x07)==0x01)
                            {
                                Chip_AltMode_Handle(PDACK,Exit_Mode);//Object position=1
                            }
                            else
                            {
                                Chip_AltMode_Handle(PDNACK,Exit_Mode);//Object position != 1
                            }
                        }
                        else
                        {							
                            Chip_AltMode_Handle(PDNACK,Exit_Mode);								
                        }	
                        UCCMSG.pDataOrder = UCCMSG.szCC_ModeMsg_Buffer;
                        Chip_Send_MessageUcc();	
                        UCCStatus.ucVDM_Step &= BIT3_0;
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Vdm_Msg,Exit_Mode,StrVdm);
                        break;
                    case Attention           :
                    break;
                    case DP_Status_Update    :
                        UCCStatus.ucVDM_Step |= BIT4_1;
                        UCCStatus.u1Multi_Function = (g_stDpRx.ucRxMaxLaneCount == 4)?(FALSE):(TRUE);
                        if(UCCStatus.ucVDM_Step & BIT6_1)//Attention HIGH
                        {
                            UCCMSG.pDataOrder = szCC_DataMsg[8];//Update HIGH
                        }
                        else
                        {
                            UCCMSG.pDataOrder = szCC_DataMsg[7];//Update LOW
                        }
                        Chip_Send_MessageUcc();	 //
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Vdm_Msg,DP_Status_Update,StrVdm);
                        break;
                    case DP_Config	         :
                        UCCStatus.ucVDM_Step |= BIT5_1;
                        UCCMSG.pDataOrder = szCC_DataMsg[9];
                        Chip_Send_MessageUcc();							
                        #if TYPEC_PRSWAP_EN == ENABLED
                        if((CHIP_DccOn_Det(SINK)==TRUE)&&(UCCStatus.ucPRSended==0)&&(!UCCStatus.u1PowerRole))//dcc in
                        {
                            UCCStatus.ucPRSended = 1;
                        }
                        else
                        #endif
                        {
                            if(UCCStatus.u1IsCc_done == FALSE)
                            {
                                UCCStatus.u1IsCc_done = TRUE; //
                            }
                        }
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Vdm_Msg,DP_Config,StrVdm);
                        break;
                    default               :
                    break;
                }		
            }         
            else if((UCCMSG.szRcvDate[2] == 0x61)&&(UCCMSG.szRcvDate[3]== 0x2f))// for lontium
            {
                switch(UCCMSG.szRcvDate[0]&0x1F) //Command
                {
                    case Discover_Modes  :
                        UCCStatus.ucVDM_Step |= BIT2_1;
                        memcpy(UCCMSG.szCC_ModeMsg_Buffer,szCC_DataMsg[14],10);
                        if(UCCStatus.ucVDM_Step & BIT1_1)
                        {							
                            ;
                        }
                        else
                        {							
                            Chip_AltMode_Handle(PDNACK,Discover_Modes);	//NACK																	
                        }
                        UCCMSG.pDataOrder = UCCMSG.szCC_ModeMsg_Buffer;
                        Chip_Send_MessageUcc();
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Vdm_Msg,Discover_Modes,StrVdm);      
                        break;
                    case Enter_Mode  :
                        UCCStatus.ucVDM_Step |= BIT3_1;
                        if(UCCStatus.ucVDM_Step & BIT1_1)
                        {							
                            if(((UCCStatus.u1DataRole == TRUE)&&(UCCStatus.ucSwap_Sent&DR_Sent_Accept))||(UCCStatus.u1DataRole == FALSE))
                            {								
                                memcpy(UCCMSG.szCC_ModeMsg_Buffer,szCC_DataMsg[5],6);
                                if(((UCCMSG.szRcvDate[1]&0x07)==0)||((UCCMSG.szRcvDate[1]&0x07)==0x07))
                                {
                                    Chip_AltMode_Handle(PDNACK,Enter_Mode);
                                }
                                else
                                {
                                    Chip_AltMode_Handle(PDACK,Enter_Mode);
                                }
                                UCCMSG.pDataOrder = UCCMSG.szCC_ModeMsg_Buffer;
                                Chip_Send_MessageUcc();									
                            }
                        }
                        else
                        {
                            memcpy(UCCMSG.szCC_ModeMsg_Buffer,szCC_DataMsg[5],6);
                            Chip_AltMode_Handle(PDNACK,Enter_Mode);
                            UCCMSG.pDataOrder = UCCMSG.szCC_ModeMsg_Buffer;
                            Chip_Send_MessageUcc();	
                        }
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Vdm_Msg,Enter_Mode,StrVdm);
                        break;
                    case Exit_Mode           :						
                        if(UCCStatus.ucVDM_Step &BIT3_1)
                        {
                            memcpy(UCCMSG.szCC_ModeMsg_Buffer,szCC_DataMsg[6],6);
                            if(((UCCMSG.szRcvDate[1]&0x07)==0)||((UCCMSG.szRcvDate[1]&0x07)==0x07))
                            {
                                Chip_AltMode_Handle(PDNACK,Exit_Mode);
                            }
                            else
                            {
                                Chip_AltMode_Handle(PDACK,Exit_Mode);
                            }
                            UCCMSG.pDataOrder = UCCMSG.szCC_ModeMsg_Buffer;
                            Chip_Send_MessageUcc();	
                        }
                        else
                        {
                            memcpy(UCCMSG.szCC_ModeMsg_Buffer,szCC_DataMsg[6],6);
                            Chip_AltMode_Handle(PDNACK,Exit_Mode);
                            UCCMSG.pDataOrder = UCCMSG.szCC_ModeMsg_Buffer;
                            Chip_Send_MessageUcc();	
                        }	
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Vdm_Msg,Exit_Mode,StrVdm);
                        UCCStatus.ucVDM_Step &= BIT3_0;
                        break;
                    default     :
                        break;
                }
            }
            else if((UCCMSG.szRcvDate[2]==Samsung_LByte)&&(UCCMSG.szRcvDate[3]==Samsung_HByte))// for Samsung Dex
            {
                switch  (UCCMSG.szRcvDate[0]&0x1F)  //Command
                {
                    ;
                }
            }
            else if((UCCMSG.szRcvDate[2]==Switch_LByte)&&(UCCMSG.szRcvDate[3]==Switch_HByte))	//Switch
            {
                switch(UCCMSG.szRcvDate[0]&0x1F)
                {
                    ;
                }
            }
            else
            {
                switch(UCCMSG.szRcvDate[0]&0x1F) //Command
                {
                    case Discover_Identity   :	
                        Chip_Discover_Handle(UCCMSG.ucCcVersion,UCCMSG.szRcvDate,NACK);
                        UCCMSG.pDataOrder = szCC_DiscoverIDMsg;
                        Chip_Send_MessageUcc();                         
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Vdm_Msg,Discover_Identity,StrVdm);
                        break;
                    case Discover_SVIDs      :                       
                        memcpy(UCCMSG.szCC_ModeMsg_Buffer,szCC_DataMsg[2],10);
                        Chip_AltMode_Handle(PDNACK,Discover_SVIDs);	//NACK
                        UCCMSG.pDataOrder = UCCMSG.szCC_ModeMsg_Buffer;
                        Chip_Send_MessageUcc();	
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Vdm_Msg,Discover_SVIDs,StrVdm);
                        break;
                    default:
                        break;
                }
            }
        }
        else //unstructure
        {
            if(UCCMSG.ucCcVersion >= 2)
            {
                UCCMSG.pDataOrder = szCC_CtrlMsg[6];
                Chip_Send_MessageUcc();	
                UCCMSG.ucLastMsgType = 0xff;
            }
        }
    }
}

void CHIP_UFP_Message(u8 ucMsg_Type,u8 ucLength,u8 ucExt)  //UFP message
{
    if(ucExt == 0x00)//Not Extented
    {
        if(ucLength == 0x00)   //Control Message
        {
            switch(ucMsg_Type)
            {
                case GoodCRC  :
                    break;
                case GotoMin        : 
                    break;
                case Accept  :
                    if(UCCStatus.ucFlow_Step == 2)//receive source cap
                    {
                        UCCStatus.ucFlow_Step = 3;
                    }
                    if(UCCMSG.ucLastMsgType == CHIP_MsgType_Cal(Ctrl_Msg,PS_RDY,StrVdm))
                    {                        
                        if(UCCStatus.ucFlow_Step == 1)
                        {
                            UCCMSG.pDataOrder = szCC_CtrlMsg[7];
                            Chip_Send_MessageUcc();                            
                        }
                    }
                    #if TYPEC_DRSWAP_EN == ENABLED			
                    if(UCCMSG.ucLastMsgType==CHIP_MsgType_Cal(Ctrl_Msg,DR_Swap,StrVdm))
                    {
                        UCCStatus.ucSwap_Sent &= DR_No_Sent;
                        UCCStatus.ucSwap_Sent |= DR_Sent_Accept;
                        UCCStatus.u1DataRole = FALSE;
                    }
                    else if(UCCMSG.ucLastMsgType==CHIP_MsgType_Cal(Ctrl_Msg,VCONN_Swap,StrVdm))
                    {
                        if((UCCStatus.ucSwap_Sent&DR_Sent) == 0)
                        {
                            UCCStatus.ucDrSwap_En = 1;							
                        }
                    }
                    else if(UCCMSG.ucLastMsgType==CHIP_MsgType_Cal(Ctrl_Msg,PR_Swap,StrVdm))
                    {
                        if(UCCStatus.ucPRSwaping == 1)
                        {
                            UCCStatus.ucPRSwaping = 2;//pr swap enter into Accept
                        }
                        if(UCCStatus.ucPRSwaped == 1)
                        {
                            UCCStatus.ucPRSwaped = 2;
                        }
                        UCCStatus.u1PowerRole = TRUE;
                    }
                    #endif
                    break;
                case Reject         :
                    if(UCCMSG.ucLastMsgType==CHIP_MsgType_Cal(Ctrl_Msg,PR_Swap,StrVdm))
                    {
                        Adapter_GPIO_Ctrl(IN LOW);
                        UCCStatus.u1PrDone = TRUE;
                        UCCStatus.ucPRSwaping = 0;
                        UCCStatus.ucPRSwaped = 3;
                        if(UCCStatus.u1IsCc_done == FALSE)//fixed
                        {
                            UCCStatus.u1IsCc_done = TRUE; // Hdmi_Edid = 0x02;
                        }
                    }
                    else if(UCCMSG.ucLastMsgType==CHIP_MsgType_Cal(Ctrl_Msg,VCONN_Swap,StrVdm))
                    {
                        if((UCCStatus.ucSwap_Sent & DR_Sent) == 0)
                        {
                            UCCStatus.ucDrSwap_En = 1;
                        }
                    }
                    else if(UCCMSG.ucLastMsgType==CHIP_MsgType_Cal(Ctrl_Msg,DR_Swap,StrVdm))
                    {						
                        UCCStatus.ucSwap_Sent |= DR_Sent_Reject;
                        UCCMSG.ucLastMsgType = 0xff;																		
                    }
                    break;
                case Ping          	:	
                    break; 
                case PS_RDY   :               
                    UCCStatus.ucFlow_Step = 1;
                    #if TYPEC_PRSWAP_EN == ENABLED
                    if((UCCStatus.ucPRSwaping)&&((UCCStatus.ucPRSwaped==2)||(UCCStatus.ucPRSwaped==3))) //SEND PS_RDY RECIEVE PS_RDY
                    {
                        UCCStatus.ucPRSwaping = 1;
                        UCCStatus.ucPRSwaped = 3;
                        if(UCCMSG.ucCcVersion >= 0x02)
                        {
                            DRV_RpCur_Sel(UCC,Rp_SinkTxOK);
                        }
                        else
                        {
                            DRV_RpCur_Sel(UCC,Rp_SinkTxNG);
                        }
                        Source_GPIO_Ctrl(IN HIGH);
                        Adapter_GPIO_Ctrl(IN HIGH);
                        DRV_PowerRole_Set(UCC,SOURCE);
                        UCCStatus.u1Toggle_DFP_EN = TRUE;
                        BKD0_3E_REG = 0x01;//DFP
                        UCCStatus.u1PowerRole = TRUE;
                        if(UCCStatus.u1UCcInput_type == FEMALE)
                        {
                            DRV_CC_LogicRst(UCC);
                        }
                        UCCStatus.u1PsRdy_Send  = TRUE;
                        TH2 = 0xD0;//4ms
                        TL2 = 0x00;
                        TR2 = 1;   //enable Time0
                    }
                    if(UCCStatus.ucPRSwaped == 6)
                    {                          
                        UCCStatus.ucPRSwaping = 0;
                        UCCStatus.u1PowerRole = FALSE;
                        UCCStatus.ucPRSwaped = 2;    
                    }
                    #endif
                    #if TYPEC_DRSWAP_EN == ENABLED
                    if(UCCMSG.ucLastMsgType == CHIP_MsgType_Cal(Ctrl_Msg,VCONN_Swap,StrVdm))
                    {
                        if((UCCStatus.ucSwap_Sent & DR_Sent) == 0)
                        {
                            UCCStatus.ucDrSwap_En = 1;
                        }
                    }		
                    if((CHIP_DccOn_Det(SINK)== TRUE)&&(UCCStatus.ucPRSended==0)&&(UCCStatus.u1PowerRole == FALSE)&&(UCCStatus.ucFRSwaping==0))
                    {
                        UCCStatus.ucPRSended = 1;
                    }
                    #endif
                    break;
                case Get_Source_Cap ://20210728
                    if(CHIP_DccOn_Det(SINK) == TRUE)
                    {                           
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
                        if(Chip_RpOn_Scan() == 1)//TEST.PD.PROT.SRC.1
                        {
                            UCCStatus.ucFlow_Step = 5;
                        }
                        else  //TEST.PD.PROT.SRC.2
                        {
                            ;
                        }
                    }
                    else
                    {
                        if(UCCMSG.ucCcVersion < 2)//PD2.0
                        {
                            UCCMSG.pDataOrder = szCC_CtrlMsg[3];
                        }
                        else
                        {
                            UCCMSG.pDataOrder = szCC_CtrlMsg[6];
                        }
                    }
                    Chip_Send_MessageUcc();			
                    break;
                case Get_Sink_Cap   :
                    if((UCCStatus.ucFlow_Step == 2)||(UCCStatus.ucFlow_Step == 6))	//TDA2.2.1//TEST.PD.PORT.SRC.06//TEST.PD.PORT.SNK.08
                    {
                        if(Chip_RpOn_Scan()==1)
                        {
                            UCCStatus.u1Flag_Source_Send = TRUE;
                        }
                        UCCMSG.ucMessageID = 0x00;
                        UCCMSG.pDataOrder = szCC_CtrlMsg[7];
                        Chip_Send_MessageUcc();                        
                    }		
                    else if(UCCStatus.ucFlow_Step ==3)
                    {
                        if(Chip_UccOff_Det() == FALSE)
                        {
                            DRV_HardReset_Set(UCC);
                            CHIP_Ucc_OffAction();
                        }
                    }
                    else
                    {
                        UCCStatus.ucFlow_Step = 0x01;
                        if(UCCMSG.ucCcVersion >= 2)
                        {
                            if(CHIP_DccOn_Det(SINK)==TRUE)
                            {
                                UCCMSG.pDataOrder = szCC_DataMsg[16];
                            }
                            else
                            {
                                UCCMSG.pDataOrder = szCC_DataMsg[19];
                            }							
                        }
                        else
                        {
                            if(CHIP_DccOn_Det(SINK)==TRUE)
                            {
                                UCCMSG.pDataOrder = szCC_DataMsg[13];
                            }
                            else
                            {
                                UCCMSG.pDataOrder = szCC_DataMsg[18];
                            }
                        }
                        Chip_Send_MessageUcc();
                    }					
                    break;
                case DR_Swap        :
                    #if TYPEC_DRSWAP_EN == ENABLED
                    if(UCCStatus.ucVDM_Step&0xf8)
                    {
                        if(Chip_UccOff_Det() == FALSE)
                        {
                            DRV_HardReset_Set(UCC);
                            CHIP_Ucc_OffAction();
                        }
                    }
                    else
                    {
                        UCCStatus.u1WaitMsg_Receive = FALSE;
                        UCCStatus.ucDrSwap_En = 2;
                        if(UCCStatus.u1DataRole == FALSE)
                        {
                            UCCMSG.pDataOrder = szCC_CtrlMsg[3];
                            Chip_Send_MessageUcc();
                        }
                        else
                        {
                            UCCMSG.pDataOrder = szCC_CtrlMsg[2];
                            Chip_Send_MessageUcc();
                            UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,DR_Swap,StrVdm);
                        }					
                        UCCStatus.ucSwap_Sent &= DR_No_Sent;
                        UCCStatus.ucSwap_Sent |= DR_Sent_Accept;
                    }
                    #endif
                    break;
                case PR_Swap :	
                    if(CHIP_DccOn_Det(SINK) == FALSE)//Adapter unplug
                    {                        
                        if(UCCMSG.ucCcVersion >= 0x02)
                        {
                            UCCMSG.pDataOrder = szCC_CtrlMsg[6];
                        }
                        else
                        {
                            UCCMSG.pDataOrder = szCC_CtrlMsg[3];
                        }   
                        UCCMSG.ucLastMsgType = 0xff;
                    }
                    else
                    {	
                        if(BKE2_17_REG&BIT2_1)//Rp as source
                        {
                            UCCStatus.ucFlow_Step = 2;
                            UCCStatus.ucPRSwaping = 1;
                            UCCStatus.ucPRSwaped = 4;
                            UCCMSG.pDataOrder = szCC_CtrlMsg[2];
                            Chip_Send_MessageUcc();
                            UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,Accept,StrVdm);
                        }
                        else
                        {                           
                            UCCStatus.ucPRSwaping = 2;//TEST.PD.PORT.SRC.09
                            UCCStatus.ucPRSwaped = 2;
                            UCCMSG.pDataOrder = szCC_CtrlMsg[2];
                            Chip_Send_MessageUcc();
                            UCCMSG.ucLastMsgType = 0xff;
                        }
                    }	
                    break;
                case VCONN_Swap		://20210804
                    #if TYPEC_DRSWAP_EN == ENABLED
                    UCCStatus.u1WaitMsg_Receive = FALSE;
                    UCCStatus.ucSwap_Sent |= Vconn_Sent;
                    UCCStatus.u1VconnSwap_En = FALSE;
                    if((CHIP_DccOn_Det(SINK)==TRUE)&&((UCCStatus.ucSwap_Sent&Vconn_Sent)==0x00))
                    {
                        UCCMSG.pDataOrder = szCC_CtrlMsg[2];
                    }
                    else
                    {
                        if((UCCMSG.ucCcVersion)>= 2)//not support
                        {
                            UCCMSG.pDataOrder = szCC_CtrlMsg[6];
                        }
                        else//reject
                        {
                            UCCMSG.pDataOrder = szCC_CtrlMsg[3];
                        }						
                    }					
                    Chip_Send_MessageUcc();
                    UCCMSG.ucLastMsgType = 0xff;
                    if((UCCStatus.ucSwap_Sent & DR_Sent) == 0)
                    {
                        UCCStatus.ucDrSwap_En = TRUE;
                    }
                    #endif
                    break;
                case Wait           :	
                    UCCStatus.u1WaitMsg_Receive = TRUE;
                    UCCMSG.pLast_DataOrder = UCCMSG.pBuffer_Order;
                    break;
                case Soft_Reset 	:
                    UCCMSG.ucMessageID = 0;
                    if(Chip_RpOn_Scan()== 1)
                    {
                        UCCStatus.u1Flag_Source_Send = TRUE;
                    }
                    UCCMSG.pDataOrder = szCC_CtrlMsg[2];//send ACCEPT
                    Chip_Send_MessageUcc();
                    UCCMSG.ucLastMsgType = 0xff;
                    break;
                case Not_Support    :
                    if(UCCMSG.ucLastMsgType==CHIP_MsgType_Cal(Ctrl_Msg,PR_Swap,StrVdm))
                    {
                        Adapter_GPIO_Ctrl(IN LOW);
                        UCCStatus.u1PrDone = TRUE;
                        UCCStatus.ucPRSwaping = 0;
                        UCCStatus.ucPRSwaped = 3;
                        if(UCCStatus.u1IsCc_done == FALSE)//fixed
                        {
                            UCCStatus.u1IsCc_done = TRUE; // Hdmi_Edid = 0x02;
                        }
                    }
                    else if(UCCMSG.ucLastMsgType==CHIP_MsgType_Cal(Ctrl_Msg,VCONN_Swap,StrVdm))
                    {
                        if((UCCStatus.ucSwap_Sent&DR_Sent) == 0)
                        {
                            UCCStatus.ucDrSwap_En = TRUE;
                        }
                    }
                    else if(UCCMSG.ucLastMsgType==CHIP_MsgType_Cal(Ctrl_Msg,DR_Swap,StrVdm))
                    {						
                        UCCStatus.ucSwap_Sent |= DR_Sent_Reject;
                        UCCMSG.ucLastMsgType = 0xff;																		
                    }
                    break;
                case Get_Source_Cap_Extended     : //20210728
                    if(CHIP_DccOn_Det(SINK) == TRUE)
                    {					
                        szCC_SourceCapExt[27] = UCCMSG.szPDP_Value[0];
                        UCCMSG.pDataOrder = szCC_SourceCapExt;
                    }
                    else
                    {							
                        UCCMSG.pDataOrder = szCC_CtrlMsg[6];			
                    }	
                    Chip_Send_MessageUcc();	
                    UCCMSG.ucLastMsgType = 0xff;
                    break;
                case FR_Swap :
                    #if TYPEC_FRSWAP_EN  == ENABLED
                    if(UCCStatus.ucFRSwaping)
                    {
                        if(UCCStatus.u1PowerRole)
                        {
                            UCCMSG.pDataOrder = szCC_CtrlMsg[2];
                            Chip_Send_MessageUcc();
                            UCCStatus.u1PowerRole = FALSE;
                            UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,FR_Swap,StrVdm);                          }
                        else
                        {
                            UCCMSG.pDataOrder = szCC_CtrlMsg[3];//reject
                            Chip_Send_MessageUcc();
                            UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,Reject,StrVdm);
                        }
                    }
                    else
                    {
                        KNL_Delay1ms(1);
                        if(Chip_UccOff_Det() == FALSE)
                        {
                            DRV_HardReset_Set(UCC);
                            CHIP_Ucc_OffAction();
                        }
                    }
                    #endif
                    break;								
                case Get_Status     : 			
                case Get_PPS_Status     :
                case Get_Country_Codes  :
                    UCCMSG.pDataOrder = szCC_CtrlMsg[6];//Not support
                    Chip_Send_MessageUcc();	
                    UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,Not_Support,StrVdm);
                    break;			
                default :
                    if(UCCMSG.ucCcVersion >= 2)
                    {
                        UCCMSG.pDataOrder = szCC_CtrlMsg[6];//not support
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,Not_Support,StrVdm);
                    }
                    else
                    {
                        UCCMSG.pDataOrder = szCC_CtrlMsg[3];
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,Reject,StrVdm);
                    }						
                    Chip_Send_MessageUcc();	
                    break;
            }
        }
        else //Data Message
        {
            switch (ucMsg_Type)
            {
                case Source_Capabilities   :
                    UCCStatus.u1Toggle_enable = FALSE;
                    UCCStatus.ucFlow_Step = 2;
                    UCCStatus.ucContract_Succeed = 1;
                    if(UCCMSG.ucCcVersion == 1)
                    {
                        ;
                    }
                    else
                    {
                        UCCMSG.ucCcVersion = (UCCMSG.szHeader[0]&0xc0)>>6;
                    }
                    UCCStatus.u1PowerRole = FALSE;
                    Chip_Request_Fix(UCCMSG.szRcvDate,0x01,UCCMSG.szRequest_Buffer,UCCMSG.ucCcVersion);//unchunked
                    UCCMSG.pDataOrder = UCCMSG.szRequest_Buffer; //UFP_SINK 1
                    Chip_Send_MessageUcc();
                    UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Data_Msg,Request,StrVdm);
                    break;
                case Request :
                    #if TYPEC_FRSWAP_EN  == ENABLED
                    BKD0_1B_REG &= BIT1_0;//int clear
                    BKD0_15_REG |= BIT1_1;//int enable	
                    UCCStatus.ucFlow_Step = 4;
                    if(UCCMSG.ucCcVersion == 1)
                    {
                        ;
                    }
                    else
                    {
                        UCCMSG.ucCcVersion = (UCCMSG.szHeader[0]&0xc0)>>6;
                    }
                    if(UCCMSG.ucCcVersion >= 0x02)
                    {
                        DRV_RpCur_Sel(UCC,Rp_SinkTxOK);
                    }
                    else
                    {
                        DRV_RpCur_Sel(UCC,Rp_SinkTxNG);
                    }
                    UCCStatus.u1PowerRole = TRUE; 							                           
                    #endif
                    #if PD_PPS_EN == ENABLED
                    if(((Chip_Ucc_RequestCal() == 1)&&(UCCMSG.ucCcVersion < 2))||(Chip_Request_Compare() == 0))//PD2.0 request PPS,reject
                    {
                        UCCMSG.pDataOrder = szCC_CtrlMsg[3];
                        Chip_Send_MessageUcc();//DFP_SOURCE 2//UFP_SINK 5
                        UCCMSG.ucLastMsgType = 0xff; //Accept time must less than 15ms
                    }
                    else
                    {                               
                        UCCMSG.pDataOrder = szCC_CtrlMsg[2];
                        Chip_Send_MessageUcc();//DFP_SOURCE 2//UFP_SINK 5
                        UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,Accept,StrVdm);
                    }	
                    #else
                    Chip_Ucc_RequestCal(); //request DCC For the Power cal
                    UCCMSG.pDataOrder = szCC_CtrlMsg[2];
                    Chip_Send_MessageUcc();//DFP_SOURCE 2//UFP_SINK 5
                    UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,Accept,StrVdm);
                    #endif
                    break;
                case BIST					:                           
                    if(UCCMSG.szRcvDate[3]== 0x50)//TDA.2.1.1.1
                    {
                        StructAmsType.ucBist_Ams = 0;
                        BKD0_97_REG |= 0x80;
                        BKD0_9A_REG =  0x43;	 
                        BKD0_99_REG =  0x09;
                        KNL_Delay1ms(40);
                        BKD0_97_REG &= 0x7F;	
                    }
                    else //TEST.PD.PHY.PORT.1
                    {
                        StructAmsType.ucBist_Ams = 1;
                    }
                    break;
                case Sink_Capabilities  	:					  								
                    break; 
                case Battery_Status     	:					  								
                    break; 
                case Alert     				:											  													
                case Get_Country_Info   	:	
                    UCCMSG.pDataOrder = szCC_CtrlMsg[6];//not support
                    Chip_Send_MessageUcc();	
                    UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,Not_Support,StrVdm);
                    break; 
                case Vendor_Defined :							
                    UCCMSG.u1Vdm_Msg = 1;
                    Chip_UFP_VdmMsg(ucMsg_Type);   //xxxmsg = Vendor Defined Msg
                    break;
                default :
                    break;
            }
        }
    }
    else
    {
        switch (ucMsg_Type)
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
                UCCMSG.pDataOrder = szCC_CtrlMsg[6];//not support msg
                Chip_Send_MessageUcc();
                UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Ctrl_Msg,Not_Support,StrVdm);
                break;
            default                 : 
                Chip_ChunkMessage_Handle();
                break;
        }	
    }
}

void Chip_Adapter_SourceCal(u8 ucDataLength) //SOURCE CAP FOR THE SOURCE
{
    u8 Adtmp;
	u8 AdapterTmpLenth= 0;
    u8 loop_Adatper;
    u16 Adapter_Cur_Cap = 0x00;
    u16 Adapter_Vol_Cap = 0x00;
	u32 Adapter_Wat_Cap = 0x00;
	#if PD_PPS_EN == ENABLED
	u8 Loop_PPS_Cnt;
	u8 PPS_Max_Vol = 0;
	u8 PPS_Max_Cur = 0;
	u16 PPS_Wat_Cap = 0;
	Loop_PPS_Cnt = 0;
	memset(DCCMSG.szPPS_Object,0x00,6);
	#endif
	UCCMSG.szPDP_Value[0] = 0x07;
	UCCMSG.szPDP_Value[1] = 0x07;
	AdapterTmpLenth	= ucDataLength + 2;
    for(Adtmp = 0; Adtmp < AdapterTmpLenth; Adtmp++)
    {
		if(Adtmp == 0)
		{
			DCCMSG.szAdapterTmp[0] = DCCMSG.szHeader[0];
		}
		else if(Adtmp == 1)
		{
			DCCMSG.szAdapterTmp[1] = DCCMSG.szHeader[1];
		}
		else
		{
			DCCMSG.szAdapterTmp[Adtmp]= DCCMSG.szRcvDate[Adtmp-2];
		}
    }
    DCCMSG.szAdapterTmp[0] &= 0x0F;
    DCCMSG.szAdapterTmp[0] |= 0x40;
	memcpy(DCCMSG.szAdapterCap_Ori,DCCMSG.szAdapterTmp,30);
	#if PD_PPS_EN == ENABLED
	memcpy(DCCMSG.szAdapterCap_For_PD30,DCCMSG.szAdapterTmp,30);
	#endif
	for(Adtmp = 2; Adtmp < AdapterTmpLenth ; Adtmp += 4)
	{
		if((DCCMSG.szAdapterTmp[Adtmp+3]&0xc0) == 0xc0) //PPS Package
		{		
			for(loop_Adatper = Adtmp ; (loop_Adatper + 4) < AdapterTmpLenth; loop_Adatper++)
			{
				DCCMSG.szAdapterTmp[loop_Adatper] = DCCMSG.szAdapterTmp[loop_Adatper + 4];
			}
			DCCMSG.szAdapterTmp[1] -= 0x10;
			#if PD_PPS_EN == ENABLED
			if(DCCMSG.szAdapterCap_For_PD30[Adtmp] > 8)//reduce 400mA
			{
				DCCMSG.szAdapterCap_For_PD30[Adtmp] -= 8;
			}
			else
			{
				;
			}
			PPS_Max_Cur = DCCMSG.szAdapterCap_For_PD30[Adtmp]; //[0-6]:Cur;[8-15]:min Vol;[17-24]:max vol;
			PPS_Max_Vol = DCCMSG.szAdapterCap_For_PD30[Adtmp+3];
			PPS_Max_Vol <<= 7;
			PPS_Max_Vol = PPS_Max_Vol|(DCCMSG.szAdapterCap_For_PD30[Adtmp+2]>>1);
			PPS_Wat_Cap = (u16)(PPS_Max_Vol)*(PPS_Max_Cur);
			PPS_Wat_Cap = PPS_Wat_Cap / 200;
			if(UCCMSG.szPDP_Value[1] > PPS_Wat_Cap)
			{
				;
			}
			else
			{
				UCCMSG.szPDP_Value[1] = PPS_Wat_Cap;
			}
			DCCMSG.szPPS_Object[Loop_PPS_Cnt] = (Adtmp>>2) + 1;
			Loop_PPS_Cnt++;
			#else
			AdapterTmpLenth -= 4;
			(Adtmp == 2)?(Adtmp = 0xfe):(Adtmp -= 4);
			#endif
		}
		else   //FIXED SUPPLY
		{
			Adapter_Cur_Cap	= ((u16)(DCCMSG.szAdapterTmp[Adtmp+1]&0x03)<<8) + DCCMSG.szAdapterTmp[Adtmp] ;
			Adapter_Vol_Cap = ((u16)(DCCMSG.szAdapterTmp[Adtmp+2]&0x0f)<<6) + ((DCCMSG.szAdapterTmp[Adtmp+1]&0xfc)>>2);	
			Adapter_Wat_Cap = (u32)(Adapter_Vol_Cap)*(Adapter_Cur_Cap);
			Adapter_Wat_Cap -= 16000;                                 // 8W in 0.5mW each divide
			Adapter_Cur_Cap = (Adapter_Wat_Cap/Adapter_Vol_Cap);
			
			DCCMSG.szAdapterTmp[Adtmp] = Adapter_Cur_Cap;
			DCCMSG.szAdapterTmp[Adtmp+1] &= 0xfc;
			DCCMSG.szAdapterTmp[Adtmp+1] |= ((Adapter_Cur_Cap>>8)&0x03);
			DCCMSG.szAdapterTmp[5] = ((DCCMSG.szAdapterTmp[5]&BIT3_1)|0x3e);//Externally Powered	
			DCCMSG.szAdapterTmp[5] &= 0xfe;                               //Unchunked Extended Messages Not Supported
			#if PD_PPS_EN == ENABLED
			DCCMSG.szAdapterCap_For_PD30[Adtmp] = DCCMSG.szAdapterTmp[Adtmp];
			DCCMSG.szAdapterCap_For_PD30[Adtmp+1] = DCCMSG.szAdapterTmp[Adtmp+1];
			DCCMSG.szAdapterCap_For_PD30[5] = DCCMSG.szAdapterTmp[5];//Externally Powered	
			DCCMSG.szAdapterCap_For_PD30[5] &= 0xfe;//Unchunked Extended Messages Not Supported
			Adapter_Wat_Cap = (Adapter_Wat_Cap/2000);
			if(UCCMSG.szPDP_Value[0] > Adapter_Wat_Cap)
			{
				;
			}
			else
			{
				UCCMSG.szPDP_Value[0] = Adapter_Wat_Cap;
			}
            #endif
		}
	}
	#if PD_PPS_EN == ENABLED
	if(UCCMSG.szPDP_Value[0] >= UCCMSG.szPDP_Value[1])
	{
		;
	}
	else
	{
		UCCMSG.szPDP_Value[0] = UCCMSG.szPDP_Value[1];
	}
	#endif
}

void Chip_Send_MessageDcc(void)
{
    u8 ucSendData;
    u8 ucSendMegSndDataOffset;
    static u8 ucDccTotalData;
    static u8 ucMessage_ID_Send = 0x00;
    DCCMSG.pBuffer_Order = DCCMSG.pDataOrder;
    ucDccTotalData = ((DCCMSG.pDataOrder[1] & 0x70)>>2) + 2;
    for(ucSendMegSndDataOffset=0; ucSendMegSndDataOffset<ucDccTotalData; ucSendMegSndDataOffset++)
    {
        ucSendData = *DCCMSG.pDataOrder;
        DCCMSG.pDataOrder++;
        if(ucSendMegSndDataOffset < 10)
        {
            if(ucSendMegSndDataOffset == 1)
            {		
                ucSendData &=0xF0;
                if(DCCStatus.u1Msg_ID_Change == TRUE)
                {
                    ucMessage_ID_Send = DCCMSG.ucMessageID;
                    DCCMSG.ucMessageID = Chip_Sum_Cal(DCCMSG.ucMessageID);	
                }
                else
                {
                    ;
                }
                ucSendData=(ucSendData|ucMessage_ID_Send);
                (DCCStatus.u1PowerRole)?(ucSendData |= BIT0_1):(ucSendData &= BIT0_0);
            }
            else if(ucSendMegSndDataOffset == 0)
            {
                ucSendData &= 0x1F;       //ufp pd2.0
                #if PD_PPS_EN == ENABLED
                if(DCCMSG.ucCcVersion < 0x02)
                {
                    ucSendData |=  BIT6_1;
                }
                else
                {
                    ucSendData |=  BIT7_1;
                }
                #else
                ucSendData |= BIT6_1;
                #endif
                (DCCStatus.u1DataRole)?(ucSendData|= BIT5_1):(ucSendData &= BIT5_0);
            }
        }
        else if(ucSendMegSndDataOffset==10)
        {        
            BKD0_19_REG = 0x09; 
        }
        BKD0_1A_REG	= ucSendData;      
    }
    if(ucSendMegSndDataOffset > 10)
    {
        ;
    }
    else
    {
        BKD0_19_REG = 0x09; 
    }
    BKD0_23_REG =  0x01; //clr rx fifo
    BKD0_18_REG |= BIT3_1;	  //mark all data done
    BKD0_18_REG &= BIT3_0;	
    Chip_CCMessage_Resend(DCC);	
}

void Chip_DFP_VdmMsg(void)
{
    switch(DCCMSG.szRcvDate[0]&0x1F)  //Command
    {
        case Discover_Identity :
            Chip_Discover_Handle(DCCMSG.ucCcVersion,DCCMSG.szRcvDate,ACK);
            DCCMSG.pDataOrder = szCC_DiscoverIDMsg;
            Chip_Send_MessageDcc();
            break;
        case Discover_SVIDs :
            DCCMSG.pDataOrder = szCC_DataMsg[2];
            Chip_Send_MessageDcc();
            break;
        default :
            break;
    }
}

void CHIP_DFP_Message(u8 ucMsg_Type,u8 ucLength,u8 ucExt)  //DFP message
{
    if(ucExt == 0x00)//Not Extended message
    {
        if(ucLength == 0x00)   //Control Message
        {
            switch(ucMsg_Type)
            {
                case GoodCRC      	:
                        break;
                case PS_RDY         :
                    if((CHIP_DccOn_Det(SINK) == TRUE)&&(UCCStatus.ucPRSended == 0)&&(UCCStatus.u1PowerRole == FALSE))//DCC IS IN
                    {
                        if(Chip_UccOff_Det() == FALSE)
                        {
                            UCCStatus.ucPRSended = 1;
                        }
                    }
                    if((!UCCStatus.u1PsRdy_Send)&&(UCCStatus.u1PrDone)) //DFP_SOURCE 4 UFP_SINK 7
                    {
                        if(UCCStatus.u1DataRole)
                        {
                            if((UCCStatus.ucSwap_Sent&Vconn_Sent) == 0)
                            {
                                UCCStatus.u1VconnSwap_En=1;
                            }
                            else if((UCCStatus.ucSwap_Sent & DR_Sent)== 0)
                            {
                                UCCStatus.ucDrSwap_En = 1;
                            }
                        }
                        UCCStatus.u1PsRdy_Send = TRUE;
                        TH2 = 0xD0;//4ms
                        TL2 = 0x00;
                        TR2 = 1;    //enable Time0
                    }
                    break;
                case PR_Swap        :
                    break;
                case DR_Swap        :
                    break;
                case Get_Sink_Cap   :
                    DCCMSG.pDataOrder = szCC_DataMsg[13];
                    Chip_Send_MessageDcc();
                    break;
                case Soft_Reset     :
                    DCCMSG.ucMessageID = 0;
                    DCCMSG.pDataOrder = szCC_CtrlMsg[2];
                    Chip_Send_MessageDcc();
                    break;
                default         :
                    break;
            }
        }
        else//Data Message
        {
            switch (ucMsg_Type)
            {
                case Source_Capabilities   :
                    #if PD_PPS_EN == ENABLED
                    DCCMSG.ucCcVersion = (DCCMSG.szHeader[0]&0xc0)>>6;
                    #endif
                    DCCStatus.u1AdapterWithPD = TRUE; //20210804
                    Chip_Adapter_SourceCal(ucLength);
                    Chip_Request_Fix(DCCMSG.szRcvDate,0x00,DCCMSG.szRequest_Buffer,DCCMSG.ucCcVersion);
                    DCCMSG.pDataOrder = DCCMSG.szRequest_Buffer; //send Request
                    Chip_Send_MessageDcc();
                    UCCMSG.ucLastMsgType = CHIP_MsgType_Cal(Data_Msg,Request,StrVdm);
                    break;
                case Request               :
                    #if PD_PPS_EN == ENABLED
                    DCCMSG.ucCcVersion = (DCCMSG.szHeader[0]&0xc0)>>6;
                    #endif
                break;
                case Vendor_Defined        :
                    Chip_DFP_VdmMsg();
                    break;
                default                    :
                    break;
            }
        }
    }
}

#endif