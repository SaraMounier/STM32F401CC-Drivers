/*************************************************************
 * 
 * Filename: GPIO.c
 * Description: Source file of the GPIO driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "includes\GPIO.h"
#include "includes\STD_TYPES.h"

//GPIO_registers_t *const gpio =(GPIO_registers_t *const) (GPIO_BASE_ADDRESS);

static void SET_2B(u32* Reg,u32 Pin_Num,u32 Desired_Pin_Value )
{
	u32 TempVar;
	TempVar = *(Reg) & ~(CLR_MASK <<Pin_Num);
	*(Reg) = TempVar | (Desired_Pin_Value<<Pin_Num);
}

static void SET_4B(u32* Reg,u32 Pin_Num,u32 Desired_Pin_Value )
{
	u32 TempVar;
	TempVar = *(Reg) & ~(CLR_MASK_4B <<Pin_Num);
	*(Reg) = TempVar | (Desired_Pin_Value<<Pin_Num);
}
static u32 GET_2B(u32* Reg,u32 Pin_Num )
{
	return (((*Reg) >> (Pin_Num)) & 0b11);
}

static void SET_PORT(u32* Reg,u32 Desired_Port_Value )
{
	u32 TempVar;
	TempVar = *(Reg) & ~(GPIO_ODR_MAX_PORTX_VALUE);
	*(Reg) = TempVar | (Desired_Port_Value);
}

void Init_Pin_Configure(GPIO_Pin_Confg * Struct_object)
{
	gpio_setPinMode( Struct_object->GPIO_Port, Struct_object->GPIO_Pin, Struct_object->GPIO_PinMode);

	gpio_setPinPullUp_PullDown(Struct_object->GPIO_Port, Struct_object->GPIO_Pin, Struct_object->GPIO_PinPullUp_PullDown);
	if(Struct_object->GPIO_PinMode==GPIO_MODE_GENERAL_PURPOSE_OUTPUT)
	{
	gpio_setOutputPinTyPe(Struct_object->GPIO_Port,Struct_object->GPIO_Pin, Struct_object->GPIO_OutputPinType);
	gpio_setOutputPinSpeed(Struct_object->GPIO_Port, Struct_object->GPIO_Pin, Struct_object->GPIO_OutputPinSpeed);
	gpio_setOutputPinValue(Struct_object->GPIO_Port, Struct_object->GPIO_Pin, Struct_object->GPIO_OutputPinValue);
	}
	if(Struct_object->GPIO_PinMode==GPIO_MODE_ALTERNATIVE_FUNCTION)
	{
	gpio_setPinAlternativeFunction(Struct_object->GPIO_Port,Struct_object->GPIO_Pin,Struct_object->GPIO_AlternateFunctionNumber);
	}
}
GPIO_ErrorStatus_t gpio_setPinMode(void* GPIO_PORTx, u32 GPIO_Pin_x, u32  GPIO_Pin_Direction)
{
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	if(GPIO_PORTx !=NULL)
	{
		if(GPIO_PORTx == GPIO_PORTA ||GPIO_PORTx == GPIO_PORTB ||GPIO_PORTx == GPIO_PORTC ||GPIO_PORTx == GPIO_PORTD ||GPIO_PORTx == GPIO_PORTE ||GPIO_PORTx == GPIO_PORTH )
		{
			if( GPIO_Pin_x >=GPIO_MODER00 && GPIO_Pin_x <= (GPIO_MODER15/2) )
			{
				if( GPIO_Pin_Direction >=GPIO_MODE_INPUT && GPIO_Pin_Direction <=GPIO_MODE_ANALOG )
				{
					SET_2B(&(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_MODER) , (GPIO_Pin_x *2), GPIO_Pin_Direction );
					Loc_GPIO_ErrorStatus= GPIO_enuOk;
				}
				else
				{
					Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinDirection;
				}
			}
			else
			{
				Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinNumber;
			}
		}
		else
		{
			Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortNumber;
		}
	}
	else
	{
		Loc_GPIO_ErrorStatus= GPIO_enuNullPointer;
	}
	return Loc_GPIO_ErrorStatus;
}


GPIO_ErrorStatus_t gpio_setOutputPinTyPe(void* GPIO_PORTx,u32  GPIO_Pin_x,u32 GPIO_OUTPUT_)
{
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	u32 Loc_PinModeValue = GET_2B(&(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_MODER) , (GPIO_Pin_x *2));
	if(GPIO_PORTx !=NULL)
	{
		if(Loc_PinModeValue==GPIO_MODE_INPUT || Loc_PinModeValue==GPIO_MODE_ANALOG)
		{
			Loc_GPIO_ErrorStatus=GPIO_enuInvalidPinMode;
		}
		else
		{
			if(GPIO_PORTx == GPIO_PORTA ||GPIO_PORTx == GPIO_PORTB ||GPIO_PORTx == GPIO_PORTC ||GPIO_PORTx == GPIO_PORTD ||GPIO_PORTx == GPIO_PORTE ||GPIO_PORTx == GPIO_PORTH )
			{
				if( GPIO_Pin_x >=GPIO_OT00 && GPIO_Pin_x <=GPIO_OT15 )
				{
					if( GPIO_OUTPUT_ == GPIO_OUTPUT_OPEN_DRAIN )
					{
						(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_OTYPER) |=(1<<GPIO_Pin_x);
						Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
					else if( GPIO_OUTPUT_ == GPIO_OUTPUT_PUSH_PULL)
					{
						(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_OTYPER) &=~(1<<GPIO_Pin_x);
						Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
					else
					{
						Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinOutputConfiguration;
					}
				}
				else
				{
					Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinNumber;
				}
			}
			else
			{
				Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortNumber;
			}
		}
	}
	else
	{
		Loc_GPIO_ErrorStatus= GPIO_enuNullPointer;
	}

	return Loc_GPIO_ErrorStatus;
}


GPIO_ErrorStatus_t gpio_setOutputPinSpeed(void* GPIO_PORTx,u32  GPIO_Pin_x,u32 GPIO_OUTPUT_X_SPEED)
{
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	u32 Loc_PinModeValue = GET_2B(&(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_MODER) , (GPIO_Pin_x *2));
	if(GPIO_PORTx !=NULL)
	{
		if(Loc_PinModeValue==GPIO_MODE_INPUT || Loc_PinModeValue==GPIO_MODE_ANALOG)
		{
			Loc_GPIO_ErrorStatus=GPIO_enuInvalidPinMode;
		}
		else
		{
			if(GPIO_PORTx == GPIO_PORTA ||GPIO_PORTx == GPIO_PORTB ||GPIO_PORTx == GPIO_PORTC ||GPIO_PORTx == GPIO_PORTD ||GPIO_PORTx == GPIO_PORTE ||GPIO_PORTx == GPIO_PORTH )
			{
				if( GPIO_Pin_x >= GPIO_OSPEEDR00 && GPIO_Pin_x <= (GPIO_OSPEEDR15/2) )
				{
					if( GPIO_OUTPUT_X_SPEED >=GPIO_OUTPUT_lOW_SPEED && GPIO_OUTPUT_X_SPEED <=GPIO_OUTPUT_VERY_HIGH_SPEED )
					{
						SET_2B(&(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_OSPEEDR) , (GPIO_Pin_x *2), GPIO_OUTPUT_X_SPEED );
						Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
					else
					{
						Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinSpeedConfiguration;
					}
				}
				else
				{
					Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinNumber;
				}
			}
			else
			{
				Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortNumber;
			}
		}
	}
	else
	{
		Loc_GPIO_ErrorStatus= GPIO_enuNullPointer;
	}
	return Loc_GPIO_ErrorStatus;
}


GPIO_ErrorStatus_t gpio_setPinPullUp_PullDown(void* GPIO_PORTx,u32 GPIO_Pin_x,u32 GPIO_PUPDR_X)
{
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus;
	u32 Loc_PinModeValue = GET_2B(&(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_MODER) , (GPIO_Pin_x *2));

	if(GPIO_PORTx !=NULL)
	{
		if(GPIO_PORTx == GPIO_PORTA ||GPIO_PORTx == GPIO_PORTB ||GPIO_PORTx == GPIO_PORTC ||GPIO_PORTx == GPIO_PORTD ||GPIO_PORTx == GPIO_PORTE ||GPIO_PORTx == GPIO_PORTH )
		{
			if( GPIO_Pin_x >= GPIO_PUPDR00 && GPIO_Pin_x <= (GPIO_PUPDR15/2) )
			{
				if( GPIO_PUPDR_X >=GPIO_PUPDR_NO_PULL_UP_NO_PULL_DOWN && GPIO_PUPDR_X <=GPIO_PUPDR_PULL_DOWN )
				{
					/*checkkkk*/
					if(Loc_PinModeValue==GPIO_MODE_ANALOG && GPIO_PUPDR_X != GPIO_PUPDR_NO_PULL_UP_NO_PULL_DOWN)
					{
						Loc_GPIO_ErrorStatus=GPIO_enuInvalidPinMode;
					}
					else
					{
						SET_2B(&(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_PUPDR) , GPIO_Pin_x, GPIO_PUPDR_X );
						Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
				}
				else
				{
					Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinPullConfiguration;
				}
			}
			else
			{
				Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinNumber;
			}
		}
		else
		{
			Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortNumber;
		}
	}
	else
	{
		Loc_GPIO_ErrorStatus= GPIO_enuNullPointer;
	}
	return Loc_GPIO_ErrorStatus;
}

GPIO_ErrorStatus_t gpio_getPinInputData(void* GPIO_PORTx,u32 GPIO_Pin_x,u32* GPIO_IDR_Pinx_Value)
{
	u32 Loc_PinModeValue = GET_2B(&(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_MODER) , (GPIO_Pin_x*2));
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	if(Loc_PinModeValue==GPIO_MODE_INPUT)
	{
		if(GPIO_PORTx !=NULL)
		{
			if(GPIO_PORTx == GPIO_PORTA ||GPIO_PORTx == GPIO_PORTB ||GPIO_PORTx == GPIO_PORTC ||GPIO_PORTx == GPIO_PORTD ||GPIO_PORTx == GPIO_PORTE ||GPIO_PORTx == GPIO_PORTH )
			{
				if( GPIO_Pin_x >= GPIO_IDR00 && GPIO_Pin_x <=GPIO_IDR15 )
				{
					*GPIO_IDR_Pinx_Value=((( (((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_IDR)  >> GPIO_Pin_x ) )& 0x1);
					Loc_GPIO_ErrorStatus= GPIO_enuOk;
				}
				else
				{
					Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinNumber;
				}
			}
			else
			{
				Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortNumber;
			}
		}
		else
		{
			Loc_GPIO_ErrorStatus= GPIO_enuNullPointer;
		}
	}
	else
	{
		Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinMode;
	}
	return Loc_GPIO_ErrorStatus;
}
GPIO_ErrorStatus_t gpio_getPortInputData(void* GPIO_PORTx,u32* GPIO_IDR_Portx_Value)
{
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	u8 Iterator=0;
	u32 Loc_PinModeValue;
	for(Iterator=0; Iterator <=GPIO_MODER15; Iterator++)
	{
		Loc_PinModeValue = GET_2B(&(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_MODER) , Iterator);
		if(Loc_PinModeValue==GPIO_MODE_GENERAL_PURPOSE_OUTPUT)
		{
			Loc_GPIO_ErrorStatus=GPIO_enuInvalidPinMode;
			break;
		}
		else
		{
			Iterator++;
		}
	}

	if(Loc_GPIO_ErrorStatus != GPIO_enuInvalidPinMode)
	{
		if(GPIO_PORTx !=NULL)
		{
			if(GPIO_PORTx == GPIO_PORTA ||GPIO_PORTx == GPIO_PORTB ||GPIO_PORTx == GPIO_PORTC ||GPIO_PORTx == GPIO_PORTD ||GPIO_PORTx == GPIO_PORTE ||GPIO_PORTx == GPIO_PORTH )
			{
					*GPIO_IDR_Portx_Value= (( (((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_IDR) )& 0x0000ffff);
					Loc_GPIO_ErrorStatus= GPIO_enuOk;
			}
			else
			{
				Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortNumber;
			}
		}
		else
		{
			Loc_GPIO_ErrorStatus= GPIO_enuNullPointer;
		}
	}
		return Loc_GPIO_ErrorStatus;
}
GPIO_ErrorStatus_t gpio_setOutputPinValue(void* GPIO_PORTx,u32 GPIO_Pin_x,u32 GPIO_ODR_PINX_VAL)
{
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	u32 Loc_PinModeValue = GET_2B(&(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_MODER) ,(GPIO_Pin_x*2));
	if(GPIO_PORTx !=NULL)
	{
		if(Loc_PinModeValue==(u32)GPIO_MODE_INPUT)
		{
			Loc_GPIO_ErrorStatus=GPIO_enuInvalidPinMode;
		}
		else
		{
			if(GPIO_PORTx == GPIO_PORTA ||GPIO_PORTx == GPIO_PORTB ||GPIO_PORTx == GPIO_PORTC ||GPIO_PORTx == GPIO_PORTD ||GPIO_PORTx == GPIO_PORTE ||GPIO_PORTx == GPIO_PORTH )
			{
				if( GPIO_Pin_x >=GPIO_ODR00 && GPIO_Pin_x <=GPIO_ODR15 )
				{
					if( GPIO_ODR_PINX_VAL == GPIO_ODR_PINX_HIGH )
					{
						(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_ODR) |=(1<<GPIO_Pin_x);
						Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
					else if( GPIO_ODR_PINX_VAL == GPIO_ODR_PINX_LOW)
					{
						(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_ODR) &=~(1<<GPIO_Pin_x);
						Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
					else
					{
						Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinOutputValue;
					}
				}
				else
				{
					Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinNumber;
				}
			}
			else
			{
				Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortNumber;
			}
		}
	}
	else
	{
		Loc_GPIO_ErrorStatus= GPIO_enuNullPointer;
	}

return Loc_GPIO_ErrorStatus;
}


 GPIO_ErrorStatus_t gpio_setOutputPortValue(void* GPIO_PORTx,u32 GPIO_ODR_PORTX_VAL)
{
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	u32 Loc_PinModeValue;
	u8 Iterator=0;
	for(Iterator=0; Iterator <=GPIO_MODER15; Iterator++)
	{
		Loc_PinModeValue = GET_2B(&(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_MODER) , Iterator);
		if(Loc_PinModeValue==GPIO_MODE_INPUT)
		{
			Loc_GPIO_ErrorStatus=GPIO_enuInvalidPinMode;
			break;
		}
		else
		{
			Iterator++;
		}
	}

	if(Loc_GPIO_ErrorStatus != GPIO_enuInvalidPinMode)
	{
		if(GPIO_PORTx !=NULL)
		{
			if(GPIO_PORTx == GPIO_PORTA ||GPIO_PORTx == GPIO_PORTB ||GPIO_PORTx == GPIO_PORTC ||GPIO_PORTx == GPIO_PORTD ||GPIO_PORTx == GPIO_PORTE ||GPIO_PORTx == GPIO_PORTH )
			{
				if( GPIO_ODR_PORTX_VAL>= GPIO_ODR_MIN_PORTX_VALUE && GPIO_ODR_PORTX_VAL<=GPIO_ODR_MAX_PORTX_VALUE )
				{
					SET_PORT((&((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_ODR), GPIO_ODR_PORTX_VAL);
					Loc_GPIO_ErrorStatus= GPIO_enuOk;
				}
				else
				{
					Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortOutputValue;
				}
			}
			else
			{
				Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortNumber;
			}
		}
		else
		{
			Loc_GPIO_ErrorStatus= GPIO_enuNullPointer;
		}
	}
	return Loc_GPIO_ErrorStatus;
}

GPIO_ErrorStatus_t gpio_atomicSet_ResetOutputPinValue(u32 ATOMIC_,void* GPIO_PORTx,u32 GPIO_Pin_x,u32 GPIO_BSRR_BXX_Value)
{
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	u32 Loc_PinModeValue=0;
	if(GPIO_Pin_x >= GPIO_Pin_00 && GPIO_Pin_x <= GPIO_Pin_15)
	{
		Loc_PinModeValue = (u8)GET_2B(&(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_MODER) , (GPIO_Pin_x*2)); /*to convert BSX TO MODERX*/
	}
	else
	{
		Loc_GPIO_ErrorStatus=GPIO_enuInvalidPinNumber;
	}

	if(GPIO_PORTx !=NULL)
	{
		if(Loc_PinModeValue==GPIO_MODE_INPUT)
		{
			Loc_GPIO_ErrorStatus=GPIO_enuInvalidPinMode;
		}
		else
		{
			if(GPIO_PORTx == GPIO_PORTA ||GPIO_PORTx == GPIO_PORTB ||GPIO_PORTx == GPIO_PORTC ||GPIO_PORTx == GPIO_PORTD ||GPIO_PORTx == GPIO_PORTE ||GPIO_PORTx == GPIO_PORTH )
			{
				if( ATOMIC_ == ATOMIC_BSX_SET)
				{
					if(GPIO_BSRR_BXX_Value==GPIO_BSRR_BSX_SET_ODRX_BIT)
					{
						(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_BSRR)|=(1<<GPIO_Pin_x);
						Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
					else if(GPIO_BSRR_BXX_Value==GPIO_BSRR_BSX_NO_ACTION_ODRX_BIT)
					{
						(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_BSRR) &=~(1<<GPIO_Pin_x);
						Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
					else
					{
						Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinOutputValue;
					}
				}
				else if( ATOMIC_ == ATOMIC_BRX_RESET)
				{
					if(GPIO_BSRR_BXX_Value==GPIO_BSRR_BRX_RESET_ODRX_BIT)
					{
						(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_BSRR)|=(1<< (GPIO_Pin_x+GPIO_BR00));
						Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
					else if(GPIO_BSRR_BXX_Value==GPIO_BSRR_BRX_NO_ACTION_ODRX_BIT)
					{
						(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_BSRR) &= ~(1<<( GPIO_Pin_x+GPIO_BR00));
						Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
					else
					{
						Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinOutputValue;
					}
				}
				else
				{
					Loc_GPIO_ErrorStatus= GPIO_enuInvalidAtomicOperation;
				}
			}
			else
			{
				Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortNumber;
			}
		}
	}
	else
	{
		Loc_GPIO_ErrorStatus= GPIO_enuNullPointer;
	}

	return Loc_GPIO_ErrorStatus;
}


GPIO_ErrorStatus_t gpio_setLockRegPinValue(void*  GPIO_PORTx,u32 GPIO_Pin_x,u32 GPIO_PORT_CFG_)
{
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	if((((((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_LCKR) & (1<<(GPIO_LCKK)))) == 0)
	{
		if(GPIO_PORTx !=NULL)
		{
			if(GPIO_PORTx == GPIO_PORTA ||GPIO_PORTx == GPIO_PORTB ||GPIO_PORTx == GPIO_PORTC ||GPIO_PORTx == GPIO_PORTD ||GPIO_PORTx == GPIO_PORTE ||GPIO_PORTx == GPIO_PORTH )
			{
				if( GPIO_Pin_x >= GPIO_LCK00 && GPIO_Pin_x<= GPIO_LCK15 )
				{
					if(GPIO_PORT_CFG_ == GPIO_PORT_CFG_LOCKED)
					{
					(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_LCKR) |= 1<<(GPIO_Pin_x);
					Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
					else if(GPIO_PORT_CFG_ == GPIO_PORT_CFG_NOT_LOCKED)
					{
					(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_LCKR) &= ~(1<<(GPIO_Pin_x));
					Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
					else
					{
						Loc_GPIO_ErrorStatus= GPIO_enuInvalidLockConfiguration;
					}
				}
				else
				{
					Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinNumber;
				}
			}
			else
			{
				Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortNumber;
			}
		}
		else
		{
			Loc_GPIO_ErrorStatus= GPIO_enuNullPointer;
		}
	}
	else
	{
		Loc_GPIO_ErrorStatus= GPIO_enuLockedRegister;
	}
	return Loc_GPIO_ErrorStatus;
}

GPIO_ErrorStatus_t gpio_setLockRegPortValue(void* GPIO_PORTx,u32 GPIO_PORT_CFG_Val)
{
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus;
	if(((((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_LCKR) &(1<<(GPIO_LCKK))) ==0)
	{
		if(GPIO_PORTx !=NULL)
		{
			if(GPIO_PORTx == GPIO_PORTA ||GPIO_PORTx == GPIO_PORTB ||GPIO_PORTx == GPIO_PORTC ||GPIO_PORTx == GPIO_PORTD ||GPIO_PORTx == GPIO_PORTE ||GPIO_PORTx == GPIO_PORTH )
			{
				if( GPIO_PORT_CFG_Val>= GPIO_ODR_MIN_PORTX_VALUE && GPIO_PORT_CFG_Val<=GPIO_ODR_MAX_PORTX_VALUE )
				{
					SET_PORT((&((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_LCKR), GPIO_PORT_CFG_Val );
					Loc_GPIO_ErrorStatus= GPIO_enuOk;
				}
				else
				{
					Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortLockValue;
				}
			}
			else
			{
				Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortNumber;
			}
		}
		else
		{
			Loc_GPIO_ErrorStatus= GPIO_enuNullPointer;
		}
	}
	else
	{
		Loc_GPIO_ErrorStatus=GPIO_enuLockedRegister;
	}
	return Loc_GPIO_ErrorStatus;
}


GPIO_ErrorStatus_t gpio_Enablelock_LockReg(void* GPIO_PORTx,u32 GPIO_LCK_KEY_)
{
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	u32 LocalVar=0;
	if(GPIO_PORTx !=NULL)
	{
		if(GPIO_PORTx == GPIO_PORTA ||GPIO_PORTx == GPIO_PORTB ||GPIO_PORTx == GPIO_PORTC ||GPIO_PORTx == GPIO_PORTD ||GPIO_PORTx == GPIO_PORTE ||GPIO_PORTx == GPIO_PORTH )
		{
			if( GPIO_LCK_KEY_== GPIO_LOCK_KEY_ACTIVE)
			{
				//LocalVar |= 1<<GPIO_LCKK; /*write 1 in LCKK pin*/
				(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_LCKR)|= 1<<GPIO_LCKK;;

				//LocalVar=0;
				//LocalVar &= ~(1<<GPIO_LCKK); /*write 0 in LCKK pin*/
				(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_LCKR) &= ~(1<<GPIO_LCKK);

				//LocalVar=0;
				//LocalVar |= 1<<GPIO_LCKK; /*write 1 in LCKK pin*/
				(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_LCKR) |= 1<<GPIO_LCKK;

				LocalVar=(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_LCKR); /*Read LCKR register*/

				Loc_GPIO_ErrorStatus= GPIO_enuOk;
			}
			else if(GPIO_LCK_KEY_== GPIO_LOCK_KEY_NOT_ACTIVE)
			{
				(((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_LCKR) &= ~(1<<GPIO_LCKK);
			}
			else
			{
				Loc_GPIO_ErrorStatus= GPIO_enuInvalidLockKeyValue;
			}
		}
		else
		{
			Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortNumber;
		}
	}
	else
	{
		Loc_GPIO_ErrorStatus= GPIO_enuNullPointer;
	}
	return Loc_GPIO_ErrorStatus;

}


/*GPIO_Pin_x*/
GPIO_ErrorStatus_t gpio_setPinAlternativeFunction(void* GPIO_PORTx,u32 GPIO_Pin_x,u32 GPIO_AF_NUM)
{
	GPIO_ErrorStatus_t Loc_GPIO_ErrorStatus=0;
	u32 Loc_PinModeValue=0;
	Loc_PinModeValue= GET_2B((&((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_MODER) ,(GPIO_Pin_x*2));
/*check*/
	if(Loc_PinModeValue != GPIO_MODE_ALTERNATIVE_FUNCTION)
	{
		Loc_GPIO_ErrorStatus=GPIO_enuInvalidPinMode;
	}
	else
	{
		if(GPIO_PORTx !=NULL)
		{
			if(GPIO_PORTx == GPIO_PORTA ||GPIO_PORTx == GPIO_PORTB ||GPIO_PORTx == GPIO_PORTC ||GPIO_PORTx == GPIO_PORTD ||GPIO_PORTx == GPIO_PORTE ||GPIO_PORTx == GPIO_PORTH )
			{
				if(GPIO_AF_NUM >= GPIO_AF00 && GPIO_AF_NUM <= GPIO_AF15)
				{
					if( GPIO_Pin_x >= GPIO_Pin_00 && GPIO_Pin_x<= GPIO_Pin_07 )
					{
						SET_4B((&((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_AFRL), (GPIO_Pin_x *4), GPIO_AF_NUM);
						Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
					else if(GPIO_Pin_x >= GPIO_Pin_08 && GPIO_Pin_x <= GPIO_Pin_15 )
					{
						GPIO_Pin_x-=GPIO_Pin_08;
						SET_4B((&((GPIO_registers_t *const)(GPIO_PORTx))->GPIOx_AFRH), (GPIO_Pin_x *4), GPIO_AF_NUM);
						Loc_GPIO_ErrorStatus= GPIO_enuOk;
					}
					else
					{
						Loc_GPIO_ErrorStatus= GPIO_enuInvalidPinNumber;
					}
				}
				else
				{
					Loc_GPIO_ErrorStatus= GPIO_enuInvalidAlternateFunctionNumber;
				}
			}
			else
			{
				Loc_GPIO_ErrorStatus= GPIO_enuInvalidPortNumber;
			}
		}
		else
		{
			Loc_GPIO_ErrorStatus= GPIO_enuNullPointer;
		}
	}
return Loc_GPIO_ErrorStatus;
}
