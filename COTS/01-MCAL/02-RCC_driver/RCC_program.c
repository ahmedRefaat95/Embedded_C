/************************************************************************
 * File name: RCC_program.c
 *
 * Description: This file contains the implementation of the RCC driver
 * functions
 *
 * Owner: Ahmed Refaat
 * Date: 6/3/2020
 * Version 1.1
 ***************************************************************************/

/***************************** Includes ***********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"

/* Initializing the pointer with the base address of the RCC registers */
RCC_Registers volatile * RCC = (RCC_Registers *) RCC_BASE_ADDRESS;

/************************************************************************
 * Function name: RCC_STD_ERROR_ControlClock
 *
 * parameters:  Input:
 *                 Copy_32ClockType
 *                     type: u32
                        Description: Clock sources (HSI_CLK,HSE_CLK,PLL_CLK)
 *                 Copy_u8Status
 *                     type: u8
 *                     Description: control the clock source (ON,OFF)
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function enables or disables the clock sources (HSI-HSE-PLL) of the system
 *****************************************************************************/
STD_ERROR RCC_STD_ERROR_ControlClock(u32 Copy_32ClockType, u8 Copy_u8Status) {
	STD_ERROR LocError = NOT_OK;

	if ( CHECK_CLOCK_SOURCES(Copy_32ClockType) )
	{
		LocError = OK;
		switch (Copy_u8Status) {
		case ON:
			RCC->CR |= Copy_32ClockType;
			break;
		case OFF:
			RCC->CR &= ~Copy_32ClockType;
			break;
		default:
			LocError = NOT_OK;
		}
	}
	else
	{
		LocError = NOT_OK;
	}

	return LocError;
}
/************************************************************************
 * Function name: RCC_STD_ERROR_SelectSysClock
 *
 * parameters:  Input:
 *                 Copy_u32SysClock
 *                     type: u32
                        Description: system clock (SYSTEM_HSI,SYSTEM_HSE,SYSTEM_PLL)
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function selects one of the clock sources(HSI-HSE-PLL) as the system clock
 *****************************************************************************/
STD_ERROR RCC_STD_ERROR_SelectSysClock(u32 Copy_u32SysClock) {
	STD_ERROR LocError = OK;
	u32 tmp = 0;

	switch (Copy_u32SysClock) {
	case SYSTEM_HSI:
		if (RCC->CR & HSI_RDY) {
			LocError = OK;
		} else {
			LocError = NOT_OK;
		}
		break;

	case SYSTEM_HSE:
		if (RCC->CR & HSE_RDY) {
			LocError = OK;
		} else {
			LocError = NOT_OK;
		}
		break;

	case SYSTEM_PLL:
		if (RCC->CFGR & PLL_RDY) {
			LocError = OK;
		} else {
			LocError = NOT_OK;
		}
		break;

	default:
		LocError = NOT_OK;
	}

	tmp = (RCC->CFGR & SYSTEM_CLEAR);
	tmp |= Copy_u32SysClock;
	RCC->CFGR = tmp;

	return LocError;
}
/************************************************************************
 * Function name: RCC_PLL_CLockSource
 *
 * parameters:  Input:
 *                 PLL_Source
 *                     type: u8
 *                     Description: PLL clock source (PLL_HSI,PLL_HSE,PLL_HSE_2)
 *                 Copy_u32PllMult
 *                     type: u32
 *                     Description: PLL multiplier value(PLL_x2,PLL_x3...PLL_x16)
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function selects PLL clock source (HSI - HSE - HSE/2)
 *****************************************************************************/
STD_ERROR RCC_PLL_CLockSource (u8 PLL_Source,u32 Copy_u32PllMult) {

	STD_ERROR LocError = NOT_OK;
	u32 temp = 0;

	if ( CHECK_PLL_SRC(PLL_Source) && CHECK_PLL_MULT(Copy_u32PllMult))
	{
		LocError = OK;

		if (RCC->CR & PLL_RDY)
		{
			switch (PLL_Source) {
			case PLL_HSI:
				if (RCC->CR & HSI_RDY) {
					LocError = OK;
				} else {
					LocError = NOT_OK;
				}
				/*Setting the HSI as PLL source */
				RCC->CFGR &= ~ PLL_SRC;
				/*Reading the RCC register and clearing the PLLMULL BITS */
				temp = RCC->CFGR & (CLR_MUL_BITS);
				/* Setting the PLLMULL BITS according to the input values */
				temp |= Copy_u32PllMult;

				RCC->CFGR = temp;
				break;

			case PLL_HSE:
				if (RCC->CR & HSE_RDY) {
					LocError = OK;
				} else {
					LocError = NOT_OK;
				}
				/* clearing the PLLXPTRE bit */
				RCC->CFGR &= ~PLLXPTRE;
				/* Setting the HSE as PLL source */
				RCC->CFGR |= PLL_SRC;
				/*Reading the RCC register and clearing the PLLMULL BITS */
				temp = RCC->CFGR & CLR_MUL_BITS;
				temp |= Copy_u32PllMult;
				/* Setting the PLLMULL BITS according to the input values */
				RCC->CFGR = temp;
				break;

			case PLL_HSE_2:
				if (RCC->CR & HSE_RDY) {
					LocError = OK;
				} else {
					LocError = NOT_OK;
				}
				/* Setting the PLLXPTRE bit */
				RCC->CFGR |= PLLXPTRE;
				/* Setting the HSE as PLL source */
				RCC->CFGR |= PLL_SRC;
				/*Reading the RCC register and clearing the PLLMULL BITS */
				temp = RCC->CFGR & PLL_MUL_BITS;
				temp |= Copy_u32PllMult;
				/* Setting the PLLMULL BITS according to the input values */
				RCC->CFGR = temp;
				break;
			default :
				LocError = NOT_OK;
				break;
			}
		}
		else
		{
			LocError = NOT_OK;
		}

	}
	else
	{
		LocError = NOT_OK;
	}

	/* Turning the PLL on */
	RCC_STD_ERROR_ControlClock(PLL_CLK, ON);

	return LocError;
}
/************************************************************************
 * Function name: RCC_MCO_Config
 *
 * parameters:  Input:
 *                 Copy_u32MCO_Source
 *                     type: u32
 *                     Description: MCO clock source (PLL_HSI,PLL_HSE,PLL_HSE_2)
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function selects MCO source (MCO_SYS - MCO_HSI - MCO_HSE - MCO_PLL)
 *****************************************************************************/
STD_ERROR RCC_MCO_Config(u32 Copy_u32MCO_Source) {
	STD_ERROR LocError = NOT_OK;
	u32 tmp = 0;

	if (CHECK_MCO_SOURCE(Copy_u32MCO_Source))
	{
		LocError = OK;
		tmp = (RCC->CFGR & MCO_BITS);
		tmp |= Copy_u32MCO_Source;
		RCC->CFGR = tmp;
	}
	else
	{
		LocError = NOT_OK;
	}


	return LocError;
}
/************************************************************************
 * Function name: RCC_ControlPeripheralClock
 *
 * parameters:  Input:
 *                 Bus
 *                     type: u8
 *                     Description: BUS type (PLL_HSI,PLL_HSE,PLL_HSE_2)
 *                 Copy_u32Peripheral
 *                     type: u32
 *                     Description: Desired peripheral to be enabled/disabled (AHB_x,APB1_x,APB2_x)
 *                 Copy_u8Status
 *                     type: u8
 *                     Description: Status of the desired peripheral (ON,OFF)
 *
 * Description: This function enables or disables the desired peripheral on its corresponding Bus
 *****************************************************************************/
STD_ERROR RCC_ControlPeripheralClock(u8 Bus , u32 Copy_u32Peripheral, u8 Copy_u8Status)
{
	STD_ERROR LocError = NOT_OK;
	if (CHECK_BUS(Bus))
	{
		LocError = OK;
		switch (Copy_u8Status) {
		case ON:
			switch (Bus) {
			case AHB:
				RCC->AHBENR |= Copy_u32Peripheral;
				break;
			case APB1:
				RCC->APB1ENR |= Copy_u32Peripheral;
				break;
			case APB2:
				RCC->APB2ENR |= Copy_u32Peripheral;
				break;
			}
			break;

			case OFF:
				switch (Bus) {
				case AHB:
					RCC->AHBENR &= ~Copy_u32Peripheral;
					break;
				case APB1:
					RCC->APB1ENR &= ~Copy_u32Peripheral;
					break;
				case APB2:
					RCC->APB2ENR &= ~Copy_u32Peripheral;
					break;

				}
				break;
		}
	}
	else
	{
		LocError = NOT_OK;
	}
	return LocError;
}

/************************************************************************
 * Function name: RCC_getClockSpeed
 *
 * parameters:  Input:
 *                 Bus
 *                     type: pointer to u32
 *                     Description: container to save the system clock speed
 *
 * Description: This function gets the clock speed of the system in MHz
 *****************************************************************************/
void RCC_GetSysClock ( u32 * ClockSpeed )
{

	u32 MultiplierVal =0;
	u32 PLL_source =0;

	if ( !(RCC->CFGR & SWS_BITS))
	{
		* ClockSpeed = HSI_SPEED;

	}
	else if  (RCC->CFGR & SWS_HSE)
	{
		* ClockSpeed = HSE_SPEED;
	}
	else if (RCC->CFGR & SWS_PLL)
	{
		if ( RCC->CFGR & PLL_SRC)
		{
			// checking if HSE or HSE_Div_2
			if (RCC->CFGR & PLLXPTRE)
			{
				PLL_source = HSE_SPEED_div2;
			}
			else
			{
				PLL_source = HSE_SPEED;
			}
		}
		else
		{
			PLL_source = HSI_SPEED;
		}
		MultiplierVal = ( (RCC->CFGR & PLL_MUL_BITS) >> 18 ) +2;
		* ClockSpeed = (PLL_source * MultiplierVal);
	}
	else
	{
		//Error
	}

}

/************************************************************************
 * Function name: RCC_GetAHBClock
 *
 * parameters:  Input:
 *                 AHB_Speed
 *                     type: pointer to f32
 *                     Description: container to save the AHB bus clock speed
 *
 * Description: This function gets the clock speed of the AHB bus in MHz
 *****************************************************************************/
void RCC_GetAHBClock (f32 * AHB_Speed)
{
	u16 AHB_preValues [8] = {2,4,8,16,64,128,256,512};
	u32 index;
	u32 SystemClockSpeed ;
	u32 AHB_prescaler;

	RCC_GetSysClock ( &SystemClockSpeed);

	if ( !((RCC->CFGR & HPRE_BITS) >> 7) )
	{
		* AHB_Speed = (f32)SystemClockSpeed;
	}
	else
	{
		index = ( (RCC->CFGR & HPRE_BITS) >> 4 )-8;
		AHB_prescaler = AHB_preValues [index];
		* AHB_Speed = (f32)SystemClockSpeed / AHB_prescaler ;
	}

}

void RCC_GetAPB2Clock (u32 * APB2_Speed)
{
	u8 APB2_preValues [4] = {2,4,8,16};
	u32 index;
	f32 AHBClockSpeed ;
	u32 APB2_prescaler;

	RCC_GetAHBClock ( &AHBClockSpeed);

	if ( !((RCC->CFGR & PPRE2_BITS) >> 13) )
	{
		* APB2_Speed = (f32)AHBClockSpeed;
	}
	else
	{
		index = ( (RCC->CFGR & PPRE2_BITS) >> 11 )-4;
		APB2_prescaler = APB2_preValues [index];
		* APB2_Speed = (f32)AHBClockSpeed / APB2_prescaler ;
	}

}

void RCC_GetAPB1Clock (u32 * APB1_Speed)
{
	u8 APB1_preValues [4] = {2,4,8,16};
	u32 index;
	f32 AHBClockSpeed ;
	u32 APB1_prescaler;

	RCC_GetAHBClock ( &AHBClockSpeed);

	if ( !((RCC->CFGR & PPRE1_BITS) >> 10) )
	{
		* APB1_Speed = (f32)AHBClockSpeed;
	}
	else
	{
		index = ( (RCC->CFGR & PPRE1_BITS) >> 8 )-4;
		APB1_prescaler = APB1_preValues [index];
		* APB1_Speed = (f32)AHBClockSpeed / APB1_prescaler ;
	}

}

