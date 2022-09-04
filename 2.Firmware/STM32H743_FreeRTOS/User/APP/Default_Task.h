/*
 * @Description: 默认任务
 * @Autor: Pi
 * @Date: 2022-08-27 21:56:33
 * @LastEditTime: 2022-08-27 21:57:04
 */
#ifndef DEFAULT_TASK_H
#define DEFAULT_TASK_H


/*FreeRTOS相关头文件*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"


/*BSP相关文件*/
#include "main.h"




void Default_Task(void const * argument);


#endif
