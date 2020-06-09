/************************************************************************
 * File name: DMA_interface.h
 *
 * Description: This file contains the prototypes of the DMA driver
 * and the macros
 *
 * Owner: Ahmed Refaat
 * Date: 1/4/2020
 * Version 1.1
 ************************************************************************/
#ifndef DMA_INTERFACE_H
#define DMA_INTERFACE_H

/***************************** Macros ***********************************/

/* DMA control register bit masks */
#define MEM2MEM_ENABLE		    0x4000
#define MEM2MEM_CLR				0xBFFF
#define MEM2MEM_DISABLE		    0x0

#define CH_PRI_CLR				0xCFFF
#define CH_PRI_LOW			    0x0
#define CH_PRI_MED			    0x1000
#define CH_PRI_HIGH			    0x2000
#define CH_PRI_VERYHIGH		    0x3000

#define MEM_SIZE_CLR			0xF3FF
#define MEM_SIZE_8BITS		    0x0
#define MEM_SIZE_16BITS		    0x400
#define MEM_SIZE_32BITS		    0x800

#define PERI_SIZE_CLR			0xFCFF
#define PERI_SIZE_8BITS		    0x0
#define PERI_SIZE_16BITS	    0x100
#define PERI_SIZE_32BITS	    0x200

#define MEM_INC_CLR				0xFF7F
#define MEM_INC_ENABLED		    0x80
#define MEM_INC_DISABLED	    0x0

#define	PERI_INC_CLR			0xFFBF
#define PERI_INC_ENABLED	    0x40
#define PERI_INC_DISABLED 	    0x0

#define CIRC_MODE_CLR			0xFFDF
#define CIRC_MODE_ENABLED	    0x20
#define CIRC_MODE_DISABLED	    0x0

#define	TRANS_DIR_CLR			0xFFEF
#define DIR_READ_FROM_PERI	    0x0
#define DIR_READ_FROM_MEM	    0x10

#define TRANS_ERR_CLR			0xFFF7
#define TRANS_ERR_ENABLE	    0x8
#define TRANS_ERR_DISABLE	    0x0

#define	HALF_TRANS_INT_CLR		0xFFFB
#define HALF_TRANS_INT_ENABLE	0x4
#define HALF_TRANS_INT_DISABLE	0x0

#define TRANS_COMP_INT_CLR		0xFFFD
#define TRANS_COMP_INT_ENABLE	0x2
#define TRANS_COMP_INT_DISABLE	0x0

#define DMA_ENABLE				0x1

/* DMA interrupt flags */
 #define TRANS_ERR_FLAG			1
 #define HALF_TRANS_FLAG		2
 #define TRANS_COMP_FLAG		3
 #define GLOBAL_INT_FLAG		4


/* DMA channels */
#define DMA_CH_1				1
#define DMA_CH_2				2
#define DMA_CH_3				3
#define DMA_CH_4				4
#define DMA_CH_5				5
#define DMA_CH_6				6
#define DMA_CH_7				7

/* DMA channels peripherals requests  */
#define USART1_DR ((u32*)0x40013804)
#define USART2_DR ((u32*)0x40004404)
#define USART3_DR ((u32*)0x40004804)

/***************************** Type definitions ***************************/

typedef void (*DMA_Cbf_t) (void);


typedef struct
{
	u16 MEM2MEM;
	u16 ChannelPriority;
	u16 MemorySize;
	u16 PeripheralSize;
	u16 MemoryIncMode;
	u16 PeripheralIncMode;
	u16 CircularMode;
	u16 DataTransferDirection;
	u16 TransferErrIntEn;
	u16 HalfTransferIntEn;
	u16 TransferCompleteIntEn;

}DMA_config;

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
void DMA_ConfigChannel (u8 ChannelNumber , DMA_config * DMA_ConfigStruct);

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
void DMA_Start (u8 ChannelNumber , u32 MemoryAddress,u32 PeripheralAddress,u16 BlockLength );

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
void DMA_Stop (u8 ChannelNumber );

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
void DMA_ClearIntFlag (u8 ChannelNumber , u32 Flag);

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
void DMA_SetTransCompCbf (u8 ChannelNumber, DMA_Cbf_t DMA_Cbf );
#endif
