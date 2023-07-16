/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			AFIO.c
 *  DESCRIPTION:	C file for the AFIO peripheral
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "AFIO.h"
#include "../../Config/AFIO_config.h"

extern AFIO_Config_t AFIO_Configuration[];

void AFIO_Init(void)
{
	/* ENABLE CLOCK */
	setBitState(REG(RCC_BASE, RCC_APB2ENR), 0, HIGH);

	uint8_t i;

	for (i = 0; i < USED_AFIO; i++)
	{
		switch (AFIO_Configuration[i].thePeripheral)
		{
		case SPI:
			setBitState(REG(AFIO_BASE, AFIO_MAPR), 0, AFIO_Configuration[i].theMap);
			break;

		case USART:
			setBitState(REG(AFIO_BASE, AFIO_MAPR), 3, AFIO_Configuration[i].theMap);
			break;

		case EXT_INT:
			setBitState(REG(AFIO_BASE, AFIO_EXTICR1 + 0x04 * (AFIO_Configuration[i].theMap / 4)), (AFIO_Configuration[i].theMap % 4) * 4, AFIO_Configuration[i].thePort);
			break;
		}
	}
}

 /** END OF FILE: AFIO.c
  *****************************************************/