/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			BrakingStates.h
 *  DESCRIPTION:	Header file for the Braking States
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef BRAKING_STATES_H
#define BRAKING_STATES_H

#include "BrakingRelays.h"

#define ABS_STATE	0
#define MCU_STATE	1

typedef uint8	Braking_FlagType;

void Braking_AbsState(void);
void Braking_McuState(void);
void Braking_SwitchState(void);

#endif