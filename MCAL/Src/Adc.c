/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Adc.C
 *  DESCRIPTION:	C file for the ADC for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../Inc/Adc.h"

static Adc_ValueGroupType RegularData = 0;
static Adc_ValueGroupType InjectedData = 0;

void Adc_Init(const Adc_ConfigType *ConfigPtr)
{
	/* ENABLE CLOCK */
	setBitState(REG(RCC_BASE, RCC_APB2ENR), 9, STD_HIGH);

	/* SET PRESCALER */
	setValue(REG(RCC_BASE, RCC_CFGR), 14, ConfigPtr->Prescaler);

	uint8 i = 0;
	uint8 j = 0;
	
	extern const Adc_GroupConfigType* ADC_GROUPS_CONFIG_PTR;
	
	for (i = 0; i < 2; i++) // LOOP THROUGH 2 GROUPS
	{
		Adc_EnableGroupNotification(ADC_GROUPS_CONFIG_PTR[i].Group);

		/* SET TRIGGER SOURCE */
		switch (ADC_GROUPS_CONFIG_PTR[i].Group)
		{
		case ADC_REGULAR:
			if (ADC_GROUPS_CONFIG_PTR[i].Trigger == ADC_TRIGG_SRC_HW)
			{
				setBitState(REG(ADC1_BASE, ADC_CR2), 20, STD_HIGH);	/* ENABLE EXTERNAL TRIGGER */
				setValue(REG(ADC1_BASE, ADC_CR2), 17, ADC_GROUPS_CONFIG_PTR[i].Ext_Trigger);	/* SELECT THE EXTERNAL TRIGGER */
			}
			
			/* SET CHANNELS LENGTH */
			setValue(REG(ADC1_BASE, ADC_SQR1), 20, REGULAR_CHANNELS_NUMBER - 1);

			for (j = 0; j < REGULAR_CHANNELS_NUMBER; j++)
			{				
				Adc_ChannelType CurrentChannel = ADC_GROUPS_CONFIG_PTR[i].ChannelList[j].Channel;

				/* SET CHANNELS */
				setValue(REG(ADC1_BASE, ADC_SQR3), (j * 5), CurrentChannel);

				/* START CONVERSION */
				setBitState(REG(ADC1_BASE, ADC_CR2), 22, STD_HIGH);

				/* SET SAMPLING TIME */
				setValue(REG(ADC1_BASE, ADC_SMPR2), CurrentChannel * 3, ADC_GROUPS_CONFIG_PTR[i].ChannelList[j].SamplingTime);
			}

			break;

		case ADC_INJECTED:
			if (ADC_GROUPS_CONFIG_PTR[i].Trigger == ADC_TRIGG_SRC_HW)
			{
				setBitState(REG(ADC1_BASE, ADC_CR2), 15, STD_HIGH);
				setValue(REG(ADC1_BASE, ADC_CR2), 12, ADC_GROUPS_CONFIG_PTR[i].Ext_Trigger);
			}

			setValue(REG(ADC1_BASE, ADC_JSQR), 20, (INJECTED_CHANNELS_NUMBER - 1));

			j = 0; 
			uint8 k = 15;
			for (j = 0; j < INJECTED_CHANNELS_NUMBER; j++, k -= 5)
			{
				Adc_ChannelType CurrentChannel = ADC_GROUPS_CONFIG_PTR[i].ChannelList[j].Channel;

				/* SET CHANNELS */
				setValue(REG(ADC1_BASE, ADC_JSQR), k, CurrentChannel);

				/* START CONVERSION */
				setBitState(REG(ADC1_BASE, ADC_CR2), 21, STD_HIGH);
				
				/* SET SAMPLING TIME */
				setValue(REG(ADC1_BASE, ADC_SMPR2), CurrentChannel * 3, ADC_GROUPS_CONFIG_PTR[i].ChannelList[j].SamplingTime);
			}

			break;
		}
	}
		/* SET CONVERSION MODE */
	setBitState(REG(ADC1_BASE, ADC_CR2), 1, ConfigPtr->ConversionMode);

	/* SET DATA ALIGNMENT MODE */
	setBitState(REG(ADC1_BASE, ADC_CR2), 11, ConfigPtr->Alignment);
	
		/* EHABLE ADC */
	setBitState(REG(ADC1_BASE, ADC_CR2), 0, STD_HIGH);
}

void Adc_DeInit(void)
{
	setBitState(REG(ADC1_BASE, ADC_CR2), 0, STD_LOW);
}	

Std_ReturnType Adc_GetFlag(Adc_FlagType Flag)
{
	return (getBit(REG(ADC1_BASE, ADC_SR), Flag));
}

void Adc_ClearFlag(Adc_FlagType Flag)
{
	setBitState(REG(ADC1_BASE, ADC_SR), Flag, STD_LOW);
}

void Adc_StartGroupConversion(Adc_GroupType Group)
{
	switch (Group)
	{
	case ADC_REGULAR:
		setBitState(REG(ADC1_BASE, ADC_CR2), 22, STD_HIGH);
		break;
	case ADC_INJECTED:
		setBitState(REG(ADC1_BASE, ADC_CR2), 21, STD_HIGH);
		break;
	}
}

void Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType* DataBufferPtr)
{
	Adc_ValueGroupType Data = 0;

	Adc_StartGroupConversion(Group);

	switch (Group)
	{
	case ADC_REGULAR:
		Data = RegularData;
		break;
	case ADC_INJECTED:
		Data = InjectedData;
		break;
	}

	*DataBufferPtr = Data;
}

void Adc_EnableHardwareTrigger(Adc_GroupType Group);
void Adc_DisableHardwareTrigger(Adc_GroupType Group);

void Adc_EnableGroupNotification(Adc_GroupType Group)
{
	switch (Group)
		{
		case ADC_REGULAR:
			setBitState(REG(ADC1_BASE, ADC_CR1), 5, STD_HIGH);	/* ENABLE EOC INTR  */
			break;
		case ADC_INJECTED:
			setBitState(REG(ADC1_BASE, ADC_CR1), 7, STD_HIGH);	/* ENABLE JEOC INTR  */
			break;
		}
}

void Adc_DisableGroupNotification(Adc_GroupType Group)
{
	switch (Group)
	{
	case ADC_REGULAR:
		setBitState(REG(ADC1_BASE, ADC_CR1), 5, STD_LOW);	/* DISABLE EOC INTR  */			
		break;
	case ADC_INJECTED:
		setBitState(REG(ADC1_BASE, ADC_CR1), 7, STD_LOW);	/* DISABLE JEOC INTR  */
		break;
	}
}

void ADC_ISR()
{
	if (Adc_GetFlag(ADC_EOC_FLAG))
		RegularData = getValue(REG(ADC1_BASE, ADC_DR), 0, 0xFFFF);
	else if (Adc_GetFlag(ADC_JEOC_FLAG))
		InjectedData = getValue(REG(ADC1_BASE, ADC_DR), 0, 0xFFFF);
}
