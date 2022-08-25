/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"

void setup_scr_main_screen(lv_ui *ui){

	//Write codes main_screen
	ui->main_screen = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_main_main_default
	static lv_style_t style_main_screen_main_main_default;
	if (style_main_screen_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_main_screen_main_main_default);
	else
		lv_style_init(&style_main_screen_main_main_default);
	lv_style_set_bg_color(&style_main_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_main_screen_main_main_default, 255);
	lv_obj_add_style(ui->main_screen, &style_main_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_screen_Wifi_Set_btn
	ui->main_screen_Wifi_Set_btn = lv_btn_create(ui->main_screen);
	lv_obj_set_pos(ui->main_screen_Wifi_Set_btn, 15, 38);
	lv_obj_set_size(ui->main_screen_Wifi_Set_btn, 100, 50);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_wifi_set_btn_main_main_default
	static lv_style_t style_main_screen_wifi_set_btn_main_main_default;
	if (style_main_screen_wifi_set_btn_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_main_screen_wifi_set_btn_main_main_default);
	else
		lv_style_init(&style_main_screen_wifi_set_btn_main_main_default);
	lv_style_set_radius(&style_main_screen_wifi_set_btn_main_main_default, 5);
	lv_style_set_bg_color(&style_main_screen_wifi_set_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_main_screen_wifi_set_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_main_screen_wifi_set_btn_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_wifi_set_btn_main_main_default, 255);
	lv_style_set_shadow_color(&style_main_screen_wifi_set_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_main_screen_wifi_set_btn_main_main_default, 255);
	lv_style_set_border_color(&style_main_screen_wifi_set_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_main_screen_wifi_set_btn_main_main_default, 0);
	lv_style_set_border_opa(&style_main_screen_wifi_set_btn_main_main_default, 255);
	lv_obj_add_style(ui->main_screen_Wifi_Set_btn, &style_main_screen_wifi_set_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->main_screen_Wifi_Set_btn_label = lv_label_create(ui->main_screen_Wifi_Set_btn);
	lv_label_set_text(ui->main_screen_Wifi_Set_btn_label, "WIFI设置");
	lv_obj_set_style_text_color(ui->main_screen_Wifi_Set_btn_label, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_screen_Wifi_Set_btn_label, &lv_font_simsun_20, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->main_screen_Wifi_Set_btn, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->main_screen_Wifi_Set_btn_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes main_screen_Wifi_State_label
	ui->main_screen_Wifi_State_label = lv_label_create(ui->main_screen);
	lv_obj_set_pos(ui->main_screen_Wifi_State_label, 4, 5);
	lv_obj_set_size(ui->main_screen_Wifi_State_label, 120, 10);
	lv_label_set_text(ui->main_screen_Wifi_State_label, "WIFI:已连接");
	lv_label_set_long_mode(ui->main_screen_Wifi_State_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->main_screen_Wifi_State_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_wifi_state_label_main_main_default
	static lv_style_t style_main_screen_wifi_state_label_main_main_default;
	if (style_main_screen_wifi_state_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_main_screen_wifi_state_label_main_main_default);
	else
		lv_style_init(&style_main_screen_wifi_state_label_main_main_default);
	lv_style_set_radius(&style_main_screen_wifi_state_label_main_main_default, 0);
	lv_style_set_bg_color(&style_main_screen_wifi_state_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_main_screen_wifi_state_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_main_screen_wifi_state_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_wifi_state_label_main_main_default, 0);
	lv_style_set_text_color(&style_main_screen_wifi_state_label_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_main_screen_wifi_state_label_main_main_default, &lv_font_simsun_10);
	lv_style_set_text_letter_space(&style_main_screen_wifi_state_label_main_main_default, 2);
	lv_style_set_pad_left(&style_main_screen_wifi_state_label_main_main_default, 0);
	lv_style_set_pad_right(&style_main_screen_wifi_state_label_main_main_default, 0);
	lv_style_set_pad_top(&style_main_screen_wifi_state_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_main_screen_wifi_state_label_main_main_default, 0);
	lv_obj_add_style(ui->main_screen_Wifi_State_label, &style_main_screen_wifi_state_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Init events for screen
	events_init_main_screen(ui);
}
