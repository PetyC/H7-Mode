/*
 * @Description: KEY按键任务
 * @Autor: Pi
 * @Date: 2022-06-27 18:29:33
 * @LastEditTime: 2022-08-08 18:29:25
 */
#ifndef KEY_TASK_H
#define KEY_TASK_H


/*FreeRTOS相关头文件*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"


/*BSP相关文件*/
#include "main.h"
#include "string.h"
#include "stdio.h"
#include "Bsp_Uart.h"



void KEY_Task(void const * argument);


#endif
