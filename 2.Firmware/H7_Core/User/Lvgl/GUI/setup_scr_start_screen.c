/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_start_screen(lv_ui *ui){

	//Write codes start_screen
	ui->start_screen = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->start_screen, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_start_screen_main_main_default
	static lv_style_t style_start_screen_main_main_default;
	if (style_start_screen_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_start_screen_main_main_default);
	else
		lv_style_init(&style_start_screen_main_main_default);
	lv_style_set_bg_color(&style_start_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_start_screen_main_main_default, 255);
	lv_obj_add_style(ui->start_screen, &style_start_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes start_screen_schedule_bar
	ui->start_screen_schedule_bar = lv_bar_create(ui->start_screen);
	lv_obj_set_pos(ui->start_screen_schedule_bar, 4, 100);
	lv_obj_set_size(ui->start_screen_schedule_bar, 120, 10);
	lv_obj_set_scrollbar_mode(ui->start_screen_schedule_bar, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_start_screen_schedule_bar_main_main_default
	static lv_style_t style_start_screen_schedule_bar_main_main_default;
	if (style_start_screen_schedule_bar_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_start_screen_schedule_bar_main_main_default);
	else
		lv_style_init(&style_start_screen_schedule_bar_main_main_default);
	lv_style_set_radius(&style_start_screen_schedule_bar_main_main_default, 10);
	lv_style_set_bg_color(&style_start_screen_schedule_bar_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_start_screen_schedule_bar_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_start_screen_schedule_bar_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_start_screen_schedule_bar_main_main_default, 60);
	lv_obj_add_style(ui->start_screen_schedule_bar, &style_start_screen_schedule_bar_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_start_screen_schedule_bar_main_indicator_default
	static lv_style_t style_start_screen_schedule_bar_main_indicator_default;
	if (style_start_screen_schedule_bar_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_start_screen_schedule_bar_main_indicator_default);
	else
		lv_style_init(&style_start_screen_schedule_bar_main_indicator_default);
	lv_style_set_radius(&style_start_screen_schedule_bar_main_indicator_default, 10);
	lv_style_set_bg_color(&style_start_screen_schedule_bar_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_start_screen_schedule_bar_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_start_screen_schedule_bar_main_indicator_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_start_screen_schedule_bar_main_indicator_default, 255);
	lv_obj_add_style(ui->start_screen_schedule_bar, &style_start_screen_schedule_bar_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_anim_time(ui->start_screen_schedule_bar, 8000, 0);
	lv_bar_set_mode(ui->start_screen_schedule_bar, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->start_screen_schedule_bar, 100, LV_ANIM_ON);

	//Write codes start_screen_label_1
	ui->start_screen_label_1 = lv_label_create(ui->start_screen);
	lv_obj_set_pos(ui->start_screen_label_1, 14, 30);
	lv_obj_set_size(ui->start_screen_label_1, 100, 20);
	lv_obj_set_scrollbar_mode(ui->start_screen_label_1, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->start_screen_label_1, "H7-Mode");
	lv_label_set_long_mode(ui->start_screen_label_1, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_start_screen_label_1_main_main_default
	static lv_style_t style_start_screen_label_1_main_main_default;
	if (style_start_screen_label_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_start_screen_label_1_main_main_default);
	else
		lv_style_init(&style_start_screen_label_1_main_main_default);
	lv_style_set_radius(&style_start_screen_label_1_main_main_default, 0);
	lv_style_set_bg_color(&style_start_screen_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_start_screen_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_start_screen_label_1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_start_screen_label_1_main_main_default, 0);
	lv_style_set_text_color(&style_start_screen_label_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_start_screen_label_1_main_main_default, &lv_font_simsun_20);
	lv_style_set_text_letter_space(&style_start_screen_label_1_main_main_default, 2);
	lv_style_set_text_line_space(&style_start_screen_label_1_main_main_default, 0);
	lv_style_set_text_align(&style_start_screen_label_1_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_start_screen_label_1_main_main_default, 0);
	lv_style_set_pad_right(&style_start_screen_label_1_main_main_default, 0);
	lv_style_set_pad_top(&style_start_screen_label_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_start_screen_label_1_main_main_default, 0);
	lv_obj_add_style(ui->start_screen_label_1, &style_start_screen_label_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes start_screen_label_2
	ui->start_screen_label_2 = lv_label_create(ui->start_screen);
	lv_obj_set_pos(ui->start_screen_label_2, 14, 88);
	lv_obj_set_size(ui->start_screen_label_2, 100, 10);
	lv_obj_set_scrollbar_mode(ui->start_screen_label_2, LV_SCROLLBAR_MODE_OFF);
	lv_label_set_text(ui->start_screen_label_2, "加载中");
	lv_label_set_long_mode(ui->start_screen_label_2, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_start_screen_label_2_main_main_default
	static lv_style_t style_start_screen_label_2_main_main_default;
	if (style_start_screen_label_2_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_start_screen_label_2_main_main_default);
	else
		lv_style_init(&style_start_screen_label_2_main_main_default);
	lv_style_set_radius(&style_start_screen_label_2_main_main_default, 0);
	lv_style_set_bg_color(&style_start_screen_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_start_screen_label_2_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_start_screen_label_2_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_start_screen_label_2_main_main_default, 0);
	lv_style_set_text_color(&style_start_screen_label_2_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_start_screen_label_2_main_main_default, &lv_font_simsun_10);
	lv_style_set_text_letter_space(&style_start_screen_label_2_main_main_default, 2);
	lv_style_set_text_line_space(&style_start_screen_label_2_main_main_default, 0);
	lv_style_set_text_align(&style_start_screen_label_2_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_start_screen_label_2_main_main_default, 0);
	lv_style_set_pad_right(&style_start_screen_label_2_main_main_default, 0);
	lv_style_set_pad_top(&style_start_screen_label_2_main_main_default, 0);
	lv_style_set_pad_bottom(&style_start_screen_label_2_main_main_default, 0);
	lv_obj_add_style(ui->start_screen_label_2, &style_start_screen_label_2_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);


	events_init_start_screen(ui);
}