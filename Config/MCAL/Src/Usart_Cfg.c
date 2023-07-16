
/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Usart_Cfg.c
 *  DESCRIPTION:	C file for the USART configuration for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../../MCAL/Inc/Usart.h"

const Usart_ConfigType Usart_Configuration[2] =
{
	{USART_1, 9600, USART_STOPBIT_1, 9},
	{USART_3, 9600, USART_STOPBIT_1, 9}
};


 /** END OF FILE: Usart_Cfg.h
  *****************************************************/
