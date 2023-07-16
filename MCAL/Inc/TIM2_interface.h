/*****************************************/
/* Author  :  Gehad Elkoumy              */
/* Version :  V01                        */
/* Date    :  10 MAR 2023                */
/*****************************************/

#ifndef TIM2_INTERFACE_H
#define TIM2_INTERFACE_H

#include "../../Common/Std_Types.h"

void MTIM2_voidInit (void);
void MTIM2_voidSetBusyWait(uint32 Copy_u16Ticks);
void MTIM2_voidOutputPWM (uint16 Frequency, uint16 DutyCycle);

#endif

/*
see RCC to enable clock on timer
for counter --- dont need to enable GPIO clock
for PWM ----- GPIO clock must be enabled

to get the timer going we need to 
psc = 65535
ARR = 6000
CR1 = enable counter , direction

PWM freq = Fclk/(PSC*ARR)
PWM duty cycle = CCR / ARR

ex: if we want freq of 1KHz then Fclk = 72MHZ , ARR = 1000 , PSC = 72
so pwm freq = 72M/(72*1000) = 1KHZ

*/
