/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Can.c
 *  DESCRIPTION:	C file for the CAN driver for STM32F103C8
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#include "../Inc/Can.h"
#include "../Inc/Usart.h"

extern const Can_IdType Can_AcceptedFilters[CAN_ACCEPTED_IDS_NUMBER];

void Can_Init(const Can_ConfigType* ConfigPtr)
{
	/* ENABLE CLOCK */
	setBitState(REG(RCC_BASE, RCC_APB1ENR), 25, STD_HIGH);

	/* RESET THE PERIPHERAL */
	setBitState(REG(RCC_BASE, RCC_APB1RSTR), 25, STD_HIGH);
	setBitState(REG(RCC_BASE, RCC_APB1RSTR), 25, STD_LOW);

	/* ENTER INTIALIZATION MODE */
	setBitState(REG(CAN1_BASE, CAN_MCR), 1, STD_LOW); /* SET SLEEP BIT TO ZERO */
	setBitState(REG(CAN1_BASE, CAN_MCR), 0, STD_HIGH);

	/* SET AUTOTRANSMISSION */
	setBitState(REG(CAN1_BASE, CAN_MCR), 4, ConfigPtr->AutoTransmission);

	/* SET TX PRIORITY */
	setBitState(REG(CAN1_BASE, CAN_MCR), 2, ConfigPtr->TxPriority);

	/* INTERRUPTS ENABLE */
	//if (ConfigPtr->IntrEnable)
		//Can_EnableControllerInterrupts(CAN_MAIN_CONTROLLER);

	/* SET CAN MODE */
	switch (ConfigPtr->Mode)
	{
	case CAN_TEST_MODE_SILENT:
		setBitState(REG(CAN1_BASE, CAN_BTR), 31, STD_HIGH);
		break;
	case CAN_TEST_MODE_LOOPBACK:
		setBitState(REG(CAN1_BASE, CAN_BTR), 30, STD_HIGH);
		break;
	case CAN_TEST_MODE_COMBINED:
		setBitState(REG(CAN1_BASE, CAN_BTR), 30, STD_HIGH);
		setBitState(REG(CAN1_BASE, CAN_BTR), 31, STD_HIGH);
		break;
	case CAN_TEST_MODE_NORMAL:
		setBitState(REG(CAN1_BASE, CAN_BTR), 30, STD_LOW);
		setBitState(REG(CAN1_BASE, CAN_BTR), 31, STD_LOW);
		break;
	}
	/*
CAN RECEPTION LOGIC:
- RF0R: FMP0 BITS TO DETECT HOW MANY MESSAGES ARE PENDING - 1 FIFO = 3 MESSSAGES
- RF0R: RFOM0 BITS TO CLEAR THE MAILBOX
- DATA RECEIVED IS STORED IN: CAN_RDLXR - RDHXR
- IDENTIFIER OF THE DATA RECEIVED IS STORED IN CAN_RIXR

- For filters:
- 1. Set FINIT in FMR before.
- 2. Set identifier mode in CAN_FM1R
- 3. Set scale in FS1R
- 4. Set filter as active in FA1R
- 5. Received ID is @ CAN_RDTXR
- 6. Received data is @ RDLxR and RDHxR
*/


	/* INITIALIZE FILTERS RECEPTION */
	setBitState(REG(CAN1_BASE, CAN_FMR), 0, STD_HIGH);

	/* SET IDENTIFIER MODE FOR ALL FILTER BANKS */
	setValue(REG(CAN1_BASE, CAN_FM1R), 0, (/*ConfigPtr->IdMode*/0 * 0x1FFF));

	/* SET FILTER BANK SCALE */
	setValue(REG(CAN1_BASE, CAN_FS1R), 0, (ConfigPtr->FilterScale * 0x1FFF));

	/* SET FILTERS IDENTIFIERS FOR 16BIT IDENTIFIER, NO MASK */
	uint8 k = 0, j = 0;
	
	for (k = 0; k < 54; k++)
	{
		REG(CAN1_BASE, (CAN_F0R1 + (0x04 * (k) ) ) ) = 0;
	}
	
	for (k = 0; k < CAN_ACCEPTED_IDS_NUMBER; k++)
	{ 
		if (k % 2 == 0)
		{
			j = (k == 0 ? 0 : (j + 1) );
			setValue(REG(CAN1_BASE, (CAN_F0R1 + (0x04 * (j) ) ) ), 0, Can_AcceptedFilters[k]);
		}
		else
			setValue(REG(CAN1_BASE, (CAN_F0R1 + (0x04 * (j) ) ) ), 16, Can_AcceptedFilters[k]);
	}
	
	/* ENABLE RECEPTION INTERRUPTS */
	setBitState(REG(CAN1_BASE, CAN_IER), 1, STD_HIGH);

		/* RELEASE MAILBOXES IF NOT EMPTY */
	setBitState(REG(CAN1_BASE, CAN_RF0R), 5, STD_HIGH);
	setBitState(REG(CAN1_BASE, CAN_RF1R), 5, STD_HIGH);
	
	/* DEINITIALIZE RECEPTION */
	setBitState(REG(CAN1_BASE, CAN_FMR), 0, STD_LOW);

	/* ACTIVATE FILTER BANKS */
	setValue(REG(CAN1_BASE, CAN_FA1R), 0, 0x1FFF);

	/* ENTER NORMAL MODE */
	setBitState(REG(CAN1_BASE, CAN_MCR), 0, STD_LOW);
}

static uint8 Can_isMailBoxEmpty(Can_MailBoxType MailBox)
{
	return ( getBit(REG(CAN1_BASE, CAN_TSR), (MailBox + 26)) );
}

Can_ReturnType Can_SetControllerMode(uint8 Controller, Can_StateTransitionType Transition);
void Can_DisableControllerInterrupts(uint8 Controller);
void Can_EnableControllerInterrupts(uint8 Controller);

Can_ReturnType Can_Write(uint8 Hth, const Can_PduType* PduInfo) /* Hth refers to Mailbox */
{	
	Can_MailBoxType MailBox = (Can_MailBoxType)Hth;
	
	if (Can_isMailBoxEmpty(MailBox))
	{
		/* SET THE IDENTIFIER */
		if (PduInfo->id <= 0x7FF) /* STANDARD IDENTIFIER */
		{
			setBitState(REG(CAN1_BASE, (CAN_TI0R + (MailBox * 0x10))), 2, STD_LOW);
			setValue(REG(CAN1_BASE, (CAN_TI0R + (MailBox * 0x10))), 21, PduInfo->id);
		}
		else /* EXTENDED IDENTIFIER */
		{
			setBitState(REG(CAN1_BASE, (CAN_TI0R + (MailBox * 0x10))), 2, STD_HIGH);
			setValue(REG(CAN1_BASE, (CAN_TI0R + (MailBox * 0x10))), 3, PduInfo->id);
		}

		/* SET DLC */

		setValue(REG(CAN1_BASE, (CAN_TDT0R + (MailBox * 0x04))), 0, PduInfo->length);

		/* SET DATA REGISTER */
		if (PduInfo->length <= 4)
			setValue(REG(CAN1_BASE, (CAN_TDL0R + (MailBox * 0x10))), 0, *(PduInfo->sdu));
		else
		{
			setValue(REG(CAN1_BASE, (CAN_TDL0R + (MailBox * 0x10))), 0, getValue( (*(PduInfo->sdu)), 0, 0xFFFF));
			setValue(REG(CAN1_BASE, (CAN_TDH0R + (MailBox * 0x10))), 0, getValue( (*(PduInfo->sdu)), 32, 0xFFFF));
		}

		/* ENABLE TX BIT */
		setBitState(REG(CAN1_BASE, (CAN_TI0R + (MailBox * 0x10))), 0, STD_HIGH);
	}
}

Can_PduType ReceivedPdu;
volatile static uint8 ReceivedFlag = 0;

void Can_MainFunctionRead(void)
{
	uint64 ReceivedSdu = 0;

	ReceivedPdu.id = getValue(REG(CAN1_BASE, CAN_RI0R), 21, 0x7FF);
	
	ReceivedSdu = (getValue(REG(CAN1_BASE, CAN_RDH0R), 0, 0xFFFFFFFF) << 32) | (getValue(REG(CAN1_BASE, CAN_RDL0R), 0, 0xFFFFFFFF));
	ReceivedPdu.sdu = &ReceivedSdu;

	ReceivedPdu.length = getValue(REG(CAN1_BASE, CAN_RDT0R), 0, 0xF);
}

void Can_ISR()
{
	ReceivedFlag = 1;
	Can_MainFunctionRead();
	setBitState(REG(CAN1_BASE, CAN_RF0R), 5, STD_HIGH);
}

 /** END OF FILE: Can.c
  *****************************************************/