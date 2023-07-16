/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Dio.h
 *  DESCRIPTION:	Header file for the Dio driver for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef DIO_H_
#define DIO_H_

#include "../../Common/Registers.h"
#include "../../Common/Std_Types.h"
#include "Port.h"
#include "../../Config/MCAL/Inc/Dio_Cfg.h"

 /** TYPEDEFS
 *****************************************************/
typedef Port_PinType Dio_ChannelType;

typedef Port_PortType Dio_PortType;

typedef struct
{
	Dio_PortType port;
	uint8 offset;
	uint16 mask;
} Dio_ChannelGroupType;

typedef uint8 Dio_LevelType;

typedef uint16 Dio_PortLevelType;


/** FUNCTIONS PROTOTYPES
*****************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);
void Dio_ToggleChannel(Dio_ChannelType ChannelId);

Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr);
void Dio_WriteChannelGroup(const Dio_ChannelGroupType *ChannelGroupIdPtr, Dio_PortLevelType Level);


#endif

/** END OF FILE: Dio.h
 *****************************************************/