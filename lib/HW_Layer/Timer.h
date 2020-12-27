
#ifndef TIMER_H
	#define TIMER_H

	// подключение заголовочных файлов модулей проекта
	#include "link.h"
	
	
	// прототипы функций
	void TIM6_DAC_init(void);
	void TIM6_DAC_IRQHandler(void);
	
	void delay_ms(uint32_t Delay_ms_Data);	// функия задержки в мс
	void delay_us(uint32_t Delay_us_Data);	// функия задержки в мкс
	
	void TIM7_init(void);
	void TIM7_IRQHandler(void);


#endif
