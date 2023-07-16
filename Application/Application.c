/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Application.c
 *  DESCRIPTION:	C file for the project for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "Application.h"

extern const Port_ConfigType Port_Configuration[];
extern const Adc_ConfigType Adc_Configuration[];
extern const Com_ConfigType Com_Configuration[];

void App_Init()
{
	Port_Init(Port_Configuration);
	IntCtrl_Init();
	Adc_Init(Adc_Configuration);
	Com_Init(Com_Configuration);
	MTIM2_voidInit();
}

void App_Start()
{

}