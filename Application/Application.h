/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Application.h
 *  DESCRIPTION:	Header file for the project for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef APP_H_
#define APP_H_

#include "../MCAL/Inc/Port.h"
#include "../MCAL/Inc/Dio.h"
#include "../MCAL/Inc/IntCtrl.h"
#include "../MCAL/Inc/Adc.h"
//#include "../MCAL/Inc/Usart.h"
//#include "../MCAL/Inc/Can.h"
#include "../MCAL/Inc/TIM2_interface.h"
#include "../Config/MCAL/Inc/TIM2_config.h"

#include "../HAL/Inc/Relay.h"
#include "../Service/Inc/Com.h"

#define DEBUGGING_MODE		1
#define PROTEUS_SIMULATION	1

void App_Init(void);
void Brake_MapDutyCycleToDistance(void);
void Brake_ReturnToOriginal(void);
void Brake_ActivateBraking(void);

#endif