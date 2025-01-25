/******************************************************************************
  * @project: LT2101
  * @file: dprx.c
  * @author: qihan
  * @company: LONTIUM
  * @date: 2021.10.12
/******************************************************************************/

#include "Include.h"
//===========================================
//func  :used to intital the dpcd high byte addr bit19-16 =0 ucAddr15_8 for bit15:8
//input :ucAddr15_8
//output:N/A
//return:void
//Info  :N/A
//===========================================

u8 DRV_DpRx_AuxDcDet(void)
{
    if(((BKE5_D5_REG&BIT1_1)==0x02)&&((BKE5_D5_REG&BIT2_1)== 0x00))//auxp=1,auxn =0 not connect
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void DRV_Dpcd_HighAddrWrite(IN u8 ucAddr15_8)
{
    BKDB_03_REG = 0x00;
    BKDB_04_REG = ucAddr15_8;
}
//===========================================
//func  :used to intital the dpcd addr bit7:0 and value
//input :ucAddr7_0/ucValue
//output:N/A
//return:void
//Info  :N/A
//===========================================
void DRV_Dpcd_Init_Write(IN u8 ucAddr7_0,IN u8 ucValue)
{
    BKDB_05_REG = ucAddr7_0;
    BKDB_53_REG = ucValue;
}
//===========================================
//func  :used to intital the dpcd for dp rx,
//input :ucLinkRate/ucLinkCount/u1Ssc_En/u1Tps4_En
//output:N/A
//return:void
//Info  :N/A
//===========================================
void DRV_DpRx_Dpcd_Init(IN StructDpRx pstDpRx)
{
    BKDB_00_REG = 0xc0;//DPCD mode select 1 = Register mode 0 = AUX mode;
    DRV_Dpcd_HighAddrWrite(0x00);
    if(pstDpRx.ucRxLinkRate == HBR3)
    {
        DRV_Dpcd_Init_Write(0x00,0x14);
        DRV_Dpcd_Init_Write(0x01,0x14);
        DRV_Dpcd_Init_Write(0x02,0xc0|pstDpRx.ucRxLinkRate);
        if(pstDpRx.u1Tps4_Support)
        {
            DRV_Dpcd_Init_Write(0x03,0x80|pstDpRx.u1Ssc_Support);
        }
        else
        {
            DRV_Dpcd_Init_Write(0x03,0x00|pstDpRx.u1Ssc_Support);
        }
    }
    else
    {
        DRV_Dpcd_Init_Write(0x00,0x14);
        DRV_Dpcd_Init_Write(0x01,pstDpRx.ucRxLinkRate);
        DRV_Dpcd_Init_Write(0x02,0xc0|pstDpRx.ucRxLinkCount);
        DRV_Dpcd_Init_Write(0x03,0x00|pstDpRx.u1Ssc_Support);
    }
    DRV_Dpcd_Init_Write(0x04,0x01);
    DRV_Dpcd_Init_Write(0x05,0x15);
    DRV_Dpcd_Init_Write(0x06,0x01);
    DRV_Dpcd_Init_Write(0x07,0x00);
    DRV_Dpcd_Init_Write(0x08,0x00);
    DRV_Dpcd_Init_Write(0x09,0x00);
    DRV_Dpcd_Init_Write(0x0a,0x00);
    DRV_Dpcd_Init_Write(0x0b,0x00);
    DRV_Dpcd_Init_Write(0x0c,0x00);
    DRV_Dpcd_Init_Write(0x0d,0x00);

    DRV_Dpcd_Init_Write(0x0e,0x80);

    DRV_Dpcd_Init_Write(0x21,0x00);//not support mst
    DRV_Dpcd_Init_Write(0x22,0x00);
    DRV_Dpcd_Init_Write(0x23,0x00);
    
    DRV_Dpcd_Init_Write(0x80,0x4b);
    DRV_Dpcd_Init_Write(0x81,0xf0);// 600M
    DRV_Dpcd_Init_Write(0x82,0x02);
    DRV_Dpcd_Init_Write(0x83,0x00);
    
    DRV_Dpcd_HighAddrWrite(0x02);
    DRV_Dpcd_Init_Write(0x00,0x01);//sink cnt = 1
    DRV_Dpcd_HighAddrWrite(0x20);
    DRV_Dpcd_Init_Write(0x02,0x01);//sink cnt = 1
    
    DRV_Dpcd_HighAddrWrite(0x22);
    DRV_Dpcd_Init_Write(0x00,0x14);
    DRV_Dpcd_Init_Write(0x01,pstDpRx.ucRxLinkRate);
    DRV_Dpcd_Init_Write(0x02,0xc0|pstDpRx.ucRxLinkCount);
    if((pstDpRx.ucRxLinkRate == HBR3)&&(pstDpRx.u1Tps4_Support))
    {
        DRV_Dpcd_Init_Write(0x03,0x80|pstDpRx.u1Ssc_Support);
    }
    else
    {
        DRV_Dpcd_Init_Write(0x03,0x00|pstDpRx.u1Ssc_Support);
    }
    DRV_Dpcd_Init_Write(0x04,0x01);
    DRV_Dpcd_Init_Write(0x05,0x15);
    DRV_Dpcd_Init_Write(0x06,0x01);
    DRV_Dpcd_Init_Write(0x07,0x00);
    DRV_Dpcd_Init_Write(0x08,0x00);
    DRV_Dpcd_Init_Write(0x09,0x00);
    DRV_Dpcd_Init_Write(0x0a,0x00);
    DRV_Dpcd_Init_Write(0x0b,0x00);
    DRV_Dpcd_Init_Write(0x0c,0x00);
    DRV_Dpcd_Init_Write(0x0d,0x00);
    DRV_Dpcd_Init_Write(0x0e,0x80);
    DRV_Dpcd_Init_Write(0x10,0x08);//VSC support

}
//=============================================
//func  :enable  1M Resi
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//=============================================
void DRV_DpRx_1MResiEn(void)
{
    BKE2_31_REG |= BIT0_1;
}

void DRV_DpRx_HpdSet(u8 u1IsHigh,u8 u1IsIrqHigh)
{
    BKE2_12_REG &= BIT6_0;//UCC isolate switch enable
    BKE2_12_REG |= BIT5_1;//Deadbattery Rd disconnected
    BKE2_E1_REG |= BIT1_1|BIT0_1;//OSET
    if(u1IsHigh == TRUE)
    {
        BKE2_F0_REG |= BIT5_1|BIT4_1;//dp rx hpd high
        if(u1IsIrqHigh == TRUE)
        {
            BKE2_F0_REG &= BIT4_0;//dp rx hpd low
            KNL_Delay1us(800);
            BKE2_F0_REG |= BIT5_1|BIT4_1;//dp rx hpd high
        }
        printLT(PRINT_PRIO_HIG,"\nDpRx Hpd High"); 
    }
    else
    {
        BKE2_F0_REG &= BIT4_0;//dp rx hpd low
        printLT(PRINT_PRIO_HIG,"\nDpRx Hpd Low"); 
    }
}
void DRV_DpRx_AuxInit(void)
{
    #if SYSCLK == SYS_CLK_36M
    BKD9_20_REG = 0x11; //aux_clk_div_num 36M/2-1
    #endif
    BKE2_30_REG = 0x2a;//aux enable
    BKE2_31_REG = 0x3b;//bit2 aux swap        
    BKE2_32_REG = 0x24;
}

void Drv_DpRx_AuxSwap(u8 u1SwapEn)
{
    if(u1SwapEn == TRUE)
    {
        BKE2_31_REG |= BIT2_1;//bit2 aux swap
    }
    else
    {
        BKE2_31_REG &= BIT2_0;//bit2 aux swap
    }       
}

void Drv_DpRx_CrLockHoldSet(u8 u1IsLock)
{
    if(u1IsLock == TRUE)
    {
        BKDB_0F_REG = 0x00;
        BKDB_15_REG = 0x00;
        BKDB_1B_REG = 0x00;
        BKDB_3D_REG = 0x00;
    }
    else
    {
        BKDB_0F_REG = 0x0f;
        BKDB_15_REG = 0x0f;
        BKDB_1B_REG = 0x0f;
        BKDB_3D_REG = 0x0f;
    } 
}

void DRV_DpRx_PiEnable(u8 u1Enable)
{
    BKE2_70_REG = 0x80;//
    if(u1Enable == TRUE)
    {
        BKE2_70_REG |= 0x0f;// bit3:0 pi_en
    }
    else
    {
        BKE2_70_REG &= 0xf0;// bit3:0 pi_en
    }
}

void DRV_DpRx_PiSet(u8 ucLinkRate)
{
    if(ucLinkRate == HBR3)
    {
        BKE2_70_REG = 0x80|(BKE2_70_REG&0x3f);
    }
    else if(ucLinkRate == HBR2)
    {
        BKE2_70_REG = 0x40|(BKE2_70_REG&0x3f);
    }
    else
    {
        BKE2_70_REG = BKE2_70_REG&0x3f;
    } 
}
void DRV_DpRx_FreqIntg(void)
{
    BKE7_17_REG = 0x0a;
    BKE7_18_REG = 0xcd;//soft freq intg value
}
//===========================================================================================

void DRV_DpRx_Reset( u8 u1SscEnable)
{
    if(u1SscEnable == TRUE)
    {
        BKE7_11_REG |= BIT4_1;
        BKE7_17_REG |= BIT7_1; 
    }
    else
    {
        BKE7_17_REG &= BIT7_0;
    }
    BKE1_0E_REG &= BIT2_0;
    BKE1_0F_REG &= BIT4_0;
    BKE1_0C_REG &= 0xf0;
    BKE1_0E_REG |= BIT2_1;//rx div rest release
    BKE1_0F_REG |= BIT4_1;// pi rest release
    BKE1_0C_REG |= 0x0f;   //cdr logic reset
    BKE7_17_REG &= BIT7_0;// disable the freq intg  
    BKE7_11_REG &= BIT4_0;
}

void DRV_DpRx_Cdr( u8 u1SscEnable)
{
    if(u1SscEnable == TRUE)
    {
        BKE7_11_REG = 0x41;
        BKE7_12_REG = 0x55;//FRUG = 2^-8 PHUG = 2^-1
    }
    else
    {
        BKE7_11_REG = 0x01;
        BKE7_12_REG = 0x35; //FRUG = 2^-11 PHUG = 2^-1
    }
}

void DRV_DpRx_DivSet(u8 ucLinkRate)//issue for the cdr 
{
    BKE1_0E_REG &= BIT2_0;//rx div reset
    BKE2_6E_REG = (ucLinkRate >= HBR2)?(0x80):(0xa0);
    BKE1_0E_REG |= BIT2_1;//rx div release
}

void DRV_DpRx_RxPllBand(u8 ucLinkRate)
{
    if(ucLinkRate == HBR3)
    {
        BKE2_89_REG |= BIT7_1;//controls the VCO working on high frequency
    }
    else
    {
        BKE2_89_REG &= BIT7_0;//controls the VCO working on high frequency
    }
}

void DRV_DpRx_RxPllCali(u8 ucLinkRate)
{
    u8 ucRxpll_Cal_Cnt;
    u8 ucLoop_Pll_cnt;
    if(BKE7_60_REG&BIT7_1)
    {
        return;
    }
    for(ucLoop_Pll_cnt = 0;ucLoop_Pll_cnt< 2;ucLoop_Pll_cnt++)
    {
        if(ucLinkRate <= HBR2)
        {
            ucLoop_Pll_cnt = 1;
        }
        BKE2_80_REG = 0x50;// Dhrxpll power down = 0
        BKE2_81_REG = 0x08;// rxpll charge bump
        if(ucLoop_Pll_cnt == 0)
        {
            BKE2_89_REG |= BIT7_1;//controls the VCO working on high frequency
        }
        else
        {
            BKE2_89_REG &= BIT7_0;//controls the VCO working on high frequency
        }
        BKE7_60_REG = 0x20;//bit0 band bi5 auto cal en en
        BKE7_61_REG = 0x20;//bit5:4 ks value
        BKE7_62_REG = 0x04;//kf value
        BKE7_65_REG = 0x08;//bit7:6 auto control bit 3  RX divide 8 enable
        ucRxpll_Cal_Cnt = 0;
        do
        {
            BKE1_0C_REG &=BIT6_0&BIT5_0;
            BKE1_0E_REG &=BIT4_0;
            BKE7_60_REG &= BIT7_0;//
            KNL_Delay1ms(1);
            BKE1_0C_REG |=BIT6_1|BIT5_1;// rxpll cal reset
            BKE1_0E_REG |=BIT4_1;// rxpll _rst
            BKE7_60_REG |= BIT7_1;//cal en
            ucRxpll_Cal_Cnt++;
            KNL_Delay1ms(5);
        }while((ucRxpll_Cal_Cnt <= 3)&&((BKE7_6D_REG&0xc0) != 0x80));
        printLT(PRINT_PRIO_HIG,"\nRxpll Band = 0x%02bx,0x%02bx,0x%02bx,0x%02bx",BKE7_70_REG,BKE7_71_REG,BKE7_72_REG,BKE7_73_REG);
        if(ucLoop_Pll_cnt == 0)
        {
            BKE7_69_REG = BKE7_73_REG;//8.1g band out
            BKE7_65_REG = 0xb8;//soft mode
        }
        else
        {
            BKE7_66_REG = BKE7_70_REG;//1.62g band out
            BKE7_67_REG = BKE7_71_REG;//2.7g band out
            BKE7_68_REG = BKE7_72_REG;//5.4g band out
            BKE7_65_REG = 0x88;       //soft mode 
        }
        ucRxpll_Cal_Cnt = 0;
        do
        {
            ucRxpll_Cal_Cnt++;
            KNL_Delay1ms(1);
            if(BKE7_6C_REG&BIT0_1)
            {
                printLT(PRINT_PRIO_HIG,"\nRxpll lock");
                break;
            }
        }while(ucRxpll_Cal_Cnt < 10);
    }
    BKE7_65_REG = 0x48;//bit7:6 mainlink control mode 
    BKE7_60_REG |= BIT0_1;//bit0 band soft control en
    BKE2_82_REG &= BIT5_0;
    BKE2_82_REG |= BIT5_1;//Dhrxpll VCODIV reset
}

void DRV_DpRx_PhySet(u8 u1IsDp,u8 u1IsFemale,u8 u1IsFlip,u8 ucLane)
{
    if((u1IsDp == TRUE)||(u1IsFemale == FALSE))
    {
		printLT(PRINT_PRIO_HIG,"\nDp Or Male");
		switch(ucLane)
        {
            case 0x04:
                BKE2_38_REG = 0x33;//rx0 rx1 enable
                BKE2_39_REG = 0x33;//rx2 rx3 enable
                break;
            case 0x02:
                BKE2_38_REG = 0x33;//rx0 rx1 enable
                BKE2_39_REG = 0x00;//rx2 rx3 enable
                break;
            case 0x01:
                BKE2_38_REG = 0x30;//rx0 rx1 enable
                BKE2_39_REG = 0x00;//rx2 rx3 enable
                break; 
            default:
                break;
        }
        BKE1_30_REG &= BIT1_0&BIT0_0;//control logic link_clk source
        BKE5_E8_REG &=0xf0;//bit3:0 pn swap
        BKE5_E9_REG = 0x1b;//dp controller data source select
        Drv_DpRx_AuxSwap(FALSE);
    }
    else
    {
		if(u1IsFlip == FALSE)//normal aux need swap
        {
			printLT(PRINT_PRIO_HIG,"\nFemale Normal");
			switch(ucLane)
            {
                case 0x04:
                    BKE2_38_REG = 0x33;//rx0 rx1 enable
                    BKE2_39_REG = 0x33;//rx2 rx3 enable
                    break;
                case 0x02:
                    BKE2_38_REG = 0x00;//rx0 rx1 enable
                    BKE2_39_REG = 0x33;//rx2 rx3 enable
                    break;
                case 0x01:
                    BKE2_38_REG = 0x00;//rx0 rx1 enable
                    BKE2_39_REG = 0x03;//rx2 rx3 enable
                    break; 
                default:
                    break;                
            }
            BKE1_30_REG |= BIT1_1|BIT0_1;//DPRX control logic link_clk 0x03
            BKE5_E8_REG |= BIT2_1|BIT0_1;//bit3:0 pn swap
            BKE5_E9_REG = 0xe1;//dp controller data source select
            Drv_DpRx_AuxSwap(FALSE);
        }
        else //fancha 
        {
			printLT(PRINT_PRIO_HIG,"\nFemale Flip");
			switch(ucLane)
            {
                case 0x04:
                    BKE2_38_REG = 0x33;//rx0 rx1 enable
                    BKE2_39_REG = 0x33;//rx2 rx3 enable
                    break;
                case 0x02:
                    BKE2_38_REG = 0x33;//rx0 rx1 enable
                    BKE2_39_REG = 0x00;//rx2 rx3 enable
                    break;
                case 0x01:
                    BKE2_38_REG = 0x03;//rx0 rx1 enable
                    BKE2_39_REG = 0x00;//rx2 rx3 enable
                    break; 
                default:
                    break;                
            }
            BKE1_30_REG &= BIT1_0;//DPRX control logic link_clk 0x01
            BKE1_30_REG |= BIT0_1;//DPRX control logic link_clk 0x01
            BKE5_E8_REG |= BIT2_1|BIT0_1;//bit3:0 pn swap
            BKE5_E9_REG = 0x4b;//dp controller data source select
            Drv_DpRx_AuxSwap(TRUE);
        }
    }
}

void DRV_DpRx_PhyCal(void)
{
    u8 ucDhRxterm_cnt;
    if(BKE7_20_REG&BIT0_1)
    {
        return;
    }
    BKE2_38_REG = 0x33;//rx0 rx1 enable
    BKE2_39_REG = 0x33;//rx2 rx3 enable
    BKE2_42_REG |=BIT7_1;//dp rx bisa enable 
    BKE2_3B_REG = BKE2_44_REG = BKE2_4D_REG = BKE2_56_REG = 0xec;//rx eq stg0 cur/rl
    BKE2_3C_REG = BKE2_45_REG = BKE2_4E_REG = BKE2_57_REG = 0xec;//rx eq stg1 cur/rl
    BKE2_3D_REG = BKE2_46_REG = BKE2_4F_REG = BKE2_58_REG = 0xec;//rx bf stg0 cur/rl
    BKE2_3E_REG = BKE2_47_REG = BKE2_50_REG = BKE2_59_REG = 0xef;//rx bf stg1 cur/rl
    BKE2_3F_REG = BKE2_48_REG = BKE2_51_REG = BKE2_5A_REG = 0xa6;//rx eq cs0/cs1;
    BKE2_40_REG = BKE2_49_REG = BKE2_52_REG = BKE2_5B_REG = 0xa8;//rx eq fb0/fb1;
    BKE2_41_REG = BKE2_4A_REG = BKE2_53_REG = BKE2_5C_REG = 0xc0;//rx eq fb0/fb1;
    ucDhRxterm_cnt = 0;
    do
    {
        BKE7_20_REG &= BIT0_0;
        BKE7_20_REG |= BIT0_1;//Rterm calibration enable.
        KNL_Delay1ms(5);
        ucDhRxterm_cnt++;
    }while((ucDhRxterm_cnt < 3)&&((BKE7_27_REG&BIT3_1)== 0x00));
    printLT(PRINT_PRIO_HIG,"\nRxterm = 0x%02bx",BKE7_28_REG); 
}

void DRV_DpRx_PhyCsFbSet(u8 ucLinkRate)
{
    switch(ucLinkRate)
    {
        case  HBR3:
            BKE2_3B_REG = BKE2_44_REG = BKE2_4D_REG = BKE2_56_REG = 0xec;//rx eq stg0 cur/rl
            BKE2_3C_REG = BKE2_45_REG = BKE2_4E_REG = BKE2_57_REG = 0xec;//rx eq stg1 cur/rl
            BKE2_3D_REG = BKE2_46_REG = BKE2_4F_REG = BKE2_58_REG = 0xec;//rx bf stg0 cur/rl
            BKE2_3E_REG = BKE2_47_REG = BKE2_50_REG = BKE2_59_REG = 0xef;//rx bf stg1 cur/rl
            BKE2_3F_REG = BKE2_48_REG = BKE2_51_REG = BKE2_5A_REG = 0xa6;//rx eq cs0/cs1;
            BKE2_40_REG = BKE2_49_REG = BKE2_52_REG = BKE2_5B_REG = 0xa8;//rx eq fb0/fb1;
            BKE2_41_REG = BKE2_4A_REG = BKE2_53_REG = BKE2_5C_REG = 0xc0;//rx eq fb0/fb1;
            break;
        case HBR2:
            BKE2_3B_REG = BKE2_44_REG = BKE2_4D_REG = BKE2_56_REG = 0xa8;//rx eq stg0 cur/rl
            BKE2_3C_REG = BKE2_45_REG = BKE2_4E_REG = BKE2_57_REG = 0x88;//rx eq stg1 cur/rl
            BKE2_3D_REG = BKE2_46_REG = BKE2_4F_REG = BKE2_58_REG = 0x88;//rx bf stg0 cur/rl
            BKE2_3E_REG = BKE2_47_REG = BKE2_50_REG = BKE2_59_REG = 0x88;//rx bf stg1 cur/rl
            BKE2_3F_REG = BKE2_48_REG = BKE2_51_REG = BKE2_5A_REG = 0x66;//rx eq cs0/cs1;
            BKE2_40_REG = BKE2_49_REG = BKE2_52_REG = BKE2_5B_REG = 0x83;//rx eq fb0/fb1;
            BKE2_41_REG = BKE2_4A_REG = BKE2_53_REG = BKE2_5C_REG = 0x40;//rx eq fb0/fb1;           
            break;
        case HBR:
            BKE2_3B_REG = BKE2_44_REG = BKE2_4D_REG = BKE2_56_REG = 0x64;//rx eq stg0 cur/rl
            BKE2_3C_REG = BKE2_45_REG = BKE2_4E_REG = BKE2_57_REG = 0x44;//rx eq stg1 cur/rl
            BKE2_3D_REG = BKE2_46_REG = BKE2_4F_REG = BKE2_58_REG = 0x44;//rx bf stg0 cur/rl
            BKE2_3E_REG = BKE2_47_REG = BKE2_50_REG = BKE2_59_REG = 0x44;//rx bf stg1 cur/rl
            BKE2_3F_REG = BKE2_48_REG = BKE2_51_REG = BKE2_5A_REG = 0x33;//rx eq cs0/cs1;
            BKE2_40_REG = BKE2_49_REG = BKE2_52_REG = BKE2_5B_REG = 0x33;//rx eq fb0/fb1;
            BKE2_41_REG = BKE2_4A_REG = BKE2_53_REG = BKE2_5C_REG = 0x40;//rx eq fb0/fb1;  
            break;
        case RBR:
            BKE2_3B_REG = BKE2_44_REG = BKE2_4D_REG = BKE2_56_REG = 0x43;//rx eq stg0 cur/rl
            BKE2_3C_REG = BKE2_45_REG = BKE2_4E_REG = BKE2_57_REG = 0x22;//rx eq stg1 cur/rl
            BKE2_3D_REG = BKE2_46_REG = BKE2_4F_REG = BKE2_58_REG = 0x22;//rx bf stg0 cur/rl
            BKE2_3E_REG = BKE2_47_REG = BKE2_50_REG = BKE2_59_REG = 0x22;//rx bf stg1 cur/rl
            BKE2_3F_REG = BKE2_48_REG = BKE2_51_REG = BKE2_5A_REG = 0x22;//rx eq cs0/cs1;
            BKE2_40_REG = BKE2_49_REG = BKE2_52_REG = BKE2_5B_REG = 0x22;//rx eq fb0/fb1;
            BKE2_41_REG = BKE2_4A_REG = BKE2_53_REG = BKE2_5C_REG = 0x40;//rx eq fb0/fb1;  
        default:
            break;
    }
}

void DRV_DpRx_EqMode(u8 IsHardEq)
{
    if(IsHardEq == TRUE)
    {
        BKDB_5D_REG|= BIT6_1;//hard eq enable
    }
    else
    {
        BKDB_5D_REG &= BIT6_0;//hard eq enable
    }
}

void DRV_DpRx_MainLink(void)
{
    BKDB_C2_REG = 0x21;//Link lock soft mode Link lock status in soft mode/Eq stage select in tps1 pattern
    BKDB_5F_REG = 0xe4;  //eq swap
    BKDB_5D_REG|= BIT6_1;//hard eq enable
    BKE1_0C_REG &=BIT4_0;//eq hard reset disable in aux training
    BKE1_0E_REG &=BIT3_0;//Analog RX hardware reset enable
    BKE1_0F_REG &=BIT5_0;//Analog RXPI hardware reset enable
    
    BKDB_7D_REG = 0x00;
    BKDB_7F_REG = 0x00;
    BKDB_81_REG = 0x00;
    BKDB_82_REG = 0x00;
    BKDB_85_REG &=0xf0;// eq offset zero
    #if 0 // soft eq mode
    BKDB_5D_REG &= BIT6_0;//hard eq enable
    BKDB_7E_REG = 0x13;
    BKDB_80_REG = 0x13;
    BKDB_82_REG = 0x13;
    BKDB_83_REG = 0x13;
    #endif
    
    BKDB_25_REG = 0x03;
    BKDB_26_REG = 0xBE;//CHEQ TPS2 threshold value at RBR(1.62G)
    
    BKDB_2E_REG = 0x06;
    BKDB_2F_REG = 0xE8;//2.7g
    
    BKDB_37_REG = 0x0e;
    BKDB_38_REG = 0xd6;//5.4g
    
    BKDB_3A_REG = 0x00;
    BKDB_3B_REG = 0x96;
    BKDB_3C_REG = 0x4b;//CRLOCK_CLK_COUNTER_HBR3
    BKDB_3D_REG = 0x00;
    BKDB_3E_REG = 0x96;
    BKDB_3F_REG = 0x4b;//CRLOCK_TPS1_COUNTER_THRESHOLD_HBR3
    
    BKDB_40_REG = 0x00;
    BKDB_41_REG = 0x1f;
    BKDB_42_REG = 0xa4;//CHEQ_TOTAL_CLK_COUNTER_HBR3
    BKDB_43_REG = 0x00;
    BKDB_44_REG = 0x07;
    BKDB_45_REG = 0xe9;//CHEQ_WAIT_CLK_COUNTER_HBR3
    BKDB_46_REG = 0x00;
    BKDB_47_REG = 0x16;
    BKDB_48_REG = 0xb5;//CHEQ_TPS2_COUNTER_THRESHOLD_HBR3
    
    #if 0
    BKDB_4A_REG = SzMainLink_Eq[2];  
    BKDB_4C_REG = SzMainLink_Eq[3];
    BKDB_4E_REG = SzMainLink_Eq[4];
    BKDB_50_REG = SzMainLink_Eq[5];
    BKDB_64_REG = SzMainLink_Eq[6];
    BKDB_66_REG = SzMainLink_Eq[7];
    BKDB_68_REG = SzMainLink_Eq[8];
    
    BKDB_6C_REG = SzMainLink_Eq[9];
    BKDB_6E_REG = SzMainLink_Eq[10];
    BKDB_70_REG = SzMainLink_Eq[11];
    BKDB_72_REG = SzMainLink_Eq[12];
    BKDB_74_REG = SzMainLink_Eq[13];
    BKDB_76_REG = SzMainLink_Eq[14];
    BKDB_78_REG = SzMainLink_Eq[15];
    BKDB_7A_REG = SzMainLink_Eq[16];
    BKDB_7C_REG = SzMainLink_Eq[17];
    #endif
}

void DRV_DpRx_SoftMsaEn( u8 u1MsaSoftEn,u8 u1Ycc420)
{
	u16 usHstart,usHtotal,usHactive,usHsync;
	if(u1MsaSoftEn == FALSE)
	{
		BKDA_68_REG &= BIT7_0;
	}
	else
	{
        usHtotal = ((u16)BKDC_DB_REG<<8) + BKDC_DC_REG;
        usHactive =((u16)BKDC_E7_REG<<8) + BKDC_E8_REG;
        usHstart = ((u16)BKDC_E1_REG<<8) + BKDC_E2_REG;
        usHsync =  ((u16)BKDC_DF_REG<<8) + BKDC_E0_REG;
        if(u1Ycc420 == TRUE)
        {
            usHtotal  >>= 1;
            usHactive >>= 1;
            usHstart  >>= 1;
            usHsync   >>= 1;
        }
		usHstart -= 4;
		BKDA_64_REG = usHtotal>>8 ;
		BKDA_65_REG = usHtotal ;//htotal
		BKDA_6A_REG = usHactive>>8 ;
		BKDA_6B_REG = usHactive ;//hactive
		BKDA_66_REG = usHstart>>8 ;
		BKDA_67_REG = usHstart ; //hstart
		BKDA_68_REG = (usHsync>>8)&0x7f;
		BKDA_69_REG = usHsync ;//hsync
		BKDA_68_REG |= BIT7_1;
	}
}

void DRV_DpRx_MlcRest(void)
{
    printLT(PRINT_PRIO_HIG,"\nRxMlc Reset");
}
void DRV_DpRx_VidPcrReset(void)
{
    BKDB_B4_REG &=BIT1_0;
    BKDB_B4_REG |=BIT1_1;//vid pcr soft reset
    printLT(PRINT_PRIO_HIG,"\nRxPcr Reset");          
}
//======================================================================
// initial the digital pcr setting,not need calbration analog pcr, 
//pcrpll is same as txpll
//=======================================================================
void DRV_DpRx_PcrInit(void)
{
    BKDA_04_REG = 0X0a;//step_out pcr 
    BKDA_21_REG = 0X90;//DIV_LIMTI_low 500/27+2
    BKDA_22_REG = 0Xb9;//DIV_LIMTI_UP 1500/27+2   
    BKDA_23_REG = 0xc0;// Almost full value 0 step
    BKDA_28_REG = 0x32;//Stream clock tracker timer set
    BKDA_2F_REG = 0x0F;//KP select:
    BKDA_31_REG = 0xa4;//rg_lin_cnt_sel 
    BKDA_35_REG = 0x04;//Frequency stable threshold
    BKDA_46_REG &=BIT5_0;//Pixel clock recovery mode select DE MODE
    BKDA_47_REG = 0xc0;
    BKDA_70_REG = 0x01; //value of line counter maximum set for pixel clock calibration.
    BKDA_77_REG = 0x0b;//hactive/hblanking between received video and standard video.
    BKDA_83_REG = 0x21;//initial the mk
    BKDA_86_REG = 0X10;//Dividing ratio lower limit threshold
    BKDA_87_REG = 0Xb9;//Dividing ratio upper limit threshold
}
//=======================================================================
//  
//TURE :HDMI20 FALSE : HDMI14
//=======================================================================

u8 DRV_DpRx_PcrPllTbcr(void)
{
    if((BKDA_DE_REG&0xc0) == 0x00)
    {
        return FALSE;
    }
    return TRUE;
}

void DRV_DpRx_SettingInit(void)
{
    DRV_DpRx_Dpcd_Init(g_stDpRx);
    DRV_Interrupt_Set(IRQ_AUXRX_INT,ON);
    DRV_DpRx_AuxInit();
    DRV_DpRx_RxPllCali(g_stDpRx.ucRxLinkRate);
    DRV_DpRx_PiEnable(TRUE);
    DRV_DpRx_FreqIntg();
    DRV_DpRx_Cdr(g_stDpRx.u1Ssc_Support);
    DRV_DpRx_PhyCal();
    DRV_DpRx_PhySet(g_stDpRx.u1Input_Type_Sel,UCCStatus.CcInput_type,UCCStatus.IsFlip,g_stDpRx.ucRxLinkCount); 
    DRV_DpRx_MainLink();
    DRV_DpRx_PcrInit();
    DRV_DpRx_VidPcrReset();
    DRV_DpRx_Reset(g_stDpRx.u1Ssc_Support);
}


