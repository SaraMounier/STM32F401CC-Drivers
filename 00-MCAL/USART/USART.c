/*************************************************************
 * 
 * Filename: SUART.c
 * Description: Source file of the SUART driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "./includes/SUART_Cfg.h"
#include "./includes/SUART_Priv.h"
#include "./includes/SUART.h"
#include "./includes/GPIO.h"
#include <math.h>


USART_Registers_t *const USART= ( USART_Registers_t *const) (USART1_BASE_ADDRESS);
static volatile u32 SR_RegReading,DR_RegReading;
static RX_State RX = {
		.RX_Status = RX_IDLE
};

static TX_State TX = {
		.TX_Status = TX_IDLE
};

void USART1_vidInit(void)
{
	u8 Iterator;
	for(Iterator=0;Iterator<USART_CONFIG_PINS;Iterator++)
	{
		GPIO_Pin_Confg USART1;
		USART1.GPIO_Port=GPIO_PORTA;
		USART1.GPIO_Pin=(GPIO_Pin_09 +Iterator);
		USART1.GPIO_PinMode=GPIO_MODE_ALTERNATIVE_FUNCTION;
		USART1.GPIO_AlternateFunctionNumber=GPIO_AF07;
		USART1.GPIO_PinPullUp_PullDown=GPIO_PUPDR_NO_PULL_UP_NO_PULL_DOWN;
		Init_Pin_Configure( & USART1);
	}
}

void USART2_vidInit(void)
{
	u8 Iterator;
	for(Iterator=0;Iterator<USART_CONFIG_PINS;Iterator++)
	{
		GPIO_Pin_Confg USART2;
		USART2.GPIO_Port=GPIO_PORTA;
		USART2.GPIO_Pin=(GPIO_Pin_00 +Iterator);
		USART2.GPIO_PinMode=GPIO_MODE_ALTERNATIVE_FUNCTION;
		USART2.GPIO_AlternateFunctionNumber=GPIO_AF07;
		USART2.GPIO_PinPullUp_PullDown=GPIO_PUPDR_PULL_UP;
		Init_Pin_Configure( & USART2);
	}
}

USART_ErrorStatus_t USART_getCTSFlagState(u8* CTSFlagState)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if( CTSFlagState !=NULL)
	{
		* CTSFlagState= ( (USART->USART_SR)>>USART_SR_CTS ) & 0x01;
		Loc_USARTErrStatus=USART_enuOK;
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNullPtr;
	}
	return Loc_USARTErrStatus;
}
USART_ErrorStatus_t USART_clearCTSFlagState()
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	(USART->USART_SR) &= ~(1 << USART_SR_CTS) ;
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_getLINBreakDetectionState(u8* LINBreakDetectionState)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if( LINBreakDetectionState !=NULL)
	{
		* LINBreakDetectionState= ( (USART->USART_SR)>>USART_SR_LBD) & 0x01;
		Loc_USARTErrStatus=USART_enuOK;
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNullPtr;
	}
	return Loc_USARTErrStatus;
}
USART_ErrorStatus_t USART_clearLINBreakDetectionState()
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	(USART->USART_SR) &= ~(1 << USART_SR_LBD) ;
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_getDataTransmitRegisterState(u8* TransmitRegisterState)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if( TransmitRegisterState !=NULL)
	{
		* TransmitRegisterState= ( (USART->USART_SR)>>USART_SR_TXE ) & 0x01;
		Loc_USARTErrStatus=USART_enuOK;
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNullPtr;
	}
	return Loc_USARTErrStatus;
}
USART_ErrorStatus_t USART_clearDataTransmitRegisterState()
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
 USART->USART_DR=0; //DDEBUGG
//	(USART->USART_SR) &= ~(1 << USART_SR_TXE) ;
	return Loc_USARTErrStatus;
}
USART_ErrorStatus_t USART_getTransmittedDataState(u8* DataTransmissionState)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if( DataTransmissionState !=NULL)
	{
		* DataTransmissionState= ( (USART->USART_SR)>>USART_SR_TC ) & 0x01;
		Loc_USARTErrStatus=USART_enuOK;
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNullPtr;
	}
	return Loc_USARTErrStatus;
}
USART_ErrorStatus_t USART_clearTransmittedDataState()
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	/*SR_RegReading= USART->USART_SR;
	USART->USART_DR=DR_RegReading;*/ // multi-buffer communication.
	(USART->USART_SR) &= ~(1 << USART_SR_TC) ;
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_getReceivedDataState(u8* DataReceiveState)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if( DataReceiveState !=NULL)
	{
		*DataReceiveState= ( (USART->USART_SR)>>USART_SR_RXNE ) & 0x01;
		Loc_USARTErrStatus=USART_enuOK;
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNullPtr;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_clearReceivedDataState()
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	DR_RegReading= USART->USART_DR;  //multi-buffer communication.
	//(USART->USART_SR) &= ~(1 << USART_SR_RXNE) ;
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_getIDLELineDetection(u8* IDLE_LineDetection)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if( IDLE_LineDetection !=NULL)
	{
		* IDLE_LineDetection= ( (USART->USART_SR)>>USART_SR_IDLE ) & 0x01;
		Loc_USARTErrStatus=USART_enuOK;
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNullPtr;
	}
	return Loc_USARTErrStatus;
}
USART_ErrorStatus_t USART_clearIDLELineDetection()
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
//	SR_RegReading= USART->USART_SR;
//	DR_RegReading= USART->USART_DR;
	(USART->USART_SR) &= ~(1 << USART_SR_IDLE) ;
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_getOverRunErrorDetection(u8* OverRunErrorDetection)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(OverRunErrorDetection !=NULL)
	{
		* OverRunErrorDetection= ( (USART->USART_SR)>>USART_SR_ORE ) & 0x01;
		Loc_USARTErrStatus=USART_enuOK;
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNullPtr;
	}
	return Loc_USARTErrStatus;
}
USART_ErrorStatus_t USART_clearOverRunErrorDetection()
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	SR_RegReading= USART->USART_SR;
	DR_RegReading= USART->USART_DR;
	(USART->USART_SR) &= ~(1 << USART_SR_ORE)  ;
	return Loc_USARTErrStatus;
}


USART_ErrorStatus_t USART_getNoiseFlagDetection(u8* NoiseDetection)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;

	if( NoiseDetection !=NULL)
	{
		* NoiseDetection= ( (USART->USART_SR)>>USART_SR_NF ) & 0x01;
		Loc_USARTErrStatus=USART_enuOK;
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNullPtr;
	}
	return Loc_USARTErrStatus;
}
USART_ErrorStatus_t USART_clearNoiseFlagDetection()
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	SR_RegReading= USART->USART_SR;
	DR_RegReading= USART->USART_DR;
	(USART->USART_SR) &= ~(1 << USART_SR_NF)  ;
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_getFramingFlagDetection(u8* FramingFlagDetection)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if( FramingFlagDetection !=NULL)
	{
		* FramingFlagDetection= ( (USART->USART_SR)>>USART_SR_FE ) & 0x01;
		Loc_USARTErrStatus=USART_enuOK;
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNullPtr;
	}
	return Loc_USARTErrStatus;
}
USART_ErrorStatus_t USART_clearFramingFlagDetection()
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	SR_RegReading= USART->USART_SR;
	DR_RegReading= USART->USART_DR;
	(USART->USART_SR) &= ~(1 << USART_SR_FE)  ;

	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_getParityErrorDetection(u8* ParityErrorDetection)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if( ParityErrorDetection !=NULL)
	{
		* ParityErrorDetection= ( (USART->USART_SR)>>USART_SR_PE ) & 0x01;
		Loc_USARTErrStatus=USART_enuOK;
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNullPtr;
	}
	return Loc_USARTErrStatus;
}
USART_ErrorStatus_t USART_clearParityErrorDetection()
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	u8 DataReceiveState;
	USART_getReceivedDataState(&DataReceiveState);
	if(DataReceiveState==1)
	{
		SR_RegReading= USART->USART_SR;
		DR_RegReading= USART->USART_DR;
		(USART->USART_SR) &= ~(1 << USART_SR_PE)  ;
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}


USART_ErrorStatus_t USART_getRecievedData(u16* RecievedData)
{
	/*implement if parity control enable is enabled and word length*/
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
//	u8 ParityControlEnable=((USART->USART_CR1)>>USART_CR1_PCE) &0x01;
//	u8 WordLength=((USART->USART_CR1)>>USART_CR1_M) &0x01;
//	if(ParityControlEnable==1 && WordLength==0 )
//	{
//	* RecievedData=(USART->USART_DR) & 0x7f;
//	}
//	else if(ParityControlEnable==1 && WordLength==1 )
//	{
//	* RecievedData=(USART->USART_DR) & 0xff;
//	}
//	else if(ParityControlEnable==0 && WordLength==0 )
//	{
//	* RecievedData=(USART->USART_DR) & 0xff;
//	}
//	else if(ParityControlEnable==0 && WordLength==1 )
//	{
//	* RecievedData=(USART->USART_DR) & 0x1ff;
//	}

	* RecievedData=(USART->USART_DR);
	return Loc_USARTErrStatus;
}
USART_ErrorStatus_t USART_setTransmittedData(u16 TransmittedData)
{
	/*implement if parity control enable is enabled and word length*/
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
//	u8 ParityControlEnable=((USART->USART_CR1)>>USART_CR1_PCE) &0x01;
//	u8 WordLength=((USART->USART_CR1)>>USART_CR1_M) &0x01;
//	if(ParityControlEnable==1 && WordLength==0 )
//		{
//			(USART->USART_DR) =TransmittedData & 0x7f;
//		}
//		else if(ParityControlEnable==1 && WordLength==1 )
//		{
//			(USART->USART_DR) =TransmittedData & 0xff;
//		}
//		else if(ParityControlEnable==0 && WordLength==0 )
//		{
//			(USART->USART_DR) =TransmittedData & 0xff;
//		}
//		else if(ParityControlEnable==0 && WordLength==1 )
//		{
//			(USART->USART_DR) =TransmittedData & 0x1ff;
//		}

	(USART->USART_DR) =TransmittedData;
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_setOverSamplingMode(u8 OVER_SAMPLING_BY)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(OVER_SAMPLING_BY==OVER_SAMPLING_BY8)
	{
		(USART->USART_CR1) |= 1<<USART_CR1_OVER8;
	}
	if(OVER_SAMPLING_BY==OVER_SAMPLING_BY16)
	{
		(USART->USART_CR1) &=~( 1<<USART_CR1_OVER8);
	}
	return Loc_USARTErrStatus;
}


USART_ErrorStatus_t USART_SetBaudRateValue(f32 BaudRateValue)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	f32 TX_RX_Baud;
	u32 int_TX_RX_Baud;
	f32 DIV_Fraction;
	u32 int_DIV_Fraction;
	u8 over8BitVal=(((USART->USART_CR1)>>USART_CR1_OVER8) & 0x01);
	if(over8BitVal==1) //over8=8
	{

		TX_RX_Baud=RCC_CLOCK/(8*BaudRateValue*1000);
		int_TX_RX_Baud=TX_RX_Baud;
		DIV_Fraction=TX_RX_Baud-int_TX_RX_Baud;
		DIV_Fraction*=8;

		if(((f32)((f32)DIV_Fraction-(u32)DIV_Fraction)) >= 0.5)
		{
			DIV_Fraction=ceil(DIV_Fraction);
			int_DIV_Fraction=DIV_Fraction;
			if(int_DIV_Fraction <= 7)
			{
				(USART->USART_BRR)|=int_DIV_Fraction;
				(USART->USART_BRR)|=int_TX_RX_Baud << 4;
			}
			else
			{
				(USART->USART_BRR)|=(int_TX_RX_Baud << 4)+1;
			}

		}
		else if(((f32)((f32)DIV_Fraction-(u32)DIV_Fraction)) < 0.5)
		{
			DIV_Fraction=floor(DIV_Fraction);
			int_DIV_Fraction=DIV_Fraction;
			if(int_DIV_Fraction <= 7)
			{
				(USART->USART_BRR)|=int_DIV_Fraction;
				(USART->USART_BRR)|=int_TX_RX_Baud << 4;
			}
			else
			{
				(USART->USART_BRR)|=(int_TX_RX_Baud << 4)+1;
			}

		}
	}
	else //over8=16
	{
		TX_RX_Baud=(RCC_CLOCK)/(16*BaudRateValue*1000);
		int_TX_RX_Baud=TX_RX_Baud;
		DIV_Fraction=TX_RX_Baud-int_TX_RX_Baud;
		DIV_Fraction*=16;
		if(((f32)((f32)DIV_Fraction-(u32)DIV_Fraction)) >= 0.5)
		{
			DIV_Fraction=ceil(DIV_Fraction);
			int_DIV_Fraction=DIV_Fraction;
			if(int_DIV_Fraction <= 15)
			{
				(USART->USART_BRR)|=int_DIV_Fraction;
				(USART->USART_BRR)|=int_TX_RX_Baud << 4;
			}
			else
			{
				(USART->USART_BRR)|=(int_TX_RX_Baud << 4)+1;
			}

		}
		else if(((f32)((f32)DIV_Fraction-(u32)DIV_Fraction)) < 0.5)
		{
			DIV_Fraction=floor(DIV_Fraction);
			int_DIV_Fraction=DIV_Fraction;
			if(int_DIV_Fraction <= 15)
			{
				(USART->USART_BRR)|=int_DIV_Fraction;
				(USART->USART_BRR)|=int_TX_RX_Baud << 4;
			}
			else
			{
				(USART->USART_BRR)|=(int_TX_RX_Baud << 4)+1;
			}

		}
	}

	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_enableInterruptX(u8 USART_CR1_InterruptName)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(USART_CR1_InterruptName==USART_CR1_IDLEIE ||USART_CR1_InterruptName==USART_CR1_RXNEIE ||USART_CR1_InterruptName==USART_CR1_TCIE
			||USART_CR1_InterruptName==USART_CR1_TXEIE ||USART_CR1_InterruptName==USART_CR1_PEIE)
	{
		(USART->USART_CR1) |= (1<<USART_CR1_InterruptName);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}
USART_ErrorStatus_t USART_disableInterruptX(u8 USART_CR1_InterruptName)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(USART_CR1_InterruptName==USART_CR1_IDLEIE ||USART_CR1_InterruptName==USART_CR1_RXNEIE ||USART_CR1_InterruptName==USART_CR1_TCIE
			||USART_CR1_InterruptName==USART_CR1_TXEIE ||USART_CR1_InterruptName==USART_CR1_PEIE)
	{
		(USART->USART_CR1) &= ~(1<<USART_CR1_InterruptName);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_enableUART()
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	(USART->USART_CR1) |= (1<<USART_CR1_UE);
	return Loc_USARTErrStatus;

}

USART_ErrorStatus_t USART_disableUART()
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	(USART->USART_CR1) |= (1<<USART_CR1_UE);
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_enable_TX_RX_PC(u8 USART_CR1_BitName)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(USART_CR1_BitName==USART_CR1_RE || USART_CR1_BitName==USART_CR1_TE || USART_CR1_BitName==USART_CR1_PCE)
	{
		(USART->USART_CR1) |= (1<<USART_CR1_BitName);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}
USART_ErrorStatus_t USART_disable_TX_RX_PC(u8 USART_CR1_BitName)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(USART_CR1_BitName==USART_CR1_RE || USART_CR1_BitName==USART_CR1_TE || USART_CR1_BitName==USART_CR1_PCE)
	{
		(USART->USART_CR1) &= ~(1<<USART_CR1_BitName);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

/*
 * Options: DATA_8_BITS,DATA_9_BITS
 */
USART_ErrorStatus_t USART_setWordLength(u8 DATA_x_BITS)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(DATA_x_BITS==DATA_8_BITS)
	{
		(USART->USART_CR1) &= ~(1<<USART_CR1_M);
	}
	else if(DATA_x_BITS==DATA_9_BITS)
	{
		(USART->USART_CR1) |= (1<<USART_CR1_M);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_setWakeUpMode(u8 WAKE_)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(WAKE_==WAKE_IDLE_LINE)
	{
		(USART->USART_CR1) &= ~(1<<USART_CR1_WAKE);
	}
	else if(WAKE_==WAKE_ADDRESS_MARK)
	{
		(USART->USART_CR1) |= (1<<USART_CR1_WAKE);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_selectParity(u8 PS_x_PARITY)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(PS_x_PARITY==PS_EVEN_PARITY)
	{
		(USART->USART_CR1) &= ~(1<<USART_CR1_PS);
	}
	else if(PS_x_PARITY==PS_ODD_PARITY)
	{
		(USART->USART_CR1) |= (1<<USART_CR1_PS);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_setReceiverWakeUpMode(u8 x_RECIEVER_MODE)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(x_RECIEVER_MODE==ACTIVE_RECIEVER_MODE)
	{
		(USART->USART_CR1) &= ~(1<<USART_CR1_RWU);
	}
	else if(x_RECIEVER_MODE==MUTE_RECIEVER_MODE)
	{
		(USART->USART_CR1) |= (1<<USART_CR1_RWU);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_setSendBreak(u8 x_BREAK_CHAR_TRANSMITTED)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(x_BREAK_CHAR_TRANSMITTED==NO_BREAK_CHAR_TRANSMITTED)
	{
		(USART->USART_CR1) &= ~(1<<USART_CR1_SBK);
	}
	else if(x_BREAK_CHAR_TRANSMITTED==BREAK_CHAR_TRANSMITTED)
	{
		(USART->USART_CR1) |= (1<<USART_CR1_SBK);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_selectStopBits(u32 STOP_X_BIT )
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(STOP_X_BIT==STOP_1_BIT ||STOP_X_BIT==STOP_0_5_BIT ||STOP_X_BIT==STOP_2_BIT ||STOP_X_BIT==STOP_1_5_BIT )
	{
		u32 TempVar= (USART->USART_CR2) & ~(0b11 << USART_CR2_STOP);
		(USART->USART_CR2)= TempVar | (STOP_X_BIT<<STOP_X_BIT);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_setWakeUpAddressMark(u32 ADD_)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(ADD_<= 0xf)
	{
		u32 TempVar= (USART->USART_CR2) & ~(USART_CR2_ADD_MASK << USART_CR2_ADD);
		(USART->USART_CR2)= TempVar | (ADD_);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;

}
/*
 * Options: LIN_MODE_DISABLED , LIN_MODE_ENABLED*/
USART_ErrorStatus_t USART_setLINMode(u8 LIN_MODE_)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(LIN_MODE_ == LIN_MODE_DISABLED)
	{
		(USART->USART_CR2) &= ~(1<<USART_CR2_LINEN);
	}
	else if(LIN_MODE_ == LIN_MODE_ENABLED)
	{
		(USART->USART_CR2) |= (1<<USART_CR2_LINEN);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_configClkPin(u8 CK_,u8 CPOL_, u8 CPHA_, u8  LBCL_)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(CK_==CK_DISABLE)
	{
		(USART->USART_CR2) &= ~(1<<USART_CR2_CLKEN);
	}
	else if(CK_==CK_ENABLE)
	{
		(USART->USART_CR2) |= (1<<USART_CR2_CLKEN);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}

	if(CPOL_==CPOL_LOW)
	{
		(USART->USART_CR2) &= ~(1<<USART_CR2_CPOL);
	}
	else if(CPOL_==CPOL_HIGH)
	{
		(USART->USART_CR2) |= (1<<USART_CR2_CPOL);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}

	if(CPHA_==CPHA_FIRST_CLK_TRANSITION)
	{
		(USART->USART_CR2) &= ~(1<<USART_CR2_CPHA);
	}
	else if(CK_==CPHA_SECOND_CLK_TRANSITION)
	{
		(USART->USART_CR2) |= (1<<USART_CR2_CPHA);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}

	if(LBCL_==LBCL_NOT_OUTPUT)
	{
		(USART->USART_CR2) &= ~(1<<USART_CR2_LBCL);
	}
	else if(LBCL_==LBCL_OUTPUT)
	{
		(USART->USART_CR2) |= (1<<USART_CR2_LBCL);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}


USART_ErrorStatus_t USART_setLINBreakDetectionInterrupt(u8 LIN_BD_INTERRUPT_)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(LIN_BD_INTERRUPT_ == LIN_BD_INTERRUPT_ENABLE)
	{
		(USART->USART_CR2) &= ~(1<<USART_CR2_LBDIE);
	}
	else if(LIN_BD_INTERRUPT_ == LIN_BD_INTERRUPT_DISABLE)
	{
		(USART->USART_CR2) |= (1<<USART_CR2_LBDIE);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_setLINBreakDetectionLength(u8 LIN_BD_X_BIT)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(LIN_BD_X_BIT == LIN_BD_10_BIT)
	{
		(USART->USART_CR2) &= ~(1<<USART_CR2_LBDL);
	}
	else if(LIN_BD_X_BIT == LIN_BD_11_BIT)
	{
		(USART->USART_CR2) |= (1<<USART_CR2_LBDL);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_setErrorInterrupt(u8 ERROR_INTERRUPT_)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(ERROR_INTERRUPT_ == ERROR_INTERRUPT_INHIBITED)
	{
		(USART->USART_CR3) &= ~(1<<USART_CR3_EIE);
	}
	else if(ERROR_INTERRUPT_ == ERROR_INTERRUPT_GENERATED)
	{
		(USART->USART_CR3) |= (1<<USART_CR3_EIE);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_configIrDA(u8 IrDA_,u8 IRLP_)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(IrDA_ == IrDA_DISABLE)
	{
		(USART->USART_CR3) &= ~(1<<USART_CR3_IREN);
	}
	else if(IrDA_ == IrDA_ENABLE)
	{
		(USART->USART_CR3) |= (1<<USART_CR3_IREN);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}

	if(IRLP_ == IRLP_NORMAL_MODE)
	{
		(USART->USART_CR3) &= ~(1<<USART_CR3_IRLP);
	}
	else if(IRLP_ == IRLP_LOW_POWER_MODE)
	{
		(USART->USART_CR3) |= (1<<USART_CR3_IRLP);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}

	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_setLHalfDuplexSelection(u8 HALF_DUPLEX_)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(HALF_DUPLEX_ == HALF_DUPLEX_NOT_SELECTED)
	{
		(USART->USART_CR3) &= ~(1<<USART_CR3_HDSEL);
	}
	else if(HALF_DUPLEX_ == HALF_DUPLEX_SELECTED)
	{
		(USART->USART_CR3) |= (1<<USART_CR3_HDSEL);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}


USART_ErrorStatus_t USART_configSmartCardMode(u8 SC_MODE_,u8 NACK_PE_)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(SC_MODE_ == SC_MODE_DISABLED)
	{
		(USART->USART_CR3) &= ~(1<<USART_CR3_SCEN);
	}
	else if(SC_MODE_ == SC_MODE_ENABLED)
	{
		(USART->USART_CR3) |= (1<<USART_CR3_SCEN);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}

	if(NACK_PE_ == NACK_PE_DISABLED)
	{
		(USART->USART_CR3) &= ~(1<<USART_CR3_NACK);
	}
	else if(NACK_PE_ == NACK_PE_DISABLED)
	{
		(USART->USART_CR3) |= (1<<USART_CR3_NACK);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}

	return Loc_USARTErrStatus;
}


USART_ErrorStatus_t USART_setDMATransmitter_ReceiverMode(u8 DMA_TRANSMITTER_MODE_, u8 DMA_RECEIVER_MODE_)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(DMA_TRANSMITTER_MODE_ == DMA_TRANSMITTER_MODE_DISABLED)
	{
		(USART->USART_CR3) &= ~(1<<USART_CR3_DMAT);
	}
	else if(DMA_TRANSMITTER_MODE_ == DMA_TRANSMITTER_MODE_ENABLED)
	{
		(USART->USART_CR3) |= (1<<USART_CR3_DMAT);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}

	if(DMA_RECEIVER_MODE_ == DMA_RECEIVER_MODE_DISABLED)
	{
		(USART->USART_CR3) &= ~(1<<USART_CR3_DMAR);
	}
	else if(DMA_RECEIVER_MODE_ == DMA_RECEIVER_MODE_ENABLED)
	{
		(USART->USART_CR3) |= (1<<USART_CR3_DMAR);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}

	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_setRTSInterrupt(u8 RTS_INTERRUPT_)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(RTS_INTERRUPT_ == RTS_INTERRUPT_DISABLE)
	{
		(USART->USART_CR3) &= ~(1<<USART_CR3_RTSE);
	}
	else if(RTS_INTERRUPT_ == RTS_INTERRUPT_ENABLE)
	{
		(USART->USART_CR3) |= (1<<USART_CR3_RTSE);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_setCTSMode(u8 CTS_MODE_)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(CTS_MODE_ == CTS_MODE_DISABLE)
	{
		(USART->USART_CR3) &= ~(1<<USART_CR3_CTSE);
	}
	else if(CTS_MODE_ == CTS_MODE_ENABLE)
	{
		(USART->USART_CR3) |= (1<<USART_CR3_CTSE);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_setCTSInterrupt(u8 CTS_INTERRUPT_)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(CTS_INTERRUPT_ == CTS_INTERRUPT_INHIBITED)
	{
		(USART->USART_CR3) &= ~(1<<USART_CR3_CTSIE);
	}
	else if(CTS_INTERRUPT_ == CTS_INTERRUPT_GENERATED)
	{
		(USART->USART_CR3) |= (1<<USART_CR3_CTSIE);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_setSampleBitMethod(u8 X_SAMPLE_BIT_METHOD)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuOK;
	if(X_SAMPLE_BIT_METHOD == THREE_SAMPLE_BIT_METHOD)
	{
		(USART->USART_CR3) &= ~(1<<USART_CR3_ONEBIT);
	}
	else if(X_SAMPLE_BIT_METHOD == ONE_SAMPLE_BIT_METHOD)
	{
		(USART->USART_CR3) |= (1<<USART_CR3_ONEBIT);
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNOK;
	}
	return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_receiveBuffer(u8* Buffer,u32 Size)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuBUSY;
	 if(RX.RX_Status == RX_IDLE)
	 {
		RX.RX_Buffer=Buffer;
		RX.RX_Size=Size;
		RX.RX_Idx=0;
		USART_clearReceivedDataState();
		USART_clearIDLELineDetection();
		RX.RX_Status = RX_BUSY;
		USART_enableInterruptX(USART_CR1_RXNEIE);
		Loc_USARTErrStatus=USART_enuOK;

	 }
return Loc_USARTErrStatus;
}

USART_ErrorStatus_t USART_sendBuffer(u8* Buffer,u32 Size)
{
	USART_ErrorStatus_t Loc_USARTErrStatus=USART_enuBUSY;
	 if(TX.TX_Status == TX_IDLE)
	 {
		TX.TX_Buffer=Buffer;
		TX.TX_Size=Size;
		TX.TX_Idx=0;
		USART_clearDataTransmitRegisterState();
		USART_clearTransmittedDataState();
		TX.TX_Status = TX_BUSY;
		USART_enableInterruptX(USART_CR1_TXEIE);
		USART_setTransmittedData(TX.TX_Buffer[TX.TX_Idx]);
		TX.TX_Idx++;
		Loc_USARTErrStatus=USART_enuOK;
	 }
return Loc_USARTErrStatus;
}

void (*AppNotifyTX)(void)=NULL;
USART_ErrorStatus_t USART_TX_setCallBack( void(* AppNotifyTX_MAIN)(void) )
{
	USART_ErrorStatus_t Loc_USARTErrStatus;
	if (AppNotifyTX_MAIN !=NULL)
	{
		AppNotifyTX=AppNotifyTX_MAIN ;
		Loc_USARTErrStatus=USART_enuOK;
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNullPtr;
	}
	return Loc_USARTErrStatus;
}

void (*AppNotifyRX)(void)=NULL;
USART_ErrorStatus_t USART_RX_setCallBack( void(* AppNotifyRX_MAIN)(void) )
{
	USART_ErrorStatus_t Loc_USARTErrStatus;
	if (AppNotifyRX_MAIN !=NULL)
	{
		AppNotifyRX=AppNotifyRX_MAIN ;
		Loc_USARTErrStatus=USART_enuOK;
	}
	else
	{
		Loc_USARTErrStatus=USART_enuNullPtr;
	}
	return Loc_USARTErrStatus;
}


void __attribute__ ((section(".after_vectors")))
USART1_IRQHandler(void)
{
	u8 RXNE_Status;
	u8 TransmitRegisterState=0;
	u16 RecievedData;
	USART_getReceivedDataState(&RXNE_Status);
	if(RXNE_Status==1 && RX.RX_Status == RX_BUSY)
	{
		USART_getRecievedData(& RecievedData);
		RX.RX_Buffer[RX.RX_Idx]=RecievedData;
		RX.RX_Idx++;
		if(RX.RX_Idx == RX.RX_Size)
		{
			RX.RX_Status=RX_IDLE;
			USART_disableInterruptX(USART_CR1_RXNEIE);
			if(AppNotifyRX!=NULL)
			{
				AppNotifyRX();
			}
		}
	}
	USART_getDataTransmitRegisterState(& TransmitRegisterState);

	if(TransmitRegisterState==DATA_TRANSFERED_TO_SHIFT_REGISTER)
	{
		if(TX.TX_Idx < TX.TX_Size)
		{
			USART_setTransmittedData( TX.TX_Buffer[TX.TX_Idx]);
			TX.TX_Idx++;
		}
		else
		{
			TX.TX_Status=TX_IDLE;
			if(AppNotifyTX!=NULL)
			{
				AppNotifyTX();
			}

		}
	}

}

