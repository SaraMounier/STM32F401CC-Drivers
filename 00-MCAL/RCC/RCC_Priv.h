/*************************************************************
 * 
 * Filename: RCC_Priv.h
 * Description: Private header file of the RCC driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/

#ifndef __RCC_PRIV_H__
#define __RCC_PRIV_H__
#include "STD_TYPES.h"
/*
#define RCC_CR 		(*((volatile u32*)0x40023800))
#define RCC_PLLCFGR (*(volatile u32 *)0x40023804) // PLL Configuration register
#define RCC_CFGR 	(*(volatile u32 *)0x40023808) //CLOCK Configuration register
*/

typedef struct{
	u32 RCC_CR;
	u32 RCC_PLLCFGR;
	u32 RCC_CFGR;
	u32 RCC_CIR;
	u32 RCC_AHB1RSTR;
	u32 RCC_AHB2RSTR;
	u32 Reserved0;
	u32 Reserved1;
	u32 RCC_APB1RSTR;
	u32 RCC_APB2RSTR;
	u32 Reserved2;
	u32 Reserved3;
	u32 RCC_AHB1ENR;
	u32 RCC_AHB2ENR;
	u32 Reserved4;
	u32 Reserved5;
	u32 RCC_APB1ENR;
	u32 RCC_APB2ENR;
	u32 Reserved6;
	u32 Reserved7;
	u32 RCC_AHB1LPENR;
	u32 RCC_AHB2LPENR;
	u32 Reserved8;
	u32 Reserved9;
	u32 RCC_APB1LPENR;
	u32 RCC_APB2LPENR;
	u32 Reserved10;
	u32 Reserved11;
	u32 RCC_BDCR;
	u32 RCC_CSR;
	u32 Reserved12;
	u32 Reserved13;
	u32 RCC_SSCGR;
	u32 RCC_PLLI2SCFGR;
	u32 Reserved14;
	u32 CC_DCKCFGR;

}RCC_Registers;

#define RCC_BASEADRESS 0x40023800

#endif /* __RCC_PRIV_H__ */
