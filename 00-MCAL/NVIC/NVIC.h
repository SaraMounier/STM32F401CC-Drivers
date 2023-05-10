/*************************************************************
 * 
 * Filename: NVIC.h
 * Description: Header (interface) file of the NVIC driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __NVIC_H__
#define __NVIC_H__
#include "STD_TYPES.h"


#define REG_SIZE 32
#define PR_REG_SIZE 4
#define NVIC_IRQ_NUM_WWDG                   00
#define NVIC_IRQ_NUM_EXTI16_PVD             01
#define NVIC_IRQ_NUM_EXTI21_TAMP_STAMP      02
#define NVIC_IRQ_NUM_EXTI22_RTC_WKUP        03
#define NVIC_IRQ_NUM_FLASH                  04
#define NVIC_IRQ_NUM_RCC                    05
#define NVIC_IRQ_NUM_EXTI0                  06
#define NVIC_IRQ_NUM_EXTI1                  07
#define NVIC_IRQ_NUM_EXTI2                  08
#define NVIC_IRQ_NUM_EXTI3                  09
#define NVIC_IRQ_NUM_EXTI4                  10
#define NVIC_IRQ_NUM_DMA1_Stream0           11
#define NVIC_IRQ_NUM_DMA1_Stream1           12
#define NVIC_IRQ_NUM_DMA1_Stream2           13
#define NVIC_IRQ_NUM_DMA1_Stream3           14
#define NVIC_IRQ_NUM_DMA1_Stream4           15
#define NVIC_IRQ_NUM_DMA1_Stream5           16
#define NVIC_IRQ_NUM_DMA1_Stream6           17
#define NVIC_IRQ_NUM_ADC                    18
#define NVIC_IRQ_NUM_EXTI9_5                23
#define NVIC_IRQ_NUM_TIM1_BRK_TIM9          24
#define NVIC_IRQ_NUM_TIM1_UP_TIM10          25
#define NVIC_IRQ_NUM_TIM1_TRG_COM_TIM11     26
#define NVIC_IRQ_NUM_TIM1_CC                27
#define NVIC_IRQ_NUM_TIM2                   28
#define NVIC_IRQ_NUM_TIM3                   29
#define NVIC_IRQ_NUM_TIM4                   30
#define NVIC_IRQ_NUM_I2C1_EV                31
#define NVIC_IRQ_NUM_I2C1_ER                32
#define NVIC_IRQ_NUM_I2C2_EV                33
#define NVIC_IRQ_NUM_I2C2_ER                34
#define NVIC_IRQ_NUM_SPI1                   35
#define NVIC_IRQ_NUM_SPI2                   36
#define NVIC_IRQ_NUM_USART1                 37
#define NVIC_IRQ_NUM_USART2                 38
#define NVIC_IRQ_NUM_EXTI15_10              40
#define NVIC_IRQ_NUM_EXTI17_RTC_Alarm       41
#define NVIC_IRQ_NUM_EXTI18_OTG_FS_WKUP     42
#define NVIC_IRQ_NUM_DMA1_Stream7           47
#define NVIC_IRQ_NUM_SDIO                   49
#define NVIC_IRQ_NUM_TIM5                   50
#define NVIC_IRQ_NUM_SPI3                   51
#define NVIC_IRQ_NUM_DMA2_Stream0           56
#define NVIC_IRQ_NUM_DMA2_Stream1           57
#define NVIC_IRQ_NUM_DMA2_Stream2           58
#define NVIC_IRQ_NUM_DMA2_Stream3           59
#define NVIC_IRQ_NUM_DMA2_Stream4           60
#define NVIC_IRQ_NUM_OTG_FS                 67
#define NVIC_IRQ_NUM_DMA2_Stream5           68
#define NVIC_IRQ_NUM_DMA2_Stream6           69
#define NVIC_IRQ_NUM_DMA2_Stream7           70
#define NVIC_IRQ_NUM_USART6                 71
#define NVIC_IRQ_NUM_I2C3_EV                72
#define NVIC_IRQ_NUM_I2C3_ER                73
#define NVIC_IRQ_NUM_FPU                    81
#define NVIC_IRQ_NUM_SPI4                   84


#define NVIC_PR_NON_IMP_BITS   4
#define NVIC_PRIORRITY_00					(00 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_01					(01 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_02					(02 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_03					(03 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_04					(04 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_05					(05 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_06					(06 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_07					(07 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_08					(08 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_09					(09 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_10					(10 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_11					(11 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_12					(12 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_13					(13 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_14					(14 << NVIC_PR_NON_IMP_BITS)
#define NVIC_PRIORRITY_15					(15 << NVIC_PR_NON_IMP_BITS)

typedef enum {
	NVIC_enuOK,
	NVIC_enuNOK,
	NVIC_enuNullPtr,
}NVIC_ErrorStatus_t;

NVIC_ErrorStatus_t NVIC_enableIRQ(u32 NVIC_IRQ_NUM_);
NVIC_ErrorStatus_t NVIC_disableIRQ(u32 NVIC_IRQ_NUM_);
NVIC_ErrorStatus_t NVIC_setPendingIRQ(u32 NVIC_IRQ_NUM_);
NVIC_ErrorStatus_t NVIC_clearPendingIRQ(u32 NVIC_IRQ_NUM_);
NVIC_ErrorStatus_t NVIC_getActiveIRQStatus(u32 NVIC_IRQ_NUM_,u32 *PendingIRQVvalue);
NVIC_ErrorStatus_t NVIC_getPendingIRQStatus(u32 NVIC_IRQ_NUM_,u32 *PendingIRQValue);
NVIC_ErrorStatus_t NVIC_setPriorityIRQ(u32 NVIC_IRQ_NUM_,u32 NVIC_PRIORRITY_);
NVIC_ErrorStatus_t NVIC_getPriorityIRQ(u32 NVIC_IRQ_NUM_,u32 *PriorityValue);
NVIC_ErrorStatus_t NVIC_triggerSoftwareIRQ(u32 NVIC_IRQ_NUM_);



#endif /* __NVIC_H__ */
