/*************************************************************
 * 
 * Filename: SUART_Priv.h
 * Description: Private header file of the SUART driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __SUART_PRIV_H__
#define __SUART_PRIV_H__
#include "STD_TYPES.h"

#define  USART1_BASE_ADDRESS	 (0x40011000)
#define  USART6_BASE_ADDRESS	 (*( (volatile u32*)(0x40011400) ))

#endif /* __SUART_PRIV_H__ */
