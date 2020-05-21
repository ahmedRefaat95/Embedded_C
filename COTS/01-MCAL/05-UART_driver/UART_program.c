/************************************************************************
 * File name: GPIO.c
 *
 * Description: This file contains the implementation of the GPIO driver
 * functions
 *
 * Owner: Ahmed Refaat
 * Date: 29/3/2020
 * Version 1.1
 ************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "UART_register.h"
#include "UART_interface.h"
#include "UART_private.h"


typedef enum
{
	IDLE,
	BUSY
}BufferState_t;


typedef struct 
{
	u8 * ptr;
	u32 position;
	u32 size ;
	BufferState_t state;
}DataBuffer_t;


static IntCallback_t IntCallBacks[3];

/* Array of UART channels base addresses */
UART_Register_t  * UART_channels [3] = {USART1_R,USART2_R,USART3_R};


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
extern u8 UART_init (u8 ChannelNumber, UART_Param_t * UART_config)
{
	u8 Result = STATUS_NOK;

	if ( (ChannelNumber >=1) || (ChannelNumber <=5))
	{
		/*Enabling the UART channel  */
		UART_channels[ChannelNumber] -> USART_CR1 |= UE;
		UART_channels[ChannelNumber] -> USART_CR1 |= UART_config ->WordLength;
		UART_channels[ChannelNumber] -> USART_CR1 |= UART_config ->WakeUpMethod;
		UART_channels[ChannelNumber] -> USART_CR1 |= UART_config ->ParityControl;
		UART_channels[ChannelNumber] -> USART_CR1 |= UART_config ->ParitySelection;
		UART_channels[ChannelNumber] -> USART_CR1 |= UART_config ->ParityErrorInt;
		/* clearing the TC flag */
		USART1_R -> USART_SR &= ~(1<<6);
		UART_channels[ChannelNumber] -> USART_CR1 |= UART_config ->TXEInt;
		UART_channels[ChannelNumber] -> USART_CR1 |= UART_config ->TCInt;
		UART_channels[ChannelNumber] -> USART_CR1 |= UART_config ->RXNEInt;
		UART_channels[ChannelNumber] -> USART_CR1 |= UART_config ->IDLEInt;
		UART_channels[ChannelNumber] -> USART_CR1 |= UART_config ->ReceiverWakeUp;
		UART_channels[ChannelNumber] -> USART_CR1 |= UART_config ->SendBreak;

		UART_channels[ChannelNumber] -> USART_CR2 |= UART_config ->StopBits;
		UART_channels[ChannelNumber] -> USART_CR2 |= UART_config ->ClockEnable;
		UART_channels[ChannelNumber] -> USART_CR2 |= UART_config ->ClockPol;
		UART_channels[ChannelNumber] -> USART_CR2 |= UART_config ->ClockPhase;
		UART_channels[ChannelNumber] -> USART_CR2 |= UART_config ->LastBitClockPulse;
		UART_channels[ChannelNumber] -> USART_CR2 |= UART_config ->LINBreakDetection;

		UART_channels[ChannelNumber] -> USART_CR3 |= UART_config ->DMAEnableTrans;
		UART_channels[ChannelNumber] -> USART_CR3 |= UART_config ->DMAEnableRec;
		UART_channels[ChannelNumber] -> USART_CR3 |= UART_config ->ErrorInt;
		/* Setting baud rate */
		UART_channels[ChannelNumber] -> USART_BRR |= UART_config ->UART_DIV;
		/* Enabling UART transmitter and receiver control */
		UART_channels[ChannelNumber] -> USART_CR1 |= (TE | RE);
	}
	else
	{
		Result = STATUS_NOK;
	}
	return Result;
}


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
extern u8 UART_send (u8 ChannelNumber , u8 Data)
{
	u8 Result = STATUS_NOK;

	UART_channels[ChannelNumber] -> USART_DR = Data;

	return Result;
}

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
extern u8 UART_receive (u8 ChannelNumber, u8* Data)
{
	u8 Result = STATUS_NOK;

	*Data = UART_channels[ChannelNumber] -> USART_DR ;

	return Result;
}

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
extern u8 UART_configure (u8 ChannelNumber ,u32 UARTDIV , u8 StopBits , u8 Parity )
{
	u8 Result = STATUS_NOK;

	if ( (ChannelNumber >=1) || (ChannelNumber <=5))
	{
		Result = STATUS_OK;

		/* Setting the BRR register with the UARTDIV value of the desired baudrate */
		UART_channels[ChannelNumber] -> USART_BRR = UARTDIV;


		UART_channels[ChannelNumber] -> USART_CR2 |= StopBits;


		UART_channels[ChannelNumber] -> USART_CR1 |= Parity;

	}
	return Result;
}

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
extern u8 UART_SetIntCbf ( u8 ChannelNumber , IntCallback_t IntCallBack )
{
	u8 Result = STATUS_NOK;
	if (IntCallBack)
	{
		IntCallBacks[ChannelNumber] = IntCallBack;
		Result = STATUS_OK;
	}
	else
	{
		Result = STATUS_NOK;
	}
	return Result;
}

/*****************************************************************************
 * Function name: UART_GetFlagStatus
 *
 * parameters:  Input:
 *                 Flag
 *                     type: u8
                        Description:	flag which to be read from the status
                        				register
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function sets the call back function of the UART interrupt
 *****************************************************************************/
extern u8 UART_GetFlagStatus (u8 ChannelNumber , u8 Flag)
{
	u8 FlagStatus = 0;

	FlagStatus = GET_BIT((UART_channels[ChannelNumber] ->USART_SR),Flag);

	return FlagStatus;
}

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
extern void UART_CtrlFlag (u8 ChannelNumber , u8 Flag , u8 state)
{
	if ( state == 0)
	{
		UART_channels[ChannelNumber] -> USART_SR &= ~ (1<<Flag);
	}
	else if ( state == 1)
	{
		UART_channels[ChannelNumber] -> USART_SR |= (1<<Flag);
	}

}

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
extern void UART_SendBreak (u8 ChannelNumber)
{
	UART_channels[ChannelNumber] -> USART_CR1 |= BREAK_CHAR;
}

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
extern void LIN_Enable (u8 ChannelNumber)
{
	UART_channels[ChannelNumber] -> USART_CR2 |= LIN_MODE_ENABLE;
}


void USART1_IRQHandler(void)
{
	if (IntCallBacks[0])
	{
		IntCallBacks[0]();
	}

}

void USART2_IRQHandler(void)
{
	if (IntCallBacks[1])
	{
		IntCallBacks[1]();
	}

}

void USART3_IRQHandler(void)
{

	if (IntCallBacks[2])
	{
		IntCallBacks[2]();
	}
}

