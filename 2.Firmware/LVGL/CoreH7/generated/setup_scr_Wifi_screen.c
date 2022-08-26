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


void setup_scr_Wifi_screen(lv_ui *ui){

	//Write codes Wifi_screen
	ui->Wifi_screen = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_wifi_screen_main_main_default
	static lv_style_t style_wifi_screen_main_main_default;
	if (style_wifi_screen_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_main_main_default);
	else
		lv_style_init(&style_wifi_screen_main_main_default);
	lv_style_set_bg_color(&style_wifi_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_wifi_screen_main_main_default, 255);
	lv_obj_add_style(ui->Wifi_screen, &style_wifi_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Wifi_screen_APU_btn
	ui->Wifi_screen_APU_btn = lv_btn_create(ui->Wifi_screen);
	lv_obj_set_pos(ui->Wifi_screen_APU_btn, 4, 70);
	lv_obj_set_size(ui->Wifi_screen_APU_btn, 120, 10);

	//Write style state: LV_STATE_DEFAULT for style_wifi_screen_apu_btn_main_main_default
	static lv_style_t style_wifi_screen_apu_btn_main_main_default;
	if (style_wifi_screen_apu_btn_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_apu_btn_main_main_default);
	else
		lv_style_init(&style_wifi_screen_apu_btn_main_main_default);
	lv_style_set_radius(&style_wifi_screen_apu_btn_main_main_default, 5);
	lv_style_set_bg_color(&style_wifi_screen_apu_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_wifi_screen_apu_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_apu_btn_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_wifi_screen_apu_btn_main_main_default, 108);
	lv_style_set_shadow_color(&style_wifi_screen_apu_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_wifi_screen_apu_btn_main_main_default, 0);
	lv_style_set_border_color(&style_wifi_screen_apu_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_wifi_screen_apu_btn_main_main_default, 0);
	lv_style_set_border_opa(&style_wifi_screen_apu_btn_main_main_default, 0);
	lv_obj_add_style(ui->Wifi_screen_APU_btn, &style_wifi_screen_apu_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->Wifi_screen_APU_btn_label = lv_label_create(ui->Wifi_screen_APU_btn);
	lv_label_set_text(ui->Wifi_screen_APU_btn_label, "启动APU配网");
	lv_obj_set_style_text_color(ui->Wifi_screen_APU_btn_label, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->Wifi_screen_APU_btn_label, &lv_font_simsun_8, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->Wifi_screen_APU_btn, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->Wifi_screen_APU_btn_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes Wifi_screen_label_1
	ui->Wifi_screen_label_1 = lv_label_create(ui->Wifi_screen);
	lv_obj_set_pos(ui->Wifi_screen_label_1, 0, 3);
	lv_obj_set_size(ui->Wifi_screen_label_1, 128, 10);
	lv_label_set_text(ui->Wifi_screen_label_1, "WIFI");
	lv_label_set_long_mode(ui->Wifi_screen_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->Wifi_screen_label_1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_wifi_screen_label_1_main_main_default
	static lv_style_t style_wifi_screen_label_1_main_main_default;
	if (style_wifi_screen_label_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_label_1_main_main_default);
	else
		lv_style_init(&style_wifi_screen_label_1_main_main_default);
	lv_style_set_radius(&style_wifi_screen_label_1_main_main_default, 0);
	lv_style_set_bg_color(&style_wifi_screen_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_wifi_screen_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_label_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_wifi_screen_label_1_main_main_default, 0);
	lv_style_set_text_color(&style_wifi_screen_label_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_wifi_screen_label_1_main_main_default, &lv_font_simsun_8);
	lv_style_set_text_letter_space(&style_wifi_screen_label_1_main_main_default, 2);
	lv_style_set_pad_left(&style_wifi_screen_label_1_main_main_default, 0);
	lv_style_set_pad_right(&style_wifi_screen_label_1_main_main_default, 0);
	lv_style_set_pad_top(&style_wifi_screen_label_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_wifi_screen_label_1_main_main_default, 0);
	lv_obj_add_style(ui->Wifi_screen_label_1, &style_wifi_screen_label_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Wifi_screen_Wifi_sw
	ui->Wifi_screen_Wifi_sw = lv_switch_create(ui->Wifi_screen);
	lv_obj_set_pos(ui->Wifi_screen_Wifi_sw, 44, 20);
	lv_obj_set_size(ui->Wifi_screen_Wifi_sw, 40, 15);

	//Write style state: LV_STATE_DEFAULT for style_wifi_screen_wifi_sw_main_main_default
	static lv_style_t style_wifi_screen_wifi_sw_main_main_default;
	if (style_wifi_screen_wifi_sw_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_wifi_sw_main_main_default);
	else
		lv_style_init(&style_wifi_screen_wifi_sw_main_main_default);
	lv_style_set_radius(&style_wifi_screen_wifi_sw_main_main_default, 100);
	lv_style_set_bg_color(&style_wifi_screen_wifi_sw_main_main_default, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_color(&style_wifi_screen_wifi_sw_main_main_default, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_wifi_sw_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_wifi_screen_wifi_sw_main_main_default, 255);
	lv_obj_add_style(ui->Wifi_screen_Wifi_sw, &style_wifi_screen_wifi_sw_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_CHECKED for style_wifi_screen_wifi_sw_main_indicator_checked
	static lv_style_t style_wifi_screen_wifi_sw_main_indicator_checked;
	if (style_wifi_screen_wifi_sw_main_indicator_checked.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_wifi_sw_main_indicator_checked);
	else
		lv_style_init(&style_wifi_screen_wifi_sw_main_indicator_checked);
	lv_style_set_radius(&style_wifi_screen_wifi_sw_main_indicator_checked, 100);
	lv_style_set_bg_color(&style_wifi_screen_wifi_sw_main_indicator_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_wifi_screen_wifi_sw_main_indicator_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_wifi_sw_main_indicator_checked, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_wifi_screen_wifi_sw_main_indicator_checked, 255);
	lv_obj_add_style(ui->Wifi_screen_Wifi_sw, &style_wifi_screen_wifi_sw_main_indicator_checked, LV_PART_INDICATOR|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for style_wifi_screen_wifi_sw_main_knob_default
	static lv_style_t style_wifi_screen_wifi_sw_main_knob_default;
	if (style_wifi_screen_wifi_sw_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_wifi_sw_main_knob_default);
	else
		lv_style_init(&style_wifi_screen_wifi_sw_main_knob_default);
	lv_style_set_radius(&style_wifi_screen_wifi_sw_main_knob_default, 100);
	lv_style_set_bg_color(&style_wifi_screen_wifi_sw_main_knob_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_wifi_screen_wifi_sw_main_knob_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_wifi_screen_wifi_sw_main_knob_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_wifi_screen_wifi_sw_main_knob_default, 255);
	lv_obj_add_style(ui->Wifi_screen_Wifi_sw, &style_wifi_screen_wifi_sw_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes Wifi_screen_label_2
	ui->Wifi_screen_label_2 = lv_label_create(ui->Wifi_screen);
	lv_obj_set_pos(ui->Wifi_screen_label_2, 0, 40);
	lv_obj_set_size(ui->Wifi_screen_label_2, 128, 8);
	lv_label_set_text(ui->Wifi_screen_label_2, "已连接WIFI:");
	lv_label_set_long_mode(ui->Wifi_screen_label_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->Wifi_screen_label_2, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_wifi_screen_label_2_main_main_default
	static lv_style_t style_wifi_screen_label_2_main_main_default;
	if (style_wifi_screen_label_2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_label_2_main_main_default);
	else
		lv_style_init(&style_wifi_screen_label_2_main_main_default);
	lv_style_set_radius(&style_wifi_screen_label_2_main_main_default, 50);
	lv_style_set_bg_color(&style_wifi_screen_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_wifi_screen_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_label_2_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_wifi_screen_label_2_main_main_default, 0);
	lv_style_set_text_color(&style_wifi_screen_label_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_wifi_screen_label_2_main_main_default, &lv_font_simsun_8);
	lv_style_set_text_letter_space(&style_wifi_screen_label_2_main_main_default, 2);
	lv_style_set_pad_left(&style_wifi_screen_label_2_main_main_default, 0);
	lv_style_set_pad_right(&style_wifi_screen_label_2_main_main_default, 0);
	lv_style_set_pad_top(&style_wifi_screen_label_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_wifi_screen_label_2_main_main_default, 0);
	lv_obj_add_style(ui->Wifi_screen_label_2, &style_wifi_screen_label_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Wifi_screen_wifi_name_now_label
	ui->Wifi_screen_wifi_name_now_label = lv_label_create(ui->Wifi_screen);
	lv_obj_set_pos(ui->Wifi_screen_wifi_name_now_label, 4, 55);
	lv_obj_set_size(ui->Wifi_screen_wifi_name_now_label, 120, 10);
	lv_label_set_text(ui->Wifi_screen_wifi_name_now_label, "Moujiti");
	lv_label_set_long_mode(ui->Wifi_screen_wifi_name_now_label, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->Wifi_screen_wifi_name_now_label, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_wifi_screen_wifi_name_now_label_main_main_default
	static lv_style_t style_wifi_screen_wifi_name_now_label_main_main_default;
	if (style_wifi_screen_wifi_name_now_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_wifi_name_now_label_main_main_default);
	else
		lv_style_init(&style_wifi_screen_wifi_name_now_label_main_main_default);
	lv_style_set_radius(&style_wifi_screen_wifi_name_now_label_main_main_default, 50);
	lv_style_set_bg_color(&style_wifi_screen_wifi_name_now_label_main_main_default, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_color(&style_wifi_screen_wifi_name_now_label_main_main_default, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_wifi_name_now_label_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_wifi_screen_wifi_name_now_label_main_main_default, 108);
	lv_style_set_text_color(&style_wifi_screen_wifi_name_now_label_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_wifi_screen_wifi_name_now_label_main_main_default, &lv_font_simsun_8);
	lv_style_set_text_letter_space(&style_wifi_screen_wifi_name_now_label_main_main_default, 1);
	lv_style_set_pad_left(&style_wifi_screen_wifi_name_now_label_main_main_default, 0);
	lv_style_set_pad_right(&style_wifi_screen_wifi_name_now_label_main_main_default, 0);
	lv_style_set_pad_top(&style_wifi_screen_wifi_name_now_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_wifi_screen_wifi_name_now_label_main_main_default, 0);
	lv_obj_add_style(ui->Wifi_screen_wifi_name_now_label, &style_wifi_screen_wifi_name_now_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DISABLED for style_wifi_screen_wifi_name_now_label_main_main_disabled
	static lv_style_t style_wifi_screen_wifi_name_now_label_main_main_disabled;
	if (style_wifi_screen_wifi_name_now_label_main_main_disabled.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_wifi_name_now_label_main_main_disabled);
	else
		lv_style_init(&style_wifi_screen_wifi_name_now_label_main_main_disabled);
	lv_style_set_radius(&style_wifi_screen_wifi_name_now_label_main_main_disabled, 5);
	lv_style_set_bg_color(&style_wifi_screen_wifi_name_now_label_main_main_disabled, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_color(&style_wifi_screen_wifi_name_now_label_main_main_disabled, lv_color_make(0xf5, 0xf5, 0xf5));
	lv_style_set_bg_grad_dir(&style_wifi_screen_wifi_name_now_label_main_main_disabled, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_wifi_screen_wifi_name_now_label_main_main_disabled, 255);
	lv_style_set_text_color(&style_wifi_screen_wifi_name_now_label_main_main_disabled, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_wifi_screen_wifi_name_now_label_main_main_disabled, &lv_font_simsun_8);
	lv_style_set_text_letter_space(&style_wifi_screen_wifi_name_now_label_main_main_disabled, 2);
	lv_style_set_pad_left(&style_wifi_screen_wifi_name_now_label_main_main_disabled, 0);
	lv_style_set_pad_right(&style_wifi_screen_wifi_name_now_label_main_main_disabled, 0);
	lv_style_set_pad_top(&style_wifi_screen_wifi_name_now_label_main_main_disabled, 0);
	lv_style_set_pad_bottom(&style_wifi_screen_wifi_name_now_label_main_main_disabled, 0);
	lv_obj_add_style(ui->Wifi_screen_wifi_name_now_label, &style_wifi_screen_wifi_name_now_label_main_main_disabled, LV_PART_MAIN|LV_STATE_DISABLED);

	//Write codes Wifi_screen_btn_1
	ui->Wifi_screen_btn_1 = lv_btn_create(ui->Wifi_screen);
	lv_obj_set_pos(ui->Wifi_screen_btn_1, 4, 85);
	lv_obj_set_size(ui->Wifi_screen_btn_1, 120, 10);

	//Write style state: LV_STATE_DEFAULT for style_wifi_screen_btn_1_main_main_default
	static lv_style_t style_wifi_screen_btn_1_main_main_default;
	if (style_wifi_screen_btn_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_btn_1_main_main_default);
	else
		lv_style_init(&style_wifi_screen_btn_1_main_main_default);
	lv_style_set_radius(&style_wifi_screen_btn_1_main_main_default, 5);
	lv_style_set_bg_color(&style_wifi_screen_btn_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_wifi_screen_btn_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_btn_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_wifi_screen_btn_1_main_main_default, 108);
	lv_style_set_shadow_color(&style_wifi_screen_btn_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_wifi_screen_btn_1_main_main_default, 0);
	lv_style_set_border_color(&style_wifi_screen_btn_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_wifi_screen_btn_1_main_main_default, 0);
	lv_style_set_border_opa(&style_wifi_screen_btn_1_main_main_default, 109);
	lv_obj_add_style(ui->Wifi_screen_btn_1, &style_wifi_screen_btn_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->Wifi_screen_btn_1_label = lv_label_create(ui->Wifi_screen_btn_1);
	lv_label_set_text(ui->Wifi_screen_btn_1_label, "返回");
	lv_obj_set_style_text_color(ui->Wifi_screen_btn_1_label, lv_color_make(0x00, 0x00, 0x00), LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->Wifi_screen_btn_1_label, &lv_font_simsun_8, LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->Wifi_screen_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->Wifi_screen_btn_1_label, LV_ALIGN_CENTER, 0, 0);

	//Init events for screen
	events_init_Wifi_screen(ui);
}