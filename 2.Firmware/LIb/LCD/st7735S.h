/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-08-22 17:12:15
 * @LastEditTime: 2022-08-22 17:17:26
 */
#ifndef ST7735S_H
#define ST7735S_H

#include "bsp_st7735s.h"


/*LCD功能设置*/
void LCD_Init(void);
void LCD_Reset(void);
void LCD_BacklightPct(uint8_t pct);


/*绘图功能*/
void LCD_SetRegion(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end);
void LCD_SetXY(uint16_t x, uint16_t y);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t Data);
void LCD_FullColor(uint16_t Color);
void LCD_DisplayImages(uint16_t *Images);


#endif