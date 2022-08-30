/*
 * @Description: LCD显示任务
 * @Autor: Pi
 * @Date: 2022-06-27 15:20:33
 * @LastEditTime: 2022-08-30 22:57:55
 */
#ifndef LCD_TASK_H
#define LCD_TASK_H

/*FreeRTOS相关头文件*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "limits.h"
#include "Network_Task.h"


/*相关微库*/
#include <string.h>



/*BSP相关文件*/
#include "Bsp_st7735s.h"
#include "st7735s.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"


#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

void LCD_Task(void const * argument);

#endif
