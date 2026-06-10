/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "board.h"
#include "modes.h"
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
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

RNG_HandleTypeDef hrng;

SD_HandleTypeDef hsd;

SPI_HandleTypeDef hspi1;
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim6;

PCD_HandleTypeDef hpcd_USB_OTG_HS;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM6_Init(void);
static void MX_RNG_Init(void);
static void MX_USB_OTG_HS_PCD_Init(void);
static void MX_SDIO_SD_Init(void);
static void MX_ADC1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
#if !defined(ST25TB_HAVE_FULL_LEDS)
const KAKI_MODE Modes[] = {
    {.function = MODE_emulate,  .ledsModesBitmask = 0b01,       .Name = "Emulate"},
    {.function = MODE_rewrite,  .ledsModesBitmask = 0b10,       .Name = "Rewrite"},
    {.function = MODE_field,    .ledsModesBitmask = 0b00,       .Name = "Field"},
};
const KAKI_MODE Modes_2[] = {
    {.function = MODE_detect,   .ledsModesBitmask = 0b01,       .Name = "Detect"},
    {.function = MODE_select,   .ledsModesBitmask = 0b10,       .Name = "Select"},
    {.function = MODE_learn,    .ledsModesBitmask = 0b11,       .Name = "Learn"},
    {.function = MODE_tear,     .ledsModesBitmask = 0b00,       .Name = "Tear!"},
    {.function = MODE_cli,      .ledsModesBitmask = 0b00,       .Name = "CLI"},
};
#else
const KAKI_MODE Modes[] = {
    {.function = MODE_emulate,  .ledsModesBitmask = 1 << 0,     .Name = "Emulate"},
    {.function = MODE_rewrite,  .ledsModesBitmask = 1 << 1,     .Name = "Rewrite"},
    {.function = MODE_detect,   .ledsModesBitmask = 1 << 2,     .Name = "Detect"},
    {.function = MODE_select,   .ledsModesBitmask = 1 << 3,     .Name = "Select"},
    {.function = MODE_field,    .ledsModesBitmask = 1 << 4,     .Name = "Field"},
    {.function = MODE_unk,      .ledsModesBitmask = 0,          .Name = "Counter5"},
};
const KAKI_MODE Modes_2[] = {
    {.function = MODE_learn,    .ledsModesBitmask = 1 << 3,     .Name = "Learn"},
    {.function = MODE_tear,     .ledsModesBitmask = 1 << 4,     .Name = "Tear!"},
#if defined(ST25TB_HAVE_CLI)
    {.function = MODE_cli,      .ledsModesBitmask = 0b10101,    .Name = "CLI"},
#endif
};
#endif

#if defined(ST25TB_HAVE_CLI)
const char KIWI_BANNER[] =  "\x1b[2J\x1b[3J\x1b[H" UART_NEWLINE
    "  .#####.         " ST25TB_BOARD_NAME " (fw " ST25TB_FW_VERSION ")" UART_NEWLINE
    " .## ^ ##.__ _    " ST25TB_MCU_NAME " & TRF7970A" UART_NEWLINE
    " ## / \\ /   ('>-  /***" UART_NEWLINE
    " ## \\ / | K  |     Benjamin DELPY `gentilkiwi` ( benjamin@gentilkiwi.com )" UART_NEWLINE
    " '## v #\\____/" UART_NEWLINE
    "  '#####' L\\_      ***/" UART_NEWLINE UART_NEWLINE;
#endif
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	uint8_t maxModes;
#if defined(ST25TB_HAVE_CLI) && defined(__msp430)
    uint16_t calculatedCRC;
#endif
	const KAKI_MODE *pMode, *cMode;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  (void) MX_SDIO_SD_Init; // avoid a warning as not called
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_SPI2_Init();
  MX_TIM6_Init();
  MX_RNG_Init();
  MX_USB_OTG_HS_PCD_Init();
  MX_USB_DEVICE_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  TRF7970A_init();
  LEDS_Animation();
  SLOTS_Change(FlashStoredData.CurrentSlot);

#if defined(ST25TB_HAVE_CLI)
    UART_Redirect_std();
    HAL_Delay(2000);

    puts(KIWI_BANNER);
#if defined(__msp430)
    calculatedCRC = CRC16_CCIT((const uint8_t *)(TLVMEM_START + 0x04), 0xf4);

    printf("CRC Value   : r:0x%04x c:0x%04x - %s" UART_NEWLINE
            "Device ID   : 0x%04x" UART_NEWLINE
            "Lot wafer ID: 0x%08lx (x:%u/y:%u)" UART_NEWLINE
            "SYSRSTIV    : 0x%04x" UART_NEWLINE
            , CRC_VALUE, calculatedCRC, (CRC_VALUE == calculatedCRC) ? "OK" : "KO"
            , DEVICE_ID
            , DIE_LOT_WAFER_ID, DIE_LOT_WAFER_X_POS, DIE_LOT_WAFER_Y_POS
            , SYSRSTIV
    );
#elif defined(STM32F405xx)
    printf("Device ID   : 0x%04" PRIx32 " rev: 0x%04" PRIx32 UART_NEWLINE
    		"Flash size  : %" PRIu16 " Kbytes" UART_NEWLINE
			"Device UID  : 0x%08" PRIx32 "%08" PRIx32 "%08" PRIx32 UART_NEWLINE
			"SysClockFreq: %" PRIu32 " kHz" UART_NEWLINE
			, HAL_GetDEVID(), HAL_GetREVID()
			, *(const uint16_t*)FLASHSIZE_BASE
			, HAL_GetUIDw0(), HAL_GetUIDw1(), HAL_GetUIDw2()
			, HAL_RCC_GetSysClockFreq() / 1000
	);
#endif
#endif

  if(!SW1_IS_PRESSED()) // LEARN & TEAR only available if pushing MODE at startup
  {
      pMode = cMode = Modes;
      maxModes = count_of(Modes);
  }
  else
  {
      pMode = cMode = Modes_2;
      maxModes = count_of(Modes_2);
  }

#if defined(ST25TB_HAVE_CLI)
/*  while(SW1_IS_PRESSED())
  {
	  UART_Enabled = 0x01;
  }*/

  printf(
          UART_NEWLINE "ST25TB board mode      : %s" UART_NEWLINE
          "ST25TB board UART      : %s" UART_NEWLINE
          "ST25TB Current Slot    : %" PRIu8 UART_NEWLINE
          "ST25TB Total slots     : %u" UART_NEWLINE
          "ST25TB support for     : "
#if defined(SLOTS_ST25TB_SUPPORT_4K)
          "4Kb"
#elif defined(SLOTS_ST25TB_SUPPORT_2K)
          "2Kb"
#elif defined(SLOTS_ST25TB_SUPPORT_512)
          "512b"
#endif
          UART_NEWLINE
          , (pMode == Modes) ? "normal" : "special"
          , UART_Enabled ? "enabled" : "disabled"
          , FlashStoredData.CurrentSlot
          , SLOTS_ST25TB_COUNT
  );
#endif
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  IRQ_Global &= ~(IRQ_SOURCE_SW1 | IRQ_SOURCE_SW2);
	  LEDS_MODES_Bitmask(cMode->ledsModesBitmask);
	  LEDS_STATUS_Bitmask(0);

	  kprintf(UART_NEWLINE "--- Mode: %s ---" UART_NEWLINE, cMode->Name);

	  cMode->function();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  __no_operation();
	  TRF7970A_SPI_DirectCommand(TRF79X0_STOP_DECODERS_CMD);
	  __no_operation();
	  __no_operation();
	  TRF7970A_SPI_Write_SingleRegister(TRF79X0_CHIP_STATUS_CTRL_REG, 0x00);
	  cMode++;
	  if(cMode >= (pMode + maxModes))
	  {
		  cMode = pMode + 0;
	  }
	  TIMER_delay_Milliseconds(150);
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_VREFINT;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

}

/**
  * @brief RNG Initialization Function
  * @param None
  * @retval None
  */
static void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

}

/**
  * @brief SDIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_SDIO_SD_Init(void)
{

  /* USER CODE BEGIN SDIO_Init 0 */

  /* USER CODE END SDIO_Init 0 */

  /* USER CODE BEGIN SDIO_Init 1 */

  /* USER CODE END SDIO_Init 1 */
  hsd.Instance = SDIO;
  hsd.Init.ClockEdge = SDIO_CLOCK_EDGE_RISING;
  hsd.Init.ClockBypass = SDIO_CLOCK_BYPASS_DISABLE;
  hsd.Init.ClockPowerSave = SDIO_CLOCK_POWER_SAVE_DISABLE;
  hsd.Init.BusWide = SDIO_BUS_WIDE_1B;
  hsd.Init.HardwareFlowControl = SDIO_HARDWARE_FLOW_CONTROL_DISABLE;
  hsd.Init.ClockDiv = 0;
  if (HAL_SD_Init(&hsd) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_SD_ConfigWideBusOperation(&hsd, SDIO_BUS_WIDE_4B) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SDIO_Init 2 */

  /* USER CODE END SDIO_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_SLAVE;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM6 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM6_Init(void)
{

  /* USER CODE BEGIN TIM6_Init 0 */

  /* USER CODE END TIM6_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM6_Init 1 */

  /* USER CODE END TIM6_Init 1 */
  htim6.Instance = TIM6;
  htim6.Init.Prescaler = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim6.Init.Period = 65535;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM6_Init 2 */

  /* USER CODE END TIM6_Init 2 */

}

/**
  * @brief USB_OTG_HS Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_OTG_HS_PCD_Init(void)
{

  /* USER CODE BEGIN USB_OTG_HS_Init 0 */

  /* USER CODE END USB_OTG_HS_Init 0 */

  /* USER CODE BEGIN USB_OTG_HS_Init 1 */

  /* USER CODE END USB_OTG_HS_Init 1 */
  hpcd_USB_OTG_HS.Instance = USB_OTG_HS;
  hpcd_USB_OTG_HS.Init.dev_endpoints = 6;
  hpcd_USB_OTG_HS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_OTG_HS.Init.dma_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.phy_itface = USB_OTG_EMBEDDED_PHY;
  hpcd_USB_OTG_HS.Init.Sof_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.low_power_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.lpm_enable = DISABLE;
  hpcd_USB_OTG_HS.Init.vbus_sensing_enable = ENABLE;
  hpcd_USB_OTG_HS.Init.use_dedicated_ep1 = DISABLE;
  hpcd_USB_OTG_HS.Init.use_external_vbus = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_OTG_HS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_OTG_HS_Init 2 */

  /* USER CODE END USB_OTG_HS_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LED_SLOT1_Pin|LED_SLOT0_Pin|LED_MOD_UNK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, TRF_IO2_Pin|TRF_IO4_SPI2_CS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TRF_IO1_GPIO_Port, TRF_IO1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, TRF_IO0_Pin|ULED1_Pin|LED_STATUS_BLUE_Pin|LED_STATUS_RED_Pin
                          |LED_STATUS_GREEN_Pin|LED_SLOT7_Pin|LED_SLOT6_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_SLOT2_Pin|LED_SLOT4_Pin|TRF_EN_Pin|LED_MOD_LEARN_Pin
                          |LED_MOD_EMULATE_Pin|LED_MOD_REWRITE_Pin|LED_MOD_DETECT_Pin|LED_SLOT5_Pin
                          |LED_SLOT3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_SLOT1_Pin TRF_IO2_Pin LED_SLOT0_Pin LED_MOD_UNK_Pin */
  GPIO_InitStruct.Pin = LED_SLOT1_Pin|TRF_IO2_Pin|LED_SLOT0_Pin|LED_MOD_UNK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : TRF_IO4_SPI2_CS_Pin */
  GPIO_InitStruct.Pin = TRF_IO4_SPI2_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(TRF_IO4_SPI2_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : UBTN_Pin TRF_IRQ_Pin */
  GPIO_InitStruct.Pin = UBTN_Pin|TRF_IRQ_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : TRF_IO1_Pin TRF_IO0_Pin ULED1_Pin LED_STATUS_BLUE_Pin
                           LED_STATUS_RED_Pin LED_STATUS_GREEN_Pin LED_SLOT7_Pin LED_SLOT6_Pin */
  GPIO_InitStruct.Pin = TRF_IO1_Pin|TRF_IO0_Pin|ULED1_Pin|LED_STATUS_BLUE_Pin
                          |LED_STATUS_RED_Pin|LED_STATUS_GREEN_Pin|LED_SLOT7_Pin|LED_SLOT6_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : TRF_IO5_Pin TRF_IO3_Pin */
  GPIO_InitStruct.Pin = TRF_IO5_Pin|TRF_IO3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LED_SLOT2_Pin LED_SLOT4_Pin TRF_EN_Pin LED_MOD_LEARN_Pin
                           LED_MOD_EMULATE_Pin LED_MOD_REWRITE_Pin LED_MOD_DETECT_Pin LED_SLOT5_Pin
                           LED_SLOT3_Pin */
  GPIO_InitStruct.Pin = LED_SLOT2_Pin|LED_SLOT4_Pin|TRF_EN_Pin|LED_MOD_LEARN_Pin
                          |LED_MOD_EMULATE_Pin|LED_MOD_REWRITE_Pin|LED_MOD_DETECT_Pin|LED_SLOT5_Pin
                          |LED_SLOT3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : TRF_ASK_OOK_Pin */
  GPIO_InitStruct.Pin = TRF_ASK_OOK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(TRF_ASK_OOK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : K1_Pin */
  GPIO_InitStruct.Pin = K1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(K1_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

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
#ifdef USE_FULL_ASSERT
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
