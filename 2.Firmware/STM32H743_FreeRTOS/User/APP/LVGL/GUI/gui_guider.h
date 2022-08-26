/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-08-25 15:31:45
 * @LastEditTime: 2022-08-26 19:31:46
 */
/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H


#include "lvgl/lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *main_screen;
	bool main_screen_del;
	lv_obj_t *main_screen_Wifi_Set_btn;
	lv_obj_t *main_screen_Wifi_Set_btn_label;
	lv_obj_t *main_screen_Wifi_State_label;
	lv_obj_t *main_screen_Demo_btn;
	lv_obj_t *main_screen_Demo_btn_label;
	lv_obj_t *Wifi_screen;
	bool Wifi_screen_del;
	lv_obj_t *Wifi_screen_APU_btn;
	lv_obj_t *Wifi_screen_APU_btn_label;
	lv_obj_t *Wifi_screen_label_1;
	lv_obj_t *Wifi_screen_Wifi_sw;
	lv_obj_t *Wifi_screen_label_2;
	lv_obj_t *Wifi_screen_wifi_name_now_label;
	lv_obj_t *Wifi_screen_btn_1;
	lv_obj_t *Wifi_screen_btn_1_label;
}lv_ui;


void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_main_screen(lv_ui *ui);
void setup_scr_Wifi_screen(lv_ui *ui);


#endif
