/*************************************************************
 * 
 * Filename: NVIC.c
 * Description: Source file of the NVIC driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#include "includes\NVIC_Cfg.h"
#include "includes\NVIC_Priv.h"
#include "includes\NVIC.h"
#include "includes\STD_TYPES.h"

//static u32 GlobalStaticRegNumber=0,GlobalStaticPinNumber=0;
//static void IQR_Handler(u32 IRQ_Number,u32  *Reg_Num,u32 *Pin_Num )
//{
//	 *Reg_Num=IRQ_Number/32;
//	 *Pin_Num=IRQ_Number%32;
//}

NVIC_ErrorStatus_t NVIC_enableIRQ(u32 NVIC_IRQ_NUM_)
{
	NVIC_ErrorStatus_t Loc_NVICErrSatus=NVIC_enuOK;
	*((&NVIC_ISER)+(NVIC_IRQ_NUM_/REG_SIZE)) |= (1<<(NVIC_IRQ_NUM_%REG_SIZE));
	return Loc_NVICErrSatus;
}

NVIC_ErrorStatus_t NVIC_disableIRQ(u32 NVIC_IRQ_NUM_)
{
	NVIC_ErrorStatus_t Loc_NVICErrSatus=NVIC_enuOK;
	*((&NVIC_ICER)+ (NVIC_IRQ_NUM_/REG_SIZE)) |= (1<<(NVIC_IRQ_NUM_%REG_SIZE));
	return Loc_NVICErrSatus;
}

NVIC_ErrorStatus_t NVIC_setPendingIRQ(u32 NVIC_IRQ_NUM_)
{
	NVIC_ErrorStatus_t Loc_NVICErrSatus=NVIC_enuOK;
	*((&NVIC_ISPR)+ (NVIC_IRQ_NUM_ / REG_SIZE)) |= (1<<(NVIC_IRQ_NUM_ % REG_SIZE));
	return Loc_NVICErrSatus;
}

NVIC_ErrorStatus_t NVIC_clearPendingIRQ(u32 NVIC_IRQ_NUM_)
{
	NVIC_ErrorStatus_t Loc_NVICErrSatus=NVIC_enuOK;
	*((&NVIC_ICPR)+ (NVIC_IRQ_NUM_ / REG_SIZE)) |= (1<<(NVIC_IRQ_NUM_ % REG_SIZE));
	return Loc_NVICErrSatus;
}

NVIC_ErrorStatus_t NVIC_getPendingIRQStatus(u32 NVIC_IRQ_NUM_,u32 *PendingIRQValue)
{
	NVIC_ErrorStatus_t Loc_NVICErrSatus=NVIC_enuOK;
	*PendingIRQValue=(*((&NVIC_ISPR)+ (NVIC_IRQ_NUM_ / REG_SIZE)) >> (NVIC_IRQ_NUM_ % REG_SIZE)) & 0x01 ;
	return Loc_NVICErrSatus;
}

NVIC_ErrorStatus_t NVIC_getActiveIRQStatus(u32 NVIC_IRQ_NUM_,u32 *ActiveIRQStatus)
{
	NVIC_ErrorStatus_t Loc_NVICErrSatus=NVIC_enuOK;
	*ActiveIRQStatus=(*((&NVIC_IABR)+ (NVIC_IRQ_NUM_ / REG_SIZE)) >>(NVIC_IRQ_NUM_ % REG_SIZE)) &0x01 ;
	return Loc_NVICErrSatus;
}

NVIC_ErrorStatus_t NVIC_setPriorityIRQ(u32 NVIC_IRQ_NUM_,u32 NVIC_PRIORRITY_)
{
	NVIC_ErrorStatus_t Loc_NVICErrSatus=NVIC_enuOK;
	u32 temp= (*((&NVIC_IPR)+ (NVIC_IRQ_NUM_ / PR_REG_SIZE))) &= ~(255<<(NVIC_IRQ_NUM_ % PR_REG_SIZE)*8);
	*((&NVIC_IPR)+ (NVIC_IRQ_NUM_ / PR_REG_SIZE))= temp | (NVIC_PRIORRITY_<<(NVIC_IRQ_NUM_ % PR_REG_SIZE)*8);
	return Loc_NVICErrSatus;
}

NVIC_ErrorStatus_t NVIC_getPriorityIRQ(u32 NVIC_IRQ_NUM_,u32 *PriorityValue)
{
	NVIC_ErrorStatus_t Loc_NVICErrSatus=NVIC_enuOK;
	u32 temp_PriorityValue=((*((&NVIC_IPR)+ (NVIC_IRQ_NUM_ / PR_REG_SIZE)) >> (NVIC_IRQ_NUM_ % PR_REG_SIZE)*8)) &0xF0 ;
	*PriorityValue=temp_PriorityValue>>4;
	return Loc_NVICErrSatus;
}

NVIC_ErrorStatus_t NVIC_triggerSoftwareIRQ(u32 NVIC_IRQ_NUM_)
{
	NVIC_ErrorStatus_t Loc_NVICErrSatus=NVIC_enuOK;
	*((&NVIC_STIR)+ (NVIC_IRQ_NUM_ / REG_SIZE)) = (NVIC_IRQ_NUM_);
	return Loc_NVICErrSatus;
}
