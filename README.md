# STM32
## STM32 projects using STM32L072CZ MCU

<!-- ### 1. Hello  World output :

For UART communication PA2 should be configured as USART2_TX, and PA15 should be configured as USART2_RX
1. [main.c](https://github.com/makeshm98/STM32/blob/main/hello/Core/Src/main.c)

![alt text](https://github.com/makeshm98/STM32/blob/main/hello/ezgif.com-video-to-gif-converter.gif) -->

### 1. AHT20 sensor sample output : 

* For UART communication PA2 should be configured as USART2_TX, and PA15 should be configured as USART2_RX.
* For I2C communication PB8 SCL and PB9 SDA.
* I2C settings : https://wiki.st.com/stm32mcu/wiki/Getting_started_with_I2C

  1. [main.c](https://github.com/makeshm98/STM32/blob/main/I2c_hal/Core/Src/main.c)

![alt text](https://github.com/makeshm98/STM32/blob/main/I2c_01/Screencastfrom10-05-24052154PMIST-ezgif.com-video-to-gif-converter.gif)

* Temperature and Humidity data extraction as part of **Hydroponics** project

### 2. Analog pH meter DF robot sample output :

* For UART communication PA2 should be configured as USART2_TX, and PA15 should be configured as USART2_RX
* For ADC PA0.
* ADC setting : https://wiki.st.com/stm32mcu/wiki/Getting_started_with_ADC

  1. [main.c](https://github.com/makeshm98/STM32/blob/main/PH_sensor_stm32/Core/Src/main.c)
  
![alt text](https://github.com/makeshm98/STM32/blob/main/PH_sensor_stm32/ezgif.com-video-to-gif-converter(2).gif)

* Measurement of pH for **Hydroponics** project

### 3. SCD41x CO2 sensor sample output :

  1. [main.c](https://github.com/makeshm98/STM32/blob/main/scd41_co2-stm32/co2_i2c/Core/Src/main.c)

![alt text](https://github.com/makeshm98/STM32/blob/main/scd41_co2-stm32/images/ezgif-5-6d17baf8e4.gif)

* CO2 data extraction in indoor and outdoor calibration purpose for Air Quality Monitoring project

### 4. Hello  World output :

For UART communication PA2 should be configured as USART2_TX, and PA15 should be configured as USART2_RX
1. [main.c](https://github.com/makeshm98/STM32/blob/main/hello/Core/Src/main.c)

![alt text](https://github.com/makeshm98/STM32/blob/main/hello/ezgif.com-video-to-gif-converter.gif)
