/************************************************************************
 * File name: FLASH_interface.h
 *
 * Description:	This file contains the prototypes of the Flash driver
 * 				functions
 *
 * Owner: Ahmed Refaat
 * Date: 17/5/2020
 * Version 1.0
 *************************************************************************/

#ifndef FLASH_INTERFACE_H
#define FLASH_INTERFACE_H

/**************************** prototypes *********************************/

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
STD_ERROR FLASH_ErasePage (u32 EraseAddress);

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
STD_ERROR FLASH_MassErase (void);

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
STD_ERROR FLASH_ProgramWord(void * WriteAddress , u32 Data);

/************************************************************************
 * Function name: FLASH_Lock
 *
 * parameters:  Input:
 *					N/A
 *
 * Description:	This function locks the Flash controller
 ************************************************************************/
void FLASH_Lock(void);

/************************************************************************
 * Function name: FLASH_Lock
 *
 * parameters:  Input:
 *					N/A
 *
 * Description:	This function unlocks the Flash controller
 ************************************************************************/
void FLASH_Unlock(void);


#endif
