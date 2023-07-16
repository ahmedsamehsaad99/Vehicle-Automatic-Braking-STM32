/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			IntCtrl.c
 *  DESCRIPTION:	C file for the interrupts for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../Inc/IntCtrl.h"
#include "../Inc/Dio.h"

extern IntCtrl_ConfigType IntCtrl_Configuration[];

static IntCtrl_IntHandlerType (*IntCtrl_Handlers [])() =
{
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

void IntCtrl_SetCallBack(IntCtrl_InterruptType Interrupt, IntCtrl_IntHandlerType (*CallBack))
{
	IntCtrl_Handlers[Interrupt] = CallBack;
}

void IntCtrl_EnableInterrupt(IntCtrl_InterruptType Interrupt)
{
	
	uint8 RegisterSelection = (Interrupt-16) / 32;
	setBitState(REG(ISER0, RegisterSelection * 0x04), ((Interrupt - 16) % 32), STD_HIGH);
}

void IntCtrl_DisableInterrupt(IntCtrl_InterruptType Interrupt)
{
	uint8 RegisterSelection = (Interrupt-16) / 32;
	setBitState(REG(ICER0, RegisterSelection * 0x04), ((Interrupt - 16) % 32), STD_HIGH);
}

void IntCtrl_ClearExtPendingInt(IntCtrl_InterruptType Interrupt)
{
	if ((Interrupt <= 26 && Interrupt >= 22))
		setBitState(REG(EXTI_BASE, EXTI_PR), (Interrupt - 22), STD_HIGH);
	else if (Interrupt == 39)
		setValue(REG(EXTI_BASE, EXTI_PR), 5, 0x0E); /* 15 */
}

void IntCtrl_Init(void)
{
	uint8 i = 0;

	for (i = 0; i < USED_INTERRUPTS; i++)
	{
		IntCtrl_InterruptType Interrupt = IntCtrl_Configuration[i].Interrupt;

		/* FOR EXTERNAL INTERRUPTS */
		if ( (Interrupt <= 26 && Interrupt >= 22) )
		{
			setBitState(REG(EXTI_BASE, EXTI_IMR), (Interrupt - 22), STD_HIGH);
		
			switch (IntCtrl_Configuration[i].Trigger)
			{
			case INT_TRIGGER_RISING:
				setBitState(REG(EXTI_BASE, EXTI_RTSR), (Interrupt - 22), STD_HIGH);
				break;
			case INT_TRIGGER_FALLING:
				setBitState(REG(EXTI_BASE, EXTI_FTSR), (Interrupt - 22), STD_HIGH);
				break;
			case INT_TRIGGER_NONE:
				break;
			}
		}
		else if(Interrupt == 39)
		{
			setValue(REG(EXTI_BASE, EXTI_IMR), 5, 0x0E); /* 15 */
			switch (IntCtrl_Configuration[i].Trigger)
			{
			case INT_TRIGGER_RISING:
				setValue(REG(EXTI_BASE, EXTI_RTSR), 5, 0x0E);
				break;
			case INT_TRIGGER_FALLING:
				setValue(REG(EXTI_BASE, EXTI_FTSR), 5, 0x0E);
				break;
			case INT_TRIGGER_NONE:
				break;
			}
		}
		IntCtrl_SetCallBack(Interrupt, IntCtrl_Configuration[i].CallBack);
		IntCtrl_EnableInterrupt(Interrupt);
	}
}

void SysTick_Handler(void)				{ (*(IntCtrl_Handlers[SysTick])) (); }
void WWDG_IRQHandler(void)				{ (*(IntCtrl_Handlers[WWDG])) (); }
void PVD_IRQHandler(void)				{ (*(IntCtrl_Handlers[PVD])) (); }
void TAMPER_IRQHandler(void)			{ (*(IntCtrl_Handlers[TAMPER])) (); }
void RTC_IRQHandler(void)				{ (*(IntCtrl_Handlers[RTC])) (); }
void FLASH_IRQHandler(void)				{ (*(IntCtrl_Handlers[FLASH])) (); }
void RCC_IRQHandler(void)				{ (*(IntCtrl_Handlers[RCC])) (); }
void EXTI0_IRQHandler(void)				{ IntCtrl_ClearExtPendingInt(EXTI0); (*(IntCtrl_Handlers[EXTI0])) (); }
void EXTI1_IRQHandler(void)				{ IntCtrl_ClearExtPendingInt(EXTI1); (*(IntCtrl_Handlers[EXTI1])) (); }
void EXTI2_IRQHandler(void)				{ IntCtrl_ClearExtPendingInt(EXTI2); (*(IntCtrl_Handlers[EXTI2])) (); }
void EXTI3_IRQHandler(void)				{ IntCtrl_ClearExtPendingInt(EXTI3); (*(IntCtrl_Handlers[EXTI3])) (); }
void EXTI4_IRQHandler(void)				{ IntCtrl_ClearExtPendingInt(EXTI4); (*(IntCtrl_Handlers[EXTI4])) (); }
void DMA1_Channel1_IRQHandler(void)		{ (*(IntCtrl_Handlers[DMA1_Channel1])) (); }
void DMA1_Channel2_IRQHandler(void)		{ (*(IntCtrl_Handlers[DMA1_Channel2])) (); }
void DMA1_Channel3_IRQHandler(void)		{ (*(IntCtrl_Handlers[DMA1_Channel3])) (); }
void DMA1_Channel4_IRQHandler(void)		{ (*(IntCtrl_Handlers[DMA1_Channel4])) (); }
void DMA1_Channel5_IRQHandler(void)		{ (*(IntCtrl_Handlers[DMA1_Channel5])) (); }
void DMA1_Channel6_IRQHandler(void)		{ (*(IntCtrl_Handlers[DMA1_Channel6])) (); }
void DMA1_Channel7_IRQHandler(void)		{ (*(IntCtrl_Handlers[DMA1_Channel7])) (); }
void ADC1_2_IRQHandler(void)			{ (*(IntCtrl_Handlers[ADC1_2])) (); }
void USB_HP_CAN1_TX_IRQHandler(void)	{ (*(IntCtrl_Handlers[USB_HP_CAN_TX])) (); }
void USB_LP_CAN1_RX0_IRQHandler(void)	{ (*(IntCtrl_Handlers[USB_LP_CAN_RX0])) (); }
void CAN1_RX1_IRQHandler(void)			{ (*(IntCtrl_Handlers[CAN_RX1])) (); }
void CAN1_SCE_IRQHandler(void)			{ (*(IntCtrl_Handlers[CAN_SCE])) (); }
void EXTI9_5_IRQHandler(void)			{ (*(IntCtrl_Handlers[EXTI9_5])) (); }
void TIM1_BRK_IRQHandler(void)			{ (*(IntCtrl_Handlers[TIM1_BRK])) (); }
void TIM1_UP_IRQHandler(void)			{ (*(IntCtrl_Handlers[TIM1_UP])) (); }
void TIM1_TRG_COM_IRQHandler(void)		{ (*(IntCtrl_Handlers[TIM1_TRG_COM])) (); }
void TIM1_CC_IRQHandler(void)			{ (*(IntCtrl_Handlers[TIM1_CC])) (); }
void TIM2_IRQHandler(void)				{ (*(IntCtrl_Handlers[TIM2])) (); }
void TIM3_IRQHandler(void)				{ (*(IntCtrl_Handlers[TIM3])) (); }
void TIM4_IRQHandler(void)				{ (*(IntCtrl_Handlers[TIM4])) (); }
void I2C1_EV_IRQHandler(void)			{ (*(IntCtrl_Handlers[I2C1_EV])) (); }
void I2C1_ER_IRQHandler(void)			{ (*(IntCtrl_Handlers[I2C1_ER])) (); }
void I2C2_EV_IRQHandler(void)			{ (*(IntCtrl_Handlers[I2C2_EV])) (); }
void I2C2_ER_IRQHandler(void)			{ (*(IntCtrl_Handlers[I2C2_ER])) (); }
void SPI1_IRQHandler(void)				{ (*(IntCtrl_Handlers[SPI1])) (); }
void SPI2_IRQHandler(void)				{ (*(IntCtrl_Handlers[SPI2])) (); }
void USART1_IRQHandler(void)			{ (*(IntCtrl_Handlers[USART1])) (); }
void USART2_IRQHandler(void)			{ (*(IntCtrl_Handlers[USART2])) (); }
void USART3_IRQHandler(void)			{ (*(IntCtrl_Handlers[USART3])) (); }
void EXTI15_10_IRQHandler(void)			{ (*(IntCtrl_Handlers[EXTI15_10])) (); }
void RTCAlarm_IRQHandler(void)			{ (*(IntCtrl_Handlers[RTCAlarm])) (); }
void USBWakeUp_IRQHandler(void)			{ (*(IntCtrl_Handlers[USBWakeup])) (); }


 /** END OF FILE: IntCtrl.c
  *****************************************************/