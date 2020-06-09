/************************************************************************
 * File name: FLASH_program.c
 *
 * Description: This file contains the implementation of the Flash driver
 * functions
 *
 * Owner: Ahmed Refaat
 * Date: 17/5/2020
 * Version 1.0
 *************************************************************************/

/***************************** Includes *********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "FLASH_register.h"
#include "FLASH_interface.h"
#include "FLASH_private.h"

/************************************************************************
 * Function name: FLASH_ErasePage
 *
 * parameters:  Input:
 *                 EraseAddress
 *                     type: u32
 *                       Description:	Address of the page to be erased
 *										in the flash memory
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function erases a page in the flash memory
 ************************************************************************/
STD_ERROR FLASH_ErasePage (u32 EraseAddress)
{
	STD_ERROR LocalError = OK;

	if ( (FLASHx -> FLASH_CR) & FLASH_CR_LOCK )
	{
		/* FLASH_CR is locked */
	}
	else
	{
		FLASHx ->FLASH_CR |= FLASH_CR_PER ;
		FLASHx ->FLASH_AR = EraseAddress;
		FLASHx ->FLASH_CR |= FLASH_CR_STRT;

		while (FLASHx ->FLASH_SR & FLASH_SR_BSY);

		/* Clearing the program erase flag  */
		FLASHx ->FLASH_CR &= ~(FLASH_CR_PER);


		/* Clearing the End of operation flag  */
		FLASHx ->FLASH_SR |= FLASH_SR_EOP;


	}

	return LocalError;
}

/************************************************************************
 * Function name: FLASH_MassErase
 *
 * parameters:  Input:
 *                 N/A
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description:	This function performs a mass erase of the whole
 * 				Flash memory
 ************************************************************************/
STD_ERROR FLASH_MassErase (void)
{
	STD_ERROR LocalError = OK;

	if ( (FLASHx -> FLASH_CR) & FLASH_CR_LOCK )
	{
		/* FLASH_CR is locked */
	}
	else
	{
		FLASHx ->FLASH_CR |= FLASH_CR_MER ;
		FLASHx ->FLASH_CR |= FLASH_CR_STRT;

		while (FLASHx ->FLASH_SR & FLASH_SR_BSY);

		/* Clearing the End of operation flag  */
		FLASHx ->FLASH_SR |= FLASH_SR_EOP;

		/* Clearing the master erase flag  */
		FLASHx ->FLASH_CR &= ~(FLASH_CR_MER);

	}

	return LocalError;
}

/************************************************************************
 * Function name: FLASH_ProgramWord
 *
 * parameters:  Input:
 *					WriteAddress
 *                     type: pointer to void
 *                       Description:	Address of the desired page to
 *                       				write at
 *					Data
 *                     type: u32
 *                       Description:	Data which will be written at
 *                       				the desired page
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description:	This function writes a word at the desired Flash memory
 * 				address
 ************************************************************************/
STD_ERROR FLASH_ProgramWord(void * WriteAddress , u32 Data)
{
	STD_ERROR LocalError = OK;

	if ( (FLASHx -> FLASH_CR) & FLASH_CR_LOCK )
	{
		/* FLASH_CR is locked */
	}
	else
	{
		while ( FLASHx ->FLASH_SR & FLASH_SR_BSY);

		FLASHx ->FLASH_CR |= FLASH_CR_PG ;
		* ((u16 * ) WriteAddress) =(u16) Data;

		while ( FLASHx ->FLASH_SR & FLASH_SR_BSY);

		/* Clearing the End of operation flag  */
		FLASHx ->FLASH_SR |= FLASH_SR_EOP;


		FLASHx ->FLASH_CR |= FLASH_CR_PG ;
		* ((u16 * ) WriteAddress+1) =(u16) (Data>>16);

		while ( FLASHx ->FLASH_SR & FLASH_SR_BSY);

		/* Clearing the End of operation flag  */
		FLASHx ->FLASH_SR |= FLASH_SR_EOP;

		/* Clearing the program write flag  */
		FLASHx ->FLASH_CR &= ~(FLASH_CR_PG);

		if ( * ((u32 * ) WriteAddress) == Data)
		{
			LocalError = OK;
		}
		else
		{
			LocalError = NOT_OK;
		}

	}

	return LocalError;
}

/************************************************************************
 * Function name: FLASH_Lock
 *
 * parameters:  Input:
 *					N/A
 *
 * Description:	This function locks the Flash controller
 ************************************************************************/
void FLASH_Lock(void)
{
	FLASHx -> FLASH_CR |= FLASH_CR_LOCK;
}

/************************************************************************
 * Function name: FLASH_Lock
 *
 * parameters:  Input:
 *					N/A
 *
 * Description:	This function unlocks the Flash controller
 ************************************************************************/
void FLASH_Unlock(void)
{
	FLASHx -> FLASH_KEYR = FLASH_KEY1;
	FLASHx -> FLASH_KEYR = FLASH_KEY2;
}
