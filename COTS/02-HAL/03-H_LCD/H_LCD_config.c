/************************************************************************
 * File name: H_LCD_cfg.c
 *
 * Description: This file contains the linking time configuration parameters
 * 				for the LCD HAL
 *
 * Owner: Ahmed Refaat
 * Date: 26/3/2020
 * Version 1.0
 *************************************************************************/

/***************************** Includes *********************************/
#include "STD_TYPES.h"
#include "GPIO_interface.h"
#include "H_LCD_private.h"
#include "H_LCD_interface.h"
#include "H_LCD_config.h"

/* Configuration array containing the pin configurations of LCD pins */
const GPIO_t  LCD_ConfigParam[LCD_PINS] =
{
	{	.port  = CLCD_u8_RS_PORT ,
		.pin   = CLCD_u8_RS_PIN ,
		.mode  = OUTPUT_PUSH_PULL,
		.speed = OUTPUT_SPEED_2M	}

	,{	.port  = CLCD_u8_RW_PORT ,
		.pin   = CLCD_u8_RW_PIN ,
		.mode  = OUTPUT_PUSH_PULL,
		.speed = OUTPUT_SPEED_2M	}

	,{	.port  = CLCD_u8_E_PORT ,
		.pin   = CLCD_u8_E_PIN ,
		.mode  = OUTPUT_PUSH_PULL,
		.speed = OUTPUT_SPEED_2M	}

	,{	.port  = CLCD_u8_DATA_PORT ,
		.pin   = CLCD_u8_D0 ,
		.mode  = OUTPUT_PUSH_PULL,
		.speed = OUTPUT_SPEED_2M }

	,{	.port  = CLCD_u8_DATA_PORT ,
		.pin   = CLCD_u8_D1 ,
		.mode  = OUTPUT_PUSH_PULL,
		.speed = OUTPUT_SPEED_2M }

	,{	.port  = CLCD_u8_DATA_PORT ,
		.pin   = CLCD_u8_D2 ,
		.mode  = OUTPUT_PUSH_PULL,
		.speed = OUTPUT_SPEED_2M }

	,{	.port  = CLCD_u8_DATA_PORT ,
		.pin   = CLCD_u8_D3 ,
		.mode  = OUTPUT_PUSH_PULL,
		.speed = OUTPUT_SPEED_2M }

	,{	.port  = CLCD_u8_DATA_PORT ,
		.pin   = CLCD_u8_D4 ,
		.mode  = OUTPUT_PUSH_PULL,
		.speed = OUTPUT_SPEED_2M	}

	,{	.port  = CLCD_u8_DATA_PORT ,
		.pin   = CLCD_u8_D5 ,
		.mode  = OUTPUT_PUSH_PULL,
		.speed = OUTPUT_SPEED_2M }

	,{	.port  = CLCD_u8_DATA_PORT ,
		.pin   = CLCD_u8_D6 ,
		.mode  = OUTPUT_PUSH_PULL,
		.speed = OUTPUT_SPEED_2M	 }

	,{	.port  = CLCD_u8_DATA_PORT ,
		.pin   = CLCD_u8_D7 ,
		.mode  = OUTPUT_PUSH_PULL,
		.speed = OUTPUT_SPEED_2M	 }

};



