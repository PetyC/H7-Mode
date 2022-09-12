/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-10 04:30:53
 * @LastEditTime: 2022-09-10 04:32:44
 */
#ifndef USB_TASK_H_
#define USB_TASK_H_

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os2.h"
#include "main.h"


extern osThreadId_t USB_TaskHandle;
extern const osThreadAttr_t USBTask_attributes;



void USB_Task(void *argument);

#endif
