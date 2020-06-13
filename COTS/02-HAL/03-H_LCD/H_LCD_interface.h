/************************************************************************
 * File name:  H_LCD_interface.h
 *
 * Description:	This file contains the prototypes of the LCD HAL
 * 				functions
 *
 * Owner: Ahmed Refaat
 * Date: 26/3/2020
 * Version 1.0
 *************************************************************************/
#ifndef H_LCD_INTERFACE_H
#define H_LCD_INTERFACE_H

/***************************** Macros ***********************************/
#define CLCD_u8_SHIFT_DISPLAY_RIGHT 0b00001110

#define CLCD_u8_FirstRow 			0b10000000
#define CLCD_u8_SecondRow 			0b11000000
#define CLCD_u8_CLR_DISP 			0b00000001

#define CLCD_u8_LINE_ONE	0
#define CLCD_u8_LINE_TWO	1

#define CLCD_CURSOR_BLINK_ON		0x01
#define CLCD_CURSOR_BLINK_OFF		0x00

#define CLCD_CURSOR_ON				0x02
#define CLCD_CURSOR_OFF				0x00

/************************************************************************
 * Function name: H_LCD_Init
 *
 * parameters:  Input:
 *                	N/A
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This API initializes the GPIO pins of LCD and it's
 * 				startup procedure
 **************************************************************************/
extern STD_ERROR H_LCD_Init(void);

/************************************************************************
 * Function name: H_LCD_Runnable
 *
 * parameters:  Input:
 *                 N/A
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function serves the user requests for the LCD
 **************************************************************************/
extern void H_LCD_Runnable (void);

/************************************************************************
 * Function name: H_LCD_Write
 *
 * parameters:  Input:
 *                 String
 *                     type: pointer to char
                        Description: points to the string which to be
                        			 displayed on LCD
 *                 Length
 *                     type: u8
 *                     Description: length of the passed string
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function writes the required string on the LCD
 *****************************************************************************/
extern STD_ERROR H_LCD_Write (const char * String , u8 Length);

/************************************************************************
 * Function name: H_LCD_Clear
 *
 * parameters:  Input:
 *                 N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function clears the LCD display
 *****************************************************************************/
extern STD_ERROR H_LCD_Clear (void);

/*****************************************************************************
 * Function name: H_LCD_PrintNumber
 *
 * parameters:  Input:
 *                 Number
 *                 	Type : u32
 *                 		Description: The number which to be displayed
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function prints a number on the LCD
 *****************************************************************************/
extern STD_ERROR H_LCD_PrintNumber(u32 Number);

/*****************************************************************************
 * Function name: H_LCD_GoToXYPos
 *
 * parameters:  Input:
 *                 XPos
 *                 	Type : u8
 *                 		Description: the horizontal position of the cursor
 *                 YPos
 *                 	Type : u8
 *                 		Description: the vertical position of the cursor
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function the LCD display
 *****************************************************************************/
extern STD_ERROR H_LCD_GoToXYPos(u8 XPos, u8 YPos);

/*****************************************************************************
 * Function name: H_LCD_ConfigCursor
 *
 * parameters:  Input:
 *                 CursorDisplay
 *                 	Type : u8
 *                 		Description: Mask to control the cursor visibility on
 *                 					 the LCD
 *                 CursosBlink
 *                 	Type : u8
 *                 		Description: Mask to control the cursor blinking on
 *                 					 the LCD
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function configures the cursor on the LCD
 *****************************************************************************/
extern STD_ERROR H_LCD_ConfigCursor ( u8 CursorDisplay , u8 CursosBlink);


#endif
