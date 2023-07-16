/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Adc_Cfg.C
 *  DESCRIPTION:	C file for the ADC configuration for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../../MCAL/Inc/Adc.h"

#if (REGULAR_CHANNELS_NUMBER)

const Adc_ChannelConfigType ADC_REGULAR_CHANNELS[REGULAR_CHANNELS_NUMBER] =
{
	{ ADC_A_PIN_0, ADC_SAMPLING_1},
};

const Adc_ChannelConfigType* ADC_REGULAR_CHANNELS_PTR = ADC_REGULAR_CHANNELS;

#else

Adc_ChannelConfigType *ADC_REGULAR_CHANNELS;

#endif

#if (INJECTED_CHANNELS_NUMBER)

const Adc_ChannelConfigType ADC_INJECTED_CHANNELS[INJECTED_CHANNELS_NUMBER] =
{
	{ ADC_A_PIN_3, ADC_SAMPLING_1},
};

const Adc_ChannelConfigType* ADC_INJECTEDD_CHANNELS_PTR = ADC_INJECTED_CHANNELS;

#else

Adc_ChannelConfigType *ADC_INJECTED_CHANNELS;

#endif

const Adc_GroupConfigType GroupsConfiguration[2] = 
{
	{ADC_REGULAR, ADC_REGULAR_CHANNELS, ADC_TRIGG_SRC_SW, ADC_TRIGGER_NONE},
	{ADC_INJECTED, ADC_INJECTED_CHANNELS, ADC_TRIGG_SRC_HW, ADC_TRIGGER_EXTI_11},
};

const Adc_GroupConfigType* ADC_GROUPS_CONFIG_PTR = GroupsConfiguration;


const Adc_ConfigType Adc_Configuration = 
{
	{ADC_PRESCALER_2, ADC_CONV_MODE_ONESHOT, 12, ADC_ALIGN_RIGHT, GroupsConfiguration}
};