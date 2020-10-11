/************************************************************************
 * File name: HLED_program.c
 *
 * Description: This file contains the implementation of the LED HAL
 * functions
 *
 * Owner: Ahmed Refaat
 * Date: 28/2/2020
 * Version 1.0
 *************************************************************************/

/***************************** Includes *********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "HLED_private.h"
#include "HLED_cfg.h"
#include "HLED_interface.h"

/* Extern the configuration array from HLED_cfg.c */
extern const LED_t LED_ConfigParam [LEDS_NO];

/************************************************************************
 * Function name: HLED_init
 *
 * Parameters:  Inputs :NA
 *              Output: NA
 *              In/out: NA
 * Return: OK, NOT_OK
 * Description: a function to initializes all the configured LEDs
 ***************************************************************************/
STD_ERROR HLED_init(void)
{
	u8 Local_u8LoopIndex =0;
	STD_ERROR Local_Error = NOT_OK;

	const LED_t * CfgPtr;

	for ( Local_u8LoopIndex=0; Local_u8LoopIndex < LEDS_NO; Local_u8LoopIndex++)
	{
		CfgPtr = &(LED_ConfigParam[Local_u8LoopIndex]);
		Local_Error = GPIO_Configure ( &(CfgPtr ->Pin_cfg) );
	}

	return Local_Error;
}

/************************************************************************
 * Function name: HLED_control
 *
 * Parameters:  Inputs : 1- LedChannel
 *							type: u8
 *                      	Description: LED number in configuration array
 *                       2- Status
 *                       	type: u8
 *                      	Description: status of the desired LED channel (ON ,OFF)
 *
 *              Output: NA
 *              In/out: NA
 * Return: OK, NOT_OK
 * Description: a function to  control the desired LED channel
 ***************************************************************************/
STD_ERROR HLED_control(u8 Local_u8LedChannel , u8 Local_u8Status)
{
	STD_ERROR Local_Error = NOT_OK;
	const LED_t * CfgPtr = & (LED_ConfigParam[Local_u8LedChannel]);

	if ( Local_u8Status == ON)
	{
		if ( CfgPtr -> ON_status == ACTIVE_HIGH )
		{
			Local_Error = GPIO_WritePinVal( CfgPtr ->Pin_cfg.port , CfgPtr -> Pin_cfg.pin ,HIGH);
		}
		else
		{
			Local_Error = GPIO_WritePinVal( CfgPtr -> Pin_cfg.port , CfgPtr -> Pin_cfg.pin ,LOW);
		}
	}
	else
	{
		if ( CfgPtr -> ON_status == ACTIVE_HIGH )
		{
			Local_Error = GPIO_WritePinVal( CfgPtr -> Pin_cfg.port , CfgPtr -> Pin_cfg.pin ,LOW);
		}
		else
		{
			Local_Error = GPIO_WritePinVal( CfgPtr -> Pin_cfg.port , CfgPtr -> Pin_cfg.pin ,HIGH);
		}
	}

	return Local_Error; 
}


