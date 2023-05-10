/*************************************************************
 * 
 * Filename: SCHEDULER_Cfg.c
 * Description: Configuration source file of the SCHEDULER driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "./includes/SCHEDULER_Cfg.h"
#include "./includes/LCD.h"
#include "./includes/SUART.h"
#include "./includes/DMA.h"

void DMA2_Stream2_TX_Task(void);

const Task_Info_t TaskInfo[TASKS_NUM]=
{
	[0]=
	{
		.Task_Name="LCD_vidInit",
		.Task_Period_us=5000,
		.Task_cbf=LCD_vidTask,
		.Task_Init_Delay_us=35000,
	},
	[1]=
	{
			.Task_Name=" LCD Task",
			.Task_Period_us=3000000,
			.Task_cbf= DMA_LCD,
			.Task_Init_Delay_us=1000000
	},
	[2]=
	{
		.Task_Name="DMA TX",
		.Task_Period_us=1000000,
		.Task_cbf= DMA2_Stream2_TX_Task,
		.Task_Init_Delay_us=1000000
	}
};



