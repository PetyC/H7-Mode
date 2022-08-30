/*
 * @Description: NetWork相关
 * @Autor: Pi
 * @Date: 2022-08-08 18:24:22
 * @LastEditTime: 2022-08-30 19:49:25
 */
 
#ifndef NETWORK_TASK_H
#define NETWORK_TASK_H


/*FreeRTOS相关头文件*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/*任务通知*/
#define NETWORK_CONNECT_BIT0  (1)
#define NETWORK_DISCONNECT_BIT1 (1 << 1)


/*相关微库*/
#include "string.h"
#include "stdio.h"

/*BSP相关文件*/
#include "main.h"
#include "Bsp_ESP8266.h"
#include "Network.h"

void Network_Task(void const * argument);



#endif
