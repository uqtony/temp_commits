#include	"include.h"

#ifndef		_I2C_MASTER_H
#define		_I2C_MASTER_H

extern u8 I2CADR;
extern u8 HDMI_ReadI2C_Byte(u8 RegAddr);
extern bool HDMI_ReadI2C_ByteN(u8 RegAddr,u8 *p_data,u8 N);
extern bool HDMI_WriteI2C_Byte(u8 RegAddr, u8 d);
extern bool HDMI_WriteI2C_ByteN(u8 RegAddr, u8 *d,u8 N);
extern void I2cMasterChoice(u8 i2cchannnel);


#endif