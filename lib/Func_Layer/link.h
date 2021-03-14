
#ifndef LINK_H
	#define LINK_H


	// подключение стандартных библиотек
	#include "stm32f4xx.h"                  // Device header
	
	#include "stm32f4xx_syscfg.h"
	#include "stm32f4xx_gpio.h"
	#include "stm32f4xx_i2c.h"
	#include "stm32f4xx_rcc.h"
	#include "stm32f4xx_spi.h"
	#include "stm32f4xx_tim.h"
	#include "stm32f4xx_exti.h"
	#include "misc.h"
	

	// подключение заголовочных файлов модулей проектов
	#include "CPU.h"
	#include "GPIO.h"
	#include "EXTI.h"
	#include "Timer.h"
	#include "SPI.h"
	#include "I2C.h"
	#include "Font.h"
	#include "Picture.h"
	#include "LCD_ILI9341.h"
	#include "Touch_FT6236.h"
	#include "GUI.h"
	#include "GUI_cryoTargetController.h"


#endif
