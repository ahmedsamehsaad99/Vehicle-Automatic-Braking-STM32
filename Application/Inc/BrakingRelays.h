/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			BrakingRelays.h
 *  DESCRIPTION:	Header file for the Braking Relays Handling
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef BRAKING_RELAY_H
#define BRAKING_RELAY_H

#include "BrakingPinout.h"
#include "../../HAL/Inc/Relay.h"

typedef Relay_StateType Braking_RelayStateType;

void Braking_SetAbsPosRelay(Braking_RelayStateType State);
void Braking_SetAbsNegRelay(Braking_RelayStateType State);
void Braking_Set12VRelay(Braking_RelayStateType State);
void Braking_SetBlsCtrlRelay(Braking_RelayStateType State);
void Braking_SetBlsRelay(Braking_RelayStateType State);

#endif