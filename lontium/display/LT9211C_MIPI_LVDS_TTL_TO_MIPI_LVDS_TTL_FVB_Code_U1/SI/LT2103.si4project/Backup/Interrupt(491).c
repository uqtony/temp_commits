//////////////////////////////////////
//Project:   LT2101
//Filename:  Interrupt.c
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#include "Include.h"

void CHIP_IT0InterruptService(void) interrupt 0
{
    if(BKE6_70_REG & BIT0_1)  //auxrx_int flag
    {
        BKE6_60_REG |= BIT0_1; //bit0 clear interrupt 0
        BKE6_60_REG &= BIT0_0; //bit0 release interrupt 0
        CHIP_Interrupt_Aux_Task();
    }
    #if DPRX_HDCP_DEC_MODE != NO_HDCP
    if(BKE6_70_REG & BIT1_1)//dp hdcp1.3 rx int
    {
        BKE6_60_REG |= BIT1_1;//[1]dp rx int clr en
        BKE6_60_REG &= BIT1_0;//[1]dp rx int clr dis
        if(BKDB_DC_REG & 0x06)//[2]dprx hdcp13 v ready, [1]dprx hdcp13 link intergrity check failure
        {
            g_stDpRx.u1HdcpDecIrqEvt = HPD_IRQ_EVENT;
        }
    }
    if(BKE6_71_REG & BIT6_1)//dprx hdcp22 interrupt flag
    {
        BKE6_61_REG |= BIT6_1;//[6]hdcp rx int clr en
        BKE6_61_REG &= BIT6_0;//[6]hdcp rx int clr dis
        if (BKC5_B4_REG & 0xf0)//[7:4]link fail/ekhkm ready/H ready/V ready flag
        {
            g_stDpRx.u1HdcpDecIrqEvt = HPD_IRQ_EVENT;
        }
    }
    #endif    
}

void CHIP_IT1InterruptService(void) interrupt 2
{
    #if TYPECRX_EN == ENABLED
    if(BKE6_71_REG & BIT0_1)  //ucc1 int
    {
        BKE6_61_REG |= BIT0_1; //bit0 clear interrupt 0
        BKE6_61_REG &= BIT0_0; //bit0 release interrupt 0
        EA = 0;
        CHIP_Ucc_Interrupt();
        EA = 1;
    }
    if(BKE6_71_REG & BIT1_1)  //dcc1 int
    {
        BKE6_61_REG |= BIT1_1; //bit0 clear interrupt 0
        BKE6_61_REG &= BIT1_0; //bit0 release interrupt 0
        EA = 0;
        CHIP_Dcc_Interrupt();
        EA = 1;
    }
    #endif
}

void CHIP_IT2InterruptService(void) interrupt 8 /////
{	
	EXIF = 0x00;//soft clear the ex2
}

#if ET_2 == ENABLED
void Time2InterruptService(void) interrupt 5// 0.25us per count,can be set by register
{
	TF2 = 0;
	TR2 = 0;
	#if TYPECRX_EN == ENABLED
	if(UCCStatus.u1PsRdy_Send)//PS_RDY send
	{
		CHIP_PsRdy_Send();
	}
	else //Message resend
	{      
		CHIP_Ucc_Retry();
		ChIP_Dcc_Retry();
	}
	#endif
}
#endif