
#include "include.h"

bool irq_task_flag = 0;

void MCU_SystemInit(void)
{
	P10_Input_Mode;
	P11_Input_Mode;
	P12_Input_Mode;
	P03_Input_Mode;    //IRQ
	P04_Input_Mode;

	P30_PushPull_Mode; //LT8911_RST_N
	P13_OpenDrain_Mode;//SCL_CTL
	P14_OpenDrain_Mode;//SDA_CTL
	
	//EA=1;
  InitialUART0_Timer1(115200);//UART_INTI

  Enable_INT_Port0;
	Enable_BIT3_FallEdge_Trig;
	set_EPI;

	//set_EX1;
	//set_IT1;
  //set_IE1;
	set_EA;
}

void LT9611_Reset(void)
{
   P30 = 0;
   Timer0_Delay1ms(200);
   P30 = 1;
   Timer0_Delay1ms(200);
}

void main(void)
{
	MCU_SystemInit();
	//Timer0_Delay1ms(3000);
	printf("\r\n==================Modified on ("__DATE__ " - " __TIME__ ")==================");
	LT9611_Reset();

	#ifdef _pattern_test_ 
	LT9611_pattern();
	#else
	LT9611_Init();
	#endif

	while(1);
}
