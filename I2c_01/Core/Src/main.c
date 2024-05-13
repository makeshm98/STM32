/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define SENSOR_ADDR 0x38
#define MEASURE_01 0xAC
#define MEASURE_02 0x33
#define MEASURE_03 0x00
#define DATA_SIZE 7
#define MEASURE_DELAY 80
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_tx;
DMA_HandleTypeDef hdma_i2c1_rx;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  //uint8_t data1[] = {0x38};
	  //HAL_I2C_Master_Transmit(&hi2c1, SENSOR_ADDR << 1, &data1, sizeof(data1), 10);
	  //HAL_Delay(1000);


    /* USER CODE END WHILE */
	  uint8_t data2[] = {MEASURE_01, MEASURE_02, MEASURE_03};
	  HAL_I2C_Master_Transmit(&hi2c1, SENSOR_ADDR << 1, &data2, sizeof(data2), 1000);
	  HAL_Delay(5000);


	  uint8_t received_data[7]; // Array to store received data


	  HAL_I2C_Master_Receive(&hi2c1, SENSOR_ADDR << 1, &received_data, 7, 1000);
	  HAL_Delay(5000);


      char str_01[10];
 	  sprintf(str_01, "First: %d\n\r", received_data[1]);
      //HAL_UART_Transmit(&huart2, (uint8_t *)str_01, strlen(str_01), 10);

      char str_02[10];
 	  sprintf(str_02, "second: %d\n\r", received_data[2]);
      //HAL_UART_Transmit(&huart2, (uint8_t *)str_02, strlen(str_02), 10);

      char str_03[10];
 	  sprintf(str_03, "third: %d\n\r", received_data[3]);
      //HAL_UART_Transmit(&huart2, (uint8_t *)str_03, strlen(str_03), 10);

      char str_04[10];
 	  sprintf(str_04, "fourth: %d\n\r", received_data[4]);
      //HAL_UART_Transmit(&huart2, (uint8_t *)str_04, strlen(str_04), 10);

      char str_05[10];
 	  sprintf(str_05, "fifth: %d\n\r", received_data[5]);
      //HAL_UART_Transmit(&huart2, (uint8_t *)str_05, strlen(str_05), 10);




      uint32_t humidity   = received_data[1];
               humidity <<= 8;
               humidity  |= received_data[2];
               humidity <<= 4;
               humidity  |= received_data[3] >> 4;

      float hum = ((float)humidity / 0x100000) * 100;
      char hum_str[50];
	  sprintf(hum_str, "Humidity: %f\n\r", hum);

      HAL_UART_Transmit(&huart2, (uint8_t *)hum_str, strlen(hum_str), 10);


      uint32_t temperature   = received_data[3] & 0x0F;                //20-bit raw temperature data
               temperature <<= 8;
               temperature  |= received_data[4];
               temperature <<= 8;
               temperature  |= received_data[5];

      float temp = ((float)temperature / 1048576) * 200 - 50;
      char temp_str[50];
	  sprintf(temp_str, "Temperature : %f\n\r", temp);

      HAL_UART_Transmit(&huart2, (uint8_t *)temp_str, strlen(temp_str), 10);

	  // Print the received data over UART
	  char buffer[20]; // Buffer for storing formatted data
	  //sprintf(buffer, "Received data[%d]: %d\r\n", 0, received_data[0]);


      sprintf(buffer, "Received data: %d %d %d %d %d %d\r\n", received_data[0], received_data[1], received_data[2],
              received_data[3], received_data[4], received_data[5]);

/*      char str_01[10];
 	  sprintf(str_01, "First: %d\n\r", received_data[1]);
      HAL_UART_Transmit(&huart2, (uint8_t *)str_01, strlen(str_01), 10);
*/

      HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10);

/*
      char str_01[10];
 	  sprintf(str_01, "First: %d\n\r", received_data[1]);
      HAL_UART_Transmit(&huart2, (uint8_t *)str_01, strlen(str_01), 10);
*/


/*
	  uint32_t humidity   = received_data[1];
	  humidity <<= 8;
	  humidity  |= received_data[2];
	  humidity <<= 4;
	  humidity  |= received_data[3] >> 4;
*/

/*
      uint32_t humidity   = received_data[1];
      humidity <<= 8;
      humidity  |= received_data[2];
      humidity <<= 4;
      humidity  |= received_data[3] >> 4;

*/

/*      uint32_t result = received_data[1];
      result = received_data[1] <<= 8;
      result |= received_data[2] <<= 4;
      result |= received_data[3] >> 4;
      //result |= 182;
*/


/*
      uint32_t humidity   = received_data[1];
               humidity <<= 8;
               humidity  |= received_data[2];
               humidity <<= 4;
               humidity  |= received_data[3] >> 4;
*/




/*

       //result |= 182;

	  float hum = ((float)humidity / 0x100000) * 100;
	  //char hum_str[20]; // Buffer to store the string representation of hum
	  //sprintf(hum_str, "%u", hum);
      char hum_str[50];
	  sprintf(hum_str, "Humidity: %f\n\r", hum);


      HAL_UART_Transmit(&huart2, (uint8_t *)hum_str, strlen(hum_str), 10);
*/




/*
      uint32_t temperature   = received_data[3] & 0x0F;
               temperature <<= 8;
               temperature  |= received_data[4];
               temperature <<= 8;
               temperature  |= received_data[5];
*/
/*
      uint32_t temperature = 0;
      temperature |= (received_data[3] & 0x0F) << 8; // Shift upper 4 bits of received_data[3] left by 16 bits
      temperature |= received_data[4] << 8;          // Combine with received_data[4]
      temperature |= received_data[5];               // Combine with received_data[5]
*/
/*
      uint32_t temperature   = received_data[3] & 0x0F;                //20-bit raw temperature data
               temperature <<= 8;
               temperature  |= received_data[4];
               temperature <<= 16;
               temperature  |= received_data[5];



       //result |= 182;

	  float temp = ((float)temperature / 1048576) * 200 - 50;
	  //char hum_str[20]; // Buffer to store the string representation of hum
	  //sprintf(hum_str, "%u", hum);
      char temp_str[50];
	  sprintf(temp_str, "%f\n\r", temp);
*/

      //HAL_UART_Transmit(&huart2, (uint8_t *)temp_str, strlen(temp_str), 10);







	  for (int i = 0; i < sizeof(received_data); i++) {
	      // Format the data into a string (2 characters for each byte)
	      //sprintf(buffer, "Received data[%d]: 0x%02X\r\n", i, received_data[i]);

/*		  sprintf(buffer, "Received data[%d]: %d %d %d %d %d %d\r\n", i, received_data[i]);

	      //sprintf(buffer, "Received data[%d]: \r\n", i, received_data[i]);
	      // Transmit the formatted string over UART
	      HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10);
*/


	      /*sprintf(buffer, "Received data[%d]: %d %d %d %d %d %d\r\n",
	              i, received_data[0], received_data[1], received_data[2],
	              received_data[3], received_data[4], received_data[5]);
*/



		  //sprintf(buffer, "Received data[%d]: %d\r\n", i, received_data[i]);


	      //sprintf(buffer, "Received data[%d]: %d %d %d %d %d %d\r\n",
	        //      i, received_data[0]);
	      // Transmit the formatted string over UART
	      //HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10);




		  uint32_t humidity   = received_data[1];
		  humidity <<= 8;
		  humidity  |= received_data[2];
		  humidity <<= 4;
		  humidity  |= received_data[3] >> 4;

		  float hum = ((float)humidity / 1048576) * 100;
		  char hum_str[20]; // Buffer to store the string representation of hum
		  sprintf(hum_str, "%u", hum);

	     // HAL_UART_Transmit(&huart2, (uint8_t *)hum_str, strlen(hum_str), 100);

		  // Assign received_data[0] to a new array
		  //uint8_t data_01[7]; // New array to store received_data[0]
		  //memcpy(data_01, received_data[0], sizeof(received_data[0]));
	  }


/*	  uint8_t data_01[7]; // New array to store received_data[0]
	  memcpy(data_01, received_data[0], sizeof(received_data[0]));


	  char buffer_01[20]; // Buffer for storing formatted data

	  for(int i = 0; i<sizeof(data_01); i++)
	  {
	      sprintf(buffer_01, "Received data[%d]: %d\r\n",i, data_01[i]);
	      HAL_UART_Transmit(&huart2, (uint8_t *)buffer_01, strlen(buffer_01), 10);

	  }

*/
/*
	  uint8_t received_data_01[7]; // Array to store received data

	  for (int i = 0; i < 7; i++) {
		  received_data_01[i] = received_data[0];
	    }


	    char buffer_01[sizeof(received_data_01)]; // Buffer for storing formatted data
	    for (int i = 0; i < sizeof(received_data_01); i++) {
	        // Format the data into a string
	        sprintf(buffer_01, "Received data[%d]: %d\r\n", i, received_data_01[i]);
	        // Transmit the formatted string over UART
	        HAL_UART_Transmit(&huart2, (uint8_t *)buffer_01, strlen(buffer_01), 10000);

	        HAL_Delay(100);
	    }


*/

/*
	  uint32_t humidity   = received_data_01[1];
	  humidity <<= 8;
	  humidity  |= received_data_01[2];
	  humidity <<= 4;
	  humidity  |= received_data_01[3] >> 4;

	  float hum = ((float)humidity / 1048576) * 100;
	  char hum_str[20]; // Buffer to store the string representation of hum
	  sprintf(hum_str, "%u", hum);

	  uint32_t temperature   = received_data_01[3] & 0x0F;
	  temperature <<= 8;
	  temperature  |= received_data_01[4];
	  temperature <<= 8;
	  temperature  |= received_data_01[5];

	  float temp = ((float)temperature / 1048576) * 200 - 50;
	  char temp_str[20]; // Buffer to store the string representation of hum
	  sprintf(temp_str, "%u", temp);
*/
/*
      uint8_t message_01[] = "/nTemperature /n /r";
      HAL_UART_Transmit(&huart2, message_01,sizeof(message_01), 10);
      HAL_Delay(1000);


      HAL_UART_Transmit(&huart2, (uint8_t *)temp_str, strlen(temp_str), 10000);

      uint8_t message_02[] = "/nHumidity /n /r";
      HAL_UART_Transmit(&huart2, message_01,sizeof(message_01), 10);
      HAL_Delay(1000);
      HAL_UART_Transmit(&huart2, (uint8_t *)hum_str, strlen(hum_str), 10000);
*/


	    HAL_Delay(1000);
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00707CBB;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel4_5_6_7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_5_6_7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_5_6_7_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
