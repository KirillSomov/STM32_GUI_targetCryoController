
#include "Timer.h"


volatile uint32_t Delay_dec = 0;

volatile uint8_t extFlag = 0;


void TIM6_DAC_init(void)
{
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
  if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
  {
		if(Delay_dec > 0)
			Delay_dec--;
    /* Очищаем бит обрабатываемого прерывания */
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    /* Инвертируем состояние светодиодов */
    //GPIO_Write(GPIOD, GPIO_ReadOutputData(GPIOD) ^ GPIO_Pin_0);
  }
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
}


void TIM7_init(void)
{
  TIM_TimeBaseInitTypeDef base_timer;
  TIM_TimeBaseStructInit(&base_timer);
  /* Делитель учитывается как TIM_Prescaler + 1, поэтому отнимаем 1 */
  base_timer.TIM_Prescaler = 26250-1;
  base_timer.TIM_Period = 1;
  TIM_TimeBaseInit(TIM7, &base_timer);

  /* Разрешаем прерывание по обновлению (в данном случае -
   * по переполнению) счётчика таймера TIM6.
   */
  TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
  /* Включаем таймер */
  TIM_Cmd(TIM7, ENABLE);

  /* Разрешаем обработку прерывания по переполнению счётчика
   * таймера TIM6. Так получилось, что это же прерывание
   * отвечает и за опустошение ЦАП.
   */
  NVIC_EnableIRQ(TIM7_IRQn);
}


void TIM7_IRQHandler(void)
{
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
	
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
}
