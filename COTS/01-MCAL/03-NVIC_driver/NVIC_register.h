/************************************************************************
 * File name: NVIC_register.h
 *
 * Description: This file contains the addresses of the NVIC registers
 * 				and the needed macros
 *
 * Owner	: Ahmed Refaat
 * Date		: 17/2/2020
 * Version	: 1.0
 ************************************************************************/
#ifndef NVIC_REGISTER_H
#define NVIC_REGISTER_H

/***************************** Macros ***********************************/

#define NVIC_BASE_ADDRESS		((volatile NVIC_registers *)0xE000E100)
#define SCB_BASE_ADDRESS		((volatile NVIC_registers *)0xE000ED00)

#define NVIC_STIR		*((volatile u32 *)(NVIC_BASE_ADDRESS+0xE00))

#define SCB_AIRCR		*((volatile u32 *)(0xE000ED0C))

#define	VECTKEY		0x05FA0000



/***************************** Type definitions ***************************/
typedef struct
{
	u32 NVIC_ISER[8];
	u32 RESERVED1[24];
	u32 NVIC_ICER[8];
	u32 RESERVED2[24];
	u32 NVIC_ISPR[8];
	u32 RESERVED3[24];
	u32 NVIC_ICPR[8];
	u32 RESERVED4[24];
	u32 NVIC_IABR[8];
	u32 RESERVED5[61];
	u8 NVIC_IPR[21];
}NVIC_registers;

#endif
