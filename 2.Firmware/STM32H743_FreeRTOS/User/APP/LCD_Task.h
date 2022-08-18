/*
 * @Description: LCD显示任务
 * @Autor: Pi
 * @Date: 2022-06-27 15:20:33
 * @LastEditTime: 2022-08-08 18:47:14
 */
#ifndef LCD_TASK_H
#define LCD_TASK_H

/*FreeRTOS相关头文件*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"


/*相关微库*/
#include <string.h>



/*BSP相关文件*/
#include "st7735s.h"
#include "fonts.h"
#include "gfx.h"




void LCD_Task(void const * argument);

#endif
