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
#include "esp8266.h"
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
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart2_rx;

/* USER CODE BEGIN PV */
uint32_t Start=0,End=0,Duration=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void ESP8266_Test_Case_1(void)
{
	Start = HAL_GetTick();
	ESP8266_RESPONSE Response = ESP8266_Init(&huart2,&ESP8266_Configuration);
	End = HAL_GetTick();
	Duration = End - Start;
}
void ESP8266_Test_Case_2(void)
{
	ESP8266_RESPONSE Response = 0;
	uint8_t AP_IP_Address[100];
	uint8_t Station_IP_Address[100];
	Start = HAL_GetTick();
	Response = ESP8266_Get_AP_IP_Address(AP_IP_Address);
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_Get_Station_IP_Address(Station_IP_Address);
	End = HAL_GetTick();
	Duration = End - Start;
}
void ESP8266_Test_Case_3(void)
{
	ESP8266_RESPONSE Response = 0;
	uint8_t Connected_Devices_Number = 0;
	uint8_t Device_IP_Address[4][20]={0};
	uint8_t Device_MAC_Address[4][20]={0};
	Start = HAL_GetTick();
	Response = ESP8266_Get_Connected_Devices_Number(&Connected_Devices_Number);
	End = HAL_GetTick();
	Duration = End - Start;
	for(uint8_t i=0 ; i<4 ; i++)
	{
		Start = HAL_GetTick();
		Response = ESP8266_Get_Connected_Device_Addresses(Device_IP_Address[i],\
				  	  	  	  	  Device_MAC_Address[i],i);
		End = HAL_GetTick();
		Duration = End - Start;
	}
}
void ESP8266_Test_Case_4(void)
{
	ESP8266_RESPONSE Response = 0;
	Start = HAL_GetTick();
	Response = ESP8266_WiFi_Disconnect();
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_WiFi_Connect("iPhone","11442001");
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_Check_Internet_Connection();
	End = HAL_GetTick();
	Duration = End - Start;
}
void ESP8266_Test_Case_5(void)
{
	ESP8266_RESPONSE Response = 0;
	Start = HAL_GetTick();
	Response = ESP8266_Configure_AccessPoint("HACKER","12345678",2,1);
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_Search_AccessPoint("A51S");
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_Search_AccessPoint("EECE2025");
	End = HAL_GetTick();
	Duration = End - Start;
}
void ESP8266_Test_Case_6(void)
{
	ESP8266_RESPONSE Response = 0;
	uint8_t connections_number = 0;
	uint8_t Data[500];
	uint32_t Data_Size;
	uint8_t Station_IP_Address[100];

	Start = HAL_GetTick();
	//Response = ESP8266_Establish_TCP_Connection("54.81.146.55",1883);
	Response = ESP8266_Establish_TCP_Connection("192.168.254.94",51216);
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_Check_TCP_Connections_Number(&connections_number);
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_Send_TCP_Packets("Send me dudes\r\n",16,0,SEND_ONLY,NULL);
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_Start_Receive_TCP_Packets();
	End = HAL_GetTick();
	Duration = End - Start;
	while(ESP8266_Check_Inbox(0) == RESPONSE_NOT_OK);
	Start = HAL_GetTick();
	Response = ESP8266_Read_TCP_Packets(Data,&Data_Size,0);
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_Stop_Receiving_TCP_Packets();
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_Close_TCP_Connection(0);
	End = HAL_GetTick();
	Duration = End - Start;

}
void ESP8266_Test_Case_7(void)
{
	ESP8266_RESPONSE Response = 0;
	uint8_t connections_number = 0;
	uint8_t Data[4][500];
	uint32_t Data_Sizes[4];
	Start = HAL_GetTick();
	Response = ESP8266_Establish_TCP_Server();
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_Start_Receive_TCP_Packets();
	End = HAL_GetTick();
	Duration = End - Start;
	while((ESP8266_Check_Inbox(0) == RESPONSE_NOT_OK) && (ESP8266_Check_Inbox(1) == RESPONSE_NOT_OK) && (ESP8266_Check_Inbox(2) == RESPONSE_NOT_OK) && (ESP8266_Check_Inbox(3) == RESPONSE_NOT_OK));
	if(ESP8266_Check_Inbox(0) == RESPONSE_OK)
	{
		Start = HAL_GetTick();
		Response = ESP8266_Read_TCP_Packets(Data[0],&Data_Sizes[0],0);
		End = HAL_GetTick();
		Duration = End - Start;
		Start = HAL_GetTick();
		Response = ESP8266_Send_TCP_Packets("abcdefg\r\n",10,0,SEND_ONLY,NULL);
		End = HAL_GetTick();
		Duration = End - Start;
	}
	if(ESP8266_Check_Inbox(1) == RESPONSE_OK)
	{
		Start = HAL_GetTick();
		Response = ESP8266_Read_TCP_Packets(Data[1],&Data_Sizes[1],1);
		End = HAL_GetTick();
		Duration = End - Start;
		Start = HAL_GetTick();
		Response = ESP8266_Send_TCP_Packets("abcdefg\r\n",10,0,SEND_ONLY,NULL);
		End = HAL_GetTick();
		Duration = End - Start;
	}
	if(ESP8266_Check_Inbox(2) == RESPONSE_OK)
	{
		Start = HAL_GetTick();
		Response = ESP8266_Read_TCP_Packets(Data[2],&Data_Sizes[2],2);
		End = HAL_GetTick();
		Duration = End - Start;
		Start = HAL_GetTick();
		Response = ESP8266_Send_TCP_Packets("abcdefg\r\n",10,0,SEND_ONLY,NULL);
		End = HAL_GetTick();
		Duration = End - Start;
	}
	if(ESP8266_Check_Inbox(3) == RESPONSE_OK)
	{
		Start = HAL_GetTick();
		Response = ESP8266_Read_TCP_Packets(Data[3],&Data_Sizes[3],3);
		End = HAL_GetTick();
		Duration = End - Start;
		Start = HAL_GetTick();
		Response = ESP8266_Send_TCP_Packets("abcdefg\r\n",10,0,SEND_ONLY,NULL);
		End = HAL_GetTick();
		Duration = End - Start;
	}
	Start = HAL_GetTick();
	Response = ESP8266_Check_TCP_Connections_Number(&connections_number);
	End = HAL_GetTick();
	Duration = End - Start;
	/*Close connection from Packet Sender*/
	Start = HAL_GetTick();
	Response = ESP8266_Check_TCP_Connections_Number(&connections_number);
	End = HAL_GetTick();
	Duration = End - Start;
	/*2 closes in case i closed a wrong connection from Packet Sender*/
	Start = HAL_GetTick();
	Response = ESP8266_Close_TCP_Connection(0);
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_Close_TCP_Connection(1);
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_Check_TCP_Connections_Number(&connections_number);
	End = HAL_GetTick();
	Duration = End - Start;
	Start = HAL_GetTick();
	Response = ESP8266_Disband_TCP_Server();
	End = HAL_GetTick();
	Duration = End - Start;
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == USART2)
	{
		Start = HAL_GetTick();
		ESP8266_Receive_TCP_Packets_Callback();
		End = HAL_GetTick();
		Duration = End - Start;
	}
}

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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */

  ESP8266_Test_Case_1();
  //ESP8266_Test_Case_2();
  //ESP8266_Test_Case_3();
  //ESP8266_Test_Case_4();
  //ESP8266_Test_Case_5();
  //ESP8266_Test_Case_6();
  //ESP8266_Test_Case_7();

  /* USER CODE END 2 */

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
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
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);
  /* DMA1_Channel6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

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
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB11 PB6 PB7 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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
