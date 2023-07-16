/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Adc.h
 *  DESCRIPTION:	Header file for the Adc driver for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef ADC_H_
#define ADC_H_

#include "../../Common/Registers.h"
#include "../../Common/Std_Types.h"
#include "../../Config/MCAL/Inc/Adc_Cfg.h"

 /** TYPEDEFS
 *****************************************************/
typedef enum
{
	ADC_A_PIN_0,
	ADC_A_PIN_1,
	ADC_A_PIN_2,
	ADC_A_PIN_3,
	ADC_A_PIN_4,
	ADC_A_PIN_5,
	ADC_A_PIN_6,
	ADC_A_PIN_7,
	ADC_B_PIN_0,
	ADC_B_PIN_1
}Adc_ChannelType;

typedef enum 
{
	ADC_REGULAR, ADC_INJECTED
}Adc_GroupType;

typedef sint32 Adc_ValueGroupType;

typedef enum 
{
	ADC_PRESCALER_2,
	ADC_PRESCALER_4,
	ADC_PRESCALER_6,
	ADC_PRESCALER_8,
} Adc_PrescaleType;

typedef uint8 Adc_ConversionTimeType;

typedef enum
{
	ADC_SAMPLING_1,
	ADC_SAMPLING_7,
	ADC_SAMPLING_13,
	ADC_SAMPLING_28,
	ADC_SAMPLING_41,
	ADC_SAMPLING_55,
	ADC_SAMPLING_71,
	ADC_SAMPLING_239,
} Adc_SamplingTimeType;


typedef uint8 Adc_ResolutionType;


typedef enum
{
	ADC_IDLE, ADC_BUSY, ADC_COMPLETED, ADC_STREAM_COMPLETED
}Adc_StatusType;

typedef enum
{
	ADC_TRIGG_SRC_SW, ADC_TRIGG_SRC_HW
}Adc_TriggerSourceType;

typedef enum
{
	ADC_CONV_MODE_ONESHOT, ADC_CONV_MODE_CONTINUOUS
} Adc_GroupConvModeType;

typedef enum
{
	ADC_TRIGGER_NONE = -1,
	/* REGULAR GROUPS */
	ADC_TRIGGER_TIMER1_CC1,
	ADC_TRIGGER_TIMER1_CC2,
	ADC_TRIGGER_TIMER1_CC3,
	ADC_TRIGGER_TIMER2_CC2,
	ADC_TRIGGER_TIMER3_TRGO,
	ADC_TRIGGER_TIMER4_CC4,
	ADC_TRIGGER_EXTI_11,
	ADC_TRIGGER_SWSTART,

	/* INJECTED GROUPS */
	ADC_TRIGGER_TIMER1_TRGO = 0,
	ADC_TRIGGER_TIMER1_CC4,
	ADC_TRIGGER_TIMER2_TRGO,
	ADC_TRIGGER_TIMER2_CC1,
	ADC_TRIGGER_TIMER3_CC4,
	ADC_TRIGGER_TIMER4_TRGO,
	ADC_TRIGGER_EXTI_15,
	ADC_TRIGGER_JSWSTART,
} Adc_ExternalTriggerType;

typedef enum
{
	ADC_ALIGN_RIGHT, ADC_ALIGN_LEFT
} Adc_ResultAlignmentType;

typedef struct
{
	Adc_ChannelType			Channel;
	Adc_SamplingTimeType	SamplingTime;
} Adc_ChannelConfigType;

typedef struct
{
	Adc_GroupType Group;
	Adc_ChannelConfigType	*ChannelList;
	Adc_TriggerSourceType Trigger;
	Adc_ExternalTriggerType Ext_Trigger;
} Adc_GroupConfigType;

typedef struct
{
	Adc_PrescaleType		Prescaler;
	Adc_GroupConvModeType	ConversionMode;
	Adc_ResolutionType		Resolution;
	Adc_ResultAlignmentType	Alignment;
	Adc_GroupConfigType	GroupConfig[2];
} Adc_ConfigType;

typedef enum 
{
	ADC_AWD_FLAG, ADC_EOC_FLAG, ADC_JEOC_FLAG, ADC_JSTRT_FLAG, ADC_STRT_FLAG
} Adc_FlagType;

/** FUNCTIONS PROTOTYPES
*****************************************************/
void Adc_Init(const Adc_ConfigType *ConfigPtr);
void Adc_DeInit(void);
Std_ReturnType Adc_GetFlag(Adc_FlagType Flag);
void Adc_ClearFlag(Adc_FlagType Flag);
void Adc_StartGroupConversion(Adc_GroupType Group);
void Adc_StopGroupConversion(Adc_GroupType Group);
void Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr);
Adc_ValueGroupType Adc_Read(Adc_GroupType Group);
void Adc_EnableHardwareTrigger(Adc_GroupType Group);
void Adc_DisableHardwareTrigger(Adc_GroupType Group);
void Adc_EnableGroupNotification(Adc_GroupType Group);
void Adc_DisableGroupNotification(Adc_GroupType Group);

// enable clock: from RCC_APB2ENR -- to set prescaler: ADCPRE bit in (RCC_CFGR)
// ADON --> ADC_CR2
// SWSTART IN ADC_CR2 TO START CONVERSION USING SOFTWARE
// Set mode: if ONESHOT, set CONT to 0.
// Data received is @ ADC_DR if regular, @ ADC_JDR if injected. 
// EOCIE to enable interrupt
// INJECTED DEPENDS on external trigger, cant be set on continuous
// if cont, set CONT to 1 (in ADC_CR2)
// // Select the number of conversions in ADC_SQR1, and set the channel number 16 first
// if multichannel, set SCAN to 1 in CR1
// EOCS: 0 for all conversions, 1 for 1 by 1 conversion: flag conversion
// Sampling time: ADC_SMPR1/2
// Resolution:CR1,	RES bits

// To enable external trigger: EXTEN or JEXTEN in ADC_CR2 -- Select the trigger using EXTSEL or JEXTSEL

/*
Configurations:
Sampling time
Resolution
HW or SW triggered
if HW: RISING/FALLING
MODE (ONESHOT, CONT)

Group -> Channels -> 

ChannelConfigType -> Pins of the channels
GroupConfigType: Number of channels and which channels
A: 0-7 B: 0-1

*/


#endif

/** END OF FILE: Adc.h
 *****************************************************/


