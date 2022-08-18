/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-07-04 14:40:58
 * @LastEditTime: 2022-07-04 15:56:20
 */
#ifndef APP_LCD_H
#define APP_LCD_H

#include "st7735s.h"
#include "fonts.h"
#include "gfx.h"
#include "stdio.h"
#include "string.h"

#define STATE_DISPLAY_LINE    12
#define ADD_DISPLAY_LINE      12 * 2
#define SIZE_DISPLAY_LINE     12 * 3
#define ERASE_DISPLAY_LINE    12 * 4
#define WRITE_DISPLAY_LINE    12 * 5


void UI_Init_Display(void);
void UI_Falsh_Display(uint8_t Erase_State , uint8_t Write_State);
void UI_File_Display(uint32_t ADDR , uint32_t File_Size);
void UI_Count_Down_Display(uint8_t Count);

#endif
