/*
 * @Description: NetWork相关
 * @Autor: Pi
 * @Date: 2022-08-08 18:24:13
 * @LastEditTime: 2022-08-31 14:39:56
 */
#include "Network_Task.h"
#include "Bsp_Uart.h"

extern osMutexId Uart_MutexHandle;
extern osMessageQId KEY_QueueHandle;
extern osThreadId LCD_TaskHandle;


/**
 * @brief FreeRTOS运行的任务
 * @param {void*} argument
 * @return {*}
 */
void Network_Task(void const *argument)
{

  NetWork_Init();

  for (;;)
  {

    osDelay(50);
  }
}


