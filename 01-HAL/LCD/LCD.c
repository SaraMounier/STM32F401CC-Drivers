/*************************************************************
 * 
 * Filename: LCD.c
 * Description: Source file of the LCD driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/
#include "./includes/LCD.h"
#include "./includes/LCD_Cfg.h"
#include "./includes/LCD_Priv.h"
#include "./includes/GPIO.h"

static u8 LCD_InitDone=0;
static u8 Req_Type=Req_InitializeLCD;
static u8 State=LCD_enuNotInitialized;
static u8 WriteHandle=0;
static u8 WriteNumberHandle=0;
static u8 CommandHandle=0;
static u8 LCD_InitFlag=0;
static u8 gotoxy_flag=0;

static u8 i=0,j=0;
static u8 Loc_ArrNumbers[10]={0};
static u8 Prev_req_String=0;
static u8 Prev_req_Number=0;

LCD_strInputString_t StringData;
LCD_strInputNumber_t NumberData;
LCD_strCommand_t CommandData;

void LCD_ConfigurePins(void)
{
	GPIO_Pin_Confg  LCD_ConfigObject;
	u8 idx;
	for(idx=0;idx<11;idx++)
	{
		LCD_ConfigObject.GPIO_Port=Arr_LCD_strConfig[idx].LCD_PortNum;
		LCD_ConfigObject.GPIO_Pin=Arr_LCD_strConfig[idx].LCD_PinNum;
		LCD_ConfigObject.GPIO_PinMode=Arr_LCD_strConfig[idx].LCD_PinMode;
		LCD_ConfigObject.GPIO_OutputPinType=Arr_LCD_strConfig[idx].LCD_OutputType;
		LCD_ConfigObject.GPIO_OutputPinSpeed=Arr_LCD_strConfig[idx].LCD_OutputSpeed;
		LCD_ConfigObject.GPIO_PinPullUp_PullDown=Arr_LCD_strConfig[idx].LCD_PinPullUp_PullDown;
		LCD_ConfigObject.GPIO_OutputPinValue=Arr_LCD_strConfig[idx].LCD_Initial_Value;

		Init_Pin_Configure( &LCD_ConfigObject);
	}
}
void LCD_vidInit(void)
{
	//LCD_enuErrorStatus Loc_LCDenuReturnErrStatus=LCD_enuIdle;
	if(LCD_InitDone==0 )
	{
		Req_Type=Req_InitializeLCD;
		switch(LCD_InitFlag)
		{
		case 0:
			Req_Type=Req_SendCommand;
			LCD_SendCommand(SELECTED_FUNCTION_SET);
			LCD_InitFlag++;
			State=LCD_enuNotInitialized;
			if(Req_Type==Req_Idle && State==LCD_enuIdle)
			{Req_Type=Req_InitializeLCD;}
			//Loc_LCDenuReturnErrStatus=LCD_enuNotInitialized;

			break;
		case 1:
			Req_Type=Req_SendCommand;
			LCD_SendCommand(LCD_CLR);
			LCD_InitFlag++;
			State=LCD_enuNotInitialized;
			if(Req_Type==Req_Idle && State==LCD_enuIdle)
			{Req_Type=Req_InitializeLCD;}

			//Loc_LCDe0nuReturnErrStatus=LCD_enuNotInitialized;
			break;
		case 2:
			Req_Type=Req_SendCommand;
			LCD_SendCommand(SELECTED_DISPLAY_ON_OFF_CONTROL);
			LCD_InitFlag++;
			State=LCD_enuNotInitialized;
			if(Req_Type==Req_Idle && State==LCD_enuIdle)
			{Req_Type=Req_InitializeLCD;}
			//Loc_LCDenuReturnErrStatus=LCD_enuNotInitialized;
			break;
		case 3:
			Req_Type=Req_SendCommand;
			LCD_SendCommand(SELECTED_ENTRY_MODE_SET);
			LCD_InitFlag++;
			State=LCD_enuNotInitialized;
			if(Req_Type==Req_Idle && State==LCD_enuIdle)
			{Req_Type=Req_InitializeLCD;}
			//Loc_LCDenuReturnErrStatus=LCD_enuNotInitialized;
			break;
		/*case 4:
			Req_Type=Req_SendCommand;
			LCD_SendCommand(SELECTED_CURSOR_DISPLAY_SHIFT);
			LCD_InitFlag++;
			State=LCD_enuNotInitialized;
			if(Req_Type==Req_Idle && State==LCD_enuIdle)
			{Req_Type=Req_InitializeLCD;}
			//Loc_LCDenuReturnErrStatus=LCD_enuNotInitialized;
			break;*/
		case 4:
			LCD_InitDone=1;
			State=LCD_enuIdle;
			LCD_InitFlag=0;
			Req_Type=Req_Idle;
			//Loc_LCDenuReturnErrStatus=LCD_enuIdle;
			break;
		}
		//if(LCD_InitFlag<4)Req_Type=Req_InitializeLCD;
	}
//return Loc_LCDenuReturnErrStatus;
}

LCD_enuErrorStatus LCD_WriteString(u8* string,u8 length,u8 LCD_X_Position,u8 LCD_Y_Position)
{
	LCD_enuErrorStatus Loc_enuErrStatus=LCD_enuBusy;
	if(State==LCD_enuIdle && LCD_InitDone==1 )
	{
		Req_Type=Req_WriteString;
		StringData.Word=string;
		StringData.length=length;
		StringData.X_Position=LCD_X_Position;
		StringData.Y_Position=LCD_Y_Position;
		StringData.Char_Index=0;
		State=LCD_enuBusy;
		Loc_enuErrStatus=LCD_enuIdle;
	}
	else if(State==LCD_enuBusy)
	{
		Loc_enuErrStatus=LCD_enuBusy;
	}
	else if(State==LCD_enuNotInitialized)
	{
		Loc_enuErrStatus=LCD_enuNotInitialized;
	}
	return Loc_enuErrStatus;

}

void Req_Write_String_Handle(void)
{
	Req_Type=Req_WriteString;
	u8 LocCommand=0;
	switch(WriteHandle)
	{
	case 0:
	if (StringData.X_Position>=0 && StringData.X_Position<=LCD_VISABLERANGE && (StringData.Y_Position==FIRST_LINE || StringData.Y_Position==SECOND_LINE))
	{
		if(StringData.Y_Position== FIRST_LINE)
		{
			Req_Type=Req_SendCommand;
			LocCommand=FIRST_LINE+StringData.X_Position;
			State=LCD_enuIdle;
			LCD_SendCommand(MASK_DDRAM | LocCommand);
			gotoxy_flag=1;
			Prev_req_String=Req_WriteString;
		}
		else if(StringData.Y_Position== SECOND_LINE)
		{
			Req_Type=Req_SendCommand;
			LocCommand=SECOND_LINE + StringData.X_Position;
			State=LCD_enuIdle;
			LCD_SendCommand(MASK_DDRAM | LocCommand);
			gotoxy_flag=1;
			Prev_req_String=Req_WriteString;
		}
	}
	if(State==LCD_enuBusy && gotoxy_flag==0)
	{
		State=LCD_enuBusy;
		Req_Type=Req_WriteString;
	}
	else
	{
		Req_Type=Req_SendCommand;
	}
	WriteHandle++;

	break;
	case 1:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_RS_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RS_PIN].LCD_PinNum, GPIO_ODR_PINX_HIGH);
	WriteHandle++;
	State=LCD_enuBusy;
	Req_Type=Req_WriteString;
	break;

	case 2:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_RW_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RW_PIN].LCD_PinNum, GPIO_ODR_PINX_LOW);
	WriteHandle++;
	State=LCD_enuBusy;
	Req_Type=Req_WriteString;
	break;

	case 3:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_EN_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_EN_PIN].LCD_PinNum, GPIO_ODR_PINX_HIGH);
	WriteHandle++;
	State=LCD_enuBusy;
	Req_Type=Req_WriteString;
	break;

	case 4:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D0_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D0_PIN].LCD_PinNum,(StringData.Word[StringData.Char_Index]>>LCD_D0_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D1_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D1_PIN].LCD_PinNum,(StringData.Word[StringData.Char_Index]>>LCD_D1_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D2_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D2_PIN].LCD_PinNum,(StringData.Word[StringData.Char_Index]>>LCD_D2_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D3_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D3_PIN].LCD_PinNum,(StringData.Word[StringData.Char_Index]>>LCD_D3_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D4_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D4_PIN].LCD_PinNum,(StringData.Word[StringData.Char_Index]>>LCD_D4_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D5_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D5_PIN].LCD_PinNum,(StringData.Word[StringData.Char_Index]>>LCD_D5_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D6_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D6_PIN].LCD_PinNum,(StringData.Word[StringData.Char_Index]>>LCD_D6_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D7_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D7_PIN].LCD_PinNum,(StringData.Word[StringData.Char_Index]>>LCD_D7_PIN)&(0x1));
	State=LCD_enuBusy;
	Req_Type=Req_WriteString;
	WriteHandle++;
	break;
	case 5:

	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_EN_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_EN_PIN].LCD_PinNum, GPIO_ODR_PINX_LOW);
	State=LCD_enuBusy;
	Req_Type=Req_WriteString;
	WriteHandle++;
	break;
	case 6:
	StringData.Char_Index ++;
	State=LCD_enuBusy;
	Req_Type=Req_WriteString;
	if(StringData.Char_Index == StringData.length)
	{
	WriteHandle++;
	}
	else {
		WriteHandle=1;
	}
	break;

	case 7:
	WriteHandle=0;
	State=LCD_enuIdle;
	Req_Type=Req_Idle;
	break;
	}
}

LCD_enuErrorStatus LCD_WriteNumber (u32 u32Number,u8 LCD_X_Position,u8 LCD_Y_Position)
{
	LCD_enuErrorStatus Loc_enuErrStatus=LCD_enuBusy;
	if(State==LCD_enuIdle && LCD_InitDone==1 )
	{
		Req_Type=Req_WriteNumber;
		NumberData.Number=u32Number;
		//NumberData.length=length;
		NumberData.X_Position=LCD_X_Position;
		NumberData.Y_Position=LCD_Y_Position;
		State=LCD_enuBusy;
		Loc_enuErrStatus=LCD_enuIdle;
	}
	else if(State==LCD_enuBusy)
	{
		Loc_enuErrStatus=LCD_enuBusy;
	}
	else if(State==LCD_enuNotInitialized)
	{
		Loc_enuErrStatus=LCD_enuNotInitialized;
	}
	return Loc_enuErrStatus;

}

void Req_Write_Number_Handle(void)
{
	Req_Type=Req_WriteNumber;
	u8 LocCommand=0;
	u8 perres;
//	static u8 i=0,j=0;
//	static u8 Loc_ArrNumbers[5]={0};
	switch(WriteNumberHandle)
	{
	case 0:
	if (NumberData.X_Position>=0 && NumberData.X_Position<=LCD_VISABLERANGE && (NumberData.Y_Position==FIRST_LINE || NumberData.Y_Position==SECOND_LINE))
	{
		if(NumberData.Y_Position== FIRST_LINE)
		{
			Req_Type=Req_SendCommand;
			LocCommand=FIRST_LINE+NumberData.X_Position;
			State=LCD_enuIdle;
			LCD_SendCommand(MASK_DDRAM | LocCommand);
			gotoxy_flag=1;
			Prev_req_Number=Req_WriteNumber;
			WriteNumberHandle++;

		}
		else if(NumberData.Y_Position== SECOND_LINE)
		{
			Req_Type=Req_SendCommand;
			LocCommand=SECOND_LINE + NumberData.X_Position;
			State=LCD_enuIdle;
			LCD_SendCommand(MASK_DDRAM | LocCommand);
			gotoxy_flag=1;
			Prev_req_Number=Req_WriteNumber;
			WriteNumberHandle++;

		}
	}
	if(State==LCD_enuBusy && gotoxy_flag==0)
	{
		State=LCD_enuBusy;
		Req_Type=Req_WriteNumber;

	}
	else
	{
		Req_Type=Req_SendCommand;
	}

	break;

	case 1:
	if(NumberData.Number > 0)
	{
		while(NumberData.Number != 0 && i<10 )
		{
			perres=NumberData.Number % 10;
			NumberData.Number /= 10;
			Loc_ArrNumbers[i]=perres + ZERO_ASCII;
			i++;
		}
	}
	else if(NumberData.Number==0)
	{
		Loc_ArrNumbers[0]= ZERO_ASCII;
	}
	State=LCD_enuBusy;
	Req_Type=Req_WriteNumber;
	WriteNumberHandle++;
	break;

	case 2:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_RS_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RS_PIN].LCD_PinNum, GPIO_ODR_PINX_HIGH);
	WriteNumberHandle++;
	State=LCD_enuBusy;
	Req_Type=Req_WriteNumber;
	break;

	case 3:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_RW_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RW_PIN].LCD_PinNum, GPIO_ODR_PINX_LOW);
	WriteNumberHandle++;
	State=LCD_enuBusy;
	Req_Type=Req_WriteNumber;
	break;

	case 4:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_EN_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_EN_PIN].LCD_PinNum, GPIO_ODR_PINX_HIGH);
	WriteNumberHandle++;
	State=LCD_enuBusy;
	Req_Type=Req_WriteNumber;
	break;

	case 5:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D0_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D0_PIN].LCD_PinNum,((Loc_ArrNumbers[i-j-1])>>LCD_D0_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D1_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D1_PIN].LCD_PinNum,((Loc_ArrNumbers[i-j-1])>>LCD_D1_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D2_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D2_PIN].LCD_PinNum,((Loc_ArrNumbers[i-j-1])>>LCD_D2_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D3_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D3_PIN].LCD_PinNum,((Loc_ArrNumbers[i-j-1])>>LCD_D3_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D4_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D4_PIN].LCD_PinNum,((Loc_ArrNumbers[i-j-1])>>LCD_D4_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D5_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D5_PIN].LCD_PinNum,((Loc_ArrNumbers[i-j-1])>>LCD_D5_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D6_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D6_PIN].LCD_PinNum,((Loc_ArrNumbers[i-j-1])>>LCD_D6_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D7_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D7_PIN].LCD_PinNum,((Loc_ArrNumbers[i-j-1])>>LCD_D7_PIN)&(0x1));
	State=LCD_enuBusy;
	Req_Type=Req_WriteNumber;
	WriteNumberHandle++;
	break;

	case 6:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_EN_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_EN_PIN].LCD_PinNum, GPIO_ODR_PINX_LOW);
	State=LCD_enuBusy;
	Req_Type=Req_WriteNumber;
	WriteNumberHandle++;
	break;

	case 7:
	State=LCD_enuBusy;
	Req_Type=Req_WriteNumber;
	if(j==(i-1))
	{
	WriteNumberHandle++;
	}
	else
	{
	j++;
	WriteNumberHandle=2;
	}
	break;

	case 8:
	WriteNumberHandle=0;
	i=j=0;
	State=LCD_enuIdle;
	Req_Type=Req_Idle;
	break;
	}

}

LCD_enuErrorStatus LCD_SendCommand(u8 LCD_Command )
{
	LCD_enuErrorStatus Loc_enuErrStatus=LCD_enuBusy;
	if(State==LCD_enuIdle || State==LCD_enuNotInitialized)
	{
		Req_Type=Req_SendCommand;
		CommandData.command=LCD_Command;
		State=LCD_enuBusy;
		Loc_enuErrStatus=LCD_enuBusy;
	}
	else if(State==LCD_enuBusy)
	{
		Loc_enuErrStatus=LCD_enuBusy;
	}
	else if(State==LCD_enuNotInitialized)
	{
		Loc_enuErrStatus=LCD_enuNotInitialized;
	}
	return Loc_enuErrStatus;

}
void Req_Send_Command_Handle(void)
{
	Req_Type=Req_SendCommand;
	switch(CommandHandle)
	{
	case 0:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_RS_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RS_PIN].LCD_PinNum, GPIO_ODR_PINX_LOW);
	Req_Type=Req_SendCommand;
	State=LCD_enuBusy;
	CommandHandle++;
	break;

	case 1:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_RW_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_RW_PIN].LCD_PinNum, GPIO_ODR_PINX_LOW);
	Req_Type=Req_SendCommand;
	State=LCD_enuBusy;
	CommandHandle++;
	break;
	case 2:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_EN_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_EN_PIN].LCD_PinNum, GPIO_ODR_PINX_HIGH);
	Req_Type=Req_SendCommand;
	State=LCD_enuBusy;
	CommandHandle++;
	break;
	case 3:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D0_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D0_PIN].LCD_PinNum,(CommandData.command>>LCD_D0_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D1_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D1_PIN].LCD_PinNum,(CommandData.command>>LCD_D1_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D2_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D2_PIN].LCD_PinNum,(CommandData.command>>LCD_D2_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D3_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D3_PIN].LCD_PinNum,(CommandData.command>>LCD_D3_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D4_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D4_PIN].LCD_PinNum,(CommandData.command>>LCD_D4_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D5_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D5_PIN].LCD_PinNum,(CommandData.command>>LCD_D5_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D6_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D6_PIN].LCD_PinNum,(CommandData.command>>LCD_D6_PIN)&(0x1));
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_D7_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_D7_PIN].LCD_PinNum,(CommandData.command>>LCD_D7_PIN)&(0x1));
	Req_Type=Req_SendCommand;
	State=LCD_enuBusy;
	CommandHandle++;
	break;
	case 4:
	gpio_setOutputPinValue(Arr_LCD_strConfig[LCD_EN_PIN].LCD_PortNum, Arr_LCD_strConfig[LCD_EN_PIN].LCD_PinNum, GPIO_ODR_PINX_LOW);
	State=LCD_enuBusy;
	Req_Type=Req_SendCommand;
	CommandHandle++;
	break;
	case 5:
	if(gotoxy_flag==1 && Prev_req_Number==Req_WriteNumber)
	{
		gotoxy_flag=0;
		Req_Type=Req_WriteNumber;
		WriteNumberHandle=1;
		State=LCD_enuBusy;
		Prev_req_Number=0;
	}
	else if(gotoxy_flag==1 && Prev_req_String==Req_WriteString)
	{
		gotoxy_flag=0;
		Req_Type=Req_WriteString;
		State=LCD_enuBusy;
		Prev_req_String=0;
	}
	else
	{
		Req_Type=Req_Idle;
		State=LCD_enuIdle;
	}
	CommandHandle=0;
	break;
	}
}

 void LCD_vidTask(void)
{
	switch (Req_Type)
	{
	case Req_InitializeLCD:
		if(LCD_InitDone != 1)
		{
			LCD_vidInit();
		}
		break;
	case Req_SendCommand:
		if(State==LCD_enuBusy || State == LCD_enuNotInitialized)
		{
			Req_Send_Command_Handle();
		}
		break;
//	case Req_ClearChar:
//		break;
	case Req_WriteString:
		if(State==LCD_enuBusy && LCD_InitDone == 1)
		{
			Req_Write_String_Handle();
		}
		break;
	case Req_WriteNumber:
		if((State==LCD_enuBusy/*||State==LCD_enuIdle*/) && LCD_InitDone == 1)
		{
			Req_Write_Number_Handle();
		}
		break;
	case Req_Idle:
		if(LCD_InitDone==0){Req_Type=Req_InitializeLCD;}
	    if (State==LCD_enuBusy && gotoxy_flag==1){Req_Type=Req_SendCommand;}
	    if (State==LCD_enuBusy && gotoxy_flag==0 &&Prev_req_String==Req_WriteString){Req_Type=Req_WriteString;}
	    if (State==LCD_enuBusy && gotoxy_flag==0 &&Prev_req_Number==Req_WriteNumber){Req_Type=Req_WriteNumber;}
		else{State=LCD_enuIdle; }
		break;
	default:
		break;
		/*Invalid Req*/
	}
}
