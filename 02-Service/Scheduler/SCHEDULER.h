/*************************************************************
 * 
 * Filename: SCHEDULER.h
 * Description: Header (interface) file of the SCHEDULER driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__
#include "STD_TYPES.h"
#include "SYSTICK.h"

typedef void (*Runnable_CBF_t)(void);
typedef struct {
	char* Task_Name;
	Runnable_CBF_t Task_cbf;
	u32 Task_Period_us;
	u32 Task_Init_Delay_us;
}Task_Info_t;

void sched_vidInit(void);
void sched_vidStart(void);
void tick_cbf(void);
#endif /* __SCHEDULER_H__ */
