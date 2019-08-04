/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN Private defines */
#define SNES_RESET_Pin GPIO_PIN_13
#define SNES_RESET_GPIO_Port GPIOA

#define RJ45_P1_2_Port GPIOA
#define RJ45_P1_2_Pin GPIO_PIN_0
#define RJ45_P1_3_Port GPIOA
#define RJ45_P1_3_Pin GPIO_PIN_1
#define RJ45_P1_4_Port GPIOA
#define RJ45_P1_4_Pin GPIO_PIN_2
#define RJ45_P1_5_Port GPIOA
#define RJ45_P1_5_Pin GPIO_PIN_3
#define RJ45_P1_6_Port GPIOA
#define RJ45_P1_6_Pin GPIO_PIN_4
#define RJ45_P1_7_Port GPIO
#define RJ45_P1_7_Pin GPIO_PIN_5
#define RJ45_P1_8_Port GPIOA
#define RJ45_P1_8_Pin GPIO_PIN_6

#define RJ45_P2_2_Port GPIOA
#define RJ45_P2_2_Pin GPIO_PIN_7
#define RJ45_P2_3_Port GPIOB
#define RJ45_P2_3_Pin GPIO_PIN_0
#define RJ45_P2_4_Port GPIOB
#define RJ45_P2_4_Pin GPIO_PIN_1
#define RJ45_P2_5_Port GPIOB
#define RJ45_P2_5_Pin GPIO_PIN_2
#define RJ45_P2_6_Port GPIOF
#define RJ45_P2_6_Pin GPIO_PIN_11
#define RJ45_P2_7_Port GPIOF
#define RJ45_P2_7_Pin GPIO_PIN_14
#define RJ45_P2_8_Port GPIOF
#define RJ45_P2_8_Pin GPIO_PIN_15

#define RJ45_P3_2_Port GPIOE
#define RJ45_P3_2_Pin GPIO_PIN_7
#define RJ45_P3_3_Port GPIOE
#define RJ45_P3_3_Pin GPIO_PIN_8
#define RJ45_P3_4_Port GPIOE
#define RJ45_P3_4_Pin GPIO_PIN_9
#define RJ45_P3_5_Port GPIOE
#define RJ45_P3_5_Pin GPIO_PIN_10
#define RJ45_P3_6_Port GPIOE
#define RJ45_P3_6_Pin GPIO_PIN_11
#define RJ45_P3_7_Port GPIOE
#define RJ45_P3_7_Pin GPIO_PIN_12
#define RJ45_P3_8_Port GPIOE
#define RJ45_P3_8_Pin GPIO_PIN_13

#define RJ45_P4_2_Port GPIOE
#define RJ45_P4_2_Pin GPIO_PIN_14
#define RJ45_P4_3_Port GPIOE
#define RJ45_P4_3_Pin GPIO_PIN_15
#define RJ45_P4_4_Port GPIOB
#define RJ45_P4_4_Pin GPIO_PIN_12
#define RJ45_P4_5_Port GPIOB
#define RJ45_P4_5_Pin GPIO_PIN_13
#define RJ45_P4_6_Port GPIOD
#define RJ45_P4_6_Pin GPIO_PIN_8
#define RJ45_P4_7_Port GPIOD
#define RJ45_P4_7_Pin GPIO_PIN_9
#define RJ45_P4_8_Port GPIOD
#define RJ45_P4_8_Pin GPIO_PIN_10

#define RJ45_V1_2_Port GPIOE
#define RJ45_V1_2_Pin GPIO_PIN_2
#define RJ45_V1_3_Port GPIOE
#define RJ45_V1_3_Pin GPIO_PIN_3
#define RJ45_V1_4_Port GPIOE
#define RJ45_V1_4_Pin GPIO_PIN_4
#define RJ45_V1_5_Port GPIOE
#define RJ45_V1_5_Pin GPIO_PIN_5
#define RJ45_V1_6_Port GPIOE
#define RJ45_V1_6_Pin GPIO_PIN_6
#define RJ45_V1_7_Port GPIOC
#define RJ45_V1_7_Pin GPIO_PIN_13
#define RJ45_V1_8_Port GPIOC
#define RJ45_V1_8_Pin GPIO_PIN_14

#define RJ45_V2_2_Port GPIOB
#define RJ45_V2_2_Pin GPIO_PIN_5
#define RJ45_V2_3_Port GPIOB
#define RJ45_V2_3_Pin GPIO_PIN_6
#define RJ45_V2_4_Port GPIOB
#define RJ45_V2_4_Pin GPIO_PIN_7
#define RJ45_V2_5_Port GPIOB
#define RJ45_V2_5_Pin GPIO_PIN_8
#define RJ45_V2_6_Port GPIOB
#define RJ45_V2_6_Pin GPIO_PIN_9
#define RJ45_V2_7_Port GPIOE
#define RJ45_V2_7_Pin GPIO_PIN_0
#define RJ45_V2_8_Port GPIOE
#define RJ45_V2_8_Pin GPIO_PIN_1

#define RJ45_V3_2_Port GPIOD
#define RJ45_V3_2_Pin GPIO_PIN_6
#define RJ45_V3_3_Port GPIOD
#define RJ45_V3_3_Pin GPIO_PIN_7
#define RJ45_V3_4_Port GPIOG
#define RJ45_V3_4_Pin GPIO_PIN_9
#define RJ45_V3_5_Port GPIOG
#define RJ45_V3_5_Pin GPIO_PIN_10
#define RJ45_V3_6_Port GPIOG
#define RJ45_V3_6_Pin GPIO_PIN_11
#define RJ45_V3_7_Port GPIOB
#define RJ45_V3_7_Pin GPIO_PIN_3
#define RJ45_V3_8_Port GPIOB
#define RJ45_V3_8_Pin GPIO_PIN_4

#define RJ45_V4_2_Port GPIOA
#define RJ45_V4_2_Pin GPIO_PIN_14
#define RJ45_V4_3_Port GPIOA
#define RJ45_V4_3_Pin GPIO_PIN_15
#define RJ45_V4_4_Port GPIOD
#define RJ45_V4_4_Pin GPIO_PIN_0
#define RJ45_V4_5_Port GPIOD
#define RJ45_V4_5_Pin GPIO_PIN_1
#define RJ45_V4_6_Port GPIOD
#define RJ45_V4_6_Pin GPIO_PIN_3
#define RJ45_V4_7_Port GPIOD
#define RJ45_V4_7_Pin GPIO_PIN_4
#define RJ45_V4_8_Port GPIOD
#define RJ45_V4_8_Pin GPIO_PIN_5

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
