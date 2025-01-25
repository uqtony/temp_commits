
#include "include.h"


//----------------------------------------------------------------------------------
// UART0 baud rate initial setting 
//----------------------------------------------------------------------------------
void InitialUART0_Timer1(UINT32 u32Baudrate)    //T1M = 1, SMOD = 1
{
	P06_Quasi_Mode;		//Setting UART pin as Quasi mode for transmit
	P07_Quasi_Mode;		//Setting UART pin as Quasi mode for transmit
	
    SCON = 0x50;     	//UART0 Mode1,REN=1,TI=1
    TMOD |= 0x20;    	//Timer1 Mode1
    
    set_SMOD;        	//UART0 Double Rate Enable
    set_T1M;
    clr_BRCK;        	//Serial port 0 baud rate clock source = Timer1
 
#ifdef FOSC_160000
    TH1 = 256 - (1000000/u32Baudrate+1);               /*16 MHz */
#endif    	
#ifdef FOSC_166000
    TH1 = 256 - (1037500/u32Baudrate);         		     /*16.6 MHz */
#endif
    set_TR1;
	  set_TI;						//For printf function must setting TI = 1
}
//---------------------------------------------------------------

#if 0
void InitialUART0_Timer3(UINT32 u32Baudrate) //use timer3 as Baudrate generator
{
	P06_Quasi_Mode;		//Setting UART pin as Quasi mode for transmit
	P07_Quasi_Mode;		//Setting UART pin as Quasi mode for transmit	
	
    SCON = 0x50;     //UART0 Mode1,REN=1,TI=1
    set_SMOD;        //UART0 Double Rate Enable
    T3CON &= 0xF8;   //T3PS2=0,T3PS1=0,T3PS0=0(Prescale=1)
    set_BRCK;        //UART0 baud rate clock source = Timer3

#ifdef FOSC_160000
	RH3    = HIBYTE(65536 - (1000000/u32Baudrate)-1);  		/*16 MHz */
	RL3    = LOBYTE(65536 - (1000000/u32Baudrate)-1);			/*16 MHz */
#endif
#ifdef FOSC_166000
    RH3    = HIBYTE(65536 - (1037500/u32Baudrate)); 			/*16.6 MHz */
    RL3    = LOBYTE(65536 - (1037500/u32Baudrate)); 			/*16.6 MHz */
#endif
    set_TR3;         //Trigger Timer3
	set_TI;					 //For printf function must setting TI = 1
}
#endif

//UINT8 Receive_Data_From_UART0(void)
//{
//    UINT8 c;
//    while (!RI);
//    c = SBUF;
//    RI = 0;
//    return (c);
//}

void Send_Data_To_UART0 (UINT8 c)
{
    TI = 0;
    SBUF = c;
    while(TI==0);
}
 

//void printByte(u8 UData)
//{
//  u8 reg_H,reg_L;
//  reg_L=UData&0x0f;
//  reg_H=(UData&0xf0)>>4;
// 
//  reg_L = (reg_L<0x0a) ? (reg_L+0x30):(reg_L+0x37);   //map reg_L to asicc 'a' to a (0x41),   a = 0x37 + 0x0a = 0x41
//  reg_H = (reg_H<0x0a) ? (reg_H+0x30):(reg_H+0x37);	
//  Send_Data_To_UART0(reg_H);
//  Send_Data_To_UART0(reg_L);	
//  Send_Data_To_UART0(0x20); //space	
//}

//void printnewline(void)
//{
//	Send_Data_To_UART0(0x0a);   //huanhang
//}


//void Debug_printf(unsigned char *str)
//{ 
//#ifdef _uart_debug_
//	printf(str);	
//#endif
//}

//void printWord(u16 U16Data)
//{
//	printByte((U16Data&0xFF00)>>8);
//	printByte((U16Data&0x00FF));
//	Send_Data_To_UART0(0x0a);   //???
//}


//void printByteWithSpace(u8 U8Data)
//{
//	Send_Data_To_UART0(U8Data);
//	Send_Data_To_UART0(0x20);   //space
//     //0x3c |,  0x3e ~
//}
/*
出厂前，每颗 N76E003都会预烧一个96位的序列号
，用以确保该芯片的唯一性，这个唯一代码被称为
序列号UID (Unique Code)。用户获得序列号的唯
一方式是通过 IAP指令读取，
*/
//UINT8 UID_BYTE(UINT8 Addr)
//{
//	UINT8 DATATEMP;
//	set_IAPEN;
//	IAPAL = Addr;
//  	IAPAH = 0x00;
//  	IAPCN = READ_UID;
//  	set_IAPGO;
//	DATATEMP = IAPFD;
//	clr_IAPEN;
//	return DATATEMP;
//}

//void READ_MCU_UID(void)
//{
//	UINT8 READ1,READ2;
//
//	READ1 = UID_BYTE(0x02);
//	READ2 = UID_BYTE(0x05);
//
//	printf ("\n UID1 = 0x%bx",READ1);
//	printf ("\n UID2 = 0x%bx",READ2);
//}



void printch(char ch)
{
	 Send_Data_To_UART0(ch);
}

