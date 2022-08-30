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


void setup_scr_main_screen(lv_ui *ui){

	//Write codes main_screen
	ui->main_screen = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->main_screen, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_main_main_default
	static lv_style_t style_main_screen_main_main_default;
	if (style_main_screen_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_main_screen_main_main_default);
	else
		lv_style_init(&style_main_screen_main_main_default);
	lv_style_set_bg_color(&style_main_screen_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_opa(&style_main_screen_main_main_default, 255);
	lv_obj_add_style(ui->main_screen, &style_main_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_screen_wifi_set_btn
	ui->main_screen_wifi_set_btn = lv_btn_create(ui->main_screen);
	lv_obj_set_pos(ui->main_screen_wifi_set_btn, 14, 35);
	lv_obj_set_size(ui->main_screen_wifi_set_btn, 100, 20);
	lv_obj_set_scrollbar_mode(ui->main_screen_wifi_set_btn, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_wifi_set_btn_main_main_default
	static lv_style_t style_main_screen_wifi_set_btn_main_main_default;
	if (style_main_screen_wifi_set_btn_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_main_screen_wifi_set_btn_main_main_default);
	else
		lv_style_init(&style_main_screen_wifi_set_btn_main_main_default);
	lv_style_set_radius(&style_main_screen_wifi_set_btn_main_main_default, 5);
	lv_style_set_bg_color(&style_main_screen_wifi_set_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_main_screen_wifi_set_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_main_screen_wifi_set_btn_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_main_screen_wifi_set_btn_main_main_default, 109);
	lv_style_set_shadow_width(&style_main_screen_wifi_set_btn_main_main_default, 1);
	lv_style_set_shadow_color(&style_main_screen_wifi_set_btn_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_shadow_opa(&style_main_screen_wifi_set_btn_main_main_default, 0);
	lv_style_set_shadow_spread(&style_main_screen_wifi_set_btn_main_main_default, 1);
	lv_style_set_shadow_ofs_x(&style_main_screen_wifi_set_btn_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_main_screen_wifi_set_btn_main_main_default, 0);
	lv_style_set_border_color(&style_main_screen_wifi_set_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_main_screen_wifi_set_btn_main_main_default, 0);
	lv_style_set_border_opa(&style_main_screen_wifi_set_btn_main_main_default, 0);
	lv_style_set_text_color(&style_main_screen_wifi_set_btn_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_main_screen_wifi_set_btn_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_main_screen_wifi_set_btn_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->main_screen_wifi_set_btn, &style_main_screen_wifi_set_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_FOCUSED for style_main_screen_wifi_set_btn_main_main_focused
	static lv_style_t style_main_screen_wifi_set_btn_main_main_focused;
	if (style_main_screen_wifi_set_btn_main_main_focused.prop_cnt > 1)
		lv_style_reset(&style_main_screen_wifi_set_btn_main_main_focused);
	else
		lv_style_init(&style_main_screen_wifi_set_btn_main_main_focused);
	lv_style_set_radius(&style_main_screen_wifi_set_btn_main_main_focused, 5);
	lv_style_set_bg_color(&style_main_screen_wifi_set_btn_main_main_focused, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_main_screen_wifi_set_btn_main_main_focused, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_main_screen_wifi_set_btn_main_main_focused, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_main_screen_wifi_set_btn_main_main_focused, 255);
	lv_style_set_border_color(&style_main_screen_wifi_set_btn_main_main_focused, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_main_screen_wifi_set_btn_main_main_focused, 0);
	lv_style_set_border_opa(&style_main_screen_wifi_set_btn_main_main_focused, 255);
	lv_style_set_text_color(&style_main_screen_wifi_set_btn_main_main_focused, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_main_screen_wifi_set_btn_main_main_focused, &lv_font_simsun_12);
	lv_obj_add_style(ui->main_screen_wifi_set_btn, &style_main_screen_wifi_set_btn_main_main_focused, LV_PART_MAIN|LV_STATE_FOCUSED);

	//Write style state: LV_STATE_PRESSED for style_main_screen_wifi_set_btn_main_main_pressed
	static lv_style_t style_main_screen_wifi_set_btn_main_main_pressed;
	if (style_main_screen_wifi_set_btn_main_main_pressed.prop_cnt > 1)
		lv_style_reset(&style_main_screen_wifi_set_btn_main_main_pressed);
	else
		lv_style_init(&style_main_screen_wifi_set_btn_main_main_pressed);
	lv_style_set_radius(&style_main_screen_wifi_set_btn_main_main_pressed, 5);
	lv_style_set_bg_color(&style_main_screen_wifi_set_btn_main_main_pressed, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_main_screen_wifi_set_btn_main_main_pressed, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_main_screen_wifi_set_btn_main_main_pressed, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_main_screen_wifi_set_btn_main_main_pressed, 255);
	lv_style_set_border_color(&style_main_screen_wifi_set_btn_main_main_pressed, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_main_screen_wifi_set_btn_main_main_pressed, 0);
	lv_style_set_border_opa(&style_main_screen_wifi_set_btn_main_main_pressed, 255);
	lv_style_set_text_color(&style_main_screen_wifi_set_btn_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_main_screen_wifi_set_btn_main_main_pressed, &lv_font_simsun_12);
	lv_obj_add_style(ui->main_screen_wifi_set_btn, &style_main_screen_wifi_set_btn_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);
	ui->main_screen_wifi_set_btn_label = lv_label_create(ui->main_screen_wifi_set_btn);
	lv_label_set_text(ui->main_screen_wifi_set_btn_label, "WIFI设置");
	lv_obj_set_style_pad_all(ui->main_screen_wifi_set_btn, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->main_screen_wifi_set_btn_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes main_screen_demo_btn
	ui->main_screen_demo_btn = lv_btn_create(ui->main_screen);
	lv_obj_set_pos(ui->main_screen_demo_btn, 14, 70);
	lv_obj_set_size(ui->main_screen_demo_btn, 100, 20);
	lv_obj_set_scrollbar_mode(ui->main_screen_demo_btn, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_demo_btn_main_main_default
	static lv_style_t style_main_screen_demo_btn_main_main_default;
	if (style_main_screen_demo_btn_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_main_screen_demo_btn_main_main_default);
	else
		lv_style_init(&style_main_screen_demo_btn_main_main_default);
	lv_style_set_radius(&style_main_screen_demo_btn_main_main_default, 5);
	lv_style_set_bg_color(&style_main_screen_demo_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_main_screen_demo_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_main_screen_demo_btn_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_main_screen_demo_btn_main_main_default, 109);
	lv_style_set_shadow_width(&style_main_screen_demo_btn_main_main_default, 1);
	lv_style_set_shadow_color(&style_main_screen_demo_btn_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_shadow_opa(&style_main_screen_demo_btn_main_main_default, 0);
	lv_style_set_shadow_spread(&style_main_screen_demo_btn_main_main_default, 1);
	lv_style_set_shadow_ofs_x(&style_main_screen_demo_btn_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_main_screen_demo_btn_main_main_default, 0);
	lv_style_set_border_color(&style_main_screen_demo_btn_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_main_screen_demo_btn_main_main_default, 0);
	lv_style_set_border_opa(&style_main_screen_demo_btn_main_main_default, 0);
	lv_style_set_text_color(&style_main_screen_demo_btn_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_main_screen_demo_btn_main_main_default, &lv_font_simsun_12);
	lv_style_set_text_align(&style_main_screen_demo_btn_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->main_screen_demo_btn, &style_main_screen_demo_btn_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_FOCUSED for style_main_screen_demo_btn_main_main_focused
	static lv_style_t style_main_screen_demo_btn_main_main_focused;
	if (style_main_screen_demo_btn_main_main_focused.prop_cnt > 1)
		lv_style_reset(&style_main_screen_demo_btn_main_main_focused);
	else
		lv_style_init(&style_main_screen_demo_btn_main_main_focused);
	lv_style_set_radius(&style_main_screen_demo_btn_main_main_focused, 5);
	lv_style_set_bg_color(&style_main_screen_demo_btn_main_main_focused, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_main_screen_demo_btn_main_main_focused, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_main_screen_demo_btn_main_main_focused, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_main_screen_demo_btn_main_main_focused, 255);
	lv_style_set_border_color(&style_main_screen_demo_btn_main_main_focused, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_main_screen_demo_btn_main_main_focused, 0);
	lv_style_set_border_opa(&style_main_screen_demo_btn_main_main_focused, 255);
	lv_style_set_text_color(&style_main_screen_demo_btn_main_main_focused, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_main_screen_demo_btn_main_main_focused, &lv_font_simsun_12);
	lv_obj_add_style(ui->main_screen_demo_btn, &style_main_screen_demo_btn_main_main_focused, LV_PART_MAIN|LV_STATE_FOCUSED);

	//Write style state: LV_STATE_PRESSED for style_main_screen_demo_btn_main_main_pressed
	static lv_style_t style_main_screen_demo_btn_main_main_pressed;
	if (style_main_screen_demo_btn_main_main_pressed.prop_cnt > 1)
		lv_style_reset(&style_main_screen_demo_btn_main_main_pressed);
	else
		lv_style_init(&style_main_screen_demo_btn_main_main_pressed);
	lv_style_set_radius(&style_main_screen_demo_btn_main_main_pressed, 5);
	lv_style_set_bg_color(&style_main_screen_demo_btn_main_main_pressed, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_main_screen_demo_btn_main_main_pressed, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_main_screen_demo_btn_main_main_pressed, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_main_screen_demo_btn_main_main_pressed, 255);
	lv_style_set_border_color(&style_main_screen_demo_btn_main_main_pressed, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_border_width(&style_main_screen_demo_btn_main_main_pressed, 0);
	lv_style_set_border_opa(&style_main_screen_demo_btn_main_main_pressed, 255);
	lv_style_set_text_color(&style_main_screen_demo_btn_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_main_screen_demo_btn_main_main_pressed, &lv_font_simsun_12);
	lv_obj_add_style(ui->main_screen_demo_btn, &style_main_screen_demo_btn_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);
	ui->main_screen_demo_btn_label = lv_label_create(ui->main_screen_demo_btn);
	lv_label_set_text(ui->main_screen_demo_btn_label, "关于设备");
	lv_obj_set_style_pad_all(ui->main_screen_demo_btn, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->main_screen_demo_btn_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes main_screen_led_1
	ui->main_screen_led_1 = lv_led_create(ui->main_screen);
	lv_obj_set_pos(ui->main_screen_led_1, 54, 100);
	lv_obj_set_size(ui->main_screen_led_1, 20, 20);
	lv_obj_set_scrollbar_mode(ui->main_screen_led_1, LV_SCROLLBAR_MODE_OFF);
	lv_led_set_brightness(ui->main_screen_led_1, 0);
	lv_led_set_color(ui->main_screen_led_1, lv_color_make(0x00, 0xa1, 0xb5));

	//Write codes main_screen_wifi_img
	ui->main_screen_wifi_img = lv_img_create(ui->main_screen);
	lv_obj_set_pos(ui->main_screen_wifi_img, 112, 2);
	lv_obj_set_size(ui->main_screen_wifi_img, 15, 14);
	lv_obj_set_scrollbar_mode(ui->main_screen_wifi_img, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_main_screen_wifi_img_main_main_default
	static lv_style_t style_main_screen_wifi_img_main_main_default;
	if (style_main_screen_wifi_img_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_main_screen_wifi_img_main_main_default);
	else
		lv_style_init(&style_main_screen_wifi_img_main_main_default);
	lv_style_set_img_recolor(&style_main_screen_wifi_img_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_img_recolor_opa(&style_main_screen_wifi_img_main_main_default, 0);
	lv_style_set_img_opa(&style_main_screen_wifi_img_main_main_default, 255);
	lv_obj_add_style(ui->main_screen_wifi_img, &style_main_screen_wifi_img_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->main_screen_wifi_img, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->main_screen_wifi_img,&_WIFI_discon_15x14);
	lv_img_set_pivot(ui->main_screen_wifi_img, 0,0);
	lv_img_set_angle(ui->main_screen_wifi_img, 0);

	//Init events for screen
	events_init_main_screen(ui);
}