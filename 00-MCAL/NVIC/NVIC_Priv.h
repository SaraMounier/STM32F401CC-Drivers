/*************************************************************
 * 
 * Filename: NVIC_Priv.h
 * Description: Private header file of the NVIC driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __NVIC_PRIV_H__
#define __NVIC_PRIV_H__

#define NVIC_BASE_ADDRESS   0x0E000E000
#define NVIC_(OFFSET)  (*(volatile u32*)(NVIC_BASE_ADDRESS+(OFFSET)))

/*Base Address of Interrupt set-enable register */
#define NVIC_ISER		NVIC_(0x100)
/*Base Address of Interrupt clear-enable register */
#define NVIC_ICER		NVIC_(0x180)
/*Base Address of Interrupt set-pending register */
#define NVIC_ISPR		NVIC_(0x200)
/*Base Address of Interrupt clear-pending register */
#define NVIC_ICPR		NVIC_(0x280)
/*Base Address of Interrupt active bit register */
#define NVIC_IABR		NVIC_(0x300)
/*Base Address of Interrupt priority register */
#define NVIC_IPR		NVIC_(0x400)
/*Base Address of Software trigger Interrupt register */
#define NVIC_STIR		NVIC_(0xF00)


#endif /* __NVIC_PRIV_H__ */
