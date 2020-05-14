/************************************************************************
 * File name: NVIC_program.c
 *
 * Description: This file contains the implementation of the NVIC driver
 * functions
 *
 * Owner	: Ahmed Refaat
 * Date		: 17/2/2020
 * Version	: 1.0
 ***************************************************************************/
#include "STD_TYPES.h"
#include "NVIC_register.h"
#include "NVIC_interface.h"


NVIC_registers volatile * NVIC_Ptr = NVIC_BASE_ADDRESS;


/************************************************************************
 * Function name: NVIC_SetIntPriorityGrouping
 *
 * parameters:  Input:
 *                 PriorityGrouping
 *                     type: u32
 *                       Description: configuration for number of preemption bits
 *                       			  and subgroup bits
 *
 * Description: a function to configure number of preemption bits and subgroup bits*
 ***************************************************************************/
void NVIC_SetIntPriorityGrouping ( u32 PriorityGrouping)
{
	SCB_AIRCR = PriorityGrouping;
}
/************************************************************************
 * Function name: NVIC_SetEnable
 *
 * parameters:  Input:
 *                 InterruptNumber
 *                     type: u8
 *                       Description: number of the interrupt to be enabled
 *
 * Description: a function to enable the desired interrupt *
 ***************************************************************************/
void NVIC_SetEnable(u8 InterruptNumber)
{
	NVIC_Ptr -> NVIC_ISER[InterruptNumber/32] |= 1<<(InterruptNumber%32);
}

/************************************************************************
 * Function name: NVIC_ClearEnable
 *
 * parameters:  Input:
 *                 InterruptNumber
 *                     type: u8
 *                       Description: number of the interrupt to be disabled
 *
 * Description: a function to disable the desired interrupt *
 ***************************************************************************/
void NVIC_ClearEnable (u8 InterruptNumber)
{
	NVIC_Ptr -> NVIC_ICER[InterruptNumber/32] |= 1<<(InterruptNumber%32);
}

/************************************************************************
 * Function name: NVIC_SetPending
 *
 * parameters:  Input:
 *                 InterruptNumber
 *                     type: u8
 *                       Description: number of the interrupt to be disabled
 *
 * Description: a function to set the pending bit of the desired interrupt *
 ***************************************************************************/
void NVIC_SetPending (u8 InterruptNumber)
{
	NVIC_Ptr -> NVIC_ISPR[InterruptNumber/32] |= 1<<(InterruptNumber%32);
}

/************************************************************************
 * Function name: NVIC_ClearPending
 *
 * parameters:  Input:
 *                 InterruptNumber
 *                     type: u8
 *                       Description: number of the interrupt to be disabled
 *
 * Description: a function to clear the pending bit of the desired interrupt *
 ***************************************************************************/
void NVIC_ClearPending (u8 InterruptNumber)
{
	NVIC_Ptr -> NVIC_ICPR[InterruptNumber/32] |= 1<<(InterruptNumber%32);
}

/************************************************************************
 * Function name: NVIC_GetActive
 *
 * parameters:  Input:
 *                 InterruptNumber
 *                 		type: u8
 *                      Description: number of the interrupt to be disabled
 *              In/out:
 *              		type: pointer to u8
 *						Description: container for the active interrupts
 *
 * Description: a function to get the active bits of the interrupts *
 ***************************************************************************/
void NVIC_GetActive (u8 InterruptNumber , u8* ActiveInterrupt)
{
	*ActiveInterrupt = (NVIC_Ptr -> NVIC_IABR[InterruptNumber/32]) & (1<<(InterruptNumber%32));
}

/************************************************************************
 * Function name: NVIC_SetPriority
 *
 * parameters:  Input:
 *					InterruptNumber
 *                 		type: u8
 *                      Description: number of the interrupt to be configured
 *					Priority
 *						type: u8
 *						Description: priority of the passed interrupt number
 *
 * Description: a function to set the priority of the desired interrupt number *
 ******************************************************************************/
void NVIC_SetPriority ( u8 InterruptNumber, u8 Priority)
{
	NVIC_Ptr -> NVIC_IPR[InterruptNumber] |= Priority;
}

/************************************************************************
 * Function name: NVIC_TriggerSoftwareInterrupt
 *
 * parameters:  Input:
 *                 InterruptNumber
 *                     type: u32
 *                       Description: number of the interrupt to be triggered
 *
 * Description: a function to trigger a software interrupt of the desired interrupt *
 ***************************************************************************/
void NVIC_TriggerSoftwareInterrupt (u32 InterruptNumber)
{
	NVIC_STIR = 0;
	NVIC_STIR |= InterruptNumber;
}

/************************************************************************
 * Function name: NVIC_SetPRIMASK
 *
 * Description: a function to set the Pri mask  *
 ******************************************************************************/
void NVIC_SetPRIMASK (void)
{
	asm ("MOV R0, #1");
	asm ("MSR PRIMASK, R0");
}

/************************************************************************
 * Function name: NVIC_SetPRIMASK
 *
 * Description: a function to clear the Pri mask  *
 ******************************************************************************/
void NVIC_ClearPRIMASK (void)
{
	asm ("MOV R0, #0");
	asm ("MSR PRIMASK, R0");
}

/************************************************************************
 * Function name: NVIC_SetPRIMASK
 *
 * Description: a function to set the Fault mask  *
 ******************************************************************************/
void NVIC_SetFAULTMASK (void)
{
	asm ("MOV R0, #1");
	asm ("MSR FAULTMASK, R0");
}

/************************************************************************
 * Function name: NVIC_SetPRIMASK
 *
 * Description: a function to set the Pri mask  *
 ******************************************************************************/
void NVIC_ClearFAULTMASK (void)
{
	asm ("MOV R0, #0");
	asm ("MSR FAULTMASK, R0");
}

/************************************************************************
 * Function name: NVIC_SetPRIMASK
 *
 * Description: a function to disable the Pri mask  *
 ******************************************************************************/
void NVIC_DisableBASEPRI (void)
{
	asm	("MOV R0, #0x0");
	asm	("MSR BASEPRI, R0");
}

/************************************************************************
 * Function name: NVIC_SetPRIMASK
 *
 * Description: a function to set the BasePri with the desired priority *
 ******************************************************************************/
void NVIC_WriteBASEPRI (u32 priority)
{
	//TODO : check the data sheet for the shift instructions
	asm ("MSR BASEPRI, R0");
}
