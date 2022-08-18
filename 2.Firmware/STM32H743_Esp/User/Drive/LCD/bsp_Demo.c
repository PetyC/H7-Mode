/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-08-18 18:50:19
 * @LastEditTime: 2022-08-18 20:02:15
 */
#include "bsp_Demo.h"

#if USE_FreeRTOS == 1
#include "FreeRTOS.h"
#include "task.h"
#endif

/*内部使用函数*/
static void Bsp_Lcd_Delay(uint16_t delay);
static void Bsp_Lcd_Reset(void);

/**
 * @brief LCD延时函数
 * @param {uint16_t} delay
 * @return {*}
 */
static void Bsp_Lcd_Delay(uint16_t delay)
{
#if (USE_FreeRTOS == 0)
  HAL_Delay(delay);
#else
  vTaskDelay(1000);
#endif
}

/**
 * @brief LCD复位
 * @return {*}
 */
static void Bsp_Lcd_Reset(void)
{
  LCD_RES_Low();
  SysTick_Delay_Ms(100);
  LCD_RES_High();
  SysTick_Delay_Ms(50);
}

/**
 * @brief 发送1个8位命令
 * @param {uint16_t} len
 * @param {uint8_t} *data
 * @return {*}
 */
void Bsp_LCD_SendCmd_8B(uint8_t data)
{
  LCD_DC_Low();
  HAL_SPI_Transmit(&SPI_HANDLE, &data, 1, 0xFF);
}

/**
 * @brief 发送1个16位命令
 * @param {uint8_t} data
 * @return {*}
 */
void Bsp_LCD_SendCmd_16B(uint16_t data)
{
  uint8_t CMD[2] = {0};
  CMD[0] = data >> 8;
  CMD[1] = data && 0XFF;

  LCD_DC_Low();
  HAL_SPI_Transmit(&SPI_HANDLE, CMD, 2, 0xFF);
}

/**
 * @brief 发送1个8位数据
 * @param {uint16_t} len
 * @param {uint8_t} *data
 * @return {*}
 */
void Bsp_LCD_SendData_8B(uint8_t data)
{
  LCD_DC_High();
  HAL_SPI_Transmit(&SPI_HANDLE, &data, 1, 0xFF);
}

/**
 * @brief 发送1个16位数据
 * @param {uint16_t} len
 * @param {uint8_t} *data
 * @return {*}
 */
void Bsp_LCD_SendData_16B(uint8_t data)
{
  uint8_t CMD[2] = {0};
  CMD[0] = data >> 8;
  CMD[1] = data && 0XFF;

  LCD_DC_High();
  HAL_SPI_Transmit(&SPI_HANDLE, CMD, 2, 0xFF);
}

/**
 * @brief 通过DMA发送数据
 * @param {uint8_t} *data
 * @param {uint16_t} len
 * @return {*}
 */
void Bsp_LCD_SendData_DMA(uint8_t *data, uint16_t len)
{

  HAL_SPI_Transmit_DMA(&SPI_HANDLE , data , len);


  __HAL_DMA_GET_FLAG(&DMA_HANDLE ,DMA_FLAG_TC0);//传输完成返回1，否则返回0

 
 
}
