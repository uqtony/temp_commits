#include "include.h"

//===========================================
//func  :Drvtypec
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
#if TYPECRX_EN == ENABLED
void UCCRX_Rate_Set(void)
{
    #if SYSCLK == SYS_CLK_36M
    BKD0_31_REG = 0x08;//40m Type-C RX first sample position
    BKD0_32_REG = 0x50;//Type-C RX second sample position
    BKD0_33_REG = 0x51;
    BKD0_34_REG = 0x52;
    BKD0_35_REG = 0x60;//
    BKD0_22_REG = 0x52;//RX receiving half-bit positonFC22 > max of width of "1"
    BKD0_1F_REG = 0xa3;//		
    #endif

    #if SYSCLK == SYS_CLK_36M
    BKD0_B1_REG = 0x08;//40m Type-C RX first sample position
    BKD0_B2_REG = 0x50;//Type-C RX second sample position
    BKD0_B3_REG = 0x51;
    BKD0_B4_REG = 0x52;
    BKD0_B5_REG = 0x60;//
    BKD0_A2_REG = 0x52;//RX receiving half-bit positonFC22 > max of width of "1"
    BKD0_9F_REG = 0xa3;//		
    #endif
}
void CCTX_Rate_Set(u8 UCC_DCC)
{
	if(UCC_DCC == UCC)
	{
		#if SYSCLK == SYS_CLK_36M
		BKD0_AD_REG = 0x40;//TX transmitting half-bit position 50
		BKD0_AE_REG = 0x75;//TX transmitting time of one bitA0
		BKD0_C1_REG = 0x62;//IDLE DET_EN 13 and Rx rate detect mode
		BKD0_C2_REG = 0x60;//HALF 270K
		BKD0_C3_REG = 0x30;//HALF 330K
		BKD0_C5_REG = 0xd8;//
		BKD0_C6_REG = 0x80;//	
		#endif
	}
	else
	{
		#if SYSCLK == SYS_CLK_36M
		BKD0_2D_REG = 0x40;//TX transmitting half-bit position 50
		BKD0_2E_REG = 0x75;//TX transmitting time of one bitA0
		BKD0_41_REG = 0x62;//IDLE DET_EN 13 and Rx rate detect mode
		BKD0_42_REG = 0x60;//HALF 270K
		BKD0_43_REG = 0x30;//HALF 330K
		BKD0_45_REG = 0xd8;//
		BKD0_46_REG = 0x80;//	
		#endif		
	}
}
void CC_Clr_Int_Set(u8 UCC_DCC)
{
	if(UCC_DCC == UCC)
	{
		BKE6_11_REG &= BIT0_0;  //UCC INT MASK
		BKE6_61_REG |= BIT0_1;	// clear UCC interrupt
		BKE6_61_REG &= BIT0_0;  // clear UCC interrupt
		
		BKD0_8C_REG = 0x60;
		BKD0_8D_REG = 0x0A; // close vconnaA
		BKD0_93_REG = 0x0B; // goodcrc delay
		//type-c int source
		BKD0_95_REG = 0xA8; //interrupt en 0xa8
		BKD0_96_REG = 0x0f;
		BKD0_97_REG = 0x40; //auto goodcrc
		BKD0_99_REG = 0x21; //prswap in& order set
	}
	else
	{
		BKE6_11_REG &= BIT1_0;  //UCC INT MASK
		BKE6_61_REG |= BIT1_1;	// clear UCC interrupt
		BKE6_61_REG &= BIT1_0;  // clear UCC interrupt
		
		BKD0_0C_REG = 0x60;
		BKD0_0D_REG = 0x0A; // close vconnaA
		BKD0_13_REG = 0x0B; // goodcrc delay
		//type-c int source
		BKD0_15_REG = 0xA8; //interrupt en 0xa8
		BKD0_16_REG = 0x0f;
		BKD0_17_REG = 0x40; //auto goodcrc
		BKD0_19_REG = 0x21; //prswap in& order set			
	}		
}

void CC_Debounce_Set(u8 UCC_DCC)
{
	if(UCC_DCC == UCC)
	{
		BKD0_8A_REG = 0x10;//CC DEBAOUNCE WIDTH
//		BKD0_8B_REG = 0x10;//can not be too large
//		BKD0_AA_REG = 0x00;
//		BKD0_AB_REG = 0x80;
		BKD0_A9_REG = 0x10; // cc_det_debounce
		BKD0_AC_REG = 0x62; //Dcc connect soft en
		#if SYSCLK == SYS_CLK_36M //90us
		BKD0_BC_REG = 0x10;//FR_DEBOUNCE_WIDTH[7:0]
		BKD0_BD_REG = 0x0e;//FR_DEBOUNCE_WIDTH[15:8]
		#endif
		BKD0_BE_REG = 0x00;// rd  0x00: 0x01;// rp must follow the 0xd306
	}
	else
	{
		BKD0_0A_REG = 0x10;//CC DEBAOUNCE WIDTH
//		BKD0_0B_REG = 0x10;//can not be too large
//		BKD0_2A_REG = 0x00;
//		BKD0_2B_REG = 0x80;
		BKD0_29_REG = 0x10; // cc_det_debounce
		BKD0_2C_REG = 0x62; //Dcc connect soft en
		#if SYSCLK == SYS_CLK_36M //90us
		BKD0_3C_REG = 0x10;//FR_DEBOUNCE_WIDTH[7:0]
		BKD0_3D_REG = 0x0e;//FR_DEBOUNCE_WIDTH[15:8]
		#endif
		BKD0_3E_REG = 0x00;// rd  0x00: 0x01;// rp must follow the 0xd306
	}
}
void CCRx_PHY_Set(u8 UCC_DCC)
{
	if(UCC_DCC == UCC)
	{
		BKE2_18_REG = 0x10;//ucc rd enable and ip disable
		BKE2_17_REG = 0xaa;//ucc cc detection enable
		BKE2_10_REG = 0x88;//ucc bias enabel
		BKE2_11_REG = 0x10;//ucc abs bias current
		BKE2_12_REG = 0x76;//ucc sys clk invert,rd enable
		BKE2_13_REG = 0x1f;//ucc tx and rx enable
		BKE2_14_REG = 0x01;//ucc rx lvl
		BKE2_15_REG = 0x01;//ucc vbus detect enable
		BKE2_16_REG = 0x04;//ucc vbus off select
	}
	else
	{
		BKE2_28_REG = 0x10;//dcc rd enable and ip disable
		BKE2_20_REG = 0x88;//dcc bias enabel
		BKE2_21_REG = 0x10;//dcc abs bias current
		BKE2_22_REG = 0x76;//dcc sys clk invert,rd enable
		BKE2_23_REG = 0x1f;//dcc tx and rx enable
		BKE2_24_REG = 0x01;//dcc rx lvl
		BKE2_25_REG = 0x01;//dcc vbus detect enable
		BKE2_26_REG = 0x04;//dcc vbus off select
		BKE2_27_REG = 0xaa;//dcc cc detection enable
	}	
}
void GPIO12_UCC_TEST_Set(void)
{
	BKE2_D9_REG = 0x30;//GPIO12 PP*2
	BKE5_80_REG = 0x0b;//test out bit3
	BKE5_EA_REG = 0x04;//test out source select
}
void CC_Logic_Rst(u8 UCC_DCC)
{
	if(UCC_DCC == UCC)
	{
		BKE1_07_REG &= BIT5_0;//UCC logic soft reset
		BKE1_07_REG |= BIT5_1;//UCC logic soft reset
	}
	else if(UCC_DCC == DCC)
	{
		BKE1_07_REG &= BIT7_0;//DCC logic soft reset
		BKE1_07_REG |= BIT7_1;//DCC logic soft reset
	}
}
void DrvUcc_Set_All(void)
{
	GPIO12_UCC_TEST_Set();
//	UCCRX_Rate_Set();		
	CCTX_Rate_Set(UCC);	
	CCTX_Rate_Set(DCC);	
	CC_Clr_Int_Set(UCC);
	CC_Clr_Int_Set(DCC);	
	CC_Debounce_Set(UCC);
	CC_Debounce_Set(DCC);

	CCRx_PHY_Set(UCC);
	CCRx_PHY_Set(DCC);
 
}
#endif
