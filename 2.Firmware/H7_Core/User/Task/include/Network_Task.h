/*
 * @Description: 网络任务
 * @Autor: Pi
 * @Date: 2022-09-22 19:54:15
 * @LastEditTime: 2023-05-23 02:18:06
 */
#ifndef NETWORK_TASK_H_
#define NETWORK_TASK_H_

#include "Task_Public.h"

#include "Network.h"

extern osThreadId_t NetWork_TaskHandle;
extern const osThreadAttr_t NetWorkTask_attributes;

extern osMessageQueueId_t KEY_QueueHandle;
extern const osMessageQueueAttr_t KEY_Queue_attributes;

extern osSemaphoreId_t Network_QueueHandle;
extern const osMessageQueueAttr_t Network_Queue_attributes;

extern osSemaphoreId_t Wifi_Set_QueueHandle;
extern const osMessageQueueAttr_t Wifi_Set_attributes;

void NetWork_Task(void *argument);

#endif
