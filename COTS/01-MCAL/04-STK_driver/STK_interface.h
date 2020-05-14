/************************************************************************
 * File name: STK_program.c
 *
 * Description: This file contains the prototypes of the STK functions
 *
 * Owner: Ahmed Refaat
 * Date:  8 March 2020
 * Version 1.0
 ***************************************************************************/
#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H


/***************************** Macros ***********************************/
#define PRE_AHB			1
#define PRE_AHB_DIV_8	2

#define STK_CLKSOURCE	0x4
#define STK_INT			0x2
#define STK_ENABLE		0x1

/***************************** Type definitions ***************************/
typedef void (*STK_cbf_t) (void);

/**************************** Prototypes *********************************/

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
void STK_Init(void);

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
void STK_Start(void);

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
void STK_Stop(void);

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
void STK_SetTime (u32 Time_us , const u32 InputClock);

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
void STK_SetCallBack(STK_cbf_t App_cbf );



#endif
