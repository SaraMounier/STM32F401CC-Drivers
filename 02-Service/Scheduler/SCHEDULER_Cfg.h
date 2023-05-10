/*************************************************************
 * 
 * Filename: SCHEDULER_Cfg.h
 * Description: Configuration header file of the SCHEDULER driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __SCHEDULER_CFG_H__
#define __SCHEDULER_CFG_H__
#include "SCHEDULER.h"
#define TASKS_NUM 3
#define TICK 1000

extern const Task_Info_t TaskInfo[TASKS_NUM];
#endif /* __SCHEDULER_CFG_H__ */
