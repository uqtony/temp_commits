//////////////////////////////////////
//Project:   LT2101
//Filename:  EqScan.c
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#include "Include.h"

u8 SzMainLink_Eq[16] = {0x00,0x09,0x0c,0x0e,0x0f,0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x19,0x1b,0x1f};

void CHIP_DpRx_EqScan(void)
{
    u8 ucEq_ScanCnt;
    u16 szErrCount_lane[4];
	printLT(PRINT_PRIO_HIG, "\nEQ0 = 0x%02bx,0x%02bx",BKDB_F3_REG,BKDB_F4_REG);	
    printLT(PRINT_PRIO_HIG, "\nEQ1 = 0x%02bx,0x%02bx",BKDB_F5_REG,BKDB_F6_REG);	
    printLT(PRINT_PRIO_HIG, "\nEQ2 = 0x%02bx,0x%02bx",BKDB_F7_REG,BKDB_F4_REG);	
    printLT(PRINT_PRIO_HIG, "\nEQ3 = 0x%02bx,0x%02bx",BKDB_F8_REG,BKDB_F9_REG);	
    for(ucEq_ScanCnt = 0;ucEq_ScanCnt< 16;ucEq_ScanCnt++)
    {
        DRV_DpRx_EqMode(FALSE);
        BKDB_7D_REG = 0x00;
        BKDB_7E_REG = SzMainLink_Eq[ucEq_ScanCnt];
        BKDB_7F_REG = 0x00;
        BKDB_80_REG = SzMainLink_Eq[ucEq_ScanCnt];
        BKDB_81_REG = 0x00;
        BKDB_82_REG = SzMainLink_Eq[ucEq_ScanCnt];
        BKDB_82_REG = 0x00;
        BKDB_83_REG = SzMainLink_Eq[ucEq_ScanCnt]; 
        KNL_Delay1ms(1);
        BKDB_A5_REG |= 0x0f;//clear the error
        BKDB_A5_REG &= 0xf0;//clear the error
        KNL_Delay1ms(50);
        szErrCount_lane[0] =  BKDB_CC_REG;
        szErrCount_lane[0] <<= 8;
        szErrCount_lane[0] |= BKDB_CD_REG;
        szErrCount_lane[1] =  BKDB_CE_REG;
        szErrCount_lane[1] <<= 8;
        szErrCount_lane[1] |= BKDB_CF_REG;
        szErrCount_lane[2] =  BKDB_D0_REG;
        szErrCount_lane[2] <<= 8;
        szErrCount_lane[2] |= BKDB_D1_REG;
        szErrCount_lane[3] =  BKDB_D2_REG;
        szErrCount_lane[3] <<= 8;
        szErrCount_lane[3] |= BKDB_D3_REG;
        
        printLT(PRINT_PRIO_HIG, "\nFFF= 0x%02bx,0x%04x,0x%04x,0x%04x,0x%04x", SzMainLink_Eq[ucEq_ScanCnt],szErrCount_lane[0],szErrCount_lane[1],szErrCount_lane[2],szErrCount_lane[3]);
           
        BKDB_7D_REG = 0x00;
        BKDB_7E_REG = SzMainLink_Eq[1];
        BKDB_7F_REG = 0x00;
        BKDB_80_REG = SzMainLink_Eq[1];
        BKDB_81_REG = 0x00;
        BKDB_82_REG = SzMainLink_Eq[1];
        BKDB_82_REG = 0x00;
        BKDB_83_REG = SzMainLink_Eq[1]; 
        BKDB_A5_REG |= 0x0f;//clear the error
        BKDB_A5_REG &= 0xf0;//clear the error
    }
    
}