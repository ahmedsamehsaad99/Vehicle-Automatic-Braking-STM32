/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			BrakingLogic.c
 *  DESCRIPTION:	C file for the Braking Logic
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../Inc/BrakingLogic.h"
#include "../../MCAL/Inc/Usart.h"
#include <stdio.h>
#include <string.h>

Braking_FlagType CurrentState = ABS_STATE;

void Braking_MapDistanceToDutyCycle(Braking_DistanceType Distance, Braking_VehicleSpeedType CurrentSpeed, Braking_PwmDutyCycleType *DutyCycle)
{
		if (CurrentSpeed <= VEHICLE_FINAL_SPEED)
		{
			*DutyCycle = 0;
			return;
		}
		
		static const Braking_PwmDutyCycleType DutyCycleArr[] =
		{ 100,	96,		92,		88,		81,		73,		67,		58,		48,		29,		9 };

		static const Braking_AccelerationType AccelrArr[] =
		{ -20,	-18,	-16,	-14,	-12,	-10,	-8,		-6,		-4,		-2,		-1 };

		Braking_PwmDutyCycleType DutyCycleToReturn = 0;
	uint8 i = 0;

	Braking_AccelerationType CalculatedAccel = ((SQUARE(KMH_TO_MPS(VEHICLE_FINAL_SPEED))) - (SQUARE(KMH_TO_MPS(CurrentSpeed * 1.0)))) / (2.0 * Distance);
	
	for (; i < 10; i++)
	{
		if (CalculatedAccel <= AccelrArr[0])
		{
			DutyCycleToReturn = DutyCycleArr[0];
			break;
		}
		else if (CalculatedAccel <= AccelrArr[i] && CalculatedAccel > AccelrArr[i-1])
		{
			DutyCycleToReturn = DutyCycleArr[i];
			break;
		}
	}

	*DutyCycle = DutyCycleToReturn;
}

void Braking_NameObjectId(Braking_ObjectType ObjectId, Braking_ObjectNameType *ObjectName)
{
	Braking_ObjectNameType ObjectNames[3][11] = {"Car", "Motorcycle", "Pedestrian"};
	
	strcpy(ObjectName, ObjectNames[ObjectId-1]);
}

void Braking_Logic(void)
{
	Braking_DistanceType DistanceToLeadObject = 0;
	Braking_ObjectType LeadObject = 0;
	Braking_VehicleSpeedType CurrentSpeed = 0;
	Braking_PwmDutyCycleType DutyCycleToOutput = 0;
	Braking_ObjectNameType ObjectName[11];

	//Usart_StringType test;
	
	Braking_ReadMsg();

	Braking_GetObject(&LeadObject);
	Braking_GetDistance(&DistanceToLeadObject);

	Braking_NameObjectId(LeadObject, ObjectName);

	
	if (DistanceToLeadObject <= MIN_DISTANCE_TO_BREAK && DistanceToLeadObject > 0)
	{

		Braking_McuState();

		CurrentSpeed = 50;
		Braking_GetCurrentSpeed(&CurrentSpeed);

		Braking_MapDistanceToDutyCycle(DistanceToLeadObject, CurrentSpeed, &DutyCycleToOutput);
		
		//sprintf(test, "DISTANCE <= 15: Distance = %.2f | Object = %s | Speed = %d | DutyCycle = %d||||||||||||||||||||||\n", DistanceToLeadObject, ObjectName, CurrentSpeed, DutyCycleToOutput);
		//Usart_TransmitString(USART_3, test);
		
		Com_MsgType DutyCycleSent = {0xE, 4, round(DutyCycleToOutput * 1.0 / 10.0)};
		Com_SendMsg(PROTOCOL_UART, &DutyCycleSent);

		Braking_OutputDutyCycle(DutyCycleToOutput);

	}
	else if (DistanceToLeadObject > 15)
	{
		Braking_OutputDutyCycle(0);
		//sprintf(test, " STATE2: DISTANCE IS %.2f m - LeadObject is %d kmh\t\t", Distance, LeadObject);
		//Usart_TransmitString(USART_3, test);	
		Braking_AbsState();
	}
}

void Braking_StartApp(void)
{

}