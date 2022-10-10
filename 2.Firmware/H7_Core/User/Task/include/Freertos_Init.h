/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-06 03:37:47
 * @LastEditTime: 2022-10-10 18:04:47
 */
#ifndef FREERTOS_INIT_H_
#define FREERTOS_INIT_H_

/*FreeRTOS相关头文件*/
#include "Task_Public.h"

/*C库相关*/
#include  <stdio.h>
 

/*Event Recorder调试组件*/
#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif


/*Task头文件*/
#include "LED_Task.h"
#include "Uart_Task.h"
#include "Test_Task.h"
#include "LCD_Task.h"
#include "Network_Task.h"
#include "IAP_Task.h"


/*底层头文件*/
#include "User_config.h"

/*BSP驱动*/
#include "Bsp_DWT.h"
#include "Bsp_MPU.h"

/*Freertos初始化*/
void Freertos_Init(void);

/*MPU配置*/
void MPU_Config(void);

#endif