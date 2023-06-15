/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "gpio.h"
#include "tim.h"
#include <stdio.h>
#include "sbus.h"
//#include "stm32_pca9685.h"

//#include "i2c.h"
#define cos45 0.707106
#define sin45 0.707106
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

	
#define USART_REC_LEN  			100  	//
#define RXBUFFERSIZE   			1 		//
extern	uint8_t MC6C; 
extern 	int MC6C_st; 
extern uint8_t USART3_RX_BUF; 
extern uint16_t USART3_RX_STA; 
extern uint8_t aRxBuffer3[] ; 		  
extern UART_HandleTypeDef UART3_Handler; 

#define cnt_clk 84000000/(84+1)//计时器时�?
#define arr 30000  //重装载寄存器的�?�，根据实际情况设置�?
extern uint32_t ccr_cnt1,ccr_cnt2;//存捕获寄存器获取的�?�的变量
extern uint32_t Period_cnt,Period_cnt1,Period_cnt2;//更新中断次数以及存放更新中断次数的变�?
extern uint32_t ic_flag,end_flag;//触发标志位，捕获完成标志
extern float duty_cycle,frequency;//频率，占空比

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

extern SBUS_CH_Struct SBUS_CH;
//  ֢o޸ѐԵʼۯքƤ׃
// س˖ԍąؖҦÊӦكˇ2100  Ԓҟֽӣ255
// ؜֮Јۮ֨Եʼֵ


// here mid value 
int ML_CH3 =  480  ; // left_spd
int ML_CH4 =  930 ; // rotate 
int MR_CH2 =  960 ; //  right_y  max 1400 min 600
int MR_CH1 =  850 ;  // right_x

int LY = 0;
int LX = 0;
int RX = 0;
int RY = 0;
int CH6 = 0x06F0 ; // 
int CH5 = 0x03E4 ;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */


int * speedcc(int rx , int ry, int lx );






/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
int * wheelspeed ; 
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId ForservoHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartTask02(void const * argument);
void StartTask03(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of myTask02 */
  osThreadDef(myTask02, StartTask02, osPriorityIdle, 0, 128);
  myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

  /* definition and creation of Forservo */
  osThreadDef(Forservo, StartTask03, osPriorityIdle, 0, 128);
  ForservoHandle = osThreadCreate(osThread(Forservo), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	


	
	HAL_UART_Receive_IT(&huart3,aRxBuffer3,1);	
	//char msg[] = "\n";
  /* Infinite loop */ 
	
  for(;;)
  {
		
		
		
		RY =  SBUS_CH.CH2 - MR_CH2; 
		RX =  SBUS_CH.CH1 - MR_CH1;
    LX =  SBUS_CH.CH4 - ML_CH4; 
		
		osDelay(20);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the myTask02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void const * argument)
{
  /* USER CODE BEGIN StartTask02 */
	
	int stop = 300 ;
	int biasA1 = 0;
	int biasA2 = 200;
	int biasB1 = 200;
	int biasB2 = -50 ;
  
	
  /* Infinite loop */
  for(;;)
  {
	

			
		wheelspeed = speedcc(RY,RX,LX);
		/*	wheelspeed[0] -= biasA1 ;
			wheelspeed[1] -= biasA2 ;
			wheelspeed[2] -= biasB1 ; 
			wheelspeed[3] -= biasB2 ;
		*/
		
			wheelspeed[0] = wheelspeed[0] * 1.5 ;
			wheelspeed[1] = wheelspeed[1] * 1.5  ;
			wheelspeed[2] = wheelspeed[2] * 1.5  ; 
			wheelspeed[3] = wheelspeed[3] * 1.5  ; 
		
			// we add human stop here
			if(wheelspeed[0] >= 1000) wheelspeed[0] = 1700;
			if(wheelspeed[1] >= 1000) wheelspeed[1] = 1700;
			if(wheelspeed[2] >= 1000) wheelspeed[2] = 1700;
			if(wheelspeed[3] >= 1000) wheelspeed[3] = 1700;
			
			if(wheelspeed[0] <= -1000) wheelspeed[0] = -1700;
			if(wheelspeed[1] <= -1000) wheelspeed[1] = -1700;
			if(wheelspeed[2] <= -1000) wheelspeed[2] = -1700;
			if(wheelspeed[3] <= -1000) wheelspeed[3] = -1700;
				
			

		
			if(wheelspeed[0] < -stop ) {
						
						HAL_GPIO_WritePin(WHEEL_A1_AIN1_GPIO_Port,WHEEL_A1_AIN1_Pin,GPIO_PIN_SET);
						HAL_GPIO_WritePin(WHEEL_A1_AIN2_GPIO_Port,WHEEL_A1_AIN2_Pin,GPIO_PIN_RESET);
						__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_2, -wheelspeed[0]); 
					}
					else if(wheelspeed[0] > stop ) {
						HAL_GPIO_WritePin(WHEEL_A1_AIN1_GPIO_Port,WHEEL_A1_AIN1_Pin,GPIO_PIN_RESET);
						HAL_GPIO_WritePin(WHEEL_A1_AIN2_GPIO_Port,WHEEL_A1_AIN2_Pin,GPIO_PIN_SET);
						__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_2, wheelspeed[0]);
						
					}
					else{
					
					
						__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_2, 0);
					
					}
					if(wheelspeed[1] < -stop) {
						
						HAL_GPIO_WritePin(WHEEL_A2_AIN1_GPIO_Port,WHEEL_A2_AIN1_Pin,GPIO_PIN_RESET);
						HAL_GPIO_WritePin(WHEEL_A2_AIN2_GPIO_Port,WHEEL_A2_AIN2_Pin,GPIO_PIN_SET);
						__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2, -wheelspeed[1]); 
					}
					else if (wheelspeed[1] > stop){
						
						HAL_GPIO_WritePin(WHEEL_A2_AIN1_GPIO_Port,WHEEL_A2_AIN1_Pin,GPIO_PIN_SET);
						HAL_GPIO_WritePin(WHEEL_A2_AIN2_GPIO_Port,WHEEL_A2_AIN2_Pin,GPIO_PIN_RESET);
						__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2, (wheelspeed[1]));
						
					}
					else{
						__HAL_TIM_SetCompare(&htim12,TIM_CHANNEL_2, 0);
					}
					
					if(wheelspeed[2] < -stop) {
						
						HAL_GPIO_WritePin(WHEEL_B1_BIN1_GPIO_Port,WHEEL_B1_BIN1_Pin,GPIO_PIN_SET);
						HAL_GPIO_WritePin(WHEEL_B1_BIN2_GPIO_Port,WHEEL_B1_BIN2_Pin,GPIO_PIN_RESET);
						__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_1, -wheelspeed[2]); 
					}
					else if(wheelspeed[2] > stop){
						HAL_GPIO_WritePin(WHEEL_B1_BIN1_GPIO_Port,WHEEL_B1_BIN1_Pin,GPIO_PIN_RESET);
						HAL_GPIO_WritePin(WHEEL_B1_BIN2_GPIO_Port,WHEEL_B1_BIN2_Pin,GPIO_PIN_SET);
						__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_1, wheelspeed[2]);
						
					}
					else{
					
					__HAL_TIM_SetCompare(&htim9,TIM_CHANNEL_1, 0);
					}
						
					if(wheelspeed[3] < -stop) {
						
						HAL_GPIO_WritePin(WHEEL_B2_BIN1_GPIO_Port,WHEEL_B2_BIN1_Pin,GPIO_PIN_RESET);
						HAL_GPIO_WritePin(WHEEL_B2_BIN2_GPIO_Port,WHEEL_B2_BIN2_Pin,GPIO_PIN_SET);
						__HAL_TIM_SetCompare(&htim13,TIM_CHANNEL_1, -wheelspeed[3]); 
					}
					else if(wheelspeed[3] > stop){
						HAL_GPIO_WritePin(WHEEL_B2_BIN1_GPIO_Port,WHEEL_B2_BIN1_Pin,GPIO_PIN_SET);
						HAL_GPIO_WritePin(WHEEL_B2_BIN2_GPIO_Port,WHEEL_B2_BIN2_Pin,GPIO_PIN_RESET);
						__HAL_TIM_SetCompare(&htim13,TIM_CHANNEL_1, wheelspeed[3]);
						
					}
					else{
						
						__HAL_TIM_SetCompare(&htim13,TIM_CHANNEL_1,  0 );
					}
		
		
	
			
			if(end_flag==1)// Mayve we still need PWM catch
		{
     	duty_cycle=(float)(Period_cnt1*(arr+1)+ccr_cnt1+1)*100/(Period_cnt2*(arr+1)+ccr_cnt2+1);
  		frequency=(float)cnt_clk/(Period_cnt2*(arr+1)+ccr_cnt2+1);
	
			end_flag=0; 
			
		}
		
		
	
	
    osDelay(1);
			}
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the Forservo thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void const * argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
	int end = 1750;
	int start = 900;
	int end_b = 900;
	int start_b =2200; 
  for(;;)
  {
		
	
		if(SBUS_CH.CH6 <= CH6){
		__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1, end+100);
		
		//
		__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_4, start);
    }
		else{
		__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1, start-50);
		
		//
		__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_4, end+100);
		
		}
		
		
		if(SBUS_CH.CH5<=CH5){
		
		__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2, start_b);
		
		//
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1, end_b);
    
		
		
		}else{
		__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2, end_b);
		
		//
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1, start_b);
		
		}
		
		osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
int * speedcc(int rx, int ry , int lx){
		// trans speed to MACAXIS
	
		static int wheelspeed[10]; // A1 A2  B1 B2
	
	//	int macx = ry * cos45 +  rx * cos45  ;
	//	int macy = ry * cos45 +  rx * cos45  ; 
		int macr = lx ;
	
		wheelspeed[0] = 0 ;
		wheelspeed[1] = 0 ;
		wheelspeed[2] = 0 ;
		wheelspeed[3] = 0 ;
	
	
	//trans valur to macx
 
		wheelspeed[0] = rx ;
		wheelspeed[1] = rx ;
		wheelspeed[2] = rx ;
		wheelspeed[3] = rx ;
	
	// 
	 wheelspeed[0] += ry ;
	 wheelspeed[1] += ry ;
	 wheelspeed[2] -= ry ;
	 wheelspeed[3] -= ry ;
	
	
		// cc and add rotate speed to the car 
		
		wheelspeed[0] -= lx ;
		wheelspeed[1] += lx ; 
		wheelspeed[2] += lx ; 
		wheelspeed[3] -= lx ;
		
		return wheelspeed;
		
	

}	
/* USER CODE END Application */
