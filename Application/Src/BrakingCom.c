/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			BrakingCom.c
 *  DESCRIPTION:	C file for the Braking Communication Handling
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../Inc/BrakingCom.h"

Braking_MsgType ReceivedMsg;

void Braking_ReadMsg(void)
{
	//DEBUG(d4, "|||||||READ FUNCTION - NOTHING|||||||///", ReceivedMsg.Id, ReceivedMsg.Data, 3);

	Braking_MsgType Msg;
	
	Com_ReceiveMsg(BRAKING_USED_COM_PROTOCOL, &Msg);

	ReceivedMsg = Msg;
}

void Braking_GetObject(Braking_ObjectType *Object)
{
	if (ReceivedMsg.Id != BRAKING_OBJECT_SPEED)
		*Object = ReceivedMsg.Id;
}
void Braking_GetDistance(Braking_DistanceType *Distance)
{
	if (ReceivedMsg.Id != BRAKING_OBJECT_SPEED)
		*Distance = (Braking_DistanceType)ReceivedMsg.Data;
}

void Braking_GetCurrentSpeed(Braking_VehicleSpeedType *VehicleSpeed)
{	
	while (ReceivedMsg.Id != 0x4)
	{
			Braking_ReadMsg();
	}

	*VehicleSpeed = (Braking_VehicleSpeedType)ReceivedMsg.Data * 4;
	
	Usart_StringType test;
	sprintf(test, "----- RX SPEED: %d ------\n", *VehicleSpeed);
	Usart_TransmitString(USART_3, test);
	//DEBUG(d4, "AFTER SPEED: %d - %d///", *Object, *Distance, 3);

	//DEBUG(d2, "AFTER SPEED: %d%d///", ReceivedMsg.Id, ReceivedMsg.Data, 3);
}
