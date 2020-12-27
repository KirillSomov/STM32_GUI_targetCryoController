
#include "GPIO.h"


// конфигурация портов на вход
void	GPIO_gpiSetup(void)
{
	//
	GPIO_InitTypeDef GPIO_initGpi;
	GPIO_StructInit(&GPIO_initGpi);
	
  GPIO_initGpi.GPIO_Mode  = GPIO_Mode_IN;
  GPIO_initGpi.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_initGpi.GPIO_OType = GPIO_OType_OD;
  GPIO_initGpi.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	
  GPIO_initGpi.GPIO_Pin   = GPIO_Pin_5;					// PD5 - LCD_IRQ
	GPIO_Init(GPIOD,&GPIO_initGpi); 							// PD5 - LCD_IRQ
}	

// конфигурация портов на выход
void	GPIO_gpoSetup(void)
{
	//
	GPIO_InitTypeDef GPIO_initGpo;
	GPIO_StructInit(&GPIO_initGpo);
	
  GPIO_initGpo.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_initGpo.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_initGpo.GPIO_OType = GPIO_OType_PP;
  GPIO_initGpo.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	
  GPIO_initGpo.GPIO_Pin   = GPIO_Pin_9;															// PC9 - LCD_DC
	GPIO_Init(GPIOC,&GPIO_initGpo); 																	// PC9 - LCD_DC
	
	GPIO_initGpo.GPIO_Pin   = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_0;		// PD3 - LCD_RST, PD4 - TOUCH_FT6236_RSTN
	GPIO_Init(GPIOD,&GPIO_initGpo);																		// PD3 - LCD_RST, PD4 - TOUCH_FT6236_RSTN
}

// конфигурация порта для работы интерфейса SPI (SSP3)
void	GPIO_spi3Setup(void)
{
	// PC10 - SCK, PC11 - MISO, PC12 - MOSI
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_SPI3);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_SPI3);
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_SPI3);
	
	GPIO_InitTypeDef GPIO_initSPI3;
	GPIO_StructInit(&GPIO_initSPI3);
	
  GPIO_initSPI3.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_initSPI3.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_initSPI3.GPIO_OType = GPIO_OType_PP;
  GPIO_initSPI3.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_initSPI3.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
	
	GPIO_Init(GPIOC,&GPIO_initSPI3); 								//

	// PA15 - CS
	GPIO_initSPI3.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_initSPI3.GPIO_Pin   = GPIO_Pin_15;
  GPIO_Init(GPIOA, &GPIO_initSPI3);
}

// конфигурация порта для работы интерфейса I2C (I2C1)
void	GPIO_i2c1Setup(void)
{
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);
	
	GPIO_InitTypeDef GPIO_initI2C1;
	GPIO_StructInit(&GPIO_initI2C1);
	
  GPIO_initI2C1.GPIO_Pin		=	GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_initI2C1.GPIO_Mode		=	GPIO_Mode_AF; 
  GPIO_initI2C1.GPIO_Speed	=	GPIO_Speed_50MHz;
  GPIO_initI2C1.GPIO_OType	=	GPIO_OType_OD;
  GPIO_initI2C1.GPIO_PuPd		= GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_initI2C1);
}


// конфигурация портов
void	GPIO_setup(void)
{
	GPIO_gpiSetup();						// конфигурация портов на вход
	GPIO_gpoSetup();						// конфигурация портов на выход
	GPIO_spi3Setup();						// конфигурация порта для работы интерфейса SPI (SSP3)
	GPIO_i2c1Setup();						// конфигурация порта для работы интерфейса I2C (I2C1)
}
