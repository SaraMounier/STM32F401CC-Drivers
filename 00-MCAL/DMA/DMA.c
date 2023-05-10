/*************************************************************
 * 
 * Filename: DMA.c
 * Description: Source file of the DMA driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "./includes/DMA_Cfg.h"
#include "./includes/DMA_Priv.h"
#include "./includes/DMA.h"
static void SET_3B(u32* Reg,u32 Pin_Num,u32 Desired_Pin_Value );
static void SET_2B(u32* Reg,u32 Pin_Num,u32 Desired_Pin_Value );

void DMA_Init(void* DMAx,u8 DMA_StreamNumber)
{

		u8 StreamStatus=((((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR) >> DMA_enuSxCR_EN) &0x01;
	while(StreamStatus != DISABLE )
	{
		DMA_setStreamState( DMAx, DMA_StreamNumber, DISABLE);
		StreamStatus=((((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR) >> DMA_enuSxCR_EN) &0x01;
	}

	(((DMA_Registers_t *const)(DMAx))->DMA_LISR) =0;
	(((DMA_Registers_t *const)(DMAx))->DMA_HISR) =0;

}

DMA_ErrorStatus_t DMA_getStreamXInterruptFlag(void* DMAx,u32 InterruptFlagName,u8* FlagValue)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus;
	if(InterruptFlagName<32)
	{
		*FlagValue = ((((DMA_Registers_t *const)(DMAx))->DMA_LISR) >> InterruptFlagName) & 0x01;
		DMA_LocErrorStatus=DMA_enuOK;
	}
	else if(InterruptFlagName>=32 && InterruptFlagName<60)
	{
		*FlagValue = ((((DMA_Registers_t *const)(DMAx))->DMA_HISR) >> (InterruptFlagName-32)) & 0x01;
		DMA_LocErrorStatus=DMA_enuOK;
	}
	else
	{
		DMA_LocErrorStatus=DMA_enuNOK;
	}
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_clearStreamXInterruptFlag(void* DMAx,u32 InterruptFlagName)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus;
	if(InterruptFlagName>=64 &&InterruptFlagName<96)
	{
		(((DMA_Registers_t *const)(DMAx))->DMA_LIFCR) |= 1<< (InterruptFlagName-64);
		DMA_LocErrorStatus=DMA_enuOK;
	}
	else if(InterruptFlagName >=96 && InterruptFlagName<128)
	{
		(((DMA_Registers_t *const)(DMAx))->DMA_HIFCR) |= 1<< (InterruptFlagName-96);
		DMA_LocErrorStatus=DMA_enuOK;
	}
	else
	{
		DMA_LocErrorStatus=DMA_enuNOK;
	}
	return DMA_LocErrorStatus;
}



DMA_ErrorStatus_t DMA_selectStreamXChannel(void* DMAx,u8 DMA_StreamNumber,u32 DMA_CHANNEL_x)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	SET_3B(&(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR),DMA_enuSxCR_CHSEL0, DMA_CHANNEL_x );
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_setMemoryBurstTransferCfg(void* DMAx,u8 DMA_StreamNumber,u32 DMA_XBURST_INC_x)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	SET_2B(&(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR),DMA_enuSxCR_MBURST0, DMA_XBURST_INC_x );
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_setPeripheralBurstTransferCfg(void* DMAx,u8 DMA_StreamNumber,u32 DMA_XBURST_INC_x)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	SET_2B(&(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR),DMA_enuSxCR_PBURST0, DMA_XBURST_INC_x );
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t getCurrentTarget(void* DMAx,u8 DMA_StreamNumber,u8* CurrentTargetValue)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	*CurrentTargetValue = ((((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR) >> DMA_enuSxCR_CT) & 0x01;
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t setCurrentTarget(void* DMAx,u8 DMA_StreamNumber,u8 CurrentTarget)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	if(CurrentTarget==CURRENT_TARGET_MEMORY_1)
	{
			(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR)  |= (1<< DMA_enuSxCR_CT);
	}
	else if(CurrentTarget==CURRENT_TARGET_MEMORY_0)
	{
			(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR)  &= ~(1<< DMA_enuSxCR_CT);
	}
	else
	{
		DMA_LocErrorStatus=DMA_enuNOK;
	}
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_setMode(void* DMAx,u8 DMA_StreamNumber,u32 DMA_enuSxCR_Mode)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	if(DMA_enuSxCR_Mode==DMA_enuSxCR_DBM ||DMA_enuSxCR_Mode==DMA_enuSxCR_MINC ||DMA_enuSxCR_Mode==DMA_enuSxCR_PINC ||DMA_enuSxCR_Mode==DMA_enuSxCR_CIRC )
	{
	(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR) |= (1<< DMA_enuSxCR_Mode);
	}
	else
	{
		DMA_LocErrorStatus=DMA_enuNOK;
	}
	return DMA_LocErrorStatus;
}
DMA_ErrorStatus_t DMA_clearMode(void* DMAx,u8 DMA_StreamNumber,u32 DMA_enuSxCR_Mode)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	if(DMA_enuSxCR_Mode==DMA_enuSxCR_DBM ||DMA_enuSxCR_Mode==DMA_enuSxCR_MINC ||DMA_enuSxCR_Mode==DMA_enuSxCR_PINC ||DMA_enuSxCR_Mode==DMA_enuSxCR_CIRC )
	{
	(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR) &= ~(1<< DMA_enuSxCR_Mode);
	}
	else
	{
		DMA_LocErrorStatus=DMA_enuNOK;
	}
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_setPriorityLevel(void* DMAx,u8 DMA_StreamNumber,u32 DMA_PRIORITY_X)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	SET_2B(&(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR), DMA_enuSxCR_PL0, DMA_PRIORITY_X );
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_setPeripheralIncrementOffsetSize(void* DMAx,u8 DMA_StreamNumber,u32 DMA_PINCOS_X)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	if(DMA_PINCOS_X==DMA_PINCOS_FIXED_TO_4)
	{
			(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR)  |= (1<< DMA_enuSxCR_PINCOS);
	}
	else if(DMA_PINCOS_X==DMA_PINCOS_LINKED_TO_PSIZE)
	{
			(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR)  &= ~(1<< DMA_enuSxCR_PINCOS);
	}
	else
	{
		DMA_LocErrorStatus=DMA_enuNOK;
	}
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_setMemoryDataSize(void* DMAx,u8 DMA_StreamNumber,u32 DMA_DATA_SIZE_X)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	SET_2B(&(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR), DMA_enuSxCR_MSIZE0, DMA_DATA_SIZE_X );
	return DMA_LocErrorStatus;
}
DMA_ErrorStatus_t DMA_setPeripheralDataSize(void* DMAx,u8 DMA_StreamNumber,u32 DMA_DATA_SIZE_X)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	SET_2B(&(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR), DMA_enuSxCR_PSIZE0, DMA_DATA_SIZE_X );
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_setDataTransferDirection(void* DMAx,u8 DMA_StreamNumber,u32 DMA_DATA_TRANSFER_X)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	SET_2B(&(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR), DMA_enuSxCR_DIR0, DMA_DATA_TRANSFER_X );
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_selectFlowController(void* DMAx,u8 DMA_StreamNumber,u32 FLOW_CONTROLLER_X)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	if(FLOW_CONTROLLER_X==FLOW_CONTROLLER_PERIPHERAL)
	{
			(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR)  |= (1<< DMA_enuSxCR_PFCTRL);
	}
	else if(FLOW_CONTROLLER_X==FLOW_CONTROLLER_DMA)
	{
			(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR)  &= ~(1<< DMA_enuSxCR_PFCTRL);
	}
	else
	{
		DMA_LocErrorStatus=DMA_enuNOK;
	}
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_setInterruptState(void* DMAx,u8 DMA_StreamNumber,u32 DMA_enuSxCR_IntName, u8 Interrupt_State)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	if(Interrupt_State==ENABLE)
	{
		(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR) |= (1<< DMA_enuSxCR_IntName);
		if(DMA_enuSxCR_IntName==DMA_enuSxFCR_FEIE)
		{
			(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxFCR) |= (1<< DMA_enuSxCR_IntName);
		}

	}
	else if(Interrupt_State==DISABLE)
	{
		(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR) &= ~(1<< DMA_enuSxCR_IntName);
		if(DMA_enuSxCR_IntName==DMA_enuSxFCR_FEIE)
		{
			(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxFCR) &= ~(1<< DMA_enuSxCR_IntName);
		}
	}
	else
	{
		DMA_LocErrorStatus = DMA_enuNOK;
	}
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_setStreamState(void* DMAx,u8 DMA_StreamNumber, u8 Stream_State)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	if(Stream_State==ENABLE)
	{
			(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR)  |= (1<< DMA_enuSxCR_EN);
	}
	else if(Stream_State==DISABLE)
	{
			(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxCR)  &= ~(1<< DMA_enuSxCR_EN);
	}
	else
	{
		DMA_LocErrorStatus=DMA_enuNOK;
	}
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_setNumberOfDataToBeTransferred(void* DMAx,u8 DMA_StreamNumber, u16 NumberOfData)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxNDTR) = NumberOfData;
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_setPeripheralAddres(void* DMAx,u8 DMA_StreamNumber,  void* PeripheralAddress)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxPAR) =(u32 ) PeripheralAddress;
	return DMA_LocErrorStatus;
}
DMA_ErrorStatus_t DMA_setMemory0Addres(void* DMAx,u8 DMA_StreamNumber,  void* Memory0Address)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxM0AR) =(u32 )Memory0Address;
	return DMA_LocErrorStatus;
}
DMA_ErrorStatus_t DMA_setMemory1Addres(void* DMAx,u8 DMA_StreamNumber, void* Memory1Address)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxM1AR) = (u32 )Memory1Address;
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_getFIFOStatus(void* DMAx,u8 DMA_StreamNumber, u32* FIFO_LEVEL_X)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	*FIFO_LEVEL_X=((((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxFCR) >>DMA_enuSxFCR_FS0) & 0b111;
	return DMA_LocErrorStatus;
}

DMA_ErrorStatus_t DMA_setDirectModeStatus(void* DMAx,u8 DMA_StreamNumber, u8 DirectModeStatus)
{
	DMA_ErrorStatus_t DMA_LocErrorStatus=DMA_enuOK;
	if(DirectModeStatus==DISABLE)
	{
			(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxFCR)  |= (1<< DMA_enuSxFCR_DMDIS);
	}
	else if(DirectModeStatus==ENABLE)
	{
			(((DMA_Registers_t *const)(DMAx))->StreamRegs[DMA_StreamNumber].DMA_SxFCR)  &= ~(1<< DMA_enuSxFCR_DMDIS);
	}
	else
	{
		DMA_LocErrorStatus=DMA_enuNOK;
	}
	return DMA_LocErrorStatus;
}


void (*DMA2_Stream2_CBF)(void)=NULL;

DMA_ErrorStatus_t DMA2_Stream2_setCallBack( void(* DMA2_Stream2_CBF_MAIN)(void) )
{
	DMA_ErrorStatus_t Loc_DMAErrStatus;
	if (DMA2_Stream2_CBF_MAIN !=NULL)
	{
		DMA2_Stream2_CBF=DMA2_Stream2_CBF_MAIN ;
		Loc_DMAErrStatus=DMA_enuOK;
	}
	else
	{
		Loc_DMAErrStatus=DMA_enuNullPtr;
	}
	return Loc_DMAErrStatus;
}

 void DMA2_Stream2_IRQHandler(void)
{
	 u8 FlagValue;
	DMA_getStreamXInterruptFlag(DMA2, DMA_enuLISR_TCIF2, &FlagValue);
	if(FlagValue==ENABLE)
	{
	DMA_clearStreamXInterruptFlag( DMA2,DMA_enuLIFCR_CTCIF2);
	DMA_clearStreamXInterruptFlag( DMA2,DMA_enuLIFCR_CDMEIF2);
	DMA_clearStreamXInterruptFlag( DMA2,DMA_enuLIFCR_CFEIF2);
	DMA_clearStreamXInterruptFlag( DMA2,DMA_enuLIFCR_CHTIF2);
	DMA_clearStreamXInterruptFlag( DMA2,DMA_enuLIFCR_CTEIF2);
	if (DMA2_Stream2_CBF !=NULL)
	{
		DMA2_Stream2_CBF();
	}
	}

}



void (*DMA2_Stream7_CBF)(void)=NULL;

DMA_ErrorStatus_t DMA2_Stream7_setCallBack( void(* DMA2_Stream7_CBF_MAIN)(void) )
{
	DMA_ErrorStatus_t Loc_DMAErrStatus;
	if (DMA2_Stream7_CBF_MAIN !=NULL)
	{
		DMA2_Stream7_CBF=DMA2_Stream7_CBF_MAIN ;
		Loc_DMAErrStatus=DMA_enuOK;
	}
	else
	{
		Loc_DMAErrStatus=DMA_enuNullPtr;
	}
	return Loc_DMAErrStatus;
}

void DMA2_Stream7_IRQHandler(void)
{
	u8 FlagValue;
	DMA_getStreamXInterruptFlag(DMA2, DMA_enuHISR_TCIF7, &FlagValue);
	if(FlagValue==ENABLE)
	{
		DMA_clearStreamXInterruptFlag( DMA2,DMA_enuHIFCR_CTCIF7);
	DMA_clearStreamXInterruptFlag( DMA2,DMA_enuHIFCR_CDMEIF7);
	DMA_clearStreamXInterruptFlag( DMA2,DMA_enuHIFCR_CFEIF7);
	DMA_clearStreamXInterruptFlag( DMA2,DMA_enuHIFCR_CHTIF7);
	DMA_clearStreamXInterruptFlag( DMA2,DMA_enuHIFCR_CTEIF7);
	if (DMA2_Stream7_CBF !=NULL)
	{
		DMA2_Stream7_CBF();
	}
	}

}

static void SET_3B(u32* Reg,u32 Pin_Num,u32 Desired_Pin_Value )
{
	u32 TempVar;
	TempVar = *(Reg) & ~(CLR_MASK_3B <<Pin_Num);
	*(Reg) = TempVar | (Desired_Pin_Value<<Pin_Num);
}

static void SET_2B(u32* Reg,u32 Pin_Num,u32 Desired_Pin_Value )
{
	u32 TempVar;
	TempVar = *(Reg) & ~(CLR_MASK_2B <<Pin_Num);
	*(Reg) = TempVar | (Desired_Pin_Value<<Pin_Num);
}
