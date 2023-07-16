/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Gpt.h
 *  DESCRIPTION:	Header file for the GPT for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef GPT_H
#define GPT_H

#include "../../Common/Std_Types.h"
#include "../../Common/Registers.h"
#include "../../Config/MCAL/Inc/Gpt_Cfg.h"

 /** TYPEDEFS
 *****************************************************/

typedef enum
{
	GPT_TIMER_1,
	GPT_TIMER_2,
	GPT_TIMER_3,
	GPT_TIMER_4,
	GPT_TIMER_5,
	GPT_TIMER_6
} Gpt_ChannelType;

typedef uint32 Gpt_ValueType;

typedef enum
{
	GPT_MODE_NORMAL, GPT_MODE_SLEEP
} Gpt_ModeType;

typedef enum
{
	GPT_PREDEF_TIMER_1US_16BIT, 
	GPT_PREDEF_TIMER_1US_24BIT, 
	GPT_PREDEF_TIMER_1US_32BIT, 
	GPT_PREDEF_TIMER_100US_32BIT, 
} Gpt_PredefTimerType;

typedef struct
{

} Gpt_ConfigType;

 /** FUNCTIONS PROTOTYPES
 *****************************************************/
void Gpt_Init(Gpt_ConfigType* ConfigPtr);
void Gpt_DeInit(void);
Gpt_ValueType Gpt_GetTimeElapsed(Gpt_ChannelType Channel);		/* RETURNS NUMBER OF TICKS */
Gpt_ValueType Gpt_GetTimeRemaining(Gpt_ChannelType Channel);	/* RETURNS NUMBER OF TICKS */
void Gpt_StartTimer(Gpt_ChannelType Channel, Gpt_ValueType Value);
void Gpt_StopTimer(Gpt_ChannelType Channel);
void Gpt_EnableNotification(Gpt_ChannelType Channel);
void Gpt_DisableNotification(Gpt_ChannelType Channel);
void Gpt_GetPredefTimerValue(Gpt_PredefTimerType PredefTimer, uint32* TimeValuePtr);


#endif

 /** END OF FILE: Gpt.h
  *****************************************************/