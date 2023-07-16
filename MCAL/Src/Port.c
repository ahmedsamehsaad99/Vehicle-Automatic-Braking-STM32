/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Port.c
 *  DESCRIPTION:	C file for the Port driver for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../Inc/Port.h"

void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
	Port_PortType CurrentPort = Pin / 16;

	uint16 isHigh = (Pin - (CurrentPort * 16)) < 8 ? 0 : 1;
	setValue(REG(GPIOA_BASE + (CurrentPort) * 0x400, GPIO_CRL + 0x04 * isHigh), (Pin % 8) * 4, Direction);

}

void Port_Init(const Port_ConfigType *ConfigType) 
{
	uint8 i = 0;

	for (i = 0; i < USED_PINS; i++)
	{
		Port_PinType CurrentPin = ConfigType[i].PortPin;
		Port_PortType CurrentPort = CurrentPin / 16;

		uint16 isHigh = (CurrentPin - (CurrentPort * 16)) < 8 ? 0 : 1;

		/* ENABLE CLOCK FOR THE CURRENT GPIO AND AFIO */
		setBitState(REG(RCC_BASE, RCC_APB2ENR), CurrentPort + 2, STD_HIGH);
		setBitState(REG(RCC_BASE, RCC_APB2ENR), 0, STD_HIGH);
		
		/* SET THE MODE BITS*/
		Port_SetPinDirection(CurrentPin, ConfigType[i].PORT_PIN_DIRECTION);

		/* SET THE CONF BITS */
		setValue(REG(GPIOA_BASE + (CurrentPort) * 0x400, GPIO_CRL + 0x04 * isHigh), ((CurrentPin % 8) * 4) + 2, ConfigType[i].PORT_PIN_MODE % 4);

		/* SET THE LEVEL BITS */
		switch (ConfigType[i].PORT_PIN_LEVEL_VALUE)
		{
		case PIN_LOW:
			setBitState(REG(GPIOA_BASE + (CurrentPin / 16) * 0x400, GPIO_BSRR), (CurrentPin % 16) + 16, STD_HIGH);
			break;

		case PIN_HIGH:
			setBitState(REG(GPIOA_BASE + (CurrentPin / 16) * 0x400, GPIO_BSRR), (CurrentPin % 16), STD_HIGH);
			break;
		}

		/* HANDLING EXTERNAL INTERRUPTS PINS */

		if (ConfigType[i].PORT_PIN_MODE == PORT_MODE_EXT_INT)
		{
			setValue(REG(AFIO_BASE, AFIO_EXTICR1 + ((CurrentPin % 16) / 4) * 0x04), (CurrentPin % 4) * 4, CurrentPort);
		}
	}
}

/** END OF FILE: Port.c
 *****************************************************/