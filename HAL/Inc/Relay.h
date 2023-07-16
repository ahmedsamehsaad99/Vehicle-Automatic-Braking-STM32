/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Relay.h
 *  DESCRIPTION:	Header file for the Relay HAL
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef RELAY_H
#define RELAY_H

#include "../../MCAL/Inc/Dio.h"
#include "../../Config/HAL/Inc/Relay_Cfg.h"

typedef Dio_ChannelType Relay_Type;
typedef uint8 Relay_StateType;

void Relay_SetState(Relay_Type Relay, Relay_StateType State);
void Relay_ToggleState(Relay_Type Relay);

#endif