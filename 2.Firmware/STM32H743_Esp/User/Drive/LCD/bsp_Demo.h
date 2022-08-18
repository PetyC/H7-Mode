/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-08-18 18:50:27
 * @LastEditTime: 2022-08-18 19:56:20
 */
#ifndef BSP_DEMO_H
#define BSP_DEMO_H

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




/*是否使用FreeRTOS*/
#define USE_FreeRTOS  0

/*IO操作*/
#define LCD_RES_Low()   LCD_RES_GPIO_Port->BSRR = (uint32_t)LCD_RES_Pin << 16U
#define LCD_RES_High()  LCD_RES_GPIO_Port->BSRR = LCD_RES_Pin

#define LCD_DC_Low()    LCD_DC_GPIO_Port->BSRR = (uint32_t)LCD_DC_Pin << 16U  
#define LCD_DC_High()   LCD_DC_GPIO_Port->BSRR = LCD_DC_Pin    






#endif
