
#ifndef 	_UART0_H
#define 	_UART0_H

void  InitialUART0_Timer1(UINT32 u32Baudrate); //T1M = 1, SMOD = 1
//void  InitialUART0_Timer3(UINT32 u32Baudrate); //Timer3 as Baudrate, SMOD=1, Prescale=0
//void  Send_Data_To_UART0(UINT8 c);
//UINT8 Receive_Data_From_UART0(void);
//
//UINT8 UID_BYTE(UINT8 Addr);
//void READ_MCU_UID(void);
//void Debug_printf(unsigned char *str);
//void printByte(u8 U8Data);
//void printByteWithSpace(u8 U8Data);
//void printWord(u16 U16Data);

extern void printdec_u32(u32 u32_dec);
extern void print(char* fmt, ...);

#endif




