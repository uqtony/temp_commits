//////////////////////////////////////
//Project:   LT2101
//Filename:  LtType.h
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////
#ifndef _LTTYPE_H
#define _LTTYPE_H

#define IN
#define OUT
#define INOUT

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef enum bool_tag
{
    FALSE = 0,
    TRUE = !FALSE,
}bool;

#define BIT0_1  0x01
#define BIT1_1  0x02
#define BIT2_1  0x04
#define BIT3_1  0x08
#define BIT4_1  0x10
#define BIT5_1  0x20
#define BIT6_1  0x40
#define BIT7_1  0x80

#define BIT0_0  0xFE
#define BIT1_0  0xFD
#define BIT2_0  0xFB
#define BIT3_0  0xF7
#define BIT4_0  0xEF
#define BIT5_0  0xDF
#define BIT6_0  0xBF
#define BIT7_0  0x7F

#define DATA    data
#define BDATA   bdata
#define IDATA   idata
#define PDATA   pdata
#define XDATA   xdata
#define RDATA   code

//state
#define LOW      0
#define HIGH     1
#define OFF      0
#define ON       1
#define LED_ON   0
#define LED_OFF  1
#define ENABLED  1
#define DISABLED 0

//----------------------------------------------------------------------------------------------------------------------------------------------//
#define UART_0   0
#define UART_1   1

#define   TYPEC_IN 					       0
#define   DP_IN 					       1

#define   UFP 					           0
#define   DFP 					           1

#define   UCC  					           0
#define   DCC 					           1

#define   MALE						       0
#define   FEMALE					       1

#define   HPD_LOW						   0
#define   HPD_HIGH				           1

#define   IRQ_LOW						   0
#define   IRQ_HIGH				           1

#define   SYS_CLK_27M                      0
#define   SYS_CLK_36M                      1
#define   SYS_CLK_54M                      2

// link rate
#define   RBR                              6
#define   HBR                              10
#define   HBR2                             20
#define   HBR3                             30

//lane count
#define   ONE_LANE                         1
#define   TWO_LANE                         2
#define   FOUR_LANE                        4

//swing level
#define   LEVEL_0                          0
#define   LEVEL_1                          1
#define   LEVEL_2                          2
#define   LEVEL_3                          3


#define   PTN1080P                         1
#define   PTN4K30                          2
#define   PTN4K60                          3

//VSC DEINED
#define   VSC_RGB                          0
#define   VSC_YCC444                       1
#define   VSC_YCC422                       2
#define   VSC_YCC420                       3

//VSC DEINED
#define   MISC_RGB                         0
#define   MISC_YCC422                      1
#define   MISC_YCC444                      2
#define   MISC_RGB_WIDE                    3

//VSC AND MISC0 DEINED
#define   VESA_8BIT                        1
#define   VESA_10BIT                       2
#define   VESA_12BIT                       3

//VSC DEINED
#define   SRGB                             0
#define   RGB_WIDE_FIXED                   1
#define   RGB_WIDE_FLOATING                2
#define   ADOBE_RGB                        3
#define   DCI_P3                           4
#define   CUSTOM_COLOR                     5
#define   ITUR_BT2020RGB                   6

//VSC DEINED
#define   ITUR_BT601                       0
#define   ITUR_BT709                       1
#define   XVYCC601                         2
#define   XVYCC709                         3
#define   SYCC601                          4
#define   OPYCC601                         5
#define   ITUR_BT2020YCYBCYRC              6
#define   ITUR_BT2020YCBCR                 7

//MISC0 DEINED
#define   LEGCAY_RGB                       0
#define   CTA_RGB                          1
#define   ADOBE_MISC_RGB                   3

//MISC0 DEINED
#define   FIXED_WIDE_RGB                   0
#define   DCI_P3_MISC                      1
#define   FLOATING_WIDE_RGB                2
#define   COLOR_PROFILE                    3

//MISC0 DEINED
#define   XVYCC601_MISC                    0
#define   ITUR_BT601_MISC                  1
#define   XVYCC709_MISC                    2
#define   ITUR_BT709_MISC                  3

//HDMI TX DEFINED
#define   DEEP_8BIT                        8
#define   DEEP_10BIT                       10
#define   DEEP_12BIT                       12

#define   NOT_YCC422                       0
#define   IS_YCC422                        1

#define   DVI_MODE                         0
#define   HDMI_MODE                        1

//mode
#define SW_MODE  0
#define HW_MODE  1
#define FIX_MODE 2

//hdcp
#define HDCP_NOT    0x00
#define HDCP_1X     0x10
#define HDCP_2X     0x20

//frequence meter
#define FREQ_METER_1    1
#define FREQ_METER_2    2

//audio out
#define AUDIO_CLOSE     0x00//close audio out
#define AUDIO_I2S_OUT   0x01//open i2s out
#define AUDIO_SPDIF_OUT 0x02//open spdif out
#define AUDIO_HDMI_OUT  0x04//open hdmi out

//audio in
#define AUDIO_I2S_IN    0x00
#define AUDIO_SPDIF_IN  0x01


typedef struct DpRx
{
    bool ubInput_Type_Sel  :1;
    bool ubSsc_Support  :1;
    bool ubTps4_Support  :1;
    bool ubDynamicRange  :1;
    bool ubVscPkg  :1;
    bool ubIsRxRdy  :1;
    bool ubIsRxVidRdy  :1;
    bool ubIsRxPkgRdy  :1;
    u8 ucRxLinkRate;
    u8 ucRxLinkCount;
    u8 ucPixelEncoding;
    u8 ucColorimetryFormat;
    u8 ucBitDepth;
    u8 ucRxStatus;

} StructDpRx;

typedef struct HdmiTx
{
    bool ubIsHdmi20  :1;
    bool ubIsTxEdidRdy  :1;
    u8 ucszAviPkt[5];
    u8 ucBitDepth;
    u8 ucHdmiVic;
    u8 ucTxStatus;

} StructHdmiTx;

typedef enum
{
    SOFT_RUNNING = 0,  //flow is running
    SOFT_RST_STATE = 1,//flow state reset
}EnumFlowState;

typedef enum
{
    STEP_CONTINUE = 0,//proceed to the next step
    STEP_DEAL_END,    //step end
    STEP_RESET_RX,    //restart rx soft flow
    STEP_RESET_TX,    //restart tx soft flow
    STEP_PORT_LINK = 0xff,//rx and tx link
}EnumFlowStep;

typedef enum
{
    OUT_DISABLE = 0x00,//None pullup or pulldown
    NO_PU_PD =  0x00,//None pullup or pulldown
    OUT_OPD  =  0x01,//Open drain
    OUT_PP_1x = 0x02,//Driver capability X1
    OUT_PP_2x = 0x03,//Driver capability X2
    PD_100K  =  0x04,//100k pulldown
    PU_100K  =  0x08,//100k pullup
    FORBIDDEN = 0x0C,//Forbidden
}EnumIOMode;

typedef enum
{
    GPIO0 = 0,
	GPIO1_MCLK,
	GPIO2_SCLK,
	GPIO3_WS,
	GPIO4_D0_SPDIF,
	GPIO5_D1,
	GPIO6_D2,
	GPIO7_D3,
	GPIO12,
	GPIO13,
	GPIO14,
	GPIO15,
	HTX_CEC,
	GPIO16,
	GPIO17,
	GPIO18_DCAUXN,
	GPIO19_DCAUXP,
	GPIO20_MCLK,
	GPIO21,
	GPIO22,
	DRXHPD,
	GPIO23,
	GPIO24,
	GPIO25,
	GPIO26_SPDIF,
	SPI_MISO,
	SPI_WPB,
	GPIO29_IIC_ADDR,
	GPIO28_MODE_SEL,
	HTX_HPD,
	GPIO27
}EnumGPION;

typedef enum
{
    Dprx_hpd=0,
	Cec_out=0,
	Int_out=1,//1
	Acr_spdif=1,
	Uart_tx_data0=2,//2
	Uart_tx_data1=3,
	Bb_usb_dp_data=4,
	Dcc_vbus_en=5,
	Dcc_vconn1_en=6,
	Dcc_vconn2_en=7,
	Ucc_vbus_en=5,
	Ucc_vconn1_en=6,
	Ucc_vconn2_en=7,
	Blk_test_out_b0,
	Blk_test_out_b1,
	Blk_test_out_b2,
	Blk_test_out_b3,
	Blk_test_out_b4,
	Blk_test_out_b5,
	Blk_test_out_b6,
	Blk_test_out_b7,
}EnumGPIO_Src;

typedef enum
{
    I2C_SLAVE = 0x00,
    I2C_MASTER = 0x10,
    GPIO_MODE = 0x20,
}IO_MODE_E;


typedef enum
{
    PRINT_PRIO_HIG = 0,//High priority
    PRINT_PRIO_MID,    //middle priority
    PRINT_PRIO_LOW,    //low priority
    PRINT_PRIO_TEST,   //test priority
    PRINT_PRIO_MAX,    //max
}EnumPrintLvl;

#endif
