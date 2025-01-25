//////////////////////////////////////
//Project:   LT2101
//Filename:  Lt8711uxd.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _LT8711UXD_H
#define _LT8711UXD_H
#include "LtType.h"

#if LT8711UXD == ENABLED

//uart rx & tx
#define UART_TX_PIN        GPIO_24
#define UART_RX_PIN        GPIO_22

#define          Source_UVbus_Ctrl(output_value)  ((output_value==1)?(BKE2_ED_REG |= 0x04):(BKE2_ED_REG &= 0xFB))//gpio14
#define          Adapter_DVbus_Ctrl(output_value) ((output_value==1)?(BKE2_ED_REG |= 0x01):(BKE2_ED_REG &= 0xFE))//gpio15


#define          DPRX_LINK_RATE                HBR2                //HBR3/HBR2/HBR/RBR
#define          DPRX_LINK_COUNT               TWO_LANE           //FOUR_LANE/TWO_LANE/ONE_LANE
#define          DPRX_TPS4_SUPPORT_EN          DISABLED           //ENABLED/DISABLED
#define          DPRX_SSC_SUPPORT_EN           DISABLED           //ENABLED/DISABLED
#define          DPRX_SWING_MIN_LEVEL          LEVEL_1            //LEVEL_0/LEVEL_1/LEVEL_2/LEVEL_3

#define          HDMITX_EDID_READ_EN           ENABLED            //ENABLED/DISABLED
#define          HDMITX_EDID_PRINT_EN          ENABLED            //ENABLED/DISABLED


#define          TYPECRX_EN                     ENABLED            //ENABLED/DISABLED
#define          TYPEC_PRSWAP_EN                ENABLED            //ENABLED/DISABLED
#define          TYPEC_DRSWAP_EN                ENABLED            //ENABLED/DISABLED
#define          TYPEC_FRSWAP_EN                DISABLED           //ENABLED/DISABLED
#define          ET_2							1					
#define			 PD_PPS_EN						1
#define          TX_CEC_EN						1


extern StructDpRx     g_stDpRx;
extern StructHdmiTx   g_stHdmiTx;

extern void CHIP_Var_PowerOn(void);
extern void CHIP_Main_LT8711uxdScan(void);

#endif
#endif


