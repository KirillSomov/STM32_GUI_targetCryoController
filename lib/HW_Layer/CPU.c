
#include "CPU.h"


void	clockSetup(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	
	PWR->CR |= PWR_CR_PLS | PWR_CR_PVDE | ((uint32_t)0x00004000);
	while(!(PWR->CSR & PWR_CSR_VOSRDY))	{;}
	
	RCC->CR |=RCC_CR_HSEON; // Enable external quartz
  while(!(RCC->CR & RCC_CR_HSERDY))	{;} //wait for quartz ready 
	
	FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;
	
	RCC->PLLCFGR=(cPLLQ<<24) | (cPLLP<<16) | (cPLLN<<6) | cPLLM | RCC_PLLCFGR_PLLSRC_HSE;
	
	RCC->CR |=	RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY))	{;} //wait for PLL ready 
    
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1; 		// AHB = PLLCLK / 1 = 105 MHz
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;   // APB2 = AHB / 2 = 52.5 MHz
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV4; 	// APB1 = AHB / 4 = 26.25 MHz
	
	RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | RCC_CFGR_SW_PLL;
  while((RCC->CFGR & RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL)	{;}

	RCC->CR &= ~RCC_CR_HSION; // page 224, HSI clock 16 MHz Off 
}


void	periphClockSetup(void)
{	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,	ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,	ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,	ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,	ENABLE);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_EXTIT,	ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,		ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,		ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3,		ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,		ENABLE);
}


void	CPU_init(void)
{
	clockSetup();
	periphClockSetup();
}
