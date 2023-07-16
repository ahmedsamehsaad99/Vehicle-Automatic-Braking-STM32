/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			BrakingRelays.c
 *  DESCRIPTION:	C file for the Braking Relays Handling
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../Inc/BrakingRelays.h"

void Braking_SetAbsPosRelay(Braking_RelayStateType State)
{
	Relay_SetState((Relay_Type)ABS_POS_RELAY, State);
}

void Braking_SetAbsNegRelay(Braking_RelayStateType State)
{
	Relay_SetState((Relay_Type)ABS_NEG_RELAY, State);
}

void Braking_Set12VRelay(Braking_RelayStateType State)
{
	Relay_SetState((Relay_Type)BATTERY_12V_RELAY, State);
}

void Braking_SetBlsRelay(Braking_RelayStateType State)
{
	Relay_SetState((Relay_Type)BLS_CTRL_RELAY, State);
}

void Braking_SetBlsCtrlRelay(Braking_RelayStateType State)
{
	Relay_SetState((Relay_Type)BLS_RELAY, State);
}
