
#include "LCD_ILI9341.h"


// посылка команды
void LCD_sendCommand(uint16_t com)
{
  LCD_DC_RESET;
	SPI3_CS_RESET;
  SPI3_sendData(com);
	SPI3_CS_SET;
}

// посылка данных
void LCD_sendData(uint16_t data)
{
  LCD_DC_SET;
	SPI3_CS_RESET;
  SPI3_sendData(data);
	SPI3_CS_SET;
}


// инициализация LCD
void LCD_init(void)
{	
	// установка линии SPI
	SPI3_CS_SET;
   
  // сброс дисплея
  LCD_RST_SET;
  LCD_sendCommand(ILI9341_RESET);
  delay_ms(100);
   
  /// настройка дисплея
  LCD_sendCommand(ILI9341_POWERA);
  LCD_sendData(0x39);
  LCD_sendData(0x2C);
  LCD_sendData(0x00);
  LCD_sendData(0x34);
  LCD_sendData(0x02);
  LCD_sendCommand(ILI9341_POWERB);
  LCD_sendData(0x00);
  LCD_sendData(0xC1);
  LCD_sendData(0x30);
  LCD_sendCommand(ILI9341_DTCA);
  LCD_sendData(0x85);
  LCD_sendData(0x00);
  LCD_sendData(0x78);
  LCD_sendCommand(ILI9341_DTCB);
  LCD_sendData(0x00);
  LCD_sendData(0x00);
  LCD_sendCommand(ILI9341_POWER_SEQ);
  LCD_sendData(0x64);
  LCD_sendData(0x03);
  LCD_sendData(0x12);
  LCD_sendData(0x81);
  LCD_sendCommand(ILI9341_PRC);
  LCD_sendData(0x20);
  LCD_sendCommand(ILI9341_POWER1);
  LCD_sendData(0x23);
  LCD_sendCommand(ILI9341_POWER2);
  LCD_sendData(0x10);
  LCD_sendCommand(ILI9341_VCOM1);
  LCD_sendData(0x3E);
  LCD_sendData(0x28);
  LCD_sendCommand(ILI9341_VCOM2);
  LCD_sendData(0x86);
  LCD_sendCommand(ILI9341_MAC);
  LCD_sendData(0x48);
  LCD_sendCommand(ILI9341_PIXEL_FORMAT);
  LCD_sendData(0x55);
  LCD_sendCommand(ILI9341_FRC);
  LCD_sendData(0x00);
  LCD_sendData(0x18);
  LCD_sendCommand(ILI9341_DFC);
  LCD_sendData(0x08);
  LCD_sendData(0x82);
  LCD_sendData(0x27);
  LCD_sendCommand(ILI9341_3GAMMA_EN);
  LCD_sendData(0x00);
  LCD_sendCommand(ILI9341_COLUMN_ADDR);
  LCD_sendData(0x00);
  LCD_sendData(0x00);
  LCD_sendData(0x00);
  LCD_sendData(0xEF);
  LCD_sendCommand(ILI9341_PAGE_ADDR);
  LCD_sendData(0x00);
  LCD_sendData(0x00);
  LCD_sendData(0x01);
  LCD_sendData(0x3F);
  LCD_sendCommand(ILI9341_GAMMA);
  LCD_sendData(0x01);
  LCD_sendCommand(ILI9341_PGAMMA);
  LCD_sendData(0x0F);
  LCD_sendData(0x31);
  LCD_sendData(0x2B);
  LCD_sendData(0x0C);
  LCD_sendData(0x0E);
  LCD_sendData(0x08);
  LCD_sendData(0x4E);
  LCD_sendData(0xF1);
  LCD_sendData(0x37);
  LCD_sendData(0x07);
  LCD_sendData(0x10);
  LCD_sendData(0x03);
  LCD_sendData(0x0E);
  LCD_sendData(0x09);
  LCD_sendData(0x00);
  LCD_sendCommand(ILI9341_NGAMMA);
  LCD_sendData(0x00);
  LCD_sendData(0x0E);
  LCD_sendData(0x14);
  LCD_sendData(0x03);
  LCD_sendData(0x11);
  LCD_sendData(0x07);
  LCD_sendData(0x31);
  LCD_sendData(0xC1);
  LCD_sendData(0x48);
  LCD_sendData(0x08);
  LCD_sendData(0x0F);
  LCD_sendData(0x0C);
  LCD_sendData(0x31);
  LCD_sendData(0x36);
  LCD_sendData(0x0F);
  LCD_sendCommand(ILI9341_SLEEP_OUT);
   
  delay_ms(100);
  LCD_sendCommand(ILI9341_DISPLAY_ON);
  LCD_sendCommand(ILI9341_GRAM);
	
	// вкл подсветка
	//LCD_LED_ON;
}


// установка курсора на LCD
void LCD_setCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
//	x1--;
//	y1--;
//	x2--;
//	y2--;
	
  LCD_sendCommand(ILI9341_COLUMN_ADDR);
  LCD_sendData(x1 >> 8);
  LCD_sendData(x1 & 0xFF);
  LCD_sendData(x2 >> 8);
  LCD_sendData(x2 & 0xFF);
 
  LCD_sendCommand(ILI9341_PAGE_ADDR);
  LCD_sendData(y1 >> 8);
  LCD_sendData(y1 & 0xFF);
  LCD_sendData(y2 >> 8);
  LCD_sendData(y2 & 0xFF);
}


// заливка всего экрана цветом
void LCD_fill(uint16_t color)
{
	unsigned int n, i, j;
	i = color >> 8;
	j = color & 0xFF;
	LCD_setCursorPosition(0, 0, LCD_WIDTH-1, LCD_HEIGHT-1);

	LCD_sendCommand(ILI9341_GRAM);

	for (n = 0; n < LCD_PIXEL_COUNT; n++)
	{
		LCD_sendData(i);
		LCD_sendData(j);
	}
}


// отрисовка пикселя
void LCD_drawPixel(uint16_t x, uint16_t y, uint16_t color)
{
//	x--;
//	y--;
	
	y = (LCD_HEIGHT-1) - y;
	
  LCD_setCursorPosition(x, y, x, y);
  LCD_sendCommand(ILI9341_GRAM);
  LCD_sendData(color >> 8);
  LCD_sendData(color & 0xFF);
}


// закрасить область
void LCD_drawFilledRectangle(uint16_t x0, uint16_t x1, uint16_t y0, uint16_t y1, uint16_t color)
{
//	x0--;
//	x1--;
//	y0--;
//	y1--;
	
	uint16_t tempCoor = y0;
	
	y0 = (LCD_HEIGHT-1) - y1;
	y1 = (LCD_HEIGHT-1) - tempCoor;
	
	uint16_t i = 0;
	uint16_t j = 0;
	uint16_t ILI9341_x = x0;
	uint16_t ILI9341_y = y0;

	for(i=0;i<=(y1-y0);i++)
	{
		LCD_setCursorPosition(ILI9341_x, ILI9341_y + i, x1, ILI9341_y + i+1);
		LCD_sendCommand(ILI9341_GRAM);
		for(j=0;j<=(x1-x0);j++)
		{
			LCD_sendData(color >> 8);
			LCD_sendData(color & 0xFF);
		}
	}
}


uint16_t	LCD_printChar(uint32_t x, uint32_t y, uint16_t symbol, uint16_t fontColor, const uint8_t charArray[], const uint16_t charInfoArray[][3], uint16_t charOffset)
{	
	uint8_t	i = 0;
	
	for(uint8_t width = 0; width < charInfoArray[symbol - charOffset][0]; width++)
	{
		i = 0;
		for(uint8_t height = charInfoArray[symbol - charOffset][1]; height > 0; height--)
		{
			for(uint8_t byte = 0; byte < 8; byte++)
			{
				if(charArray[charInfoArray[symbol - charOffset][2] + width + i*charInfoArray[symbol - charOffset][0]] & (1 << byte))
					LCD_drawPixel(x, (y + height*8 - byte), fontColor);
			}
			i++;
		}
		x++;
	}
	
	return x;
}


// вывод строки
uint16_t	LCD_printString(uint32_t x, uint32_t y, char* str, uint16_t fontColor)
{
//	x--;
//	y--;
	
	uint16_t symbol = 0;	// код ascii символа
	
	//y = (LCD_HEIGHT-1) - y;
	while(*str)
	{
		symbol = *str++;
		
		// пробел
		if(symbol == ' ')
		{
			x = x + 6;
		}

		
		// цифры
		if(symbol >= 0x2E && symbol <= 0x3B)
		{
			x = LCD_printChar(x, y, symbol, fontColor, impact_18ptBitmapsNum, impact_18ptDescriptorsNum, DESCRIPTORSBLOCK0_OFFSET);
		}

		
		// Кириллица
		if(symbol >= 0xC0)
		{
			x = LCD_printChar(x, y, symbol, fontColor, impact_18ptBitmaps, impact_18ptDescriptors, DESCRIPTORSBLOCK1_OFFSET);
		}
		
		
		if(str && symbol != ' ')
			x = x + 1;
	}
	
	return x;
}
