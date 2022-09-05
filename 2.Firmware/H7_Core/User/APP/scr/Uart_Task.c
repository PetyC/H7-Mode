/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-06 04:01:54
 * @LastEditTime: 2022-09-06 04:18:22
 */
#include "Uart_Task.h"


osThreadId_t Uart_TaskHandle;
const osThreadAttr_t UartTask_attributes = {
  .name = "Uart_Task",
  .stack_size = 1024 * 4,
  .priority = (osPriority_t) osPriorityHigh,
};



#include "Bsp_w25qxx.h"

/**
 * @brief LED任务
 * @param {void} *argument
 * @return {*}
 */
void Uart_Task(void *argument)
{

  uint32_t size;
  uint8_t buff[255];
  static uint32_t count;



  QSPI_FLASH_Test_ReadSpeed();

  for (;;)
  {
    
    size = Bsp_UART_Read(&huart1, buff, 255);

    if (size > 0)
    {
      Bsp_UART_Write(&huart1, buff, size);
      Bsp_UART_Poll_DMA_TX(&huart1);
    }

    osDelay(5);
  }
  
}