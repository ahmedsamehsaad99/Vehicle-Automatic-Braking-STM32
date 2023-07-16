/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Can.h
 *  DESCRIPTION:	Header file for the CAN driver for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef CAN_H
#define CAN_H

#include "../../Common/Registers.h"
#include "../../Common/Std_Types.h"
#include "../../Config/MCAL/Inc/Can_Cfg.h"

 /** TYPEDEFS
 *****************************************************/

#define CAN_MAIN_CONTROLLER		0

typedef enum
{
	CAN_AUTO_TX_ENABLE, CAN_AUTO_TX_DISABLE
} Can_AutoTxType;

typedef enum
{
	CAN_TX_PRIORITY_ID, CAN_TX_PRIORITY_RQ
} Can_TxPriorityType;

typedef enum
{
	CAN_TEST_MODE_NORMAL, CAN_TEST_MODE_SILENT, CAN_TEST_MODE_LOOPBACK, CAN_TEST_MODE_COMBINED
} Can_TestModeType;

typedef enum
{
	CAN_INTR_DISABLE, CAN_INTR_ENABLE
} Can_IntrEnableType;

typedef enum
{
	 CAN_RXMODE_MASK, CAN_RXMODE_ID
} Can_RxIdModeType;

typedef enum
{
	CAN_FILTER_16BIT, CAN_FILTER_32BIT
} Can_FilterScaleType;

typedef struct
{
	Can_AutoTxType AutoTransmission;
	Can_TxPriorityType TxPriority;
	Can_TestModeType Mode;
	Can_IntrEnableType IntrEnable;
	Can_RxIdModeType IdMode;
	Can_FilterScaleType FilterScale;
} Can_ConfigType;

typedef enum
{
	CAN_MAILBOX_0, CAN_MAILBOX_1, CAN_MAILBOX_2
} Can_MailBoxType;

typedef uint32 Can_IdType;

typedef struct
{
	uint64* sdu;
	Can_IdType id;
	uint8 length;
} Can_PduType; /* FRAME */


typedef enum
{
	CAN_T_START,
	CAN_T_STOP,
	CAN_T_SLEEP,
	CAN_T_WAKEUP
} Can_StateTransitionType;

typedef enum
{
	CAN_OK,
	CAN_NOT_OK,
	CAN_BUSY
} Can_ReturnType;

 /** FUNCTIONS PROTOTYPES
 *****************************************************/
void Can_Init(const Can_ConfigType* ConfigPtr);
Can_ReturnType Can_SetControllerMode(uint8 Controller, Can_StateTransitionType Transition);
void Can_DisableControllerInterrupts(uint8 Controller);
void Can_EnableControllerInterrupts(uint8 Controller);
Can_ReturnType Can_Write(uint8 Hth, const Can_PduType* PduInfo);
void Can_MainFunctionRead(void);



#endif
 /** END OF FILE: Can.h
  *****************************************************/