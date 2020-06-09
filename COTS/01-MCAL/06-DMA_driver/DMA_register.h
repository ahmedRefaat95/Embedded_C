/************************************************************************
 * File name: FLASH_register.h
 *
 * Description:	This file contains the macros and register addresses
 * 				of the Flash controller registers
 *
 * Owner: Ahmed Refaat
 * Date: 1/4/2020
 * Version 1.1
 ***********************************************************************/

#ifndef DMA_REGISTER_H
#define DMA_REGISTER_H

/***************************** Type definitions ***************************/
typedef struct 
{
	u32 CCR;
	u32 CNDTR;
	u32 CPAR;
	u32 CMAR;
	u32 Reserved;
}DMA_Channel;

typedef struct 
{
	u32			ISR;
	u32			IFCR;
	DMA_Channel	Channel[7];
}DMA_Type;

/****************************** Macros *********************************/
#define DMA_Registers		((volatile DMA_Type*)0x40020000)

#define TEIF_Bits(BitNumber)		( 3+(4* (BitNumber-1)) )
#define HTIF_Bits(BitNumber)		( 2+(4* (BitNumber-1)) )
#define TCIF_Bits(BitNumber)		( 1+(4* (BitNumber-1)) )
#define GIF_Bits(BitNumber)			( 4* (BitNumber-1)	   )

#define TEIF_GET(ChannelNumber) 	( DMA_Registers -> ISR & 1<< TEIF_Bits[ChannelNumber]  )
#define HTIF_GET(ChannelNumber) 	( DMA_Registers -> ISR & 1<< HTIF_Bits[ChannelNumber]  )
#define TCIF_GET(ChannelNumber) 	( DMA_Registers -> ISR & 1<< TCIF_Bits[ChannelNumber]  )
#define GIF_GET(ChannelNumber) 		( DMA_Registers -> ISR & 1<< GIF_Bits[ChannelNumber]   )

#define TEIF_CLEAR(ChannelNumber) 	( DMA_Registers -> IFCR |= 1<< TEIF_Bits(ChannelNumber)  )
#define HTIF_CLEAR(ChannelNumber) 	( DMA_Registers -> IFCR |= 1<< HTIF_Bits(ChannelNumber)  )
#define TCIF_CLEAR(ChannelNumber) 	( DMA_Registers -> IFCR |= 1<< TCIF_Bits(ChannelNumber)  )
#define GIF_CLEAR(ChannelNumber) 	( DMA_Registers -> IFCR |= 1<< GIF_Bits(ChannelNumber)   )


#endif
