/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Can_Cfg.C
 *  DESCRIPTION:	C file for the Can configuration for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include"../../MCAL/Inc/Can.h"

#if (CAN_ENABLE)

const Can_ConfigType Can_Configuration = 
{
	CAN_AUTO_TX_ENABLE, CAN_TX_PRIORITY_ID, CAN_TEST_MODE_NORMAL, CAN_INTR_DISABLE, CAN_RXMODE_ID, CAN_FILTER_16BIT
};

const Can_IdType Can_AcceptedFilters[CAN_ACCEPTED_IDS_NUMBER] =
{
	0x03,
	/*0x04,
	0x0E,
	0x0A,
	0x0B,
	0x100,
	0x40,*/
};

#else

const Can_ConfigType* Can_Configuration;

#endif