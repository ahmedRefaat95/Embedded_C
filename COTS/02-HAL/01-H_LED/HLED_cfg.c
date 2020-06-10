/************************************************************************
 * File name: HLED_cfg.c
 *
 * Description: This file contains the linking time configuration parameters
 * 				for the LED HAL
 *
 * Owner: Ahmed Refaat
 * Date: 28/2/2020
 * Version 1.0
 *************************************************************************/

/***************************** Includes *********************************/
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "HLED_private.h"
#include "HLED_interface.h"
#include "HLED_cfg.h"

/* Configuration array containing the parameters of each LED connected to the system */
const LED_t  LED_ConfigParam[LEDS_NO] =
{ 
	{	.Pin_cfg.port = PORTC ,
		.Pin_cfg.pin = PIN13 ,
		.Pin_cfg.mode = OUTPUT_PUSH_PULL,
		.Pin_cfg.speed= OUTPUT_SPEED_10M,
		.ON_status = ACTIVE_LOW }
		
	,{	.Pin_cfg.port = PORTB ,
		.Pin_cfg.pin = PIN12 ,
		.Pin_cfg.mode = OUTPUT_PUSH_PULL,
		.Pin_cfg.speed= OUTPUT_SPEED_10M,
		.ON_status = ACTIVE_HIGH }

	,{	.Pin_cfg.port = PORTB ,
		.Pin_cfg.pin = PIN13 ,
		.Pin_cfg.mode = OUTPUT_PUSH_PULL,
		.Pin_cfg.speed= OUTPUT_SPEED_10M,
		.ON_status = ACTIVE_HIGH }
};

