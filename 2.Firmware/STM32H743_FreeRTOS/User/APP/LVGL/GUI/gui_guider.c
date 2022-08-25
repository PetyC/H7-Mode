/*
 * Copyright 2022 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl/lvgl.h"
#include <stdio.h>
#include "gui_guider.h"

lv_ui guider_ui;

void setup_ui(lv_ui *ui){
	setup_scr_main_screen(ui);
	lv_scr_load(ui->main_screen);
}
