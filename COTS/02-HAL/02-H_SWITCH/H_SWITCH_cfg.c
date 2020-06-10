/************************************************************************
 * File name: H_SWITCH_cfg.c
 *
 * Description: This file contains the linking time configuration parameters
 * 				for the Switch HAL
 *
 * Owner: Ahmed Refaat
 * Date: 29/2/2020
 * Version 1.0
 *************************************************************************/

/***************************** Includes *********************************/
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "H_SWITCH_private.h"
#include "H_SWITCH_interface.h"
#include "H_SWITCH_cfg.h"


/* Configuration array containing the parameters of each switch */
const SWITCH_t  Switch_ConfigParam[SWITCHES_NO] =
{ 
	{	.Pin_cfg.port = PORTB ,
		.Pin_cfg.pin = PIN1 ,
		.Pin_cfg.mode = INPUT_PULLUP_DOWN,
		.Pin_cfg.speed= INPUT_SPEED,
		.ON_status = ACTIVE_LOW }
		
	,{	.Pin_cfg.port = PORTA ,
		.Pin_cfg.pin = PIN12 ,
		.Pin_cfg.mode = INPUT_PULLUP_DOWN,
		.Pin_cfg.speed= INPUT_SPEED,
		.ON_status = ACTIVE_LOW }

	,{	.Pin_cfg.port = PORTB ,
		.Pin_cfg.pin = PIN4 ,
		.Pin_cfg.mode = INPUT_PULLUP_DOWN,
		.Pin_cfg.speed= INPUT_SPEED,
		.ON_status = ACTIVE_LOW }

	,{	.Pin_cfg.port = PORTB ,
		.Pin_cfg.pin = PIN10 ,
		.Pin_cfg.mode = INPUT_PULLUP_DOWN,
		.Pin_cfg.speed= INPUT_SPEED,
		.ON_status = ACTIVE_LOW }

	,{	.Pin_cfg.port = PORTB ,
		.Pin_cfg.pin = PIN11 ,
		.Pin_cfg.mode = INPUT_PULLUP_DOWN,
		.Pin_cfg.speed= INPUT_SPEED,
		.ON_status = ACTIVE_LOW }};
