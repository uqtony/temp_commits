/******************************************************************************
  * @project: LT9211C
  * @file: main.c
  * @author: sxue
  * @company: LONTIUM COPYRIGHT and CONFIDENTIAL
  * @date: 2023.01.29
/******************************************************************************/

#include "include.h"


void main(void)
{
    Mod_System_Init();
    Mod_LT9211C_Reset();
    LTLog(LOG_INFO, "LT9211C %s %s",__DATE__,__TIME__);
    Mod_ChipID_Read();
    #if (LT9211C_MODE_SEL != PATTERN_OUT)
    Mod_SystemRx_PowerOnInit();
    Mod_SystemTx_PowerOnInit();
    #endif

    while(1)
    {
        #if (LT9211C_MODE_SEL == PATTERN_OUT)
        Mod_ChipTx_PtnOut();
        #endif
        #if (LT9211C_MODE_SEL == MIPI_REPEATER)
        Mod_MipiRpt_Handler();
        #endif
        #if (LT9211C_MODE_SEL == MIPI_LEVEL_SHIFT)
        Mod_MipiLs_Handler();
        #endif
        #if (LT9211C_MODE_SEL == LVDS_IN_LVDS_OUT)
        Mod_LvdsRx_Handler();
        Mod_LvdsTx_Handler();
        #endif
        #if (LT9211C_MODE_SEL == LVDS_IN_MIPI_OUT)
        Mod_LvdsRx_Handler();
        Mod_MipiTx_Handler();
        #endif
        #if (LT9211C_MODE_SEL == LVDS_IN_TTL_OUT)
        Mod_LvdsRx_Handler();
        Mod_TtlTx_Handler();
        #endif
        #if (LT9211C_MODE_SEL == MIPI_IN_LVDS_OUT)
        Mod_MipiRx_Handler();
        Mod_LvdsTx_Handler();
        #endif
        #if (LT9211C_MODE_SEL == MIPI_IN_MIPI_OUT)
        Mod_MipiRx_Handler();
        Mod_MipiTx_Handler();
        #endif
        #if (LT9211C_MODE_SEL == MIPI_IN_TTL_OUT)
        Mod_MipiRx_Handler();
        Mod_TtlTx_Handler();
        #endif
        #if (LT9211C_MODE_SEL == TTL_IN_LVDS_OUT)
        Mod_TtlRx_Handler();
        Mod_LvdsTx_Handler();
        #endif
        #if (LT9211C_MODE_SEL == TTL_IN_MIPI_OUT)
        Mod_TtlRx_Handler();
        Mod_MipiTx_Handler();
        #endif
        #if (LT9211C_MODE_SEL == TTL_IN_TTL_OUT)
        Mod_TtlRx_Handler();
        Mod_TtlTx_Handler();
        #endif
    }
}