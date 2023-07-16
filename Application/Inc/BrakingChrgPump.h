/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			BrakingChrgPump.h
 *  DESCRIPTION:	Header file for the Braking Charge Pump Handling
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef BRAKING_CHRG_PMP_H
#define BRAKING_CHRG_PMP_H

#include "BrakingPinout.h"
#include "../../MCAL/Inc/TIM2_interface.h"

#define CHRG_PUMP_SIGNAL_FREQ		15000

typedef uint8 Braking_PwmDutyCycleType;

void Braking_OutputDutyCycle(Braking_PwmDutyCycleType DutyCycle);


#endif