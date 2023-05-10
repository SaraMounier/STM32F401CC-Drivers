/*************************************************************
 * 
 * Filename: RCC.c
 * Description: Source file of the RCC driver.
 * Author: Sara Mounier
 * Github: https://github.com/SaraMounier
 * 
 *************************************************************/
#include "includes\RCC.h"
#include "includes\STD_TYPES.h"
#include "includes\RCC_Cfg.h"
#include "includes\RCC_Priv.h"

#define ENABLED 1
#define DISABLED 0

 RCC_Registers *const rcc= ( RCC_Registers *const) (RCC_BASEADRESS);


 static void Set_PLLx(u32 PLLx_,u32 PLLx_Mask,u32 PLLx_Start){
 u32 LocTempVar= (rcc->RCC_PLLCFGR) & PLLx_Mask;
 (rcc->RCC_PLLCFGR)= LocTempVar | PLLx_<<(PLLx_Start);
 }

 static void Set_RCC_CFGR(u32 SysClk_,u32 SysClk_Mask,u32 SHIFT_Start){
 u32 LocTempVar= (rcc->RCC_CFGR) & SysClk_Mask;
 (rcc->RCC_CFGR)= LocTempVar | SysClk_<<(SHIFT_Start);
 }
/*
 static void Set_RCC_AHB1RSTR(u32 AHB1RSTR_BIT,u32 AHB1RSTR_Mask,u32 SHIFT_Start){
 u32 LocTempVar= (rcc->RCC_AHB1RSTR) & AHB1RSTR_Mask;
 (rcc->RCC_AHB1RSTR)= LocTempVar | AHB1RSTR_BIT<<(SHIFT_Start);
 }
*/


rcc_enuErrorStatus_t rcc_getSWS(u8* Add_RCC_CurrSWS)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	u8 LocSWS0Val= (( (rcc->RCC_CFGR) >> (RCC_CFGR_enuSWS0)) &0x01);
	u8 LocSWS1Val= (( (rcc->RCC_CFGR) >> (RCC_CFGR_enuSWS1)) &0x01);
	if(LocSWS1Val==0 && LocSWS0Val==0)
	{
		*Add_RCC_CurrSWS=SysClk_HSI_SW;
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else if(LocSWS1Val==0 && LocSWS0Val==1)
	{
		*Add_RCC_CurrSWS=SysClk_HSE_SW;
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else if(LocSWS1Val==1 && LocSWS0Val==0)
	{
		*Add_RCC_CurrSWS=SysClk_PLL_SW;
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}

return 	Loc_RccErrStsReturn;
}


rcc_enuErrorStatus_t rcc_setHSION(void)
{
	u8 LocHSIValRdy;
	u8 Loctimeout=255;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	((rcc-> RCC_CR) |= (1<< (RCC_CR_enuHSION)));
	LocHSIValRdy=(((rcc->RCC_CR) >> RCC_CR_enuHSIRDY) & 0x01); //get hsirdy
	while (LocHSIValRdy!=ENABLED  && Loctimeout>0 )
	{
		Loctimeout--;
	}

	if(LocHSIValRdy==ENABLED)
	{
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}

return Loc_RccErrStsReturn;
}

rcc_enuErrorStatus_t rcc_setHSIOFF(void)
{
	u8 LocHSIValRdy;
	u8 Loctimeout=255;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	((rcc-> RCC_CR) &= ~(1<< (RCC_CR_enuHSION)));
	LocHSIValRdy=(((rcc->RCC_CR) >> RCC_CR_enuHSIRDY) & 0x01); //get hsirdy
	while (LocHSIValRdy!=DISABLED  && Loctimeout>0 )
	{
		Loctimeout--;
	}

	if(LocHSIValRdy==DISABLED)
	{
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}

return Loc_RccErrStsReturn;
}


rcc_enuErrorStatus_t rcc_setHSEON(void)
{
	u8 LocHSEValRdy;
	u8 Loctimeout=255;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	(rcc->RCC_CR) |= (1<< RCC_CR_enuHSEON);
	LocHSEValRdy= ((rcc->RCC_CR) >> RCC_CR_enuHSERDY) & 0x01;
	while ( LocHSEValRdy !=ENABLED && Loctimeout>0 )
	{
		LocHSEValRdy= ((rcc->RCC_CR) >> RCC_CR_enuHSERDY) & 0x01;
		Loctimeout--;
	}
	if(LocHSEValRdy==ENABLED)
	{
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}

return Loc_RccErrStsReturn;
}


rcc_enuErrorStatus_t rcc_setHSEOFF(void)
{
	u8 LocHSEValRdy;
	u8 Loctimeout=255;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	(rcc->RCC_CR) &= ~(1<< RCC_CR_enuHSEON);
	LocHSEValRdy= ((rcc->RCC_CR) >> RCC_CR_enuHSERDY) & 0x01;
	while ( LocHSEValRdy !=DISABLED && Loctimeout>0 )
	{
		LocHSEValRdy= ((rcc->RCC_CR) >> RCC_CR_enuHSERDY) & 0x01;
		Loctimeout--;
	}
	if(LocHSEValRdy==DISABLED)
	{
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}

return Loc_RccErrStsReturn;
}

rcc_enuErrorStatus_t rcc_setPLLON(void)
{
	u8 LocPLLValRdy;
	u8 Loctimeout=255;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	(rcc->RCC_CR) |= (1<< RCC_CR_enuPLLON);
	LocPLLValRdy= ((rcc->RCC_CR) >> RCC_CR_enuPLLRDY) & 0x01;
	while ( LocPLLValRdy!=ENABLED  && Loctimeout>0 )
	{
		Loctimeout--;
	}
	if(LocPLLValRdy==ENABLED)
	{
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}

return Loc_RccErrStsReturn;
}

rcc_enuErrorStatus_t rcc_setPLLOFF(void)
{
	u8 LocPLLValRdy;
	u8 Loctimeout=255;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	(rcc->RCC_CR) &= ~(1<< RCC_CR_enuPLLON);
	LocPLLValRdy= ((rcc->RCC_CR) >> RCC_CR_enuPLLRDY) & 0x01;
	while ( LocPLLValRdy!=DISABLED  && Loctimeout>0 )
	{
		Loctimeout--;
	}
	if(LocPLLValRdy==DISABLED)
	{
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}

return Loc_RccErrStsReturn;
}

rcc_enuErrorStatus_t rcc_setPLLI2SON(void)
{
	u8 LocPLLI2SValRdy;
	u8 Loctimeout=255;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	(rcc->RCC_CR) |= (1<< RCC_CR_enuPLLI2SON);
	LocPLLI2SValRdy= ((rcc->RCC_CR) >> RCC_CR_enuPLLI2SRDY) & 0x01;
	while ( LocPLLI2SValRdy!=ENABLED  && Loctimeout>0 )
	{
		Loctimeout--;
	}
	if(LocPLLI2SValRdy==ENABLED)
	{
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}

return Loc_RccErrStsReturn;
}

rcc_enuErrorStatus_t rcc_setPLLI2SOFF(void)
{
	u8 LocPLLI2SValRdy;
	u8 Loctimeout=255;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	(rcc->RCC_CR) &= ~(1<< RCC_CR_enuPLLI2SON);
	LocPLLI2SValRdy= ((rcc->RCC_CR) >> RCC_CR_enuPLLI2SRDY) & 0x01;
	while ( LocPLLI2SValRdy!=DISABLED  && Loctimeout>0 )
	{
		Loctimeout--;
	}
	if(LocPLLI2SValRdy==DISABLED)
	{
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}

return Loc_RccErrStsReturn;
}


rcc_enuErrorStatus_t rcc_setCSSON(void)
{	u8 LocCSSVal;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	(rcc->RCC_CR)|= (1<<RCC_CR_enuCSSON);
	LocCSSVal=((rcc->RCC_CR) >>(RCC_CR_enuCSSON)) & 0X01;
	if(LocCSSVal==ENABLED)
	{
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}
	return Loc_RccErrStsReturn;
}
rcc_enuErrorStatus_t rcc_setCSSOFF(void)
{
	u8 LocCSSVal;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	(rcc->RCC_CR) &= ~(1<<RCC_CR_enuCSSON);
	LocCSSVal=((rcc->RCC_CR) >>(RCC_CR_enuCSSON)) & 0X01;
	if(LocCSSVal==DISABLED)
	{
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}
	return Loc_RccErrStsReturn;
}


rcc_enuErrorStatus_t rcc_setHSEBYPON(void)
{
	u8 LocHSEBYPVal;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	(rcc->RCC_CR) |= (1 << RCC_CR_enuHSEBYP);
	LocHSEBYPVal=((rcc->RCC_CR) >> (RCC_CR_enuHSEBYP)) & 0X01;
	if(LocHSEBYPVal==ENABLED)
	{
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}
	return Loc_RccErrStsReturn;
}

rcc_enuErrorStatus_t rcc_setHSEBYPOFF(void)
{
	u8 LocHSEBYPVal;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	(rcc->RCC_CR) &= ~(1 << RCC_CR_enuHSEBYP);
	LocHSEBYPVal=((rcc->RCC_CR) >> (RCC_CR_enuHSEBYP)) & 0X01;
	if(LocHSEBYPVal==DISABLED)
	{
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}
	return Loc_RccErrStsReturn;
}

/*mSH 3ARFA A3ML FUNCTIONS LL GET WLA LA*/

/*********************************************************/
rcc_enuErrorStatus_t rcc_setPLLSRC(u8 PLLSRC_)
{
	u8 LocPLLSRCVal;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if(PLLSRC_==PLLSRC_HSI)
	{
		(rcc->RCC_PLLCFGR) &= ~(1 << RCC_PLLCFGR_enuPLLSRC);
		LocPLLSRCVal=((rcc->RCC_PLLCFGR) >> (RCC_PLLCFGR_enuPLLSRC)) & 0X01;
		if(LocPLLSRCVal==PLLSRC_HSI)
		{
			Loc_RccErrStsReturn=rcc_enuOK;
		}
		else
		{
			Loc_RccErrStsReturn=rcc_enuNOK;
		}
	}
	else if(PLLSRC_==PLLSRC_HSE)
	{
		(rcc->RCC_PLLCFGR) |= (1 << RCC_PLLCFGR_enuPLLSRC);
		LocPLLSRCVal=((rcc->RCC_PLLCFGR) >> (RCC_PLLCFGR_enuPLLSRC)) & 0X01;
		if(LocPLLSRCVal==PLLSRC_HSE)
		{
			Loc_RccErrStsReturn=rcc_enuOK;
		}
		else
		{
			Loc_RccErrStsReturn=rcc_enuNOK;
		}
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}

	return Loc_RccErrStsReturn;
}


rcc_enuErrorStatus_t rcc_getPLLSRC(u8* Add_u8PLLSRC)
{
	u8 LocPLLSRCVal;
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	LocPLLSRCVal=((rcc->RCC_PLLCFGR) >> (RCC_PLLCFGR_enuPLLSRC)) & 0X01;
	if(LocPLLSRCVal==PLLSRC_HSI)
	{
		*Add_u8PLLSRC=PLLSRC_HSI;
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else if(LocPLLSRCVal==PLLSRC_HSE)
	{
		*Add_u8PLLSRC=PLLSRC_HSE;
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuNOK;
	}

return Loc_RccErrStsReturn;
}


rcc_enuErrorStatus_t rcc_configPLLSysClk(u8 PLLQ_, u8 PLLP_, u16 PLLN_,u8 PLLM_)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn=0;
	u8 LocTempVar;
	LocTempVar= (rcc->RCC_CR>>RCC_CR_enuPLLRDY) &0x01;
	if(LocTempVar == ENABLED)
	{
		Loc_RccErrStsReturn= rcc_enuPLLIsAlreadyConfigured;
	}

	else if(PLLQ_>=PLLQ_02 && PLLQ_<=PLLQ_15)
	{
		if(PLLP_ > PLLP_02 && PLLP_ <= PLLP_08)
		{
			if(PLLN_>=PLLN_192 && PLLN_<=PLLN_432)
			{
				if(PLLM_>=PLLM_02 && PLLM_<=PLLM_63)
				{
					Loc_RccErrStsReturn=rcc_enuOK;
					Set_PLLx(PLLQ_, PLLQ_MASK,RCC_PLLCFGR_enuPLLQ0  );
					Set_PLLx(PLLP_, PLLP_MASK,RCC_PLLCFGR_enuPLLP0  );
					Set_PLLx(PLLN_, PLLN_MASK,RCC_PLLCFGR_enuPLLN0  );
					Set_PLLx( PLLM_, PLLM_MASK,RCC_PLLCFGR_enuPLLM0  );
				}
			}
		}
	}

	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}

return Loc_RccErrStsReturn;
}

/*.........................................*/

rcc_enuErrorStatus_t rcc_setSW(u8 SysClk_)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if (SysClk_==SysClk_HSI_SW || SysClk_== SysClk_HSE_SW || SysClk_== SysClk_PLL_SW)
	{
		Set_RCC_CFGR(SysClk_, SW_MASK,RCC_CFGR_enuSW0);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}


rcc_enuErrorStatus_t rcc_setMCO2(u32 MCO2_SelClk)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if (MCO2_SelClk==MCO2_SelClk_SYSCLK || MCO2_SelClk==MCO2_SelClk_PLLI2S  || MCO2_SelClk==MCO2_SelClk_HSE || MCO2_SelClk==MCO2_SelClk_PLL)
	{
		Set_RCC_CFGR(MCO2_SelClk, MCO2_MASK,RCC_CFGR_enuMCO20);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;

}

rcc_enuErrorStatus_t rcc_setMCO1(u8 MCO1SelClk_)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if (MCO1SelClk_==MCO1_SelClk_HSI || MCO1SelClk_==MCO1_SelClk_LSE  || MCO1SelClk_==MCO1_SelClk_HSE || MCO1SelClk_==MCO1_SelClk_PLL)
	{
		Set_RCC_CFGR(MCO1SelClk_, MCO1_MASK, RCC_CFGR_enuMCO10);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}

rcc_enuErrorStatus_t rcc_setMCO2PRE(u8 MCO2DivBy_)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if (MCO2DivBy_==MCO2DivBy_NODIV || MCO2DivBy_==MCO2DivBy_2  || MCO2DivBy_==MCO2DivBy_3 || MCO2DivBy_==MCO2DivBy_4 || MCO2DivBy_==MCO2DivBy_5 )
	{
		Set_RCC_CFGR(MCO2DivBy_, MCO2PRE_MASK, RCC_CFGR_enuMCO2PRE0);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}
rcc_enuErrorStatus_t rcc_setMCO1PRE(u8 MCO1DivBy_)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if (MCO1DivBy_==MCO1DivBy_NODIV || MCO1DivBy_==MCO1DivBy_2  || MCO1DivBy_==MCO1DivBy_3 || MCO1DivBy_==MCO1DivBy_4 || MCO1DivBy_==MCO1DivBy_5 )
	{
		Set_RCC_CFGR(MCO1DivBy_, MCO1PRE_MASK, RCC_CFGR_enuMCO1PRE0);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}

rcc_enuErrorStatus_t rcc_setI2SSRC(u8 I2SSRC_)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if (I2SSRC_==I2SSRC_PLLI2S || I2SSRC_==I2SSRC_I2S_CKIN )
	{
		Set_RCC_CFGR(I2SSRC_, I2SSRC_MASK, RCC_CFGR_enuI2SSRC);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}

rcc_enuErrorStatus_t rcc_setRTCPRE(u8 RTC_HSEDivBy_)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if (RTC_HSEDivBy_>RTC_HSEDivBy_NO0 && RTC_HSEDivBy_<=RTC_HSEDivBy_31 )
	{
		Set_RCC_CFGR(RTC_HSEDivBy_, RTCPRE_MASK, RCC_CFGR_enuRTCPRE0);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;

}

rcc_enuErrorStatus_t rcc_setAPB1_PPRE1(u8 AHBClkDivBy_)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if (AHBClkDivBy_==AHBClkDiv_NO || AHBClkDivBy_== AHBClkDiv_02 || AHBClkDivBy_==AHBClkDiv_04 || AHBClkDivBy_==AHBClkDiv_08|| AHBClkDivBy_==AHBClkDiv_16 )
	{
		Set_RCC_CFGR(AHBClkDivBy_, APB1_PPRE1_MASK, RCC_CFGR_enuPPRE10);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}

/*PPRE2: APB high-speed prescaler (APB2)
Set and cleared by software to control APB high-speed clock division factor.rcc_enuErrorStatus_t rcc_setAPB2_PPRE(u8 AHBClkDivBy_);
*/

rcc_enuErrorStatus_t rcc_setAPB2_PPRE2(u8 AHBClkDivBy_)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if (AHBClkDivBy_==AHBClkDiv_NO || AHBClkDivBy_==AHBClkDiv_02 || AHBClkDivBy_==AHBClkDiv_04 || AHBClkDivBy_==AHBClkDiv_08|| AHBClkDivBy_==AHBClkDiv_16 )
	{
		Set_RCC_CFGR(AHBClkDivBy_, APB2_PPRE2_MASK, RCC_CFGR_enuPPRE20);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}

/*
HPRE: AHB prescaler Set and cleared by software to control AHB clock division factor.
Caution: The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after
HPRE write*/

rcc_enuErrorStatus_t rcc_setAHB_HPRE(u8 SysClkDivBy_)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if (SysClkDivBy_==SysClkDivBy_NO || SysClkDivBy_==SysClkDivBy_002 || SysClkDivBy_== SysClkDivBy_004 || SysClkDivBy_==SysClkDivBy_008||SysClkDivBy_==SysClkDivBy_016 || SysClkDivBy_==SysClkDivBy_064 || SysClkDivBy_==SysClkDivBy_128 || SysClkDivBy_==SysClkDivBy_256 || SysClkDivBy_==SysClkDivBy_512 )
	{
		Set_RCC_CFGR(SysClkDivBy_, AHB_HPRE_MASK, RCC_CFGR_enuHPRE0);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
	return Loc_RccErrStsReturn;
}

/****************RCC clock interrupt register (RCC_CIR)*********************/

/*********************RCC AHB peripheral reset register (RCC_AHBRSTR)*********************/

rcc_enuErrorStatus_t rcc_reset_AHB1RSTR(tenuRCC_AHB1RSTR_Bits RCC_AHB1RSTR_enu )
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if((RCC_AHB1RSTR_enu > RCC_AHB1RSTR_enuGPIOARST && RCC_AHB1RSTR_enu <= RCC_AHB1RSTR_enuGPIOERST) || RCC_AHB1RSTR_enu == RCC_AHB1RSTR_enuGPIOHRST ||\
		RCC_AHB1RSTR_enu == RCC_AHB1RSTR_enuCRCRST   || RCC_AHB1RSTR_enu == RCC_AHB1RSTR_enuDMA2RST   || RCC_AHB1RSTR_enu == RCC_AHB1RSTR_enuDMA1RST)
	{
		(rcc->RCC_AHB1RSTR) |= AXBRSTR_RESET << (RCC_AHB1RSTR_enu);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}

rcc_enuErrorStatus_t rcc_reset_AHB2RSTR(tenuRCC_AHB2RSTR_Bits RCC_AHB2RSTR_enu)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if(RCC_AHB2RSTR_enu == RCC_AHB2RSTR_enuOTGFSRST)
	{
		(rcc->RCC_AHB2RSTR) |= AXBRSTR_RESET << (RCC_AHB2RSTR_enu);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}

/*RCC_AHB1ENR*/

/*Options:
 * AHB1ENR_Clk_Enable
 * AHB1ENR_Clk_Disable*/

rcc_enuErrorStatus_t rcc_AHB1ENR_Clk(tenuRCC_AHB1ENR_Bits RCC_AHB1ENR_enu,u32 AXBENR_Clk_Mode)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if((RCC_AHB1ENR_enu > RCC_AHB1ENR_enuGPIOAEN && RCC_AHB1ENR_enu <= RCC_AHB1ENR_enuGPIOEEN) || RCC_AHB1ENR_enu <= RCC_AHB1ENR_enuGPIOAEN ||
		RCC_AHB1ENR_enu == RCC_AHB1ENR_enuCRCEN   || RCC_AHB1ENR_enu == RCC_AHB1ENR_enuDMA1EN   || RCC_AHB1ENR_enu == RCC_AHB1ENR_enuDMA2EN )
	{
		if(AXBENR_Clk_Mode==AXBENR_Clk_ENABLED)
		{
			(rcc->RCC_AHB1ENR) |= AXBENR_Clk_ENABLED << (RCC_AHB1ENR_enu);
			Loc_RccErrStsReturn=rcc_enuOK;
		}
		else if(AXBENR_Clk_Mode==AXBENR_Clk_DISABLED)
		{
			(rcc->RCC_AHB1ENR) &= ~(AXBENR_Clk_ENABLED << (RCC_AHB1ENR_enu));
			Loc_RccErrStsReturn=rcc_enuOK;
		}
		else
		{
			Loc_RccErrStsReturn=rcc_enuInvalidParameter;
		}
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}


rcc_enuErrorStatus_t rcc_AHB2ENR_Clk(tenuRCC_AHB2ENR_Bits RCC_AHB2ENR_enu,u32 AXBENR_Clk_Mode)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if(RCC_AHB2ENR_enu == RCC_AHB2ENR_enuOTGFSEN)
	{
		if(AXBENR_Clk_Mode == AXBENR_Clk_ENABLED)
		{
			(rcc->RCC_AHB2ENR) |= AXBENR_Clk_ENABLED << (RCC_AHB2ENR_enu);
			Loc_RccErrStsReturn=rcc_enuOK;
		}
		else if(AXBENR_Clk_Mode == AXBENR_Clk_DISABLED)
		{
			(rcc->RCC_AHB2ENR) &= ~(AXBENR_Clk_ENABLED << (RCC_AHB2ENR_enu));
			Loc_RccErrStsReturn=rcc_enuOK;
		}
		else
		{
			Loc_RccErrStsReturn=rcc_enuInvalidParameter;
		}
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}


/*********************RCC APB peripheral reset register (RCC_APBRSTR)*********************/

rcc_enuErrorStatus_t rcc_reset_APB1RSTR(tenuRCC_APB1RSTR_Bits RCC_APB1RSTR_enu )
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if((RCC_APB1RSTR_enu >= RCC_APB1RSTR_enuTIM2RST && RCC_APB1RSTR_enu <= RCC_APB1RSTR_enuTIM5RST) || RCC_APB1RSTR_enu == RCC_APB1RSTR_enuWWDGRST   ||
		RCC_APB1RSTR_enu == RCC_APB1RSTR_enuSPI2RST || RCC_APB1RSTR_enu == RCC_APB1RSTR_enuSPI3RST  || RCC_APB1RSTR_enu == RCC_APB1RSTR_enuUSART2RST ||
	   (RCC_APB1RSTR_enu >= RCC_APB1RSTR_enuI2C1RST && RCC_APB1RSTR_enu <= RCC_APB1RSTR_enuI2C3RST) || RCC_APB1RSTR_enu == RCC_APB1RSTR_enuPWRRST )
	{
		(rcc->RCC_APB1RSTR) |= AXBRSTR_RESET << (RCC_APB1RSTR_enu);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}


rcc_enuErrorStatus_t rcc_reset_APB2RSTR(tenuRCC_APB2RSTR_Bits RCC_APB2RSTR_enu)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if((RCC_APB2RSTR_enu == RCC_APB2RSTR_enuTIM1RST ||  RCC_APB2RSTR_enu == RCC_APB2RSTR_enuUSART1RST) || RCC_APB2RSTR_enu == RCC_APB2RSTR_enuUSART6RST  ||
		RCC_APB2RSTR_enu == RCC_APB2RSTR_enuADC1RST || (RCC_APB2RSTR_enu >= RCC_APB2RSTR_enuSDIORST    && RCC_APB2RSTR_enu <= RCC_APB2RSTR_enuSYSCFGRST) ||
	   (RCC_APB2RSTR_enu >= RCC_APB2RSTR_enuTIM9RST &&  RCC_APB2RSTR_enu <= RCC_APB2RSTR_enuTIM11RST))
	{
		(rcc->RCC_APB2RSTR) |= AXBRSTR_RESET << (RCC_APB2RSTR_enu);
		Loc_RccErrStsReturn=rcc_enuOK;
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}


rcc_enuErrorStatus_t rcc_APB1ENR_Clk(tenuRCC_APB1ENR_Bits RCC_APB1ENR_enu,u32 AXBENR_Clk_Mode)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if((RCC_APB1ENR_enu >= RCC_APB1ENR_enuTIM2EN && RCC_APB1ENR_enu <= RCC_APB1ENR_enuTIM5EN) || RCC_APB1ENR_enu == RCC_APB1ENR_enuWWDGEN   ||
		RCC_APB1ENR_enu == RCC_APB1ENR_enuSPI2EN || RCC_APB1ENR_enu == RCC_APB1ENR_enuSPI3EN  || RCC_APB1ENR_enu == RCC_APB1ENR_enuUSART2EN ||
	   (RCC_APB1ENR_enu >= RCC_APB1ENR_enuI2C1EN && RCC_APB1ENR_enu <= RCC_APB1ENR_enuI2C3EN) || RCC_APB1ENR_enu == RCC_APB1ENR_enuPWREN )
	{
		if(AXBENR_Clk_Mode==AXBENR_Clk_ENABLED)
		{
			(rcc->RCC_APB1ENR) |= AXBENR_Clk_ENABLED << (RCC_APB1ENR_enu);
			Loc_RccErrStsReturn=rcc_enuOK;
		}
		else if(AXBENR_Clk_Mode==AXBENR_Clk_DISABLED)
		{
			(rcc->RCC_APB1ENR) &= ~(AXBENR_Clk_ENABLED << (RCC_APB1ENR_enu));
			Loc_RccErrStsReturn=rcc_enuOK;
		}
		else
		{
			Loc_RccErrStsReturn=rcc_enuInvalidParameter;
		}
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}


rcc_enuErrorStatus_t rcc_APB2ENR_Clk(tenuRCC_APB2ENR_Bits RCC_APB2ENR_enu,u32 AXBENR_Clk_Mode)
{
	rcc_enuErrorStatus_t Loc_RccErrStsReturn;
	if(RCC_APB2ENR_enu == RCC_APB2ENR_enuTIM1EN ||  RCC_APB2ENR_enu <= RCC_APB2ENR_enuUSART1EN || RCC_APB2ENR_enu == RCC_APB2ENR_enuUSART6EN  ||\
		RCC_APB2ENR_enu == RCC_APB2ENR_enuADC1EN || (RCC_APB2ENR_enu >= RCC_APB2ENR_enuSDIOEN    && RCC_APB2ENR_enu <= RCC_APB2ENR_enuSYSCFGEN) ||\
	   (RCC_APB2ENR_enu >= RCC_APB2ENR_enuTIM9EN &&  RCC_APB2ENR_enu <= RCC_APB2ENR_enuTIM11EN))
	{
		if(AXBENR_Clk_Mode==AXBENR_Clk_ENABLED)
		{
			(rcc->RCC_APB2ENR) |= AXBENR_Clk_ENABLED << (RCC_APB2ENR_enu);
			Loc_RccErrStsReturn=rcc_enuOK;
		}
		else if(AXBENR_Clk_Mode==AXBENR_Clk_DISABLED)
		{
			(rcc->RCC_APB2ENR) &= ~(AXBENR_Clk_ENABLED << (RCC_APB2ENR_enu));
			Loc_RccErrStsReturn=rcc_enuOK;
		}
		else
		{
			Loc_RccErrStsReturn=rcc_enuInvalidParameter;
		}
	}
	else
	{
		Loc_RccErrStsReturn=rcc_enuInvalidParameter;
	}
return Loc_RccErrStsReturn;
}
