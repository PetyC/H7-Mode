/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-08-27 21:56:20
 * @LastEditTime: 2022-08-27 21:59:36
 */
#include "Default_Task.h"


void Default_Task(void const * argument)
{
  for (;;)
  {
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    osDelay(800);
  }
}
