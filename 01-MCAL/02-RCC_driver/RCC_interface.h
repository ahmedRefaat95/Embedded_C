/************************************************************************
 * File name: RCC_interface.h
 *
 *
 * Description: This file contains the prototypes of the RCC driver
 * and the macros used by the user
 *
 * Owner: Ahmed Refaat
 * Date: 6/3/2020
 * Version 1.1
 ************************************************************************/

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H


/***************************** Macros ***********************************/
#define RCC_BASE_ADDRESS  0x40021000

/* Status */
#define ON	1
#define OFF 0

/* Clock speeds */
#define HSI_SPEED	8
#define HSE_SPEED	8
#define HSE_SPEED_div2	4

/* Masks for clock sources */
#define HSI_CLK		0x01
#define HSE_CLK		0x10000
#define PLL_CLK		0x1000000

#define CHECK_CLOCK_SOURCES(Clock)	( (Clock == HSI_CLK) || (Clock == HSE_CLK) || (Clock == PLL_CLK) )
/* Clock status */
#define HSI_RDY		0x02
#define HSE_RDY		0x20000
#define PLL_RDY		0x20000000
/* System clock sources */
#define SYSTEM_HSI		0x00
#define SYSTEM_HSE		0x01
#define SYSTEM_PLL		0x02
#define SYSTEM_CLEAR	0xfffffffC

#define CHECK_SYSTEM_CLOCK(System)	( (System == SYSTEM_HSI) || (System == SYSTEM_HSE) || (System == SYSTEM_PLL) )
/* current clock source selected */
#define SWS_BITS	0xC
#define SWS_HSI		0x0
#define SWS_HSE		0x4
#define	SWS_PLL		0x8

/* HPRE bits */
#define HPRE_BITS	0xF0
#define HPRE_x2		0x80
#define HPRE_x4		0x90
#define HPRE_x8		0xA0
#define HPRE_x16	0xB0
#define HPRE_x64	0xC0
#define HPRE_x128	0xD0
#define HPRE_x256	0xE0
#define HPRE_x512	0xF0

/* PPRE2 bits */
#define PPRE2_BITS	0x3800
#define PPRE2_x2	0x2000
#define PPRE2_x4	0x2800
#define PPRE2_x8	0x3000
#define PPRE2_x16	0x3800

/* PPRE1 bits */
#define PPRE1_BITS	0x700
#define PPRE1_x2	0x400
#define PPRE1_x4	0x500
#define PPRE1_x8	0x600
#define PPRE1_x16	0x700

/* MCO configuration bits */
#define MCO_BITS	0xf8ffffff
#define MCO_SYS		0x04000000
#define MCO_HSI		0x05000000
#define MCO_HSE		0x06000000
#define	MCO_PLL		0x07000000

#define CHECK_MCO_SOURCE(MCO)	( (MCO == MCO_SYS) || (MCO == MCO_HSI) || (MCO == MCO_HSE) || (MCO == MCO_PLL)  )

#define PLL_SRC		0x10000
/* PLL multiplier masks */
#define CLR_MUL_BITS	0xffC3ffff
#define PLL_MUL_BITS	0x3C0000

#define PLLXPTRE		0x20000
#define PLL_x2		0x0
#define PLL_x3		0x40000
#define PLL_x4		0x80000
#define PLL_x5		0xC0000
#define PLL_x6		0x100000
#define PLL_x7		0x140000
#define PLL_x8		0x180000
#define PLL_x9		0x1C0000
#define PLL_x10		0x200000
#define PLL_x11		0x240000
#define PLL_x12		0x280000
#define PLL_x13		0x2C0000
#define PLL_x14		0x300000
#define PLL_x15		0x340000
#define PLL_x16		0x380000

#define CHECK_PLL_MULT(Mult) ((Mult == PLL_x2) || (Mult == PLL_x3)  || (Mult == PLL_x4) || (Mult == PLL_x5) ||    	\
							 (Mult == PLL_x6)  || (Mult == PLL_x7)  || (Mult == PLL_x8) || (Mult == PLL_x9) || 	\
							 (Mult == PLL_x10) || (Mult == PLL_x11) ||	(Mult == PLL_x12) || (Mult == PLL_x13) ||   \
							 (Mult == PLL_x14)  || (Mult == PLL_x15)  || (Mult == PLL_x16))


/* Peripherals connected to AHB bus */
#define AHB_DMA1	0x01
#define AHB_DMA2	0x02
#define AHB_SRAM	0x03
#define AHB_FLITF	0x10
#define AHB_CRC		0x40
#define AHB_FSMC	0x100
#define AHB_SDIO	0x400

#define CHECK_AHB(AHBx) 		((AHBx == AHB_DMA1) || (AHBx == AHB_DMA2)  || (AHBx == AHB_SRAM) || \
								(AHBx == AHB_FLITF) || (AHBx == AHB_CRC)  || (AHBx == AHB_FSMC)  || \
								(AHBx == AHB_SDIO) )

/* Peripherals connected to APB2 bus */
#define	APB2_AFIO 		0x01
#define	APB2_IOPA 		0x04
#define	APB2_IOPB 		0x08
#define	APB2_IOPC 		0x10
#define	APB2_ADC1 		0x200
#define	APB2_ADC2 		0x400
#define	APB2_TIM1 		0x800
#define	APB2_SPI1 		0x1000
#define	APB2_TIM8 		0x2000
#define	APB2_USART1 	0x4000
#define	APB2_ADC3 		0x8000
#define	APB2_TIM9 		0x80000
#define	APB2_TIM10 		0x100000
#define	APB2_TIM11 		0x200000

#define CHECK_APB2(APB2x) 		((APB2x == APB2_AFIO)  || (APB2x == APB2_IOPA)  || (APB2x == APB2_IOPB)  || \
								(APB2x == APB2_IOPC)   || (APB2x == APB2_ADC1)  || (APB2x == APB2_ADC2)  || \
								(APB2x == APB2_TIM1)   || (APB2x == APB2_SPI1)  || (APB2x == APB2_TIM8)  || \
								(APB2x == APB2_USART1) || (APB2x == APB2_ADC3)  || (APB2x == APB2_TIM9)  || \
								(APB2x == APB2_TIM10)  || (APB2x == APB2_TIM11) )

/* Peripherals connected to APB1 bus */
#define	APB1_TIM2 		0x01
#define	APB1_TIM3 		0x02
#define	APB1_TIM4 		0x04
#define	APB1_TIM5 		0x08
#define	APB1_TIM6 		0x10
#define	APB1_TIM7 		0x20
#define	APB1_TIM12 		0x40
#define	APB1_TIM13 		0x80
#define	APB1_TIM14 		0x100
#define	APB1_WWDG 		0x800
#define	APB1_SPI2 		0x4000
#define	APB1_SPI3 		0x8000
#define	APB1_USART2		0x20000
#define	APB1_USART3		0x40000
#define	APB1_USART4		0x80000
#define	APB1_USART5 	0x100000
#define	APB1_I2C1 		0x200000
#define	APB1_I2C2 		0x400000
#define	APB1_USB 		0x800000
#define	APB1_CAN 		0x2000000
#define	APB1_BKP 		0x8000000
#define	APB1_PWR 		0x10000000
#define	APB1_DAC 		0x20000000

#define CHECK_APB1(APB1x) 		((APB1x == APB1_TIM2)  || (APB1x == APB1_TIM3)   || (APB1x == APB1_TIM4)   || \
								(APB1x == APB1_TIM5)   || (APB1x == APB1_TIM6)   || (APB1x == APB1_TIM7)   || \
								(APB1x == APB1_TIM12)  || (APB1x == APB1_TIM13)  || (APB1x == APB1_TIM14)  || \
								(APB1x == APB1_WWDG)   || (APB1x == APB1_SPI2)   || (APB1x == APB1_SPI3)   || \
								(APB1x == APB1_USART2) || (APB1x == APB1_USART3) || (APB1x == APB1_USART4) || \
								(APB1x == APB1_USART5) || (APB1x == APB1_I2C1)   || (APB1x == APB1_I2C2)   || \
								(APB1x == APB1_USB)    || (APB1x == APB1_CAN)    || (APB1x == APB1_BKP))   || \
								(APB1x == APB1_PWR)    || (APB1x == APB1_DAC))

#define AHB		1
#define APB1	2
#define APB2	3

#define CHECK_BUS(Bus) 		((Bus == AHB)  || (Bus == APB1)   || (Bus == APB2))


#define PLL_HSI		1
#define PLL_HSE		2
#define PLL_HSE_2	3

#define CHECK_PLL_SRC(PLL_src) ((PLL_src == PLL_HSI)  || (PLL_src == PLL_HSE)   || (PLL_src == PLL_HSE_2))

/***************************** Type definitions ***************************/

/* Creating a new type of structure for the RCC registers */
typedef struct
{
	u32 CR      ;
	u32 CFGR    ;
	u32 CIR     ;
	u32 APB2STR ;
	u32 APB1STR ;
	u32 AHBENR  ;
	u32 APB2ENR ;
	u32 APB1ENR ;
	u32 BDCR    ;
	u32 CSR     ;
}RCC_Registers;


/************************************************************************
 * Function name: RCC_STD_ERROR_ControlClock
 *
 * parameters:  Input:
 *                 Copy_32ClockType
 *                     type: u32
                        Description: Clock sources (HSI_CLK,HSE_CLK,PLL_CLK)
 *                 Copy_u8Status
 *                     type: u8
 *                     Description: control the clock source (ON,OFF)
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function enables or disables the clock sources (HSI-HSE-PLL) of the system
 *****************************************************************************/
STD_ERROR RCC_STD_ERROR_ControlClock (u32 Copy_32ClockType , u8 Copy_u8Status);

/************************************************************************
 * Function name: RCC_STD_ERROR_SelectSysClock
 *
 * parameters:  Input:
 *                 Copy_u32SysClock
 *                     type: u32
                        Description: system clock (SYSTEM_HSI,SYSTEM_HSE,SYSTEM_PLL)
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function selects one of the clock sources(HSI-HSE-PLL) as the system clock
 *****************************************************************************/
STD_ERROR RCC_STD_ERROR_SelectSysClock (u32 Copy_u32SysClock);

/************************************************************************
 * Function name: RCC_PLL_CLockSource
 *
 * parameters:  Input:
 *                 PLL_Source
 *                     type: u8
 *                     Description: PLL clock source (PLL_HSI,PLL_HSE,PLL_HSE_2)
 *                 Copy_u32PllMult
 *                     type: u32
 *                     Description: PLL multiplier value(PLL_x2,PLL_x3...PLL_x16)
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function selects PLL clock source (HSI - HSE - HSE/2)
 *****************************************************************************/
STD_ERROR RCC_PLL_CLockSource (u8 PLL_Source,u32 Copy_u32PllMult);

/************************************************************************
 * Function name: RCC_MCO_Config
 *
 * parameters:  Input:
 *                 Copy_u32MCO_Source
 *                     type: u32
 *                     Description: MCO clock source (PLL_HSI,PLL_HSE,PLL_HSE_2)
 *
 * return: STD_ERROR (OK, NOT_OK)
 * Description: This function selects MCO source (MCO_SYS - MCO_HSI - MCO_HSE - MCO_PLL)
 *****************************************************************************/
STD_ERROR RCC_MCO_Config (u32 Copy_u32MCO_Source);

/************************************************************************
 * Function name: RCC_ControlPeripheralClock
 *
 * parameters:  Input:
 *                 Bus
 *                     type: u8
 *                     Description: BUS type (PLL_HSI,PLL_HSE,PLL_HSE_2)
 *                 Copy_u32Peripheral
 *                     type: u32
 *                     Description: Desired peripheral to be enabled/disabled (AHB_x,APB1_x,APB2_x)
 *                 Copy_u8Status
 *                     type: u8
 *                     Description: Status of the desired peripheral (ON,OFF)
 *
 * Description: This function enables or disables the desired peripheral on its corresponding Bus
 *****************************************************************************/
STD_ERROR RCC_ControlPeripheralClock(u8 Bus , u32 Copy_u32Peripheral, u8 Copy_u8Status);

/************************************************************************
 * Function name: RCC_getClockSpeed
 *
 * parameters:  Input:
 *                 Bus
 *                     type: pointer to u32
 *                     Description: container to save the system clock speed
 *
 * Description: This function gets the clock speed of the system in MHz
 *****************************************************************************/
void RCC_GetSysClock ( u32 * ClockSpeed ) ;

/************************************************************************
 * Function name: RCC_GetAHBClock
 *
 * parameters:  Input:
 *                 AHB_Speed
 *                     type: pointer to f32
 *                     Description: container to save the AHB bus clock speed
 *
 * Description: This function gets the clock speed of the AHB bus in MHz
 *****************************************************************************/
void RCC_GetAHBClock (f32 * AHB_Speed);

/************************************************************************
 * Function name: RCC_GetAPB2Clock
 *
 * parameters:  Input:
 *                 APB2_Speed
 *                     type: pointer to f32
 *                     Description: container to save the APB2 bus clock speed
 *
 * Description: This function gets the clock speed of the APB2 bus in MHz
 *****************************************************************************/
void RCC_GetAPB2Clock (u32 * APB2_Speed);

/************************************************************************
 * Function name: RCC_GetAPB1Clock
 *
 * parameters:  Input:
 *                 APB1_Speed
 *                     type: pointer to f32
 *                     Description: container to save the APB1 bus clock speed
 *
 * Description: This function gets the clock speed of the APB1 bus in MHz
 *****************************************************************************/
void RCC_GetAPB1Clock (u32 * APB1_Speed);

#endif
