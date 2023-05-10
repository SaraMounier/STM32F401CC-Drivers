/*************************************************************
 * 
 * Filename: SYSTICK_Priv.h
 * Description: Private header file of the SYSTICK driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __SYSTICK_PRIV_H__
#define __SYSTICK_PRIV_H__
#include "STD_TYPES.h"

/*Register to set and clear pending bits for systick exceptions*/
#define ICSR  (*(volatile u32*)(0xE000E00C))
#define SHPR3 (*(volatile u32*)(0xE000ED20))
/*The SHCSR enables the system handlers*/
#define SHCSR (*(volatile u32*)(0xE000E02C))

#define STK_CTRL (*(volatile u32*)(0xE000E010))
#define STK_LOAD (*(volatile u32*)(0xE000E014))
#define STK_VAL (*(volatile u32*)(0xE000E018))
#define STC_CALIB (*(volatile u32*)(0xE000E01C))
#endif /* __SYSTICK_PRIV_H__ */


/*
 * System timer:
The system timer (SysTick) is a 24-bit count-down timer. Use this as a Real Time
Operating System (RTOS) tick timer or as a simple counter

SysTick calibration value register:
The SysTick calibration value is fixed to 10500, which gives a reference time base of 1 ms
with the SysTick clock set to 10.5 MHz (HCLK/8, with HCLK set to 84 MHz).
*/

