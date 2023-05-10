/*************************************************************
 * 
 * Filename: LED_Cfg.c
 * Description: Configuration source file of the LED driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "includes\LED_Cfg.h"
#include "includes\GPIO.h"

#define LED1_TOGGLE   0
#define LED2_TOGGLE   1
#define LED3_TOGGLE   2
#define LED4_TOGGLE   3


const LED_tstrConfig_t Arr_LED_strConfig [LED_COUNT]=
{
[LED1_TOGGLE]={
			.LED_PortNum=GPIO_PORTA,
			.LED_PinNum=GPIO_Pin_00,
			.LED_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LED_OutputSpeed=GPIO_OUTPUT_HIGH_SPEED,
			.LED_PinPullUp_PullDown= GPIO_PUPDR_PULL_UP,
			.LED_OutputValue=GPIO_ODR_PINX_HIGH,
			.LED_InitialValue= LED_Init_off },
[LED2_TOGGLE]={
			.LED_PortNum=GPIO_PORTA,
			.LED_PinNum=GPIO_Pin_01,
			.LED_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LED_OutputSpeed=GPIO_OUTPUT_HIGH_SPEED,
			.LED_PinPullUp_PullDown= GPIO_PUPDR_PULL_UP,
			.LED_OutputValue=GPIO_ODR_PINX_HIGH,
			.LED_InitialValue= LED_Init_off },
[LED3_TOGGLE]={
			.LED_PortNum=GPIO_PORTA,
			.LED_PinNum=GPIO_Pin_02,
			.LED_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LED_OutputSpeed=GPIO_OUTPUT_HIGH_SPEED,
			.LED_PinPullUp_PullDown= GPIO_PUPDR_PULL_UP,
			.LED_OutputValue=GPIO_ODR_PINX_HIGH,
			.LED_InitialValue= LED_Init_off },

[LED4_TOGGLE]={
			.LED_PortNum=GPIO_PORTA,
			.LED_PinNum=GPIO_Pin_03,
			.LED_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LED_OutputSpeed=GPIO_OUTPUT_HIGH_SPEED,
			.LED_PinPullUp_PullDown= GPIO_PUPDR_PULL_DOWN,
			.LED_OutputValue=GPIO_ODR_PINX_LOW,
			.LED_InitialValue= LED_Init_off}/*,
[LED_STABLE]={
		.LED_PortNum=GPIO_PORTA,
		.LED_PinNum=GPIO_Pin_04,
		.LED_OutputType=GPIO_OUTPUT_PUSH_PULL,
		.LED_OutputSpeed=GPIO_OUTPUT_HIGH_SPEED,
		.LED_PinPullUp_PullDown= GPIO_PUPDR_PULL_UP,
		.LED_OutputValue=GPIO_ODR_PINX_HIGH,
		.LED_InitialValue= LED_Init_off }*/
};
