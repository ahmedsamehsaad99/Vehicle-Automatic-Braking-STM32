/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			BrakingCom.h
 *  DESCRIPTION:	Header file for the Braking Communication Handling
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef BRAKING_COM_H
#define BRAKING_COM_H

#include "../../Service/Inc/Com.h"

/* CHOOSE: PROTOCOL_UART -- PROTOCOL_CAN */
#define BRAKING_USED_COM_PROTOCOL	PROTOCOL_UART

typedef Com_MsgType Braking_MsgType;

typedef float32 Braking_DistanceType;

typedef uint8	Braking_VehicleSpeedType;

typedef enum
{
	BRAKING_OBJECT_CAR=1, BRAKING_OBJECT_MOTORCYCLE, BRAKING_OBJECT_PEDESTRIAN, BRAKING_OBJECT_SPEED
} Braking_ObjectType;

void Braking_ReadMsg(void);
void Braking_GetObject(Braking_ObjectType *Object);
void Braking_GetCurrentSpeed(Braking_VehicleSpeedType *VehicleSpeed);
void Braking_GetDistance(Braking_DistanceType *Distance);

#endif