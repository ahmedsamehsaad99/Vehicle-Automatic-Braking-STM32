/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			GPIO_config.c
 *  DESCRIPTION:	C file for the GPIO config for STM32F103
 *****************************************************************************/

#include "GPIO_config.h"

#if (USED_PINS)

GPIO_Config_t GPIO_Configuration[USED_PINS] =
{
	{PINB_5, INPUT, PULL},
	{PINB_6, OUTPUT, NONE}
};

#else

GPIO_Config_t *GPIO_Configurtion;

#endif


  /** END OF FILE: GPIO_config.c
   *****************************************************/