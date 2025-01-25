//////////////////////////////////////
//Project:   LT2101
//Filename:  AuxMsg.c
//Version:   V1.0
//Copyright: Lontium
//////////////////////////////////////

#include "include.h"

StructAux IDATA g_stAuxStatus;

u8 code ucszRequest[10]={0x00,0x04,0x08,0x0c,0x01,0x05,0x09,0x02,0x06,0x03};

//===========================================
//func  :send defer
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Send_DeferReply(void)
{
    BKD9_2B_REG = AUXDEFER;
    BKD9_2C_REG = 0x00;	 // soft aux send enable;
}

//===========================================
//func  :send aux nack
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Send_NackReply(void)
{
    BKD9_2B_REG = AUXNACK;
    BKD9_2C_REG = 0x00;	 // soft aux send enable;
}

//===========================================
//func  :send aux ack
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Send_AckReply(void)
{
    BKD9_2B_REG = AUXACK;
    BKD9_2C_REG = 0x00;	 // soft aux send enable;
}
//===========================================
//func  :aux send reply data for dpcd read 
//input :AUX data length
//output:N/A
//return:void
//Info  :N/A
//===========================================

void Chip_Aux_Send_Data(u8 ucLenth)
{
    BKD9_2B_REG = AUXACK;
    for(g_stAuxStatus.ucLoopAux = 0; g_stAuxStatus.ucLoopAux < ucLenth;g_stAuxStatus.ucLoopAux++)
    {
        BKD9_2B_REG = g_stAuxStatus.szRxSendData[g_stAuxStatus.ucLoopAux];
    }
    BKD9_2C_REG = 0x00;	 // soft aux send enable;
}

//============================================
//func  :aux send data for edid read  one block from 1-7 16bytes
//input :AUX data length
//output:N/A
//return:void
//Info  :N/A
//============================================
void Chip_Read_Link_Edid(u8 ucLenth)
{
    BKD9_2B_REG = AUXACK;
    for(g_stAuxStatus.ucLoopAux = 0; g_stAuxStatus.ucLoopAux < ucLenth;g_stAuxStatus.ucLoopAux++)
    {
        BKD9_2B_REG = szEdid_Data[g_stAuxStatus.ucLoopAux + g_stAuxStatus.usEdid_Offset]; //i2c read
    }
    g_stAuxStatus.usEdid_Offset = g_stAuxStatus.usEdid_Offset + ucLenth;
    BKD9_2C_REG = 0x00;	 // soft aux send enable;
}
//===========================================
//func  :aux send data for edid read one block from 8 16bytes
//input :AUX data length
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Last_Read_Link_Edid(u8 ucLenth)
{
    BKD9_2B_REG = AUXACK;
    for(g_stAuxStatus.ucLoopAux = 0; g_stAuxStatus.ucLoopAux < ucLenth;g_stAuxStatus.ucLoopAux++)   //i2c last read
    {
        BKD9_2B_REG = szEdid_Data[g_stAuxStatus.ucLoopAux + g_stAuxStatus.usEdid_Offset];
    }
    BKD9_2C_REG = 0x00;	 // soft aux send enable;
}
//===========================================
//func  :IIC Over Aux reply
//input :AUX data ucLength
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_IICOverAux_Read(u8 ucLenth)
{
    BKD9_2B_REG = AUXACK;
    for(g_stAuxStatus.ucLoopAux = 0; g_stAuxStatus.ucLoopAux < ucLenth;g_stAuxStatus.ucLoopAux++)   //i2c last read
    {
        BKD9_2B_REG = 0x00;
    }
    BKD9_2C_REG = 0x00;	 // soft aux send enable;
}
//===========================================================================================================================
//the following function get the aux training status, maybe used in other function
//===========================================
//func  :judge the cr_lock and eq done status
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Aux_TrainingDone(void)
{
    switch(g_stAuxStatus.ucLink_Count)
    {
        case 0x01:
            if((g_stAuxStatus.ucTps_Pattern == 0x01)&&((g_stAuxStatus.ucDpcd202&0x01)==0x01))
            {
                g_stAuxStatus.b1Cr_Lock  = TRUE;
            }
            if((g_stAuxStatus.ucTps_Pattern >= 0x02)&&((g_stAuxStatus.ucDpcd202&0x0f)==0x07))
            {
                g_stAuxStatus.b1Train_Done = TRUE;
            }
            break;
        case 0x02:
            if((g_stAuxStatus.ucTps_Pattern == 0x01)&&((g_stAuxStatus.ucDpcd202&0x11) == 0x11))
            {
                g_stAuxStatus.b1Cr_Lock  = TRUE;
            }
            if((g_stAuxStatus.ucTps_Pattern >= 0x02)&&(g_stAuxStatus.ucDpcd202 == 0x77))
            {
                g_stAuxStatus.b1Train_Done = TRUE;
            }
            break;
        case 0x04:
            if((g_stAuxStatus.ucTps_Pattern == 0x01)&&((g_stAuxStatus.ucDpcd202&0x11) == 0x11)&&((g_stAuxStatus.ucDpcd203&0x11) == 0x11))
            {
                g_stAuxStatus.b1Cr_Lock  = TRUE;
            }
            if((g_stAuxStatus.ucTps_Pattern >= 0x02)&&(g_stAuxStatus.ucDpcd202 == 0x77)&&(g_stAuxStatus.ucDpcd203 == 0x77))
            {
                g_stAuxStatus.b1Train_Done = TRUE;
            }
            break;
        default:
        break; 
    }
}
//===========================================
//func  :the aux done is get from 0xdbc9 for tps7
//input :
//output:N/A
//return:void
//Info  :N/A
//===========================================
u8 Chip_Aux_DoneGet(void)
{
    u8 b1Status = FALSE; 
    switch(g_stAuxStatus.ucLink_Count)
    {
        case 0x01:
            if((BKDB_C9_REG&0x11)== 0x11)
            {
                b1Status = TRUE;
            }
            break;
        case 0x02:
            if((BKDB_C9_REG&0x33)== 0x33)
            {
                b1Status = TRUE;
            }
            break;
        case 0x04:
            if((BKDB_C9_REG&0xff)== 0xff)
            {
                b1Status = TRUE;
            }
            break;
        default:
        break; 
    }
    return b1Status;
}
//===========================================
//func  :reply the adjust request value cal from dpcd103-dpcd106
//input :aux read order
//output:N/A
//return:void
//Info  :N/A
//===========================================
u8 Chip_Aux_RequestAjustCal(u8 ucI)
{
    for(g_stAuxStatus.ucLoopAux = 0; g_stAuxStatus.ucLoopAux < 10;g_stAuxStatus.ucLoopAux++)
    {
        if(ucI == ucszRequest[g_stAuxStatus.ucLoopAux])
        {
            break;
        }
    }
    if(g_stAuxStatus.ucLoopAux < 9)
    {
        g_stAuxStatus.ucLoopAux += 1;
    }
    return ucszRequest[g_stAuxStatus.ucLoopAux] ;
}

//===========================================
//func  :read dpcd 00080
//input :aux read order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Read_Dpcd80(IN u8 ucI)
{
    g_stAuxStatus.szRxSendData[ucI] = 0x4b;
}
//===========================================
//func  :read dpcd 00081
//input :aux read order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Read_Dpcd81(IN u8 ucI)
{
    if((g_stDpRx.ucRxMaxLinkRate * g_stDpRx.ucRxMaxLaneCount) >= 60)// 4k60
    {
        g_stAuxStatus.szRxSendData[ucI] = (g_Edid.b1Hdmi20Edid == TRUE)?(0xf0):(0x88);
    }
    else if((g_stDpRx.ucRxMaxLinkRate * g_stDpRx.ucRxMaxLaneCount) >= 30)
    {
        g_stAuxStatus.szRxSendData[ucI] = 0x88;
    }
    else
    {
        g_stAuxStatus.szRxSendData[ucI] = 0x3c;
    }
}
//===========================================
//func  :read dpcd 00082
//input :aux read order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Read_Dpcd82(IN u8 ucI)
{
    if(g_Edid.ucColorDepth == DEEP_12BIT)
    {
        g_stAuxStatus.szRxSendData[ucI] = 0x02;
    }
    else if(g_Edid.ucColorDepth == DEEP_10BIT)
    {
        g_stAuxStatus.szRxSendData[ucI] = 0x01;
    }
    else
    {
        g_stAuxStatus.szRxSendData[ucI] = 0x00;
    }
}
//===========================================
//func  :read dpcd 00083
//input :aux read order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Read_Dpcd83(IN u8 ucI)
{
    g_stAuxStatus.szRxSendData[ucI] = 0x00;
}
//===========================================
//func  :read dpcd 00200
//input :aux read order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Read_Dpcd200(IN u8 ucI)
{
    g_stAuxStatus.szRxSendData[ucI] = 0x01;
    #if DPRX_HDCP_DEC_MODE != NO_HDCP
    if (g_stAuxStatus.b1ReHdcpDecEvt == HPD_IRQ_EVENT)
    {
        g_stAuxStatus.szRxSendData[ucI] = 0x41;
    }
    #endif    
}
//===========================================
//func  :read dpcd 00201
//input :aux read order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Read_Dpcd201(IN u8 ucI)
{
    g_stAuxStatus.szRxSendData[ucI] = 0x00;
    #if DPRX_HDCP_DEC_MODE != NO_HDCP
    if (g_stAuxStatus.b1ReHdcpDecEvt == HPD_IRQ_EVENT)
    {
        g_stAuxStatus.szRxSendData[ucI] = 0x04;
    }
    #endif    
}
//===========================================
//func  :read dpcd 00202
//input :aux read order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Read_Dpcd202(IN u8 ucI)
{
    g_stAuxStatus.ucDpcd202 = g_stAuxStatus.szRxSendData[ucI];
    if(g_stAuxStatus.ucTps_Pattern >= 0x02)
    {
        if((g_stAuxStatus.ucLink_Count >= 1)&&((g_stAuxStatus.ucDpcd202&0x07) != 0x07))
        {
            g_stAuxStatus.ucDpcd206 &= 0xf0;
            g_stAuxStatus.ucDpcd206 |= Chip_Aux_RequestAjustCal(g_stAuxStatus.ucDpcd103);
        }
        if((g_stAuxStatus.ucLink_Count >= 2)&&((g_stAuxStatus.ucDpcd202&0x70) != 0x70))
        {
            g_stAuxStatus.ucDpcd206 &= 0x0f;
            g_stAuxStatus.ucDpcd206 |= Chip_Aux_RequestAjustCal(g_stAuxStatus.ucDpcd104) <<4;
        }               
    }
    Chip_Aux_TrainingDone();
}
//===========================================
//func  :read dpcd 00203
//input :aux read order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Read_Dpcd203(IN u8 ucI)
{
    g_stAuxStatus.ucDpcd203 = g_stAuxStatus.szRxSendData[ucI];
    if((g_stAuxStatus.ucTps_Pattern >= 0x02)&&(g_stAuxStatus.ucLink_Count == 4))
    {
        if((g_stAuxStatus.ucDpcd203&0x07) != 0x07)
        {
            g_stAuxStatus.ucDpcd207 &= 0xf0;
            g_stAuxStatus.ucDpcd207 |= Chip_Aux_RequestAjustCal(g_stAuxStatus.ucDpcd105);;
        }
        if((g_stAuxStatus.ucDpcd203&0x70) != 0x70)
        {
            g_stAuxStatus.ucDpcd207 &= 0x0f;
            g_stAuxStatus.ucDpcd207 |= Chip_Aux_RequestAjustCal(g_stAuxStatus.ucDpcd106)<<4;
        }
    }
    Chip_Aux_TrainingDone(); 
}
//===========================================
//func  :read dpcd 00204
//input :aux read order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Read_Dpcd204(IN u8 ucI)    
{
    if(g_stAuxStatus.ucTps_Pattern == 7)//
    {
        g_stAuxStatus.szRxSendData[ucI] = ((g_stAuxStatus.b1Train_Done)||((Chip_Aux_DoneGet())== TRUE))?(0x01):(0x80);
    }
    else if((g_stAuxStatus.ucTps_Pattern == 0)&&(g_stAuxStatus.ucTps2_Pattern == 7))//
    {
        g_stAuxStatus.szRxSendData[ucI] = (g_stAuxStatus.b1Train_Done)?(0x01):(0x80);
    }
    g_stAuxStatus.ucDpcd204 = g_stAuxStatus.szRxSendData[ucI];
    if(g_stAuxStatus.ucDpcd204 & BIT0_1) //aligend down
    {
        g_stAuxStatus.b1Align_Done = TRUE;
    }
}
//===========================================
//func  :read dpcd 00205
//input :aux read order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Read_Dpcd205(IN u8 ucI)    
{
    g_stAuxStatus.ucDpcd205 = g_stAuxStatus.szRxSendData[ucI];

}
//===========================================
//func  :read dpcd 00206
//input :aux read order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Read_Dpcd206(IN u8 ucI)
{
    if(g_stAuxStatus.ucTps_Pattern == 0x01)
    {
        g_stAuxStatus.ucDpcd206 = g_stAuxStatus.szRxSendData[ucI];
        if((g_stAuxStatus.b1IsSwingLvl == FALSE)&&(g_stAuxStatus.b1Cr_Lock == FALSE))
        {
            DRV_DpRx_Reset(g_stAuxStatus.b1Ssc_Dpcd107);
        }
    }
    else
    {
        g_stAuxStatus.szRxSendData[ucI] = g_stAuxStatus.ucDpcd206 ;
    }
}
//===========================================
//func  :read dpcd 00207
//input :aux read order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Read_Dpcd207(IN u8 ucI)
{
    if(g_stAuxStatus.ucTps_Pattern == 0x01)
    {
        g_stAuxStatus.ucDpcd207 = g_stAuxStatus.szRxSendData[ucI];
    }
    else
    {
        g_stAuxStatus.szRxSendData[ucI] = g_stAuxStatus.ucDpcd207;
    }
}
//===========================================
//func  :dpcd read action for command 0x90,
//input : aux data lenth,equal byte_3+1;
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Read_Dpcd(u8 ucLenth)
{
    IDATA u8 ucIncrease;
    BKDB_00_REG = 0xc0;
    BKDB_03_REG =  g_stAuxStatus.szRxAddress[0];
    BKDB_04_REG =  g_stAuxStatus.szRxAddress[1];
    BKDB_05_REG =  g_stAuxStatus.szRxAddress[2];

    for(g_stAuxStatus.ucLoopAux = 0;g_stAuxStatus.ucLoopAux < ucLenth; g_stAuxStatus.ucLoopAux++)
    {
        if(g_stAuxStatus.ucLoopAux)//
        {
            if(BKDB_05_REG == 0xff)
            {
                    BKDB_04_REG++;
            }
            BKDB_05_REG ++;
        }
        g_stAuxStatus.szRxSendData[g_stAuxStatus.ucLoopAux] = BKDB_54_REG;//read data from DPCD
    }
    if((g_stAuxStatus.szRxAddress[0]==0x00)&&(g_stAuxStatus.szRxAddress[1]==0x00))
    {
        ucIncrease = 0;
        switch(g_stAuxStatus.szRxAddress[2])
        { 
             case 0x80  ://dpcd00080
                Chip_Read_Dpcd80(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }		  
             case 0x81 ://dpcd00081
                    Chip_Read_Dpcd81(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }				 
             case 0x82 ://dpcd00082
                Chip_Read_Dpcd82(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }	
             case 0x83 ://dpcd00202
                Chip_Read_Dpcd83(ucIncrease);
                break;
             default:
                 break;
         }
    }
    else if((g_stAuxStatus.szRxAddress[0]==0x00)&&(g_stAuxStatus.szRxAddress[1]==0x02))
    {
        ucIncrease = 0;
        switch(g_stAuxStatus.szRxAddress[2])
        { 
             case 0x00  ://dpcd00200
                Chip_Read_Dpcd200(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }		  
             case 0x01 ://dpcd00201
                Chip_Read_Dpcd201(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }				 
             case 0x02 ://dpcd00202
                Chip_Read_Dpcd202(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }				 
             case 0x03 ://dpcd00203
                Chip_Read_Dpcd203(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }				 
             case 0x04 ://dpcd00204
                Chip_Read_Dpcd204(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }				 
             case 0x05 ://dpcd00205
                Chip_Read_Dpcd205(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }			 
             case 0x06 ://dpcd00206
                Chip_Read_Dpcd206(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }			 
             case 0x07 ://dpcd00207
                Chip_Read_Dpcd207(ucIncrease);
                break;
             default:
                break;
        }
    }
    else if((g_stAuxStatus.szRxAddress[0]==0x00)&&(g_stAuxStatus.szRxAddress[1]==0x20))//DPCD 02002
    {
        ucIncrease = 0;
        switch(g_stAuxStatus.szRxAddress[2])
        { 
             case 0x02  :///dpcd02002
                Chip_Read_Dpcd200(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }		  
             case 0x03 :///dpcd02003
                Chip_Read_Dpcd201(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }				 
             case 0x04 :///dpcd02004
                if(++ucIncrease == ucLenth)
                {
                    break;
                }				 
             case 0x05 :///dpcd02005
                if(++ucIncrease == ucLenth)
                {
                    break;
                }				 
             case 0x06 :///dpcd02006
                if(++ucIncrease == ucLenth)
                {
                    break;
                }				 
             case 0x07 :///dpcd02007
                if(++ucIncrease == ucLenth)
                {
                    break;
                }			 
             case 0x08 :///dpcd02008
                if(++ucIncrease == ucLenth)
                {
                    break;
                }			 
             case 0x09 :///dpcd02009
                if(++ucIncrease == ucLenth)
                {
                    break;
                }						 
             case 0x0A :///dpcd0200A
                if(++ucIncrease == ucLenth)
                {
                    break;
                }						 
             case 0x0B :///dpcd0200B
                if(++ucIncrease == ucLenth)
                {
                    break;
                }						 
             case 0x0C :///dpcd0200C
                Chip_Read_Dpcd202(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }	
            case 0x0D :///dpcd0200D
                Chip_Read_Dpcd203(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }	
             case 0x0E ://dpcd0200E
                Chip_Read_Dpcd204(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }	
                break;
             case 0x0F ://dpcd0200F
                Chip_Read_Dpcd205(ucIncrease);
                break;
             default:
                break;
        }
    }
    else if((g_stAuxStatus.szRxAddress[0]==0x00)&&(g_stAuxStatus.szRxAddress[1]==0x04)&&(g_stAuxStatus.szRxAddress[2]==0x00))
    {
        ;				       				 
    }
    #if DPRX_HDCP_DEC_MODE != NO_HDCP
    else if(g_stAuxStatus.szRxSendData[0] == 0x06)
    {
        g_stAuxStatus.b1ReHdcpDecEvt = NONE_EVENT;
    }
    #endif    
}
//=============================================================================================================================
// this function get the dpcd write status
//===========================================
//func  :write dpcd 00100
//input :aux write order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Write_Dpcd100(IN u8 ucI)
{
    g_stAuxStatus.ucLink_Rate = g_stAuxStatus.szRxData[ucI];
    DRV_DpRx_PiSet(g_stAuxStatus.ucLink_Rate);
    DRV_DpRx_RxPllBand(g_stAuxStatus.ucLink_Rate);
    DRV_DpRx_DivSet(g_stAuxStatus.ucLink_Rate);
    DRV_DpRx_PhyCsFbSet(g_stAuxStatus.ucLink_Rate);
    g_stAuxStatus.ucTps_Pattern_Save = 0;
}
//===========================================
//func  :write dpcd 00101
//input :aux write order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Write_Dpcd101(IN u8 ucI)
{
    g_stAuxStatus.ucLink_Count = g_stAuxStatus.szRxData[ucI]&0x1f;
}
//===========================================
//func  :write dpcd 00102
//input :aux write order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Write_Dpcd102(IN u8 ucI)
{
    g_stAuxStatus.ucTps_Pattern = g_stAuxStatus.szRxData[ucI]&0x0f;
    if(g_stAuxStatus.ucTps_Pattern == g_stAuxStatus.ucTps_Pattern_Save)
    {
        return;
    }    
    if(g_stAuxStatus.ucTps_Pattern == 0x01)//TPS1
    {
        g_stAuxStatus.b1Cr_Lock = FALSE;
		g_stAuxStatus.b1Train_Done =FALSE;
        g_stAuxStatus.b1Align_Done = FALSE;
        g_stAuxStatus.ucTps2_Pattern = 0;
        g_stAuxStatus.ucDpcd206 = 0x00;
        g_stAuxStatus.ucDpcd207 = 0x00;
        g_stAuxStatus.ucDpcd103 = 0x00;
        g_stAuxStatus.ucDpcd104 = 0x00;
        g_stAuxStatus.ucDpcd105 = 0x00;
        g_stAuxStatus.ucDpcd106 = 0x00;
        DRV_DpRx_EqMode(TRUE);       
        #if DPRX_SWING_MIN_LEVEL > LEVEL_0
        Drv_DpRx_CrLockHoldSet(FALSE);
        g_stAuxStatus.b1IsSwingLvl = TRUE;
        #else
        g_stAuxStatus.b1IsSwingLvl = FALSE;
        #endif
        DRV_DpRx_Reset(g_stAuxStatus.b1Ssc_Dpcd107);
    }
    else if(g_stAuxStatus.ucTps_Pattern >= 0x02)//TPS2 TPS3 TPS4
    {
        g_stAuxStatus.ucTps2_Pattern = g_stAuxStatus.ucTps_Pattern;
    }
    else
    {
        ;
    }
    g_stAuxStatus.ucTps_Pattern_Save = g_stAuxStatus.ucTps_Pattern;
}
//===========================================
//func  :write dpcd 00103
//input :aux write order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Write_Dpcd103(IN u8 ucI)
{
    g_stAuxStatus.ucDpcd103 = g_stAuxStatus.szRxData[ucI];
    if((g_stAuxStatus.ucTps_Pattern == 0x01)&&((g_stAuxStatus.ucDpcd103 & 0x03) >= g_stAuxStatus.ucDprx_Min_Swing_Lvl)) //
    {
        g_stAuxStatus.b1IsSwingLvl = FALSE;
        Drv_DpRx_CrLockHoldSet(TRUE);
    }
    g_stAuxStatus.ucDpcd103 = ((g_stAuxStatus.ucDpcd103>>1)&0x0c)|(g_stAuxStatus.ucDpcd103&0x03);// cal for dpcd206
}

//===========================================
//func  :write dpcd 00104
//input :aux write order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Write_Dpcd104(IN u8 ucI)
{
    g_stAuxStatus.ucDpcd104 = g_stAuxStatus.szRxData[ucI];
    g_stAuxStatus.ucDpcd104 =  ((g_stAuxStatus.ucDpcd104 >> 1)&0x0c)|(g_stAuxStatus.ucDpcd104&0x03);// cal for dpcd206
}
//===========================================
//func  :write dpcd 00105
//input :aux write order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Write_Dpcd105(IN u8 ucI)
{
    g_stAuxStatus.ucDpcd105 = g_stAuxStatus.szRxData[ucI];
    g_stAuxStatus.ucDpcd105 =  ((g_stAuxStatus.ucDpcd105 >> 1)&0x0c)|(g_stAuxStatus.ucDpcd105&0x03);// cal for dpcd207
}
//===========================================
//func  :write dpcd 00106
//input :aux write order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Write_Dpcd106(IN u8 ucI)
{
    g_stAuxStatus.ucDpcd106 = g_stAuxStatus.szRxData[ucI];
    g_stAuxStatus.ucDpcd106 =  ((g_stAuxStatus.ucDpcd106 >> 1)&0x0c)|(g_stAuxStatus.ucDpcd106&0x03);// cal for dpcd206
}
//===========================================
//func  :write dpcd 00107
//input :aux write order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Write_Dpcd107(IN u8 ucI)
{
    g_stAuxStatus.b1Ssc_Dpcd107 = (g_stAuxStatus.szRxData[ucI]&0x10)>>4;
    DRV_DpRx_Cdr(g_stAuxStatus.b1Ssc_Dpcd107);
}
//===========================================
//func  :write dpcd 00600
//input :aux write order
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Write_Dpcd600(IN u8 ucI)
{
    if(ucI == 0x02)
    {
        g_stAuxStatus.ucTps_Pattern_Save = 0;
        g_stAuxStatus.ucTps2_Pattern =  0;
        g_stAuxStatus.b1Ssc_Dpcd107 =FALSE; 
        g_stAuxStatus.ucDpcd206 = 0x00;
        g_stAuxStatus.ucDpcd207 = 0x00;        
        g_stAuxStatus.b1Cr_Lock   =  FALSE;
        g_stAuxStatus.b1Train_Done = FALSE;
        g_stAuxStatus.b1Align_Done = FALSE; 
    }
}
//===========================================
//func  :dpcd write action for command 0x80
//input :aux write data lenth
//output:N/A
//return:void
//Info  :N/A
//===========================================
void Chip_Write_Dpcd(u8 ucLenth)
{
    IDATA u8 ucIncrease;
    BKDB_00_REG = 0xc0;
    BKDB_03_REG =  g_stAuxStatus.szRxAddress[0];
    BKDB_04_REG =  g_stAuxStatus.szRxAddress[1];
    BKDB_05_REG =  g_stAuxStatus.szRxAddress[2];
    
    for(g_stAuxStatus.ucLoopAux = 0;g_stAuxStatus.ucLoopAux < ucLenth; g_stAuxStatus.ucLoopAux++)
    {
        if(g_stAuxStatus.ucLoopAux)//
        {
            if(BKDB_05_REG == 0xff)
            {
                    BKDB_04_REG++;
            }
            BKDB_05_REG ++;
        }
        BKDB_53_REG = g_stAuxStatus.szRxData[g_stAuxStatus.ucLoopAux] ;//write from DPCD
    }
    if((g_stAuxStatus.szRxAddress[0]==0x00)&&(g_stAuxStatus.szRxAddress[1]==0x01))
    {
        ucIncrease = 0;
        switch(g_stAuxStatus.szRxAddress[2])
        { 
            case 0x00  ://dpcd00100
                Chip_Write_Dpcd100(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }		  
            case 0x01 ://dpcd00101
                Chip_Write_Dpcd101(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }				 
            case 0x02 ://dpcd00102
                Chip_Write_Dpcd102(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }				 
            case 0x03 ://dpcd00103
                Chip_Write_Dpcd103(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }				 
            case 0x04 ://dpcd00104
                Chip_Write_Dpcd104(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }				 
            case 0x05 ://dpcd00105
                Chip_Write_Dpcd105(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }			 
            case 0x06 ://dpcd00106
                Chip_Write_Dpcd106(ucIncrease);
                if(++ucIncrease == ucLenth)
                {
                    break;
                }			 
            case 0x07 ://dpcd00107
                Chip_Write_Dpcd107(ucIncrease);
                break;	
            default:
                break;
        }
    }
    else if((g_stAuxStatus.szRxAddress[0]==0x00)&&(g_stAuxStatus.szRxAddress[1]==0x03)&&(g_stAuxStatus.szRxAddress[2]==0x00))//dpcd300
    {
        ;
    }
    else if((g_stAuxStatus.szRxAddress[0]==0x00)&&(g_stAuxStatus.szRxAddress[1]==0x06)&&(g_stAuxStatus.szRxAddress[2]==0x00))//dpcd600
    {
        Chip_Write_Dpcd600(g_stAuxStatus.szRxData[0]);
    }
    #if DPRX_HDCP_DEC_MODE != NO_HDCP
    else if((g_stAuxStatus.szRxAddress[0]==0x06)&&(g_stAuxStatus.szRxAddress[1]==0x90)&&(g_stAuxStatus.szRxAddress[2]==0x00))//dpcd69000
    {
        ;
    }
    else if((g_stAuxStatus.szRxAddress[0]==0x06)&&(g_stAuxStatus.szRxAddress[1]==0x94)&&(g_stAuxStatus.szRxAddress[2]==0x04))//dpcd69494
    {
        ;
    }
    #endif
    
}

//===========================================
//func  :this function deal with the auxrx interrupt
//input :N/A
//output:N/A
//return:void
//Info  :N/A
//===========================================
void CHIP_Interrupt_AuxTask(void)
{
    IDATA u8 ucRdAux_Data ;
    g_stAuxStatus.ucRxCounter = BKD9_32_REG & 0x1F;
    ucRdAux_Data = BKD9_2B_REG;
    g_stAuxStatus.ucRxCmd = ucRdAux_Data  & 0xF0;
    g_stAuxStatus.szRxAddress[0] = ucRdAux_Data & 0x0F;
    g_stAuxStatus.szRxAddress[1] = BKD9_2B_REG;
    g_stAuxStatus.szRxAddress[2] = BKD9_2B_REG;
    if(g_stAuxStatus.ucRxCounter >= 0x04)//
    {
        g_stAuxStatus.ucRxLength = BKD9_2B_REG;
        g_stAuxStatus.ucRxLength += 1;
        if(g_stAuxStatus.ucRxLength > 0x10)
        {
            return;
        }
    }
    else
    {
        g_stAuxStatus.ucRxLength = 0;
    }
    if(g_stAuxStatus.ucRxCounter > 4)//data
    {
        for(g_stAuxStatus.ucLoopAux = 0; g_stAuxStatus.ucLoopAux < g_stAuxStatus.ucRxLength; g_stAuxStatus.ucLoopAux++)
        {
            g_stAuxStatus.szRxData[g_stAuxStatus.ucLoopAux] = BKD9_2B_REG;
        }
    }
    switch(g_stAuxStatus.ucRxCmd)
	{
        case CMD_DPCDW:  //0x80; Native WR
                Chip_Write_Dpcd(g_stAuxStatus.ucRxLength);
                Chip_Send_AckReply();
                break;
        case CMD_DPCDR:  //0x90; Native Read
                Chip_Read_Dpcd(g_stAuxStatus.ucRxLength);
                Chip_Aux_Send_Data(g_stAuxStatus.ucRxLength);
                break;
        case CMD_I2CW:  //0x40;
                if(g_stAuxStatus.szRxAddress[2] == 0x50)//EDID address
                {
                    if((g_stAuxStatus.ucRxLength == 1)&&(g_stAuxStatus.ucRxCounter == 0x05))//WR EDID original address
                    {
                        g_stAuxStatus.usEdid_Offset = g_stAuxStatus.szRxData[0];
                        if(g_stAuxStatus.b1Edid_Block_Offset)
                        {
                            g_stAuxStatus.usEdid_Offset |= 0x100;
                            g_stAuxStatus.b1Edid_Block_Offset = 0;
                        }
                    }
                }
                else if(g_stAuxStatus.szRxAddress[2] == 0x30)//>256 EDID block
                {
                    if((g_stAuxStatus.ucRxLength == 1)&&(g_stAuxStatus.szRxData[0]== 0x01))
                    {
                         g_stAuxStatus.b1Edid_Block_Offset = 1;
                    }
                    else
                    {
                        g_stAuxStatus.b1Edid_Block_Offset = 0;
                    }
                }
                Chip_Send_AckReply();
                break;
        case CMD_I2CR:  //0x50; MOT=1,I2C-R //address only or address length????
                if((g_stAuxStatus.szRxAddress[2] == 0x50)&&(g_stAuxStatus.ucRxCounter == 0x04))//read EDID datas
                {
                    Chip_Read_Link_Edid(g_stAuxStatus.ucRxLength);
                }
				else if((g_stAuxStatus.szRxAddress[2] == 0x52)&&(g_stAuxStatus.ucRxCounter == 0x04))//read EDID datas
				{
					Chip_Send_NackReply();
				}
                else
                {
                    Chip_IICOverAux_Read(g_stAuxStatus.ucRxLength);
                }
                break;
        case CMD_I2CS:   //0x10;
                if((g_stAuxStatus.szRxAddress[2] == 0x50)&&(g_stAuxStatus.ucRxCounter == 0x04))//EDID address
                {
                    Chip_Last_Read_Link_Edid(g_stAuxStatus.ucRxLength);
                    g_stAuxStatus.usEdid_Offset = 0;
                }
                else if((g_stAuxStatus.szRxAddress[2] == 0x50)&&(g_stAuxStatus.ucRxCounter == 0x03))//address only(read stop)
                {
                    Chip_Send_AckReply();
                    g_stAuxStatus.usEdid_Offset = 0;
                }
                else
                {
                    Chip_Send_AckReply();
                }
                break;
        case CMD_I2CLW:           //0x00;  MOT=0,I2C-over-aux,write done;address only(stop)  
                Chip_Send_AckReply();
                break;
        case CMD_I2CLD:           //0x20;MOT=0, Write-status-update
               Chip_Send_AckReply();
                break;
        default:
                Chip_Send_AckReply(); 
                break;
	}
}
//===========================================
//func  :this function get the aux training done status
//input :N/A
//output:the TRUE means aux training done ,FALSE not done
//return:void
//Info  :N/A
//===========================================
u8 CHIP_Aux_HandingStauts(void)
{
    if((g_stAuxStatus.b1Train_Done == TRUE)&&(g_stAuxStatus.b1Align_Done == TRUE))
    {
        return TRUE;
    }
    return FALSE;
}

void CHIP_Aux_TrainigStatusClear(void)
{
    g_stAuxStatus.ucLink_Rate = DPRX_LINK_RATE;
    g_stAuxStatus.ucLink_Count = DPRX_LANE_COUNT;
    g_stAuxStatus.ucTps_Pattern_Save = 0;
    g_stAuxStatus.ucTps2_Pattern = 0;
    g_stAuxStatus.ucDprx_Min_Swing_Lvl = DPRX_SWING_MIN_LEVEL;
    g_stAuxStatus.b1Ssc_Dpcd107 =FALSE; 
    g_stAuxStatus.ucDpcd206 = 0x00;
    g_stAuxStatus.ucDpcd207 = 0x00;
    g_stAuxStatus.b1Cr_Lock = FALSE;	
    g_stAuxStatus.b1Train_Done = FALSE;
    g_stAuxStatus.b1Align_Done = FALSE; 
    g_stAuxStatus.b1IsSwingLvl = FALSE;
    g_stAuxStatus.b1ReHdcpDecEvt = NONE_EVENT;
}


