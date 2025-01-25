
#ifndef 	_OCMUART0_H
#define 	_OCMUART0_H


extern bit BIT_TMP;

extern void Ocm_UART0_Timer1Init(u32 ulBaudrate) ;
extern void Ocm_PrintLevel_Set(u8 ucLvl);
extern void LTLog(u8 ucLvl, const char* fmt, ...);

#endif




