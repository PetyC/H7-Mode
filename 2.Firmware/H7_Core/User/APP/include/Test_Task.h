/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-08 14:31:41
 * @LastEditTime: 2022-09-19 16:29:55
 */
#ifndef TEST_TASK_H_
#define TEST_TASK_H_


#include "Task_Public.h"

/*相关驱动*/
#include "Bsp_Nand_Flash.h"
#include "Bsp_w25qxx.h"
#include "Bsp_st7735s.h"


#include "User_FlashFS.h"
#include "rl_usb.h"

/*Freertos句柄*/
extern osThreadId_t Test_TaskHandle;
extern const osThreadAttr_t TestTask_attributes;



void Test_Task(void *argument);


#endif
