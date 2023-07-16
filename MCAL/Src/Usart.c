/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Usart.c
 *  DESCRIPTION:	C file for the USART driver for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../Inc/Usart.h"

static uint8 DATA_RECEPTION_FLAG = 0;
volatile Usart_DataType ReceivedData = 0;

static uint32 Usart_GetBrrValue(Usart_BaudrateType Baudrate)
{
	float32 USARTDIV = (F_CPU) / (16.0 * Baudrate);
	uint16 Mantissa = (uint16) USARTDIV;
	uint16 Fraction = round(16.0 * (USARTDIV * 1.0 - Mantissa));

	if (Fraction == 16)
	{
		Fraction = 0;
		Mantissa++;
	}

	return ((Mantissa << 4) + Fraction);
}

void Usart_Init(const Usart_ConfigType* ConfigPtr)
{
	/* SET CLOCK */

	setBitState(REG(RCC_BASE, RCC_APB1ENR), 18, STD_HIGH);	/* Enable USART3 */
	setBitState(REG(RCC_BASE, RCC_APB2ENR), 14, STD_HIGH);
	uint8 i = 0;
	uint32 USART_BASE = 0;

	for (i = 0; i < 2; i++)
	{
		if (ConfigPtr[i].ContNumber == USART_1)
			USART_BASE = USART1_BASE;
		else if (ConfigPtr[i].ContNumber == USART_3)
			USART_BASE = USART3_BASE;

		/* ENABLE USART */
		setBitState(REG(USART_BASE, USART_CR1), 13, STD_HIGH);

		/* SET DATA BITS NUMBER */
		setBitState(REG(USART_BASE, USART_CR1), 12, (ConfigPtr[i].Databits - 1));

		/* SET STOP BITS */
		setValue(REG(USART_BASE, USART_CR2), 12, (ConfigPtr[i].Stopbits));

		/* SELECT BAUDRATE  */
		setValue(REG(USART_BASE, USART_BRR), 0, Usart_GetBrrValue(ConfigPtr[i].Baudrate));

		/* ENABLE TRANSMIT */
		setBitState(REG(USART_BASE, USART_CR1), 3, STD_HIGH);

		/* ENABLE RECEIVE  */
		setBitState(REG(USART_BASE, USART_CR1), 2, STD_HIGH);

		/* ENABLE INTERRUPTS */
		setBitState(REG(USART_BASE, USART_SR), 6, STD_LOW);

		//	setBitState(REG(USART_BASE, USART_CR1), 6, STD_HIGH);
		setBitState(REG(USART_BASE, USART_CR1), 5, STD_HIGH);
	}
}

void Usart_Transmit(Usart_ControllerNumber ContNumber, Usart_DataType Data)
{
	uint32 USART_BASE = 0;

	if (ContNumber == USART_1)
		USART_BASE = USART1_BASE;
	else if (ContNumber == USART_3)
		USART_BASE = USART3_BASE;

	while (! Usart_GetFlag(ContNumber, USART_TXE));
	/* FILL THE DATA REGISTER */
	REG(USART_BASE, USART_DR) = Data;
}

void Usart_TransmitString(Usart_ControllerNumber ContNumber, Usart_StringType String)
{
	uint32 USART_BASE = 0;

	if (ContNumber == USART_1)
		USART_BASE = USART1_BASE;
	else if (ContNumber == USART_3)
		USART_BASE = USART3_BASE;

	while (*String != '\0')
	{
		Usart_Transmit(ContNumber ,*String);
		String++;
	}
}

Usart_DataType Usart_Receive(Usart_ControllerNumber ContNumber)
{	
	uint32 USART_BASE = 0;

	if (ContNumber == USART_1)
		USART_BASE = USART1_BASE;
	else if (ContNumber == USART_3)
		USART_BASE = USART3_BASE;

	//while (! Usart_GetFlag(USART_RXNE) );
	if (DATA_RECEPTION_FLAG)
	{
		DATA_RECEPTION_FLAG = 0;
		ReceivedData = getValue(REG(USART_BASE, USART_DR), 0, 0xFF);
	}
	else
	{
		ReceivedData = 0;
	}

	return ReceivedData;
}

Std_ReturnType Usart_GetFlag(Usart_ControllerNumber ContNumber, Usart_FlagType Flag)
{
	uint32 USART_BASE = 0;

	if (ContNumber == USART_1)
		USART_BASE = USART1_BASE;
	else if (ContNumber == USART_3)
		USART_BASE = USART3_BASE;

	return (getBit(REG(USART_BASE, USART_SR), Flag));
}

void USART1_ISR()
{
//	DEBUG(d9, "((((INTERRUPT))))", 1, 2, 3);

	if (Usart_GetFlag(USART_1, USART_RXNE))
	{
		DATA_RECEPTION_FLAG = 1;
	}
}

void USART3_ISR()
{
					DEBUG(d2, "((((XXXXXXX))))", 1, 2, 3);

	if (Usart_GetFlag(USART_3, USART_RXNE))
	{
		DATA_RECEPTION_FLAG = 1;
	}
}

 /** END OF FILE: Usart.h
  *****************************************************/