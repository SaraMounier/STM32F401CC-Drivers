/*************************************************************
 * 
 * Filename: SWITCH.c
 * Description: Source file of the SWITCH driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "./includes/SWITCH_Cfg.h"
#include "./includes/SWITCH_Priv.h"
#include "./includes/SWITCH.h"
#include "./includes/GPIO.h"
 u32 Current_State[SWITCH_COUNT]={0}, Previous_State[SWITCH_COUNT]={0};
 u32 Arr_SWITCH_Status[SWITCH_COUNT]={0};

SWITCH_enuErrorStatus_t SWITCH_Init(void)
{
	SWITCH_enuErrorStatus_t Loc_SWITCH_ErrorStatus=0;
	u8 iterator=0;
	for(iterator=0; iterator< SWITCH_COUNT ;iterator++)
	{
		GPIO_Pin_Confg SWITCH_Init_Object;
		SWITCH_Init_Object.GPIO_Port=Arr_SWITCH_strConfig [iterator].SWITCH_PortNum;
		SWITCH_Init_Object.GPIO_Pin=Arr_SWITCH_strConfig [iterator].SWITCH_PinNum;
		SWITCH_Init_Object.GPIO_PinMode=GPIO_MODE_INPUT;
		SWITCH_Init_Object.GPIO_PinPullUp_PullDown=Arr_SWITCH_strConfig [iterator].SWITCH_PinPullUp_PullDown;
		Init_Pin_Configure(& SWITCH_Init_Object);
	}
	return Loc_SWITCH_ErrorStatus;
}
void SWITCH_getStatus(void)
{
	static u8 Debouncing_Opertor=0;
	u8 SWITCH_Name ;
	for(SWITCH_Name=0;SWITCH_Name<SWITCH_COUNT;SWITCH_Name++)
	{
		gpio_getPinInputData(Arr_SWITCH_strConfig[SWITCH_Name].SWITCH_PortNum, Arr_SWITCH_strConfig[SWITCH_Name].SWITCH_PinNum, &Previous_State[SWITCH_Name]);
		while(Debouncing_Opertor<5)
		{
			gpio_getPinInputData(Arr_SWITCH_strConfig[SWITCH_Name].SWITCH_PortNum, Arr_SWITCH_strConfig[SWITCH_Name].SWITCH_PinNum, &Current_State[SWITCH_Name]);
			if(Current_State[SWITCH_Name]==Previous_State[SWITCH_Name])
			{
				Debouncing_Opertor++;
				Previous_State[SWITCH_Name]=Current_State[SWITCH_Name];
			}
			else
			{
				Debouncing_Opertor=0;
				break;
			}
		}
		if(Debouncing_Opertor==5){Debouncing_Opertor=0;}
		Arr_SWITCH_Status[SWITCH_Name]= Current_State[SWITCH_Name] ^ Arr_SWITCH_strConfig[SWITCH_Name].SWITCH_ActiveState;
	}
}


u8 SWITCH_Runnable(u8 SWITCH_Name)
{
 return   Arr_SWITCH_Status[SWITCH_Name];
}


void App4_Runnable(void)
 {
//		u8 switchstate;
//		switchstate=SWITCH_Runnable(SWITCH_START);
	 	if(Arr_SWITCH_Status[SWITCH_START] == SWITCH_Pressed)
	 	{
	 		gpio_setOutputPinValue( GPIO_PORTA, GPIO_Pin_03, GPIO_ODR_PINX_HIGH);
	 	}
	 	else
	 	{
	 		gpio_setOutputPinValue( GPIO_PORTA, GPIO_Pin_03, GPIO_ODR_PINX_LOW);
	 	}
 }
