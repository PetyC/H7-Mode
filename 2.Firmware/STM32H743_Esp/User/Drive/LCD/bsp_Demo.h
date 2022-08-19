/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-08-18 18:50:27
 * @LastEditTime: 2022-08-19 17:32:22
 */
#ifndef BSP_DEMO_H
#define BSP_DEMO_H

#include <string.h>
#include "main.h"
#include "stm32h7xx.h"
#include "spi.h"

/*SPI句柄*/
#define SPI_HANDLE (hspi1)
extern SPI_HandleTypeDef SPI_HANDLE;

/*DMA句柄*/
#define DMA_HANDLE (hdma_spi1_tx)
extern DMA_HandleTypeDef DMA_HANDLE;

/*TIM句柄*/
#define TIM_HANDLE (htim1)
extern TIM_HandleTypeDef TIM_HANDLE;
#define TIM_CHANNEL   TIM_CHANNEL_1



/*是否使用FreeRTOS*/
#define USE_FreeRTOS  0

/*IO操作*/
#define LCD_RES_Low()   LCD_RES_GPIO_Port->BSRR = (uint32_t)LCD_RES_Pin << 16U
#define LCD_RES_High()  LCD_RES_GPIO_Port->BSRR = LCD_RES_Pin

#define LCD_DC_Low()    LCD_DC_GPIO_Port->BSRR = (uint32_t)LCD_DC_Pin << 16U  
#define LCD_DC_High()   LCD_DC_GPIO_Port->BSRR = LCD_DC_Pin    

/*屏幕分辨率*/
#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        128

/*显示方向 0~3*/
#define USE_HORIZONTAL 2

/*LCD功能设置*/
void Bsp_LCD_Init(void);
void Bsp_LCD_Reset(void);
void Bsp_LCD_BacklightPct(uint8_t pct);

/*绘图功能*/

void Bsp_LCD_FullColor(uint16_t Color);

#endif
