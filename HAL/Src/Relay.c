/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Relay.c
 *  DESCRIPTION:	C file for the Relay HAL
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../Inc/Relay.h"

void Relay_SetState(Relay_Type Relay, Relay_StateType State)
{
	Dio_WriteChannel((Dio_ChannelType) Relay, State);
}

void Relay_ToggleState(Relay_Type Relay)
{
	Dio_ToggleChannel((Dio_ChannelType)Relay);
}