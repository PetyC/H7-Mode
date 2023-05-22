/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-08-26 22:53:22
 * @LastEditTime: 2023-05-23 03:12:57
 */
// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/**
 * @file custom.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/
extern lv_indev_t *indev_encoder;

lv_group_t *encoder_group;
/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
  encoder_init();
}

/**
 * @brief 按键初始化
 * @return {*}
 */
void encoder_init(void)
{
  /*创建对象分组*/
  encoder_group = lv_group_create();

  /*设置默认分组*/
  lv_group_set_default(encoder_group);

  /*将对象分组分配至输入设备*/
  lv_indev_set_group(indev_encoder, encoder_group);
}


#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os2.h"
extern osSemaphoreId_t Network_QueueHandle;

/**
 * @brief 主菜单按键组初始化
 * @return {*}
 */
void encoder_main_init(void)
{
  /*移除原先所有对象*/
  lv_group_remove_all_objs(encoder_group);

  /*重新将被控制的对象添加进group*/
  lv_group_add_obj(encoder_group, guider_ui.main_screen_wifi_set_btn);
  lv_group_add_obj(encoder_group, guider_ui.main_screen_demo_btn);

  uint8_t network_sta = 0;
  
  if(osMessageQueueGet(Network_QueueHandle , &network_sta , 0 , 0) == osOK)
  {
    if(network_sta == 2)
    {
      UI_Wifi_ImagesDispaly(1);
    }
    else
    {
      UI_Wifi_ImagesDispaly(0);
    }
    
  }
}



/**
 * @brief wifi界面按键初始化
 * @return {*}
 */
void encoder_wifi_init(void)
{
  /*移除原先所有对象*/
  lv_group_remove_all_objs(encoder_group);

  lv_group_add_obj(encoder_group, guider_ui.Wifi_screen_wifi_en_sw);
  lv_group_add_obj(encoder_group, guider_ui.Wifi_screen_APU_btn);
  lv_group_add_obj(encoder_group, guider_ui.Wifi_screen_return_btn);


  
}

/**
 * @brief 小程序二维码界面按键初始化
 * @return {*}
 */
void encoder_qr_init(void)
{
  /*移除原先所有对象*/
  lv_group_remove_all_objs(encoder_group);
}

void ta_event_cb(lv_event_t *e);

/**
 * @brief 设备信息界面按键初始化
 * @return {*}
 */
void encoder_device_init(void)
{
  /*移除原先所有对象*/
  lv_group_remove_all_objs(encoder_group);

  lv_group_add_obj(encoder_group, guider_ui.device_screen_about_tileview);
  lv_group_add_obj(encoder_group, guider_ui.device_screen_check_btn);
  lv_group_add_obj(encoder_group, guider_ui.device_screen_return_btn);
}

/**
 * @brief 开机进度条控制
 * @param {uint8_t} num
 * @return {*}
 */
void UI_Start_Schedule_Bar_Set(uint8_t num)
{
  lv_bar_set_value(guider_ui.start_screen_schedule_bar, num, LV_ANIM_OFF);
}

/**
 * @brief Wifi连接状态图标控制
 * @param {uint8_t} Enagle
 * @return {*}
 */
void UI_Wifi_ImagesDispaly(uint8_t Enagle)
{
  if (Enagle == 1)
  {
    lv_img_set_src(guider_ui.main_screen_wifi_img, &_WIFI_con_15x14);
  }
  else
  {
    lv_img_set_src(guider_ui.main_screen_wifi_img, &_WIFI_discon_15x14);
  }
}


extern uint8_t s_wifi_set;
/**
 * @brief WIFI设置界面初始化
 * @return {*}
 */
void UI_Wifi_Set_ScreenInit(void)
{

  if(s_wifi_set == 1)
  {
    lv_obj_add_state(guider_ui.Wifi_screen_wifi_en_sw, LV_STATE_CHECKED);
  }
  else
  {
    lv_obj_clear_state(guider_ui.Wifi_screen_wifi_en_sw, LV_STATE_CHECKED);
  }
}
