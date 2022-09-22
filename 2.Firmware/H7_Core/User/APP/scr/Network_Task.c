/*
 * @Description: 网络任务
 * @Autor: Pi
 * @Date: 2022-09-22 19:54:11
 * @LastEditTime: 2022-09-22 20:00:43
 */
#include "Network_Task.h"


osThreadId_t NetWork_TaskHandle;
const osThreadAttr_t NetWorkTask_attributes = {
    .name = "NetWork_Task",
    .stack_size = 1024 * 4,
    .priority = (osPriority_t)osPriorityNormal7,
    .attr_bits = osThreadDetached,
};


osMessageQueueId_t KEY_QueueHandle;
const osMessageQueueAttr_t KEY_Queue_attributes = {
  .name = "KEY_Queue"
};

/**
 * @brief 网络任务
 * @param {void} *argument
 * @return {*}
 */
void NetWork_Task(void *argument)
{

  
  for (;;)
  {
     osDelay(800);
  }
}