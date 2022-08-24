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


void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	if (style_screen_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_main_default);
	else
		lv_style_init(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_screen_main_main_default, 0);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_btnm_1
	ui->screen_btnm_1 = lv_btnmatrix_create(ui->screen);
	lv_obj_set_pos(ui->screen_btnm_1, 2, 27);
	lv_obj_set_size(ui->screen_btnm_1, 120, 100);
	static const char *screen_btnm_1_text_map[] = {
	"1","2","3","\n",
	"4","5","6","\n",
	"7","8","9","",
	};
	lv_btnmatrix_set_map(ui->screen_btnm_1, screen_btnm_1_text_map);

	//Write style state: LV_STATE_DEFAULT for style_screen_btnm_1_main_main_default
	static lv_style_t style_screen_btnm_1_main_main_default;
	if (style_screen_btnm_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_btnm_1_main_main_default);
	else
		lv_style_init(&style_screen_btnm_1_main_main_default);
	lv_style_set_radius(&style_screen_btnm_1_main_main_default, 4);
	lv_style_set_bg_color(&style_screen_btnm_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_btnm_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_btnm_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_btnm_1_main_main_default, 255);
	lv_style_set_border_color(&style_screen_btnm_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_border_width(&style_screen_btnm_1_main_main_default, 1);
	lv_style_set_pad_left(&style_screen_btnm_1_main_main_default, 16);
	lv_style_set_pad_right(&style_screen_btnm_1_main_main_default, 16);
	lv_style_set_pad_top(&style_screen_btnm_1_main_main_default, 16);
	lv_style_set_pad_bottom(&style_screen_btnm_1_main_main_default, 16);
	lv_style_set_pad_row(&style_screen_btnm_1_main_main_default, 8);
	lv_style_set_pad_column(&style_screen_btnm_1_main_main_default, 8);
	lv_obj_add_style(ui->screen_btnm_1, &style_screen_btnm_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_btnm_1_main_items_default
	static lv_style_t style_screen_btnm_1_main_items_default;
	if (style_screen_btnm_1_main_items_default.prop_cnt > 1)
		lv_style_reset(&style_screen_btnm_1_main_items_default);
	else
		lv_style_init(&style_screen_btnm_1_main_items_default);
	lv_style_set_radius(&style_screen_btnm_1_main_items_default, 4);
	lv_style_set_bg_color(&style_screen_btnm_1_main_items_default, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_bg_grad_color(&style_screen_btnm_1_main_items_default, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_bg_grad_dir(&style_screen_btnm_1_main_items_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_btnm_1_main_items_default, 255);
	lv_style_set_border_color(&style_screen_btnm_1_main_items_default, lv_color_make(0xd6, 0xdd, 0xe3));
	lv_style_set_border_width(&style_screen_btnm_1_main_items_default, 1);
	lv_style_set_text_color(&style_screen_btnm_1_main_items_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_btnm_1_main_items_default, &lv_font_simsun_12);
	lv_obj_add_style(ui->screen_btnm_1, &style_screen_btnm_1_main_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write codes screen_label_1
	ui->screen_label_1 = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_label_1, 13.5, 3);
	lv_obj_set_size(ui->screen_label_1, 100, 32);
	lv_label_set_text(ui->screen_label_1, "Hello Word");
	lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_style_text_align(ui->screen_label_1, LV_TEXT_ALIGN_CENTER, 0);

	//Write style state: LV_STATE_DEFAULT for style_screen_label_1_main_main_default
	static lv_style_t style_screen_label_1_main_main_default;
	if (style_screen_label_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_label_1_main_main_default);
	else
		lv_style_init(&style_screen_label_1_main_main_default);
	lv_style_set_radius(&style_screen_label_1_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_label_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_label_1_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_label_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_label_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_label_1_main_main_default, &lv_font_simsun_16);
	lv_style_set_text_letter_space(&style_screen_label_1_main_main_default, 2);
	lv_style_set_pad_left(&style_screen_label_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_label_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_label_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_label_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_label_1, &style_screen_label_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
}