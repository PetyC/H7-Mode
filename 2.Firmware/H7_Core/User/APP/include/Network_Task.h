/*
 * @Description: 网络任务
 * @Autor: Pi
 * @Date: 2022-09-22 19:54:15
 * @LastEditTime: 2022-09-22 20:00:12
 */
#ifndef NETWORK_TASK_H_
#define NETWORK_TASK_H_

#include "Task_Public.h"

extern osThreadId_t NetWork_TaskHandle;
extern const osThreadAttr_t NetWorkTask_attributes;

extern osMessageQueueId_t KEY_QueueHandle;
extern const osMessageQueueAttr_t KEY_Queue_attributes;


void NetWork_Task(void *argument);

#endif
