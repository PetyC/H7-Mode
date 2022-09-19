/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-06 03:37:47
 * @LastEditTime: 2022-09-19 19:26:02
 */
#ifndef FREERTOS_INIT_H_
#define FREERTOS_INIT_H_

/*FreeRTOS相关头文件*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os2.h"

/*C库相关*/
#include  <stdio.h>
 
/*工程相关*/
#include "main.h"


/*Event Recorder调试组件*/
#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif


/*Task头文件*/
#include "LED_Task.h"
#include "Uart_Task.h"
#include "Test_Task.h"
#include "LCD_Task.h"


/*Freertos初始化*/
void Freertos_Init(void);

/*MPU配置*/
void MPU_Config(void);

#endif
