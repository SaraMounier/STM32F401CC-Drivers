/*************************************************************
 * 
 * Filename: LED.c
 * Description: Source file of the LED driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "includes\LED_Cfg.h"
#include "includes\LED_Priv.h"
#include "includes\LED.h"
#include "includes\GPIO.h"

LED_tenuErrorStatus led_Init(void)
{
	LED_tenuErrorStatus Loc_LED_ErrorStatus=0;
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	u8 iterator=0;
	for(iterator=0; iterator< LED_COUNT/*(sizeof(Arr_LED_strConfig)/sizeof(LED_tstrConfig_t))*/ ;iterator++)
	{
		GPIO_Pin_Confg LED_Init_Object;
		LED_Init_Object.GPIO_Port=Arr_LED_strConfig [iterator].LED_PortNum;
		LED_Init_Object.GPIO_Pin=Arr_LED_strConfig [iterator].LED_PinNum;
		LED_Init_Object.GPIO_PinMode=GPIO_MODE_GENERAL_PURPOSE_OUTPUT;
		LED_Init_Object.GPIO_OutputPinType= Arr_LED_strConfig [iterator].LED_OutputType;
		LED_Init_Object.GPIO_OutputPinSpeed=Arr_LED_strConfig [iterator].LED_OutputSpeed;
		LED_Init_Object.GPIO_PinPullUp_PullDown=Arr_LED_strConfig [iterator].LED_PinPullUp_PullDown;
		if(Arr_LED_strConfig [iterator].LED_PinPullUp_PullDown==GPIO_PUPDR_PULL_UP)
			LED_Init_Object.GPIO_OutputPinValue=(LED_PullUp ^ Arr_LED_strConfig [iterator].LED_InitialValue);
		if(Arr_LED_strConfig [iterator].LED_PinPullUp_PullDown==GPIO_PUPDR_PULL_DOWN)
			LED_Init_Object.GPIO_OutputPinValue=(LED_PullDown ^ Arr_LED_strConfig [iterator].LED_InitialValue);
		/*Loc_GPIO_ErrorStatus= */Init_Pin_Configure(& LED_Init_Object);
		if(Loc_GPIO_ErrorStatus !=GPIO_enuOk)
		{
			Loc_LED_ErrorStatus=LED_enuNOK;
			break;
		}
		else
		{
			Loc_LED_ErrorStatus=LED_enuOK;
		}

	}
	return Loc_LED_ErrorStatus;
}

LED_tenuErrorStatus led_setState(u32 LED_Name,u32 State_ )
{
	LED_tenuErrorStatus Loc_LED_ErrorStatus=0;
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	if(Arr_LED_strConfig [LED_Name].LED_PinPullUp_PullDown==GPIO_PUPDR_PULL_UP)
		Loc_GPIO_ErrorStatus=gpio_setOutputPinValue(Arr_LED_strConfig [LED_Name].LED_PortNum, Arr_LED_strConfig [LED_Name].LED_PinNum, ( LED_PullUp^ State_));
	else if(Arr_LED_strConfig [LED_Name].LED_PinPullUp_PullDown==GPIO_PUPDR_PULL_DOWN)
		Loc_GPIO_ErrorStatus=gpio_setOutputPinValue(Arr_LED_strConfig [LED_Name].LED_PortNum, Arr_LED_strConfig [LED_Name].LED_PinNum, ( LED_PullDown^ State_));

	if(Loc_GPIO_ErrorStatus !=GPIO_enuOk)
			{
				Loc_LED_ErrorStatus=LED_enuNOK;
			}
			else
			{
				Loc_LED_ErrorStatus=LED_enuOK;
			}
	return Loc_LED_ErrorStatus;
}


LED_tenuErrorStatus led_setGroupofLEDsState (u32 Arr[],u32 ArrSize, u32 LEDs_StatePattern)
{
	u8 Iterator=0;
	LED_tenuErrorStatus Loc_LED_ErrorStatus=0;
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	for(Iterator=0;Iterator<ArrSize;Iterator++)
	{
		if(Arr_LED_strConfig [Arr[Iterator]].LED_PinPullUp_PullDown==GPIO_PUPDR_PULL_UP)
			Loc_GPIO_ErrorStatus=gpio_setOutputPinValue(Arr_LED_strConfig [Arr[Iterator]].LED_PortNum, Arr_LED_strConfig [Arr[Iterator]].LED_PinNum, ( LED_PullUp ^ ((LEDs_StatePattern>>Iterator) & 1)) );
		else if(Arr_LED_strConfig [Arr[Iterator]].LED_PinPullUp_PullDown==GPIO_PUPDR_PULL_DOWN)
			Loc_GPIO_ErrorStatus=gpio_setOutputPinValue(Arr_LED_strConfig [Arr[Iterator]].LED_PortNum, Arr_LED_strConfig [Arr[Iterator]].LED_PinNum, ( LED_PullDown ^ ((LEDs_StatePattern>>Iterator) & 1)));
	}

	if(Loc_GPIO_ErrorStatus !=GPIO_enuOk)
			{
				Loc_LED_ErrorStatus=LED_enuNOK;
			}
			else
			{
				Loc_LED_ErrorStatus=LED_enuOK;
			}
	return Loc_LED_ErrorStatus;
}

void App1_Runnable(void)
{
	static u8 ledstate=0;

	ledstate = !ledstate;

	if(ledstate == 0)
	{
		gpio_setOutputPinValue( GPIO_PORTA, GPIO_Pin_00, GPIO_ODR_PINX_HIGH);
	}
	else
	{
		gpio_setOutputPinValue( GPIO_PORTA, GPIO_Pin_00, GPIO_ODR_PINX_LOW);
	}

}
void App2_Runnable(void)
{
	static u8 ledstate2=0;

	ledstate2 = !ledstate2;

	if(ledstate2 == 0)
	{
		gpio_setOutputPinValue( GPIO_PORTA, GPIO_Pin_01, GPIO_ODR_PINX_HIGH);
	}
	else
	{
		gpio_setOutputPinValue( GPIO_PORTA, GPIO_Pin_01, GPIO_ODR_PINX_LOW);
	}
}
void App3_Runnable(void)
{
	static u8 ledstate3=0;

	ledstate3 = !ledstate3;

	if(ledstate3 == 0)
	{
		gpio_setOutputPinValue( GPIO_PORTA, GPIO_Pin_02, GPIO_ODR_PINX_HIGH);
	}
	else
	{
		gpio_setOutputPinValue( GPIO_PORTA, GPIO_Pin_02, GPIO_ODR_PINX_LOW);
	}
}
