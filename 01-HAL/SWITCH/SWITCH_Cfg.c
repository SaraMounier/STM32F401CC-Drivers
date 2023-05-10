/*************************************************************
 * 
 * Filename: SWITCH_Cfg.c
 * Description: Configuration source file of the SWITCH driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "./includes/SWITCH_Cfg.h"
#include "./includes/GPIO.h"

 const  SWITCH_tstrConfig_t Arr_SWITCH_strConfig [SWITCH_COUNT]={
		 [SWITCH_START]=
		 {
			.SWITCH_PortNum=GPIO_PORTB,
			.SWITCH_PinNum=GPIO_Pin_00,
			.SWITCH_ActiveState=SWITCH_ActiveHigh_PullDown,
			.SWITCH_PinPullUp_PullDown= GPIO_PUPDR_PULL_DOWN,

		 }/*,
		 [SWITCH_STOP]=
		 {
			.SWITCH_PortNum=GPIO_PORTB,
			.SWITCH_PinNum=GPIO_Pin_01,
			.SWITCH_ActiveState=SWITCH_ActiveLow_PullDown,
			.SWITCH_PinPullUp_PullDown= GPIO_PUPDR_PULL_DOWN,

		 },
		 [SWITCH_PAUSE]=
		 {
			.SWITCH_PortNum=GPIO_PORTB,
			.SWITCH_PinNum=GPIO_Pin_02,
			.SWITCH_ActiveState=SWITCH_ActiveHigh_PullUp,
			.SWITCH_PinPullUp_PullDown= GPIO_PUPDR_PULL_UP,
,
		 },
		 [SWITCH_WARNING]=
		 {
			.SWITCH_PortNum=GPIO_PORTB,
			.SWITCH_PinNum=GPIO_Pin_03,
			.SWITCH_ActiveState=SWITCH_ActiveHigh_PullUp,
			.SWITCH_PinPullUp_PullDown= GPIO_PUPDR_PULL_UP,
		},
		 [SWITCH_STABLE]=
		 {
			.SWITCH_PortNum=GPIO_PORTB,
			.SWITCH_PinNum=GPIO_Pin_04,
			.SWITCH_ActiveState=SWITCH_ActiveLow_PullDown,
			.SWITCH_PinPullUp_PullDown= GPIO_PUPDR_PULL_DOWN,

		 }*/
 };
