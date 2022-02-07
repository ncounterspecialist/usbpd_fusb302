/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
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
#include "core.h"
#include "dpm.h"
#include "HWIO.h"
#include "Timing.h"
#include "PlatformI2C.h"
#include "HostComm.h"
#include "PD_Types.h"
#include "PDPolicy.h"

#ifdef FSC_DEBUG
#include "usbd_main.h"
#include "usbd_desc.h"
#include "usbd_hid.h"
#endif /* FSC_DEBUG */

#include "stm32f1xx.h"

#include "FSCTypes.h"

#include "fan6295.h"
#include "PDProtocol.h"

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
DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_i2c1_tx;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

static const uint8_t FUSB102_ADDR = 0x22 << 1; // Use 8-bit address
static const uint8_t REG_DEVICE_ID = 0x01;

volatile FSC_BOOL haveINTReady = FALSE;

#ifdef FSC_DEBUG
volatile FSC_BOOL haveUSBInMsg = FALSE;

void platform_set_debug(FSC_U8 port, FSC_BOOL enable);
#endif /* FSC_DEBUG */

/*******************************************************************************
 * Static variables
 ******************************************************************************/
static DevicePolicyPtr_t dpm;
static Port_t ports[NUM_PORTS]; /* Array of ports */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
static void InitializeBoard(void) {
#ifdef FSC_DEBUG
    /* Initialize Host com */
    HCom_Init(ports, 1);
    /* Initialize the USB interface */
    InitializeUSB();
#endif /* FSC_DEBUG */
}

static void InitializeSystem(void) {
	InitializeBoard();
	InitializeTickTimer();
	InitializeTSTimer();
}

void platform_set_debug(FSC_U8 port, FSC_BOOL enable) {

}

void handle_core_event(int event, int portid, void *usr_ctx, void *app_ctx) {
       doDataObject_t pdo;
       if (event & PD_NEW_CONTRACT)
       {
//          pdo = (doDataObject_t*)app_ctx;
          /* handle event */
} }

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	HAL_StatusTypeDef ret;
	uint8_t bufin[1];
	uint8_t bufout[1];
	uint8_t bufout2[1];

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
	HAL_InitTick(1);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	while (1) {
		bufin[0] = REG_DEVICE_ID;
		ret = HAL_I2C_Master_Transmit(&hi2c1, FUSB300SlaveAddr, bufin, 1,
				3000);
		if (ret != HAL_OK) {
		} else {
			// Read 2 bytes from the temperature register
			ret = HAL_I2C_Master_Receive(&hi2c1, FUSB102_ADDR, bufout, 1,
					3000);
			if (ret == HAL_OK) {
			}
		}

		FSC_BOOL status = DeviceRead(FUSB300SlaveAddr, regDeviceID, 1, bufout2);
		if (status == TRUE) {
			break;
		}
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	FSC_U32 timer_value;

	InitializeSystem();

	DPM_Init(&dpm);

	ports[0].dpm = dpm;
	ports[0].PortID = 0;
//	&ports[0]->PortConfig.SinkUSBSuspendOperation = TRUE;
//	&ports[0]->PortConfig.SinkUSBCommCapable = TRUE;
	core_initialize(&ports[0], FUSB300SlaveAddr);

	DPM_AddPort(dpm, &ports[0]);
	register_observer(EVENT_ALL, handle_core_event, 0);

#ifdef FSC_HAVE_PPS_SOURCE
      FAN6295_Initialize();
  #endif /* FSC_HAVE_PPS_SOURCE */

#ifdef FSC_DEBUG
      platform_set_debug(ports[0].PortID,FALSE);
  #endif /* FSC_DEBUG */

	while (1) {
//  #ifdef this
		haveINTReady = TRUE;
//  #endif /* FSC_POLLING_MODE */

		/* Run the Type-C state machine */
		if (haveINTReady
#ifdef FSC_DEBUG
                  || haveUSBInMsg
  #endif /* FSC_DEBUG */
		) {
			/* Disable the timer interrupt */
			ClearTimeInterrupt();

			/* Optional: Enable system timer(s) here if they were previously
			 * disabled while in Idle mode.
			 */

#ifdef FSC_DEBUG
              platform_set_debug(ports[0].PortID,TRUE);
  #endif /* FSC_DEBUG */

			core_state_machine(&ports[0]);
			if(ports[0].ConnState == AttachedSink && &ports[0].PolicyState == peSinkTransitionDefault) {
//				UpdateCapabilitiesRx(&ports[0], TRUE);
//				PolicySinkEvaluateCaps(&ports[0]);
			} else
			if(ports[0].ConnState == AttachedSink ) {
//				SetPEState(&ports[0], peSinkGetSourceCap);
//				ProtocolGetRxPacket(&ports[0], FALSE);
//				UpdateCapabilitiesRx(&ports[0], TRUE);
//				ProtocolFlushRxFIFO(&ports[0]);
//				  ports[0].SinkRequest.BRDO = ports[0].SrcCapsReceived[2].BRDO;
//				SetPEState(&ports[0], peSinkSelectCapability);
//				ProtocolTransmitMessage(&ports[0]);
//				ProtocolFlushTxFIFO(&ports[0]);
//				ProtocolSendingMessage(&ports[0]);
//				SetStateAttachedSink(&ports[0]);
//				UpdateCapabilitiesRx(&ports[0], TRUE);
//				PolicySinkEvaluateCaps(&ports[0]);
//				PolicySinkSelectCapability(&ports[0]);
			}
			if(ports[0].ConnState == Unattached) {
//				ProtocolFlushRxFIFO(&ports[0]);
			}

#ifdef FSC_DEBUG
              platform_set_debug(ports[0].PortID,FALSE);
  #endif /* FSC_DEBUG */

			haveINTReady = FALSE;

			/*
			 * It is possible for the state machine to go into idle mode with
			 * the interrupt pin still low and as a result the edge-sensitive
			 * IRQ won't get triggered.  Check here before returning to wait
			 * on the IRQ.
			 */
			if (platform_get_device_irq_state(ports[0].PortID)) {
				haveINTReady = TRUE;
			} else {
				/* If needed, enable timer interrupt before idling */
				timer_value = core_get_next_timeout(&ports[0]);

				if (timer_value > 0) {
					if (timer_value == 1) {
						/* A value of 1 indicates that a timer has expired
						 * or is about to expire and needs further processing.
						 */
						haveINTReady = TRUE;
					} else {
						/* A non-zero time requires a future timer interrupt */
						SetTimeInterrupt(timer_value);
					}
				} else {
					/* Optional: Disable system timer(s) here to save power
					 * if needed while in Idle mode.
					 */
				}
			}
		}

#ifdef FSC_DEBUG
		HCom_Process();
          if (haveUSBInMsg)
          {
            /* Process the message */


            /* Send response */
            USBD_HID_SendReport(&USBD_Device, HCom_OutBuf(),
                USBD_HID_OUTREPORT_BUF_SIZE);

            haveUSBInMsg = FALSE;
          }
  #endif /* FSC_DEBUG */
	}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
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
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 0;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 48-1;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 65535;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
  /* DMA1_Channel7_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

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
	while (1) {
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

