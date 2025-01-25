
#ifndef _TYPE_H
#define _TYPE_H
 
//Variable Type Definition
typedef 	char 			    CHAR, *PCHAR ;
typedef 	unsigned char 		uchar, *puchar ;
typedef 	unsigned char 		UCHAR, *PUCHAR ;
typedef 	unsigned char 		byte, *pbyte ;
typedef 	unsigned char 		BYTE, *PBYTE ;

typedef 	short 			    SHORT, *PSHORT ;
typedef 	unsigned short 		ushort, *pushort ;
typedef 	unsigned short 		USHORT, *PUSHORT ;
typedef 	unsigned short 		word, *pword ;
typedef 	unsigned short 		WORD, *PWORD ;

typedef 	long 			    LONG, *PLONG ;
typedef 	unsigned long 		ulong, *pulong ;
typedef 	unsigned long 		ULONG, *PULONG ;
typedef 	unsigned long 		dword, *pdword ;
typedef 	unsigned long 		DWORD, *PDWORD ;

typedef 	unsigned int 		UINT, uint;
//Public Definition


typedef enum
{
    STATE_POWER_ON = 1,          //0x01
    STATE_RX_INIT, //0x02
    STATE_TX_INIT,             //0x03
    STATE_PLAY_BACK,

}EnumState;

//state
#define LOW                0
#define HIGH               1
#define OFF                0
#define ON                 1
#define LED_ON             0
#define LED_OFF            1
#define ENABLED            1
#define DISABLED           0


#define 	LVDS_IN_LVDS_OUT	 	    0
#define 	LVDS_IN_MIPI_OUT	 	    1
#define 	LVDS_IN_TTL_OUT	 	        2
#define 	MIPI_IN_LVDS_OUT	 	    3
#define 	MIPI_IN_MIPI_OUT	 	    4
#define 	MIPI_IN_TTL_OUT	 	        5
#define 	TTL_IN_LVDS_OUT	 	        6
#define 	TTL_IN_MIPI_OUT	 	        7
#define 	TTL_IN_TTL_OUT	 	        8


#define 	RGB     	 	0
#define 	YCC444   	 	1
#define 	YCC422   	    2

#define 	P_MODE 	        0
#define 	I_MODE	 	    1

#define 	DEEP_8     	 	8
#define 	DEEP_10   	 	10
#define 	DEEP_12   	    12

//---------------------------LVDS MODE------------------------
#define 	LVDS_No_SSC	 	0
#define 	LVDS_W_SSC	 	1

//---------------------------MIPI MODE------------------------
#define 	MIPI_DSC	 	0
#define 	MIPI_CSC	 	1

//---------------------------TTL MODE------------------------
#define 	SEP_SYNC_RGB	   0
#define 	SEP_SYNC_YCC444	   1
#define 	SEP_SYNC_YCC422	   2

#define 	EMB_SYNC_8BT1120	       4
#define 	EMB_SYNC_8BT656            5
#define 	EMB_SYNC_16BT1120	       6   
#define 	EMB_SYNC_16BTAT1004 	   7

#define 	SDR_MODE            	   0
#define 	DDR_HALF_WIDTH	           1
#define 	DDR_HALF_PIXEL             2




#ifndef NULL
#define NULL	(void *)0
#endif




#endif