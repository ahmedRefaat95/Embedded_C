/************************************************************************
 * File name: H_LCD_cfg.h
 *
 * Description: This file contains the pre-build configuration parameters
 * 				for the LCD HAL
 *
 * Owner: Ahmed Refaat
 * Date: 26/3/2020
 * Version 1.0
 *************************************************************************/
#ifndef H_LCD_CONFIG_H
#define H_LCD_CONFIG_H

/***************************** Macros ***********************************/
/* Number of LCD pins connected to the controller*/
#define LCD_PINS		11

/* Configuring port and pin number of each LCD pin */
#define CLCD_u8_RS_PORT	PORTB
#define CLCD_u8_RS_PIN	PIN5

#define CLCD_u8_RW_PORT	PORTB
#define CLCD_u8_RW_PIN	PIN6

#define CLCD_u8_E_PORT	PORTB
#define CLCD_u8_E_PIN	PIN7


#define CLCD_u8_DATA_PORT PORTA

#define CLCD_u8_D0 PIN7
#define CLCD_u8_D1 PIN6
#define CLCD_u8_D2 PIN5
#define CLCD_u8_D3 PIN4
#define CLCD_u8_D4 PIN3
#define CLCD_u8_D5 PIN2
#define CLCD_u8_D6 PIN1
#define CLCD_u8_D7 PIN0


#endif
