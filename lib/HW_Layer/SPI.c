
#include "SPI.h"


// деинициализация контроллера SSP
void SPI3_reset(void)
{	
	SPI_I2S_DeInit(SPI3);
}


// инициализация нитерфейса SPI2
void SPI3_init(void)
{	
	SPI3_reset();
	
	SPI_InitTypeDef SPI3_initStructure;
	SPI_StructInit(&SPI3_initStructure);
	
	//
  SPI_NSSInternalSoftwareConfig(SPI3, SPI_NSSInternalSoft_Set);
	
  //
  SPI3_initStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 		//
	SPI3_initStructure.SPI_CPOL = SPI_CPOL_Low; 														//
	
  SPI3_initStructure.SPI_DataSize = SPI_DataSize_8b; 											//
  
  SPI3_initStructure.SPI_CPHA = SPI_CPHA_1Edge; 											  	//
	//
  SPI3_initStructure.SPI_NSS = SPI_NSS_Soft; 															//
  SPI3_initStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;			// SPIf = APB1 / 2 = 13.125 MHz
	
  SPI3_initStructure.SPI_FirstBit = SPI_FirstBit_MSB; 										//
  SPI3_initStructure.SPI_Mode = SPI_Mode_Master; 													//
  SPI_Init(SPI3, &SPI3_initStructure); 																		//

  SPI_Cmd(SPI3, ENABLE); 																									//
}


// передача данных по интерфейсу SPI
void SPI3_sendData(uint16_t data)
{	
	// передача данных
	SPI_I2S_SendData(SPI3, data);
	
	// ожидание завершения передачи
	while(!(SPI3->SR & SPI_I2S_FLAG_RXNE));		// wait SPI3 busy
	while(SPI3->SR & (SPI_I2S_FLAG_BSY));
}	
