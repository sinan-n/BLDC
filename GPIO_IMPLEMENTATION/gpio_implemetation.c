/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* USER CODE BEGIN PV */

#define UH 	GPIO_PIN_8
#define VH	GPIO_PIN_9
#define WH	GPIO_PIN_10

#define ENu GPIO_PIN_10
#define ENv GPIO_PIN_11
#define ENw	GPIO_PIN_12

uint8_t hall_A= 0b0;
uint8_t hall_B= 0b0;
uint8_t hall_C= 0b0;

uint8_t hall_state = 0b111;

uint32_t state_1 =0;
uint32_t state_2 =0;
uint32_t state_3 =0;
uint32_t state_4 =0;
uint32_t state_5 =0;
uint32_t state_6 =0;

uint8_t dir = 1;

const uint8_t fr_control_lookup[7][6] = {{0,0,0,0,0,0},// reset   // DIR 0
										{0,0,1,1,0,1},// reaching hal state 3
										{0,1,0,0,1,1},// reaching hal state 6
									    {0,1,0,1,1,0},// reaching hal state 2
									    {1,0,0,1,1,0},// reaching hal state 5
									    {0,0,1,0,1,1},// reaching hal state 1
									  	{1,0,0,1,0,1},// reaching hal state 4
		                            };

const uint8_t re_control_lookup[7][6] = {{0,0,0,0,0,0},//reset        //DIR 1 //ok
										{1,0,0,1,1,0},// reaching hal state 5
										{0,0,1,1,0,1},// reaching hal state 3
										{0,0,1,0,1,1},// reaching hal state 1
										{0,1,0,0,1,1},// reaching hal state 6
										{1,0,0,1,0,1},// reaching hal state 4
										{0,1,0,1,1,0},// reaching hal state 2
		                            };


uint8_t control_lookup_pos = 0b000000;
uint8_t delay = 0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  	  	  state_1 += (hall_state == 1) ? 1 : 0;
	  	  	  state_2 += (hall_state == 2) ? 1 : 0;
	  	  	  state_3 += (hall_state == 3) ? 1 : 0;
	  	  	  state_4 += (hall_state == 4) ? 1 : 0;
	  	  	  state_5 += (hall_state == 5) ? 1 : 0;
	  	  	  state_6 += (hall_state == 6) ? 1 : 0;
	  
	 		  hall_A = (GPIOA ->IDR& GPIO_PIN_15)?1:0;
	 		  hall_B = (GPIOB ->IDR& GPIO_PIN_3)?1:0;
	 		  hall_C = (GPIOB ->IDR& GPIO_PIN_10)?1:0;

	 		  hall_state = (hall_A<<2)|(hall_B<<1)|hall_C;

	 		  if(dir == 0)
	 		  {
	 				HAL_GPIO_WritePin(GPIOA, UH, fr_control_lookup[hall_state][0]);
	 				HAL_GPIO_WritePin(GPIOA, VH, fr_control_lookup[hall_state][1]);
	 				HAL_GPIO_WritePin(GPIOA, WH, fr_control_lookup[hall_state][2]);

	 				HAL_GPIO_WritePin(GPIOC, ENu, fr_control_lookup[hall_state][3]);
	 				HAL_GPIO_WritePin(GPIOC, ENv, fr_control_lookup[hall_state][4]);
	 				HAL_GPIO_WritePin(GPIOC, ENw, fr_control_lookup[hall_state][5]);
	 		  }

	 		  else
	 		  {
	 				HAL_GPIO_WritePin(GPIOA, UH, re_control_lookup[hall_state][0]);
	 				HAL_GPIO_WritePin(GPIOA, VH, re_control_lookup[hall_state][1]);
	 				HAL_GPIO_WritePin(GPIOA, WH, re_control_lookup[hall_state][2]);

	 				HAL_GPIO_WritePin(GPIOC, ENu, re_control_lookup[hall_state][3]);
	 				HAL_GPIO_WritePin(GPIOC, ENv, re_control_lookup[hall_state][4]);
	 				HAL_GPIO_WritePin(GPIOC, ENw, re_control_lookup[hall_state][5]);
	 		  }

    /* USER CODE END WHILE */

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
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
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, u_Pin|v_Pin|w_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, ENu_Pin|ENv_Pin|ENw_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : hc_Pin hb_Pin */
  GPIO_InitStruct.Pin = hc_Pin|hb_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : u_Pin v_Pin w_Pin */
  GPIO_InitStruct.Pin = u_Pin|v_Pin|w_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : ha_Pin */
  GPIO_InitStruct.Pin = ha_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ha_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ENu_Pin ENv_Pin ENw_Pin */
  GPIO_InitStruct.Pin = ENu_Pin|ENv_Pin|ENw_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

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
