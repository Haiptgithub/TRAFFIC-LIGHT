/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
int time=0;
int t1,t2;
int sys = 0;

void shiftOut(int data) {
        for (int i = 0; i < 8; i++) {
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, data << i & 0x80);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
	 }
    }
void tatTatCaLed(void)
{
    for (int k = 0; k < 8 ; k++)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0x80);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
    }
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);
}
void hienthi ( int so1, int so2 ){

	unsigned char ma7doan[] =
	{// 0 1 2 3 4 5 6 7 8 9 A b C d E F-
  0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
		};
	    shiftOut (ma7doan[so2%10]);
		shiftOut (ma7doan[so2/10]);
		shiftOut (ma7doan[so1%10]);
		shiftOut (ma7doan[so1/10]);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
	}
	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
	{

    while(HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin) == 0){
    	        tatTatCaLed();
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_5,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_1|GPIO_PIN_4,GPIO_PIN_RESET);
                time=20;
}
   t1=25;
   t2=25;
	while(HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin) == 0){
				sys++;
		        HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_5|GPIO_PIN_4,GPIO_PIN_RESET);
				hienthi(t1,t2);
				if(sys/2000 > 0){
					t1=t1-1;
					t2=t2-1;
					sys=0;
					if(t1<1 && t2<1){
					t1=25;
					t2=25;
					}
					time=43;
				}
	}
	while(HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin) == 0){
		        tatTatCaLed();
		        sys++;
	         	if(sys/6000 > 0){HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_1|GPIO_PIN_4);
	    	       sys = 0;
	        	}
			    HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_5|GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_RESET);
			    time=0;
		}
				sys = 0;
	}
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
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if( time>=0 && time<20 ){
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_5,GPIO_PIN_SET);
	  	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4,GPIO_PIN_RESET);
	    }
	  if( time>=20 && time<23 ){
		 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1|GPIO_PIN_5,GPIO_PIN_SET);
	     HAL_GPIO_WritePin(GPIOA,GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4,GPIO_PIN_RESET);
	    }
	  if( time>=23 && time<43 ){
		 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2|GPIO_PIN_3,GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_5|GPIO_PIN_4,GPIO_PIN_RESET);
	    }
	  if( time>=43 && time<46 ){
		 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_2|GPIO_PIN_4,GPIO_PIN_SET);
		 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_0|GPIO_PIN_5,GPIO_PIN_RESET);
	    }
	   if(time==0){
	  	 t1=24;
	  	 t2=21;}
	   if(time==20){
	  	 t1=4;
	  	 t2=4;}
	   if(time==23){
	  	 t1=21;
	  	 t2=24;}
	   if(time==43){
	  	 t1=4;
	  	 t2=4;}
	   time=time+1;
	  	 t1=t1-1;
	  	 t2=t2-1;
	  	 if(time>=46) time=0;
	  	 hienthi(t1,t2);
	  	 HAL_Delay(1000);
  }
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */


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
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA2 PA3
                           PA4 PA5 PA6 PA7
                           PA8 PA9 PA10 PA11
                           PA12 PA13 PA14 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : BUTTON_Pin BUTTON1_Pin BUTTON2_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin|BUTTON1_Pin|BUTTON2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

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
