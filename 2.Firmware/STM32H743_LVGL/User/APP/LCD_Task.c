/*
 * @Description: LCD显示任务
 * @Autor: Pi
 * @Date: 2022-06-27 15:14:05
 * @LastEditTime: 2022-08-23 03:36:40
 */
#include "LCD_Task.h"
#include "stdio.h"

/*FreeRTOS相关变量*/
extern osSemaphoreId Key_Binary_SemHandle;

static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
}

/**
 * Create a button with a label and react on click event.
 */
void lv_example_get_started_1(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/
    lv_obj_center(label);
}



/**
 * @brief LCD任务
 * @param {void*} argument
 * @return {*}
 */
void LCD_Task(void const *argument)
{

  lv_init();
  lv_port_disp_init();
  //lv_example_get_started_1();
  //lv_example_get_started_1();
  uint8_t Tpye = 0;
  lv_demo_benchmark();
  /* Infinite loop */
  for (;;)
  {
    
  lv_task_handler();
  osDelay(10);
  }
}





