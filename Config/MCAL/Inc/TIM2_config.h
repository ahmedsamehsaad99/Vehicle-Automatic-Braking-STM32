/*****************************************/
/* Author  :  Gehad Elkoumy              */
/* Version :  V01                        */
/* Date    :  10 MAR 2023                */
/*****************************************/

#ifndef TIM2_CONFIG_H
#define TIM2_CONFIG_H

/* Options : 0 -- upcounter 
			 1 -- downcounter  */
#define		  CR1_DIR			0


#define HIGH_FREQ_APP	1

#if (HIGH_FREQ_APP)
	#define TIM_PRESCALER		16
#else
	#define 	TIM_PRESCALER 		(F_CPU)/(1000)	/* USE TIM->ARR AS TIME IN MS */
#endif

#endif
