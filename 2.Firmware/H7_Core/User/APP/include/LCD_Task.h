/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-10 04:30:53
 * @LastEditTime: 2022-09-19 16:30:44
 */
#ifndef LCD_TASK_H_
#define LCD_TASK_H_

#include "Task_Public.h"
#include "Bsp_st7735s.h"
#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

extern osThreadId_t LCD_TaskHandle;
extern const osThreadAttr_t LCDTask_attributes;

extern osSemaphoreId_t LCD_BinarySemHandle;
extern const osSemaphoreAttr_t LCD_BinarySem_attributes;


void LCD_Task(void *argument);

#endif
