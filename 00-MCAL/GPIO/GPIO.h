/*************************************************************
 * 
 * Filename: GPIO.h
 * Description: Header (interface) file of the GPIO driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __GPIO_H__
#define __GPIO_H__

#include "STD_TYPES.h"

#define GPIO_PORTA ((void*)(0x40020000))
#define GPIO_PORTB ((void*)(0x40020400))
#define GPIO_PORTC ((void*)(0x40020800))
#define GPIO_PORTD ((void*)(0x40020C00))
#define GPIO_PORTE ((void*)(0x40021000))
#define GPIO_PORTH ((void*)(0x40021C00))


#define GPIO_Pin_00  00
#define GPIO_Pin_01  01
#define GPIO_Pin_02  02
#define GPIO_Pin_03  03
#define GPIO_Pin_04  04
#define GPIO_Pin_05  05
#define GPIO_Pin_06  06
#define GPIO_Pin_07  07
#define GPIO_Pin_08  8
#define GPIO_Pin_09  9
#define GPIO_Pin_10  10
#define GPIO_Pin_11  11
#define GPIO_Pin_12  12
#define GPIO_Pin_13  13
#define GPIO_Pin_14  14
#define GPIO_Pin_15  15

#define CLR_MASK 0B11
#define CLR_MASK_4B 0b1111

typedef struct
{
	u32 GPIOx_MODER; // where x = A..E and H
	u32 GPIOx_OTYPER;
	u32 GPIOx_OSPEEDR;
	u32 GPIOx_PUPDR;
	u32 GPIOx_IDR;
	u32 GPIOx_ODR;
	u32 GPIOx_BSRR;
	u32 GPIOx_LCKR;
	u32 GPIOx_AFRL;
	u32 GPIOx_AFRH;
}GPIO_registers_t;

/*SET MODE FUNCTION Inputs*/
/*GPIO port output speed register (GPIOx_MODER)*/
#define	GPIO_MODER00  00
#define	GPIO_MODER01  02
#define	GPIO_MODER02  04
#define	GPIO_MODER03  06
#define	GPIO_MODER04  08
#define	GPIO_MODER05  10
#define	GPIO_MODER06  12
#define	GPIO_MODER07  14
#define	GPIO_MODER08  16
#define	GPIO_MODER09  18
#define	GPIO_MODER10  20
#define	GPIO_MODER11  22
#define	GPIO_MODER12  24
#define	GPIO_MODER13  26
#define	GPIO_MODER14  28
#define	GPIO_MODER15  30

/*I/O Direction Mode*/
#define GPIO_MODE_INPUT						0b00
#define GPIO_MODE_GENERAL_PURPOSE_OUTPUT	0b01
#define GPIO_MODE_ALTERNATIVE_FUNCTION		0b10
#define GPIO_MODE_ANALOG					0b11

/*gpio_setOutputPinTyPe Function Parameters*/
/*GPIO port output type register (GPIOx_OTYPER)*/
#define	GPIO_OT00  00
#define	GPIO_OT01  01
#define	GPIO_OT02  02
#define	GPIO_OT03  03
#define	GPIO_OT04  04
#define	GPIO_OT05  05
#define	GPIO_OT06  06
#define	GPIO_OT07  07
#define	GPIO_OT08  08
#define	GPIO_OT09  09
#define	GPIO_OT10  10
#define	GPIO_OT11  11
#define	GPIO_OT12  12
#define	GPIO_OT13  13
#define	GPIO_OT14  14
#define	GPIO_OT15  15

#define GPIO_OUTPUT_PUSH_PULL   0
#define GPIO_OUTPUT_OPEN_DRAIN  1

/**gpio_setOutputPinSpeed Function Parameters*/
/*GPIO port output speed register (GPIOx_OSPEEDR)*/
#define	GPIO_OSPEEDR00  00
#define	GPIO_OSPEEDR01  02
#define	GPIO_OSPEEDR02  04
#define	GPIO_OSPEEDR03  06
#define	GPIO_OSPEEDR04  08
#define	GPIO_OSPEEDR05  10
#define	GPIO_OSPEEDR06  12
#define	GPIO_OSPEEDR07  14
#define	GPIO_OSPEEDR08  16
#define	GPIO_OSPEEDR09  18
#define	GPIO_OSPEEDR10  20
#define	GPIO_OSPEEDR11  22
#define	GPIO_OSPEEDR12  24
#define	GPIO_OSPEEDR13  26
#define	GPIO_OSPEEDR14  28
#define	GPIO_OSPEEDR15  30

#define GPIO_OUTPUT_lOW_SPEED 		0b00
#define GPIO_OUTPUT_MEDIUM_SPEED	0b01
#define GPIO_OUTPUT_HIGH_SPEED 		0b10
#define GPIO_OUTPUT_VERY_HIGH_SPEED 0b11

/*gpio_setPinPullUp_PullDown Function Parameters*/
/*GPIO port pull-up/pull-down register (GPIOx_PUPDR)*/
#define	GPIO_PUPDR00  00
#define	GPIO_PUPDR01  02
#define	GPIO_PUPDR02  04
#define	GPIO_PUPDR03  06
#define	GPIO_PUPDR04  08
#define	GPIO_PUPDR05  10
#define	GPIO_PUPDR06  12
#define	GPIO_PUPDR07  14
#define	GPIO_PUPDR08  16
#define	GPIO_PUPDR09  18
#define	GPIO_PUPDR10  20
#define	GPIO_PUPDR11  22
#define	GPIO_PUPDR12  24
#define	GPIO_PUPDR13  26
#define	GPIO_PUPDR14  28
#define	GPIO_PUPDR15  30

#define GPIO_PUPDR_NO_PULL_UP_NO_PULL_DOWN   0b00
#define GPIO_PUPDR_PULL_UP     0b01
#define GPIO_PUPDR_PULL_DOWN   0b10

/*gpio_getPinInputData Function Parameters
 * gpio_getPortInputData Function Parameters*/
/*GPIO port input data register (GPIOx_IDR)*/
#define	GPIO_IDR00  00
#define	GPIO_IDR01  01
#define	GPIO_IDR02  02
#define	GPIO_IDR03  03
#define	GPIO_IDR04  04
#define	GPIO_IDR05  05
#define	GPIO_IDR06  06
#define	GPIO_IDR07  07
#define	GPIO_IDR08  08
#define	GPIO_IDR09  09
#define	GPIO_IDR10  10
#define	GPIO_IDR11  11
#define	GPIO_IDR12  12
#define	GPIO_IDR13  13
#define	GPIO_IDR14  14
#define	GPIO_IDR15  15

/*gpio_setOutputPinValue Function Parameter
 * gpio_setOutputPORTValue Function Parameter*/
/*GPIO port output data register (GPIOx_ODR)*/
#define	GPIO_ODR00  00
#define	GPIO_ODR01  01
#define	GPIO_ODR02  02
#define	GPIO_ODR03  03
#define	GPIO_ODR04  04
#define	GPIO_ODR05  05
#define	GPIO_ODR06  06
#define	GPIO_ODR07  07
#define	GPIO_ODR08  08
#define	GPIO_ODR09  09
#define	GPIO_ODR10  10
#define	GPIO_ODR11  11
#define	GPIO_ODR12  12
#define	GPIO_ODR13  13
#define	GPIO_ODR14  14
#define	GPIO_ODR15  15

#define GPIO_ODR_PINX_HIGH 1
#define GPIO_ODR_PINX_LOW  0

#define GPIO_ODR_MAX_PORTX_VALUE 0XFFFF // just 16 bits value
#define GPIO_ODR_MIN_PORTX_VALUE 0x0
/*gpio_atomicSet_ResetOutputPinValue Function Parameter*/
/* GPIO port bit set/reset register (GPIOx_BSRR) */
#define	GPIO_BS00   00
#define	GPIO_BS01   01
#define	GPIO_BS02   02
#define	GPIO_BS03   03
#define	GPIO_BS04   04
#define	GPIO_BS05   05
#define	GPIO_BS06   06
#define	GPIO_BS07   07
#define	GPIO_BS08   8u
#define	GPIO_BS09   09
#define	GPIO_BS10   10
#define	GPIO_BS11   11
#define	GPIO_BS12   12
#define	GPIO_BS13   13
#define	GPIO_BS14   14
#define	GPIO_BS15   15
#define	GPIO_BR00   16
#define	GPIO_BR01   17
#define	GPIO_BR02   18
#define	GPIO_BR03   19
#define	GPIO_BR04   20
#define	GPIO_BR05   21
#define	GPIO_BR06   22
#define	GPIO_BR07   23
#define	GPIO_BR08   24
#define	GPIO_BR09   25
#define	GPIO_BR10   26
#define	GPIO_BR11   27
#define	GPIO_BR12   28
#define	GPIO_BR13   29
#define	GPIO_BR14   30
#define	GPIO_BR15   31

#define GPIO_BSRR_BSX_NO_ACTION_ODRX_BIT  0
#define GPIO_BSRR_BSX_SET_ODRX_BIT		  1

#define GPIO_BSRR_BRX_NO_ACTION_ODRX_BIT  0
#define GPIO_BSRR_BRX_RESET_ODRX_BIT	  1

#define ATOMIC_BSX_SET   0X55
#define ATOMIC_BRX_RESET 0XAA

/*GPIO port configuration lock register  (GPIOx_LCKR)*/
#define	GPIO_LCK00  00
#define	GPIO_LCK01  01
#define	GPIO_LCK02  02
#define	GPIO_LCK03  03
#define	GPIO_LCK04  04
#define	GPIO_LCK05  05
#define	GPIO_LCK06  06
#define	GPIO_LCK07  07
#define	GPIO_LCK08  08
#define	GPIO_LCK09  09
#define	GPIO_LCK10  10
#define	GPIO_LCK11  11
#define	GPIO_LCK12  12
#define	GPIO_LCK13  13
#define	GPIO_LCK14  14
#define	GPIO_LCK15  15
#define	GPIO_LCKK   16

#define GPIO_PORT_CFG_LOCKED 	 1
#define GPIO_PORT_CFG_NOT_LOCKED 0
#define GPIO_LOCK_KEY_ACTIVE	 1
#define GPIO_LOCK_KEY_NOT_ACTIVE 0



/*GPIO alternate function low register  (GPIOx_AFRL)*/
#define	GPIO_AFRL00  00
#define	GPIO_AFRL01  04
#define	GPIO_AFRL02  08
#define	GPIO_AFRL03  12
#define	GPIO_AFRL04  16
#define	GPIO_AFRL05  20
#define	GPIO_AFRL06  24
#define	GPIO_AFRL07  28

/*GPIO alternate function high register (GPIOx_AFRH)*/
#define DISTINCT_VAL 100
#define	GPIO_AFRH08  100
#define	GPIO_AFRH09  104
#define	GPIO_AFRH10  108
#define	GPIO_AFRH11  112
#define	GPIO_AFRH12  116
#define	GPIO_AFRH13  120
#define	GPIO_AFRH14  124
#define	GPIO_AFRH15  128

/*ALTERNATIVE FUNCTIONS */
#define GPIO_AF00  0b0000
#define GPIO_AF01  0b0001
#define GPIO_AF02  0b0010
#define GPIO_AF03  0b0011
#define GPIO_AF04  0b0100
#define GPIO_AF05  0b0101
#define GPIO_AF06  0b0110
#define GPIO_AF07  0b0111
#define GPIO_AF08  0b1000
#define GPIO_AF09  0b1001
#define GPIO_AF10  0b1010
#define GPIO_AF11  0b1011
#define GPIO_AF12  0b1100
#define GPIO_AF13  0b1101
#define GPIO_AF14  0b1110
#define GPIO_AF15  0b1111

typedef enum
{
	GPIO_enuOk,
	GPIO_enuNok,
	GPIO_enuNullPointer,
	GPIO_enuInvalidPinDirection,
	GPIO_enuInvalidPinNumber,
	GPIO_enuInvalidPortNumber,
	GPIO_enuInvalidPinOutputConfiguration,
	GPIO_enuInvalidPinSpeedConfiguration,
	GPIO_enuInvalidPinMode,
	GPIO_enuInvalidPinPullConfiguration,
	GPIO_enuInvalidPinOutputValue,
	GPIO_enuInvalidPortOutputValue,
	GPIO_enuInvalidAtomicOperation,
	GPIO_enuInvalidLockConfiguration,
	GPIO_enuInvalidPortLockValue,
	GPIO_enuInvalidLockKeyValue,
	GPIO_enuInvalidAlternateFunctionNumber,
	GPIO_enuLockedRegister,
}GPIO_ErrorStatus_t;

typedef struct{
	void* GPIO_Port;
	u32 GPIO_Pin;
	u32 GPIO_PinMode;
	u32 GPIO_OutputPinType;
	u32 GPIO_OutputPinSpeed;
	u32 GPIO_PinPullUp_PullDown;
	u32 GPIO_OutputPinValue;
	u32 GPIO_InputPinValue;
	u32 GPIO_AlternateFunctionNumber;

}GPIO_Pin_Confg;

/*Init Function */

void Init_Pin_Configure(GPIO_Pin_Confg * Struct_object);

/*
 * Description: Configure the I/O direction mode.
 * Parameters Options:
 * GPIO_Portx: GPIO_PORTA,GPIO_PORTB,GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH
 * GPIO_Pinx: GPIO_MODER00 : GPIO_MODER15
 * GPIO_Pin_Direction: GPIO_MODE_INPUT,GPIO_MODE_GENERAL_PURPOSE_OUTPUT,GPIO_MODE_ALTERNATIVE_FUNCTION,GPIO_MODE_ANALOG
 * Return type:
 *
 * */
GPIO_ErrorStatus_t gpio_setPinMode(void* GPIO_PORTx, u32 GPIO_Pin_x, u32  GPIO_Pin_Direction);

/*
 * Description: Configure the Output type of the I/O port
 * Parameters Options:
 * GPIO_Portx: GPIO_PORTA,GPIO_PORTB,GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH
 * GPIO_Pinx: GPIO_OT00 : GPIO_OT15
 * GPIO_OUTPUT_: GPIO_OUTPUT_PUSH_PULL OR GPIO_OUTPUT_OPEN_DRAIN
 * Return type:
 *
 * */
GPIO_ErrorStatus_t gpio_setOutputPinTyPe(void* GPIO_PORTx,u32  GPIO_Pin_x,u32 GPIO_OUTPUT_);

/*
 * Description: Configure the Output Speed of the I/O port
 * Parameters Options:
 * GPIO_Portx: GPIO_PORTA,GPIO_PORTB,GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH
 * GPIO_Pinx: GPIO_OSPEEDR00 : GPIO_OSPEEDR15
 * GPIO_OUTPUT_: GPIO_OUTPUT_lOW_SPEED OR GPIO_OUTPUT_MEDIUM_SPEED OR GPIO_OUTPUT_HIGH_SPEED OR GPIO_OUTPUT_VERY_HIGH_SPEED
 * Return type:
 *
 * */
GPIO_ErrorStatus_t gpio_setOutputPinSpeed(void* GPIO_PORTx,u32  GPIO_Pin_x,u32 GPIO_OUTPUT_X_SPEED);

/*
 * Description: Configure the PinMode PullUP or PullDown or None of the I/O port
 * Parameters Options:
 * GPIO_Portx: GPIO_PORTA,GPIO_PORTB,GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH
 * GPIO_Pinx: GPIO_PUPDR00 : GPIO_PUPDR15
 * GPIO_OUTPUT_: GPIO_PUPDR_NO_PULL_UP_NO_PULL_DOWN OR GPIO_PUPDR_PULL_UP OR GPIO_PUPDR_PULL_DOWN
 * Return type:
 *
 * */
GPIO_ErrorStatus_t gpio_setPinPullUp_PullDown(void* GPIO_PORTx,u32 GPIO_Pin_x,u32 GPIO_PUPDR_X);

/*
 * Description: Get the input data of the I/O port
 * Parameters Options:
 * GPIO_Portx: GPIO_PORTA,GPIO_PORTB,GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH
 * GPIO_Pinx: GPIO_IDR00 : GPIO_IDR15
 * GPIO_IDR_Pinx_Value: Variable to read input data
 * Return type:
 *
 * */
GPIO_ErrorStatus_t gpio_getPinInputData(void* GPIO_PORTx,u32 GPIO_Pin_x,u32* GPIO_IDR_Pinx_Value);
GPIO_ErrorStatus_t gpio_getPortInputData(void* GPIO_PORTx,u32* GPIO_IDR_Portx_Value);

/*
 * Description: Configure the Output VALUE of the I/O port
 * Parameters Options:
 * GPIO_Portx: GPIO_PORTA,GPIO_PORTB,GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH
 * GPIO_Pinx: GPIO_ODR00 : GPIO_ODR15
 * GPIO_OUTPUT_: GPIO_ODR_OUTPUT_HIGH OR GPIO_ODR_OUTPUT_LOW
 * Return type:
 *
 * */
GPIO_ErrorStatus_t gpio_setOutputPinValue(void* GPIO_PORTx,u32 GPIO_Pin_x,u32 GPIO_ODR_PINX_VAL);
GPIO_ErrorStatus_t gpio_setOutputPortValue(void* GPIO_PORTx,u32 GPIO_ODR_PORTX_VAL);

/*
 * Description: Configure the ATOMIC SET OR RESET Output VALUE of the I/O port
 * Parameters Options:
 * ATOMIC_: ATOMIC_BSX_SET ,ATOMIC_BRX_RESET
 * GPIO_Portx: GPIO_PORTA,GPIO_PORTB,GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH
 * GPIO_BXX: GPIO_BS00 : GPIO_BS15
 * 	     	 GPIO_BR00 : GPIO_BR15
 * Return type:
 * If both BSx and BRx are set, BSx has priority.
 * */
GPIO_ErrorStatus_t gpio_atomicSet_ResetOutputPinValue(u32 ATOMIC_,void* GPIO_PORTx,u32 GPIO_Pin_x,u32 GPIO_BSRR_BXX_Value);

/*
 * Each lock bit freezes a specific configuration register (control and alternate function registers)
 * Description: Configure the LOCK REG VALUES of the I/O port/PIN
 * Parameters Options:
 * GPIO_Portx: GPIO_PORTA,GPIO_PORTB,GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH
 * GPIO_LCKx: GPIO_LCK00 : GPIO_LCK15
 * GPIO_LCK_PINX_VAL:PORT_CFG_NOT_LOCKED ,PORT_CFG_LOCKED
 * GPIO_LCK_PORTX_VAL:  BITS VALUE ONLY LIKE OXFF
 * Return type:
 */
GPIO_ErrorStatus_t gpio_setLockRegPinValue(void*  GPIO_PORTx,u32 GPIO_LCKx,u32 GPIO_PORT_CFG_);
GPIO_ErrorStatus_t gpio_setLockRegPortValue(void* GPIO_PORTx,u32 GPIO_PORT_CFG_Val);

/*
 * Description: Configure the LOCK REG KEY of the I/O port
 * Parameters Options:
 * GPIO_Portx: GPIO_PORTA,GPIO_PORTB,GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH
 * GPIO_LCK_KEY_: GPIO_LCK_KEY_ACTIVE : GPIO_LCK_KEY_NOT_ACTIVE
 * Return type:
 */
GPIO_ErrorStatus_t gpio_Enablelock_LockReg(void* GPIO_PORTx,u32 GPIO_LCK_KEY_);

/*
 * Description: Configure Alternative function
 * Parameters Options:
 * GPIO_Portx: GPIO_PORTA,GPIO_PORTB,GPIO_PORTC,GPIO_PORTD,GPIO_PORTE,GPIO_PORTH
 * GPIO_AFRX_Pinx: GPIO_AFRL0 : GPIO_AFRL7 or GPIO_AFRH08 : GPIO_AFRH15
 * GPIO_AF_NUM: GPIO_AF00:GPIO_AF15
 * Return type:
 */
GPIO_ErrorStatus_t gpio_setPinAlternativeFunction(void* GPIO_PORTx,u32 GPIO_Pin_x,u32 GPIO_AF_NUM);


#endif /* __GPIO_H__ */
