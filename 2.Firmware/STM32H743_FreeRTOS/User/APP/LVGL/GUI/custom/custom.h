/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-08-26 22:53:22
 * @LastEditTime: 2022-08-30 23:33:27
 */
// SPDX-License-Identifier: MIT
// Copyright 2020 NXP

/*
 * custom.h
 *
 *  Created on: July 29, 2020
 *      Author: nxf53801
 */

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

void custom_init(lv_ui *ui);

void encoder_init(void);
void encoder_main_init(void);
void encoder_wifi_init(void);
void encoder_qr_init(void);
void encoder_device_init(void);


void UI_Wifi_ImagesDispaly(uint8_t Enagle);

void UI_Wifi_Set_ScreenInit(void);
#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
