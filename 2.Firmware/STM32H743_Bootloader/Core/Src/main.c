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
#include "crc.h"
#include "dma.h"
#include "mdma.h"
#include "quadspi.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "IAP.h"
#include "app_uart.h"
#include "Bsp_w25qxx.h"
#include "Bsp_ESP8266.H"
#include "network.h"
#include "User_config.h"
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

/* MDK AC5 */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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


  //User_App_Jump_Init();

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
  MX_QUADSPI_Init();
  MX_MDMA_Init();
  MX_SPI1_Init();
  MX_FMC_Init();
  MX_TIM14_Init();
  MX_TIM1_Init();
  MX_CRC_Init();
  MX_TIM13_Init();
  MX_TIM12_Init();
  /* USER CODE BEGIN 2 */
 
  HAL_TIM_PWM_Start(&htim1 , TIM_CHANNEL_1);

  QSPI_W25Qx_Init();

  User_Config_Init();

  Bsp_ESP8266_Power(1);

	User_Networt_Apuconfig();
	while(1);


  /*不需要在Bootloader中查询更新信息话*/
  if(System_Config.Inquire == 0 && System_Config.Error == 0)
  {
    /*校验当前固件*/
    if(User_App_MCU_Flash_CRC(System_Config.Info.Bin_Size) == 0)    //CRC正确 则跳转
    {
      /*跳转*/
      User_App_Jump_Start();
    }
                                                           
    /*校验错误 则从外置Flash拉取备份文件*/

    /*擦除MCU Flash*/
    User_App_MCU_Flash_Erase(System_Config.Info.Bin_Size);

    /*还原MCU Flash内容*/
    User_App_Flash_Copy();
    
    /*再次校验*/
    if(User_App_MCU_Flash_CRC(System_Config.Info.Bin_Size) == 0)    
    {
      /*跳转*/
      User_App_Jump_Start();
    }

    /*设置极端错误标志*/
    System_Config.Error = 1;

    User_Config_Set(System_Config);
  }

  /*若发生极端错误 或需要开机检查更新 */

  Bsp_ESP8266_Power(1);

//User_Network_Connect_AP((uint8_t *)"Moujiti" , (uint8_t *)"moujiti7222");

  Bsp_ESP8266_RST();

  while(Bsp_ESP8266_Config("AT+CIPSTATUS\r\n", 15, "STATUS:2", NULL, 200, 5) != 0);

  /*建立TCP通信*/
  User_Network_Connect_Tcp(System_Config.Info.IP , System_Config.Info.Port , System_Config.Info.SSLEN);

  Info_Str Temp_Info;

  /*获取云端版本信息*/
  User_Network_Get_Info(System_Config.Info.IP ,  System_Config.Info.Info_Path , System_Config.Info.SSLEN , &Temp_Info);


  /*版本号相等 则无需更新*/
  if(strcmp((char *)Temp_Info.Version  , (char *)System_Config.Info.Version) == 0 && System_Config.Error == 0)
  {
    User_App_Jump_Start();
    /*正常情况下后面的不会执行了*/
  }

  /*需要更新*/
  System_Config.Updata = 1;

  /*更新除版本信息之外的信息*/
  uint8_t Version[10] = {0};
  memcpy(Version , System_Config.Info.Version , sizeof(System_Config.Info.Version));
  System_Config.Info = Temp_Info;
  memcpy(System_Config.Info.Version , Version , sizeof(System_Config.Info.Version));

 
  /*保存配置写入到外置Flash*/
  User_Config_Set(System_Config);
	
  if(System_Config.Error != 1)
  {
    /*备份至片外Flash*/
    User_App_MCU_Flash_Copy();
  }


  /*擦除MCU Flash*/
  User_App_MCU_Flash_Erase(System_Config.Info.Bin_Size);

  Bsp_ESP8266_RST();
  while(Bsp_ESP8266_Config("AT+CIPSTATUS\r\n", 15, "STATUS:2", NULL, 200, 5) != 0);

  /*建立TCP通信*/
  User_Network_Connect_Tcp(System_Config.Info.IP , System_Config.Info.Port , System_Config.Info.SSLEN);

  /*下载APP到MCU Flash*/
  User_Network_Down_Bin(System_Config.Info.IP ,  System_Config.Info.Bin_Path , System_Config.Info.SSLEN);

  /*校验MCU Flash APP 正确性 */
  if(User_App_MCU_Flash_CRC(System_Config.Info.Bin_Size) == 1)    //校验错误
  {
    /*擦除MCU Flash*/
    User_App_MCU_Flash_Erase(System_Config.Info.Bin_Size);

    /*还原MCU Flash内容*/
    User_App_Flash_Copy();

    /*跳转*/
    User_App_Jump_Start();
  }

  /*更新Config*/
  memcpy(System_Config.Info.Version , Temp_Info.Version , sizeof(Temp_Info.Version));

  System_Config.Inquire = 0;
  System_Config.Error = 0;
  System_Config.Updata = 0;

  User_Config_Set(System_Config);

  /*跳转*/
  User_App_Jump_Start();


  /*正常情况不会运行到后面去*/

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {



    // app_loop();
    
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSE);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  RCC_OscInitStruct.PLL.PLLR = 5;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/**
 * @brief 定时器中断回调函�?
 * @param {TIM_HandleTypeDef} *htim
 * @return {*}
 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM13)
  {
    User_UART_Timer();
    //HAL_GPIO_TogglePin(LED1_GPIO_Port , LED1_Pin );
  }
	else if(htim->Instance == TIM12)
	{
    //User_UART_TX_Timer();
//		Bsp_ESP8266_Timer();
    User_Networt_Timer();
  }
}
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
