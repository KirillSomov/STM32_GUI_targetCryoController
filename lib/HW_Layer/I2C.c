
#include "I2C.h"


// Инициализация модуля I2C
void I2C1_init(void)
{
	I2C_DeInit(I2C1);
	
	I2C_InitTypeDef I2C1_InitStruct;
	I2C_StructInit(&I2C1_InitStruct);
		
	// настройка I2C
  I2C1_InitStruct.I2C_ClockSpeed = 400000; 
  I2C1_InitStruct.I2C_Mode = I2C_Mode_I2C;
  I2C1_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C1_InitStruct.I2C_OwnAddress1 = 0x15;
  I2C1_InitStruct.I2C_Ack = I2C_Ack_Enable;
  I2C1_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_Init(I2C1, &I2C1_InitStruct);
	
  I2C_Cmd(I2C1, ENABLE);
}


// отправка данных по шине I2C
void I2Cx_writeData(I2C_TypeDef* I2Cx,
										uint8_t slaveAddress,       	// адрес устройства на шине I2C
										uint8_t registerAddress,  	// адрес регистра памяти устройства
										uint8_t data)              	// передаваемые данные
{
  // Ожидание освобождения шины I2C
  while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY))	{;}

	// Отправление признака START
	I2C_GenerateSTART(I2Cx, ENABLE);
	// ожидание подтверждения
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))	{;}
	
	// инициация передачи: задание адреса устройства и признака ЗАПИСИ данных
	I2C_Send7bitAddress(I2Cx, slaveAddress<<1, I2C_Direction_Transmitter);
	// ожидание завершения передачи
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))	{;}
	
	// Отправление данных
	I2C_SendData(I2Cx, registerAddress);
	// ожидание завершения передачи
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))	{;}
		
	// Отправление данных
	I2C_SendData(I2Cx, data);
	// ожидание завершения передачи
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))	{;}
	
	// Отправление признака STOP
	I2C_GenerateSTOP(I2Cx, ENABLE);
}


// получение данных по шине I2C
uint8_t I2Cx_readData(I2C_TypeDef* I2Cx,
											uint8_t slaveAddress,				// адрес устройства на шине I2C
                      uint8_t registerAddress)		// адрес регистра памяти устройства
{
	uint8_t data;
	
	// Ожидание освобождения шины I2C
  while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY))	{;}

	// Отправление признака START
	I2C_GenerateSTART(I2Cx, ENABLE);
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))	{;}
	
	// инициация передачи: задание адреса устройства и признака ЗАПИСИ данных
	I2C_Send7bitAddress(I2Cx, slaveAddress<<1, I2C_Direction_Transmitter);
	// ожидание завершения передачи
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))	{;}
	
	/* Для очистки EV6 запускаем модуль снова */
  I2C_Cmd(I2Cx, ENABLE);
		
  /* шлем HMC5883L адрес чтения */
  I2C_SendData(I2Cx, registerAddress);
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED))	{;}
		
  /* шлем старт второй раз */
  I2C_GenerateSTART(I2Cx, ENABLE);
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT))	{;}
		
  /* шлем HMC5883L адрес чтения */
  I2C_Send7bitAddress(I2Cx, slaveAddress<<1, I2C_Direction_Receiver);
  while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))	{;}
	
	I2C_AcknowledgeConfig(I2Cx, DISABLE);
		
	while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))	{;}
	data = I2C_ReceiveData(I2Cx);
		
	I2C_GenerateSTOP(I2Cx, ENABLE);
		
  return data;
}


// последовательное получение нескольких пакетов данных
void I2Cx_readDataBurst(I2C_TypeDef* I2Cx,
												uint8_t slaveAddress,			// адрес устройства на шине I2C
												uint8_t registerAddress,	// адрес начального регистра памяти устройства
												uint8_t amount,						// количество циклов чтения
												uint8_t *buffer)					// буфер для хранения результатов чтения
{
	while(amount)
	{
		*buffer = I2Cx_readData(I2Cx, slaveAddress, registerAddress);
		buffer++;
		registerAddress++;
		amount--;
	}
}
