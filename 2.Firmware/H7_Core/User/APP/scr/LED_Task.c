/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-06 03:34:31
 * @LastEditTime: 2022-09-06 04:00:14
 */
#include "LED_Task.h"

osThreadId_t LED_TaskHandle;
const osThreadAttr_t LEDTask_attributes = {
  .name = "LED_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};






/**
 * @brief LED任务
 * @param {void} *argument
 * @return {*}
 */
void LED_Task(void *argument)
{
  for (;;)
  {
		
    HAL_GPIO_TogglePin(LED2_GPIO_Port , LED2_Pin);
    osDelay(800);
  }
  
}