/*
 * @Description:串口任务
 * @Autor: Pi
 * @Date: 2022-09-06 04:01:54
 * @LastEditTime: 2022-09-09 19:48:53
 */
#include "Uart_Task.h"

osThreadId_t Uart_TaskHandle;
const osThreadAttr_t UartTask_attributes = {
    .name = "Uart_Task",
    .stack_size = 1024 * 4,
    .priority = (osPriority_t)osPriorityNormal,
    .attr_bits = osThreadDetached,
};


#include <stdio.h>

/**
 * @brief Uart任务
 * @param {void} *argument
 * @return {*}
 */
void Uart_Task(void *argument)
{

  uint32_t size;

  for (;;)
  {
     uint8_t buff[255];
		
    size = Bsp_UART_Read(&huart1, buff, 255);

    if (size > 0)
    {
      Bsp_UART_Write(&huart1, buff, size);
			
      Bsp_UART_Poll_DMA_TX(&huart1);
    }
    
    osDelay(5);
  }
}