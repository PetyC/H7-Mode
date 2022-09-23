/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-06 03:34:41
 * @LastEditTime: 2022-09-19 16:29:51
 */
#ifndef LED_TASK_H_
#define LED_TASK_H_


#include "Task_Public.h"


/*任务句柄*/
extern osThreadId_t LED_TaskHandle;
extern const osThreadAttr_t LEDTask_attributes;


/*任务体*/
void LED_Task(void *argument);

#endif
