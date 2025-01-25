/******************************************************************************
  * @project: LT9211C
  * @file: ModLvdsTx.h
  * @author: xding
  * @company: LONTIUM COPYRIGHT and CONFIDENTIAL
  * @date: 2023.01.29
/******************************************************************************/

#ifndef _MODLVDSTX_H
#define _MODLVDSTX_H

#if ((LT9211C_MODE_SEL == LVDS_IN_LVDS_OUT)||(LT9211C_MODE_SEL == MIPI_IN_LVDS_OUT)||(LT9211C_MODE_SEL == TTL_IN_LVDS_OUT))

#define     LVDSTX_PORT_SEL         DOU_PORT        //PORTA/PORTB/DOU_PORT
#define     LVDSTX_PORT_SWAP        DISABLED         //ENABLED/DISABLED
#define     LVDSTX_PORT_COPY        DISABLED        //ENABLED/DISABLED
#define     LVDSTX_LANENUM          FOUR_LANE       //FOUR_LANE/FIVE_LANE
#define     LVDSTX_MODE             SYNC_MODE       //SYNC_MODE/DE_MODE
#define     LVDSTX_DATAFORMAT       VESA            //VESA/JEIDA
#define     LVDSTX_COLORSPACE       RGB             //RGB/YUV422
#define     LVDSTX_COLORDEPTH       DEPTH_8BIT      //DEPTH_6BIT/DEPTH_8BIT/DEPTH_10BIT
#define     LVDSTX_SYNC_INTER_MODE  DISABLED         //ENABLED/DISABLED
#define     LVDSTX_VIDEO_FORMAT     P_FORMAT        //P_FORMAT/I_FORMAT
#define     LVDSTX_SYNC_CODE_SEND   NON_REPECTIVE       ///NON_REPECTIVE/REPECTIVE
#define     LVDS_SSC_SEL            NO_SSC          //NO_SSC/SSC_1920x1080_30k5/SSC_3840x2160_30k5














extern void Mod_LvdsTx_Handler(void);

#endif

#endif