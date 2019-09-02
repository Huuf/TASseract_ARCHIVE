/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
#include <stdbool.h>
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
struct gpio_combo {
	GPIO_TypeDef *port;
	uint16_t pin;
};
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define HSEM_ID_0 (0U) /* HW semaphore 0*/

/* USER CODE END PD */
struct gpio_combo test_gpios[] = {
	{ SNES_RESET_GPIO_Port, SNES_RESET_Pin },
	{ RJ45_P1_2_Port, RJ45_P1_2_Pin },
	{ RJ45_P1_3_Port, RJ45_P1_3_Pin },
	{ RJ45_P1_4_Port, RJ45_P1_4_Pin },
	{ RJ45_P1_5_Port, RJ45_P1_5_Pin },
	{ RJ45_P1_6_Port, RJ45_P1_6_Pin },
	{ RJ45_P1_7_Port, RJ45_P1_7_Pin },
	{ RJ45_P1_8_Port, RJ45_P1_8_Pin },
	{ RJ45_P2_2_Port, RJ45_P2_2_Pin },
	{ RJ45_P2_3_Port, RJ45_P2_3_Pin },
	{ RJ45_P2_4_Port, RJ45_P2_4_Pin },
	{ RJ45_P2_5_Port, RJ45_P2_5_Pin },
	{ RJ45_P2_6_Port, RJ45_P2_6_Pin },
	{ RJ45_P2_7_Port, RJ45_P2_7_Pin },
	{ RJ45_P2_8_Port, RJ45_P2_8_Pin },
	{ RJ45_P3_2_Port, RJ45_P3_2_Pin },
	{ RJ45_P3_3_Port, RJ45_P3_3_Pin },
	{ RJ45_P3_4_Port, RJ45_P3_4_Pin },
	{ RJ45_P3_5_Port, RJ45_P3_5_Pin },
	{ RJ45_P3_6_Port, RJ45_P3_6_Pin },
	{ RJ45_P3_7_Port, RJ45_P3_7_Pin },
	{ RJ45_P3_8_Port, RJ45_P3_8_Pin },
	{ RJ45_P4_2_Port, RJ45_P4_2_Pin },
	{ RJ45_P4_3_Port, RJ45_P4_3_Pin },
	{ RJ45_P4_4_Port, RJ45_P4_4_Pin },
	{ RJ45_P4_5_Port, RJ45_P4_5_Pin },
	{ RJ45_P4_6_Port, RJ45_P4_6_Pin },
	{ RJ45_P4_7_Port, RJ45_P4_7_Pin },
	{ RJ45_P4_8_Port, RJ45_P4_8_Pin },
	{ RJ45_V1_2_Port, RJ45_V1_2_Pin },
	{ RJ45_V1_3_Port, RJ45_V1_3_Pin },
	{ RJ45_V1_4_Port, RJ45_V1_4_Pin },
	{ RJ45_V1_5_Port, RJ45_V1_5_Pin },
	{ RJ45_V1_6_Port, RJ45_V1_6_Pin },
	{ RJ45_V1_7_Port, RJ45_V1_7_Pin },
	{ RJ45_V1_8_Port, RJ45_V1_8_Pin },
	{ RJ45_V2_2_Port, RJ45_V2_2_Pin },
	{ RJ45_V2_3_Port, RJ45_V2_3_Pin },
	{ RJ45_V2_4_Port, RJ45_V2_4_Pin },
	{ RJ45_V2_5_Port, RJ45_V2_5_Pin },
	{ RJ45_V2_6_Port, RJ45_V2_6_Pin },
	{ RJ45_V2_7_Port, RJ45_V2_7_Pin },
	{ RJ45_V2_8_Port, RJ45_V2_8_Pin },
	{ RJ45_V3_2_Port, RJ45_V3_2_Pin },
	{ RJ45_V3_3_Port, RJ45_V3_3_Pin },
	{ RJ45_V3_4_Port, RJ45_V3_4_Pin },
	{ RJ45_V3_5_Port, RJ45_V3_5_Pin },
	{ RJ45_V3_6_Port, RJ45_V3_6_Pin },
	{ RJ45_V3_7_Port, RJ45_V3_7_Pin },
	{ RJ45_V3_8_Port, RJ45_V3_8_Pin },
	{ RJ45_V4_2_Port, RJ45_V4_2_Pin },
	{ RJ45_V4_3_Port, RJ45_V4_3_Pin },
	{ RJ45_V4_4_Port, RJ45_V4_4_Pin },
	{ RJ45_V4_5_Port, RJ45_V4_5_Pin },
	{ RJ45_V4_6_Port, RJ45_V4_6_Pin },
	{ RJ45_V4_7_Port, RJ45_V4_7_Pin },
	{ RJ45_V4_8_Port, RJ45_V4_8_Pin },
};
/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void setup_pin_output(GPIO_TypeDef *port, uint16_t pin, bool high)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
    port->BSRR = (high ? pin : (pin << 16));
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	/* USER CODE BEGIN 1 */
	int32_t port_count = sizeof(test_gpios) / sizeof(test_gpios[0]);
	/* USER CODE END 1 */


	/* USER CODE BEGIN Boot_Mode_Sequence_1 */
	/*HW semaphore Clock enable*/
	__HAL_RCC_HSEM_CLK_ENABLE();
	/* Activate HSEM notification for Cortex-M4*/
	HAL_HSEM_ActivateNotification(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));
	/*
	Domain D2 goes to STOP mode (Cortex-M4 in deep-sleep) waiting for Cortex-M7 to
	perform system initialization (system clock config, external memory configuration.. )
	*/
	HAL_PWREx_ClearPendingEvent();
	HAL_PWREx_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_STOPENTRY_WFE, PWR_D2_DOMAIN);
	/* Clear HSEM flag */
	__HAL_HSEM_CLEAR_FLAG(__HAL_HSEM_SEMID_TO_MASK(HSEM_ID_0));

	/* USER CODE END Boot_Mode_Sequence_1 */
	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	for (uint32_t i = 0; i < port_count; i++) {
		setup_pin_output(test_gpios[i].port, test_gpios[i].pin, true);
	}
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		for (uint32_t i = 0; i < port_count; i++) {
			test_gpios[i].port->BSRR = test_gpios[i].pin << 16;
			HAL_Delay(1000);
			test_gpios[i].port->BSRR = test_gpios[i].pin;
			HAL_Delay(1000);
		}
	}
	/* USER CODE END 3 */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();


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
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
