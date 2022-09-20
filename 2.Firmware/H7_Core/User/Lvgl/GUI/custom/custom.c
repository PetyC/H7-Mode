/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-08-26 22:53:22
 * @LastEditTime: 2022-08-30 23:32:31
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

void ta_event_cb(lv_event_t * e);

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
 * @brief Wifi连接状态图标控制
 * @param {uint8_t} Enagle
 * @return {*}
 */
void UI_Wifi_ImagesDispaly(uint8_t Enagle)
{
  if(Enagle == 1)
  {
    lv_img_set_src(guider_ui.main_screen_wifi_img, &_WIFI_con_15x14);
  }
  else
  {
    lv_img_set_src(guider_ui.main_screen_wifi_img, &_WIFI_discon_15x14);
  }
}



/**
 * @brief WIFI设置界面初始化
 * @return {*}
 */
void UI_Wifi_Set_ScreenInit(void)
{
  lv_obj_add_state(  guider_ui.Wifi_screen_wifi_en_sw , LV_STATE_CHECKED );
 
}
