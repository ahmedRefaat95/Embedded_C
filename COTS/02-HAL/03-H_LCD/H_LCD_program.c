/************************************************************************
 * File name: H_LCD_program.c
 *
 * Description: This file contains the implementation of the LCD HAL
 * 				functions
 *
 * Owner: Ahmed Refaat
 * Date: 26/3/2020
 * Version 1.0
 *************************************************************************/

/***************************** Includes *********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "Sched_interface.h"
#include "H_LCD_interface.h"
#include "H_LCD_private.h"
#include "H_LCD_config.h"


/************************* Type definitions  *****************************/

/* Defining the states of LCD initialization */
typedef enum
{
	S1,
	S2,
	S3,
	S4,
	S5
}InitState_t;

/* Defining the different states of LCD processes */
typedef  enum
{
	IdleProcess,
	WriteProcess,
	ClearProcess,
	MoveCursorProcess,
	AdjustCursorProcess
}Process_t;


/************************* Global variables *****************************/
extern Task_t InitializLCD = { H_LCD_Runnable , 5 };

/* Array of configuration parameters of LCD pins */
extern const GPIO_t LCD_ConfigParam[LCD_PINS];

static u8 DDRamAdd;
static u8 Init_complete ;
static InitState_t InitState;
static Process_t CurrProcess;
static u8 Enable ;

static u8 CursorConfig;

H_LCD_Data UserData;


/*************************************************************************
 * Function name: H_LCD_Init
 *
 * parameters:  Input:
 *                	N/A
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This API initializes the GPIO pins of LCD and it's
 * 				startup procedure
 **************************************************************************/
extern STD_ERROR H_LCD_Init(void)
{
	u8 Idx =0;
	STD_ERROR Local_Error = NOT_OK;

	for ( Idx=0; Idx < LCD_PINS; Idx++)
	{
		Local_Error = GPIO_Configure ( &LCD_ConfigParam[Idx] );
	}

	for ( Idx=0; Idx < LCD_PINS; Idx++)
	{
		GPIO_WritePinVal(LCD_ConfigParam[Idx].port,LCD_ConfigParam[Idx].pin,LOW);
	}

	return Local_Error;
}


/*************************************************************************
 * Function name: H_LCD_Runnable
 *
 * parameters:  Input:
 *                 N/A
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function serves the user requests for the LCD
 **************************************************************************/
extern void H_LCD_Runnable (void)
{

	if (Init_complete)
	{

		switch (CurrProcess)

		{
		case IdleProcess :

			break;

		case WriteProcess:

			H_LCD_WriteProcess();
			break;

		case ClearProcess :

			H_LCD_ClearProcess();
			break;

		case MoveCursorProcess:

			H_LCD_MoveCursorProcess();
			break;

		case AdjustCursorProcess:

			H_LCD_AdjustCursorProcess();
			break;
		}
	}
	else
	{
		H_LCD_InitProcess();
	}
}


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
extern STD_ERROR H_LCD_Write (const char * String , u8 Length)
{
	STD_ERROR Local_Err = OK;
	u8 idx =0;

	if (CurrProcess == IdleProcess )
	{
		for ( idx =0;idx<Length;idx++)
		{
			UserData.str[idx] = String[idx];
		}

		UserData.Length = Length;

		CurrProcess = WriteProcess;
		Local_Err = OK;
	}
	else
	{
		Local_Err = NOT_OK;
	}
	return Local_Err;
}


/************************************************************************
 * Function name: H_LCD_Clear
 *
 * parameters:  Input:
 *                 N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function clears the LCD display
 *****************************************************************************/
extern STD_ERROR H_LCD_Clear (void)
{
	STD_ERROR Local_Err = OK;
	if (CurrProcess == IdleProcess)
	{
		CurrProcess = ClearProcess;
	}
	else
	{
		Local_Err = NOT_OK;
	}
	return Local_Err;
}


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
extern STD_ERROR H_LCD_PrintNumber(u32 Number)
{
	STD_ERROR Local_Err = OK;
	u8 TempArr [10] = {0};
	u8 Length=0;
	u8 idx=0;
	u8 j=0;
	if (CurrProcess == IdleProcess )
	{
		while(Number>=0)
		{
			TempArr[idx]=(Number%10)+48;
			Number=Number/10;
			idx++;
			Length ++;
			if(Number==0)
			{
				break;
			}

		}

		for( j=0; j<(Length); j++)
		{
			UserData.str[j] = TempArr[idx-1];
			idx --;
		}

		UserData.Length = Length;

		CurrProcess = WriteProcess;
		Local_Err = OK;
	}

	else
	{
		Local_Err = NOT_OK;
	}
	return Local_Err;

}


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
extern STD_ERROR H_LCD_GoToXYPos(u8 XPos, u8 YPos) {

	STD_ERROR Local_Err = OK;

	if (CurrProcess == IdleProcess)
	{
		if (YPos == CLCD_u8_LINE_ONE) {
			DDRamAdd = XPos;
		} else if (YPos == CLCD_u8_LINE_TWO) {
			DDRamAdd = XPos + CLCD_u8_LINE_TWO_ADD_OFFSET;
		} else {
			/* Do nothing*/
		}
		CurrProcess = MoveCursorProcess;
	}
	else
	{
		Local_Err = NOT_OK;
	}
	return Local_Err;

}

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
extern STD_ERROR H_LCD_ConfigCursor ( u8 CursorDisplay , u8 CursosBlink)
{
	STD_ERROR Local_Err = OK;

		if (CurrProcess == IdleProcess)
		{
			CursorConfig = CLCD_DISPLAY_COMMAND | CursorDisplay;
			CursorConfig |= CursosBlink;
			CurrProcess = AdjustCursorProcess;
		}
		else
		{
			Local_Err = NOT_OK;
		}
		return Local_Err;
}


/*****************************************************************************
 * Function name: H_LCD_InitProcess
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function handles the logic of LCD initialization
 *****************************************************************************/
static void H_LCD_InitProcess(void)
{
	static u8 counter=0;

	switch (InitState)
	{
	case S1:

		if ( counter ==8)
		{
			InitState =S2;
			counter =0;
		}
		counter ++;

		break;

	case S2:

		if (!Enable)
		{
			/*	Number of lines -> 2
			 Font
			 small -> 0
			 Large -> 1 */
			H_LCD_WriteCmd(0b00111000);

			H_LCD_SetEnable();
		}
		else
		{
			H_LCD_ClearEnable();
			InitState = S3;
		}
		break;

	case S3:

		if (!Enable)
		{
			/* Display ON/OFF , customizing the blink , cursor */
			H_LCD_WriteCmd(0b00001100);

			H_LCD_SetEnable();
		}
		else
		{
			H_LCD_ClearEnable();
			InitState = S4;
		}
		break;

	case S4:

		if (!Enable)
		{
			/* clearing display */
			H_LCD_WriteCmd(0b00000001);

			H_LCD_SetEnable();
		}
		else
		{
			H_LCD_ClearEnable();
			InitState = S5;
		}
		break;

	case S5 :

		if (counter ==1)
		{
			Init_complete = 1;
		}
		counter ++;
		break;

	}

}

/*****************************************************************************
 * Function name: H_LCD_WriteProcess
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function shall display data on LCD
 *****************************************************************************/
static void H_LCD_WriteProcess( void) {

	static u8 CurrChar =0;

	if (Enable)
	{
		/* Clearing the Enable pin */
		H_LCD_ClearEnable();
	}
	else
	{
		if ( CurrChar < UserData.Length)
		{
			/* Set RS = 1 */
			GPIO_WritePinVal(CLCD_u8_RS_PORT, CLCD_u8_RS_PIN, HIGH);
			/* Set RW = 0 */
			GPIO_WritePinVal(CLCD_u8_RW_PORT, CLCD_u8_RW_PIN, LOW);

			/* Set Data on Data Port */
			H_LCD_SetDataPort(UserData.str[CurrChar]);

			CurrChar ++;

			/* Raising the Enable pin */
			H_LCD_SetEnable();
		}
		else
		{
			CurrChar = 0;
			CurrProcess = IdleProcess;
			// Notify app -- yet to be implemented
		}
	}
}

/*****************************************************************************
 * Function name: H_LCD_WriteProcess
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function clears display on LCD
 *****************************************************************************/
static void H_LCD_ClearProcess (void)
{
	if (Enable)
	{
		/* Clearing the Enable pin */
		H_LCD_ClearEnable();

		CurrProcess = IdleProcess;
	}
	else
	{
		H_LCD_WriteCmd(CLCD_u8_CLR_DISP);
	}
}

/*****************************************************************************
 * Function name: H_LCD_MoveCursorProcess
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function moves the cursor on the LCD
 *****************************************************************************/
static void H_LCD_MoveCursorProcess (void)
{
	if (Enable)
	{
		/* Clearing the Enable pin */
		H_LCD_ClearEnable();

		CurrProcess = IdleProcess;
	}
	else
	{
		H_LCD_WriteCmd(DDRamAdd | CLCD_u8_SET_DDRAM_ADD_COMM);
	}
}

/*****************************************************************************
 * Function name: H_LCD_AdjustCursorProcess
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function changes the cursor characteristics in run time
 *****************************************************************************/
static void H_LCD_AdjustCursorProcess (void)
{
	if (Enable)
		{
			/* Clearing the Enable pin */
			H_LCD_ClearEnable();

			CurrProcess = IdleProcess;
		}
		else
		{
			H_LCD_WriteCmd(CursorConfig);
			CursorConfig = 0;
		}
}

/*****************************************************************************
 * Function name: H_LCD_WriteCmd
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This API shall execute command on LCD
 *****************************************************************************/
static void H_LCD_WriteCmd(u8 Copy_u8Cmd) {
	/* Set RS = 0 */
	GPIO_WritePinVal(CLCD_u8_RS_PORT, CLCD_u8_RS_PIN, 0);
	/* Set RW = 0 */
	GPIO_WritePinVal(CLCD_u8_RW_PORT, CLCD_u8_RW_PIN, 0);

	/* Set Command on Data Port */
	H_LCD_SetDataPort(Copy_u8Cmd);

	/* Raising the Enable pin */
	H_LCD_SetEnable();
}

/*****************************************************************************
 * Function name: H_LCD_MoveCursorProcess
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This API shall send Data on the 8 data pins of LCD
 *****************************************************************************/
static void H_LCD_SetDataPort(u8 Copy_u8Data)

{
	u8 Local_u8BitVal;

	Local_u8BitVal = GET_BIT(Copy_u8Data, 0);
	GPIO_WritePinVal(CLCD_u8_DATA_PORT, CLCD_u8_D0, Local_u8BitVal);

	Local_u8BitVal = GET_BIT(Copy_u8Data, 1);
	GPIO_WritePinVal(CLCD_u8_DATA_PORT, CLCD_u8_D1, Local_u8BitVal);

	Local_u8BitVal = GET_BIT(Copy_u8Data, 2);
	GPIO_WritePinVal(CLCD_u8_DATA_PORT, CLCD_u8_D2, Local_u8BitVal);

	Local_u8BitVal = GET_BIT(Copy_u8Data, 3);
	GPIO_WritePinVal(CLCD_u8_DATA_PORT, CLCD_u8_D3, Local_u8BitVal);

	Local_u8BitVal = GET_BIT(Copy_u8Data, 4);
	GPIO_WritePinVal(CLCD_u8_DATA_PORT, CLCD_u8_D4, Local_u8BitVal);

	Local_u8BitVal = GET_BIT(Copy_u8Data, 5);
	GPIO_WritePinVal(CLCD_u8_DATA_PORT, CLCD_u8_D5, Local_u8BitVal);

	Local_u8BitVal = GET_BIT(Copy_u8Data, 6);
	GPIO_WritePinVal(CLCD_u8_DATA_PORT, CLCD_u8_D6, Local_u8BitVal);

	Local_u8BitVal = GET_BIT(Copy_u8Data, 7);
	GPIO_WritePinVal(CLCD_u8_DATA_PORT, CLCD_u8_D7, Local_u8BitVal);
}

/*****************************************************************************
 * Function name: H_LCD_SetEnable
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This API activate the enable pin of the LCD
 *****************************************************************************/
static void H_LCD_SetEnable (void)
{
	GPIO_WritePinVal(CLCD_u8_E_PORT, CLCD_u8_E_PIN, HIGH);
	Enable = 1;
}

/*****************************************************************************
 * Function name: H_LCD_ClearEnables
 *
 * parameters:  Input:
 *                N/A
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This API deactivate the enable pin of the LCD
 *****************************************************************************/
static void H_LCD_ClearEnable (void)
{
	GPIO_WritePinVal(CLCD_u8_E_PORT, CLCD_u8_E_PIN, LOW);
	Enable = 0;
}



