/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			BrakingLogicPinout.h
 *  DESCRIPTION:	Header file for the pinouts
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef BRAKING_PINOUT_H
#define BRAKING_PINOUT_H

//#define ABS_POS_RELAY		PORT_A_PIN_0

#define ABS_POS_RELAY		PORT_B_PIN_0
#define ABS_NEG_RELAY		PORT_B_PIN_1

#define BATTERY_12V_RELAY	PORT_A_PIN_7

#define BLS_CTRL_RELAY		PORT_B_PIN_12	/* RELAY TO TURN OFF THE RELAY FROM THE CONTROLLER */
#define BLS_RELAY			PORT_B_PIN_13	/* RELAY TO TURN ON THE BLS */

#define PWM_SIG_OUT			PORT_A_PIN_3

#endif