/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-06 04:01:57
 * @LastEditTime: 2022-09-06 04:10:35
 */
#ifndef UART_TASK_H
#define UART_TASK_H

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "main.h"

#include "Bsp_Uart.h"

extern osThreadId_t Uart_TaskHandle;
extern const osThreadAttr_t UartTask_attributes;


void Uart_Task(void *argument);

#endif