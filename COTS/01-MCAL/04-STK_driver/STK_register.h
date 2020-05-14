/************************************************************************
 * File name: STK_register.h
 *
 * Description: This file contains the defines of the STK registers
 *
 * Owner: Ahmed Refaat
 * Date:  8 March 2020
 * Version 1.0
 ***************************************************************************/
#ifndef STK_REGISTER_H
#define STK_REGISTER_H

/***************************** Macros ***********************************/
#define STK_BASE_ADDRESS  (u32)0xE000E010

/***************************** Type definitions ***************************/
typedef struct 
{
	u32 STK_CTRL;
	u32 STK_LOAD;
	u32 STK_VAL;
	
}STK_registers;


#endif
