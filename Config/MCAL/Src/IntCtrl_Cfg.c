/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			IntCtrl_Cfg.c
 *  DESCRIPTION:	C file for the interrupt configuration for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../../MCAL/Inc/IntCtrl.h"

#if (USED_INTERRUPTS)


extern void Button_1_ISR();
extern void Button_0_ISR();
extern void ADC_ISR();
extern void USART1_ISR();
extern void USART3_ISR();
extern void Can_ISR();

const IntCtrl_ConfigType IntCtrl_Configuration[USED_INTERRUPTS] =
{
	{ADC1_2, 1, INT_TRIGGER_NONE, ADC_ISR},
	{USART1, 1, INT_TRIGGER_NONE, USART1_ISR},
	{USART3, 1, INT_TRIGGER_NONE, USART3_ISR},
	{USB_LP_CAN_RX0, 1, INT_TRIGGER_NONE, Can_ISR},
};


#else

IntCtrl_ConfigType* IntCtrl_Configuration;

#endif
 /** END OF FILE: IntCtrl_Cfg.c
  *****************************************************/