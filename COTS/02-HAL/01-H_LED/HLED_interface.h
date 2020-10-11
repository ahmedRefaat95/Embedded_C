/************************************************************************
 * File name: HLED_interface.c
 *
 * Description: This file contains prototypes for the LED HAL APIs
 *
 * Owner: Ahmed Refaat
 * Date: 28/2/2020
 * Version 1.0
 *************************************************************************/

#ifndef HLED_INTERFACE_H
#define HLED_INTERFACE_H

#define ON		1
#define OFF		0

/************************************************************************
 * Function name: HLED_init
 *
 * Parameters:  Inputs :NA
 *              Output: NA
 *              In/out: NA
 * Return: OK, NOT_OK
 * Description: a function to initializes all the configured LEDs
 ***************************************************************************/
STD_ERROR HLED_init(void);

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
STD_ERROR HLED_control(u8 Local_u8LedChannel , u8 Local_u8Status);

#endif
