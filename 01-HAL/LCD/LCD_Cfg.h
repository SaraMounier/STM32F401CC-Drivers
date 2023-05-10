/*************************************************************
 * 
 * Filename: LCD_Cfg.h
 * Description: Configuration header file of the LCD driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __LCD_CFG_H__
#define __LCD_CFG_H__

#include "STD_TYPES.h"
#include "GPIO.h"

#define ZERO_ASCII 48


#define LCD_D0_PIN 	00
#define LCD_D1_PIN 	01
#define LCD_D2_PIN 	02
#define LCD_D3_PIN 	03
#define LCD_D4_PIN 	04
#define LCD_D5_PIN 	05
#define LCD_D6_PIN 	06
#define LCD_D7_PIN 	07
#define LCD_RS_PIN 	8
#define LCD_RW_PIN 	9
#define LCD_EN_PIN  10
#define LCD_PINS_NUMBER 11
#define LCD_CONTROL_PORT GPIO_PORTB
#define LCD_DATA_PORT  GPIO_PORTA

#define High 1
#define LOW 0

#define CGRAM_BlockSize 8
#define LCD_VISABLERANGE 15
typedef struct  
{
	void* LCD_PortNum;
	u32   LCD_PinNum;
	u32   LCD_PinMode;
	u32	  LCD_OutputType;
	u32   LCD_OutputSpeed;
	u32   LCD_PinPullUp_PullDown;
	u32   LCD_Initial_Value;
} LCD_tstrConfig_t;



extern const  LCD_tstrConfig_t Arr_LCD_strConfig [LCD_PINS_NUMBER];
extern u8 UnFilledHeart[8];
extern u8 Mobile[8];
extern u8 Bell[8];
extern u8 Silent[8];
extern u8 Music[8];
extern u8 Plug[8];
extern u8 Face[8];
extern u8 FilledHeart[8];
extern u8 YogaHuman[8];
extern u8 Human[8];
extern u8 Cat[8];
extern u8 Paw[8] ;
#endif /* __LCD_CFG_H__ */
