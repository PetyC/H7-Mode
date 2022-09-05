/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-06 03:37:47
 * @LastEditTime: 2022-09-06 04:11:57
 */
#ifndef FREERTOS_INIT_H_
#define FREERTOS_INIT_H_

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "main.h"

/*Event Recorder调试组件*/
#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif


/*Task头文件*/
#include "LED_Task.h"
#include "Uart_Task.h"


void Freertos_Init(void);


#endif
