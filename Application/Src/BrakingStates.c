/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			BrakingStates.c
 *  DESCRIPTION:	C file for the Braking States
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../Inc/BrakingStates.h"

extern Braking_FlagType CurrentState;

void Braking_AbsState(void)
{
	Braking_Set12VRelay(STD_LOW);

	Braking_SetAbsPosRelay(STD_LOW);
	Braking_SetAbsNegRelay(STD_LOW);

	Braking_SetBlsRelay(STD_LOW);
}

void Braking_McuState(void)
{
	Braking_Set12VRelay(STD_HIGH);

	Braking_SetAbsPosRelay(STD_HIGH);
	Braking_SetAbsNegRelay(STD_HIGH);

	Braking_SetBlsRelay(STD_HIGH);
}

void Braking_SwitchState(void)
{
	if (CurrentState == MCU_STATE)
	{
		Braking_AbsState();
		CurrentState = ABS_STATE;
	}
	else
	{	
		Braking_McuState();
		CurrentState = MCU_STATE;
	}
}