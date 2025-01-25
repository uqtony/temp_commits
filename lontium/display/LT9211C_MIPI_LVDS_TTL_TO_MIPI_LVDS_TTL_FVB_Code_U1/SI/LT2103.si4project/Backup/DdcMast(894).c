//////////////////////////////////////
//Project:   LT2101
//Filename:  DdcMast.c
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#include "Include.h"

u8 ucSegmentBlock;

void DRV_HdmiTx_Ddc_Init(void)
{
    BKE2_E7_REG &= 0xc3;// htx_ddc _sel hard mode
    BKC6_DD_REG =  0x08;//DDC master input select[5:4]: 00:Auto mode; 10:Register data 11:hdmi hdcp tx data
    BKC6_DE_REG =  0xC1;//
    BKC6_CB_REG =  0xD0;//
    #if SYSCLK == SYS_CLK_36M
    BKC6_DF_REG =  0x13;//Fsys_clk/(Fscl*25)-1. ddc speed
    #endif
}

void DRV_HdmiTx_WriteI2CByte(u16 usRegAddr, u8 ucValue)
{
    u8 ucDelay;
    BKC6_DD_REG |= BIT5_1;//DDC master input select Software mode
    BKC6_DE_REG |= BIT5_1;//DDC Access Control:
    BKC6_DE_REG &= BIT4_0;//DDC Access Control:

    BKC6_BA_REG = usRegAddr >>8;//addr high
    BKC6_BC_REG = usRegAddr;// addr low
    BKC6_BD_REG = 0x01;//data lenth
    BKC6_C9_REG = ucValue;//write data
    BKC6_BE_REG = 0x9a;//write command
    ucDelay = 0;
    while(((BKC6_90_REG & BIT7_1) == 0x00)&&(ucDelay < 10))
    {
        KNL_Delay1ms(1);
        ucDelay++;
    }
    BKC6_BE_REG = 0x9f;
    KNL_Delay1us(10);
    BKC6_DD_REG &= BIT5_0;// Auto mode
    BKC6_DE_REG &= BIT4_0&BIT5_0;//DDC Access Control:     
}

u8 DRV_HdmiTx_ReadI2CByteN(u8 ucSegmentAddr,u16 usRegAddr, u8 *pucValue,u8 ucNum)
{
    u8 ucVaule;
    u8 ucReadCnt;
    u8 ucDelay;
    BKC6_DD_REG |= BIT5_1;//DDC master input select Software mode
    BKC6_DE_REG |= BIT5_1;//DDC Access Control:
    BKC6_DE_REG &= BIT4_0;//DDC Access Control:
    
    #if 0 //max read lenth == 32
    for(ucReadCnt = 0;ucReadCnt < ucNum; ucReadCnt += 32)
    {
        BKC6_BA_REG = usRegAddr >>8;//addr high
        BKC6_BB_REG = (ucSegmentAddr == 0x01)?(0x01):(0x00);//segment addr
        BKC6_BC_REG = (usRegAddr&0xff) + ucReadCnt ;// addr++
        BKC6_BD_REG = (ucNum > 32)?(32):(ucNum);//
        BKC6_BE_REG = (ucSegmentAddr == 0x01)?(0x9c):(0x99);//read command
        
        if((ucSegmentAddr == 0x01)&&((ucReadCnt + 32) >= ucNum))
        {
            ucSegmentAddr = 0x00;
        }
        ucDelay = 0;
        while(((BKC6_90_REG & BIT7_1) == 0x00)&&(ucDelay < 100))
        {
            KNL_Delay1ms(1);
            ucDelay++;
        }
        if(BKC6_90_REG & BIT5_1)//no nack
        {
            ucVaule = FALSE;
            *pucValue = 0xff;
        }
        else
        {
            while((BKC6_9D_REG&0x3f) != 0)
            {
                *pucValue = BKC6_D0_REG ;
                pucValue++;
            }
            ucVaule = TRUE;
        }
        BKC6_BE_REG = 0x9f;
    }
    #else
    BKC6_D5_REG |=BIT3_1;//must clear for next read request
    BKC6_D6_REG = 0x00; // initial the addr before c6d5
    BKC6_D5_REG &=BIT3_0;//must clear for next read request
    BKC6_BA_REG = usRegAddr >>8;//addr high
    BKC6_BB_REG = (ucSegmentAddr == 0x01)?(0x01):(0x00);//segment addr
    BKC6_BC_REG = usRegAddr&0xff;// addr++
    BKC6_BD_REG = ucNum;//
    BKC6_BE_REG = (ucSegmentAddr == 0x01)?(0x9c):(0x99);//read command  
    ucSegmentAddr = 0x00;
    ucDelay = 0;
    while(((BKC6_90_REG & BIT7_1) == 0x00)&&(ucDelay < 100))
    {
        KNL_Delay1ms(1);
        ucDelay++;
    }
    if(BKC6_90_REG & BIT5_1)//no nack
    {
        ucVaule = FALSE;
        *pucValue = 0xff;
    }
    else
    {
        BKC6_D5_REG |= BIT4_1|BIT3_1;//Set to software of KSV list sram reading/Set to software of KSV list sram.
        for(ucReadCnt = 0;ucReadCnt < ucNum; ucReadCnt ++)
        {
            BKC6_D6_REG = ucReadCnt;
            *pucValue = BKC6_A0_REG ;
            pucValue++;
        }
        ucVaule = TRUE;
    }
    BKC6_BE_REG = 0x9f;
    BKC6_D6_REG = 0x00;// initial the addr before c6d5
    BKC6_D5_REG &= BIT4_0&BIT3_0;//must clear for next read request
    #endif
    KNL_Delay1us(10);
    BKC6_DD_REG &= BIT5_0;// Auto mode
    BKC6_DE_REG &= BIT4_0&BIT5_0;//DDC Access Control: 
    return ucVaule;
}

u8 DRV_HdmiTx_ReadI2CByte(u16 usRegAddr)
{
    u8 ucVaule;
    u8 ucDelay;
    BKC6_DD_REG |= BIT5_1;// DDC master input select Software mode
    BKC6_DE_REG |= BIT5_1;//DDC Access Control:
    BKC6_DE_REG &= BIT4_0;//DDC Access Control:

    BKC6_BA_REG = usRegAddr >>8;//addr high
    BKC6_BB_REG = 0x00;
    BKC6_BC_REG = usRegAddr;// addr low
    BKC6_BD_REG = 0x01;    //data lenth
    BKC6_BE_REG = 0x99;

    ucDelay = 0;
    while(((BKC6_90_REG & BIT7_1) == 0x00)&&(ucDelay < 10))
    {
        KNL_Delay1ms(1);
        ucDelay++;
    }
    if(BKC6_90_REG & BIT5_1)//no nack
    {
        ucVaule = 0xff;
    }
    else
    {
        ucVaule = BKC6_D0_REG ;
    }
    BKC6_BE_REG = 0x9f;
    KNL_Delay1us(10);
    BKC6_DD_REG &= BIT5_0;// Auto mode
    BKC6_DE_REG &= BIT4_0&BIT5_0;//DDC Access Control: 
    return ucVaule;
}