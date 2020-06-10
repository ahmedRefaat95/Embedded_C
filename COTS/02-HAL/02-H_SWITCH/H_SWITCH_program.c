/************************************************************************
 * File name: H_SWITCH_program.c
 *
 * Description: This file contains the implementation of the Switch HAL
 * 				functions
 *
 * Owner: Ahmed Refaat
 * Date: 29/2/2020
 * Version 1.0
 *************************************************************************/

/***************************** Includes *********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "Sched_interface.h"
#include "H_SWITCH_interface.h"
#include "H_SWITCH_cfg.h"
#include "H_SWITCH_private.h"

/************************* Global variables *****************************/
u8 SwitchChannel =0;
u8 SwitchState[5] ;


Task_t HSwitch_Get = { HSwitch_Runnable , 5 };

extern const SWITCH_t Switch_ConfigParam [SWITCHES_NO];

/************************************************************************
 * Function name: HSwitch_Init
 *
 * Parameters:  Input: NA
 *              Output : STD_ERROR
 *
 * Description: This API shall initializes all the configured switches
 *****************************************************************************/
STD_ERROR HSwitch_Init(void)
{
	u8 Local_u8LoopIndex =0;
	STD_ERROR Local_Error = NOT_OK;

	const SWITCH_t * CfgPtr =0;

	for ( Local_u8LoopIndex=0; Local_u8LoopIndex < SWITCHES_NO; Local_u8LoopIndex++)
	{
		 CfgPtr = & (Switch_ConfigParam[Local_u8LoopIndex]);

		Local_Error = GPIO_Configure ( &(CfgPtr ->Pin_cfg) );
		/* Checking for the Active state of the switch */
		if (CfgPtr -> ON_status == ACTIVE_LOW)
		{
			/* Activating Pull up resistor */
			GPIO_WritePinVal(CfgPtr ->Pin_cfg.port,CfgPtr ->Pin_cfg.pin,HIGH);
		}
		else
		{
			/* Do nothing as pull down is activated by default */
		}
	}

	return Local_Error;
}

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
void HSwitch_GetSwitchState(u8 SwitchChannel,u8* State)
{
	*State = SwitchState[SwitchChannel] ;
}


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
void HSwitch_Runnable(void)
{
	static u8 Prestate [SWITCHES_NO] ={0};
	static u8 Counter  [SWITCHES_NO] ={0};
	u8 CurrentState;
	u8 Idx;

	const SWITCH_t * CfgPtr;

	for (Idx=0;Idx<SWITCHES_NO;Idx++)
	{
		CfgPtr = & (Switch_ConfigParam[Idx]);

			GPIO_GetPinVal( CfgPtr ->Pin_cfg.port , CfgPtr -> Pin_cfg.pin ,&CurrentState);

			if (CurrentState == Prestate[Idx])
			{
				Counter[Idx] ++;
			}
			else
			{
				Counter[Idx] = 0;
			}

			if (Counter[Idx] ==5)
			{
				SwitchState[Idx]= CurrentState;
				Counter[Idx] = 0;

				if ( CfgPtr -> ON_status == ACTIVE_HIGH )
				{
					// No change to the retrieved pin value
				}
				else
				{
					SwitchState[Idx] = !( SwitchState[Idx] );
				}
			}

			Prestate[Idx] = CurrentState ;
	}

}
