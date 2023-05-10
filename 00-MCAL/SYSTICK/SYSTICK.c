/*************************************************************
 * 
 * Filename: SYSTICK.c
 * Description: Source file of the SYSTICK driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "./includes/SYSTICK_Cfg.h"
#include "./includes/SYSTICK_Priv.h"
#include "./includes/SYSTICK.h"


Systick_ErrorStatus_t Systick_setPendingExceptionBit(void)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	ICSR |= 1<<ICSR_PENDSTSET;
	return Loc_systick_ErrStatus;
}
Systick_ErrorStatus_t Systick_clearPendingExceptionBit(void)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	ICSR |= 1<<ICSR_PENDSTCLR;
	return Loc_systick_ErrStatus;
}

Systick_ErrorStatus_t Systick_setPendingExceptionPriority(u32 Systick_exception_Priority)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	u32 tempVar=SHPR3 & (MASK_SHPR3_PRI_15);
	SHPR3 =tempVar | (Systick_exception_Priority<<SHPR3_PRI_15);
	return Loc_systick_ErrStatus;
}

Systick_ErrorStatus_t Systick_activateException(void)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	SHCSR |= 1<<SHCSR_SYSTICKACT;
	return Loc_systick_ErrStatus;
}

Systick_ErrorStatus_t Systick_deactivateException(void)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	SHCSR &=~( 1<<SHCSR_SYSTICKACT);
	return Loc_systick_ErrStatus;
}
Systick_ErrorStatus_t Systick_readActivateExceptionStatus(u32 *Systick_ExceptionState)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	*Systick_ExceptionState= (SHCSR >>SHCSR_SYSTICKACT) &0x01;
	return Loc_systick_ErrStatus;
}

Systick_ErrorStatus_t Systick_enable(void)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	STK_CTRL |= 1<<Systick_COUNTER_ENABLE;
	return  Loc_systick_ErrStatus;
}
Systick_ErrorStatus_t Systick_disable(void)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	STK_CTRL &= ~(1<<Systick_COUNTER_ENABLE);
	return  Loc_systick_ErrStatus;
}
Systick_ErrorStatus_t Systick_exceptionRequestEnable(void)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	STK_CTRL |= 1<<Systick_INT_ENABLE;
	return  Loc_systick_ErrStatus;
}
Systick_ErrorStatus_t Systick_exceptionRequestDisable(void)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	STK_CTRL &= ~(1<<Systick_INT_ENABLE);
	return  Loc_systick_ErrStatus;
}

Systick_ErrorStatus_t Systick_selectClockSource(u32 Systick_CLK_)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	if(Systick_CLK_==Systick_CLK_AHB_DivBy8)
	{
		STK_CTRL &= ~(1<<Systick_ClOCK_SOURCE);
	}
	else if(Systick_CLK_==Systick_CLK_AHB)
	{
		STK_CTRL |= (1<<Systick_ClOCK_SOURCE);
	}
	else
	{
		Loc_systick_ErrStatus=Systick_enuNOK;
	}
	return  Loc_systick_ErrStatus;
}
Systick_ErrorStatus_t Systick_getCountFlag(u32* Systick_CountFlag)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	* Systick_CountFlag = (STK_CTRL >> Systick_COUNT_FLAG)& 0x01;
	return  Loc_systick_ErrStatus;
}

Systick_ErrorStatus_t Systick_setTimeDelay(u32 Delay_Time_microsec)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	u32 intClock=RCC_CLOCK;
	u32 Pulses=0;
	if(((STK_CTRL >> Systick_ClOCK_SOURCE)& 0x01)==1)
	{
		Pulses=Delay_Time_microsec *( intClock/1000000);
	}
	else if (((STK_CTRL >> Systick_ClOCK_SOURCE)& 0x01)==0)
	{
		intClock /= By8;
		Pulses= Delay_Time_microsec *( intClock/1000000);
	}

	if(Pulses>MIN_TICKS && Pulses<MAX_TICKS)
	{
		STK_LOAD=Pulses-1;
	}
	else
	{
		Loc_systick_ErrStatus=Systick_enuOK;
	}
	return  Loc_systick_ErrStatus;
}

Systick_ErrorStatus_t Systick_getCurrentCounterValue(u32* Systick_CurrentCounterTicks,u32* Systick_CurrentCounterValue)
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus=Systick_enuOK;
	u32 intclock=RCC_CLOCK;
	*Systick_CurrentCounterTicks = (STK_VAL >>0) & MAX_TICKS;
	if(((STK_CTRL >> Systick_ClOCK_SOURCE)& 0x01)==1)
	{
		*Systick_CurrentCounterValue= *Systick_CurrentCounterTicks/intclock;
	}
	else if(((STK_CTRL >> Systick_ClOCK_SOURCE)& 0x01)==0)
	{
		intclock /= By8;
		*Systick_CurrentCounterValue= *Systick_CurrentCounterTicks/(intclock);

	}
	return  Loc_systick_ErrStatus;
}

void (*Systick_Timer)(void)=NULL;

Systick_ErrorStatus_t Systick_setCallBack( void(* Systick_Timer_Handler)(void) )
{
	Systick_ErrorStatus_t Loc_systick_ErrStatus;
	if (Systick_Timer_Handler !=NULL)
	{
		Systick_Timer=Systick_Timer_Handler ;
		Loc_systick_ErrStatus=Systick_enuOK;
	}
	else
	{
		Loc_systick_ErrStatus=Systick_enuNullPtr;
	}
	return Loc_systick_ErrStatus;
}

void __attribute__ ((section(".after_vectors"), weak))
SysTick_Handler (void)
{
	if (Systick_Timer !=NULL)
	{
		Systick_Timer();
	}
}



