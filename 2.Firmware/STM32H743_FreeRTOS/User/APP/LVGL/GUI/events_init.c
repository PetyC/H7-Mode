/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-08-25 15:31:45
 * @LastEditTime: 2022-08-26 19:30:54
 */
/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl/lvgl.h"

extern lv_indev_t * indev_keypad;
lv_group_t * key_group;

void events_init(lv_ui *ui)
{
   /*创建对象分组*/
   key_group = lv_group_create();
  /*将对象分组分配至输入设备*/
  lv_indev_set_group(indev_keypad , key_group);
  
  /*将被控制的对象添加进group*/
  lv_group_add_obj(key_group , guider_ui.main_screen_Wifi_Set_btn);
  lv_group_add_obj(key_group , guider_ui.main_screen_Demo_btn);
}

static void main_screen_Wifi_Set_btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
    /*
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.Wifi_screen_del == true)
				setup_scr_Wifi_screen(&guider_ui);
			lv_scr_load_anim(guider_ui.Wifi_screen, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.main_screen_del = true;
    */
    setup_scr_Wifi_screen(&guider_ui);
			lv_scr_load_anim(guider_ui.Wifi_screen, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
	}
		break;
	default:
		break;
	}
}

static void main_screen_Demo_btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	default:
		break;
	}
}

void events_init_main_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->main_screen_Wifi_Set_btn, main_screen_Wifi_Set_btn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->main_screen_Demo_btn, main_screen_Demo_btn_event_handler, LV_EVENT_ALL, NULL);
}

static void Wifi_screen_btn_1_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.main_screen_del == true)
				setup_scr_main_screen(&guider_ui);
			lv_scr_load_anim(guider_ui.main_screen, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		}
		guider_ui.Wifi_screen_del = true;
	}
		break;
	default:
		break;
	}
}

void events_init_Wifi_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->Wifi_screen_btn_1, Wifi_screen_btn_1_event_handler, LV_EVENT_ALL, NULL);
}
