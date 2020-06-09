/************************************************************************
 * File name: DMA_program.c
 *
 * Description: This file contains the implementation of the DMA driver
 * functions
 *
 * Owner: Ahmed Refaat
 * Date: 1/4/2020
 * Version 1.1
 ************************************************************************/

/***************************** Includes *********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "DMA_interface.h"
#include "DMA_register.h"
#include "DMA_private.h"


/* Array of DMA call back functions */
static DMA_Cbf_t DMA_Cbf_arr[7];

/* Array of DMA channel 1 interrupt numbers */
static u8 DMA1_IntNumbers[7] = { DMA1_CHANNEL1,DMA1_CHANNEL2,DMA1_CHANNEL3,DMA1_CHANNEL4,DMA1_CHANNEL5,DMA1_CHANNEL6,DMA1_CHANNEL7};


/***************************************************************************
 * Function name: DMA_ConfigChannel
 *
 * Parameters:  Input:
 *                 ChannelNumber
 *                 	type: u8
 *                  	Description: Channel number of DMA peripheral
 *
 *                 DMA_ConfigStruct
 *                 	type: pointer to structure
 *                  	Description:	Structure holding the configuration
 *                  					parameters of the DMA channel
 *
 * Description:	This function shall configure the parameters of the desired
 * 				DMA channel
 ***************************************************************************/
void DMA_ConfigChannel (u8 ChannelNumber , DMA_config * DMA_ConfigStruct)
{

	/* Clearing the CCR register */
	DMA_Registers -> Channel[ChannelNumber -1].CCR = 0;

	DMA_Registers -> Channel[ChannelNumber -1].CCR |= DMA_ConfigStruct -> MEM2MEM;
	DMA_Registers -> Channel[ChannelNumber -1].CCR |= DMA_ConfigStruct -> ChannelPriority;
	DMA_Registers -> Channel[ChannelNumber -1].CCR |= DMA_ConfigStruct -> MemorySize;
	DMA_Registers -> Channel[ChannelNumber -1].CCR |= DMA_ConfigStruct -> PeripheralSize;
	DMA_Registers -> Channel[ChannelNumber -1].CCR |= DMA_ConfigStruct -> MemoryIncMode;
	DMA_Registers -> Channel[ChannelNumber -1].CCR |= DMA_ConfigStruct -> PeripheralIncMode;
	DMA_Registers -> Channel[ChannelNumber -1].CCR |= DMA_ConfigStruct -> CircularMode;
	DMA_Registers -> Channel[ChannelNumber -1].CCR |= DMA_ConfigStruct -> DataTransferDirection;

	if ( (DMA_ConfigStruct ->TransferErrIntEn) | (DMA_ConfigStruct ->HalfTransferIntEn) | (DMA_ConfigStruct ->TransferCompleteIntEn) )
	{
		NVIC_SetEnable(DMA1_IntNumbers[ChannelNumber -1]);
	}

	DMA_Registers -> Channel[ChannelNumber -1].CCR |= DMA_ConfigStruct ->TransferErrIntEn;
	DMA_Registers -> Channel[ChannelNumber -1].CCR |= DMA_ConfigStruct ->HalfTransferIntEn;
	DMA_Registers -> Channel[ChannelNumber -1].CCR |= DMA_ConfigStruct ->TransferCompleteIntEn;

}

/***************************************************************************
 * Function name: DMA_Start
 *
 * Parameters:  Input:
 *                 ChannelNumber
 *                 	type: u8
 *                  	Description: Channel number of DMA peripheral
 *
 *                 	MemoryAddress
 *                 	type: u32
 *                  	Description:	memory address of the DMA channel
 *                  					to move to/from
 *					PeripheralAddress
 *                 	type: u32
 *                  	Description:	peripheral address of the DMA channel
 *                  					to move to/from
 *
 *					BlockLength
 *                 	type: u16
 *                  	Description:	length of the one DMA transfer block
 *
 * Description:	This function shall start the DMA channel transfer from memory
 * 				to peripheral or vice versa
 ***************************************************************************/
void DMA_Start (u8 ChannelNumber , u32 MemoryAddress,u32 PeripheralAddress,u16 BlockLength )
{

	DMA_Registers -> Channel[ChannelNumber-1].CPAR	= PeripheralAddress;
	DMA_Registers -> Channel[ChannelNumber-1].CMAR	= MemoryAddress;


	DMA_Registers -> Channel[ChannelNumber-1].CNDTR	= BlockLength;

	/*DMA channel enable */
	DMA_Registers -> Channel[ChannelNumber-1].CCR |= DMA_ENABLE;
}

/***************************************************************************
 * Function name: DMA_Stop
 *
 * Parameters:  Input:
 *                 ChannelNumber
 *                 	type: u8
 *                  	Description: Channel number of DMA peripheral
 *
 *
 * Description:	This function shall stop the DMA transfer of the desired
 * 				DMA channel
 ***************************************************************************/
void DMA_Stop (u8 ChannelNumber )
{
	/*DMA channel disable */
	DMA_Registers -> Channel[ChannelNumber-1].CCR &= ~DMA_ENABLE;

}

/***************************************************************************
 * Function name: DMA_ClearIntFlag
 *
 * Parameters:  Input:
 *                 ChannelNumber
 *                 	type: u8
 *                  	Description: Channel number of DMA peripheral
 *
 *                 Flag
 *                 	type: u32
 *                  	Description: macro for the desired DMA interrupt
 *                  				 flag to be cleared
 *
 *
 * Description:	This function shall clear the desired DMA channel interrupt
 * 				flag
 ***************************************************************************/
void DMA_ClearIntFlag (u8 ChannelNumber , u32 Flag)
{
	switch (Flag)
	{
	case TRANS_ERR_FLAG:
		TEIF_CLEAR(ChannelNumber);
		break;

	case HALF_TRANS_FLAG:
		HTIF_CLEAR(ChannelNumber);
		break;

	case TRANS_COMP_FLAG:
		TCIF_CLEAR(ChannelNumber);
		break;

	case GLOBAL_INT_FLAG:
		GIF_CLEAR(ChannelNumber);
		break;
	}
}

/***************************************************************************
 * Function name: DMA_SetTransCompCbf
 *
 * Parameters:  Input:
 *                 ChannelNumber
 *                 	type: u8
 *                  	Description: Channel number of DMA peripheral
 *
 *                 DMA_Cbf
 *                 	type: pointer to function
 *                  	Description: pointer to the call back function
 *                  				 of the DMA channel interrupt
 *
 *
 * Description:	This function shall set the call back function of the desired
 * 				DMA channel
 ***************************************************************************/
void DMA_SetTransCompCbf (u8 ChannelNumber, DMA_Cbf_t DMA_Cbf )
{
	if (DMA_Cbf)
	{
		DMA_Cbf_arr[ChannelNumber -1] = DMA_Cbf;
	}

}


/*********************** DMA 1 interrupt handlers *************************/
void DMA1_Channel1_IRQHandler (void)
{

	DMA_ClearIntFlag(DMA_CH_1,TRANS_COMP_FLAG);
	DMA_Stop(DMA_CH_1);

	if  ( DMA_Cbf_arr[0] )
	{
		DMA_Cbf_arr[0]();
	}
}

void DMA1_Channel2_IRQHandler (void)
{
	DMA_ClearIntFlag(DMA_CH_2,TRANS_COMP_FLAG);
	DMA_Stop(DMA_CH_2);

	if  ( DMA_Cbf_arr[1] )
	{
		DMA_Cbf_arr[1]();
	}
}

void DMA1_Channel3_IRQHandler (void)
{
	DMA_ClearIntFlag(DMA_CH_3,TRANS_COMP_FLAG);
	DMA_Stop(DMA_CH_3);

	if  ( DMA_Cbf_arr[2] )
	{
		DMA_Cbf_arr[2]();
	}
}

void DMA1_Channel4_IRQHandler (void)
{
	DMA_ClearIntFlag(DMA_CH_4,TRANS_COMP_FLAG);
	DMA_Stop(DMA_CH_4);

	if  ( DMA_Cbf_arr[3] )
	{
		DMA_Cbf_arr[3]();
	}
}

void DMA1_Channel5_IRQHandler (void)
{
	DMA_ClearIntFlag(DMA_CH_5,TRANS_COMP_FLAG);
	DMA_Stop(DMA_CH_5);

	if  ( DMA_Cbf_arr[4] )
	{
		DMA_Cbf_arr[4]();
	}
}

void DMA1_Channel6_IRQHandler (void)
{
	DMA_ClearIntFlag(DMA_CH_6,TRANS_COMP_FLAG);
	DMA_Stop(DMA_CH_6);

	if  ( DMA_Cbf_arr[5] )
	{
		DMA_Cbf_arr[5]();
	}
}

void DMA1_Channel7_IRQHandler (void)
{
	DMA_ClearIntFlag(DMA_CH_7,TRANS_COMP_FLAG);
	DMA_Stop(DMA_CH_7);

	if  ( DMA_Cbf_arr[6] )
	{
		DMA_Cbf_arr[6]();
	}
}
