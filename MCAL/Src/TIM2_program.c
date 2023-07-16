/*****************************************/
/* Author  :  Gehad Elkoumy              */
/* Version :  V01                        */
/* Date    :  10 MAR 2023                */
/*****************************************/


#include "../../Common/Std_Types.h"
#include "../../Common/Registers.h"

//#include "STD_TYPES.h"
//#include "BIT_MATH.h"

#include "../Inc/TIM2_interface.h"
#include "../Inc/TIM2_private.h"
#include "../../Config/MCAL/Inc/TIM2_config.h"

void MTIM2_voidInit (void)
{
	// Enable clock for Timer2
	setBitState(REG(RCC_BASE, RCC_APB1ENR), 0, STD_HIGH);

	/*direction of counter when it is edge aligned mode , no need for this bit if centered aligned*/
	setBitState(TIM2 -> CR1 , 4, STD_LOW);
	TIM2->CR1 |= (CR1_DIR << 4);
	
	/*prescaler value*/
	TIM2->PSC = TIM_PRESCALER;
	
	/*if there is interrupt then DIER_UIE must be enabled*/
	setBitState(TIM2 -> DIER , 0, STD_HIGH);
	
	/*enable channel*/
	setBitState(TIM2->CCER , 12, STD_HIGH);

	/*enable pwm mode 1*/
	setBitState(TIM2->CCMR2 , 12, STD_LOW);
	setBitState(TIM2->CCMR2 , 13, STD_HIGH);
	setBitState(TIM2->CCMR2 , 14, STD_HIGH);

	/*enable output compare -- update value after overflow or immediately*/
	setBitState(TIM2->CCMR2 , 11, STD_LOW);   //immediately

	/*enable auto reload preload for PWM*/
	setBitState(TIM2 -> CR1 , 7, STD_HIGH);

	/*load desired value of ARR*/
	TIM2->ARR  = 500; /* INPUT IS PERIOD IN MS */

	/*enable counter*/
	setBitState(TIM2 -> CR1 , 0, STD_HIGH);
	/*enable update generation*/
	setBitState(TIM2 -> EGR , 0, STD_HIGH);

}

void MTIM2_voidSetBusyWait(uint32 Copy_u16Ticks)
{
	/* Load ticks to ARR register */
	TIM2 -> ARR = Copy_u16Ticks;
	/*start counter*/
	setBitState(TIM2 -> CR1 , 0, STD_HIGH);
	/* Wait till flag is raised */
	while( (getBit(TIM2 -> SR , 0)) == 0);
	/*Stop counter*/
	setBitState(TIM2 -> CR1 , 0, STD_LOW);
	/*Clear flag*/
	setBitState(TIM2 -> SR , 0, STD_LOW);
	
}

void MTIM2_voidOutputPWM (uint16 Frequency, uint16 DutyCycle)
{
	#if (HIGH_FREQ_APP)
		TIM2->ARR  = (F_CPU)/(Frequency * TIM_PRESCALER); 
	#else
		TIM2->ARR = Frequency;	/* INPUT IS PERIOD IN MS */
	#endif
	CCR4 = DutyCycle * TIM2->ARR / 100;
}


