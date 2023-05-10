/*************************************************************
 * 
 * Filename: LCD_Cfg.c
 * Description: Configuration source file of the LCD driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "./includes/LCD_Cfg.h"
#include "./includes/GPIO.h"
 const LCD_tstrConfig_t Arr_LCD_strConfig [LCD_PINS_NUMBER] =
{
	
	[LCD_RS_PIN ]=
	{
			.LCD_PortNum=LCD_CONTROL_PORT ,
			.LCD_PinNum=GPIO_Pin_00 ,
			.LCD_Initial_Value=LOW,
			.LCD_PinMode=GPIO_MODE_GENERAL_PURPOSE_OUTPUT,
			.LCD_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LCD_OutputSpeed=GPIO_OUTPUT_VERY_HIGH_SPEED,
			.LCD_PinPullUp_PullDown=GPIO_PUPDR_PULL_UP,
	},
	[LCD_RW_PIN ]=
	{
			.LCD_PortNum=LCD_CONTROL_PORT ,
			.LCD_PinNum=GPIO_Pin_01 ,
			.LCD_Initial_Value=LOW,
			.LCD_PinMode=GPIO_MODE_GENERAL_PURPOSE_OUTPUT,
			.LCD_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LCD_OutputSpeed=GPIO_OUTPUT_VERY_HIGH_SPEED,
			.LCD_PinPullUp_PullDown=GPIO_PUPDR_PULL_UP,
	},
	[LCD_EN_PIN ]=
	{
			.LCD_PortNum=LCD_CONTROL_PORT ,
			.LCD_PinNum=GPIO_Pin_02 ,
			.LCD_Initial_Value=LOW,
			.LCD_PinMode= GPIO_MODE_GENERAL_PURPOSE_OUTPUT,
			.LCD_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LCD_OutputSpeed=GPIO_OUTPUT_VERY_HIGH_SPEED,
			.LCD_PinPullUp_PullDown=GPIO_PUPDR_PULL_UP,
	},
	[LCD_D0_PIN ]=
	{
			.LCD_PortNum=LCD_DATA_PORT ,
			.LCD_PinNum=GPIO_Pin_00 ,
			.LCD_Initial_Value=LOW,
			.LCD_PinMode=GPIO_MODE_GENERAL_PURPOSE_OUTPUT,
			.LCD_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LCD_OutputSpeed=GPIO_OUTPUT_VERY_HIGH_SPEED,
			.LCD_PinPullUp_PullDown=GPIO_PUPDR_PULL_UP,
	},
	[LCD_D1_PIN ]=
	{
			.LCD_PortNum=LCD_DATA_PORT,
			.LCD_PinNum=GPIO_Pin_01 ,
			.LCD_Initial_Value=LOW,
			.LCD_PinMode=GPIO_MODE_GENERAL_PURPOSE_OUTPUT,
			.LCD_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LCD_OutputSpeed=GPIO_OUTPUT_VERY_HIGH_SPEED,
			.LCD_PinPullUp_PullDown=GPIO_PUPDR_PULL_UP,
	},
	[LCD_D2_PIN ]=
	{
			.LCD_PortNum=LCD_DATA_PORT,
			.LCD_PinNum=GPIO_Pin_02 ,
			.LCD_Initial_Value=LOW,
			.LCD_PinMode=GPIO_MODE_GENERAL_PURPOSE_OUTPUT,
			.LCD_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LCD_OutputSpeed=GPIO_OUTPUT_VERY_HIGH_SPEED,
			.LCD_PinPullUp_PullDown=GPIO_PUPDR_PULL_UP,
	},
	[LCD_D3_PIN ]=
	{
			.LCD_PortNum=LCD_DATA_PORT,
			.LCD_PinNum=GPIO_Pin_03 ,
			.LCD_Initial_Value=LOW,
			.LCD_PinMode=GPIO_MODE_GENERAL_PURPOSE_OUTPUT,
			.LCD_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LCD_OutputSpeed=GPIO_OUTPUT_VERY_HIGH_SPEED,
			.LCD_PinPullUp_PullDown=GPIO_PUPDR_PULL_UP,
	},
	[LCD_D4_PIN ]=
	{
			.LCD_PortNum=LCD_DATA_PORT,
			.LCD_PinNum=GPIO_Pin_04 ,
			.LCD_Initial_Value=LOW,
			.LCD_PinMode=GPIO_MODE_GENERAL_PURPOSE_OUTPUT,
			.LCD_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LCD_OutputSpeed=GPIO_OUTPUT_VERY_HIGH_SPEED,
			.LCD_PinPullUp_PullDown=GPIO_PUPDR_PULL_UP,
	},
	[LCD_D5_PIN ]=
	{
			.LCD_PortNum=LCD_DATA_PORT,
			.LCD_PinNum=GPIO_Pin_05 ,
			.LCD_Initial_Value=LOW,
			.LCD_PinMode=GPIO_MODE_GENERAL_PURPOSE_OUTPUT,
			.LCD_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LCD_OutputSpeed=GPIO_OUTPUT_VERY_HIGH_SPEED,
			.LCD_PinPullUp_PullDown=GPIO_PUPDR_PULL_UP,
	},
	[LCD_D6_PIN ]=
	{
			.LCD_PortNum=LCD_DATA_PORT,
			.LCD_PinNum=GPIO_Pin_06 ,
			.LCD_Initial_Value=LOW,
			.LCD_PinMode=GPIO_MODE_GENERAL_PURPOSE_OUTPUT,
			.LCD_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LCD_OutputSpeed=GPIO_OUTPUT_VERY_HIGH_SPEED,
			.LCD_PinPullUp_PullDown=GPIO_PUPDR_PULL_UP,
	},
	[LCD_D7_PIN ]=
	{
			.LCD_PortNum=LCD_DATA_PORT,
			.LCD_PinNum=GPIO_Pin_07 ,
			.LCD_Initial_Value=LOW,
			.LCD_PinMode=GPIO_MODE_GENERAL_PURPOSE_OUTPUT,
			.LCD_OutputType=GPIO_OUTPUT_PUSH_PULL,
			.LCD_OutputSpeed=GPIO_OUTPUT_VERY_HIGH_SPEED,
			.LCD_PinPullUp_PullDown=GPIO_PUPDR_PULL_UP,
	}
};


/* Custom char set for alphanumeric LCD Module */
u8 UnFilledHeart[8] = { 0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00};  
u8 Mobile[8] = { 0x04, 0x1F, 0x11, 0x11, 0x1F, 0x1F, 0x1F, 0x1F};
u8 Bell[8] = { 0x04, 0x0E, 0x0E, 0x0E, 0x1F, 0x00, 0x04, 0x00};
u8 Silent[8] = { 0x01, 0x03, 0x07, 0x1F, 0x1F, 0x07, 0x03, 0x01};
u8 Music[8] = { 0x01, 0x03, 0x05, 0x09, 0x09, 0x0B, 0x1B, 0x18};
u8 Plug[8] = { 0x0A, 0x0A, 0x1F, 0x11, 0x11, 0x0E, 0x04, 0x04};
u8 Face[8] = { 0x00, 0x00, 0x0A, 0x00, 0x04, 0x11, 0x0E, 0x00};
u8 FilledHeart[8] = { 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00};
u8 YogaHuman[8] = { 0x04, 0x0E, 0x0E, 0x04, 0x0E, 0x15, 0x0E, 0x11};
u8 Human[8] = { 0x04, 0x0E, 0x04, 0x0E, 0x015, 0x0E, 0x11, 0x00};	
u8 Cat[8] = { 0x1B, 0x15, 0x0E, 0x1F, 0x15, 0x1F, 0x0E, 0x00};
u8 Paw[8] = { 0x15, 0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x00, 0x00};
	/*
	//defining House Icon
	u8 housechar1[8]={0b00000, 0b00001, 0b00011, 0b00011, //Row 0, Col 0
	0b00111, 0b01111, 0b01111, 0b11111,};
	u8 housechar2[8]={0b11111, 0b11111, 0b11100, 0b11100, //Row 1, Col 0
	0b11100, 0b11100, 0b11100, 0b11100,};
	u8 housechar3[8]={0b00000, 0b10010, 0b11010, 0b11010, //ROW 0, Col 1
	0b11110, 0b11110, 0b11110, 0b11111,};
	u8 housechar4[8]={0b11111, 0b11111, 0b11111, 0b10001, //Row 1, Col 1
	0b10001, 0b10001, 0b11111, 0b11111,};
	//Defining Thermometer Icon
	u8 tempchar1[8]={0b00000, 0b00001, 0b00010, 0b00100, //Row 0, Col 2
	0b00100, 0b00100, 0b00100, 0b00111,};
	u8 tempchar2[8]={0b00111, 0b00111, 0b00111, 0b01111, //Row 1, Col 2
	0b11111, 0b11111, 0b01111, 0b00011,};
	u8 tempchar3[8]={0b00000, 0b10000, 0b01011, 0b00100, //ROW 0, Col 3
	0b00111, 0b00100, 0b00111, 0b11100,};
	u8 tempchar4[8]={0b11111, 0b11100, 0b11100, 0b11110, //Row 1, Col 3
	0b11111, 0b11111, 0b11110, 0b11000,};

	//Defining Humidity Icon
	u8 humchar1[8]={0b00000, 0b00001, 0b00011, 0b00011,
	0b00111, 0b01111, 0b01111, 0b11111,};
	u8 humchar2[8]={0b11111, 0b11111, 0b11111, 0b01111,
	0b00011, 0b00000, 0b00000, 0b00000,};
	u8 humchar3[8]={0b00000, 0b10000, 0b11000, 0b11000,
	0b11100, 0b11110, 0b11110, 0b11111,};
	u8 humchar4[8]={0b11111, 0b11111, 0b11111, 0b11110,
	0b11100, 0b00000, 0b00000, 0b00000,};*/
