/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-06 01:28:00
 * @LastEditTime: 2022-09-06 04:11:50
 */
#include "freertos_Init.h"





/*默认任务*/
static osThreadId_t Default_TaskHandle;
const osThreadAttr_t DefaultTask_attributes = {
  .name = "Default_Task",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};


/**
 * @brief 默认任务，用于创建其他任务
 * @param {void} *argument
 * @return {*}
 */
static void Default_Task(void *argument)
{
	/*创建其他任务*/
	LED_TaskHandle = osThreadNew(LED_Task, NULL, &LEDTask_attributes);

  Uart_TaskHandle = osThreadNew(Uart_Task, NULL, &UartTask_attributes);


  /*删除自身任务*/
  vTaskDelete(NULL);

  while (1);

 
}



void Freertos_Init(void)
{
  Default_TaskHandle = osThreadNew(Default_Task, NULL, &DefaultTask_attributes);

#ifdef RTE_Compiler_EventRecorder
  // Initialize and start Event Recorder
  EventRecorderInitialize(EventRecordAll, 1U);
  EventRecorderStart();
#endif

  osKernelInitialize(); 

  osKernelStart();

  while (1);

}