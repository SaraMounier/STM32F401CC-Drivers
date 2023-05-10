/*************************************************************
 * 
 * Filename: LED.h
 * Description: Header (interface) file of the LED driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __LED_H__
#define __LED_H__
#include "STD_TYPES.h"
#include "LED_Cfg.h"

#define State_ON  1
#define State_OFF 0

typedef enum {
	LED_enuOK=0,
	LED_enuNOK,
	LED_enuNullPtr
} LED_tenuErrorStatus;


LED_tenuErrorStatus led_Init(void);
LED_tenuErrorStatus led_setState(u32 LED_Name, u32 State_);
LED_tenuErrorStatus led_setGroupofLEDsState (u32 Arr[],u32 ArrSize, u32 LEDs_StatePattern);
void App1_Runnable(void);
void App2_Runnable(void);
void App3_Runnable(void);
#endif /* __LED_H__ */
