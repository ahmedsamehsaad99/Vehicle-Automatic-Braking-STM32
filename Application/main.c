/******************************************************************************
 *  FILE DESCRIPTION
 *  FILE:			MAIN.c
 *  DESCRIPTION:	MAIN FILE
 *****************************************************************************/

#include "Application.h"
#include "Inc/BrakingLogic.h"

#define USE_CAN 0
#define USE_UART 1


int main(void)
{
	App_Init();

	while (1)
	{			
		Braking_Logic();
	}
}