/************************************************************************
 * File name: HLED_private.h
 *
 * Description: This file contains static functions and private macros
 * 				for the LED HAL
 *
 * Owner: Ahmed Refaat
 * Date: 28/2/2020
 * Version 1.0
 *************************************************************************/

#ifndef HLED_PRIVATE_H
#define HLED_PRIVATE_H

/******************************* Macros **********************************/
#define ACTIVE_HIGH		1
#define ACTIVE_LOW		2

/************************* Type definitions *****************************/
typedef struct
{
	GPIO_t Pin_cfg;
	u8 ON_status;
}LED_t;


#endif

