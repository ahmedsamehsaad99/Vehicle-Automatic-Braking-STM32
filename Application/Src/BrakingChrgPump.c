/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			BrakingChrgPump.c
 *  DESCRIPTION:	C file for the Braking Charge Pump Handling
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../Inc/BrakingChrgPump.h"

void Braking_OutputDutyCycle(Braking_PwmDutyCycleType DutyCycle)
{
	MTIM2_voidOutputPWM(CHRG_PUMP_SIGNAL_FREQ, DutyCycle);
}