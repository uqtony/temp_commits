//////////////////////////////////////
//Project:   LT2101
//Filename:  HdmiTx.c
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#include "Include.h"

bool DRV_HdmiTx_HpdDet(void)
{
    return((BKE5_D8_REG>>6)&BIT0_1);
}

void DRV_HdmiTx_RtermCali(void)
{
    u8 ucNum,ucRterm_Cali_Cnt;
    if(BKE7_30_REG&BIT0_1)
    {
        return;
    }
    BKE2_91_REG |= BIT7_1;//hdmitx phy enable control: 1-en,  0-dis
    BKE7_36_REG = 0xa8;  //Rterm calibration value change wait time set
    ucRterm_Cali_Cnt = 0;
    do
    {
        BKE7_30_REG &= BIT0_0;//rterm calibration enable, dis
        BKE7_30_REG |= BIT0_1;//rterm calibration enable,  en
        ucNum = 0;
        while(ucNum < 10)
        {
            ucNum++;
            KNL_Delay1ms(1);
            if(BKE7_37_REG & BIT3_1)//rterm calibration done status
            {
                printLT(PRINT_PRIO_TEST, "\nHdmiTx Reterm = 0x%02bx", BKE7_38_REG);
                break;
            }
        }
        ucRterm_Cali_Cnt++;
    }while((ucRterm_Cali_Cnt < 3)&&((BKE7_38_REG > 0xc0)||(BKE7_38_REG < 0x70))); 
}

void DRV_HdmiTx_DcDet(void)
{
    BKE2_91_REG |= BIT0_1;//dc_det channel select TX1 channel
    BKE2_98_REG |= 0x0f;//phy  channel dc detect enable control 
}

void DRV_HdmiTx_PhyDis(void)
{
    BKE2_92_REG = 0x00;//phy tx0 channel enable control/ phy tx0 channel rterm enable control
    BKE2_93_REG = 0x00;//tx0 tx1 tap0/tap1 en
    BKE2_94_REG = 0x00;//tx2 tx3 tap0/tap1 en  
}

void DRV_HdmiTx_PktSendDis(void)
{
    BKD6_18_REG = 0x00;
    BKD6_19_REG = 0x00;
}

void DRV_HdmiTx_DigSet(bool ubIsHdmiMode,bool ubIsHdmi20)
{
    if(ubIsHdmiMode == TRUE)
    {
        BKD5_01_REG |= BIT2_1;//HDMI MODE
    }
    else
    {
        BKD5_01_REG &= BIT2_0;//DVI MODE
    }
    if(ubIsHdmi20 == FALSE)
    {
        BKD5_01_REG &=BIT3_0;//scramble disable
        BKD5_01_REG &=BIT4_0;//Clock channel output data pattern select
        BKD5_0C_REG = 0x01;//SSCP specified line.
    }
    else
    {
        BKD5_01_REG |=BIT3_1;//scramble eanble
        BKD5_01_REG |=BIT4_1;//Clock channel output data pattern select
        BKD5_0C_REG = 0x01;//SSCP specified line. 
    }
    BKD5_02_REG |= BIT3_1; //HDMI TX encoder date sel:
}

void DRV_HdmiTx_DeepColor(bool IsYcc422,u8 ucDeepColor) 
{
    switch(ucDeepColor)
    {
        case 10:
            BKD5_03_REG = (IsYcc422 == TRUE)?(0x55|BIT3_1):(0x55&BIT3_0);
            break;
        case 12:
            BKD5_03_REG = (IsYcc422 == TRUE)?(0x66|BIT3_1):(0x66&BIT3_0);
            break;
        default:
            BKD5_03_REG = (IsYcc422 == TRUE)?(0x44|BIT3_1):(0x44&BIT3_0);
            break;
    }  
}

void DRV_HdmiTx_PhySet( bool ubIsHdmi20)
{    
    if(ubIsHdmi20 == FALSE)
    {
        BKE2_91_REG &= BIT4_0;//div reset
        BKE2_92_REG = 0x00;
        BKE2_A0_REG = 0x50;
        BKE2_A1_REG = 0x00;//clk

        BKE2_A2_REG = 0x50;
        BKE2_A3_REG = 0x08;//d0

        BKE2_A4_REG = 0x50;
        BKE2_A5_REG = 0x08;//d1

        BKE2_A6_REG = 0x50;
        BKE2_A7_REG = 0x08;//d2

        BKE2_93_REG = 0xAA;//tx0 tx1 tap0/tap1 en
        BKE2_94_REG = 0xAA;//tx2 tx3 tap0/tap1 en
        BKE2_92_REG = 0xf0;//tx channel enable
        BKE2_91_REG |= BIT4_1;//div reset
        DRV_HdmiTx_WriteI2CByte(0xA820,0x00);
        printLT(PRINT_PRIO_TEST, "\nHdmiTx1.4 Out");
    }
    else
    {
        BKE2_91_REG &= BIT4_0;//div reset
        BKE2_92_REG = 0x00;
        BKE2_A0_REG = 0xa0;
        BKE2_A1_REG = 0x00;//clk

        BKE2_A2_REG = 0xa0;
        BKE2_A3_REG = 0x08;//d0

        BKE2_A4_REG = 0xa0;
        BKE2_A5_REG = 0x08;//d1

        BKE2_A6_REG = 0xa0;
        BKE2_A7_REG = 0x08;//d2
        
        BKE2_93_REG = 0xAA;//tx0 tx1 tap0/tap1 en
        BKE2_94_REG = 0xAA;//tx2 tx3 tap0/tap1 en
        BKE2_92_REG = 0xff;//tx channel enable  tx reterm eanble
        BKE2_91_REG |= BIT4_1;//div reset
        DRV_HdmiTx_WriteI2CByte(0xA820,0x03);
        KNL_Delay1ms(10);
        if(DRV_HdmiTx_ReadI2CByte(0xa821) != 0x01)
        {
            DRV_HdmiTx_WriteI2CByte(0xA820,0x03);
        }
        printLT(PRINT_PRIO_TEST, "\nHdmiTx2.0 Out");
    }    
}

void DRV_HdmiTx_TxPllIni(void)//PCRPLL+TXPLL
{
    BKE2_C0_REG = 0x40;//bit7 txpll_pd =0,bit6 txpll_bias_en -1;
    BKE2_C1_REG = 0xc1;//Dhtxpll charge bump current
    BKE2_C2_REG = 0x81;//dhtxpll half pixel clock divide
    
    BKE7_81_REG = 0x20;// ks value
    BKE7_84_REG = 0x40;//PLL calibration compare position set.
    BKE7_85_REG = 0x20;//PLL calibration dprx_vid control freq_khz set enable
    
    BKE7_80_REG &=BIT7_0;
    BKE7_80_REG |=BIT7_1;//TXPLL CAL EN
}

void DRV_HdmiTx_Hdmi20Get(bool ubIsHdmi20)
{  
    g_stHdmiTx.ubIsHdmi20 = ubIsHdmi20 ;
}

void DRV_HmdiTx_SettingIni(void)
{
    DRV_HdmiTx_Ddc_Ini();
    DRV_HdmiTx_RtermCali();
    DRV_HdmiTx_DcDet();
    DRV_HdmiTx_TxPllIni();
    DRV_HdmiTx_PktSendDis();
}

void DRV_HmdiTx_EdidRead(u8 *pucEDID_Data)
{
    u16 usLoop_Cnt;
    #if HDMITX_EDID_READ_EN == ENABLED
    DRV_HdmiTx_ReadI2CByteN(0x00,0xA000,&pucEDID_Data[0x00],128);
    if((pucEDID_Data[0x7e] >= 1)&&(pucEDID_Data[0x7e] <= 3))
    {
        DRV_HdmiTx_ReadI2CByteN(0x00,0xA080,&pucEDID_Data[0x80],128);
    }
    if((pucEDID_Data[0x7e] >= 2)&&(pucEDID_Data[0x7e] <= 3))
    {
        DRV_HdmiTx_ReadI2CByteN(0x01,0xA000,&pucEDID_Data[0x100],128);
    }
    if(pucEDID_Data[0x7e] == 3)
    {	
        DRV_HdmiTx_ReadI2CByteN(0x01,0xA080,&pucEDID_Data[0x180],128);
    }
    if((pucEDID_Data[0]==0x00)&&(pucEDID_Data[1]==0xff)&&(pucEDID_Data[2]==0xff)&&(pucEDID_Data[7]==0x00))
    {
            ;
    }
    else
    #endif
    {
        memcpy(pucEDID_Data,szEdid_Block,512); //copy the EDID to matrix
    }
    #if TX_EDID_PRINT_EN == ENABLED
    for(usLoop_Cnt = 0; usLoop_Cnt < 128*(pucEDID_Data[0x7e]+1); usLoop_Cnt++)
    {
        if((usLoop_Cnt &0x0f) == 0)
        {
            printLT(PRINT_PRIO_TEST, "\n");
        }
        printLT(PRINT_PRIO_TEST, "0x%02bx,", pucEDID_Data[usLoop_Cnt]);
    }
    #endif	
}

void DRV_HdmiTx_ColorSpaceSet(u8 *pucAviPkg,u8 ucBitDepth,u8 ucHdmiVic)
{
    u8 ucAvi_Checksum;
    
    BKD6_60_REG = 0x82;//hb0
    BKD6_61_REG = 0x02;//hb1
    BKD6_62_REG = 0x0d;//hb2
    ucAvi_Checksum = 0x91;
    BKD6_64_REG = pucAviPkg[0];//PB1
    BKD6_65_REG = pucAviPkg[1];//PB2
    BKD6_66_REG = pucAviPkg[2];//PB3
    BKD6_67_REG = pucAviPkg[3];//PB4
    BKD6_68_REG = pucAviPkg[4];//PB5
    
    ucAvi_Checksum += BKD6_64_REG;
    ucAvi_Checksum += BKD6_65_REG;
    ucAvi_Checksum += BKD6_66_REG;
    ucAvi_Checksum += BKD6_67_REG;
    ucAvi_Checksum += BKD6_68_REG;
    BKD6_63_REG = 0x100- ucAvi_Checksum;//PB0   
    if((pucAviPkg[0]&0x60) != 0x02)//Y1Y0 = 01
    {
        DRV_HdmiTx_DeepColor(NOT_YCC422,ucBitDepth);
    }
    else
    {
        DRV_HdmiTx_DeepColor(IS_YCC422,ucBitDepth);
    }
    if(ucBitDepth > 0x00)
    {
        BKD6_73_REG = 0x81;
        BKD6_74_REG = 0x01;
        BKD6_75_REG = 0x05;//length
        BKD6_76_REG = 0x4A- ucHdmiVic;//check sum
        BKD6_77_REG = 0x03;
        BKD6_78_REG = 0x0c;
        BKD6_79_REG = 0x00;
        BKD6_7A_REG = 0x20;
        BKD6_7B_REG = ucHdmiVic;	
        BKD6_19_REG |= BIT5_1;//enable the vsi0 pkt
    }
    else
    {
        BKD6_19_REG &= BIT5_0;//enable the vsi0 pkt
    }
    BKD6_18_REG |= BIT4_1;// gcp pckt enable
    BKD6_19_REG |= BIT3_1;
}

void DRV_HdmiTx_OutSet(void)
{
    DRV_HdmiTx_DigSet(HDMI_MODE,g_stHdmiTx.ubIsHdmi20);
    DRV_HdmiTx_PhySet(g_stHdmiTx.ubIsHdmi20);
}
