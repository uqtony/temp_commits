/******************************************************************************
  * @project: LT9211C
  * @file: DrvI2cMaster.c
  * @author: sxue
  * @company: LONTIUM COPYRIGHT and CONFIDENTIAL
  * @date: 2023.01.29
/******************************************************************************/

#include "include.h"

#define  SCL_Set_High     P13=1
#define  SCL_Set_Low      P13=0

#define  SDA_Set_High     P14=1
#define  SDA_Set_Low      P14=0 

#define I2C_SDA_READ      P14

u8   ucAck;
u8   ucI2cAddr = 0x5a; 

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
    SDA_Set_High;   
    I2C_Delay_us(1);
    SCL_Set_High;
    I2C_Delay_us(10); 
    SDA_Set_Low;       
    I2C_Delay_us(7);        
    SCL_Set_Low;   
    I2C_Delay_us(1);
}

static void Stop_I2c(void)
{
    SDA_Set_Low;    
    I2C_Delay_us(2);
    SCL_Set_High; 
    I2C_Delay_us(10);
    SDA_Set_High;  
    I2C_Delay_us(10);
}

static void  I2C_SendByte(u8 c)
{
    u8 bit_Cnt;

    for(bit_Cnt=0; bit_Cnt<8; bit_Cnt++) 
    {
        if((c<<bit_Cnt) & 0x80)
        {
            SDA_Set_High;   
        }
        else
        { 
            SDA_Set_Low;                
        }
        I2C_Delay_us(3);
        SCL_Set_High;             
        I2C_Delay_us(4);         
        SCL_Set_Low; 
    }

    I2C_Delay_us(1);
    SDA_Set_High;              
    I2C_Delay_us(3);  
    SCL_Set_High;
    I2C_Delay_us(3);

    if(I2C_SDA_READ != 0)
    { 
        ucAck = 0;
    }     
    else
    {
        ucAck = 1;
    }     
    SCL_Set_Low;
    I2C_Delay_us(3);
}
    
static u8 RcvByte(void)
{
    u8 retc;
    u8 bit_Cnt;
    retc = 0; 
    SDA_Set_High;                 
    for (bit_Cnt=0; bit_Cnt<8; bit_Cnt++)
    {
        I2C_Delay_us(1);          
        SCL_Set_Low;                  
        I2C_Delay_us(4);
        SCL_Set_High;            
        I2C_Delay_us(2);
        retc=retc<<1;
        if (I2C_SDA_READ != 0)
        {
            retc = retc+1;
        }                    
        I2C_Delay_us(2);
    }
    SCL_Set_Low;    
    I2C_Delay_us(5);
    return   retc;
}

static void Ack_I2c(bool a)
{
    if (a == 0)
    {
        SDA_Set_Low;
    }         
    else
    { 
        SDA_Set_High;
    }     
    I2C_Delay_us(8);     
    SCL_Set_High;
    I2C_Delay_us(15);  
    SCL_Set_Low;                 
    I2C_Delay_us(8);   
}

static bool i2c_write_byte(u8 sla,u8 suba,u8 *s,u8 no)
{
    u8 i;
    Start_I2c();  
    I2C_SendByte(sla);  
    
    if(ucAck==0)
    {
        Stop_I2c();
        return  FALSE;
    }
    I2C_SendByte(suba);            
    if(ucAck == 0)
    {
        Stop_I2c();
        return FALSE;
    }

    for(i=0;i<no;i++)
    {   
        I2C_SendByte(*s);          
        if(ucAck == 0)
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
    if(ucAck==0)
    {
        Stop_I2c();
        *s = 0x00;
        return FALSE;
    }
    I2C_SendByte(suba);             
    if (ucAck == 0)
    {
        Stop_I2c();
        *s = 0x00;
        return  FALSE;
    }
    Start_I2c();            
    I2C_SendByte(sla+1);
    if (ucAck == 0)
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
    if (i2c_read_byte(ucI2cAddr, RegAddr, &p_data,1) != FALSE)
    {
        return p_data;
    }
    return 0;
}

bool HDMI_ReadI2C_ByteN(u8 RegAddr,u8 *p_data,u8 N)
{
    bool flag;
    flag = i2c_read_byte(ucI2cAddr, RegAddr, p_data,N);
    return flag;
}

bool HDMI_WriteI2C_Byte(u8 RegAddr, u8 d)
{
    bool flag;
    flag=i2c_write_byte(ucI2cAddr, RegAddr,&d,1);
    return flag;
}

bool HDMI_WriteI2C_ByteN(u8 RegAddr, u8 *d,u8 N)
{
    bool flag;
    flag=i2c_write_byte(ucI2cAddr, RegAddr,d,N) ;
    return flag;
}