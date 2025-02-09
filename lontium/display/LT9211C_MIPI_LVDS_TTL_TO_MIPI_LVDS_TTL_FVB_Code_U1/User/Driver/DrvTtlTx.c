/******************************************************************************
  * @project: LT9211C
  * @file: DrvTtlTx.c
  * @author: xding
  * @company: LONTIUM COPYRIGHT and CONFIDENTIAL
  * @date: 2023.01.29
/******************************************************************************/

#include "include.h"
#if ((LT9211C_MODE_SEL == LVDS_IN_TTL_OUT)||(LT9211C_MODE_SEL == MIPI_IN_TTL_OUT)||(LT9211C_MODE_SEL == TTL_IN_TTL_OUT))

void Drv_TtlTxHalfBit_Set()
{
    #if   ((TTLTX_OUTPUT_MODE == OUTPUT_YCBCR422_8BIT) || (TTLTX_OUTPUT_MODE == OUTPUT_YCBCR422_10BIT) || (TTLTX_OUTPUT_MODE == OUTPUT_YCBCR422_12BIT))
        #define     TTLTX_HALF_BIT_MODE         ENABLED
    #elif ((TTLTX_OUTPUT_MODE == OUTPUT_BT656_8BIT)    || (TTLTX_OUTPUT_MODE == OUTPUT_BT656_10BIT)    || (TTLTX_OUTPUT_MODE == OUTPUT_BT656_12BIT))
        #define     TTLTX_HALF_BIT_MODE         ENABLED
    #elif ((TTLTX_OUTPUT_MODE == OUTPUT_BT1120_8BIT)   || (TTLTX_OUTPUT_MODE == OUTPUT_BT1120_10BIT)   || (TTLTX_OUTPUT_MODE == OUTPUT_BT1120_12BIT))
        #define     TTLTX_HALF_BIT_MODE         ENABLED
    #else
        #define     TTLTX_HALF_BIT_MODE         DISABLED
    #endif
}

void Drv_TtlTxSyncInter_Set()
{
    #if   ((TTLTX_OUTPUT_MODE == OUTPUT_BT656_8BIT)     || (TTLTX_OUTPUT_MODE == OUTPUT_BT656_10BIT)    || (TTLTX_OUTPUT_MODE == OUTPUT_BT656_12BIT))
        #define     TTLTX_SYNC_INTER_FORMAT     BT656
    #elif ((TTLTX_OUTPUT_MODE == OUTPUT_BT1120_8BIT)    || (TTLTX_OUTPUT_MODE == OUTPUT_BT1120_10BIT)   || (TTLTX_OUTPUT_MODE == OUTPUT_BT1120_12BIT))
        #define     TTLTX_SYNC_INTER_FORMAT     BT1120
    #elif ((TTLTX_OUTPUT_MODE == OUTPUT_BTA_T1004_16BIT)|| (TTLTX_OUTPUT_MODE == OUTPUT_BTA_T1004_20BIT)|| (TTLTX_OUTPUT_MODE == OUTPUT_BTA_T1004_24BIT))
        #define     TTLTX_SYNC_INTER_FORMAT     BTA_T1004
    #elif ((TTLTX_OUTPUT_MODE == OUTPUT_BT1120_16BIT)   || (TTLTX_OUTPUT_MODE == OUTPUT_BT1120_20BIT)   || (TTLTX_OUTPUT_MODE == OUTPUT_BT1120_24BIT))
        #define     TTLTX_SYNC_INTER_FORMAT     BT1120
    #endif
}

void Drv_TtlTxDdrMode_Set()
{
    #if TTLTX_MODE == SDR
        #define     TTLTX_DATARATE_MODE         SDR
        #define     TTLTX_HALF_CLOCK_MODE       DISABLED
        #define     TTLTX_HALF_WIDTH_MODE       DISABLED
    #elif TTLTX_MODE == DDR
        #define     TTLTX_DATARATE_MODE         DDR
        #define     TTLTX_HALF_CLOCK_MODE       ENABLED
        #define     TTLTX_HALF_WIDTH_MODE       DISABLED
    #elif TTLTX_MODE == DPI
        #define     TTLTX_DATARATE_MODE         DDR
        #define     TTLTX_HALF_CLOCK_MODE       DISABLED
        #define     TTLTX_HALF_WIDTH_MODE       ENABLED
    #endif
}

void Drv_TTlTxPhy_Poweron()
{
    HDMI_WriteI2C_Byte(0xff,0x82);
    HDMI_WriteI2C_Byte(0x64,0xff); //ff
    HDMI_WriteI2C_Byte(0x65,0x80); //dll phase
    
    #if TTLTX_DATARATE_MODE == DDR
        HDMI_WriteI2C_Byte(0x63,0x1b); //dll reset, ddr on
        HDMI_WriteI2C_Byte(0x63,0x3b); //dll release
        HDMI_WriteI2C_Byte(0x63,0x3f); //phdly_en on
        #if TTLTX_HALF_CLOCK_MODE == ENABLED
            LTLog(LOG_INFO,"DDR Half Clock Mode:    Enable");
        #endif
        #if TTLTX_HALF_WIDTH_MODE == ENABLED
            //desscpll set
            HDMI_WriteI2C_Byte(0x29,HDMI_ReadI2C_Byte(0x29) | 0x10); //rg_desscpll_phclk_en = 1
            //div set: 822c[5:4] same as 822f[1:0]
            if(HDMI_ReadI2C_Byte(0x2f) & 0x01)
            {
                HDMI_WriteI2C_Byte(0x2c,HDMI_ReadI2C_Byte(0x2c) | 0x10);
            }
            if(HDMI_ReadI2C_Byte(0x2f) & 0x02)
            {
                HDMI_WriteI2C_Byte(0x2c,HDMI_ReadI2C_Byte(0x2c) | 0x20);
            }
            //div set: 822d[3:2] same as 822c[1:0]
            if(HDMI_ReadI2C_Byte(0x2c) & 0x01)
            {
                HDMI_WriteI2C_Byte(0x2d,HDMI_ReadI2C_Byte(0x2d) | 0x04);
            }
            if(HDMI_ReadI2C_Byte(0x2c) & 0x02)
            {
                HDMI_WriteI2C_Byte(0x2d,HDMI_ReadI2C_Byte(0x2d) | 0x08);
            }
            HDMI_WriteI2C_Byte(0x2b,HDMI_ReadI2C_Byte(0x2b) | 0x01); //dessc double pix clock output
            LTLog(LOG_INFO,"DDR Half Width Mode:    Enable");
        #endif
    #else
        HDMI_WriteI2C_Byte(0x63,0x17); //dll reset
        HDMI_WriteI2C_Byte(0x63,0x37); //dll release
    #endif
    
    #if TTLTX_HALF_BIT_MODE == ENABLED
        //desscpll set
        HDMI_WriteI2C_Byte(0x29,HDMI_ReadI2C_Byte(0x29) | 0x10); //rg_desscpll_phclk_en = 1
        //div set: 822c[5:4] same as 822f[1:0]
        if(HDMI_ReadI2C_Byte(0x2f) & 0x01)
        {
            HDMI_WriteI2C_Byte(0x2c,HDMI_ReadI2C_Byte(0x2c) | 0x10);
        }
        if(HDMI_ReadI2C_Byte(0x2f) & 0x02)
        {
            HDMI_WriteI2C_Byte(0x2c,HDMI_ReadI2C_Byte(0x2c) | 0x20);
        }
        //div set: 822d[3:2] same as 822c[1:0]
        if(HDMI_ReadI2C_Byte(0x2c) & 0x01)
        {
            HDMI_WriteI2C_Byte(0x2d,HDMI_ReadI2C_Byte(0x2d) | 0x04);
        }
        if(HDMI_ReadI2C_Byte(0x2c) & 0x02)
        {
            HDMI_WriteI2C_Byte(0x2d,HDMI_ReadI2C_Byte(0x2d) | 0x08);
        }
        HDMI_WriteI2C_Byte(0x2b,HDMI_ReadI2C_Byte(0x2b) | 0x01); //dessc double pix clock output
        LTLog(LOG_INFO,"Half Bit Mode:    Enable");
    #endif
}

void Drv_TtlTxMapping_Set()
{
    HDMI_WriteI2C_Byte(0xff,0x86);
    
    switch(TTLTX_OUTPUT_MODE)
    {
        case OUTPUT_RGB888:
            //RGB swap case
            #if 0   //output RGB  R: D23->D16    G: D15->D8    B:D7->D0    
                HDMI_WriteI2C_Byte(0xa8,0x00);
            #endif
            #if 0   //output RBG  R: D23->D16    B: D15->D8    G:D7->D0    
                HDMI_WriteI2C_Byte(0xa8,0x30);
            #endif
            #if 0   //output GRB  G: D23->D16    R: D15->D8    B:D7->D0    
                HDMI_WriteI2C_Byte(0xa8,0x40);
            #endif
            #if 0   //output GBR  G: D23->D16    B: D15->D8    R:D7->D0    
                HDMI_WriteI2C_Byte(0xa8,0x50);
            #endif
            #if 0   //output BRG  B: D23->D16    R: D15->D8    G:D7->D0    
                HDMI_WriteI2C_Byte(0xa8,0x60);
            #endif
            #if 1   //output BGR  B: D23->D16    G: D15->D8    R:D7->D0    
                HDMI_WriteI2C_Byte(0xa8,0x70);
            #endif
            //RGB high/low swap case
            #if 0   //output BGR  B: D23->D16    G: D15->D8    R:D0->D7    
                HDMI_WriteI2C_Byte(0xa8,0x71);
            #endif
            #if 0   //output BGR  B: D23->D16    G: D8->D15    R:D7->D0    
                HDMI_WriteI2C_Byte(0xa8,0x72);
            #endif
            #if 0   //output BGR  B: D16->D23    G: D15->D8    R:D7->D0    
                HDMI_WriteI2C_Byte(0xa8,0x74);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    RGB888");
            break;
            
        case OUTPUT_RGB666:
            //RGB swap case
            #if 1   //output RGB  R: D23->D18    G: D15->D10    B:D7->D2    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x00);
            #endif
            #if 0   //output RBG  R: D23->D18    B: D15->D10    G:D7->D2    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x30);
            #endif
            #if 0   //output GRB  G: D23->D18    R: D15->D10    B:D7->D2    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x40);
            #endif
            #if 0   //output GBR  G: D23->D18    B: D15->D10    R:D7->D2    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x50);
            #endif
            #if 0   //output BRG  B: D23->D18    R: D15->D10    G:D7->D2    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x60);
            #endif
            #if 0   //output BGR  B: D23->D18    G: D15->D10    R:D7->D2    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x70);
            #endif
            //RGB high/low swap case
            #if 0   //output BGR  B: D23->D18    G: D15->D10    R:D0->D5    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x71);
            #endif
            #if 0   //output BGR  B: D23->D18    G: D8->D13    R:D7->D2     
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x72);
            #endif
            #if 0   //output BGR  B: D16->D21    G: D15->D10    R:D7->D2    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x74);
            #endif
            //RGB666 swap case
            #if 0   //output BGR  B: D17->D12    G: D11->D6    R:D5->D0     
                HDMI_WriteI2C_Byte(0xa7,0x05);
                HDMI_WriteI2C_Byte(0xa8,0x70);
            #endif
            #if 0   //output BGR  B: D23->D18    G: D17->D12    R:D11->D6   
                HDMI_WriteI2C_Byte(0xa7,0x04);
                HDMI_WriteI2C_Byte(0xa8,0x70);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    RGB666");
            break;
            
        case OUTPUT_RGB565:
            //RGB swap case
            #if 0   //output RGB  R: D23->D19    G: D15->D10    B:D7->D3    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x00);
            #endif
            #if 0   //output RBG  R: D23->D19    B: D15->D11    G:D7->D2    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x30);
            #endif
            #if 0   //output GRB  G: D23->D18    R: D15->D11    B:D7->D3    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x40);
            #endif
            #if 0   //output GBR  G: D23->D18    B: D15->D11    R:D7->D3    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x50);
            #endif
            #if 0   //output BRG  B: D23->D19    R: D15->D11    G:D7->D2    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x60);
            #endif
            #if 0   //output BGR  B: D23->D19    G: D15->D10    R:D7->D3    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x70);
            #endif
            //RGB high/low swap case
            #if 0   //output BGR  B: D23->D19    G: D15->D10    R:D0->D4    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x71);
            #endif
            #if 0   //output BGR  B: D23->D19    G: D8->D13    R:D7->D3   
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x72);
            #endif
            #if 0   //output BGR  B: D16->D20    G: D15->D10    R:D7->D3  
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x74);
            #endif
            //RGB565 case
            #if 1   //output RGB  B: D15->D11    G: D10->D5    R: D4->D0  
                HDMI_WriteI2C_Byte(0xa7,0x07);
                HDMI_WriteI2C_Byte(0xa8,0x70);
            #endif
            #if 0   //output RGB  B: D23->D19    G: D18->D13    R: D12->D8
                HDMI_WriteI2C_Byte(0xa7,0x06);
                HDMI_WriteI2C_Byte(0xa8,0x70);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    RGB565");
            break;
        
        case OUTPUT_YCBCR444:
            //RGB swap case
            #if 1   //output YUV  V: D23->D16    Y: D15->D8    U:D7->D0   
                HDMI_WriteI2C_Byte(0xa8,0x00);
            #endif
            #if 0   //output YUV  V: D23->D16    U: D15->D8    Y:D7->D0   
                HDMI_WriteI2C_Byte(0xa8,0x30);
            #endif
            #if 0   //output YUV  Y: D23->D16    V: D15->D8    U:D7->D0   
                HDMI_WriteI2C_Byte(0xa8,0x40);
            #endif
            #if 0   //output YUV  Y: D23->D16    U: D15->D8    V:D7->D0   
                HDMI_WriteI2C_Byte(0xa8,0x50);
            #endif
            #if 0   //output YUV  U: D23->D16    V: D15->D8    Y:D7->D0   
                HDMI_WriteI2C_Byte(0xa8,0x60);
            #endif
            #if 0   //output YUV  U: D23->D16    Y: D15->D8    V:D7->D0   
                HDMI_WriteI2C_Byte(0xa8,0x70);
            #endif
            //RGB high/low swap case
            #if 0   //output YUV  U: D23->D16    Y: D15->D8    V:D0->D7   
                HDMI_WriteI2C_Byte(0xa8,0x71);
            #endif
            #if 0   //output YUV  U: D23->D16    Y: D8->D15    V:D7->D0   
                HDMI_WriteI2C_Byte(0xa8,0x72);
            #endif
            #if 0   //output YUV  U: D16->D23    Y: D15->D8    V:D7->D0   
                HDMI_WriteI2C_Byte(0xa8,0x74);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    YCBCR444");
            break;
        
        case OUTPUT_YCBCR422_8BIT:
            LTLog(LOG_INFO,"TTLTx Output Mode:    YCBCR422_8BIT");
            break;
        
        case OUTPUT_YCBCR422_10BIT:
            LTLog(LOG_INFO,"TTLTx Output Mode:    YCBCR422_10BIT");
            break;
        
        case OUTPUT_YCBCR422_12BIT:
            LTLog(LOG_INFO,"TTLTx Output Mode:    YCBCR422_12BIT");
            break;
        
        case OUTPUT_YCBCR422_16BIT:
            //RGB swap case
            #if 1   //output YUV  C: D23->D16    Y: D15->D8 
                HDMI_WriteI2C_Byte(0xa8,0x00);
            #endif
            #if 0   //output YUV  C: D23->D16    Y:D7->D0   
                HDMI_WriteI2C_Byte(0xa8,0x30);
            #endif
            #if 0   //output YUV  Y: D23->D16    C: D15->D8 
                HDMI_WriteI2C_Byte(0xa8,0x40);
            #endif
            #if 0   //output YUV  Y: D23->D16    C:D7->D0   
                HDMI_WriteI2C_Byte(0xa8,0x50);
            #endif
            #if 0   //output YUV  C: D15->D8    Y:D7->D0    
                HDMI_WriteI2C_Byte(0xa8,0x60);
            #endif
            #if 0   //output YUV  Y: D15->D8    C:D7->D0    
                HDMI_WriteI2C_Byte(0xa8,0x70);
            #endif
            //RGB high/low swap case
            #if 0   //output YUV  Y: D15->D8    C:D0->D7    
                HDMI_WriteI2C_Byte(0xa8,0x71);
            #endif
            #if 0   //output YUV  Y: D8->D15    C:D7->D0    
                HDMI_WriteI2C_Byte(0xa8,0x72);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    YCBCR422_16BIT");
            break;
        
        case OUTPUT_YCBCR422_20BIT:
            //20Bit swap case
            #if 1  //output YUV  Y: D23->D14    C:D13->D4    
                HDMI_WriteI2C_Byte(0xa7,0x02);
                HDMI_WriteI2C_Byte(0xa8,0x40);
            #endif
            #if 0  //output YUV  Y: D19->D10    C:D9->D0    
                HDMI_WriteI2C_Byte(0xa7,0x03);
                HDMI_WriteI2C_Byte(0xa8,0x40);
            #endif
            //RGB swap case
            #if 0  //output YUV  Y: D15->D8  D19->D18    C:D8->D0  D23->D22    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x70);
            #endif
            #if 0  //output YUV  Y: D23->D16  D3->D2    C:D15->D6   
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x40);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    YCBCR422_20BIT");
            break;
        
        case OUTPUT_YCBCR422_24BIT:
            //24Bit swap case
            #if 1  //output YUV  Y: D23->D12    C:D11->D0   
                HDMI_WriteI2C_Byte(0xa7,0x01);
                HDMI_WriteI2C_Byte(0xa8,0x40);
            #endif
            #if 0  //output YUV  C: D23->D12    Y:D11->D0  
                HDMI_WriteI2C_Byte(0xa7,0x01);
                HDMI_WriteI2C_Byte(0xa8,0x00);
            #endif
            //RGB swap case
            #if 0  //output YUV  Y: D15->D8  D19->D16    C:D7->D0  D23->D20    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x70);
            #endif
            #if 0  //output YUV  Y: D23->D16  D3->D0    C:D15->D4    
                HDMI_WriteI2C_Byte(0xa7,0x00);
                HDMI_WriteI2C_Byte(0xa8,0x40);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    YCBCR422_24BIT");
            break;
        
        case OUTPUT_BT656_8BIT:
            //RGB swap case
            #if 0  //output YUV  D7-D0   
                HDMI_WriteI2C_Byte(0xa9,0x07);
            #endif
            #if 1  //output YUV  D15-D8    
                HDMI_WriteI2C_Byte(0xa9,0x09);
            #endif
            #if 0  //output YUV  D23-D16   
                HDMI_WriteI2C_Byte(0xa9,0x40);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    BT656_8BIT");
            break;
        
        case OUTPUT_BT656_10BIT:
            //YC swap, 20Bit swap case
            #if 0  //output YUV  D9-D0    
                HDMI_WriteI2C_Byte(0xa9,0x05);
            #endif
            #if 0  //output YUV  D13-D4    
                HDMI_WriteI2C_Byte(0xa9,0x04);
            #endif
            #if 0  //output YUV  D19-D10    
                HDMI_WriteI2C_Byte(0xa9,0x45);
            #endif
            #if 0  //output YUV  D23-D14    
                HDMI_WriteI2C_Byte(0xa9,0x40);
            #endif
            //other case
            #if 1  //output YUV  D15-D6    
                HDMI_WriteI2C_Byte(0xa9,0x08);
            #endif
            #if 0  //output YUV  D11-D2 
                HDMI_WriteI2C_Byte(0xa9,0x00);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    BT656_10BIT");
            break;
        
        case OUTPUT_BT656_12BIT:
            //YC swap case
            #if 0  //output YUV  D11-D0   
                HDMI_WriteI2C_Byte(0xa9,0x00);
            #endif
            #if 0  //output YUV  D23-D12  
                HDMI_WriteI2C_Byte(0xa9,0x40);
            #endif
            //other case
            #if 1  //output YUV  D15-D4    
                HDMI_WriteI2C_Byte(0xa9,0x01);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    BT656_12BIT");
            break;
        
        case OUTPUT_BT1120_8BIT:
            //RGB swap case
            #if 0  //output YUV  D7-D0   
                HDMI_WriteI2C_Byte(0xa9,0x07);
            #endif
            #if 1  //output YUV  D15-D8    
                HDMI_WriteI2C_Byte(0xa9,0x09);
            #endif
            #if 0  //output YUV  D23-D16   
                HDMI_WriteI2C_Byte(0xa9,0x40);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    BT1120_8BIT");
            break;
        
        case OUTPUT_BT1120_10BIT:
            //YC swap, 20Bit swap case
            #if 0  //output YUV  D9-D0    
                HDMI_WriteI2C_Byte(0xa9,0x05);
            #endif
            #if 0  //output YUV  D13-D4    
                HDMI_WriteI2C_Byte(0xa9,0x04);
            #endif
            #if 0  //output YUV  D19-D10    
                HDMI_WriteI2C_Byte(0xa9,0x45);
            #endif
            #if 0  //output YUV  D23-D14    
                HDMI_WriteI2C_Byte(0xa9,0x40);
            #endif
            //other case
            #if 1  //output YUV  D15-D6    
                HDMI_WriteI2C_Byte(0xa9,0x08);
            #endif
            #if 0  //output YUV  D11-D2 
                HDMI_WriteI2C_Byte(0xa9,0x00);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    BT1120_10BIT");
            break;
        
        case OUTPUT_BT1120_12BIT:
            //YC swap case
            #if 0  //output YUV  D11-D0   
                HDMI_WriteI2C_Byte(0xa9,0x00);
            #endif
            #if 0  //output YUV  D23-D12  
                HDMI_WriteI2C_Byte(0xa9,0x40);
            #endif
            //other case
            #if 1  //output YUV  D15-D4    
                HDMI_WriteI2C_Byte(0xa9,0x01);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    BT1120_12BIT");
            break;
        
        case OUTPUT_BTA_T1004_16BIT:
            //RGB swap case
            #if 0  //output YUV  C: D7-D0    Y: D15-D8    
                HDMI_WriteI2C_Byte(0xa9,0x47);
            #endif
            #if 0  //output YUV  Y: D7-D0    C: D15-D8    
                HDMI_WriteI2C_Byte(0xa9,0x07);
            #endif
            #if 0  //output YUV  Y: D23-D16    C: D15-D8  
                HDMI_WriteI2C_Byte(0xa9,0x46);
            #endif
            #if 1  //output YUV  C: D23-D16    Y: D15-D8  
                HDMI_WriteI2C_Byte(0xa9,0x06);
            #endif
            //other case
            #if 0  //output YUV  C: D23-D16    Y: D11-D4    
                HDMI_WriteI2C_Byte(0xa9,0x00);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    BTA_T1004_16BIT");
            break;
        
        case OUTPUT_BTA_T1004_20BIT:
            //YC swap, 20Bit swap case
            #if 0  //output YUV  C: D9-D0    Y: D19-D10 
                HDMI_WriteI2C_Byte(0xa9,0x45);
            #endif
            #if 0  //output YUV  Y: D9-D0    C: D19-D10 
                HDMI_WriteI2C_Byte(0xa9,0x05);
            #endif
            #if 0  //output YUV  Y: D23-D14    C: D13-D4
                HDMI_WriteI2C_Byte(0xa9,0x44);
            #endif
            #if 0  //output YUV  C: D23-D14    Y: D13-D4
                HDMI_WriteI2C_Byte(0xa9,0x04);
            #endif
            //other case
            #if 1 //output YUV  C: D23-D14    Y: D11-D2    
                HDMI_WriteI2C_Byte(0xa9,0x00);
            #endif
            #if 0 //output YUV  Y: D23-D14    C: D11-D2    
                HDMI_WriteI2C_Byte(0xa9,0x40);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    BTA_T1004_20BIT");
            break;
        
        case OUTPUT_BTA_T1004_24BIT:
            //YC swap case 
            #if 0 //output YUV  Y: D23-D12    C: D11-D0   
                HDMI_WriteI2C_Byte(0xa9,0x40);
            #endif
            #if 1 //output YUV  C: D23-D12    Y: D11-D0   
                HDMI_WriteI2C_Byte(0xa9,0x00);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    BTA_T1004_24BIT");
            break;
        
        case OUTPUT_BT1120_16BIT: 
            //RGB swap case
            #if 0  //output YUV  C: D7-D0    Y: D15-D8    
                HDMI_WriteI2C_Byte(0xa9,0x47);
            #endif
            #if 0  //output YUV  Y: D7-D0    C: D15-D8    
                HDMI_WriteI2C_Byte(0xa9,0x07);
            #endif
            #if 0  //output YUV  Y: D23-D16    C: D15-D8  
                HDMI_WriteI2C_Byte(0xa9,0x46);
            #endif
            #if 1  //output YUV  C: D23-D16    Y: D15-D8  
                HDMI_WriteI2C_Byte(0xa9,0x06);
            #endif
            //other case
            #if 0  //output YUV  C: D23-D16    Y: D11-D4    
                HDMI_WriteI2C_Byte(0xa9,0x00);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    BT1120_16BIT");
            break;
        
        case OUTPUT_BT1120_20BIT:
            //YC swap, 20Bit swap case
            #if 0  //output YUV  C: D9-D0    Y: D19-D10 
                HDMI_WriteI2C_Byte(0xa9,0x45);
            #endif
            #if 0  //output YUV  Y: D9-D0    C: D19-D10 
                HDMI_WriteI2C_Byte(0xa9,0x05);
            #endif
            #if 0  //output YUV  Y: D23-D14    C: D13-D4
                HDMI_WriteI2C_Byte(0xa9,0x44);
            #endif
            #if 0  //output YUV  C: D23-D14    Y: D13-D4
                HDMI_WriteI2C_Byte(0xa9,0x04);
            #endif
            //other case
            #if 1 //output YUV  C: D23-D14    Y: D11-D2    
                HDMI_WriteI2C_Byte(0xa9,0x00);
            #endif
            #if 0 //output YUV  Y: D23-D14    C: D11-D2    
                HDMI_WriteI2C_Byte(0xa9,0x40);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    BT1120_20BIT");
            break;
        
        case OUTPUT_BT1120_24BIT:
            //YC swap case 
            #if 0 //output YUV  Y: D23-D12    C: D11-D0   
                HDMI_WriteI2C_Byte(0xa9,0x40);
            #endif
            #if 1 //output YUV  C: D23-D12    Y: D11-D0   
                HDMI_WriteI2C_Byte(0xa9,0x00);
            #endif
            LTLog(LOG_INFO,"TTLTx Output Mode:    BT1120_24BIT");
            break;
    }
}

void Drv_TtlTx_BtTiming_Set()
{
    u16 vss,hss;
    
    vss = g_stVidChk.usVs + g_stVidChk.usVbp;
    hss = g_stVidChk.usHs + g_stVidChk.usHbp;
    HDMI_WriteI2C_Byte(0xb6,(u8)(g_stVidChk.usHtotal>>8));
	HDMI_WriteI2C_Byte(0xb7,(u8)(g_stVidChk.usHtotal));  
    HDMI_WriteI2C_Byte(0xb8,(u8)(g_stVidChk.usHact>>8));
	HDMI_WriteI2C_Byte(0xb9,(u8)(g_stVidChk.usHact)); 
    HDMI_WriteI2C_Byte(0xba,(u8)(hss>>8));
	HDMI_WriteI2C_Byte(0xbb,(u8)(hss)); 
    HDMI_WriteI2C_Byte(0xbc,(u8)(g_stVidChk.usVact>>8));
	HDMI_WriteI2C_Byte(0xbd,(u8)(g_stVidChk.usVact)); 
    HDMI_WriteI2C_Byte(0xbe,(u8)(vss>>8));
	HDMI_WriteI2C_Byte(0xbf,(u8)(vss));
    
    LTLog(LOG_INFO,"hss, hact, htotal = %d %d %d",hss, g_stVidChk.usHact, g_stVidChk.usHtotal);
	LTLog(LOG_INFO,"vss, vact, vtotal = %d %d %d",vss, g_stVidChk.usVact, g_stVidChk.usVtotal);
}

void Drv_TtlTxDig_Set()
{
    HDMI_WriteI2C_Byte(0xff,0x86);
    HDMI_WriteI2C_Byte(0xa5,0x00);
    HDMI_WriteI2C_Byte(0xa8,0x00);
    HDMI_WriteI2C_Byte(0xa9,0x00);
    HDMI_WriteI2C_Byte(0xaf,0x3f);
    

    #if TTLTX_SYNC_INTER_MODE == ENABLED
        Drv_TtlTx_BtTiming_Set();
        #if TTLTX_HALF_BIT_MODE == ENABLED
            HDMI_WriteI2C_Byte(0xa5,HDMI_ReadI2C_Byte(0xa5) | 0x04); //8bit embedded enable
            LTLog(LOG_INFO,"Sync Mode:    8Bit Embedded");
        #else
            HDMI_WriteI2C_Byte(0xa5,HDMI_ReadI2C_Byte(0xa5) | 0x02); //16bit embedded enable
            LTLog(LOG_INFO,"Sync Mode:    16Bit Embedded");
        #endif
        #if TTLTX_SYNC_INTER_FORMAT == BT1120
            HDMI_WriteI2C_Byte(0xa5,HDMI_ReadI2C_Byte(0xa5) | 0x01); //BT1120 enable
            LTLog(LOG_INFO,"Embedded Format:    BT1120");
        #elif TTLTX_SYNC_INTER_FORMAT == BTA_T1004
            LTLog(LOG_INFO,"Embedded Format:    BTA_T1004");
        #elif TTLTX_SYNC_INTER_FORMAT == BT656
            LTLog(LOG_INFO,"Embedded Format:    BT656");
        #endif
        #if TTLTX_VSYNC_POLARITY == PLUS
            HDMI_WriteI2C_Byte(0xa5,HDMI_ReadI2C_Byte(0xa5) | 0x20); //vsync polarity
            LTLog(LOG_INFO,"Vsync Polarity:    plus");
        #else
            HDMI_WriteI2C_Byte(0xa5,HDMI_ReadI2C_Byte(0xa5) & 0xdf); //vsync polarity
            LTLog(LOG_INFO,"Vsync Polarity:    minus");
        #endif
        #if TTLTX_HSYNC_POLARITY == PLUS
            HDMI_WriteI2C_Byte(0xa5,HDMI_ReadI2C_Byte(0xa5) | 0x10); //hsync polarity
            LTLog(LOG_INFO,"Hsync Polarity:    plus");
        #else
            HDMI_WriteI2C_Byte(0xa5,HDMI_ReadI2C_Byte(0xa5) & 0xef); //hsync polarity
            LTLog(LOG_INFO,"Hsync Polarity:    minus");
        #endif
        #if TTLTX_VIDEO_FORMAT == I_FORMAT
            HDMI_WriteI2C_Byte(0xa5,HDMI_ReadI2C_Byte(0xa5) | 0x08); //Interlace format
            LTLog(LOG_INFO,"Video Format:    I Format");
        #else
            HDMI_WriteI2C_Byte(0xa5,HDMI_ReadI2C_Byte(0xa5) & 0xf7); //Progressive format
            LTLog(LOG_INFO,"Video Format:    P Format");
        #endif
    #endif

    
    #if TTLTX_DATARATE_MODE == DDR
        #if TTLTX_HALF_WIDTH_MODE == ENABLED
            HDMI_WriteI2C_Byte(0xaf,HDMI_ReadI2C_Byte(0xaf) | 0x80); //DDR Half Width Mode Enable
            #if 0
            HDMI_WriteI2C_Byte(0xaf,HDMI_ReadI2C_Byte(0xaf) | 0x40); //high 12 Bit first
            LTLog(LOG_INFO,"DDR Trans Mode:    High 12Bit First");
            #else
            HDMI_WriteI2C_Byte(0xaf,HDMI_ReadI2C_Byte(0xaf) & 0xbf); //low 12 Bit first
            LTLog(LOG_INFO,"DDR Trans Mode:    Low 12Bit First");
            #endif
        #endif
    #endif
    
    HDMI_WriteI2C_Byte(0xff,0x81);
    HDMI_WriteI2C_Byte(0x0d,0x7d); //ttl tx reset
    HDMI_WriteI2C_Byte(0x0d,0x7f); //ttl tx release
}

void Drv_CscSet_ForTtlTx()
{
    #if TTLTX_COLORSPACE == RGB
        LTLog(LOG_INFO,"Color Format:    RGB");
    #elif TTLTX_COLORSPACE == YUV444
        HDMI_WriteI2C_Byte(0xff,0x86);
        if((HDMI_ReadI2C_Byte(0x87) & 0x10) == 0)
        {
            HDMI_WriteI2C_Byte(0x85,HDMI_ReadI2C_Byte(0x85) | 0x10);
        }
        else
        {
            HDMI_WriteI2C_Byte(0x87,HDMI_ReadI2C_Byte(0x87) & 0xef);
        }
        LTLog(LOG_INFO,"Color Format:    YUV444");
    #elif TTLTX_COLORSPACE == YUV422
        HDMI_WriteI2C_Byte(0xff,0x86);
        if((HDMI_ReadI2C_Byte(0x87) & 0x10) == 0)
        {
            HDMI_WriteI2C_Byte(0x85,HDMI_ReadI2C_Byte(0x85) | 0x10);
        }
        else
        {
            HDMI_WriteI2C_Byte(0x87,HDMI_ReadI2C_Byte(0x87) & 0xef);
        }
        if((HDMI_ReadI2C_Byte(0x86) & 0x04) == 0)
        {
            HDMI_WriteI2C_Byte(0x86,HDMI_ReadI2C_Byte(0x86) | 0x40);
        }
        else
        {
            HDMI_WriteI2C_Byte(0x86,HDMI_ReadI2C_Byte(0x86) & 0xfb);
        }
        LTLog(LOG_INFO,"Color Format:    YUV422");
    #endif
}

//Drv_TtlTxPhase_Set函数：调节ttltx IO时钟的相位
void Drv_TtlTxPhase_Set()
{
    //pclk_khz: ttltx参考的pix_clk
    //io_dclk_khz: ttltx实际通过IO输出到pin脚的dclk
    //ucphase：DLL 相位 范围0~7
    u32 pclk_khz;
    u32 io_dclk_khz;
    u8 ucphase;
    
    //参考时钟pix_clk选择: 
        //ad_desscpll_pix_clk（pattern全部模式/mipirx全部模式/lvdsrx的dessc模式）   
        //ad_rxpll_pix_clk（ttlrx全部模式/lvdsrx的非dessc模式）
    #if LT9211C_MODE_SEL == MIPI_IN_TTL_OUT
        pclk_khz = Drv_System_FmClkGet(AD_DESSCPLL_PIX_CLK);
    #elif LT9211C_MODE_SEL == TTL_IN_TTL_OUT
        pclk_khz = Drv_System_FmClkGet(AD_RXPLL_PIX_CLK);
    #elif LT9211C_MODE_SEL == LVDS_IN_TTL_OUT
        #if LVDSRX_DESSC_SEL == ENABLED
            pclk_khz = Drv_System_FmClkGet(AD_DESSCPLL_PIX_CLK);
        #elif LVDSRX_DESSC_SEL == DISABLED
            pclk_khz = Drv_System_FmClkGet(AD_RXPLL_PIX_CLK);
        #endif
    #endif
    LTLog(LOG_INFO,"pclk_khz: %ld",pclk_khz);
    
    //ttltx不同模式下io_dclk_khz与pclk_khz的对应关系
    #if TTLTX_DATARATE_MODE == SDR// SDR case
        #if TTLTX_HALF_BIT_MODE == DISABLED     //case 1：RGB 24BIT、YUV422 16BIT、BT1120 16BIT 
            io_dclk_khz = pclk_khz;
        #elif TTLTX_HALF_BIT_MODE == ENABLED    //case 2：BT656 8BIT
            io_dclk_khz = pclk_khz*2;
        #endif
    #elif TTLTX_DATARATE_MODE == DDR// DDR case
        #if TTLTX_HALF_CLOCK_MODE == ENABLED//一般DDR模式
            #if TTLTX_HALF_BIT_MODE == DISABLED     //case 1：RGB 24BIT、YUV422 16BIT、BT1120 16BIT
                io_dclk_khz = pclk_khz/2;
            #elif TTLTX_HALF_BIT_MODE == ENABLED    //case 2：BT656 8BIT
                io_dclk_khz = pclk_khz;
            #endif
        #endif
        #if TTLTX_HALF_WIDTH_MODE == ENABLED//DPI模式
            io_dclk_khz = pclk_khz;     //RGB 24BIT DPI
        #endif
    #endif
    
    //根据io_dclk_khz配置相位
    //相位配置方法：
        //SDR模式：DLL 相位默认0，时钟信号上升沿采样，低频（io_dclk_khz < 100MHz）反向，高频不反向。如果客户的接收端有明确要求，按要求调整DLL相位
        //DDR模式：默认DE后第一个有效沿是上升沿，DLL用相位3；默认DE后第一个有效沿是下降沿时，DLL用相位7。如果客户的接收端有明确要求，按要求调整DLL相位
    #if TTLTX_DATARATE_MODE == SDR
        ucphase = 0; //默认相位0
        HDMI_WriteI2C_Byte(0xff,0x82);
        HDMI_WriteI2C_Byte(0x65,HDMI_ReadI2C_Byte(0x65) | (ucphase<<4)); //DLL 相位配置 （注: 相位调节失败可检查8263[2]是否打开）
        if(io_dclk_khz <= 100000)
        {
            HDMI_WriteI2C_Byte(0x2b,HDMI_ReadI2C_Byte(0x2b) | BIT3_1);  //822b[3]=1,时钟反向
        }
        else
        {
            HDMI_WriteI2C_Byte(0xff,0x82);
            HDMI_WriteI2C_Byte(0x2b,HDMI_ReadI2C_Byte(0x2b) & BIT3_0);  //822b[3]=1,时钟不反向
        }
    #elif TTLTX_DATARATE_MODE == DDR
        ucphase = 3; //默认相位3或7
        HDMI_WriteI2C_Byte(0xff,0x82);
        HDMI_WriteI2C_Byte(0x65,HDMI_ReadI2C_Byte(0x65) | (ucphase<<4)); //DLL 相位配置 （注: 相位调节失败可检查8263[2]是否打开）
    #endif
}

//Drv_DesscPll_ForTtlTx函数：ttlrx全部模式/lvdsrx的非dessc模式 的情况下使用ttltx模块需要配置DesscPll
void Drv_DesscPll_ForTtlTx()
{   
    //pclk_khz: ttltx参考的pix_clk 选择ad_rxpll_pix_clk
    u32 pclk_khz;
    pclk_khz = Drv_System_FmClkGet(AD_RXPLL_PIX_CLK); 
    LTLog(LOG_INFO,"pclk_khz: %ld",pclk_khz);
    
    //desscpll的ref_clk选择aa_rxpll_pix_clk
    HDMI_WriteI2C_Byte(0xff,0x82);
    HDMI_WriteI2C_Byte(0x26,0x60); 
    
    //根据pclk_khz分档配置desscpll_preck_div、desscpll_div_ratio和desscpll_pixck_div
        //desscpll_preck_div：输入desscpll的时钟前pre_div分频器大小
        //desscpll_div_ratio：desscpll环路反馈分频器大小
        //desscpll_pixck_div：vco_clk与pix_clk之间的分频器
    if(pclk_khz <= 44000)
    {
        HDMI_WriteI2C_Byte(0x27,(HDMI_ReadI2C_Byte(0x27)&0xf3)| 0x00);  //desscpll_preck_div = 1
        HDMI_WriteI2C_Byte(0x2e,0x8e);                                  //desscpll_div_ratio = 14+2 = 16
        HDMI_WriteI2C_Byte(0x2f,0x07);                                  //desscpll_pixck_div = 16  
    }
    else if((pclk_khz > 44000)&&(pclk_khz <= 88000))
    {
        HDMI_WriteI2C_Byte(0x27,(HDMI_ReadI2C_Byte(0x27)&0xf3)| 0x04);  //desscpll_preck_div = 2
        HDMI_WriteI2C_Byte(0x2e,0x8e);                                  //desscpll_div_ratio = 14+2 = 16
        HDMI_WriteI2C_Byte(0x2f,0x06);                                  //desscpll_pixck_div = 8
    }
    else if((pclk_khz > 88000)&&(pclk_khz <= 176000))
    {
        HDMI_WriteI2C_Byte(0x27,(HDMI_ReadI2C_Byte(0x27)&0xf3)| 0x08);  //desscpll_preck_div = 4
        HDMI_WriteI2C_Byte(0x2e,0x8e);                                  //desscpll_div_ratio = 14+2 = 16
        HDMI_WriteI2C_Byte(0x2f,0x05);                                  //desscpll_pixck_div = 4
    }
    else if((pclk_khz > 176000)&&(pclk_khz <= 352000))
    {
        HDMI_WriteI2C_Byte(0x27,(HDMI_ReadI2C_Byte(0x27)&0xf3)| 0x0c);  //desscpll_preck_div = 8
        HDMI_WriteI2C_Byte(0x2e,0x8e);                                  //desscpll_div_ratio = 14+2 = 16
        HDMI_WriteI2C_Byte(0x2f,0x04);                                  //desscpll_pixck_div = 2
    }
    
    //复位 desscpll
    HDMI_WriteI2C_Byte(0xff,0x81);
    HDMI_WriteI2C_Byte(0x03,0xfe);
    Ocm_Timer0_Delay1ms(1);
    HDMI_WriteI2C_Byte(0x03,0xff);
    Ocm_Timer0_Delay1ms(20);
    
    //检测desscpll lock状态
    HDMI_WriteI2C_Byte(0xff,0x87);
    if((HDMI_ReadI2C_Byte(0x2a)&0x01)== 0x01)
    {
        LTLog(LOG_INFO,"TtlTx DesscPll: lock");
    }

}
#endif