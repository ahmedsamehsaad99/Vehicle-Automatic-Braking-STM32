/*****************************************/
/* Author  :  Gehad Elkoumy              */
/* Version :  V01                        */
/* Date    :  10 MAR 2023                */
/*****************************************/

#ifndef TIM2_PRIVATE_H
#define TIM2_PRIVATE_H

#define 	TIM2_Base_Address		0x40000000

#include "../../Common/Std_Types.h"

typedef struct
{
	volatile uint32 CR1   ;
	volatile uint32 CR2   ;
	volatile uint32 SMCR  ;
	volatile uint32 DIER  ;
	volatile uint32 SR    ;
	volatile uint32 EGR   ;
	volatile uint32 CCMR1 ;
	volatile uint32 CCMR2 ;
	volatile uint32 CCER  ;
	volatile uint32 CNT   ;
	volatile uint32 PSC   ;
	volatile uint32 ARR   ;
	
}TIMER_t;

#define     TIM2    ((TIMER_t*) TIM2_Base_Address)


#define 	CCR1	*((volatile uint32*)(TIM2_Base_Address + 0x34))
#define 	CCR2	*((volatile uint32*)(TIM2_Base_Address + 0x38)) 
#define 	CCR3	*((volatile uint32*)(TIM2_Base_Address + 0x3C)) 
#define 	CCR4	*((volatile uint32*)(TIM2_Base_Address + 0x40))
#define 	DCR		*((volatile uint32*)(TIM2_Base_Address + 0x48)) 
#define 	DMAR	*((volatile uint32*)(TIM2_Base_Address + 0x4C)) 



#endif
