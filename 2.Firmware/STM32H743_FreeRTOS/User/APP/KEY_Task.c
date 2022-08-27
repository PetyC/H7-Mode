/*
 * @Description: KEY按键任务
 * @Autor: Pi
 * @Date: 2022-06-27 18:29:29
 * @LastEditTime: 2022-08-27 22:11:22
 */
#include "KEY_Task.h"

extern UART_HandleTypeDef huart1;

/*FreeRTOS相关变量*/
extern osSemaphoreId Key_Binary_SemHandle;

/**
 * @brief KEY按键任务，按下打印任务相关信息
 * @return {*}
 */
void KEY_Task(void const *argument)
{
  /* USER CODE BEGIN Start_KEY_Task */
//    char pcWriteBuffer[512];
 
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
