/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-09-10 04:30:49
 * @LastEditTime: 2022-09-20 01:12:00
 */
#include "LCD_Task.h"

osThreadId_t LCD_TaskHandle;
const osThreadAttr_t LCDTask_attributes = {
    .name = "LCD_Task",
    .stack_size = 1024 * 8,
    .priority = (osPriority_t)osPriorityLow,
};



osSemaphoreId_t LCD_BinarySemHandle;
const osSemaphoreAttr_t LCD_BinarySem_attributes = {
    .name = "LCD_BinarySem"};

		
 
		
/**
 * @brief LCD任务
 * @param {void} *argument
 * @return {*}
 */
void LCD_Task(void *argument)
{
  /*LCD*/
  LCD_Init();
	
	 
	LCD_FillColor_DMA(0, 0, 127, 127, 0x400);
	
  for (;;)
  {
    osDelay(800);

  };
}