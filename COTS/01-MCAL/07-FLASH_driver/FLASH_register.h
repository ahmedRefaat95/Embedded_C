/************************************************************************
 * File name: FLASH_register.h
 *
 * Description:	This file contains the macros and register addresses
 * 				of the Flash controller registers
 *
 * Owner: Ahmed Refaat
 * Date: 17/5/2020
 * Version 1.1
 ***********************************************************************/
#ifndef FLASH_REGISTER_H
#define FLASH_REGISTER_H

/****************************** Macros *********************************/

#define FLASH_ACR_PRFTBS	0x20
#define FLASH_ACR_PRFTBE	0x10
#define FLASH_ACR_HLFCYA	0x08
#define FLASH_ACR_LATENCY	0x07

#define FLASH_SR_EOP		0x20
#define FLASH_SR_WRPRTERR	0x10
#define FLASH_SR_PGERR		0x04
#define FLASH_SR_BSY		0x01

#define FLASH_CR_EOPIE		0x1000
#define FLASH_CR_ERRIE		0x400
#define FLASH_CR_OPTWRE		0x200
#define FLASH_CR_LOCK		0x80
#define FLASH_CR_STRT		0x40
#define FLASH_CR_OPTER		0x20
#define FLASH_CR_OPTPG		0x10
#define FLASH_CR_MER		0x4
#define FLASH_CR_PER		0x2
#define FLASH_CR_PG			0x1


#define FLASH_BASE_ADDRESS 0x40022000

#define FLASHx ((FlashRegisters_t volatile * const)FLASH_BASE_ADDRESS)

/***************************** Type definitions ***************************/

typedef struct
{
	u32	FLASH_ACR;
	u32	FLASH_KEYR;
	u32	FLASH_OPTKEYR;
	u32	FLASH_SR;
	u32	FLASH_CR;
	u32	FLASH_AR;
	u32	RESERVED;
	u32	FLASH_OBR;
	u32	FLASH_WRPR;
	
}FlashRegisters_t;

#endif
