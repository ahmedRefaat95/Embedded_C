/************************************************************************
 * File name: HLED_interface.h
 *
 * Description: This file contains prototypes for the LED HAL APIs
 *
 * Owner: Ahmed Refaat
 * Date: 28/2/2020
 * Version 1.0
 *************************************************************************/

#ifndef H_SWITCH_INTERFACE_H
#define H_SWITCH_INTERFACE_H

#define SWITCH1	0
#define SWITCH2	1


/************************************************************************
 * Function name: HSwitch_Init
 *
 * Parameters:  Input: NA
 *              Output : STD_ERROR
 *
 * Description: This API shall initializes all the configured switches
 *****************************************************************************/
STD_ERROR HSwitch_Init(void);


/************************************************************************
 * Function name: HSwitch_GetSwitchState
 *
 * Parameters:  Input:
 *                	SwitchChannel
 *                     type: u8
 *                       Description:	LED number in configuration array
 * 				I/O:
 * 					State
 *                     type: pointer to u8
 *                       Description:	container for the LED state
 *                       				ranges : ON ,OFF
 * Return: STD_ERROR (OK, NOT_OK)
 * Description: This API shall get status of the required switch
 ************************************************************************/
void HSwitch_GetSwitchState(u8 SwitchChannel,u8* State);


/************************************************************************
*   Function name: HSwitch_Runnable
*	Inputs	:
*				N/A
*	Outputs :
*				N/A
*
*	Description: This API monitors the state of the switch and handles
*					the de-bouncing
************************************************************************/
void HSwitch_Runnable(void);


#endif
