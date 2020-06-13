/************************************************************************
 * File name:H_LCD_private.h
 *
 * Description: This file contains static functions and private macros
 * 				for the LCD HAL
 *
 * Owner: Ahmed Refaat
 * Date: 26/3/2020
 * Version 1.0
 *************************************************************************/
#ifndef H_LCD_PRIVATE_H
#define H_LCD_PRIVATE_H

/***************************** Macros ***********************************/
#define CLCD_u8_LINE_TWO_ADD_OFFSET		0x40

#define CLCD_u8_SET_DDRAM_ADD_COMM		0x80

#define CLCD_DISPLAY_COMMAND			0b00001100


/************************* Type definitions  *****************************/
typedef struct
{
	u8 str [30];
	u16 Length;
}H_LCD_Data;


/*****************************************************************************
 * Function name: H_LCD_InitProcess
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function handles the logic of LCD initialization
 *****************************************************************************/
static void H_LCD_InitProcess(void);


/*****************************************************************************
 * Function name: H_LCD_WriteProcess
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function shall display data on LCD
 *****************************************************************************/
static void H_LCD_WriteProcess (void);

/*****************************************************************************
 * Function name: H_LCD_WriteProcess
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function clears display on LCD
 *****************************************************************************/
static void H_LCD_ClearProcess (void);

/*****************************************************************************
 * Function name: H_LCD_MoveCursorProcess
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function moves the cursor on the LCD
 *****************************************************************************/
static void H_LCD_MoveCursorProcess (void);

/*****************************************************************************
 * Function name: H_LCD_AdjustCursorProcess
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function changes the cursor characteristics in run time
 *****************************************************************************/
static void H_LCD_AdjustCursorProcess (void);

/*****************************************************************************
 * Function name: H_LCD_WriteCmd
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This API shall execute command on LCD
 *****************************************************************************/
static void H_LCD_WriteCmd	(u8 Copy_u8Cmd);

/*****************************************************************************
 * Function name: H_LCD_MoveCursorProcess
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This API shall send Data on the 8 data pins of LCD
 *****************************************************************************/
static void H_LCD_SetDataPort (u8 Copy_u8Data);

/*****************************************************************************
 * Function name: H_LCD_SetEnable
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This API activate the enable pin of the LCD
 *****************************************************************************/
static void H_LCD_SetEnable (void);

/*****************************************************************************
 * Function name: H_LCD_ClearEnables
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This API deactivate the enable pin of the LCD
 *****************************************************************************/
static void H_LCD_ClearEnable (void);

#endif
