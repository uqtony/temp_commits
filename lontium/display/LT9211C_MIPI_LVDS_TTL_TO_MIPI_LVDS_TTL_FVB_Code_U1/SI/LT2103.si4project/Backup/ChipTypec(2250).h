//////////////////////////////////////
//Project:   LT2101
//Filename:  I2CMast.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _CHIPTYPEC_H
#define _CHIPTYPEC_H
#include "LtType.h"

//CC INT
#define   Init 						0x00
#define   ACK 						0x40
#define   NACK						0x80
#define   BUSY						0xC0

#define   SOP 						0x01
#define   SOP1 						0x02
#define   SOP2						0x03
#define   HardRst					0x04
#define   Cable_Rst					0x05
#define   SOP1_Debug				0x06
#define   SOP2_Debug				0x07

#define   DP_ALT_MODE_LBYTE         0x01
#define   DP_ALT_MODE_HBYTE         0xFF
#define   Samsung_LByte		        0xe8
#define   Samsung_HByte       		0x04
#define   Switch_LByte		        0x7e
#define   Switch_HByte       		0x05
#define   APPLE_ADAPTER_LBYTE       0xAC
#define   APPLE_ADAPTER_HBYTE       0x05


//Control Msg Type
#define   GoodCRC     		        0x01
#define   GotoMin     		        0x02
#define   Accept     		        0x03
#define   Reject      		        0x04
#define   Ping        		        0x05
#define   PS_RDY      		        0x06
#define   Get_Source_Cap            0x07
#define   Get_Sink_Cap              0x08
#define   DR_Swap                   0x09
#define   PR_Swap                   0x0A
#define   VCONN_Swap                0x0B
#define   Wait                      0x0C
#define   Soft_Reset                0x0D
#define	  Not_Support				 0x10
#define	  Get_Source_Cap_Extended	 0x11
#define	  Get_Status				 0x12
#define	  FR_Swap					 0x13
#define	  Get_PPS_Status		 	 0x14
#define	  Get_Country_Codes	 		 0x15


//Data Msg Type
#define   Source_Capabilities     	0x01
#define   Request     		        0x02
#define   BIST     		            0x03
#define   Sink_Capabilities      	0x04
#define   Battery_Status	      	0x05
#define   Alert				      	0x06
#define   Get_Country_Info	        0x07
#define   Vendor_Defined        	0x0f

//*****Extended Msg Type******//
#define   Source_Cap_Extended     	0x01
#define   Status    		        0x02
#define   Get_Battery_Cap	        0x03
#define   Get_Battery_Status      	0x04
#define   Battery_Capabilities     	0x05
#define   Get_Manufacturer_Info   	0x06
#define   Manufacturer_Info	      	0x07
#define   Security_Request        	0x08
#define   Security_Response        	0x09
#define   Firmware_Update_Request  	0x0a
#define   Firmware_Update_Response	0x0b
#define   PPS_Status	        	0x0c
#define   Country_Info	        	0x0d
#define   Country_Codes	        	0x0e

//SVDM
#define   Discover_Identity     	0x01
#define   Discover_SVIDs     	    0x02
#define   Discover_Modes     		0x03
#define   Enter_Mode      	        0x04
#define   Exit_Mode      	        0x05
#define   Attention        	        0x06
#define   DP_Status_Update        	0x10 //16
#define   DP_Config              	0x11 //17

#define   Ctrl_Msg					0x00
#define   Data_Msg					0x01
#define   Ext_Msg					0x02
#define   Vdm_Msg					0x03

#define   StrVdm					0x80
#define   UnStrVdm					0x00

#define   PDREQ						0x00
#define   PDACK						0x01
#define   PDNACK					0x02
#define   PDBUSY					0x03

#define   Vconn_Sent				0x01
#define   Vconn_No_Sent				0xf0
#define   DR_No_Sent				0x0f
#define   DR_Sent_Accept			0x10
#define   DR_Sent_Reject			0x20
#define   DR_Sent					0x30

typedef struct AmsStatus
{
	u8 ucPower_Ams;
	u8 ucGotoMin_Ams;
	u8 ucSoftReset_Ams;
	u8 ucHardReset_Ams;
	u8 ucCableReset_Ams;
	u8 ucGetSrcCap_Ams;
	u8 ucGetSnkCap_Ams;
	u8 ucPrSwap_Ams;
	u8 ucFrSwap_Ams;
	u8 ucDrSwap_Ams;
	u8 ucVconnSwap_Ams;
	u8 ucSrcAlert_Ams;
	u8 ucGetSrcExtCap_Ams;
	u8 ucGetStatus_Ams;
	u8 ucGetBattCap_Ams;
	u8 ucGetBattStatus_Ams;
	u8 ucGetManuInfo_Ams;
	u8 ucSecurity_Ams;
	u8 ucFwUpdate_Ams;
	u8 ucDiscoverID_Ams;
	u8 ucSrcStartup_Ams;
	u8 ucDiscoverSvids_Ams;
	u8 ucDiscoverModes_Ams;
	u8 ucDToUEnterMode_Ams;
	u8 ucDToUExitMode_Ams;
	u8 ucDToCEnterMode_Ams;
	u8 ucDToCExitMode_Ams;
	u8 ucAttention_Ams;
	u8 ucBist_Ams;
} StructAms;

typedef struct TypecStatus
{
	u8 u1PowerRole :1;
	u8 u1DataRole :1;
    u8 u1VconnSwap_En:1;
    u8 u1FrTriggle :1;
    u8 u1PrDone :1;
	u8 u1Multi_Function :1;
	u8 u1Charger_Scan :1;
	u8 u1AdapterWithPD :1;
    u8 u1PsRdy_Send :1;
	u8 u1Toggle_enable :1;
	u8 u1WaitMsg_Receive :1;
	u8 u1Msg_ID_Change:1;
    u8 u1IsFlip :1;
    u8 u1Flag_Source_Send :1;
    u8 u1Toggle_DFP_EN :1;
    u8 u1Hardreset_Rec :1;
    u8 u1IsCc_done :1;
    u8 u1CCDataMsg_Sent :1;
    u8 u1UCcInput_type  :1;
	u8 ucPRSended;
	u8 ucPRSwaping;
	u8 ucPRSwaped;	
	u8 ucDrSwap_En;	
	u8 ucFRSwaping;
	u8 ucContract_Succeed;
	u8 ucSwap_Sent;
	u8 ucRetryCounter;	
	u8 ucFlow_Step;
	u8 ucVDM_Step;  
    u8 ucnUccSourceCapCnt;
    u8 ucDccState_Tmp;  

    u8 ucnRetryCount;
    
} StructCcStatus;

typedef struct TypecMSG
{
	u8 u1RcvGoodCRC :1;
	u8 u1SendEN     :1;
	u8 u1ReadEN     :1;
	u8 u1Vdm_Msg    :1;
	u8 *pDataOrder;
	u8 szRcvDate[30];
	u8 szHeader[4];
	u8 szRequest_Buffer[6];
	u8 szRequestTmp[6];
	u8 szAdapterTmp[30];
    u8 szPPS_Object[6];
    u8 szPDP_Value[2];
    u8 szCC_ModeMsg_Buffer[10];
    u8 szAdapterCap_Ori[30];
    u8 szAdapterCap_For_PD30[30];
	u8 ucCcVersion;
	u8 ucMessageID_New;
	u8 ucMessageID_Tmp;
	u8 ucMsgType_Tmp;
	u8 ucLastMsgType;
	u8 ucMessageID;
	u8 *pBuffer_Order;
	u8 *pLast_DataOrder;

} StructCcMsg;

extern u8 code szCC_DataMsg[][10];
extern u8 szCC_DiscoverIDMsg[22];
extern u8 code szCC_CtrlMsg[][2];
extern u8 szCC_SourceCapExt[30];

extern StructCcStatus DCCStatus;
extern StructCcStatus UCCStatus;
extern StructCcMsg DCCMSG;
extern StructCcMsg UCCMSG;
extern StructAms StructAmsType;


extern void CHIP_Ucc_HpdIrqSend(bool IsAttentionHigh, bool IsIrqHigh);
extern bool CHIP_Ucc_ComDoneFlag(void);
extern void Typec_Var_Init(void);
extern void CHIP_CC_Loop(void);
extern u8 CHIP_MsgType_Cal(IN u8 ucCommandType,IN u8 ucMessageType,IN u8 ucVdmType);

extern u8 CHIP_DccOn_Det(IN u8 ucPow_Role);
extern u8 Chip_RpOn_Scan(void);
extern u8 Chip_UccOff_Det(void);
extern u8 CHIP_Ucc_SourceCapSend(u8 ucFlag);
extern u8 CHIP_Swap_Scan(u8 ucFlag);
extern void CHIP_Typec_VarInit(void);
extern void CHIP_Dcc_TmpIni(void);
extern void Chip_Dvbus_Lvl_Set(void);
extern void CHIP_Ucc_OffAction(void);

#endif
