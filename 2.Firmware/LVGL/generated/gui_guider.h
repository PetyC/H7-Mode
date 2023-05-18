/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *main_screen;
	bool main_screen_del;
	lv_obj_t *main_screen_wifi_set_btn;
	lv_obj_t *main_screen_wifi_set_btn_label;
	lv_obj_t *main_screen_demo_btn;
	lv_obj_t *main_screen_demo_btn_label;
	lv_obj_t *main_screen_led_1;
	lv_obj_t *main_screen_wifi_img;
	lv_obj_t *device_screen;
	bool device_screen_del;
	lv_obj_t *device_screen_about_tileview;
	lv_obj_t *about_tileview_about_name_0;
	lv_obj_t *device_screen_label_3;
	lv_obj_t *device_screen_version_label;
	lv_obj_t *device_screen_mcu_label;
	lv_obj_t *device_screen_label_2;
	lv_obj_t *device_screen_type_label;
	lv_obj_t *device_screen_label_1;
	lv_obj_t *about_tileview_about_name_1;
	lv_obj_t *device_screen_return_btn;
	lv_obj_t *device_screen_return_btn_label;
	lv_obj_t *device_screen_check_btn;
	lv_obj_t *device_screen_check_btn_label;
	lv_obj_t *Wifi_screen;
	bool Wifi_screen_del;
	lv_obj_t *Wifi_screen_APU_btn;
	lv_obj_t *Wifi_screen_APU_btn_label;
	lv_obj_t *Wifi_screen_label_2;
	lv_obj_t *Wifi_screen_wifi_name_now_label;
	lv_obj_t *Wifi_screen_return_btn;
	lv_obj_t *Wifi_screen_return_btn_label;
	lv_obj_t *Wifi_screen_cont;
	lv_obj_t *Wifi_screen_wifi_en_sw;
	lv_obj_t *Wifi_screen_label_3;
	lv_obj_t *QR_screen;
	bool QR_screen_del;
	lv_obj_t *QR_screen_img_1;
	lv_obj_t *QR_screen_QR_bar;
}lv_ui;

void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_main_screen(lv_ui *ui);
void setup_scr_device_screen(lv_ui *ui);
void setup_scr_Wifi_screen(lv_ui *ui);
void setup_scr_QR_screen(lv_ui *ui);
LV_IMG_DECLARE(_QR_100x100);
LV_IMG_DECLARE(_WIFI_discon_15x14);

#ifdef __cplusplus
}
#endif
#endif