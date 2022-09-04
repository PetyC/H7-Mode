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


void setup_scr_device_screen(lv_ui *ui){

	//Write codes device_screen
	ui->device_screen = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->device_screen, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_device_screen_main_main_default
	static lv_style_t style_device_screen_main_main_default;
	if (style_device_screen_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_device_screen_main_main_default);
	else
		lv_style_init(&style_device_screen_main_main_default);
	lv_style_set_bg_color(&style_device_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_device_screen_main_main_default, 255);
	lv_obj_add_style(ui->device_screen, &style_device_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_about_tileview
	ui->device_screen_about_tileview = lv_tileview_create(ui->device_screen);
	lv_obj_set_pos(ui->device_screen_about_tileview, 0, 0);
	lv_obj_set_size(ui->device_screen_about_tileview, 128, 128);
	lv_obj_set_scrollbar_mode(ui->device_screen_about_tileview, LV_SCROLLBAR_MODE_ON);

	//Write style state: LV_STATE_DEFAULT for style_device_screen_about_tileview_main_main_default
	static lv_style_t style_device_screen_about_tileview_main_main_default;
	if (style_device_screen_about_tileview_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_device_screen_about_tileview_main_main_default);
	else
		lv_style_init(&style_device_screen_about_tileview_main_main_default);
	lv_style_set_radius(&style_device_screen_about_tileview_main_main_default, 0);
	lv_style_set_bg_color(&style_device_screen_about_tileview_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_device_screen_about_tileview_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_device_screen_about_tileview_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_device_screen_about_tileview_main_main_default, 255);
	lv_obj_add_style(ui->device_screen_about_tileview, &style_device_screen_about_tileview_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_device_screen_about_tileview_main_scrollbar_default
	static lv_style_t style_device_screen_about_tileview_main_scrollbar_default;
	if (style_device_screen_about_tileview_main_scrollbar_default.prop_cnt > 1)
		lv_style_reset(&style_device_screen_about_tileview_main_scrollbar_default);
	else
		lv_style_init(&style_device_screen_about_tileview_main_scrollbar_default);
	lv_style_set_radius(&style_device_screen_about_tileview_main_scrollbar_default, 0);
	lv_style_set_bg_color(&style_device_screen_about_tileview_main_scrollbar_default, lv_color_make(0xea, 0xef, 0xf3));
	lv_style_set_bg_opa(&style_device_screen_about_tileview_main_scrollbar_default, 255);
	lv_obj_add_style(ui->device_screen_about_tileview, &style_device_screen_about_tileview_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Update pos for widget device_screen_about_tileview
	lv_obj_update_layout(ui->device_screen_about_tileview);

	//add new tile about_tileview_about_name_0
	ui->about_tileview_about_name_0 = lv_tileview_add_tile(ui->device_screen_about_tileview, 0, 0, LV_DIR_TOP);  //LV_DIR_TOP

	//Write codes device_screen_label_3
	ui->device_screen_label_3 = lv_label_create(ui->about_tileview_about_name_0);
	lv_obj_set_pos(ui->device_screen_label_3, 0, 90);
	lv_obj_set_size(ui->device_screen_label_3, 128, 15);
	lv_obj_set_scrollbar_mode(ui->device_screen_label_3, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->device_screen_label_3, "版本号");
	lv_label_set_long_mode(ui->device_screen_label_3, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_device_screen_label_3_main_main_default
	static lv_style_t style_device_screen_label_3_main_main_default;
	if (style_device_screen_label_3_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_device_screen_label_3_main_main_default);
	else
		lv_style_init(&style_device_screen_label_3_main_main_default);
	lv_style_set_radius(&style_device_screen_label_3_main_main_default, 0);
	lv_style_set_bg_color(&style_device_screen_label_3_main_main_default, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_color(&style_device_screen_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_device_screen_label_3_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_device_screen_label_3_main_main_default, 0);
	lv_style_set_shadow_width(&style_device_screen_label_3_main_main_default, 1);
	lv_style_set_shadow_color(&style_device_screen_label_3_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_device_screen_label_3_main_main_default, 0);
	lv_style_set_shadow_spread(&style_device_screen_label_3_main_main_default, 1);
	lv_style_set_shadow_ofs_x(&style_device_screen_label_3_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_device_screen_label_3_main_main_default, 0);
	lv_style_set_text_color(&style_device_screen_label_3_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_device_screen_label_3_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_device_screen_label_3_main_main_default, 2);
	lv_style_set_text_line_space(&style_device_screen_label_3_main_main_default, 0);
	lv_style_set_text_align(&style_device_screen_label_3_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_device_screen_label_3_main_main_default, 0);
	lv_style_set_pad_right(&style_device_screen_label_3_main_main_default, 0);
	lv_style_set_pad_top(&style_device_screen_label_3_main_main_default, 0);
	lv_style_set_pad_bottom(&style_device_screen_label_3_main_main_default, 0);
	lv_obj_add_style(ui->device_screen_label_3, &style_device_screen_label_3_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_version_label
	ui->device_screen_version_label = lv_label_create(ui->about_tileview_about_name_0);
	lv_obj_set_pos(ui->device_screen_version_label, 7, 110);
	lv_obj_set_size(ui->device_screen_version_label, 114, 15);
	lv_obj_set_scrollbar_mode(ui->device_screen_version_label, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->device_screen_version_label, "0.0.1");
	lv_label_set_long_mode(ui->device_screen_version_label, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_device_screen_version_label_main_main_default
	static lv_style_t style_device_screen_version_label_main_main_default;
	if (style_device_screen_version_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_device_screen_version_label_main_main_default);
	else
		lv_style_init(&style_device_screen_version_label_main_main_default);
	lv_style_set_radius(&style_device_screen_version_label_main_main_default, 0);
	lv_style_set_bg_color(&style_device_screen_version_label_main_main_default, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_color(&style_device_screen_version_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_device_screen_version_label_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_device_screen_version_label_main_main_default, 109);
	lv_style_set_shadow_width(&style_device_screen_version_label_main_main_default, 1);
	lv_style_set_shadow_color(&style_device_screen_version_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_device_screen_version_label_main_main_default, 0);
	lv_style_set_shadow_spread(&style_device_screen_version_label_main_main_default, 1);
	lv_style_set_shadow_ofs_x(&style_device_screen_version_label_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_device_screen_version_label_main_main_default, 0);
	lv_style_set_text_color(&style_device_screen_version_label_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_device_screen_version_label_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_device_screen_version_label_main_main_default, 2);
	lv_style_set_text_line_space(&style_device_screen_version_label_main_main_default, 0);
	lv_style_set_text_align(&style_device_screen_version_label_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_device_screen_version_label_main_main_default, 0);
	lv_style_set_pad_right(&style_device_screen_version_label_main_main_default, 0);
	lv_style_set_pad_top(&style_device_screen_version_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_device_screen_version_label_main_main_default, 0);
	lv_obj_add_style(ui->device_screen_version_label, &style_device_screen_version_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_mcu_label
	ui->device_screen_mcu_label = lv_label_create(ui->about_tileview_about_name_0);
	lv_obj_set_pos(ui->device_screen_mcu_label, 7, 70);
	lv_obj_set_size(ui->device_screen_mcu_label, 110, 15);
	lv_obj_set_scrollbar_mode(ui->device_screen_mcu_label, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->device_screen_mcu_label, "STM32H743VIT6");
	lv_label_set_long_mode(ui->device_screen_mcu_label, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_device_screen_mcu_label_main_main_default
	static lv_style_t style_device_screen_mcu_label_main_main_default;
	if (style_device_screen_mcu_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_device_screen_mcu_label_main_main_default);
	else
		lv_style_init(&style_device_screen_mcu_label_main_main_default);
	lv_style_set_radius(&style_device_screen_mcu_label_main_main_default, 0);
	lv_style_set_bg_color(&style_device_screen_mcu_label_main_main_default, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_color(&style_device_screen_mcu_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_device_screen_mcu_label_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_device_screen_mcu_label_main_main_default, 109);
	lv_style_set_shadow_width(&style_device_screen_mcu_label_main_main_default, 1);
	lv_style_set_shadow_color(&style_device_screen_mcu_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_device_screen_mcu_label_main_main_default, 0);
	lv_style_set_shadow_spread(&style_device_screen_mcu_label_main_main_default, 1);
	lv_style_set_shadow_ofs_x(&style_device_screen_mcu_label_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_device_screen_mcu_label_main_main_default, 0);
	lv_style_set_text_color(&style_device_screen_mcu_label_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_device_screen_mcu_label_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_device_screen_mcu_label_main_main_default, 2);
	lv_style_set_text_line_space(&style_device_screen_mcu_label_main_main_default, 0);
	lv_style_set_text_align(&style_device_screen_mcu_label_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_device_screen_mcu_label_main_main_default, 0);
	lv_style_set_pad_right(&style_device_screen_mcu_label_main_main_default, 0);
	lv_style_set_pad_top(&style_device_screen_mcu_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_device_screen_mcu_label_main_main_default, 0);
	lv_obj_add_style(ui->device_screen_mcu_label, &style_device_screen_mcu_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_label_2
	ui->device_screen_label_2 = lv_label_create(ui->about_tileview_about_name_0);
	lv_obj_set_pos(ui->device_screen_label_2, 0, 50);
	lv_obj_set_size(ui->device_screen_label_2, 128, 15);
	lv_obj_set_scrollbar_mode(ui->device_screen_label_2, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->device_screen_label_2, "主控芯片");
	lv_label_set_long_mode(ui->device_screen_label_2, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_device_screen_label_2_main_main_default
	static lv_style_t style_device_screen_label_2_main_main_default;
	if (style_device_screen_label_2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_device_screen_label_2_main_main_default);
	else
		lv_style_init(&style_device_screen_label_2_main_main_default);
	lv_style_set_radius(&style_device_screen_label_2_main_main_default, 0);
	lv_style_set_bg_color(&style_device_screen_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_device_screen_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_device_screen_label_2_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_device_screen_label_2_main_main_default, 0);
	lv_style_set_text_color(&style_device_screen_label_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_device_screen_label_2_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_device_screen_label_2_main_main_default, 2);
	lv_style_set_text_line_space(&style_device_screen_label_2_main_main_default, 0);
	lv_style_set_text_align(&style_device_screen_label_2_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_device_screen_label_2_main_main_default, 0);
	lv_style_set_pad_right(&style_device_screen_label_2_main_main_default, 0);
	lv_style_set_pad_top(&style_device_screen_label_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_device_screen_label_2_main_main_default, 0);
	lv_obj_add_style(ui->device_screen_label_2, &style_device_screen_label_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_type_label
	ui->device_screen_type_label = lv_label_create(ui->about_tileview_about_name_0);
	lv_obj_set_pos(ui->device_screen_type_label, 7, 30);
	lv_obj_set_size(ui->device_screen_type_label, 110, 15);
	lv_obj_set_scrollbar_mode(ui->device_screen_type_label, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->device_screen_type_label, "H7-Mode");
	lv_label_set_long_mode(ui->device_screen_type_label, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_device_screen_type_label_main_main_default
	static lv_style_t style_device_screen_type_label_main_main_default;
	if (style_device_screen_type_label_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_device_screen_type_label_main_main_default);
	else
		lv_style_init(&style_device_screen_type_label_main_main_default);
	lv_style_set_radius(&style_device_screen_type_label_main_main_default, 0);
	lv_style_set_bg_color(&style_device_screen_type_label_main_main_default, lv_color_make(0xe6, 0xe2, 0xe6));
	lv_style_set_bg_grad_color(&style_device_screen_type_label_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_device_screen_type_label_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_device_screen_type_label_main_main_default, 109);
	lv_style_set_text_color(&style_device_screen_type_label_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_device_screen_type_label_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_device_screen_type_label_main_main_default, 2);
	lv_style_set_text_line_space(&style_device_screen_type_label_main_main_default, 0);
	lv_style_set_text_align(&style_device_screen_type_label_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_device_screen_type_label_main_main_default, 0);
	lv_style_set_pad_right(&style_device_screen_type_label_main_main_default, 0);
	lv_style_set_pad_top(&style_device_screen_type_label_main_main_default, 0);
	lv_style_set_pad_bottom(&style_device_screen_type_label_main_main_default, 0);
	lv_obj_add_style(ui->device_screen_type_label, &style_device_screen_type_label_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes device_screen_label_1
	ui->device_screen_label_1 = lv_label_create(ui->about_tileview_about_name_0);
	lv_obj_set_pos(ui->device_screen_label_1, 0, 10);
	lv_obj_set_size(ui->device_screen_label_1, 128, 15);
	lv_obj_set_scrollbar_mode(ui->device_screen_label_1, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->device_screen_label_1, "设备型号");
	lv_label_set_long_mode(ui->device_screen_label_1, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_device_screen_label_1_main_main_default
	static lv_style_t style_device_screen_label_1_main_main_default;
	if (style_device_screen_label_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_device_screen_label_1_main_main_default);
	else
		lv_style_init(&style_device_screen_label_1_main_main_default);
	lv_style_set_radius(&style_device_screen_label_1_main_main_default, 0);
	lv_style_set_bg_color(&style_device_screen_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_device_screen_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_device_screen_label_1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_device_screen_label_1_main_main_default, 0);
	lv_style_set_text_color(&style_device_screen_label_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_device_screen_label_1_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_letter_space(&style_device_screen_label_1_main_main_default, 2);
	lv_style_set_text_line_space(&style_device_screen_label_1_main_main_default, 0);
	lv_style_set_text_align(&style_device_screen_label_1_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_device_screen_label_1_main_main_default, 0);
	lv_style_set_pad_right(&style_device_screen_label_1_main_main_default, 0);
	lv_style_set_pad_top(&style_device_screen_label_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_device_screen_label_1_main_main_default, 0);
	lv_obj_add_style(ui->device_screen_label_1, &style_device_screen_label_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//add new tile about_tileview_about_name_1
	ui->about_tileview_about_name_1 = lv_tileview_add_tile(ui->device_screen_about_tileview, 0 , 1, LV_DIR_TOP);//LV_DIR_BOTTOM

	//Write codes device_screen_return_btn
	ui->device_screen_return_btn = lv_btn_create(ui->about_tileview_about_name_1);
	lv_obj_set_pos(ui->device_screen_return_btn, 14, 35);
	lv_obj_set_size(ui->device_screen_return_btn, 100, 20);
	lv_obj_set_scrollbar_mode(ui->device_screen_return_btn, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_device_screen_return_btn_main_main_default
	static lv_style_t style_device_screen_return_btn_main_main_default;
	if (style_device_screen_return_btn_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_device_screen_return_btn_main_main_default);
	else
		lv_style_init(&style_device_screen_return_btn_main_main_default);
	lv_style_set_radius(&style_device_screen_return_btn_main_main_default, 5);
	lv_style_set_bg_color(&style_device_screen_return_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_device_screen_return_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_device_screen_return_btn_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_device_screen_return_btn_main_main_default, 112);
	lv_style_set_shadow_width(&style_device_screen_return_btn_main_main_default, 1);
	lv_style_set_shadow_color(&style_device_screen_return_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_device_screen_return_btn_main_main_default, 0);
	lv_style_set_shadow_spread(&style_device_screen_return_btn_main_main_default, 1);
	lv_style_set_shadow_ofs_x(&style_device_screen_return_btn_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_device_screen_return_btn_main_main_default, 0);
	lv_style_set_border_color(&style_device_screen_return_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_device_screen_return_btn_main_main_default, 0);
	lv_style_set_border_opa(&style_device_screen_return_btn_main_main_default, 0);
	lv_style_set_text_color(&style_device_screen_return_btn_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_device_screen_return_btn_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_device_screen_return_btn_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->device_screen_return_btn, &style_device_screen_return_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->device_screen_return_btn_label = lv_label_create(ui->device_screen_return_btn);
	lv_label_set_text(ui->device_screen_return_btn_label, "返回");
	lv_obj_set_style_pad_all(ui->device_screen_return_btn, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->device_screen_return_btn_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes device_screen_check_btn
	ui->device_screen_check_btn = lv_btn_create(ui->about_tileview_about_name_1);
	lv_obj_set_pos(ui->device_screen_check_btn, 14, 10);
	lv_obj_set_size(ui->device_screen_check_btn, 100, 20);
	lv_obj_set_scrollbar_mode(ui->device_screen_check_btn, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_device_screen_check_btn_main_main_default
	static lv_style_t style_device_screen_check_btn_main_main_default;
	if (style_device_screen_check_btn_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_device_screen_check_btn_main_main_default);
	else
		lv_style_init(&style_device_screen_check_btn_main_main_default);
	lv_style_set_radius(&style_device_screen_check_btn_main_main_default, 5);
	lv_style_set_bg_color(&style_device_screen_check_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_device_screen_check_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_device_screen_check_btn_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_device_screen_check_btn_main_main_default, 112);
	lv_style_set_shadow_width(&style_device_screen_check_btn_main_main_default, 1);
	lv_style_set_shadow_color(&style_device_screen_check_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_device_screen_check_btn_main_main_default, 0);
	lv_style_set_shadow_spread(&style_device_screen_check_btn_main_main_default, 1);
	lv_style_set_shadow_ofs_x(&style_device_screen_check_btn_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_device_screen_check_btn_main_main_default, 0);
	lv_style_set_border_color(&style_device_screen_check_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_device_screen_check_btn_main_main_default, 0);
	lv_style_set_border_opa(&style_device_screen_check_btn_main_main_default, 0);
	lv_style_set_text_color(&style_device_screen_check_btn_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_device_screen_check_btn_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_device_screen_check_btn_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->device_screen_check_btn, &style_device_screen_check_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->device_screen_check_btn_label = lv_label_create(ui->device_screen_check_btn);
	lv_label_set_text(ui->device_screen_check_btn_label, "检查更新");
	lv_obj_set_style_pad_all(ui->device_screen_check_btn, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->device_screen_check_btn_label, LV_ALIGN_CENTER, 0, 0);

	//Init events for screen
	events_init_device_screen(ui);
}
