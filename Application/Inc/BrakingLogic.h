/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			BrakingLogic.h
 *  DESCRIPTION:	Header file for the Braking Logic
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef BRAKING_LOGIC_H
#define BRAKING_LOGIC_H

#include "../Inc/BrakingChrgPump.h"
#include "../Inc/BrakingCom.h"
#include "../Inc/BrakingStates.h"


#define VEHICLE_INITIAL_SPEED	60.0	/* REPLACED BY THE SPEED RETURNED FROM CARLA SIMULATOR */
#define VEHICLE_FINAL_SPEED		10.0

#define KMH_TO_MPS(SPEED)		(SPEED * 5 / 18.0)
#define SQUARE(VAL)				(VAL * VAL * 1.0)

#define MIN_DISTANCE_TO_BREAK	15

typedef float32	Braking_AccelerationType;
typedef uint8	Braking_VehicleSpeedType;
typedef uint8 Braking_ObjectNameType;

void Braking_NameObjectId(Braking_ObjectType ObjectId, Braking_ObjectNameType *ObjectName);
void Braking_MapDistanceToDutyCycle(Braking_DistanceType Distance, Braking_VehicleSpeedType CurrentSpeed, Braking_PwmDutyCycleType *DutyCycle);
void Braking_Logic(void);
void Braking_StartApp(void);


#endif