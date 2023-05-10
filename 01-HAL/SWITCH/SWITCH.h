/*************************************************************
 * 
 * Filename: SWITCH.h
 * Description: Header (interface) file of the SWITCH driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __SWITCH_H__
#define __SWITCH_H__
#include "STD_TYPES.h"
#include "GPIO.h"
#include "SWITCH_Cfg.h"
#include "SWITCH_Priv.h"
typedef enum
{
	SWITCH_enuOK,
	SWITCH_enuNOK,
	SWITCH_enuNullPtr,
}SWITCH_enuErrorStatus_t;

SWITCH_enuErrorStatus_t SWITCH_Init(void);
void SWITCH_getStatus(void);
u8 SWITCH_Runnable(u8 SWITCH_Name);
void App4_Runnable(void);
#endif /* __SWITCH_H__ */
