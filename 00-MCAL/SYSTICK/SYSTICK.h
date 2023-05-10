/*************************************************************
 * 
 * Filename: SYSTICK.h
 * Description: Header (interface) file of the SYSTICK driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __SYSTICK_H__
#define __SYSTICK_H__
#include "STD_TYPES.h"

#define ICSR_PENDSTCLR 		 25
#define ICSR_PENDSTSET 		 26
#define SHPR3_PRI_15    	 28
#define MASK_SHPR3_PRI_15    0x0fffffff

#define SHCSR_SYSTICKACT 	 11
/*STK_CTRL bits*/
#define Systick_COUNTER_ENABLE  0
#define Systick_INT_ENABLE 		1 /*SysTick exception request enable*/
#define Systick_ClOCK_SOURCE	2
#define Systick_COUNT_FLAG		16

/*select system clock function*/
#define Systick_CLK_AHB_DivBy8  0
#define Systick_CLK_AHB			1
#define By8						8

#define MAX_TICKS 0x00FFFFFF
#define MIN_TICKS 0x00000001

typedef enum
{
	Systick_enuOK,
	Systick_enuNOK,
	Systick_enuNullPtr,

}Systick_ErrorStatus_t;

Systick_ErrorStatus_t Systick_setPendingExceptionBit(void);
Systick_ErrorStatus_t Systick_clearPendingExceptionBit(void);
/*set Priority of system handler 15, SysTick exception*/
Systick_ErrorStatus_t Systick_setPendingExceptionPriority(u32 Systick_exception_Priority);

/*SYSTICKACT: SysTick exception active bit, reads as 1 if exception is active*
 * Active bits, read as 1 if the exception is active, or as 0 if it is not active. You can write to these bits to change the active
status of the exceptions, but see the Caution in this section. (use read modify write)*/
Systick_ErrorStatus_t Systick_activateException(void);
Systick_ErrorStatus_t Systick_deactivateException(void);
Systick_ErrorStatus_t Systick_readActivateExceptionStatus(u32 *Systick_ExceptionState);


/*STK_CTRL*/
/*
 Enables the counter. When ENABLE is set to 1, the counter loads the RELOAD value from the
LOAD register and then counts down. On reaching 0, it sets the COUNTFLAG to 1 and
optionally asserts the SysTick depending on the value of TICKINT. It then loads the RELOAD
value again, and begins counting.*/
Systick_ErrorStatus_t Systick_enable(void);
Systick_ErrorStatus_t Systick_disable(void);

/*TICKINT: SysTick exception request enable
0: Counting down to zero does not assert the SysTick exception request
1: Counting down to zero to asserts the SysTick exception request.*/
Systick_ErrorStatus_t Systick_exceptionRequestEnable(void);
Systick_ErrorStatus_t Systick_exceptionRequestDisable(void);

/*
 *
 * Options:Systick_CLK_AHB_DivBy8 or Systick_CLK_AHB
 * */
Systick_ErrorStatus_t Systick_selectClockSource(u32 Systick_CLK_);
/*Returns 1 if timer counted to 0 since last time this was read.*/
Systick_ErrorStatus_t Systick_getCountFlag(u32* Systick_CountFlag);

/* 0x00000001-0x00FFFFFF*/
/*Description:
 specifies the start value to load into the STK_VAL register when the
counter is enabled and when it reaches 0

The RELOAD value is calculated according to its use:
l) To generate a multi-shot timer with a period of N processor clock cycles, use a RELOAD
value of N-1. For example, if the SysTick interrupt is required every 100 clock pulses, set
RELOAD to 99.
l) To deliver a single SysTick interrupt after a delay of N processor clock cycles, use a
RELOAD of value N. For example, if a SysTick interrupt is required after 100 clock
pulses, set RELOAD to 99.
*/
Systick_ErrorStatus_t Systick_setTimeDelay(u32 Delay_Time_microsec);
Systick_ErrorStatus_t Systick_setInterruptafterTimeDelay(u32 Delay_Time_microsec); /*MKSLA*/
Systick_ErrorStatus_t Systick_getCurrentCounterValue(u32* Systick_CurrentCounterTicks,u32* Systick_CurrentCounterValue);
Systick_ErrorStatus_t Systick_setCallBack(void(*Systick_Timer_Handler)(void));

/*
 The SysTick counter reload and current value are undefined at reset, the correct
initialization sequence for the SysTick counter is:
1. Program reload value.
2. Clear current value.
3. Program Control and Status register*/
#endif /* __SYSTICK_H__ */
