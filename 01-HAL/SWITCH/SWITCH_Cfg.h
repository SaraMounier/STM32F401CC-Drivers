/*************************************************************
 * 
 * Filename: SWITCH_Cfg.h
 * Description: Configuration header file of the SWITCH driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __SWITCH_CFG_H__
#define __SWITCH_CFG_H__

#include "STD_TYPES.h"
#define SWITCH_COUNT   1

#define SWITCH_START   0
//#define SWITCH_STOP    1
//#define SWITCH_PAUSE   2
//#define SWITCH_WARNING 3
//#define SWITCH_STABLE  4

typedef struct
{
	void* SWITCH_PortNum;
	u32 SWITCH_PinNum;
	u32 SWITCH_PinPullUp_PullDown;
	u32 SWITCH_ActiveState;

} SWITCH_tstrConfig_t;

typedef enum
{
		SWITCH_ActiveLow_PullUp,
		SWITCH_ActiveHigh_PullDown,

}SWITCH_Active_State;


typedef enum
{
	SWITCH_Released,
	SWITCH_Pressed,
}SWITCH_State;

extern const  SWITCH_tstrConfig_t Arr_SWITCH_strConfig [SWITCH_COUNT];
extern u32 Arr_SWITCH_Status[SWITCH_COUNT];
#endif /* __SWITCH_CFG_H__ */
