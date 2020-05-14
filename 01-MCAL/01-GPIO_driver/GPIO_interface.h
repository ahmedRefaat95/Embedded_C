/************************************************************************
 * File name: GPIO_interface.h
 *
 * Description: This file contains the prototypes of the GPIO driver
 * and the macros used by the user
 *
 * owner: Ahmed Refaat
 * date: 6/3/2020
 * version 1.2
 ************************************************************************/

#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

/***************************** Macros ***********************************/

#define HIGH	1
#define LOW		0

/* Pin masks */
#define PIN0	0x01
#define PIN1	0x02
#define PIN2	0x04
#define PIN3	0x08
#define PIN4	0x10
#define PIN5	0x20
#define PIN6	0x40
#define PIN7	0x80
#define PIN8	0x100
#define PIN9	0x200
#define PIN10	0x400
#define PIN11	0x800
#define PIN12	0x1000
#define PIN13	0x2000
#define PIN14	0x4000
#define PIN15	0x8000

/* Macro like function to check if the input Pin mask is valid */
#define CHECK_PIN(Pin)		(	(Pin == PIN0) || (Pin == PIN1) || (Pin == PIN2) || (Pin == PIN3) ||    	\
								(Pin == PIN4) || (Pin == PIN5) || (Pin == PIN6) || (Pin == PIN7) || 	\
								(Pin == PIN8) || (Pin == PIN9) ||	(Pin == PIN10) || (Pin == PIN11) ||   \
								(Pin == PIN12) || (Pin == PIN13) || (Pin == PIN14) ||(Pin == PIN15))


/* Mode bits mask in port configuration register */
#define CLR_MODE_BITS			0b1111

/* Pin configuration masks */
#define INPUT_ANALOG			0b0000
#define INPUT_FLOATING			0b0100
#define INPUT_PULLUP_DOWN		0b1000

#define OUTPUT_PUSH_PULL		0b0000
#define OUTPUT_OPEN_DRAIN		0b0100
#define OUTPUT_AF_PUSH_PULL		0b1000
#define OUTPUT_AF_OPEN_DRAIN	0b1100

#define INPUT_SPEED				0b00

#define OUTPUT_SPEED_2M			0b10
#define OUTPUT_SPEED_10M		0b01
#define OUTPUT_SPEED_50M		0b11


/* Base addresses of GPIO ports */
#define PORTA		(( GPIO_registers*)0x40010800)
#define PORTB		(( GPIO_registers*)0x40010C00)
#define PORTC		(( GPIO_registers*)0x40011000)

/* Macro like function to check if the input Port address is valid */
#define CHECK_PORT(Port)		((Port ==PORTA) || (Port == PORTB) || (Port ==PORTC))


/***************************** Type definitions ***************************/

/* structure for GPIO registers */
typedef struct
{
	u32 GPIO_CRL ;
	u32 GPIO_CRH ;
	u32 GPIO_IDR ;
	u32 GPIO_ODR ;
	u32 GPIO_BSRR;
	u32 GPIO_BRR ;
	u32 GPIO_LCKR;
}GPIO_registers;


/* Typedef for GPIO configuration parameters */
typedef struct
{
	GPIO_registers * port;
	u32 pin;
	u8 mode;
	u8 speed;

}GPIO_t;

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
STD_ERROR GPIO_Configure(const GPIO_t * cfg_ptr) ;

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
STD_ERROR GPIO_WritePinVal(GPIO_registers* Port, u32 Pin, u8 Val);

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
STD_ERROR GPIO_GetPinVal(GPIO_registers* Port, u32 Pin ,u8* Data);


#endif 
