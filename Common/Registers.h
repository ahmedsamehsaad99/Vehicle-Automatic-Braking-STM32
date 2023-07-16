/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Registers.h
 *  DESCRIPTION:	Header file for the registers for STM32F103
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef REGISTERS_H_
#define REGISTERS_H_

#include "Std_Types.h"

#define REG(BASE, OFFSET)				*((volatile uint32*)(BASE+OFFSET))


/* CORTEX M3 RELATED REGISTERS */
/* NVIC */
#define ISER0		(0xE000E100)
#define ISER1		(0xE000E104)

#define ICER0		(0xE000E180)
#define ICER1		(0xE000E184)

#define ISPR0		(0xE000E200)
#define ISPR1		(0xE000E204)

#define ICPR0		(0xE000E280)

#define IPR0		(0xE000E400)
#define IPR1		(0xE000E404)

/* STM32F103 RELATED REGISTERS */

/* CAN DRIVERS */
#define CAN1_BASE			(0x40006400)

#define CAN_MCR				(0x000)
#define CAN_MSR				(0x004)
#define CAN_TSR				(0x008)

#define CAN_RF0R			(0x00C)
#define CAN_RF1R			(0x010)

#define CAN_IER				(0x014)
#define CAN_ESR				(0x018)
#define CAN_BTR				(0x01C)
#define CAN_TI0R			(0x180)
#define CAN_TDT0R			(0x184)
#define CAN_TDL0R			(0x188)
#define CAN_TDH0R			(0x18C)
#define CAN_TI1R			(0x190)
#define CAN_TDT1R			(0x194)
#define CAN_TDL1R			(0x198)
#define CAN_TDH1R			(0x19C)
#define CAN_TI2R			(0x1A0)
#define CAN_TDT2R			(0x1A4)
#define CAN_TDL2R			(0x1A8)
#define CAN_TDH2R			(0x1AC)
#define CAN_RI0R			(0x1B0)
#define CAN_RDT0R			(0x1B4)
#define CAN_RDL0R			(0x1B8)
#define CAN_RDH0R			(0x1BC)
#define CAN_RI1R			(0x1C0)
#define CAN_RDT1R			(0x1C4)
#define CAN_RDL1R			(0x1C8)
#define CAN_RDH1R			(0x1CC)
#define CAN_FMR				(0x200)
#define CAN_FM1R			(0x204)
#define CAN_FS1R			(0x20C)
#define CAN_FFA1R			(0x214)
#define CAN_FA1R			(0x21C)
#define CAN_F0R1			(0x240)
#define CAN_F0R2			(0x244)
#define CAN_F1R1			(0x248)
#define CAN_F1R2			(0x24C)
#define CAN_F27R1			(0x318)
#define CAN_F27R2			(0x31C)

/* ADC REGISTERS */
#define ADC1_BASE			(0x40012400)
#define ADC2_BASE			(0x40012800)

#define ADC_SR				(0x00)
#define ADC_CR1				(0x04)
#define ADC_CR2				(0x08)
#define ADC_SMPR1			(0x0C)
#define ADC_SMPR2			(0x10)
#define ADC_JOFR1			(0x14)
#define ADC_JOFR2			(0x18)
#define ADC_JOFR3			(0x1C)
#define ADC_JOFR4			(0x20)
#define ADC_HTR				(0x24)
#define ADC_LTR				(0x28)
#define ADC_SQR1			(0x2C)
#define ADC_SQR2			(0x30)
#define ADC_SQR3			(0x34)
#define ADC_JSQR			(0x38)
#define ADC_JDR1			(0x3C)
#define ADC_JDR2			(0x40)
#define ADC_JDR3			(0x44)
#define ADC_JDR4			(0x48)
#define ADC_DR				(0x4C)

/* USART REGISTERSR */
#define USART1_BASE			(0x40013800)
#define USART3_BASE			(0x40004800)

#define USART_SR			(0x00)
#define USART_DR			(0x04)
#define USART_BRR			(0x08)
#define USART_CR1			(0x0C)
#define USART_CR2			(0x10)
#define USART_CR3			(0x14)
#define USART_GTPR			(0x18)

/* EXTERNAL INTERRUPTS */
#define EXTI_BASE			(0x40010400)
#define EXTI_IMR			(0x00)
#define EXTI_EMR			(0x04)
#define EXTI_RTSR			(0x08)
#define EXTI_FTSR			(0x0C)
#define EXTI_SWIER			(0x10)
#define EXTI_PR				(0x14)

/* RCC REGISTERS */
#define RCC_BASE			(0x40021000)

#define RCC_CR				(0x00)
#define RCC_CFGR			(0x04)
#define RCC_CIR				(0x08)
#define RCC_APB2RSTR		(0x0C)
#define RCC_APB1RSTR		(0x10)
#define RCC_AHBENR			(0x14)
#define RCC_APB2ENR			(0x18)
#define RCC_APB1ENR			(0x1C)
#define RCC_BDCR			(0x20)
#define RCC_CSR				(0x24)


/* AFIO REGISTERS */
#define AFIO_BASE			(0x40010000)

#define AFIO_MAPR			(0x04)
#define AFIO_EXTICR1		(0x08)
#define AFIO_EXTICR2		(0x0C)
#define AFIO_EXTICR3		(0x10)
#define AFIO_EXTICR4		(0x14)

/* GPIO REGISTERS */

#define GPIOA_BASE			(0x40010800)
#define GPIOB_BASE			(0x40010C00)

#define GPIO_CRL			(0x00)
#define GPIO_CRH			(0x04)
#define GPIO_IDR			(0x08)
#define GPIO_ODR			(0x0C)
#define GPIO_BSRR			(0x10)
#define GPIO_BRR			(0x14)
#define GPIO_LCKR			(0x18)

#endif

/** END OF FILE: Registers.h
 *****************************************************/