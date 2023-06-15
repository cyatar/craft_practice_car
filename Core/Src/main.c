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
	
#include "sbus.h"
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include <stdio.h>
#include "stm32_pca9685.h"
	uint8_t MC6C[40]; 
	int MC6C_st = 0; 
	
#define USART_REC_LEN  			100  	//
#define RXBUFFERSIZE   			1 		//

uint8_t USART3_RX_BUF[USART_REC_LEN]; 
uint16_t USART3_RX_STA = 0; 
uint8_t aRxBuffer3[RXBUFFERSIZE];		  
UART_HandleTypeDef UART3_Handler; 
extern SBUS_CH_Struct SBUS_CH;

//



#define cnt_clk 84000000/(84)
#define arr 30000
uint32_t ccr_cnt1,ccr_cnt2;//存捕获寄存器获取的�?�的变量
uint32_t Period_cnt,Period_cnt1,Period_cnt2;//更新中断次数以及存放更新中断次数的变�?
uint32_t ic_flag,end_flag;//触发标志位，捕获完成标志
float duty_cycle,frequency;//频率，占空比


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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
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
  MX_USART3_UART_Init();
  MX_TIM6_Init();
  MX_TIM9_Init();
  MX_TIM12_Init();
  MX_TIM13_Init();
  MX_TIM8_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim9,TIM_CHANNEL_1);
	HAL_TIM_Base_Start_IT(&htim6);
	HAL_TIM_PWM_Start(&htim12,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim13,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_4);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
//	MX_I2C1_Init();
//		PCA_MG9XX_Init(60,90);
		
		
		
		__HAL_TIM_CLEAR_IT(&htim8,TIM_CHANNEL_1);//清除更新中断标志位，防止�?使能就进入更新中�?
		HAL_TIM_Base_Start_IT(&htim8);
		HAL_TIM_IC_Start_IT(&htim8,TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_4);
  /* USER CODE END 2 */

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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

/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	int i;
	
	while (huart->Instance == USART3) //uart3 ?
	{
		USART3_RX_BUF[USART3_RX_STA] = aRxBuffer3[0];
		if (USART3_RX_STA == 0 && USART3_RX_BUF[USART3_RX_STA] != 0x0F) break; //
		USART3_RX_STA++;
		if (USART3_RX_STA > USART_REC_LEN) USART3_RX_STA = 0;  //
		if (USART3_RX_BUF[0] == 0x0F && USART3_RX_BUF[24] == 0x00 && USART3_RX_STA == 25)	//
		{
			update_sbus(USART3_RX_BUF);

			
			for (i = 0; i<25; i++)		//
			
				HAL_GPIO_TogglePin(GPIOF,GPIO_PIN_1);
				USART3_RX_BUF[i] = 0;
			USART3_RX_STA = 0;
		}
		
		break;
	}
}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
				switch(ic_flag)//触发标志位判�?
				{
					case 0://第一个上升沿捕获
					{
						__HAL_TIM_SET_COUNTER(&htim8,0);//清除计数器的计数
						ccr_cnt1=0;//初始化相关变�?
						ccr_cnt2=0;
						Period_cnt=0;
						Period_cnt1=0;
						Period_cnt2=0;
						__HAL_TIM_SET_CAPTUREPOLARITY(&htim8,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_FALLING); //设置成下降沿触发	
						ic_flag=1;//更改捕获标志位，进入case1进行相关变量的处理�??
						break;
					}
					case 1://第一个下降沿捕获
					{
						ccr_cnt1=__HAL_TIM_GET_COMPARE(&htim8,TIM_CHANNEL_1);//获取存放在CCR寄存器的值（捕获值）
						Period_cnt1=Period_cnt;//获取第一个下降沿到来时的进入更新中断的次�?
						__HAL_TIM_SET_CAPTUREPOLARITY(&htim8,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_RISING);	//设置成上升沿触发	
						ic_flag=2;	//更改捕获标志位，进入case2进行相关变量的处�?
						break;
					}
					case 2://第二个上沿捕�?	
					{
						ccr_cnt2=__HAL_TIM_GET_COMPARE(&htim8,TIM_CHANNEL_1);//获取存放在CCR寄存器的值（捕获值）
						Period_cnt2=Period_cnt;//获取第二个上升沿到来时的进入更新中断的次�?
						ic_flag=0;	//更改捕获标志位，进入case0进行相关变量的处理�??
						end_flag=1;//捕获完成标志
						break;
					}	
					default:
					break;
				}
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
	if (htim->Instance == TIM8) {
    
		Period_cnt++;
  }
  /* USER CODE END Callback 1 */
}

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
