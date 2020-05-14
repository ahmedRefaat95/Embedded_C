/************************************************************************
 * File name: STK_program.c
 *
 * Description: This file contains the implementation of the STK driver
 * functions
 *
 * Owner: Ahmed Refaat
 * Date:  8 March 2020
 * Version 1.0
 *************************************************************************/

/***************************** Includes **********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "STK_register.h"
#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"
#include "NVIC_interface.h"

/* Creating an object of STK_CallBack (pointer to function)  */
STK_cbf_t STK_CallBack;

/* Initializing the pointer with the base address of the STK registers */
STK_registers volatile * STK = (STK_registers *) STK_BASE_ADDRESS;

/*************************** Definitions ********************************/

/************************************************************************
 * Function name: STK_Init
 *
 * parameters:  Inputs :
 * 					N/A
 * 				Outputs :
 * 					N/A
 *
 * Description: This API shall initialize the sysTick timer
 ************************************************************************/
void STK_Init(void)
{
#if (PRESCALER == PRE_AHB_DIV_8)
	/* Clock source = AHB /8 */
	STK -> STK_CTRL &= ~(STK_CLKSOURCE);
#elif (PRESCALER == PRE_AHB)
	/* Clock source = AHB */
	STK -> STK_CTRL |= (STK_CLKSOURCE);
#endif
	/* STK exception request enable */
	STK -> STK_CTRL |= STK_INT;
}

/************************************************************************
 * Function name: STK_Start
 *
 * parameters:  Inputs :
 * 					N/A
 * 				Outputs :
 * 					N/A
 *
 * Description: This API shall start the sysTick timer
 ************************************************************************/
void STK_Start(void)
{
	/* Start System Timer */
	STK -> STK_CTRL |= STK_ENABLE;
}

/************************************************************************
 * Function name: STK_Stop
 *
 * parameters:  Inputs :
 * 					N/A
 * 				Outputs :
 * 					N/A
 *
 * Description: This API shall stop the sysTick timer
 ************************************************************************/
void STK_Stop(void)
{
	/* Stop System Timer */
	STK -> STK_CTRL &= ~(STK_ENABLE);
}


/************************************************************************
 * Function name: STK_SetTime
 *
 * parameters:  Input:
 *                 Time_us
 *                     type: u32
                        Description: Required time in microseconds
 *                 InputClock
 *                     type: u32
 *                     Description: the input clock speed of the sysTick timer
 *
 * Description: This API shall load the sysTick timer with the value of
 * 				needed time in us
 *************************************************************************/
void STK_SetTime (u32 Time_us , const u32 InputClock)
{
#if (PRESCALER == PRE_AHB_DIV_8)
	/* Clock source = AHB /8 */
	STK ->STK_LOAD = (u32)( (f32)Time_us / (8/(f32)InputClock) );
#elif (PRESCALER == PRE_AHB)
	/* Clock source = AHB */
	STK ->STK_LOAD = (u32)( (f32)Time_us / (1/(f32)InputClock) );
#endif

}

/************************************************************************
 * Function name: STK_SetCallBack
 *
 * parameters:  Input:
 *              	App_cbf
 *                     type: u32
 *                      Description: pointer to the the desired call
 *                      			 back function
 *				Outputs :
 * 					N/A
 *
 * Description: This API shall load the set the call back function of the
 * 				SysTick handler
 ************************************************************************/
void STK_SetCallBack(STK_cbf_t App_cbf)
{
	STK_CallBack = App_cbf;
}

/* SystTick Handler */
void SysTick_Handler(void)
{
	/* Checking if the pointer is initialized */
	if ( STK_CallBack )
	{
		STK_CallBack();
	}
	else
	{
		/* Do nothing as the pointer is NULL */
	}
}
