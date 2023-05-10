/*************************************************************
 * 
 * Filename: LED_Cfg.h
 * Description: Configuration header file of the LED driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __LED_CFG_H__
#define __LED_CFG_H__
#include "STD_TYPES.h"
#define LED_COUNT   4
/*
#define LED_Stop    1
#define LED_Pause   2
#define LED_Warning 3
#define LED_STABLE  4
*/
typedef struct
{
	void* LED_PortNum;
	u32 LED_PinNum;
	u32	LED_OutputType;
	u32 LED_OutputSpeed;
	u32 LED_PinPullUp_PullDown;
	u32 LED_OutputValue;
	u32 LED_InitialValue;

} LED_tstrConfig_t;

typedef enum
{
	LED_PullUp,
	LED_PullDown,
}LED_PinPullUp_PullDown;

typedef enum
{
	LED_Init_on,
	LED_Init_off,

}LED_Init_Value;

extern const  LED_tstrConfig_t Arr_LED_strConfig [LED_COUNT];


#endif /* __LED_CFG_H__ */
