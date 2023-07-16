/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Com.c
 *  DESCRIPTION:	C file for the Communication Service
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../Inc/Com.h"

extern const Usart_ConfigType Usart_Configuration;
//extern const Can_ConfigType Can_Configuration;

void Com_Init(const Com_ConfigType *ConfigPtr)
{
	uint8 i = 0;

	for (; i < COM_PROTOCOLS_USED; i++)
	{
		switch (ConfigPtr->Protocol)
		{
		case PROTOCOL_UART:
			Usart_Init(&Usart_Configuration);
			break;

		case PROTOCOL_CAN:
			//Can_Init(&Can_Configuration);
			break;
		}

	}
}


void Com_SendMsg(Com_ProtocolType Protocol, Com_MsgType* Message)
{
	switch (Protocol)
	{
	case PROTOCOL_UART:
		uint8 IdBits = 8 - Message->DataLength;
		Usart_Transmit(USART_1, (Message->Id << IdBits | (Message->Data) ) );
		break;

	case PROTOCOL_CAN:
		Can_PduType TxPdu;
		TxPdu.id = Message->Id;
		TxPdu.sdu = Message->Data;
		TxPdu.length = (Message->DataLength) / 8;
		
		//Can_Write(CAN_MAILBOX_0, &TxPdu)
		//Can_Init(&Can_Configuration);
		break;
	}
}

void Com_ReceiveMsg(Com_ProtocolType Protocol, Com_MsgType *MsgToReturn)
{
	Com_MsgType RxMsg;

	switch (Protocol)
	{
	case PROTOCOL_UART:
		Usart_DataType Usart_RxData = Usart_Receive(USART_1);
		RxMsg.Data = Usart_RxData & 0x0F;
		RxMsg.DataLength = 8;
		RxMsg.Id = (Usart_RxData & 0xF0) >> 4;
		break;

	case PROTOCOL_CAN:
		//Can_Write(CAN_MAILBOX_0, &TxPdu)
		//Can_Init(&Can_Configuration);
		break;
	}

	*MsgToReturn = RxMsg;
}
