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
    .stack_size = 1024 * 10,
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
  /*初始化LCD*/
  LCD_Init();
	//LCD_FillColor_DMA(0, 0, 127, 127, 0x00);
	
	/*初始化LVGL*/
	lv_init();
	/*初始化显示*/
	lv_port_disp_init();
	/*初始化输入设备*/
	//lv_port_indev_init();
	
	  /*初始化自定义UI*/
  setup_ui(&guider_ui);
 // events_init(&guider_ui);
	
	/*延时*/
  TickType_t xLastWakeTime = 0;
  xLastWakeTime = xTaskGetTickCount(); 
	
  for (;;)
  {
    
		vTaskDelayUntil( &xLastWakeTime,10);

		lv_task_handler();
  };
}