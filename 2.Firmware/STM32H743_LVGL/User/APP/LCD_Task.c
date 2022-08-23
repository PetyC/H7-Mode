/*
 * @Description: LCD显示任务
 * @Autor: Pi
 * @Date: 2022-06-27 15:14:05
 * @LastEditTime: 2022-08-23 03:36:40
 */
#include "LCD_Task.h"
#include "stdio.h"

/*FreeRTOS相关变量*/
extern osSemaphoreId Key_Binary_SemHandle;
extern osSemaphoreId LCD_BinarySemHandle;
/**
 * @brief LCD任务
 * @param {void*} argument
 * @return {*}
 */
void LCD_Task(void const *argument)
{
  /*初始值为1，防止未阻塞运行*/
  osSemaphoreWait(LCD_BinarySemHandle, osWaitForever);
  
  lv_init();
  lv_port_disp_init();
 
  lv_demo_benchmark();
  //lv_ui guider_ui;
  
  //setup_ui(&guider_ui);
  //events_init(&guider_ui);

  /* Infinite loop */
  for (;;)
  {
    
    lv_task_handler();
    osDelay(5);
  }
}





