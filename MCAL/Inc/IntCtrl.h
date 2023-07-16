/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			IntCtrl.h
 *  DESCRIPTION:	Header file for the interrupt for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef INTCTRL_H_
#define INTCTRL_H_

#include "../../Common/Registers.h"
#include "../../Common/Std_Types.h"
#include "../../Config/MCAL/Inc/IntCtrl_Cfg.h"

 /** TYPEDEFS
 *****************************************************/

typedef enum 
{
	/* EXCEPTIONS */
	NMI = 2,
	HardFault,
	MemManage,
	BusFault,
	UsageFault,
	SVCall = 11,
	PendSV = 14,
	SysTick = 15,

	/* INTERRUPTS */
	WWDG = 16,
	PVD,
	TAMPER,
	RTC,
	FLASH,
	RCC,
	EXTI0,
	EXTI1,
	EXTI2,
	EXTI3,
	EXTI4,
	DMA1_Channel1,
	DMA1_Channel2,
	DMA1_Channel3,
	DMA1_Channel4,
	DMA1_Channel5,
	DMA1_Channel6,
	DMA1_Channel7,
	ADC1_2,
	USB_HP_CAN_TX,
	USB_LP_CAN_RX0,
	CAN_RX1,
	CAN_SCE,
	EXTI9_5,
	TIM1_BRK,
	TIM1_UP,
	TIM1_TRG_COM,
	TIM1_CC,
	TIM2,
	TIM3,
	TIM4,
	I2C1_EV,
	I2C1_ER,
	I2C2_EV,
	I2C2_ER,
	SPI1,
	SPI2,
	USART1,
	USART2,
	USART3,
	EXTI15_10,
	RTCAlarm,
	USBWakeup,
} IntCtrl_InterruptType;

typedef uint8 IntCtrl_PriorityType;

typedef enum 
{
	INT_TRIGGER_NONE, INT_TRIGGER_RISING, INT_TRIGGER_FALLING
} IntCtrl_TriggerType;

typedef void IntCtrl_IntHandlerType;

typedef struct
{
	IntCtrl_InterruptType Interrupt;
	IntCtrl_PriorityType Priority;
	IntCtrl_TriggerType Trigger;
	IntCtrl_IntHandlerType (*CallBack)();
} IntCtrl_ConfigType;


/** FUNCTIONS PROTOTYPES
*****************************************************/

void IntCtrl_EnableInterrupt(IntCtrl_InterruptType Interrupt);
void IntCtrl_DisableInterrupt(IntCtrl_InterruptType Interrupt);
void IntCtrl_SetCallBack(IntCtrl_InterruptType Interrupt, IntCtrl_IntHandlerType (*CallBack));
void IntCtrl_Init(void);
void IntCtrl_ClearExtPendingInt(IntCtrl_InterruptType Interrupt);

#endif

 /** END OF FILE: IntCtrl.h
  *****************************************************/