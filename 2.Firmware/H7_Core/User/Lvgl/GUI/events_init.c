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
	// encoder_main_init();
}

static void main_screen_wifi_set_btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t *d = lv_obj_get_disp(lv_scr_act());
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
		lv_disp_t *d = lv_obj_get_disp(lv_scr_act());
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
		lv_disp_t *d = lv_obj_get_disp(lv_scr_act());
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

static void device_screen_tile_event_handler(lv_event_t *e)
{
	lv_obj_t * cont = lv_event_get_target(e);
	lv_event_code_t code = lv_event_get_code(e);

    lv_obj_t * tv = lv_obj_get_parent(cont);

    if(lv_event_get_code(e) == LV_EVENT_SCROLL_END) 
		{
 
    }
}

void events_init_device_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->device_screen_return_btn, device_screen_return_btn_event_handler, LV_EVENT_ALL, NULL);
	//lv_obj_add_event_cb(ui->device_screen, device_screen_tile_event_handler, LV_EVENT_SCROLL_END, NULL);
}


static void Wifi_screen_APU_btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		lv_disp_t *d = lv_obj_get_disp(lv_scr_act());
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
		lv_disp_t *d = lv_obj_get_disp(lv_scr_act());
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
extern osSemaphoreId_t Wifi_Set_QueueHandle;
uint8_t s_wifi_set = 1;

static void Wifi_screen_wifi_en_sw_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	uint8_t wifi_set = 0;

	switch (code)
	{
	case LV_EVENT_VALUE_CHANGED:
	{
		if (lv_obj_has_state(guider_ui.Wifi_screen_wifi_en_sw, LV_STATE_CHECKED) == 1) // wifi开
		{
			s_wifi_set = 1;
		}
		else // wifi关
		{
			s_wifi_set = 0;
		}

		osMessageQueuePut(Wifi_Set_QueueHandle , &s_wifi_set , NULL , NULL); 
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



uint8_t ui_init_flag = 0;

static void start_screen_schedule_bar_event_handler(lv_anim_t *anim)
{
	lv_disp_t *d = lv_obj_get_disp(lv_scr_act());
	if (d->prev_scr == NULL && d->scr_to_load == NULL)
	{
		if (guider_ui.main_screen_del == true)
		setup_scr_main_screen(&guider_ui);
		lv_scr_load_anim(guider_ui.main_screen, LV_SCR_LOAD_ANIM_OVER_TOP, 0, 0, true);
		encoder_main_init();
		ui_init_flag = 1;
	}
	guider_ui.start_screen_del = true;

}

void events_init_start_screen(lv_ui *ui)
{
	lv_anim_t anim;
	lv_anim_init(&anim);
	lv_anim_set_var(&anim, ui->start_screen_schedule_bar);
	lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_bar_set_value); // 执行回调函数lv_bar_set_value()来设置进度条的值
	lv_anim_set_values(&anim, 0, 100);								  // 设定动画的起始值和结束值
	lv_anim_set_time(&anim, 8000);									  // 设定动画的总时间为10秒
	lv_anim_set_ready_cb(&anim, start_screen_schedule_bar_event_handler);
	lv_anim_start(&anim);

	 
}