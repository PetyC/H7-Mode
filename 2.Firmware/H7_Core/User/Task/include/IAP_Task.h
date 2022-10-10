/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-10-10 17:58:48
 * @LastEditTime: 2022-10-10 18:03:28
 */
#ifndef IAP_TASK_H_
#define IAP_TASK_H_

#include "Task_Public.h"

#include "User_config.h" 

extern osThreadId_t IAP_TaskHandle;
extern const osThreadAttr_t IAPTask_attributes;


void IAP_Task(void *argument);

#endif
