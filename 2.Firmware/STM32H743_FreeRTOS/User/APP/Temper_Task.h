/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-08-27 22:05:09
 * @LastEditTime: 2022-08-27 22:05:40
 */
#ifndef TEMPER_TASK_
#define TEMPER_TASK_


/*FreeRTOS相关头文件*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"


/*BSP相关文件*/
#include "main.h"
#include "adc.h"

void Temper_Task(void const * argument);

#endif
