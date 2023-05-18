/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_Wifi_screen(lv_ui *ui){

	//Write codes Wifi_screen
	ui->Wifi_screen = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->Wifi_screen, LV_SCROLLBAR_MODE_OFF);

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
	lv_obj_set_pos(ui->Wifi_screen_APU_btn, 14, 65);
	lv_obj_set_size(ui->Wifi_screen_APU_btn, 100, 20);
	lv_obj_set_scrollbar_mode(ui->Wifi_screen_APU_btn, LV_SCROLLBAR_MODE_OFF);

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
	lv_style_set_shadow_width(&style_wifi_screen_apu_btn_main_main_default, 1);
	lv_style_set_shadow_color(&style_wifi_screen_apu_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_wifi_screen_apu_btn_main_main_default, 0);
	lv_style_set_shadow_spread(&style_wifi_screen_apu_btn_main_main_default, 1);
	lv_style_set_shadow_ofs_x(&style_wifi_screen_apu_btn_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_wifi_screen_apu_btn_main_main_default, 0);
	lv_style_set_border_color(&style_wifi_screen_apu_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_wifi_screen_apu_btn_main_main_default, 0);
	lv_style_set_border_opa(&style_wifi_screen_apu_btn_main_main_default, 0);
	lv_style_set_text_color(&style_wifi_screen_apu_btn_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_wifi_screen_apu_btn_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_wifi_screen_apu_btn_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->Wifi_screen_APU_btn, &style_wifi_screen_apu_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->Wifi_screen_APU_btn_label = lv_label_create(ui->Wifi_screen_APU_btn);
	lv_label_set_text(ui->Wifi_screen_APU_btn_label, "启动APU配网");
	lv_obj_set_style_pad_all(ui->Wifi_screen_APU_btn, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->Wifi_screen_APU_btn_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes Wifi_screen_label_2
	ui->Wifi_screen_label_2 = lv_label_create(ui->Wifi_screen);
	lv_obj_set_pos(ui->Wifi_screen_label_2, 0, 25);
	lv_obj_set_size(ui->Wifi_screen_label_2, 128, 15);
	lv_obj_set_scrollbar_mode(ui->Wifi_screen_label_2, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->Wifi_screen_label_2, "连接WIFI:");
	lv_label_set_long_mode(ui->Wifi_screen_label_2, LV_LABEL_LONG_WRAP);

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
	lv_style_set_text_font(&style_wifi_screen_label_2_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_wifi_screen_label_2_main_main_default, 2);
	lv_style_set_text_line_space(&style_wifi_screen_label_2_main_main_default, 0);
	lv_style_set_text_align(&style_wifi_screen_label_2_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_wifi_screen_label_2_main_main_default, 0);
	lv_style_set_pad_right(&style_wifi_screen_label_2_main_main_default, 0);
	lv_style_set_pad_top(&style_wifi_screen_label_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_wifi_screen_label_2_main_main_default, 0);
	lv_obj_add_style(ui->Wifi_screen_label_2, &style_wifi_screen_label_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Wifi_screen_wifi_name_now_label
	ui->Wifi_screen_wifi_name_now_label = lv_label_create(ui->Wifi_screen);
	lv_obj_set_pos(ui->Wifi_screen_wifi_name_now_label, 4, 45);
	lv_obj_set_size(ui->Wifi_screen_wifi_name_now_label, 120, 15);
	lv_obj_set_scrollbar_mode(ui->Wifi_screen_wifi_name_now_label, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->Wifi_screen_wifi_name_now_label, "Moujiti");
	lv_label_set_long_mode(ui->Wifi_screen_wifi_name_now_label, LV_LABEL_LONG_WRAP);

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
	lv_style_set_bg_opa(&style_wifi_screen_wifi_name_now_label_main_main_default, 109);
	lv_style_set_text_color(&style_wifi_screen_wifi_name_now_label_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_wifi_screen_wifi_name_now_label_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_wifi_screen_wifi_name_now_label_main_main_default, 1);
	lv_style_set_text_line_space(&style_wifi_screen_wifi_name_now_label_main_main_default, 3);
	lv_style_set_text_align(&style_wifi_screen_wifi_name_now_label_main_main_default, LV_TEXT_ALIGN_CENTER);
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
	lv_style_set_text_line_space(&style_wifi_screen_wifi_name_now_label_main_main_disabled, 0);
	lv_style_set_text_align(&style_wifi_screen_wifi_name_now_label_main_main_disabled, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_wifi_screen_wifi_name_now_label_main_main_disabled, 0);
	lv_style_set_pad_right(&style_wifi_screen_wifi_name_now_label_main_main_disabled, 0);
	lv_style_set_pad_top(&style_wifi_screen_wifi_name_now_label_main_main_disabled, 0);
	lv_style_set_pad_bottom(&style_wifi_screen_wifi_name_now_label_main_main_disabled, 0);
	lv_obj_add_style(ui->Wifi_screen_wifi_name_now_label, &style_wifi_screen_wifi_name_now_label_main_main_disabled, LV_PART_MAIN|LV_STATE_DISABLED);

	//Write codes Wifi_screen_return_btn
	ui->Wifi_screen_return_btn = lv_btn_create(ui->Wifi_screen);
	lv_obj_set_pos(ui->Wifi_screen_return_btn, 14, 90);
	lv_obj_set_size(ui->Wifi_screen_return_btn, 100, 20);
	lv_obj_set_scrollbar_mode(ui->Wifi_screen_return_btn, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_wifi_screen_return_btn_main_main_default
	static lv_style_t style_wifi_screen_return_btn_main_main_default;
	if (style_wifi_screen_return_btn_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_return_btn_main_main_default);
	else
		lv_style_init(&style_wifi_screen_return_btn_main_main_default);
	lv_style_set_radius(&style_wifi_screen_return_btn_main_main_default, 5);
	lv_style_set_bg_color(&style_wifi_screen_return_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_wifi_screen_return_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_return_btn_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_wifi_screen_return_btn_main_main_default, 108);
	lv_style_set_shadow_width(&style_wifi_screen_return_btn_main_main_default, 1);
	lv_style_set_shadow_color(&style_wifi_screen_return_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_wifi_screen_return_btn_main_main_default, 0);
	lv_style_set_shadow_spread(&style_wifi_screen_return_btn_main_main_default, 1);
	lv_style_set_shadow_ofs_x(&style_wifi_screen_return_btn_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_wifi_screen_return_btn_main_main_default, 0);
	lv_style_set_border_color(&style_wifi_screen_return_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_wifi_screen_return_btn_main_main_default, 0);
	lv_style_set_border_opa(&style_wifi_screen_return_btn_main_main_default, 0);
	lv_style_set_text_color(&style_wifi_screen_return_btn_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_wifi_screen_return_btn_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_wifi_screen_return_btn_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->Wifi_screen_return_btn, &style_wifi_screen_return_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->Wifi_screen_return_btn_label = lv_label_create(ui->Wifi_screen_return_btn);
	lv_label_set_text(ui->Wifi_screen_return_btn_label, "返回");
	lv_obj_set_style_pad_all(ui->Wifi_screen_return_btn, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->Wifi_screen_return_btn_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes Wifi_screen_cont
	ui->Wifi_screen_cont = lv_obj_create(ui->Wifi_screen);
	lv_obj_set_pos(ui->Wifi_screen_cont, 0, 0);
	lv_obj_set_size(ui->Wifi_screen_cont, 128, 20);
	lv_obj_set_scrollbar_mode(ui->Wifi_screen_cont, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_wifi_screen_cont_main_main_default
	static lv_style_t style_wifi_screen_cont_main_main_default;
	if (style_wifi_screen_cont_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_cont_main_main_default);
	else
		lv_style_init(&style_wifi_screen_cont_main_main_default);
	lv_style_set_radius(&style_wifi_screen_cont_main_main_default, 0);
	lv_style_set_bg_color(&style_wifi_screen_cont_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_wifi_screen_cont_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_cont_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_wifi_screen_cont_main_main_default, 0);
	lv_style_set_border_color(&style_wifi_screen_cont_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_wifi_screen_cont_main_main_default, 0);
	lv_style_set_border_opa(&style_wifi_screen_cont_main_main_default, 0);
	lv_style_set_pad_left(&style_wifi_screen_cont_main_main_default, 0);
	lv_style_set_pad_right(&style_wifi_screen_cont_main_main_default, 0);
	lv_style_set_pad_top(&style_wifi_screen_cont_main_main_default, 0);
	lv_style_set_pad_bottom(&style_wifi_screen_cont_main_main_default, 0);
	lv_obj_add_style(ui->Wifi_screen_cont, &style_wifi_screen_cont_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes Wifi_screen_wifi_en_sw
	ui->Wifi_screen_wifi_en_sw = lv_switch_create(ui->Wifi_screen_cont);
	lv_obj_set_pos(ui->Wifi_screen_wifi_en_sw, 65, 5);
	lv_obj_set_size(ui->Wifi_screen_wifi_en_sw, 40, 12);
	lv_obj_set_scrollbar_mode(ui->Wifi_screen_wifi_en_sw, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_wifi_screen_wifi_en_sw_main_main_default
	static lv_style_t style_wifi_screen_wifi_en_sw_main_main_default;
	if (style_wifi_screen_wifi_en_sw_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_wifi_en_sw_main_main_default);
	else
		lv_style_init(&style_wifi_screen_wifi_en_sw_main_main_default);
	lv_style_set_radius(&style_wifi_screen_wifi_en_sw_main_main_default, 100);
	lv_style_set_bg_color(&style_wifi_screen_wifi_en_sw_main_main_default, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_color(&style_wifi_screen_wifi_en_sw_main_main_default, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_wifi_en_sw_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_wifi_screen_wifi_en_sw_main_main_default, 255);
	lv_style_set_border_color(&style_wifi_screen_wifi_en_sw_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_wifi_screen_wifi_en_sw_main_main_default, 0);
	lv_style_set_border_opa(&style_wifi_screen_wifi_en_sw_main_main_default, 0);
	lv_obj_add_style(ui->Wifi_screen_wifi_en_sw, &style_wifi_screen_wifi_en_sw_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_FOCUSED for style_wifi_screen_wifi_en_sw_main_main_focused
	static lv_style_t style_wifi_screen_wifi_en_sw_main_main_focused;
	if (style_wifi_screen_wifi_en_sw_main_main_focused.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_wifi_en_sw_main_main_focused);
	else
		lv_style_init(&style_wifi_screen_wifi_en_sw_main_main_focused);
	lv_style_set_radius(&style_wifi_screen_wifi_en_sw_main_main_focused, 100);
	lv_style_set_bg_color(&style_wifi_screen_wifi_en_sw_main_main_focused, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_color(&style_wifi_screen_wifi_en_sw_main_main_focused, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_wifi_en_sw_main_main_focused, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_wifi_screen_wifi_en_sw_main_main_focused, 255);
	lv_style_set_border_color(&style_wifi_screen_wifi_en_sw_main_main_focused, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_wifi_screen_wifi_en_sw_main_main_focused, 0);
	lv_style_set_border_opa(&style_wifi_screen_wifi_en_sw_main_main_focused, 255);
	lv_obj_add_style(ui->Wifi_screen_wifi_en_sw, &style_wifi_screen_wifi_en_sw_main_main_focused, LV_PART_MAIN|LV_STATE_FOCUSED);

	//Write style state: LV_STATE_DISABLED for style_wifi_screen_wifi_en_sw_main_main_disabled
	static lv_style_t style_wifi_screen_wifi_en_sw_main_main_disabled;
	if (style_wifi_screen_wifi_en_sw_main_main_disabled.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_wifi_en_sw_main_main_disabled);
	else
		lv_style_init(&style_wifi_screen_wifi_en_sw_main_main_disabled);
	lv_style_set_radius(&style_wifi_screen_wifi_en_sw_main_main_disabled, 100);
	lv_style_set_bg_color(&style_wifi_screen_wifi_en_sw_main_main_disabled, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_color(&style_wifi_screen_wifi_en_sw_main_main_disabled, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_wifi_en_sw_main_main_disabled, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_wifi_screen_wifi_en_sw_main_main_disabled, 255);
	lv_style_set_border_color(&style_wifi_screen_wifi_en_sw_main_main_disabled, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_wifi_screen_wifi_en_sw_main_main_disabled, 0);
	lv_style_set_border_opa(&style_wifi_screen_wifi_en_sw_main_main_disabled, 255);
	lv_obj_add_style(ui->Wifi_screen_wifi_en_sw, &style_wifi_screen_wifi_en_sw_main_main_disabled, LV_PART_MAIN|LV_STATE_DISABLED);

	//Write style state: LV_STATE_CHECKED for style_wifi_screen_wifi_en_sw_main_indicator_checked
	static lv_style_t style_wifi_screen_wifi_en_sw_main_indicator_checked;
	if (style_wifi_screen_wifi_en_sw_main_indicator_checked.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_wifi_en_sw_main_indicator_checked);
	else
		lv_style_init(&style_wifi_screen_wifi_en_sw_main_indicator_checked);
	lv_style_set_bg_color(&style_wifi_screen_wifi_en_sw_main_indicator_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_wifi_screen_wifi_en_sw_main_indicator_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_wifi_en_sw_main_indicator_checked, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_wifi_screen_wifi_en_sw_main_indicator_checked, 255);
	lv_style_set_border_color(&style_wifi_screen_wifi_en_sw_main_indicator_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_wifi_screen_wifi_en_sw_main_indicator_checked, 0);
	lv_style_set_border_opa(&style_wifi_screen_wifi_en_sw_main_indicator_checked, 255);
	lv_obj_add_style(ui->Wifi_screen_wifi_en_sw, &style_wifi_screen_wifi_en_sw_main_indicator_checked, LV_PART_INDICATOR|LV_STATE_CHECKED);

	//Write style state: LV_STATE_DEFAULT for style_wifi_screen_wifi_en_sw_main_knob_default
	static lv_style_t style_wifi_screen_wifi_en_sw_main_knob_default;
	if (style_wifi_screen_wifi_en_sw_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_wifi_en_sw_main_knob_default);
	else
		lv_style_init(&style_wifi_screen_wifi_en_sw_main_knob_default);
	lv_style_set_radius(&style_wifi_screen_wifi_en_sw_main_knob_default, 100);
	lv_style_set_bg_color(&style_wifi_screen_wifi_en_sw_main_knob_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_wifi_screen_wifi_en_sw_main_knob_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_wifi_screen_wifi_en_sw_main_knob_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_wifi_screen_wifi_en_sw_main_knob_default, 255);
	lv_style_set_border_color(&style_wifi_screen_wifi_en_sw_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_wifi_screen_wifi_en_sw_main_knob_default, 0);
	lv_style_set_border_opa(&style_wifi_screen_wifi_en_sw_main_knob_default, 255);
	lv_obj_add_style(ui->Wifi_screen_wifi_en_sw, &style_wifi_screen_wifi_en_sw_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Write codes Wifi_screen_label_3
	ui->Wifi_screen_label_3 = lv_label_create(ui->Wifi_screen_cont);
	lv_obj_set_pos(ui->Wifi_screen_label_3, 20, 5);
	lv_obj_set_size(ui->Wifi_screen_label_3, 50, 15);
	lv_obj_set_scrollbar_mode(ui->Wifi_screen_label_3, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->Wifi_screen_label_3, "WIFI");
	lv_label_set_long_mode(ui->Wifi_screen_label_3, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_wifi_screen_label_3_main_main_default
	static lv_style_t style_wifi_screen_label_3_main_main_default;
	if (style_wifi_screen_label_3_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_wifi_screen_label_3_main_main_default);
	else
		lv_style_init(&style_wifi_screen_label_3_main_main_default);
	lv_style_set_radius(&style_wifi_screen_label_3_main_main_default, 0);
	lv_style_set_bg_color(&style_wifi_screen_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_wifi_screen_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_wifi_screen_label_3_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_wifi_screen_label_3_main_main_default, 0);
	lv_style_set_text_color(&style_wifi_screen_label_3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_wifi_screen_label_3_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_wifi_screen_label_3_main_main_default, 2);
	lv_style_set_text_line_space(&style_wifi_screen_label_3_main_main_default, 0);
	lv_style_set_text_align(&style_wifi_screen_label_3_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_wifi_screen_label_3_main_main_default, 0);
	lv_style_set_pad_right(&style_wifi_screen_label_3_main_main_default, 0);
	lv_style_set_pad_top(&style_wifi_screen_label_3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_wifi_screen_label_3_main_main_default, 0);
	lv_obj_add_style(ui->Wifi_screen_label_3, &style_wifi_screen_label_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Init events for screen
	events_init_Wifi_screen(ui);
}
