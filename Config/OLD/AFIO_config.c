/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			AFIO_confi.c
 *  DESCRIPTION:	C file for the configuration AFIO peripheral
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "AFIO_config.h"

#if (USED_AFIO)
AFIO_Config_t AFIO_Configuration[USED_AFIO] = 
{
	{SPI, MAP_0},
	{USART, MAP_1},
	{EXT_INT, MAP_5}
}

#else

AFIO_Config_t *AFIO_Configuration;

#endif

/** END OF FILE: AFIO_config.c
  *****************************************************/