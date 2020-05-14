/************************************************************************
 * File name: GPIO.c
 *
 * Description: This file contains the implementation of the GPIO driver
 * functions
 *
 * Owner: Ahmed Refaat
 * Date: 6/3/2020
 * Version 1.2
 ***************************************************************************/


/***************************** Includes ***********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"

/***************************************************************************
 * Function name: GPIO_Configure
 *
 * Parameters:  Input:
 *                 cfg_ptr
 *                 	type: pointer to constant structure (GPIO_t)
 *                  	Description: Address of the configuration structure
 *
 * Return: STD_ERROR (OK, NOT_OK)
 * Description: This function shall configure the GPIO pins
 * 				 ( single pin or a whole port )
 ***************************************************************************/
STD_ERROR GPIO_Configure(const GPIO_t * cfg_ptr) {
	STD_ERROR LocError = NOT_OK;
	u8 tmpPin = 0;
	u32 TempRegisterValue;
	u16 Iterator = 0;

	if ( cfg_ptr != NULL)
	{
		LocError = OK;
		for (Iterator = 0; Iterator < 16; Iterator++) {
			if( ( (cfg_ptr->pin) >> Iterator )& 0x01 )
			{
				if (Iterator <= 7) {

					/* Clear 4 bits of mode configuration*/
					TempRegisterValue =  (cfg_ptr-> port -> GPIO_CRL) & ~(CLR_MODE_BITS << (Iterator * 4));
					/* Set the mode 4 bits */
					TempRegisterValue |= (cfg_ptr->mode << (Iterator * 4));
					TempRegisterValue |= (cfg_ptr->speed << (Iterator * 4));

					cfg_ptr-> port -> GPIO_CRL = TempRegisterValue;
				}
				else if (Iterator <= 15)
				{
					tmpPin = Iterator - 8;
					/* Clear 4 bits of mode configuration*/
					TempRegisterValue = (cfg_ptr->port->GPIO_CRH) & ~(CLR_MODE_BITS << (tmpPin * 4));
					/* Set the mode 4 bits */
					TempRegisterValue|= (cfg_ptr->mode << (tmpPin * 4));
					TempRegisterValue |= (cfg_ptr->speed << (tmpPin * 4));

					cfg_ptr->port->GPIO_CRH = TempRegisterValue;
				}
			}
			else
			{
				/* The pin does not need to be configured */
			}
		}

	}
	else
	{
		LocError = NOT_OK;
	}

	return LocError;
}


/************************************************************************
 * Function name: GPIO_WritePinVal
 *
 * Parameters:  Input:
 *
 * 				Port
 *                 	type: pointer to constant structure (GPIO_registers)
 *						Description:	PORT address , ranges are :
 * 										1- PORTA
 * 										2- PORTB
 * 										3- PORTC
 *				Pin
 *					type: u32
 *						Description:	Pin number masks , ranges are :
 * 										PINx ( 1 ... 15 )
 *
 * 				Val
 *                 	type: u8
 *                  	Description:	Pin value , ranges are :
 * 										1- HIGH
 * 										2- LOW
 *
 * Return: STD_ERROR (OK, NOT_OK)
 * Description: This function shall write a value on the GPIO pins
 ************************************************************************/
STD_ERROR GPIO_WritePinVal(GPIO_registers* Port, u32 Pin, u8 Val) {
	STD_ERROR LocError = NOT_OK;

	if ( ( Port != NULL) && CHECK_PIN(Pin) && CHECK_PORT(Port) )
	{
		LocError = OK;

		if (Val == HIGH)
		{
			Port->GPIO_BSRR = Pin;
		}
		else if (Val == LOW)
		{
			Port->GPIO_BRR =  Pin;
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

	return LocError;
}

/************************************************************************
 * Function name: GPIO_GetPinVal
 *
 * Parameters:	Input:
 *
 * 				Port
 *                 	type: pointer to constant structure (GPIO_registers)
 *						Description:	PORT address , ranges are :
 * 										1- PORTA
 * 										2- PORTB
 * 										3- PORTC
 *				Pin
 *					type: u32
 *						Description:	Pin number masks , ranges are :
 * 										PINx ( 1 ... 15 )
 *
 * 				Val
 *                 	type: u8
 *                  	Description:	Pin value , ranges are :
 * 										1- HIGH
 * 										2- LOW
 *
 *				Input/Output :
 *					type: pointer to u8
 *                  	Description:	The value of desired pin of type u8
 *
 * Return: STD_ERROR (OK, NOT_OK)
 * Description: This function shall get the pin value of desired GPIO pins
 ************************************************************************/
STD_ERROR GPIO_GetPinVal(GPIO_registers* Port, u32 Pin ,u8* Data) {
	STD_ERROR LocError = NOT_OK;

	if ( ( Port != NULL) && CHECK_PIN(Pin) && CHECK_PORT(Port) )
	{
		LocError = OK;
		if (Port->GPIO_IDR & Pin) {
			*Data = 1;
		} else {
			*Data = 0;
		}

	}
	else
	{
		LocError = NOT_OK;
	}

	return LocError;
}
