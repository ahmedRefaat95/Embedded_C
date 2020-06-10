/************************************************************************
 * File name: H_SWITCH_private.h
 *
 * Description: This file contains static functions and private macros
 * 				for the Switch HAL
 *
 * Owner: Ahmed Refaat
 * Date: 29/2/2020
 * Version 1.0
 *************************************************************************/

#ifndef H_SWITCH_PRIVATE_H
#define H_SWITCH_PRIVATE_H

/****************************** Macros **********************************/
#define ACTIVE_HIGH		1
#define ACTIVE_LOW		2

/************************* Type definitions *****************************/
typedef struct
{
	GPIO_t Pin_cfg;
	u8 ON_status;
}SWITCH_t;


#endif
