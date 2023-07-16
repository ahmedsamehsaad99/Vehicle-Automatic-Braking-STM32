/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Port.h
 *  DESCRIPTION:	Header file for the Port driver for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef PORT_H_
#define PORT_H_

#include "../../Common/Registers.h"
#include "../../Common/Std_Types.h"
#include "../../Config/MCAL/Inc/Port_Cfg.h"

 /** TYPEDEFS
 *****************************************************/

#define INPUT_ANALOG			0
#define INPUT_FLOATING			1
#define INPUT_PULL				2

#define	OUTPUT_GP_PULL			4
#define OUTPUT_GP_DRAIN			5
#define OUTPUT_AF_PUSH_PULL		6
#define OUTPUT_AF_DRAIN			7

typedef enum
{
	PORT_A_PIN_0,
	PORT_A_PIN_1,
	PORT_A_PIN_2,
	PORT_A_PIN_3,
	PORT_A_PIN_4,
	PORT_A_PIN_5,
	PORT_A_PIN_6,
	PORT_A_PIN_7,
	PORT_A_PIN_8,
	PORT_A_PIN_9,
	PORT_A_PIN_10,
	PORT_A_PIN_11,
	PORT_A_PIN_12,
	PORT_A_PIN_13,
	PORT_A_PIN_14,
	PORT_A_PIN_15,

	PORT_B_PIN_0,
	PORT_B_PIN_1,
	PORT_B_PIN_2,
	PORT_B_PIN_3,
	PORT_B_PIN_4,
	PORT_B_PIN_5,
	PORT_B_PIN_6,
	PORT_B_PIN_7,
	PORT_B_PIN_8,
	PORT_B_PIN_9,
	PORT_B_PIN_10,
	PORT_B_PIN_11,
	PORT_B_PIN_12,
	PORT_B_PIN_13,
	PORT_B_PIN_14,
	PORT_B_PIN_15,
} Port_PinType;

typedef enum
{
	PORT_MODE_DIO_IN		= INPUT_PULL,
	PORT_MODE_DIO_OUT		= OUTPUT_GP_PULL,
	PORT_MODE_ADC			= INPUT_ANALOG,
	PORT_MODE_CAN_OUT		= OUTPUT_AF_PUSH_PULL,
	PORT_MODE_CAN_IN		= INPUT_FLOATING,
	PORT_MODE_I2C			= OUTPUT_AF_DRAIN,
	PORT_MODE_SPI_OUT		= OUTPUT_AF_PUSH_PULL,
	PORT_MODE_SPI_IN		= INPUT_FLOATING,
	PORT_MODE_USART_OUT		= OUTPUT_AF_PUSH_PULL,
	PORT_MODE_USART_IN		= INPUT_FLOATING,
	PORT_MODE_TIMER_OUT		= OUTPUT_AF_PUSH_PULL,
	PORT_MODE_TIMER_IN		= INPUT_FLOATING,
	PORT_MODE_EXT_INT		= INPUT_PULL,
} Port_PinModeType;

typedef enum
{
	PORT_PIN_IN, PORT_PIN_OUT
} Port_PinDirectionType;

typedef enum
{
	PIN_LOW, PIN_HIGH
} Port_PinLevelType;

typedef struct
{
	Port_PinType PortPin;
	Port_PinModeType PORT_PIN_MODE;
	Port_PinDirectionType PORT_PIN_DIRECTION;
	Port_PinLevelType PORT_PIN_LEVEL_VALUE;
} Port_ConfigType;

typedef enum
{
	PORTA, PORTB
} Port_PortType;


/** FUNCTION PROTOTYPES
 *****************************************************/
void Port_Init(const Port_ConfigType *ConfigType);
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
void Port_RefreshPortDirection(void);

#endif

/** END OF FILE
 *****************************************************/