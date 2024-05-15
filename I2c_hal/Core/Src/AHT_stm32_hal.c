#include "AHT_stm32_hal.h"
#include "main.h"

I2C_HandleTypeDef *_AHT_ui2c;

uint8_t data2[] = {MEASURE_01, MEASURE_02, MEASURE_03};
uint8_t received_data[7];


void AHT_Init(I2C_HandleTypeDef *hi2c1) {
	_AHT_ui2c = hi2c1;
}

float AHT_GetTemperature()
{
	  HAL_I2C_Master_Transmit(_AHT_ui2c, SENSOR_ADDR << 1, &data2, sizeof(data2), 1000);
	  HAL_Delay(1000);

	  HAL_I2C_Master_Receive(_AHT_ui2c, SENSOR_ADDR << 1, &received_data, 7, 1000);
	  HAL_Delay(1000);


  	  uint32_t temperature   = received_data[3] & 0x0F;
           temperature <<= 8;
           temperature  |= received_data[4];
           temperature <<= 8;
           temperature  |= received_data[5];

  	  float temp = ((float)temperature / 1048576) * 200 - 50;
  	  return temp;
}

float AHT_GetHumidity()
{
	  HAL_I2C_Master_Transmit(_AHT_ui2c, SENSOR_ADDR << 1, &data2, sizeof(data2), 1000);
	  HAL_Delay(1000);

	  HAL_I2C_Master_Receive(_AHT_ui2c, SENSOR_ADDR << 1, &received_data, 7, 1000);
	  HAL_Delay(1000);

  	  uint32_t humidity   = received_data[1];
           humidity <<= 8;
           humidity  |= received_data[2];
           humidity <<= 4;
           humidity  |= received_data[3] >> 4;

  	  float hum = ((float)humidity / 0x100000) * 100;
  	  return hum;

}
