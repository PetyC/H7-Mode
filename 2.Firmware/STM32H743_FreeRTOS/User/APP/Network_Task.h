/*
 * @Description: NetWork相关
 * @Autor: Pi
 * @Date: 2022-08-08 18:24:22
 * @LastEditTime: 2022-08-16 20:21:30
 */
 
#ifndef NETWORK_TASK_H
#define NETWORK_TASK_H


/*FreeRTOS相关头文件*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/*相关微库*/
#include "string.h"
#include "stdio.h"

/*BSP相关文件*/
#include "main.h"
#include "Bsp_ESP8266.h"
#include "Network.h"




enum
{
  Key_Right = 0,
  Key_Light = 1,
  Key_Press = 2
};


void Network_Task(void const * argument);



#endif
