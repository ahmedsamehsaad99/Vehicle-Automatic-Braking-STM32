/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Port_Cfg.c
 *  DESCRIPTION:	C file for the PORT config for STM32F103
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../../MCAL/Inc/Port.h"

#if (USED_PINS)

const Port_ConfigType Port_Configuration[USED_PINS] =
{
	/* PWM PINOUT */
	{PORT_A_PIN_3, PORT_MODE_TIMER_OUT, PORT_PIN_OUT, PIN_LOW},

	/* USART PINOUTS */
	{PORT_A_PIN_10, PORT_MODE_USART_IN, PORT_PIN_IN, PIN_LOW},
	{PORT_A_PIN_9, PORT_MODE_USART_OUT, PORT_PIN_OUT, PIN_LOW},
	{PORT_B_PIN_10, PORT_MODE_USART_OUT, PORT_PIN_IN, PIN_LOW},
	{PORT_B_PIN_11, PORT_MODE_USART_IN, PORT_PIN_OUT, PIN_LOW},
	
	/* CAN PINOUTS */
	{PORT_B_PIN_0, PORT_MODE_CAN_IN, PORT_PIN_IN, PIN_LOW},
	{PORT_A_PIN_12, PORT_MODE_CAN_OUT, PORT_PIN_OUT, PIN_LOW},

	/* DIO OUT */
	{PORT_B_PIN_0, PORT_MODE_DIO_OUT, PORT_PIN_OUT, PIN_LOW},
	{PORT_B_PIN_1, PORT_MODE_DIO_OUT, PORT_PIN_OUT, PIN_LOW},
	{PORT_A_PIN_7, PORT_MODE_DIO_OUT, PORT_PIN_OUT, PIN_LOW},
	{PORT_B_PIN_12, PORT_MODE_DIO_OUT, PORT_PIN_OUT, PIN_LOW},
	{PORT_B_PIN_13, PORT_MODE_DIO_OUT, PORT_PIN_OUT, PIN_LOW},	
};

#else

Port_ConfigType *Port_Configuration;

#endif


/** END OF FILE: Port_Cfg.c
 *****************************************************/