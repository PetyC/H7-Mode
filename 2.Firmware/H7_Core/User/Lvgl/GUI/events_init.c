/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

void events_init(lv_ui *ui)
{
  custom_init(ui);
  //encoder_main_init();
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
      encoder_wifi_init();
      UI_Wifi_Set_ScreenInit();
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
		lv_disp_t * d = lv_obj_get_disp(lv_scr_act());
		if (d->prev_scr == NULL && d->scr_to_load == NULL)
		{
			if (guider_ui.device_screen_del == true)
				setup_scr_device_screen(&guider_ui);
			lv_scr_load_anim(guider_ui.device_screen, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
      encoder_device_init();
		}
		guider_ui.main_screen_del = true;
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

static void device_screen_return_btn_event_handler(lv_event_t *e)
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
      encoder_main_init();
		}
		guider_ui.device_screen_del = true;
	}
		break;
	default:
		break;
	}
}

void events_init_device_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->device_screen_return_btn, device_screen_return_btn_event_handler, LV_EVENT_ALL, NULL);
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
      encoder_qr_init();
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
      encoder_main_init();
		}
		guider_ui.Wifi_screen_del = true;
	}
		break;
	default:
		break;
	}
}


#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os2.h"
//extern osThreadId Network_TaskHandle;

static void Wifi_screen_wifi_en_sw_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
  uint32_t EventGroup;

	switch (code)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		if(lv_obj_has_state(guider_ui.Wifi_screen_wifi_en_sw , LV_STATE_CHECKED) == 1)      //wifi开
    {
      EventGroup = 1;
    }
    else                                                                                //wifi关
    {
      EventGroup = 0;
    }

    //xTaskNotify( Network_TaskHandle, EventGroup, eSetBits);
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
  lv_obj_add_event_cb(ui->Wifi_screen_wifi_en_sw, Wifi_screen_wifi_en_sw_event_handler, LV_EVENT_ALL, NULL);
}

