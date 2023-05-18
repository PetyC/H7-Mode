/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"


void init_scr_del_flag(lv_ui *ui){
	ui->main_screen_del = true;
	ui->device_screen_del = true;
	ui->Wifi_screen_del = true;
	ui->QR_screen_del = true;
}

void setup_ui(lv_ui *ui){
	init_scr_del_flag(ui);
	setup_scr_main_screen(ui);
	lv_scr_load(ui->main_screen);
}
