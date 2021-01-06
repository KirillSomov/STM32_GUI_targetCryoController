
// ����������� ������������� �����
#include "link.h"


uint8_t dataI2C = 0;

int main(void)
{	
	// ������������
	CPU_init();
	
	// GPIO
	GPIO_setup();
	
	// External interrupt init
	EXTI_init();
	
	// ������������� �������
	TIM6_DAC_init();
	TIM7_init();
		
	// ������������� SPI3
	SPI3_init();
	
	// ������������� ������ I2C
	I2C1_init();
	
	// ������������� LCD
	LCD_init();
	
	// ������������� touch ������
	FT6236_init();
	
	// ����� ��� LCD
	LCD_fill(0xBDD7);
	
	// init Graphical User Interface for CryoTargetController
	GUI_CTC_init();

//	
//	GUI_intToStr(0, &strBufNum[0]);
//	GUI_labelChangeText(12, &strBufNum[0], 0x0000);
//	GUI_intToStr(1, &strBufNum[0]);
//	GUI_labelChangeText(12, &strBufNum[0], 0x0000);
//	GUI_intToStr(10, &strBufNum[0]);
//	GUI_labelChangeText(12, &strBufNum[0], 0x0000);
//	GUI_intToStr(200, &strBufNum[0]);
//	GUI_labelChangeText(12, &strBufNum[0], 0x0000);
//	GUI_intToStr(233, &strBufNum[0]);
//	GUI_labelChangeText(12, &strBufNum[0], 0x0000);
//	GUI_intToStr(6, &strBufNum[0]);
//	GUI_labelChangeText(12, &strBufNum[0], 0x0000);
		
	while(1)
	{
		/*
		GUI_floatToStr(25.3f, &strBufNum[0]);
		for(uint8_t i = 0; i < 8; i++)
			GUI_labelChangeText(i+12, &strBufNum[0], 0x0000);
		delay_ms(250);
		GUI_floatToStr(25.0f, &strBufNum[0]);
		for(uint8_t i = 0; i < 8; i++)
			GUI_labelChangeText(i+12, &strBufNum[0], 0x0000);\
		delay_ms(250);
		GUI_floatToStr(2.3f, &strBufNum[0]);
		for(uint8_t i = 0; i < 8; i++)
			GUI_labelChangeText(i+12, &strBufNum[0], 0x0000);
		delay_ms(250);
		GUI_floatToStr(0.3f, &strBufNum[0]);
		for(uint8_t i = 0; i < 8; i++)
			GUI_labelChangeText(i+12, &strBufNum[0], 0x0000);
		delay_ms(250);
		GUI_floatToStr(1.3f, &strBufNum[0]);
		for(uint8_t i = 0; i < 8; i++)
			GUI_labelChangeText(i+12, &strBufNum[0], 0x0000);
		delay_ms(250);
		GUI_floatToStr(256.3f, &strBufNum[0]);
		for(uint8_t i = 0; i < 8; i++)
			GUI_labelChangeText(i+12, &strBufNum[0], 0x0000);
		delay_ms(250);
		GUI_floatToStr(0.0f, &strBufNum[0]);
		for(uint8_t i = 0; i < 8; i++)
			GUI_labelChangeText(i+12, &strBufNum[0], 0x0000);
		delay_ms(250);
		*/
		
		//
		GUI_Handler();
		
		delay_ms(10);
	}	
}
