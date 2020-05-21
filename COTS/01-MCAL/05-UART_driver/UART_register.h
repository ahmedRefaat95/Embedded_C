/************************************************************************
 * File name: STK_register.h
 *
 * Description: This file contains the Macros of the STK registers
 *
 * Owner: Ahmed Refaat
 * Date: 29/3/2020
 * Version 1.1
 ************************************************************************/

#ifndef UART_REGISTER_H
#define UART_REGISTER_H

/* Base addresses of the UART registers of each channel */
#define USART1_R ((UART_Register_t*)0x40013800)
#define USART2_R ((UART_Register_t*)0x40004400)
#define USART3_R ((UART_Register_t*)0x40004800)

#define	UE		0x2000
#define	M		0x1000
#define WAKE	0x800
#define PCE		0x400
#define PS		0x200
#define PEIE	0x100
#define	TXEIE	0x80
#define TCIE	0x40
#define RXNEIE	0x20
#define IDLEIE	0x10
#define TE		0x8
#define RE		0x4
#define RWU		0x2
#define SBK		0x1

#define LINEN				0x4000
#define STOP_BITS			0x3000

#define CLKEN				0x800
#define CPOL				0x400
#define CPHA				0x200
#define LBCL				0x100
#define LBDIE				0x40
#define LBDL				0x20
#define ADD					0xF

#define CTSIE				0x400
#define CTSE				0x200
#define RTSE				0x100
#define DMAT				0x80
#define DMAR				0x40
#define SCEN				0x20
#define NACK				0x10
#define HDSEL				0x8
#define IRLP				0x4
#define IREN				0x2
#define EIE					0x1

/***************************** Type definitions ***************************/

typedef struct 
{
	u32 USART_SR;
	u32 USART_DR;
	u32 USART_BRR;
	u32 USART_CR1;
	u32 USART_CR2;
	u32 USART_CR3;
	u32 USART_GTPR;
}UART_Register_t;

#endif
