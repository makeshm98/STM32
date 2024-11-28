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
#define SLAVE_ADDR 0x62
#define ANSWERSIZE 9
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

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const uint8_t txData_01[] = {0x21, 0xb1};
const uint8_t txData_02[] = {0xec, 0x05};
uint8_t rxData[ANSWERSIZE];
//uint8_t received_data[9];
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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
/*	    // Transmit first set of data
	    uint8_t data1[] = {0x21, 0xb1};
	    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDR << 1, data1, sizeof(data1), 1000);
	    HAL_Delay(5000);

	    // Transmit second set of data
	    uint8_t data2[] = {0xec, 0x05};
	    HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDR << 1, data2, sizeof(data2), 1000);
	    HAL_Delay(1000);
	    uint8_t data[9]; // Declaration of data array to store received data
	    // Receive data from slave
	    HAL_I2C_Master_Receive(&hi2c1, SLAVE_ADDR << 1, data, 9, 1000);

	    // Print received data over UART
	    char buffer[50]; // Buffer for storing formatted data
	    for (int i = 0; i < 9; i++) {
	        // Format the data into a string
	        sprintf(buffer, "Received data[%d]: 0x%02X\r\n", i, data[i]);
	        // Transmit the formatted string over UART
	        HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);
	        HAL_Delay(1000);
	    }
	    HAL_Delay(1000);
  */

	  //HAL_I2C_Master_Transmit(hi2c1, 0x62, );
      //HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDR, txData_01, sizeof(txData_01), 5000);

      //HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDR, txData_02, sizeof(txData_02), 1);

      //HAL_I2C_Master_Receive(&hi2c1, SLAVE_ADDR, rxData, ANSWERSIZE, 1000);

      // Transmit first set of data
      uint8_t data1[] = {0x21, 0xb1};
      HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDR << 1, &data1, sizeof(data1), 5000);

      // Transmit second set of data
      uint8_t data2[] = {0xec, 0x05};
      HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDR << 1, &data2, sizeof(data2), 1000);


      uint8_t received_data[9]; // Array to store received data


      HAL_I2C_Master_Receive(&hi2c1, SLAVE_ADDR << 1, &received_data, 9, 10000);


      uint8_t a = received_data[0];
      uint8_t b = received_data[1];

      // Convert the two bytes to a single hexadecimal string
      char hexBuffer[5];
      snprintf(hexBuffer, sizeof(hexBuffer), "%02X%02X", a, b);

      // Convert the hexadecimal string back to decimal
      long merged_co2 = strtol(hexBuffer, NULL, 16);

      // Print the CO2 concentration in ppm
      //printf("co2: %ld in ppm \n", merged_co2);
      printf(merged_co2);










	  //HAL_Delay(1000);

	  //uint8_t data1[] = {0x21, 0xb1};
/*	  char buffer[sizeof(received_data) * 3]; // Assuming each byte needs up to 3 characters in ASCII representation

	  // Convert each byte to its ASCII representation and store it in the buffer
	  int index = 0;
	  for (int i = 0; i < sizeof(received_data); i++) {
	      // Convert the byte to a string representation in hexadecimal format
	      index += sprintf(buffer + index, "%02X ", received_data[i]);
	  }
*/
	    // Print received data over UART
	    char buffer[sizeof(received_data) * 3]; // Buffer for storing formatted data
	    for (int i = 0; i < sizeof(received_data); i++) {
	        // Format the data into a string
	        sprintf(buffer, "Received data[%d]: 0x%02X\r\n", i, received_data[i]);
	        // Transmit the formatted string over UART
	        HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), 10000);

	        HAL_Delay(100);
	    }


//This code section entire gives CO2 concentration in PPM for required criteria

	    char buffer_01[20]; // Adjust the buffer size accordingly
	    for (int i = 0; i < 2; i++) { // Iterate only twice
	        // Format the data into a string
	    //here    //sprintf(buffer_01, "Received data[%d]: 0x%02X\r\n", i, received_data[i]);
	        // Transmit the formatted string over UART
	    // here    //HAL_UART_Transmit(&huart2, (uint8_t *)buffer_01, strlen(buffer_01), 10000);

	        uint16_t concatenated_value = (received_data[0] << 8) | received_data[1]; // Concatenated value

	        // Convert concatenated_value to a string
	        char buffer_01[6]; // Assuming max 5 digits and null terminator
	        sprintf(buffer_01, "%u", concatenated_value);

	        if(i == 1)
	        {
	        // Transmit the concatenated decimal value over UART
	        HAL_UART_Transmit(&huart2, (uint8_t *)buffer_01, strlen(buffer_01), 10000);
	        }
	        HAL_Delay(100);
	    }
        // Transmit the concatenated decimal value over UART
        //HAL_UART_Transmit(&huart2, (uint8_t *)buffer_01, strlen(buffer_01), 10000);
        uint8_t message[] = " Co2 in ppm \t";
        HAL_UART_Transmit(&huart2, message,sizeof(message), 10);
        HAL_Delay(1000);

//The co2 in ppm code ends here.

//This code section entire gives Temperature concentration in degrees for required criteria
	    char buffer_02[20]; // Adjust the buffer size accordingly
	    for (int i = 0; i < 2; i++) { // Iterate only twice
	        // Format the data into a string
	    //here    //sprintf(buffer_01, "Received data[%d]: 0x%02X\r\n", i, received_data[i]);
	        // Transmit the formatted string over UART
	    // here    //HAL_UART_Transmit(&huart2, (uint8_t *)buffer_01, strlen(buffer_01), 10000);

	        uint16_t concatenated_value_01 = (received_data[3] << 8) | received_data[4]; // Concatenated value
	        uint16_t concatenated_value_02 = (-45) + 175 * concatenated_value_01/65536;
	        // Convert concatenated_value to a string
	        char buffer_02[6]; // Assuming max 5 digits and null terminator
	        sprintf(buffer_02, "%u", concatenated_value_02);

	        if(i == 1)
	        {
	        // Transmit the concatenated decimal value over UART
	        HAL_UART_Transmit(&huart2, (uint8_t *)buffer_02, strlen(buffer_02), 10000);
	        }
	        HAL_Delay(100);
	    }
        // Transmit the concatenated decimal value over UART
        //HAL_UART_Transmit(&huart2, (uint8_t *)buffer_01, strlen(buffer_01), 10000);
        uint8_t message_01[] = " Degree celsius \t";
        HAL_UART_Transmit(&huart2, message_01,sizeof(message_01), 10);
        HAL_Delay(1000);

//This temperature code ends here

//This entire code section give relative humidity in percentage

        char buffer_03[20];
        for (int i = 0; i < 2; i++) {
	        uint16_t concatenated_value_03 = (received_data[6] << 8) | received_data[7]; // Concatenated value
	        uint16_t concatenated_value_04 = 100 * concatenated_value_03/65536;
	        // Convert concatenated_value to a string
	        char buffer_03[6]; // Assuming max 5 digits and null terminator
	        sprintf(buffer_03, "%u", concatenated_value_04);

	        if(i == 1)
	        {
	        // Transmit the concatenated decimal value over UART
	        HAL_UART_Transmit(&huart2, (uint8_t *)buffer_03, strlen(buffer_03), 10000);
	        }
	        HAL_Delay(100);
        }

        uint8_t message_02[] = " Relative Humidty in % \t\r\n";
        HAL_UART_Transmit(&huart2, message_02,sizeof(message_02), 10);
        HAL_Delay(1000);
// The realtive humidity code ends here




/*
    	uint16_t decimal_sum = (received_data[0] << 8) | received_data[1];
	    // Convert the decimal sum back to hexadecimal
	    char hex_sum[9]; // To accommodate "0x0000\r\n" and null terminator
	    sprintf(hex_sum, "0x%04X\r\n", decimal_sum);

	    // Transmit the concatenated string over UART
	    HAL_UART_Transmit(&huart2, (uint8_t *)hex_sum, strlen(hex_sum), 10000);
*/
/*
	    // Convert received_data[0] and received_data[1] from hexadecimal to decimal
	    int decimal_sum = (received_data[0] << 8) | received_data[1];

	    // Convert the decimal sum back to hexadecimal
	    char hex_sum[9]; // To accommodate "0x0000\r\n" and null terminator
	    sprintf(hex_sum, "0x%04X\r\n", decimal_sum);

	    // Transmit the concatenated string over UART
	    HAL_UART_Transmit(&huart2, (uint8_t *)hex_sum, strlen(hex_sum), 10000);
*/
	    HAL_Delay(1000);




/* This code provides the sum of very first bytes
 * and print as sum in hexadecimal strings
 *
	    // Convert received_data[0] and received_data[1] from hexadecimal to decimal
	    int decimal_sum = received_data[0] + received_data[1];

	    // Convert the decimal sum back to hexadecimal
	    char hex_sum[5]; // Assuming the maximum possible sum is within 16 bits
	    sprintf(hex_sum, "0x%04X\n", decimal_sum);

	    // Transmit the hexadecimal sum over UART
	    HAL_UART_Transmit(&huart2, (uint8_t *)hex_sum, strlen(hex_sum), 10000);
*/


	  // Transmit the buffer over UART
	  //HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 5000);
	  //HAL_UART_Transmit(&huart2, (uint8_t*)received_data[0], strlen(received_data[0]), 5000);
	  //HAL_UART_Transmit(&huart2, (uint8_t*)received_data[0], strlen(received_data[0]), 5000);


	  //This piece of code is used to extract first two bytes from 9 bytes hexadecimal
	  //string 174 - 182
/*
	  char buffer_01[2];

	  int index_01 = 0;
	  for(int i = 0; i < 2; i++) {
		  index_01 += sprintf(buffer_01 + index_01, "(%02X) ", received_data[i]);
	  }

	  // Transmit the buffer over UART
	  HAL_UART_Transmit(&huart2, (uint8_t*)buffer_01, strlen(buffer_01), 5000);


	  // Concatenate the hexadecimal representations of received_data into buffer_01
	  for (int i = 0; i < 2; i++) {
	      char temp[6]; // Temporary buffer to hold the formatted hexadecimal string
	      sprintf(temp, "(%02X) ", received_data[i]); // Format the current byte as a hexadecimal string
	      strcat(buffer_01, temp); // Concatenate the formatted string to buffer_01
	  }

	    // Transmit the concatenated hexadecimal string over UART
	    HAL_UART_Transmit(&huart2, (uint8_t*)buffer_01, strlen(buffer_01), 1000);
*/
	    // Given hexadecimal byte string
	    //char received_data[] = "04 54 B8 64 EF B8 9C EC C4";

/*
  	    // Extract the first two bytes
	    char first_two_bytes[3]; // 2 characters for two bytes + null terminator
	    strncpy(first_two_bytes, received_data, 2); // Copy the first 2 characters
	    first_two_bytes[2] = '\0'; // Null-terminate the string

	    // Extract the next two bytes
	    char next_two_bytes[3]; // 2 characters for two bytes + null terminator
	    strncpy(next_two_bytes, received_data + 3, 2); // Copy the next 2 characters after the space
	    next_two_bytes[2] = '\0'; // Null-terminate the string

	    // Concatenate the two strings
	    char concatenated_str[5]; // 4 characters for four bytes + null terminator
	    sprintf(concatenated_str, "%s%s", first_two_bytes, next_two_bytes);

	    // Convert the concatenated hexadecimal string to a single decimal value
	    unsigned int value;
	    sscanf(concatenated_str, "%X ", &value);

	    // Transmit the decimal value over UART
	    char decimal_str[12]; // Maximum value of a 32-bit integer is 4294967295, so at most 10 digits + '\0'
	    sprintf(decimal_str, "%u", value);
	    HAL_UART_Transmit(&huart2, (uint8_t*)decimal_str, strlen(decimal_str), 1000);


*/

	  //HAL_Delay(1000);

	        // Transmit third set of data
      //uint8_t data3[] = {0x3f, 0x86};
      //HAL_I2C_Master_Transmit(&hi2c1, SLAVE_ADDR << 1, &data3, sizeof(data3), 1000);
      //HAL_Delay(500);

    /* USER CODE BEGIN 3 */



  }  /* USER CODE END 3 */
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
