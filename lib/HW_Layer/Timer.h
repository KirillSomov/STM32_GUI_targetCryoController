
#ifndef TIMER_H
	#define TIMER_H

	// подключение заголовочных файлов модулей проекта
	#include "link.h"
	
	
	// прототипы функций
	void TIM6_DAC_Init(void);
	void TIM6_DAC_IRQHandler(void);
	
	void delay_ms(uint32_t Delay_ms_Data);	// функия задержки в мс
	
	void Timer3_Init(void);
	void Timer3_IRQHandler(void);
	void delay_us(uint32_t Delay_us_Data);	// функия задержки в мкс
	
	
	void Timer1_init(void);
	void Timer1_IRQHandler(void);
	
	void Timer2_Init(void);
	void EXT_INT3_IRQHandler(void);
	void Timer2_IRQHandler(void);


#endif
