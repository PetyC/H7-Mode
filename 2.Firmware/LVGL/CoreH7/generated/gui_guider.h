/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *main_screen;
	lv_obj_t *main_screen_tileview;
	lv_obj_t *main_screen_tileview_tileview;
	lv_obj_t *main_screen_Wifi_Set_btn;
	lv_obj_t *main_screen_Wifi_Set_btn_label;
	lv_obj_t *main_screen_Demo_btn;
	lv_obj_t *main_screen_Demo_btn_label;
	lv_obj_t *Wifi_screen;
	lv_obj_t *Wifi_screen_APU_btn;
	lv_obj_t *Wifi_screen_APU_btn_label;
	lv_obj_t *Wifi_screen_label_1;
	lv_obj_t *Wifi_screen_Wifi_sw;
	lv_obj_t *Wifi_screen_label_2;
	lv_obj_t *Wifi_screen_wifi_name_now_label;
	lv_obj_t *Wifi_screen_btn_1;
	lv_obj_t *Wifi_screen_btn_1_label;
}lv_ui;

void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_main_screen(lv_ui *ui);
void setup_scr_Wifi_screen(lv_ui *ui);

#ifdef __cplusplus
}
#endif
#endif