/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"


void events_init(lv_ui *ui)
{
}

static void main_screen_wifi_set_btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.Wifi_screen_del == true)
				setup_scr_Wifi_screen(&guider_ui);
			lv_scr_load_anim(guider_ui.Wifi_screen, LV_SCR_LOAD_ANIM_OVER_LEFT, 0, 0, true);
		}
		guider_ui.main_screen_del = true;
	}
		break;
	default:
		break;
	}
}

static void main_screen_demo_btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		static uint8_t LED_Flag = 0;
		if(LED_Flag == 0)
		{
		  lv_obj_set_style_bg_color(guider_ui.main_screen_led_1, lv_color_make(0x07, 0xd7, 0xf2), LV_PART_MAIN);
		 
		}
		else
		{
		   lv_obj_set_style_bg_color(guider_ui.main_screen_led_1, lv_color_make(0xff, 0xff, 0xff), LV_PART_MAIN);
		}
		LED_Flag = !LED_Flag;
		
	}
		break;
	default:
		break;
	}
}

void events_init_main_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->main_screen_wifi_set_btn, main_screen_wifi_set_btn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->main_screen_demo_btn, main_screen_demo_btn_event_handler, LV_EVENT_ALL, NULL);
}

static void Wifi_screen_APU_btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.QR_screen_del == true)
				setup_scr_QR_screen(&guider_ui);
			lv_scr_load_anim(guider_ui.QR_screen, LV_SCR_LOAD_ANIM_OVER_LEFT, 0, 0, true);
		}
		guider_ui.Wifi_screen_del = true;
	}
		break;
	default:
		break;
	}
}

static void Wifi_screen_return_btn_event_handler(lv_event_t *e)
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
	lv_obj_add_event_cb(ui->Wifi_screen_APU_btn, Wifi_screen_APU_btn_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->Wifi_screen_return_btn, Wifi_screen_return_btn_event_handler, LV_EVENT_ALL, NULL);
}
