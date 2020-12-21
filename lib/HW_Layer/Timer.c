
#include "Timer.h"


volatile uint32_t Delay_dec = 0;

volatile uint8_t extFlag = 0;


void TIM6_DAC_Init(void)
{
	/* Не забываем затактировать таймер */
  /* Инициализируем базовый таймер: делитель 24000, период 500 мс.
   * Другие параметры структуры TIM_TimeBaseInitTypeDef
   * не имеют смысла для базовых таймеров.
   */
  TIM_TimeBaseInitTypeDef base_timer;
  TIM_TimeBaseStructInit(&base_timer);
  /* Делитель учитывается как TIM_Prescaler + 1, поэтому отнимаем 1 */
  base_timer.TIM_Prescaler = 26250-1;
  base_timer.TIM_Period = 1;
  TIM_TimeBaseInit(TIM6, &base_timer);

  /* Разрешаем прерывание по обновлению (в данном случае -
   * по переполнению) счётчика таймера TIM6.
   */
  TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
  /* Включаем таймер */
  TIM_Cmd(TIM6, ENABLE);

  /* Разрешаем обработку прерывания по переполнению счётчика
   * таймера TIM6. Так получилось, что это же прерывание
   * отвечает и за опустошение ЦАП.
   */
  NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

void TIM6_DAC_IRQHandler(void)
{
  /* Так как этот обработчик вызывается и для ЦАП, нужно проверять,
   * произошло ли прерывание по переполнению счётчика таймера TIM6.
   */
  if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
  {
		if(Delay_dec > 0)
			Delay_dec--;
    /* Очищаем бит обрабатываемого прерывания */
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    /* Инвертируем состояние светодиодов */
    //GPIO_Write(GPIOD, GPIO_ReadOutputData(GPIOD) ^ GPIO_Pin_0);
  }
}


void Timer3_IRQHandler(void)
{
	;
	/*
	if(Delay_dec > 0)
		Delay_dec--;
	
	MDR_TIMER3->CNT	=	0;									// сброс счетчика таймера
	MDR_TIMER3->STATUS	=	0;							// сброс статуса прерывания
	NVIC_ClearPendingIRQ(Timer3_IRQn);		// сброс статуса прерывания
	*/
}


void delay_us(uint32_t Delay_us_Data)
{
	;
	/*
	MDR_TIMER3->CNTRL	=	1;
	
	Delay_dec = Delay_us_Data;
	while (Delay_dec) {};
	
	MDR_TIMER3->CNTRL	=	0;
	*/
}

void delay_ms(uint32_t Delay_ms_Data)
{
	Delay_dec = Delay_ms_Data;
	while(Delay_dec) {};
		
	/*
	MDR_TIMER3->CNTRL	=	1;
	
	Delay_dec = Delay_ms_Data * 1000;
	while (Delay_dec) {};
		
	MDR_TIMER3->CNTRL	=	0;
	*/
}


void Timer1_init(void)
{
	;
	/*
	// настройка Т2 на генерирование прерывания каждую мкс
	MDR_RST_CLK->TIM_CLOCK	|=	((1 << 0)			// делитель 2: F_Timer1 = 80 / 2 = 40 MHz
															|(1 << 24));	// вкл. тактирование Таймера 1
		
	// режим счета – вверх,начальное значение – число из регистра CNT
	MDR_TIMER1->CNTRL	=	1;
	MDR_TIMER1->PSG		=	39999;				// предделитель частоты
	MDR_TIMER1->ARR		=	1;						// основание счета
	MDR_TIMER1->CNT		=	0;						// начальное значение счетчика
	MDR_TIMER1->IE		=	2;						// разрешение генерир. прерывание при CNT=ARR
	
	NVIC_EnableIRQ(Timer1_IRQn);
	__enable_irq();
	*/
}


void Timer1_IRQHandler(void)
{
	;
	/*
	for(uint8_t objButNum = 0; objButNum < OBJ_BUTTON_AMOUNT; objButNum++)
	{
		if(GUI.objList.ObjButtonList[objButNum].timerVal > 0)
		{
			GUI.objList.ObjButtonList[objButNum].timerVal--;
		}
		else
		{
			GUI.objList.ObjButtonList[objButNum].flag_buttonWasClicked = 0;
		}
	}
	
	MDR_TIMER1->CNT	=	0;									// сброс счетчика таймера
	MDR_TIMER1->STATUS	=	0;							// сброс статуса прерывания
	NVIC_ClearPendingIRQ(Timer1_IRQn);		// сброс статуса прерывания
	*/
}


void Timer2_Init(void)
{
	;
	/*
	// настройка Т2 на генерирование прерывания каждую мкс
	MDR_RST_CLK->TIM_CLOCK	|=	((0 << 8)				// делитель 1: F_Timer2 = 80 / 1 = 80 MHz
															|(1 << 25));		// вкл. тактирование Таймера 2
		
	// режим счета – вверх,начальное значение – число из регистра CNT
	MDR_TIMER2->CNTRL	=	0x00000000;
	MDR_TIMER2->PSG		=	0;				// предделитель частоты
	MDR_TIMER2->ARR		=	1;				// основание счета
	MDR_TIMER2->CNT		=	0;				// начальное значение счетчика
	MDR_TIMER2->IE		=	2;				// разрешение генерир. прерывание при CNT=ARR
	
	NVIC_EnableIRQ(Timer2_IRQn);
	NVIC_EnableIRQ(EXT_INT3_IRQn);
	__enable_irq();
	*/
}


void EXT_INT3_IRQHandler(void)
{
	;
	/*
	extFlag = 1;
	*/
}


void Timer2_IRQHandler(void)
{
	;
	/*
	extFlag = 1;
	
	MDR_TIMER2->CNT	=	0;									// сброс счетчика таймера
	MDR_TIMER2->STATUS	=	0;							// сброс статуса прерывания
	NVIC_ClearPendingIRQ(Timer2_IRQn);		// сброс статуса прерывания
	*/
}
