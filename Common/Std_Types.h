/******************************************************************************
 *  FILE DESCRIPTION
 ---------------------------------------
 *  FILE:			Std_Types.h
 *  DESCRIPTION:	Header file for the used data types/bitwise operations
 *	AUTHOR:			Ahmed Sameh Saad
 *****************************************************************************/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

#include <stdio.h>

#define setBitState(REGISTER, BITNUM, BITSTATE)		((BITSTATE == 1) ? (REGISTER |= (1<<BITNUM)) : (REGISTER &= ~(1<<BITNUM)))
#define getBit(REGISTER, BITNUM) 					((REGISTER & (1<<BITNUM)) >> BITNUM)
#define toggleBit(REGISTER, BITNUM) 				(REGISTER ^= (1<<BITNUM))

/* Set value starting from NTH bit <<*/
#define setValue(REGISTER, BITNUM, VALUE)			(REGISTER = (REGISTER & ~(1<<BITNUM)) | (VALUE<<BITNUM))
#define clearValue(REGISTER, BITNUM, VALUE)			(REGISTER &= ~(VALUE<<BITNUM))
#define getValue(REGISTER, BITNUM, MASK)			((REGISTER & (MASK<<BITNUM)) >> BITNUM)

#define round(x)						((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

#define F_CPU							12000000UL
#define NULL							((void*)0)

#define	DEBUG(VAR, STRING, X, Y, Z)	Usart_StringType VAR;\
																sprintf(VAR, STRING, X, Y, Z);\
																Usart_TransmitString(USART_3, VAR);\

typedef enum
{
	STD_LOW, STD_HIGH
} Std_ReturnType;


typedef unsigned char	uint8;
typedef signed char		sint8;

typedef unsigned short	uint16;
typedef signed short	sint16;

typedef unsigned int	uint32;
typedef signed int		sint32;

typedef unsigned long	uint64;
typedef signed long		sint64;

typedef float			float32;
typedef double			float64;


#endif

/** END OF FILE: Std_types.h
 *****************************************************/