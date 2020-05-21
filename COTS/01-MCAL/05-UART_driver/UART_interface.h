/************************************************************************
 * File name: GPIO_interface.h
 *
 * Description: This file contains the prototypes of the UART driver
 * and the macros used by the user
 *
 * Owner: Ahmed Refaat
 * Date: 29/3/2020
 * Version 1.1
 ************************************************************************/

#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H


/***************************** Macros ***********************************/
#define STATUS_OK		0
#define STATUS_NOK		1
#define STATUS_BUSY		2

#define BAUD_RATE_110						110
#define BAUD_RATE_300                       300
#define BAUD_RATE_600                       600
#define BAUD_RATE_1200                      1200
#define BAUD_RATE_2400                      2400
#define BAUD_RATE_4800                      4800
#define BAUD_RATE_9600                      9600
#define BAUD_RATE_14400                     14400
#define BAUD_RATE_19200                     19200
#define BAUD_RATE_38400                     38400
#define BAUD_RATE_57600                     57600
#define BAUD_RATE_115200                    115200


/* Status register bits */
#define CTS		9
#define LBD		8
#define TXE		7
#define TC		6
#define RXNE	5

#define ORE		3
#define NE		2
#define FE		1
#define PE		0

/* Control register 1 parameters */
#define WORD_LENGTH_8BITS					0x0
#define WORD_LENGTH_9BITS					0x1000
#define WAKE_UP_METHOD_IDLE_LINE			0x0
#define WAKE_UP_METHOD_ADDRESS_MARK			0x800
#define PARITY_CONTROL_ENABLE				0x400
#define PARITY_CONTROL_DISABLE				0x0
#define EVEN_PARITY							0x0
#define ODD_PARITY							0x200
#define PE_INT_ENABLE						0x100
#define PE_INT_DISABLE						0x0
#define TXE_INT_ENABLE						0x80
#define TXE_INT_DISABLE						0x0
#define TC_INT_ENABLE						0x40
#define TC_INT_DISABLE						0x0
#define RXNE_INT_ENABLE						0x20
#define RXNE_INT_DISABLE					0x0
#define IDLE_INT_ENABLE						0x10
#define IDLE_INT_DISABLE					0x0
#define TRANSM_ENABLE						0x8
#define TRANSM_DISABLE						0x0
#define RECEIVER_ENABLE						0x4
#define RECEIVER_DISABLE					0x0
#define RECEIVER_ACTIVE_MODE				0x2
#define RECEIVER_MURE_MODE					0x0
#define BREAK_CHAR							0x1
#define NO_BREAK_CHAR						0x0


/* Control register 2 parameters */
#define LIN_MODE_ENABLE		                0x4000
#define LIN_MODE_DISABLE					0x0
#define ONE_STOP_BIT						0x0
#define HALF_STOP_BITS						0x1000
#define TWO_STOP_BITS						0x2000
#define ONE_HAL_STOP_BITS					0x3000
#define CLOCK_ENABLE		                0x800
#define CLOCK_DISABLE						0x0
#define CPOL_STEADY_HIGH	                0x400
#define CPOL_STEADY_LOW						0x0
#define CLOCK_PHASE_SECOND	                0x200
#define CLOCK_PHASE_FIRST					0x0
#define LBCL				                0x100
#define LBD_INT_ENABLE		                0x40
#define LBD_INT_DISABLE						0x0
#define LBDL_11				                0x20
#define LBDL_10								0x0

/* Control register 3 parameters */
#define CTS_INT_ENABLE		                0x400
#define CTS_INT_DISABLE						0x0
#define CTS_ENABLE			                0x200
#define CTS_DISABLE							0x0
#define RTS_ENABLE			                0x100
#define RTS_DISABLE							0x0
#define DMAT_ENABLE			                0x80
#define DMAT_DISABLE						0x0
#define DMAR_ENABLE			                0x40
#define DMAR_DISABLE						0x0
#define SMART_CARD_ENABLE	                0x20
#define SMART_CARD_DISABLE					0x0
#define SMART_CARD_NACK_ENABLE              0x10
#define SMART_CARD_NACK_DISABLE				0x0
#define HALF_DUPLEX_MODE	                0x8
#define FULL_DUPLEX_MODE					0x0
#define LOW_POWER_MODE		                0x4
#define NORMAL_MODE							0x0
#define IRD_ENABLE			                0x2
#define IRD_DISABLE							0x0
#define ERROR_INT_ENABLE	                0x1
#define ERROR_INT_DISABLE					0x0

/***************************** Type definitions ***************************/
typedef void (* IntCallback_t) (void);

typedef struct
{
	u32 BaudRate;
	u32 WordLength;
	u32 WakeUpMethod;
	u32 ParityControl;
	u32 ParitySelection;
	u32 ParityErrorInt;
	u32 TXEInt;
	u32 TCInt;
	u32 RXNEInt;
	u32 IDLEInt;
	u32 ReceiverWakeUp;
	u32 SendBreak;
	u32 LINEnable;
	u32 StopBits;
	u32 ClockEnable;
	u32 ClockPol;
	u32 ClockPhase;
	u32 LastBitClockPulse;
	u32 LINBreakDetection;
	u32 DMAEnableTrans;
	u32 DMAEnableRec;
	u32 ErrorInt;

	u32 UART_DIV;

}UART_Param_t;


/***************************** Functions prototypes  ***************************/

/*****************************************************************************
 * Function name: UART_init
 *
 * parameters:  Input:
 *                 ChannelNumber
 *                     type: u8
                        Description: number of the UART channel to be initialized
 *                 UARTDIV
 *                     type: u32
 *                     Description: control the clock source (ON,OFF)
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function initializes the UART channel with the
 * 				default configuration
 *****************************************************************************/
extern u8 UART_init (u8 ChannelNumber, UART_Param_t * UART_config);

/*****************************************************************************
 * Function name: UART_send
 *
 * parameters:  Input:
 *                 ChannelNumber
 *                     type: u8
                        Description: number of the UART channel to be initialized
 *                 Data
 *                     type: u8
 *                     Description: Data byte which to be sent on the UART channel
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function sends a byte on the desired UART channel
 *****************************************************************************/
extern u8 UART_send (u8 ChannelNumber , u8 Data);

/*****************************************************************************
 * Function name: UART_receive
 *
 * parameters:  Input:
 *                 ChannelNumber
 *                     type: u8
                        Description: number of the UART channel to be initialized
 *                 Data
 *                     type: pointer to u8
 *                     Description: container for the received data byte received
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function receives a single byte from the desired UART channel
 *****************************************************************************/
extern u8 UART_receive (u8 ChannelNumber, u8* Data);


/*****************************************************************************
 * Function name: UART_configure
 *
 * parameters:  Input:
 *                 ChannelNumber
 *                     type: u8
                        Description: number of the UART channel to be initialized
 *                 Baudrate
 *                     type: u32
 *                     Description: Desired Baud rate for the chosen UART channel
 *                 StopBits
 *                     type: u8
 *                     Description: number of stop bits for the chosen UART channel
 *                 Parity
 *                     type: u8
 *                     Description: enable/disable parity and configure type of
 *                     				parity bits
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function configures the parameters of the desired UART channel
 *****************************************************************************/
extern u8 UART_configure (u8 ChannelNumber ,u32 Baudrate , u8 StopBits , u8 Parity );

/*****************************************************************************
 * Function name: UART_SetIntCbf
 *
 * parameters:  Input:
 *  *   			ChannelNumber
 *                     type: u8
 *                      Description: number of the UART channel
 *
 *                 IntCallBack
 *                     type: IntCallback_t
 *                      Description: pointer to callback function of the UART
 *                       	 	 	 channel interrupt
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function sets the call back function of the UART interrupt
 *****************************************************************************/
extern u8 UART_SetIntCbf ( u8 ChannelNumber , IntCallback_t IntCallBack );

/*****************************************************************************
 * Function name: UART_GetFlagStatus
 *
 * parameters:  Input:
 *   				ChannelNumber
 *                     type: u8
 *                      Description: number of the UART channel
 *               	Flag
 *                     type: u8
 *                      Description:	flag which to be read from the status
 *	                     				register
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function sets the call back function of the UART interrupt
 *****************************************************************************/
extern u8 UART_GetFlagStatus (u8 ChannelNumber , u8 Flag);

/*****************************************************************************
 * Function name: UART_CtrlFlag
 *
 * parameters:  Input:
 *                 ChannelNumber
 *                     type: u8
 *                        Description: number of the UART channel to be initialized
 *                 Flag
 *                 	   type: u8
 *                      Description: flag which to be set or cleared
 *                 state
 *                 	   type : u8
 *                 	   	Description: state of the flag (set or reset )
 *
 * Description: This function controls the state of the flags in UART
 *****************************************************************************/
extern void UART_CtrlFlag (u8 ChannelNumber , u8 Flag , u8 state);

/*****************************************************************************
 * Function name: UART_SendBreak
 *
 * parameters:  Input:
 *                 ChannelNumber
 *                     type: u8
 *                        Description: number of the UART channel to be initialized
 *
 * Description: This function sends Break frame on the specified UART channel
 *****************************************************************************/
extern void UART_SendBreak (u8 ChannelNumber);

/*****************************************************************************
 * Function name: LIN_Enable
 *
 * parameters:  Input:
 *                 ChannelNumber
 *                     type: u8
 *                        Description: number of the UART channel to be initialized
 *
 * Description:	This function enables the LIN functionality on the specified
 * 				UART channel
 *****************************************************************************/
extern void LIN_Enable (u8 ChannelNumber);


#endif
