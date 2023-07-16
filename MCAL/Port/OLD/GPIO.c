/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			GPIO.c
 *  DESCRIPTION:	C file for the GPIO driver for STM32F103
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "GPIO.h"
#include "../../Config/GPIO_config.h"

extern GPIO_Config_t GPIO_Configuration[];

void GPIO_Init(void)
{
	uint8_t i = 0;

	for (i = 0; i < USED_PINS; i++)
	{
		GPIO_Pin_t currentPin = GPIO_Configuration[i].thePin;
		GPIO_Port_t currentPort = currentPin / 16;

		/* ENABLE CLOCK FOR THE CURRENT GPIO */
		setBitState(REG(RCC_BASE, RCC_APB2ENR), currentPort + 2, HIGH);

		uint16_t isHigh = (currentPin - (currentPort * 16)) < 8 ? 0 : 1;
		setValue(REG(GPIOA_BASE + (currentPort) * 0x400, GPIO_CRL + 0x04 * isHigh), (currentPin % 8) * 4, GPIO_Configuration[i].theDirection);

		if (GPIO_Configuration[i].theDirection == INPUT)
		{
			setValue(REG(GPIOA_BASE + (currentPort) * 0x400, GPIO_CRL + 0x04 * isHigh), ((currentPin % 8) * 4) + 2, GPIO_Configuration[i].InputType);
		}
	}
}

void GPIO_SetPinState(GPIO_Pin_t thePin, GPIO_PinState_t theState)
{
	switch (theState)
	{
		case LOW:
			setBitState(REG(GPIOA_BASE + (thePin / 16) * 0x400, GPIO_BSRR), (thePin % 16) + 16, HIGH);
			break;

		case HIGH:
			setBitState(REG(GPIOA_BASE + (thePin / 16) * 0x400, GPIO_BSRR), (thePin % 16), HIGH);
			break;
	}
}

void GPIO_TogglePin(GPIO_Pin_t thePin)
{
	toggleBit(REG(GPIOA_BASE + (thePin / 16) * 0x400, GPIO_ODR), thePin % 16);
}

GPIO_PinState_t GPIO_GetPinState(GPIO_Pin_t thePin)
{
	GPIO_PinState_t theState = getBit(REG(GPIOA_BASE + (thePin / 16) * 0x400, GPIO_IDR), thePin % 16);
	return theState;
}


 /** END OF FILE: GPIO.c
  *****************************************************/