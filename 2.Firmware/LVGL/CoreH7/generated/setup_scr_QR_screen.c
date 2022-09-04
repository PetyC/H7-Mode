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


void setup_scr_QR_screen(lv_ui *ui){

	//Write codes QR_screen
	ui->QR_screen = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->QR_screen, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_qr_screen_main_main_default
	static lv_style_t style_qr_screen_main_main_default;
	if (style_qr_screen_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_qr_screen_main_main_default);
	else
		lv_style_init(&style_qr_screen_main_main_default);
	lv_style_set_bg_color(&style_qr_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_qr_screen_main_main_default, 255);
	lv_obj_add_style(ui->QR_screen, &style_qr_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes QR_screen_img_1
	ui->QR_screen_img_1 = lv_img_create(ui->QR_screen);
	lv_obj_set_pos(ui->QR_screen_img_1, 14, 5);
	lv_obj_set_size(ui->QR_screen_img_1, 100, 100);
	lv_obj_set_scrollbar_mode(ui->QR_screen_img_1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_qr_screen_img_1_main_main_default
	static lv_style_t style_qr_screen_img_1_main_main_default;
	if (style_qr_screen_img_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_qr_screen_img_1_main_main_default);
	else
		lv_style_init(&style_qr_screen_img_1_main_main_default);
	lv_style_set_img_recolor(&style_qr_screen_img_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_qr_screen_img_1_main_main_default, 0);
	lv_style_set_img_opa(&style_qr_screen_img_1_main_main_default, 255);
	lv_obj_add_style(ui->QR_screen_img_1, &style_qr_screen_img_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->QR_screen_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->QR_screen_img_1,&_QR_100x100);
	lv_img_set_pivot(ui->QR_screen_img_1, 0,0);
	lv_img_set_angle(ui->QR_screen_img_1, 0);

	//Write codes QR_screen_QR_bar
	ui->QR_screen_QR_bar = lv_bar_create(ui->QR_screen);
	lv_obj_set_pos(ui->QR_screen_QR_bar, 0, 114);
	lv_obj_set_size(ui->QR_screen_QR_bar, 128, 10);
	lv_obj_set_scrollbar_mode(ui->QR_screen_QR_bar, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_qr_screen_qr_bar_main_main_default
	static lv_style_t style_qr_screen_qr_bar_main_main_default;
	if (style_qr_screen_qr_bar_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_qr_screen_qr_bar_main_main_default);
	else
		lv_style_init(&style_qr_screen_qr_bar_main_main_default);
	lv_style_set_radius(&style_qr_screen_qr_bar_main_main_default, 10);
	lv_style_set_bg_color(&style_qr_screen_qr_bar_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_qr_screen_qr_bar_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_qr_screen_qr_bar_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_qr_screen_qr_bar_main_main_default, 60);
	lv_obj_add_style(ui->QR_screen_QR_bar, &style_qr_screen_qr_bar_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_qr_screen_qr_bar_main_indicator_default
	static lv_style_t style_qr_screen_qr_bar_main_indicator_default;
	if (style_qr_screen_qr_bar_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_qr_screen_qr_bar_main_indicator_default);
	else
		lv_style_init(&style_qr_screen_qr_bar_main_indicator_default);
	lv_style_set_radius(&style_qr_screen_qr_bar_main_indicator_default, 10);
	lv_style_set_bg_color(&style_qr_screen_qr_bar_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_qr_screen_qr_bar_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_qr_screen_qr_bar_main_indicator_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_qr_screen_qr_bar_main_indicator_default, 255);
	lv_obj_add_style(ui->QR_screen_QR_bar, &style_qr_screen_qr_bar_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_anim_time(ui->QR_screen_QR_bar, 1000, 0);
	lv_bar_set_mode(ui->QR_screen_QR_bar, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->QR_screen_QR_bar, 0, LV_ANIM_ON);
}