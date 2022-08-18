/*
 * @Description:LCD 驱动层相关函数
 * @Autor: Pi
 * @Date: 2022-01-14 16:06:56
 * @LastEditTime: 2022-03-23 17:23:26
 */
#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "main.h"
#include <string.h>


#define USE_HORIZONTAL 3

#define LCD_W 128
#define LCD_H 128

#define LCD_RES_Clr() HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_RESET) // RES
#define LCD_RES_Set() HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_SET)

#define LCD_DC_Clr() LCD_DC_GPIO_Port->BSRR = (uint32_t)LCD_DC_Pin << 16U //置0
#define LCD_DC_Set() LCD_DC_GPIO_Port->BSRR = LCD_DC_Pin                  //置1		写数据

#define LCD_BLK_Clr() HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_RESET) // BLK
#define LCD_BLK_Set() HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_SET)

void LCD_Init(void);
void LCD_WR_DATA8(uint8_t dat);
void LCD_WR_DATA(uint16_t dat);
void LCD_WR_REG(uint8_t dat);
void Set_SPI_DATASIZE_16BIT(void);
void Set_SPI_DATASIZE_8BIT(void);
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);


void User_LCD_Fill(uint8_t *color);

void User_LCD_ShowPicture(const uint8_t pic[], uint32_t len);


void Demo_Images_Show(void);


void User_LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);


#endif
