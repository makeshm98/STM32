#include "main.h"


#define SENSOR_ADDR 0x38
#define MEASURE_01 0xAC
#define MEASURE_02 0x33
#define MEASURE_03 0x00
#define DATA_SIZE 7
#define MEASURE_DELAY 80


float AHT_GetTemperature(void);
float AHT_GetHumidity(void);

void AHT_Init(I2C_HandleTypeDef *hi2c1);
