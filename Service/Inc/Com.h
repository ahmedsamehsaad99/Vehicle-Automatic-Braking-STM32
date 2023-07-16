/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Com.h
 *  DESCRIPTION:	Header file for the Communication Service
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef COM_H
#define COM_H

#include "../../MCAL/Inc/Usart.h"
#include "../../MCAL/Inc/Can.h"
#include "../../Config/Services/Inc/Com_Cfg.h"

typedef enum 
{
	PROTOCOL_UART, PROTOCOL_CAN, PROTOCOL_I2C, PROTOCOL_SPI
} Com_ProtocolType;

typedef struct 
{
	Com_ProtocolType Protocol;
} Com_ConfigType;

typedef uint16	Com_DataType;
typedef uint16	Com_IdType;
typedef uint8	Com_DataLengthType;

typedef struct 
{
	Com_IdType Id;
	Com_DataLengthType DataLength;
	Com_DataType Data;
} Com_MsgType;

void Com_Init(const Com_ConfigType *ConfigPtr);
void Com_SendMsg(Com_ProtocolType Protocol, Com_MsgType* Message);
void Com_ReceiveMsg(Com_ProtocolType Protocol, Com_MsgType *MsgToReturn);

#endif