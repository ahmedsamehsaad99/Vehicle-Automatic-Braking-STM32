/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			GPIO.h
 *  DESCRIPTION:	Header file for the GPIO driver for STM32F103
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "../../Common/Registers.h"
#include "../../Common/Std_Types.h"

#define PORTS_NUMBER 2 /* A and B*/

typedef enum GPIO_Pin_t
{
	PINA_0,
	PINA_1,
	PINA_2,
	PINA_3,
	PINA_4,
	PINA_5,
	PINA_6,
	PINA_7,
	PINA_8,
	PINA_9,
	PINA_10,
	PINA_11,
	PINA_12,
	PINA_13,
	PINA_14,
	PINA_15,

	PINB_0,
	PINB_1,
	PINB_2,
	PINB_3,
	PINB_4,
	PINB_5,
	PINB_6,
	PINB_7,
	PINB_8,
	PINB_9,
	PINB_10,
	PINB_11,
	PINB_12,
	PINB_13,
	PINB_14,
	PINB_15
} GPIO_Pin_t;

typedef enum
{
	PORTA, PORTB
}GPIO_Port_t;

typedef enum
{
	INPUT, OUTPUT /* DEFUALT 10MHz*/, OUTPUT_2MHz, OUTPUT_50MHz
} GPIO_Direction_t;

typedef enum
{
	ANALOG, FLOATING, PULL, NONE
} GPIO_InputType_t;

typedef struct
{
	GPIO_Pin_t	thePin;
	GPIO_Direction_t theDirection;
	GPIO_InputType_t InputType;
} GPIO_Config_t;

typedef enum
{
	LOW, HIGH
} GPIO_PinState_t;

void GPIO_Init(void);
void GPIO_SetPinState(GPIO_Pin_t thePin, GPIO_PinState_t theState);
void GPIO_TogglePin(GPIO_Pin_t thePin);
GPIO_PinState_t GPIO_GetPinState(GPIO_Pin_t thePin);

#endif
	/** END OF FILE: GPIO.h
	 *****************************************************/