
#ifndef SPI_H
	#define SPI_H


	// подключение заголовочных файлов модулей проекта
	#include "link.h"


	// директивы работы с линией FSS
	#define SPI3_CS_RESET		GPIO_ResetBits(GPIOA, GPIO_Pin_15)
	#define SPI3_CS_SET			GPIO_SetBits(GPIOA, GPIO_Pin_15)


	// прототипы функций
	void SPI3_reset(void);								// деинициализация контроллера SSP
	void SPI3_init(void);									// инициализация нитерфейса SPI2
	void SPI3_sendData(uint16_t data);		// передача данных по интерфейсу SPI


#endif
