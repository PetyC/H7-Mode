/*
 * @Description: KEY按键任务
 * @Autor: Pi
 * @Date: 2022-06-27 18:29:29
 * @LastEditTime: 2022-08-24 01:34:57
 */
#include "KEY_Task.h"

extern UART_HandleTypeDef huart1;

/*FreeRTOS相关变量*/
extern osSemaphoreId Key_Binary_SemHandle;

extern ADC_HandleTypeDef hadc3;
/**
 * @brief KEY按键任务，按下打印任务相关信息
 * @return {*}
 */
void KEY_Task(void const *argument)
{
  /* USER CODE BEGIN Start_KEY_Task */
//    char pcWriteBuffer[512];
  uint16_t TS_CAL1 = 0;
	uint16_t TS_CAL2 = 0;
  static uint16_t mpu_temp = 0;
  
  HAL_ADCEx_Calibration_Start(&hadc3 , ADC_CALIB_OFFSET,ADC_SINGLE_ENDED);//校准ADC 
  HAL_ADC_PollForConversion(&hadc3,10);	//等待转换完成，10ms表示超时时间
  HAL_ADC_Start(&hadc3);	//启动ADC转换
  osDelay(50);
  mpu_temp = HAL_ADC_GetValue(&hadc3);	//读取ADC转换数据（16位数据）
  TS_CAL1 = *(__IO uint16_t *)(0x1FF1E820);
	TS_CAL2 = *(__IO uint16_t *)(0x1FF1E840);
  mpu_temp = ((110.0f - 30.0f) / (TS_CAL2 - TS_CAL1)) * (mpu_temp - TS_CAL1) + 30.0f;
  /* Infinite loop */
  for (;;)
  {
    if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == 1)
    {
      osDelay(50);

      if (HAL_GPIO_ReadPin(KEY_GPIO_Port, KEY_Pin) == 1)
      {
        //产生2进制信号量
        osSemaphoreRelease(Key_Binary_SemHandle);
   
 /*       
#if (configUSE_TRACE_FACILITY == 1 && configUSE_STATS_FORMATTING_FUNCTIONS == 1)
        memset(pcWriteBuffer, 0, 512);
        sprintf((char *)pcWriteBuffer, "\r\n%s\r\n", "name  state  priority  residue_stack  Number");
        strcat((char *)pcWriteBuffer, "---------------------------------------------\r\n");
        vTaskList((char *)(pcWriteBuffer + strlen(pcWriteBuffer)));
        strcat((char *)pcWriteBuffer, "---------------------------------------------\r\n");
        strcat((char *)pcWriteBuffer, "B : Blocked, R : Ready, D : Deleted, S : Suspended\r\n");

        Bsp_UART_Write(&huart1, (uint8_t *)pcWriteBuffer, strlen(pcWriteBuffer));
#endif
#if (configGENERATE_RUN_TIME_STATS == 1 && configUSE_STATS_FORMATTING_FUNCTIONS == 1)
        memset(pcWriteBuffer, 0, 512);
        strcat((char *)pcWriteBuffer, "\r\nName\t\tTime\t\tUsage rate\r\n");
        strcat((char *)pcWriteBuffer, "---------------------------------------------\r\n");
        vTaskGetRunTimeStats((char *)(pcWriteBuffer + strlen(pcWriteBuffer)));
        strcat((char *)pcWriteBuffer, "---------------------------------------------\r\n");

        Bsp_UART_Write(&huart1, (uint8_t *)pcWriteBuffer, strlen(pcWriteBuffer));

#endif
        Bsp_UART_Poll_DMA_TX(&huart1);
        */
      }
    }

    osDelay(20);
  }
}
