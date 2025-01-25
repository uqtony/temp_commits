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

bool DRV_DpRx_AuxDcDet(void)
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
//input :ucLinkRate/ucLinkCount/ubSsc_En/ubTps4_En
//output:N/A
//return:void
//Info  :N/A
//===========================================
void DRV_DpRx_Dpcd_Initial(IN u8 ucLinkRate, IN u8 ucLinkCount,IN bool ubSsc_En,IN bool ubTps4_En)
{
    BKDB_00_REG = 0x40;//DPCD mode select 1 = Register mode 0 = AUX mode;
    DRV_Dpcd_HighAddrWrite(0x00);
    if(ucLinkRate == HBR3)
    {
        DRV_Dpcd_Init_Write(0x00,0x14);
        DRV_Dpcd_Init_Write(0x01,0x14);
        DRV_Dpcd_Init_Write(0x02,0xc0|ucLinkCount);
        if(ubTps4_En)
        {
            DRV_Dpcd_Init_Write(0x03,0x80|ubSsc_En);
        }
        else
        {
            DRV_Dpcd_Init_Write(0x03,0x00|ubSsc_En);
        }
    }
    else
    {
        DRV_Dpcd_Init_Write(0x00,0x12);
        DRV_Dpcd_Init_Write(0x01,ucLinkRate);
        DRV_Dpcd_Init_Write(0x02,0xc0|ucLinkCount);
        DRV_Dpcd_Init_Write(0x03,0x00|ubSsc_En);
    }
    DRV_Dpcd_Init_Write(0x04,0x01);
    DRV_Dpcd_Init_Write(0x05,0x00);
    DRV_Dpcd_Init_Write(0x06,0x01);
    DRV_Dpcd_Init_Write(0x07,0x00);
    DRV_Dpcd_Init_Write(0x08,0x00);
    DRV_Dpcd_Init_Write(0x09,0x00);
    DRV_Dpcd_Init_Write(0x0a,0x00);
    DRV_Dpcd_Init_Write(0x0b,0x00);
    DRV_Dpcd_Init_Write(0x0c,0x00);
    DRV_Dpcd_Init_Write(0x0d,0x00);
    if(ucLinkRate == HBR3)
    {
        DRV_Dpcd_Init_Write(0x0e,0x80);
    }
    else
    {
        DRV_Dpcd_Init_Write(0x0e,0x00);
    }
    DRV_Dpcd_Init_Write(0x21,0x00);//not support mst
    DRV_Dpcd_Init_Write(0x22,0x00);
    DRV_Dpcd_Init_Write(0x23,0x00);
    DRV_Dpcd_HighAddrWrite(0x02);
    DRV_Dpcd_Init_Write(0x00,0x01);//sink cnt = 1
    DRV_Dpcd_HighAddrWrite(0x20);
    DRV_Dpcd_Init_Write(0x02,0x01);//sink cnt = 1
    if(ucLinkRate == HBR3)
    {
        DRV_Dpcd_HighAddrWrite(0x22);
        DRV_Dpcd_Init_Write(0x00,0x14);
        DRV_Dpcd_Init_Write(0x01,ucLinkRate);
        DRV_Dpcd_Init_Write(0x02,0xc0|ucLinkCount);
        if(ubTps4_En)
        {
            DRV_Dpcd_Init_Write(0x03,0x80|ubSsc_En);
        }
        else
        {
            DRV_Dpcd_Init_Write(0x03,0x00|ubSsc_En);
        }
        DRV_Dpcd_Init_Write(0x04,0x01);
        DRV_Dpcd_Init_Write(0x05,0x00);
        DRV_Dpcd_Init_Write(0x06,0x01);
        DRV_Dpcd_Init_Write(0x07,0x00);
        DRV_Dpcd_Init_Write(0x08,0x00);
        DRV_Dpcd_Init_Write(0x09,0x00);
        DRV_Dpcd_Init_Write(0x0a,0x00);
        DRV_Dpcd_Init_Write(0x0b,0x00);
        DRV_Dpcd_Init_Write(0x0c,0x00);
        DRV_Dpcd_Init_Write(0x0d,0x00);
        DRV_Dpcd_Init_Write(0x0e,0x80);
    }
}
//===========================================
//func  :enable  aux ex0 int
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void DRV_DpRx_AuxEx0Int(void)
{
    BKE6_00_REG &= BIT0_0; //bit0:aux rx_int mask
    BKE6_60_REG |= BIT0_1; //bit0 clear interrupt 0
    BKE6_60_REG &= BIT0_0; //bit0 release interrupt 0
}
//===========================================
//func  :enable  1M Resi
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void DRV_DpRx_1MResiEn(void)
{
    BKE2_31_REG |= BIT0_1;
}

void DRV_DpRx_HpdSet(bool ubIsHigh,bool ubIsIrqHigh)
{
    BKE2_12_REG &= BIT6_0;//UCC isolate switch enable
    BKE2_12_REG |= BIT5_1;//Deadbattery Rd disconnected
    BKE2_E1_REG |= BIT1_1|BIT0_1;//OSET
    if(ubIsHigh == TRUE)
    {
        BKE2_F0_REG |= BIT5_1|BIT4_1;//dp rx hpd high
        if(ubIsIrqHigh == TRUE)
        {
            BKE2_F0_REG &= BIT4_0;//dp rx hpd low
            KNL_Delay1us(800);
            BKE2_F0_REG |= BIT5_1|BIT4_1;//dp rx hpd high
        }
    }
    else
    {
        BKE2_F0_REG &= BIT4_0;//dp rx hpd low
    }
}
void DRV_DpRx_AuxIni(void)
{
    #if SYSCLK == SYS_CLK_36M
    BKD9_20_REG = 0x11; //aux_clk_div_num 36M/2-1
    #endif
    BKE2_30_REG = 0x2a;//aux enable
    BKE2_31_REG = 0x3b;//bit2 aux swap        
    BKE2_32_REG = 0x24;
}

void Drv_DpRx_AuxSwap(bool ubSwapEn)
{
    if(ubSwapEn == TRUE)
    {
        BKE2_31_REG |= BIT2_1;//bit2 aux swap
    }
    else
    {
        BKE2_31_REG &= BIT2_0;//bit2 aux swap
    }       
}

void DRV_DpRx_PiSet(bool ubEnable)
{
    if(ubEnable == TRUE)
    {
        BKE2_70_REG |= 0x0f;// bit3:0 pi_en
    }
    else
    {
        BKE2_70_REG &= 0xf0;// bit3:0 pi_en
    }
}

void DRV_DpRx_FreqIntg(void)
{
    BKE7_17_REG = 0x0a;
    BKE7_18_REG = 0xcd;//soft freq intg value
}
//==========================================================================================

void DRV_DpRx_Reset( bool ubSscEnable)
{
    if(ubSscEnable == TRUE)
    {
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
    BKE1_0C_REG |= 0x0f;// cdr logic reset
    BKE7_17_REG &= BIT7_0;// disable the freq intg
}

void DRV_DpRx_Cdr( bool ubSscEnable)
{
    BKE7_11_REG = 0x21;
    if(ubSscEnable == TRUE)
    {
        BKE7_12_REG = 0x55;//FRUG = 2^-8 PHUG = 2^-1
    }
    else
    {
        BKE7_12_REG = 0x35; //FRUG = 2^-11 PHUG = 2^-1
    }
}

void DRV_DpRx_DivSet(u8 ucLinkRate)//issue for the cdr 
{
    if(ucLinkRate >= HBR2)
    {
        BKE2_6E_REG = 0x80; //cdr div10 0x80; 
    }
    else
    {
        BKE2_6E_REG = 0xa0; //cdr div4  0xb0;
    }
}

void DRV_DpRx_RxPllCali(void)
{
    u8 ucRxpll_Cal_Cnt;
    u8 ucLoop_Pll_cnt;
    if(BKE7_60_REG&BIT7_1)
    {
        return;
    }
    for(ucLoop_Pll_cnt = 0;ucLoop_Pll_cnt< 2;ucLoop_Pll_cnt++)
    {
        BKE2_80_REG = 0x50;// Dhrxpll power down = 0
        BKE2_81_REG = 0x08;// rxpll charge bump
        if(ucLoop_Pll_cnt == 0)
        {
             BKE2_89_REG |= BIT7_1;//controls the VCO working on high frequency
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
        BKE7_65_REG |= 0x40;//bit7:6 mainlink control mode 
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
    BKE2_82_REG &=BIT5_0;
    BKE2_82_REG |=BIT5_1;//Dhrxpll VCODIV reset
}


void DRV_DpRx_PhySet(bool ubIsDp,bool ubIsFemale,bool ubIsFlip,u8 ucLane)
{
    if((ubIsDp == TRUE)||(ubIsFemale == FALSE))
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
		if(ubIsFlip == FALSE)//normal aux need swap
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
    
    BKE2_38_REG = 0x33;//rx0 rx1 enable
    BKE2_39_REG = 0x33;//rx2 rx3 enable
    BKE2_42_REG |=BIT7_1;//dp rx bisa enable 
    
    BKE2_44_REG = BKE2_4D_REG = BKE2_56_REG = BKE2_3B_REG = 0xce;//rx0 eq stg0 cur/rl ;
    BKE2_45_REG = BKE2_4E_REG = BKE2_57_REG = BKE2_3C_REG = 0xce;//rx0 eq stg1 cur/rl ;
    BKE2_46_REG = BKE2_4F_REG = BKE2_58_REG = BKE2_3D_REG = 0xcf;//rx0 bf stg0 cur/rl;
    BKE2_47_REG = BKE2_50_REG = BKE2_59_REG = BKE2_3E_REG = 0xff;//rx0 bf stg1 cur/rl;
    BKE2_48_REG = BKE2_51_REG = BKE2_5A_REG = BKE2_3F_REG = 0x88;//rx0 eq cs0/cs1;
    BKE2_49_REG = BKE2_51_REG = BKE2_5B_REG = BKE2_40_REG = 0xF0;//rx0 eq fb0/fb1;
    
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

void DRV_DpRx_EqMode(bool IsHardEq)
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
    BKDB_5F_REG = 0xe4;  //eq swap
    BKDB_5D_REG|= BIT6_1;//hard eq enable
    BKE1_0C_REG &=BIT4_0;//eq hard reset enable in aux training
    
    #if 0 // soft eq mode
    BKDB_5D_REG &= BIT6_0;//hard eq enable
    BKDB_7D_REG = 0x00;
    BKDB_7E_REG = 0x13;
    BKDB_7F_REG = 0x00;
    BKDB_80_REG = 0x13;
    BKDB_81_REG = 0x00;
    BKDB_82_REG = 0x13;
    BKDB_82_REG = 0x00;
    BKDB_83_REG = 0x13;
    #endif
}

void DRV_DpRx_SoftMsaEn( bool ubMsaSoftEn)
{
	u16 usHstart;
	if(ubMsaSoftEn == FALSE)
	{
		BKDA_05_REG &= BIT3_0&BIT2_0;
		BKDA_68_REG &= BIT7_0;
	}
	else
	{
		usHstart = BKDC_E1_REG;
		usHstart <<= 8;
		usHstart |= BKDC_E2_REG;
		usHstart -= 4;
		BKDA_64_REG = BKDC_DB_REG ;
		BKDA_65_REG = BKDC_DC_REG ;//htotal
		BKDA_6A_REG = BKDC_E7_REG ;
		BKDA_6B_REG = BKDC_E8_REG ;//hactive
		BKDA_66_REG = usHstart>>8 ;
		BKDA_67_REG = usHstart ;  //hstart
		BKDA_68_REG = BKDC_DF_REG&0x7f ;
		BKDA_69_REG = BKDC_E0_REG ;//hsync
		if(BKDC_DF_REG&BIT7_1)
		{
			BKDA_05_REG |= BIT2_1;
			BKDA_05_REG |= BIT3_1;
		}
		else
		{
			BKDA_05_REG |= BIT2_1;
			BKDA_05_REG &= BIT3_0;
		}
		BKDA_68_REG |= BIT7_1;
	}
	
}
//======================================================================
// initial the digital pcr setting,not need calbration analog pcr, 
//pcrpll is same as txpll
//=======================================================================
void DRV_DpRx_PcrIni(void)
{
    BKDA_04_REG = 0X0a;//step_out pcr 
    BKDA_28_REG = 0x32;//Stream clock tracker timer set
    BKDA_2F_REG = 0x0F;//KP select:
    BKDA_31_REG = 0xa4;//rg_lin_cnt_sel 
    BKDA_77_REG = 0x0b;//hactive/hblanking between received video and standard video.
    BKDA_35_REG = 0x04;//Frequency stable threshold
    BKDA_83_REG = 0x21;//initial the mk
    BKDA_86_REG = 0X0a;//Dividing ratio lower limit threshold
    BKDB_B4_REG &=BIT1_0;
    BKDB_B4_REG |=BIT1_1;//vid pcr soft reset
}

bool DRV_DpRx_PcrPllTbcr(void)
{
    if((BKDA_DE_REG&0xc0)==0x40)
    {
        return TRUE;
    }
    return FALSE;
}

void DRV_DpRx_SettingIni(void)
{
    DRV_DpRx_Dpcd_Initial(g_stDpRx.ucRxLinkRate,g_stDpRx.ucRxLinkCount,g_stDpRx.ubSsc_Support,g_stDpRx.ubSsc_Support);
    DRV_DpRx_AuxEx0Int();
    DRV_DpRx_AuxIni();
    DRV_DpRx_RxPllCali();
    DRV_DpRx_PiSet(TRUE);
    DRV_DpRx_FreqIntg();
    DRV_DpRx_Cdr(g_stDpRx.ubSsc_Support);
    DRV_DpRx_PhyCal();
    DRV_DpRx_PhySet(g_stDpRx.ubInput_Type_Sel,UCCStatus.CcInput_type,UCCStatus.IsFlip,g_stDpRx.ucRxLinkCount); 
    DRV_DpRx_MainLink();
    DRV_DpRx_PcrIni();
    DRV_DpRx_Reset(g_stDpRx.ubSsc_Support);
}


