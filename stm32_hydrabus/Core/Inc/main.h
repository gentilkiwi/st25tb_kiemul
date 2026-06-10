/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#define LED_SLOT1_Pin GPIO_PIN_13
#define LED_SLOT1_GPIO_Port GPIOC
#define TRF_IO2_Pin GPIO_PIN_0
#define TRF_IO2_GPIO_Port GPIOC
#define TRF_IO4_SPI2_CS_Pin GPIO_PIN_1
#define TRF_IO4_SPI2_CS_GPIO_Port GPIOC
#define TRF_IO6_SPI2_MISO_Pin GPIO_PIN_2
#define TRF_IO6_SPI2_MISO_GPIO_Port GPIOC
#define TRF_IO7_SPI2_MOSI_Pin GPIO_PIN_3
#define TRF_IO7_SPI2_MOSI_GPIO_Port GPIOC
#define UBTN_Pin GPIO_PIN_0
#define UBTN_GPIO_Port GPIOA
#define UBTN_EXTI_IRQn EXTI0_IRQn
#define TRF_IRQ_Pin GPIO_PIN_1
#define TRF_IRQ_GPIO_Port GPIOA
#define TRF_IRQ_EXTI_IRQn EXTI1_IRQn
#define TRF_IO1_Pin GPIO_PIN_2
#define TRF_IO1_GPIO_Port GPIOA
#define TRF_IO0_Pin GPIO_PIN_3
#define TRF_IO0_GPIO_Port GPIOA
#define ULED1_Pin GPIO_PIN_4
#define ULED1_GPIO_Port GPIOA
#define TRF_SYS_CLK_SPI1_SCK_Pin GPIO_PIN_5
#define TRF_SYS_CLK_SPI1_SCK_GPIO_Port GPIOA
#define LED_STATUS_BLUE_Pin GPIO_PIN_6
#define LED_STATUS_BLUE_GPIO_Port GPIOA
#define TRF_MOD_SPI1_MOSI_Pin GPIO_PIN_7
#define TRF_MOD_SPI1_MOSI_GPIO_Port GPIOA
#define TRF_IO5_Pin GPIO_PIN_4
#define TRF_IO5_GPIO_Port GPIOC
#define TRF_IO3_Pin GPIO_PIN_5
#define TRF_IO3_GPIO_Port GPIOC
#define LED_SLOT2_Pin GPIO_PIN_0
#define LED_SLOT2_GPIO_Port GPIOB
#define TRF_ASK_OOK_Pin GPIO_PIN_1
#define TRF_ASK_OOK_GPIO_Port GPIOB
#define LED_SLOT4_Pin GPIO_PIN_2
#define LED_SLOT4_GPIO_Port GPIOB
#define TRF_DATA_CLK_SPI2_SCK_Pin GPIO_PIN_10
#define TRF_DATA_CLK_SPI2_SCK_GPIO_Port GPIOB
#define TRF_EN_Pin GPIO_PIN_11
#define TRF_EN_GPIO_Port GPIOB
#define LED_SLOT0_Pin GPIO_PIN_6
#define LED_SLOT0_GPIO_Port GPIOC
#define LED_MOD_UNK_Pin GPIO_PIN_7
#define LED_MOD_UNK_GPIO_Port GPIOC
#define LED_STATUS_RED_Pin GPIO_PIN_8
#define LED_STATUS_RED_GPIO_Port GPIOA
#define LED_STATUS_GREEN_Pin GPIO_PIN_9
#define LED_STATUS_GREEN_GPIO_Port GPIOA
#define LED_SLOT7_Pin GPIO_PIN_10
#define LED_SLOT7_GPIO_Port GPIOA
#define LED_SLOT6_Pin GPIO_PIN_15
#define LED_SLOT6_GPIO_Port GPIOA
#define LED_MOD_LEARN_Pin GPIO_PIN_3
#define LED_MOD_LEARN_GPIO_Port GPIOB
#define LED_MOD_EMULATE_Pin GPIO_PIN_4
#define LED_MOD_EMULATE_GPIO_Port GPIOB
#define LED_MOD_REWRITE_Pin GPIO_PIN_5
#define LED_MOD_REWRITE_GPIO_Port GPIOB
#define LED_MOD_DETECT_Pin GPIO_PIN_6
#define LED_MOD_DETECT_GPIO_Port GPIOB
#define K1_Pin GPIO_PIN_7
#define K1_GPIO_Port GPIOB
#define K1_EXTI_IRQn EXTI9_5_IRQn
#define LED_SLOT5_Pin GPIO_PIN_8
#define LED_SLOT5_GPIO_Port GPIOB
#define LED_SLOT3_Pin GPIO_PIN_9
#define LED_SLOT3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
