/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Com_Cfg.C
 *  DESCRIPTION:	C file for the COM configuration
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../../../Service/Inc/Com.h"

#if COM_PROTOCOLS_USED

const Com_ConfigType Com_Configuration[COM_PROTOCOLS_USED] =
{
	PROTOCOL_UART, PROTOCOL_CAN
};

#else

#endif