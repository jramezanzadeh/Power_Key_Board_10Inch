/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#define KEY3_Pin GPIO_PIN_2
#define KEY3_GPIO_Port GPIOE
#define KEY4_Pin GPIO_PIN_3
#define KEY4_GPIO_Port GPIOE
#define KEY5_Pin GPIO_PIN_4
#define KEY5_GPIO_Port GPIOE
#define KEY6_Pin GPIO_PIN_5
#define KEY6_GPIO_Port GPIOE
#define KEY7_Pin GPIO_PIN_6
#define KEY7_GPIO_Port GPIOE
#define PU_DEV1_PWR_CTRL_Pin GPIO_PIN_0
#define PU_DEV1_PWR_CTRL_GPIO_Port GPIOC
#define PU_DEV1_IO1_Pin GPIO_PIN_1
#define PU_DEV1_IO1_GPIO_Port GPIOC
#define PU_DEV1_IO2_Pin GPIO_PIN_2
#define PU_DEV1_IO2_GPIO_Port GPIOC
#define PU_DEV2_PWR_CTRL_Pin GPIO_PIN_3
#define PU_DEV2_PWR_CTRL_GPIO_Port GPIOC
#define SPI1_NSS_Pin GPIO_PIN_4
#define SPI1_NSS_GPIO_Port GPIOA
#define PU_DEV2_IO1_Pin GPIO_PIN_4
#define PU_DEV2_IO1_GPIO_Port GPIOC
#define PU_DEV2_IO2_Pin GPIO_PIN_5
#define PU_DEV2_IO2_GPIO_Port GPIOC
#define ENCODER_A_Pin GPIO_PIN_0
#define ENCODER_A_GPIO_Port GPIOB
#define ENCODER_B_Pin GPIO_PIN_1
#define ENCODER_B_GPIO_Port GPIOB
#define KEY8_Pin GPIO_PIN_7
#define KEY8_GPIO_Port GPIOE
#define KEY9_Pin GPIO_PIN_8
#define KEY9_GPIO_Port GPIOE
#define KEY10_Pin GPIO_PIN_9
#define KEY10_GPIO_Port GPIOE
#define KEY11_Pin GPIO_PIN_10
#define KEY11_GPIO_Port GPIOE
#define KEY12_Pin GPIO_PIN_11
#define KEY12_GPIO_Port GPIOE
#define KEY13_Pin GPIO_PIN_12
#define KEY13_GPIO_Port GPIOE
#define KEY14_Pin GPIO_PIN_13
#define KEY14_GPIO_Port GPIOE
#define KEY15_Pin GPIO_PIN_14
#define KEY15_GPIO_Port GPIOE
#define KEY16_Pin GPIO_PIN_15
#define KEY16_GPIO_Port GPIOE
#define BB_IO_3_21_Pin GPIO_PIN_12
#define BB_IO_3_21_GPIO_Port GPIOB
#define BB_IO_3_22_Pin GPIO_PIN_13
#define BB_IO_3_22_GPIO_Port GPIOB
#define BB_IO_3_23_Pin GPIO_PIN_14
#define BB_IO_3_23_GPIO_Port GPIOB
#define BB_IO_3_24_Pin GPIO_PIN_15
#define BB_IO_3_24_GPIO_Port GPIOB
#define KEY25_Pin GPIO_PIN_8
#define KEY25_GPIO_Port GPIOD
#define KEY26_Pin GPIO_PIN_9
#define KEY26_GPIO_Port GPIOD
#define KEY27_Pin GPIO_PIN_10
#define KEY27_GPIO_Port GPIOD
#define BB_PWR_CTRL_Pin GPIO_PIN_11
#define BB_PWR_CTRL_GPIO_Port GPIOD
#define BB_ON_OFF_Pin GPIO_PIN_12
#define BB_ON_OFF_GPIO_Port GPIOD
#define BB_RST_Pin GPIO_PIN_13
#define BB_RST_GPIO_Port GPIOD
#define KEY17_Pin GPIO_PIN_0
#define KEY17_GPIO_Port GPIOD
#define KEY18_Pin GPIO_PIN_1
#define KEY18_GPIO_Port GPIOD
#define KEY19_Pin GPIO_PIN_2
#define KEY19_GPIO_Port GPIOD
#define KEY20_Pin GPIO_PIN_3
#define KEY20_GPIO_Port GPIOD
#define KEY21_Pin GPIO_PIN_4
#define KEY21_GPIO_Port GPIOD
#define KEY22_Pin GPIO_PIN_5
#define KEY22_GPIO_Port GPIOD
#define KEY23_Pin GPIO_PIN_6
#define KEY23_GPIO_Port GPIOD
#define KEY24_Pin GPIO_PIN_7
#define KEY24_GPIO_Port GPIOD
#define ENCODER_PRESS_Pin GPIO_PIN_3
#define ENCODER_PRESS_GPIO_Port GPIOB
#define BUZZER_Pin GPIO_PIN_6
#define BUZZER_GPIO_Port GPIOB
#define PWR_LED_Pin GPIO_PIN_7
#define PWR_LED_GPIO_Port GPIOB
#define BACKLIGHT_LED_Pin GPIO_PIN_8
#define BACKLIGHT_LED_GPIO_Port GPIOB
#define STATUS_LED_Pin GPIO_PIN_9
#define STATUS_LED_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_0
#define KEY1_GPIO_Port GPIOE
#define KEY2_Pin GPIO_PIN_1
#define KEY2_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
