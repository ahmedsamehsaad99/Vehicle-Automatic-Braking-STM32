/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Usart.h
 *  DESCRIPTION:	Header file for the USART driver for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef USART_H_
#define USART_H_

#include "../../Common/Registers.h"
#include "../../Common/Std_Types.h"
#include "../../Config/MCAL/Inc/Usart_Cfg.h"

 /** TYPEDEFS
 *****************************************************/

typedef enum
{
	USART_1 = 1, USART_2, USART_3
} Usart_ControllerNumber;

typedef enum
{
	USART_STOPBIT_1, USART_STOPBIT_HALF, USART_STOPBIT_2, USART_STOPBIT_1_HALF
} Usart_StopBitType;

typedef float32 Usart_BaudrateType;

typedef uint16	Usart_DataType;
typedef uint8*	Usart_StringType;

typedef struct
{
	Usart_ControllerNumber ContNumber;
	Usart_BaudrateType	Baudrate;
	Usart_StopBitType	Stopbits;
	uint8	Databits;
} Usart_ConfigType;

typedef enum
{
	USART_PE, USART_FE, USART_NE, USART_ORE, USART_IDLE, USART_RXNE, USART_TC, USART_TXE, USART_LBD, USART_CTS
} Usart_FlagType;

 /** FUNCTIONS PROTOTYPES
 *****************************************************/
void Usart_Init(const Usart_ConfigType* ConfigPtr);
void Usart_Transmit(Usart_ControllerNumber ContNumber, Usart_DataType Data);
void Usart_TransmitString(Usart_ControllerNumber ContNumber, Usart_StringType String);
Std_ReturnType Usart_GetFlag(Usart_ControllerNumber ContNumber, Usart_FlagType Flag);
Usart_DataType Usart_Receive(Usart_ControllerNumber ContNumber);

#endif

 /** END OF FILE: Usart.h
  *****************************************************/