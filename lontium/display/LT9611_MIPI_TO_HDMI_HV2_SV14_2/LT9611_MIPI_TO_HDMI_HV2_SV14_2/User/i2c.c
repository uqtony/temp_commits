#include "include.h"

bool   ack;
u8     I2CADR = 0x76; 

#define I2C_SCL P13
#define I2C_SDA P14

#define 	SCL_H 	I2C_SCL=1
#define 	SCL_L 	I2C_SCL=0

#define 	SDA_H 	I2C_SDA=1
#define 	SDA_L 	I2C_SDA=0 

#define I2C_SDA_READ  I2C_SDA





static void I2C_Delay_us(u8 uscount)
{
	  u8 x;
	  for(x=0; x<uscount; x++)
	  {
		    ;
	  }		
}

static void Start_I2c(void)
{
	SDA_H;   
	I2C_Delay_us(1);
	SCL_H;
	I2C_Delay_us(10); 
	SDA_L;   	
	I2C_Delay_us(7);        
	SCL_L;   
	I2C_Delay_us(1);
}

static void Stop_I2c(void)
{
	SDA_L;    
	I2C_Delay_us(2);
	SCL_H; 
	I2C_Delay_us(10);
	SDA_H;  
	I2C_Delay_us(10);
}


static void  I2C_SendByte(u8 c)
{
	u8 bit_Cnt;

	for(bit_Cnt=0; bit_Cnt<8; bit_Cnt++) 
	{
		if((c<<bit_Cnt) & 0x80)
		{
			SDA_H;   
		}
		else
		{ 
			SDA_L;                
		}
		I2C_Delay_us(3);
		SCL_H;             
		I2C_Delay_us(4);         
		SCL_L; 
	}

	I2C_Delay_us(1);
	SDA_H;              
	I2C_Delay_us(3);  
	SCL_H;
	I2C_Delay_us(3);

	if(I2C_SDA_READ != 0)
	{ 
		ack=0;
	}	 
	else
	{
		ack=1;
	}	 
	SCL_L;
	I2C_Delay_us(3);
}
	
static u8  RcvByte(void)
{
	u8 retc;
	u8 bit_Cnt;

	retc=0; 
	SDA_H;             	
	for (bit_Cnt=0; bit_Cnt<8; bit_Cnt++)
	{
		I2C_Delay_us(1);          
		SCL_L;                  
		I2C_Delay_us(4);
		SCL_H;            
		I2C_Delay_us(2);
		retc=retc<<1;
		if (I2C_SDA_READ != 0)
		{
			retc = retc+1;
		}					
		I2C_Delay_us(2);
	}
	SCL_L;    
	I2C_Delay_us(5);
	return   retc;
}

static void Ack_I2c(bool a)
{
	if (a == 0)
	{
		SDA_L;
	}		 
	else
	{ 
		SDA_H;
	}	 

	I2C_Delay_us(8);     
	SCL_H;
	I2C_Delay_us(15);  
	SCL_L;                 
	I2C_Delay_us(8);   
}

static bool i2c_write_byte(u8 sla,u8 suba,u8 *s,u8 no)
{
	u8 i;

	Start_I2c();  
	
	I2C_SendByte(sla);  
	
	if(ack==0)
	{
		Stop_I2c();
		return  FALSE;
	}
	I2C_SendByte(suba);            
	if(ack == 0)
	{
		Stop_I2c();
		return FALSE;
	}

	for(i=0;i<no;i++)
	{   
		I2C_SendByte(*s);          
		if(ack == 0)
		{
			Stop_I2c();
			return  FALSE;
		}
		s++;
	} 
	Stop_I2c();             
	return TRUE;
}

static bool i2c_read_byte(u8 sla,u8 suba,u8 *s,u8 no)
{
	u8 i;
	Start_I2c();                 
	I2C_SendByte(sla);              
	if(ack==0)
	{
		Stop_I2c();
		*s = 0x00;
		return FALSE;
	}
	I2C_SendByte(suba);             
	if (ack == 0)
	{
		Stop_I2c();
		*s = 0x00;
		return  FALSE;
	}
	Start_I2c();			
	I2C_SendByte(sla+1);
	if (ack == 0)
	{
		Stop_I2c();
		*s = 0x00;
		return  FALSE;
	}
	for (i=0; i<no-1; i++)
	{   
		*s= RcvByte();              
		Ack_I2c(0);               
		s++;
	} 
	*s = RcvByte();
	Ack_I2c(1);                 
	Stop_I2c();                 
	return  TRUE;
}

u8 HDMI_ReadI2C_Byte(u8 RegAddr)
{
	u8  p_data=0;
	
	if (i2c_read_byte(I2CADR, RegAddr, &p_data,1) != FALSE)
	{
		return p_data;
	}
	return 0;
}

bool HDMI_ReadI2C_ByteN(u8 RegAddr,u8 *p_data,u8 N)
{
	bool flag;
	
	flag = i2c_read_byte(I2CADR, RegAddr, p_data,N);
	
	return flag;
}

bool HDMI_WriteI2C_Byte(u8 RegAddr, u8 d)
{
	bool flag;
	
	flag=i2c_write_byte(I2CADR, RegAddr,&d,1);
	
	//printf("\r\nlt9611_write(pdata, 0x%02bx, 0x%02bx);", RegAddr,d);
	return flag;
}

bool HDMI_WriteI2C_ByteN(u8 RegAddr, u8 *d,u8 N)
{
	bool flag;
	
	flag=i2c_write_byte(I2CADR, RegAddr,d,N) ;
	
	return flag;
}


//void I2cMasterChoice(u8 i2cchannnel)
//{
//	switch(i2cchannnel)
//	{
//		case LT8631UXConfig:
//			
//			I2CADR = LT8631UX_ADDR; 
//			
//			break;
//			
//		default:
//			break;
//	}
//}
