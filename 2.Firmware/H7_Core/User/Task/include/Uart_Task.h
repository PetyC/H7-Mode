/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-06 04:01:57
 * @LastEditTime: 2022-09-19 16:29:33
 */
#ifndef UART_TASK_H
#define UART_TASK_H

#include "Task_Public.h"


#include "Bsp_Uart.h"

/*Freertos句柄*/
extern osThreadId_t Uart_TaskHandle;
extern const osThreadAttr_t UartTask_attributes;


void Uart_Task(void *argument);

#endif