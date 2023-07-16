/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			AFIO.h
 *  DESCRIPTION:	Header file for the AFIO peripheral
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef AFIO_H_
#define AFIO_H_

#include "../../Common/Registers.h"
#include "../../Common/Std_types.h"

typedef enum
{
	SPI, USART, EXT_INT
} AFIO_Peripheral_t;

typedef enum
{
	MAP_0, MAP_1, MAP_2, MAP_3, MAP_4, MAP_5, MAP_6, MAP_7, 
	MAP_8, MAP_9, MAP_10, MAP_11, MAP_12, MAP_13, MAP_14, MAP_15
} AFIO_Remap_t;

typedef enum
{
	PORTA, PORTB, NONE
}AFIO_ExtIntPort_t;

typedef struct
{
	AFIO_Peripheral_t thePeripheral;
	AFIO_Remap_t theMap;
	AFIO_ExtIntPort_t thePort;
} AFIO_Config_t;

void AFIO_Init(void);

#endif

 /** END OF FILE: AFIO.h
  *****************************************************/