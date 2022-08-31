/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-08-18 18:50:27
 * @LastEditTime: 2022-09-01 03:01:02
 */
#ifndef BSP_ST7735S_H
#define BSP_ST7735S_H

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
#define TIM_CHANNEL TIM_CHANNEL_1

/*IO操作*/
#define LCD_RES_Low()  LCD_RES_GPIO_Port->BSRR = (uint32_t)LCD_RES_Pin << 16U
#define LCD_RES_High() LCD_RES_GPIO_Port->BSRR = LCD_RES_Pin

#define LCD_DC_Low()   LCD_DC_GPIO_Port->BSRR = (uint32_t)LCD_DC_Pin << 16U
#define LCD_DC_High()  LCD_DC_GPIO_Port->BSRR = LCD_DC_Pin

/*屏幕分辨率*/
#define X_MAX_PIXEL 128
#define Y_MAX_PIXEL 128

/*显示方向 0~3*/
#define USE_HORIZONTAL 2

/*是否使用FreeRTOS*/
#define USE_FreeRTOS 1

/*LCD背光接口*/
void Bsp_LCD_BacklightPct(uint8_t pct);

void Bsp_LCD_Delay(uint16_t delay);

/*数据长度设置*/
void Bsp_LCD_SPI_SET8B(void);
void Bsp_LCD_SPI_SET16B(void);

/*DMA内存设置*/
void Bsp_LCD_DMA_SetMemInc(uint8_t Enable);

/*数据发送API*/
void Bsp_LCD_SendData_16B(uint16_t data);
void Bsp_LCD_SendData_8B(uint8_t data);
void Bsp_LCD_SendCmd_16B(uint16_t data);
void Bsp_LCD_SendCmd_8B(uint8_t data);
void Bsp_LCD_SendData(uint8_t *data, uint16_t len);
void Bsp_LCD_Send_DMA(uint8_t *data, uint16_t len);
uint8_t Bsp_LCD_TX_InquireFinish(void);

#endif
