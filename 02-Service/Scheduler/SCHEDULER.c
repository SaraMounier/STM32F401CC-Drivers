/*************************************************************
 * 
 * Filename: SCHEDULER.c
 * Description: Source file of the SCHEDULER driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "./includes/SCHEDULER_Cfg.h"
#include "./includes/SCHEDULER_Priv.h"
#include "./includes/SCHEDULER.h"
#include "./includes/SYSTICK.h"

typedef struct {
	Task_Info_t *task_info;
	u32 remain;
}Task_t;

static void sched(void);

Task_t tasks[TASKS_NUM]={0};
u8 sched_flag=0;
void sched_vidInit(void)
{
	 u8 idx;
	 for(idx=0;idx<TASKS_NUM;idx++)
	 {
		 tasks[idx].task_info = & TaskInfo[idx];
		 tasks[idx].remain = TaskInfo[idx].Task_Init_Delay_us;
	 }
	 Systick_setCallBack(& tick_cbf);
}

void sched_vidStart(void)
{
	Systick_enable();
	while(1)
	{
		if(sched_flag==1)
		{
			sched();
			sched_flag=0;
		}
	}
}

void tick_cbf(void)
{
	if(sched_flag==0)
	{
		sched_flag=1;
	}
	else
	{
		/*CPU load exceeds 100%*/
	}
}

static void sched(void)
{
	 u8 idx;
	 for(idx=0;idx<TASKS_NUM;idx++)
	 {
		 if(tasks[idx].remain==0)
		 {
			 tasks[idx].task_info->Task_cbf();
			 tasks[idx].remain=tasks[idx].task_info->Task_Period_us;
		 }
		 tasks[idx].remain -=TICK;
	 }
}
