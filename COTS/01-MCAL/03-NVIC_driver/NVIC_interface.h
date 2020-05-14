/************************************************************************
 * File name: NVIC_interface.h
 *
 * Description: This file contains the prototypes of the NVIC driver functions
 * 				and the needed macros
 *
 * Owner	: Ahmed Refaat
 * Date		: 17/2/2020
 * Version	: 1.0
 ***************************************************************************/
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H


/***************************** Macros ***********************************/
#define ALL_PREEMPTION_BITS				0x05FA0300
#define ALL_SUBGROUP_BITS				0x05FA0700
#define THREE_GROUP_ONE_SUBGROUP		0x05FA0400
#define TWO_GROUP_TWO_SUBGROUP			0x05FA0500
#define ONE_GROUP_THREE_SUBGROUP		0x05FA0600
/*
 * Defines of the STM32 interrupts
 */
#define WWDG				0
#define PVD					1
#define TAMPER				2
#define RTC					3
#define FLASH				4
#define RCCINT				5
#define EXTI0				6
#define EXTI1				7
#define EXTI2				8
#define EXTI3				9
#define EXTI4				10
#define DMA1_CHANNEL1		11
#define DMA1_CHANNEL2		12
#define DMA1_CHANNEL3		13
#define DMA1_CHANNEL4		14
#define DMA1_CHANNEL5		15
#define DMA1_CHANNEL6		16
#define DMA1_CHANNEL7		17
#define ADC1_2				18
#define USB_HP_CAN_TX		19
#define USB_LP_CAN_RX0		20
#define CAN_RX1				21
#define CAN_SCE				22
#define EXTI9_5				23
#define TIM1_BRK			24
#define TIM1_UP				25
#define TIM1_TRG_COM		26
#define TIM1_CC				27
#define TIM2				28
#define TIM3				29
#define TIM4				30
#define I2C1_EV				31
#define I2C1_ER				32
#define I2C2_EV				33
#define I2C2_ER				34
#define SPI1				35
#define SPI2				36
#define USART1				37
#define USART2				38
#define USART3				39
#define EXTI15_10			40
#define RTCALARM			41
#define USBWAKEUP			42
#define TIM8_BRK			43
#define TIM8_UP				44
#define TIM8_TRG_COM		45
#define TIM8_CC				46
#define ADC3				47
#define FSMC				48
#define SDIO				49
#define TIM5				50
#define SPI3				51
#define UART4				52
#define UART5				53
#define TIM6				54
#define TIM7				55
#define DMA2_CHANNEL1		56
#define DMA2_CHANNEL2		57
#define DMA2_CHANNEL3		58
#define DMA2_CHANNEL4_5		59

/**************************** Prototypes *********************************/

/************************************************************************
 * Function name: NVIC_SetIntPriorityGrouping
 *
 * parameters:  Input:
 *                 PriorityGrouping
 *                     type: u32
 *                       Description:	configuration for number of preemption
 *                       				bits and subgroup bits
 *
 * Description: a function to configure number of preemption bits and
 * 				subgroup bits*
 ***************************************************************************/
void NVIC_SetIntPriorityGrouping ( u32 PriorityGrouping);

/************************************************************************
 * Function name: NVIC_SetEnable
 *
 * parameters:  Input:
 *                 InterruptNumber
 *                     type: u8
 *                       Description: number of the interrupt to be enabled
 *
 * Description: a function to enable the desired interrupt *
 ***************************************************************************/
void NVIC_SetEnable(u8 InterruptNumber);

/************************************************************************
 * Function name: NVIC_ClearEnable
 *
 * parameters:  Input:
 *                 InterruptNumber
 *                     type: u8
 *                       Description: number of the interrupt to be disabled
 *
 * Description: a function to disable the desired interrupt *
 ***************************************************************************/
void NVIC_ClearEnable (u8 InterruptNumber);

/************************************************************************
 * Function name: NVIC_SetPending
 *
 * parameters:  Input:
 *                 InterruptNumber
 *                     type: u8
 *                       Description: number of the interrupt to be disabled
 *
 * Description: a function to set the pending bit of the desired interrupt *
 ***************************************************************************/
void NVIC_SetPending (u8 InterruptNumber);

/************************************************************************
 * Function name: NVIC_ClearPending
 *
 * parameters:  Input:
 *                 InterruptNumber
 *                     type: u8
 *                       Description: number of the interrupt to be disabled
 *
 * Description: a function to clear the pending bit of the desired interrupt *
 ***************************************************************************/
void NVIC_ClearPending (u8 InterruptNumber);
/************************************************************************
 * Function name: NVIC_GetActive
 *
 * parameters:  Input:
 *                 InterruptNumber
 *                 		type: u8
 *                      Description: number of the interrupt to be disabled
 *              In/out:
 *              		type: pointer to u8
 *						Description: container for the active interrupts
 *
 * Description: a function to get the active bits of the interrupts *
 ***************************************************************************/
void NVIC_GetActive (u8 InterruptNumber , u8* ActiveInterrupt);

/************************************************************************
 * Function name: NVIC_SetPriority
 *
 * parameters:  Input:
 *					InterruptNumber
 *                 		type: u8
 *                      Description: number of the interrupt to be configured
 *					Priority
 *						type: u8
 *						Description: priority of the passed interrupt number
 *
 * Description: a function to set the priority of the desired interrupt number *
 ******************************************************************************/
void NVIC_SetPriority ( u8 InterruptNumber, u8 Priority);

/************************************************************************
 * Function name: NVIC_TriggerSoftwareInterrupt
 *
 * parameters:  Input:
 *                 InterruptNumber
 *                     type: u32
 *                       Description: number of the interrupt to be triggered
 *
 * Description: a function to trigger a software interrupt of the desired interrupt *
 ***************************************************************************/
void NVIC_TriggerSoftwareInterrupt (u32 InterruptNumber);

/************************************************************************
 * Function name: NVIC_SetPRIMASK
 *
 * Description: a function to set the Pri mask  *
 ******************************************************************************/
void NVIC_SetPRIMASK (void);

/************************************************************************
 * Function name: NVIC_SetPRIMASK
 *
 * Description: a function to clear the Pri mask  *
 ******************************************************************************/
void NVIC_ClearPRIMASK (void);

/************************************************************************
 * Function name: NVIC_SetPRIMASK
 *
 * Description: a function to set the Fault mask  *
 ******************************************************************************/
void NVIC_SetFAULTMASK (void);

/************************************************************************
 * Function name: NVIC_SetPRIMASK
 *
 * Description: a function to set the Pri mask  *
 ******************************************************************************/
void NVIC_ClearFAULTMASK (void);

/************************************************************************
 * Function name: NVIC_SetPRIMASK
 *
 * Description: a function to disable the Pri mask  *
 ******************************************************************************/
void NVIC_DisableBASEPRI (void);

/************************************************************************
 * Function name: NVIC_SetPRIMASK
 *
 * Description: a function to set the BasePri with the desired priority *
 ******************************************************************************/
void NVIC_WriteBASEPRI (u32 priority);

#endif
