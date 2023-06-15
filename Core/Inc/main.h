/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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
#include "stm32f4xx_hal.h"

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
#define WHEEL_B1_PWM_Pin GPIO_PIN_5
#define WHEEL_B1_PWM_GPIO_Port GPIOE
#define WHEEL_A1_PWM_Pin GPIO_PIN_6
#define WHEEL_A1_PWM_GPIO_Port GPIOE
#define WHEEL_A1_AIN1_Pin GPIO_PIN_0
#define WHEEL_A1_AIN1_GPIO_Port GPIOF
#define WHEEL_A1_AIN2_Pin GPIO_PIN_1
#define WHEEL_A1_AIN2_GPIO_Port GPIOF
#define WHEEL_B1_BIN1_Pin GPIO_PIN_2
#define WHEEL_B1_BIN1_GPIO_Port GPIOF
#define WHEEL_B1_BIN2_Pin GPIO_PIN_3
#define WHEEL_B1_BIN2_GPIO_Port GPIOF
#define WHEEL_A2_AIN1_Pin GPIO_PIN_4
#define WHEEL_A2_AIN1_GPIO_Port GPIOF
#define WHEEL_A2_AIN2_Pin GPIO_PIN_5
#define WHEEL_A2_AIN2_GPIO_Port GPIOF
#define WHEEL_B2_BIN1_Pin GPIO_PIN_6
#define WHEEL_B2_BIN1_GPIO_Port GPIOF
#define WHEEL_B2_BIN2_Pin GPIO_PIN_7
#define WHEEL_B2_BIN2_GPIO_Port GPIOF
#define WHEEL_B2_PWM_Pin GPIO_PIN_8
#define WHEEL_B2_PWM_GPIO_Port GPIOF
#define B1_T2_2_Pin GPIO_PIN_1
#define B1_T2_2_GPIO_Port GPIOA
#define S2T2_4_Pin GPIO_PIN_3
#define S2T2_4_GPIO_Port GPIOA
#define S1T2_1_Pin GPIO_PIN_5
#define S1T2_1_GPIO_Port GPIOA
#define B2T3_1_Pin GPIO_PIN_6
#define B2T3_1_GPIO_Port GPIOA
#define WHEEL_A2_PWM_Pin GPIO_PIN_15
#define WHEEL_A2_PWM_GPIO_Port GPIOB
#define SEG_Pin GPIO_PIN_8
#define SEG_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
