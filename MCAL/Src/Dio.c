/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Dio.c
 *  DESCRIPTION:	C file for the Dio driver for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../Inc/Dio.h"

Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	Dio_LevelType State = getBit(REG(GPIOA_BASE + (ChannelId / 16) * 0x400, GPIO_IDR), ChannelId % 16);
	return State;
}

void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	switch (Level)
	{
	case STD_LOW:
		//setBitState(REG(GPIOA_BASE + (ChannelId / 16) * 0x400, GPIO_BSRR), (ChannelId % 16) + 16, STD_HIGH);
		setBitState(REG(GPIOA_BASE + (ChannelId / 16) * 0x400, GPIO_ODR), ChannelId % 16, STD_LOW);
		break;

	case STD_HIGH:
		//setBitState(REG(GPIOA_BASE + (ChannelId / 16) * 0x400, GPIO_BSRR), (ChannelId % 16), STD_HIGH);
		setBitState(REG(GPIOA_BASE + (ChannelId / 16) * 0x400, GPIO_ODR), ChannelId % 16, STD_HIGH);
		break;
	}
}

void Dio_ToggleChannel(Dio_ChannelType ChannelId)
{
	toggleBit(REG(GPIOA_BASE + (ChannelId / 16) * 0x400, GPIO_ODR), ChannelId % 16);
}


Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
	Dio_PortLevelType Level = getValue(REG((GPIOA_BASE + (PortId) * 0x400), GPIO_IDR), 0, 0xFF);
	return Level;
}

void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
	REG((GPIOA_BASE + (PortId) * 0x400), GPIO_ODR) = Level;
}



Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr)
{
	Dio_PortLevelType Level = getValue(REG(GPIOA_BASE + (ChannelGroupIdPtr->port) * 0x400, GPIO_IDR), ChannelGroupIdPtr->offset, ChannelGroupIdPtr->mask);
	return Level;
}

void Dio_WriteChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level)
{
	setValue(REG(GPIOA_BASE + (ChannelGroupIdPtr->port) * 0x400, GPIO_ODR), ChannelGroupIdPtr->offset, Level);
}


 /** END OF FILE: Dio.c
  *****************************************************/