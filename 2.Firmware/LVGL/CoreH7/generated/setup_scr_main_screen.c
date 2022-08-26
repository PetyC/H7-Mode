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

	//Write codes main_screen_tileview
	ui->main_screen_tileview = lv_tileview_create(ui->main_screen);
	lv_obj_set_pos(ui->main_screen_tileview, 0, 0);
	lv_obj_set_size(ui->main_screen_tileview, 128, 128);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_tileview_main_main_default
	static lv_style_t style_main_screen_tileview_main_main_default;
	if (style_main_screen_tileview_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_main_screen_tileview_main_main_default);
	else
		lv_style_init(&style_main_screen_tileview_main_main_default);
	lv_style_set_radius(&style_main_screen_tileview_main_main_default, 0);
	lv_style_set_bg_color(&style_main_screen_tileview_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_main_screen_tileview_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_main_screen_tileview_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_tileview_main_main_default, 255);
	lv_obj_add_style(ui->main_screen_tileview, &style_main_screen_tileview_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_tileview_main_scrollbar_default
	static lv_style_t style_main_screen_tileview_main_scrollbar_default;
	if (style_main_screen_tileview_main_scrollbar_default.prop_cnt > 1)
		lv_style_reset(&style_main_screen_tileview_main_scrollbar_default);
	else
		lv_style_init(&style_main_screen_tileview_main_scrollbar_default);
	lv_style_set_radius(&style_main_screen_tileview_main_scrollbar_default, 0);
	lv_style_set_bg_color(&style_main_screen_tileview_main_scrollbar_default, lv_color_make(0xea, 0xef, 0xf3));
	lv_style_set_bg_opa(&style_main_screen_tileview_main_scrollbar_default, 255);
	lv_obj_add_style(ui->main_screen_tileview, &style_main_screen_tileview_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//add new tile main_screen_tileview_tileview
	ui->main_screen_tileview_tileview = lv_tileview_add_tile(ui->main_screen_tileview, 0, 0, LV_DIR_RIGHT);

	//Write codes main_screen_Wifi_Set_btn
	ui->main_screen_Wifi_Set_btn = lv_btn_create(ui->main_screen_tileview_tileview);
	lv_obj_set_pos(ui->main_screen_Wifi_Set_btn, 34, 20);
	lv_obj_set_size(ui->main_screen_Wifi_Set_btn, 60, 20);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_wifi_set_btn_main_main_default
	static lv_style_t style_main_screen_wifi_set_btn_main_main_default;
	if (style_main_screen_wifi_set_btn_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_main_screen_wifi_set_btn_main_main_default);
	else
		lv_style_init(&style_main_screen_wifi_set_btn_main_main_default);
	lv_style_set_radius(&style_main_screen_wifi_set_btn_main_main_default, 50);
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
	lv_obj_set_style_text_font(ui->main_screen_Wifi_Set_btn_label, &lv_font_simsun_12, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->main_screen_Wifi_Set_btn, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->main_screen_Wifi_Set_btn_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes main_screen_Demo_btn
	ui->main_screen_Demo_btn = lv_btn_create(ui->main_screen_tileview_tileview);
	lv_obj_set_pos(ui->main_screen_Demo_btn, 34, 70);
	lv_obj_set_size(ui->main_screen_Demo_btn, 60, 20);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_demo_btn_main_main_default
	static lv_style_t style_main_screen_demo_btn_main_main_default;
	if (style_main_screen_demo_btn_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_main_screen_demo_btn_main_main_default);
	else
		lv_style_init(&style_main_screen_demo_btn_main_main_default);
	lv_style_set_radius(&style_main_screen_demo_btn_main_main_default, 50);
	lv_style_set_bg_color(&style_main_screen_demo_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_main_screen_demo_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_main_screen_demo_btn_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_main_screen_demo_btn_main_main_default, 255);
	lv_style_set_shadow_color(&style_main_screen_demo_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_main_screen_demo_btn_main_main_default, 255);
	lv_style_set_border_color(&style_main_screen_demo_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_main_screen_demo_btn_main_main_default, 0);
	lv_style_set_border_opa(&style_main_screen_demo_btn_main_main_default, 255);
	lv_obj_add_style(ui->main_screen_Demo_btn, &style_main_screen_demo_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->main_screen_Demo_btn_label = lv_label_create(ui->main_screen_Demo_btn);
	lv_label_set_text(ui->main_screen_Demo_btn_label, "Demo");
	lv_obj_set_style_text_color(ui->main_screen_Demo_btn_label, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_screen_Demo_btn_label, &lv_font_simsun_12, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->main_screen_Demo_btn, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->main_screen_Demo_btn_label, LV_ALIGN_CENTER, 0, 0);

	//Init events for screen
	events_init_main_screen(ui);
}