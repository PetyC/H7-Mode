/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-08-18 18:50:19
 * @LastEditTime: 2022-09-01 03:00:58
 */
#include "bsp_st7735s_interface.h"

#if USE_FreeRTOS == 1
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os2.h"

//extern osSemaphoreId LCD_BinarySemHandle;

#else
/*发送完成标志*/
uint8_t LCD_TX_DMA_FLAG = 0;
#endif

/**
 * @brief LCD延时函数
 * @param {uint16_t} delay
 * @return {*}
 */
void Bsp_LCD_Delay(uint16_t delay)
{
  HAL_Delay(delay);
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
  Bsp_LCD_SPI_SET8B();
  HAL_SPI_Transmit(&SPI_HANDLE, &data, 1, 0xFF);
}

/**
 * @brief 发送1个16位命令
 * @param {uint8_t} data
 * @return {*}
 */
void Bsp_LCD_SendCmd_16B(uint16_t data)
{
  LCD_DC_Low();
  Bsp_LCD_SPI_SET16B();
  HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t *)&data, 1, 0xFF);
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
  Bsp_LCD_SPI_SET8B();
  HAL_SPI_Transmit(&SPI_HANDLE, &data, 1, 0xFF);
}

/**
 * @brief 发送1个16位数据
 * @param {uint16_t} len
 * @param {uint8_t} *data
 * @return {*}
 */
void Bsp_LCD_SendData_16B(uint16_t data)
{
  LCD_DC_High();
  Bsp_LCD_SPI_SET16B();
  HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t *)&data, 1, 0xFF);
}

/**
 * @brief 通过DMA发送
 * @param {uint8_t} *data
 * @param {uint16_t} len
 * @return {*}
 */
void Bsp_LCD_Send_DMA(uint8_t *data, uint16_t len)
{
  HAL_SPI_Transmit_DMA(&SPI_HANDLE, data, len);
}

/**
 * @brief 阻塞方式发送数据
 * @param {uint8_t} *data
 * @param {uint16_t} len
 * @return {*}
 */
void Bsp_LCD_SendData(uint8_t *data, uint16_t len)
{
  LCD_DC_High();
  HAL_SPI_Transmit(&SPI_HANDLE, data, len, 0xff);
}

/**
 * @brief 设置SPI DMA是否自增
 * @param {uint8_t} Enable 0:不自增加   1:自增
 * @return {*}
 */
void Bsp_LCD_DMA_SetMemInc(uint8_t Enable)
{
  if (Enable == 0)
  {
    /*内存不自增*/
    DMA_HANDLE.Init.MemInc = DMA_MINC_DISABLE;
  }
  else
  {
    DMA_HANDLE.Init.MemInc = DMA_MINC_ENABLE;
  }

  __HAL_RCC_DMA1_CLK_ENABLE();
  HAL_DMA_Init(&hdma_spi1_tx);
}

/**
 * @brief 设置SPI 16位传输
 * @return {*}
 */
void Bsp_LCD_SPI_SET16B(void)
{
  SPI1->CFG1 = SPI1->CFG1 & ~(0X1F);
  SPI1->CFG1 = SPI1->CFG1 | (0X0F);
  hspi1.Init.DataSize = SPI_DATASIZE_16BIT;
}

/**
 * @brief 设置SPI 8位传输
 * @return {*}
 */
void Bsp_LCD_SPI_SET8B(void)
{
  SPI1->CFG1 = SPI1->CFG1 & ~(0X1F);
  SPI1->CFG1 = SPI1->CFG1 | (0X07);
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
}

/**
 * @brief LCD背光调整
 * @param {uint8_t} pct 亮度百分比 0~100
 * @return {*}
 */
void Bsp_LCD_BacklightPct(uint8_t pct)
{
  static uint8_t Flag = 0;

  if (Flag == 0)
  {
    Flag = 1;
    HAL_TIM_PWM_Start(&TIM_HANDLE, TIM_CHANNEL);
  }

  if (pct > 100)
  {
    return;
  }

  uint16_t New_CCR = 0 + (1000 - 0) / (100 - 0) * (pct - 0);

  /*调整PWM占空比*/
  __HAL_TIM_SET_COMPARE(&TIM_HANDLE, TIM_CHANNEL, New_CCR);
}

/**
 * @brief 查询DMA发送是否完成
 * @return {*}
 */
uint8_t Bsp_LCD_TX_InquireFinish(void)
{
#if (USE_FreeRTOS == 0)
  if (LCD_TX_DMA_FLAG == 0)
  {
    return 0;
  }
  else
  {
    LCD_TX_DMA_FLAG = 0;
    return 1;
  }
#else

  //osSemaphoreWait(LCD_BinarySemHandle, osWaitForever);

  return 1;

#endif
}

/**
 * @brief SPI发送完成中断
 * @param {SPI_HandleTypeDef} *hspi
 * @return {*}
 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
  if (hspi->Instance == SPI1)
  {
#if (USE_FreeRTOS == 0)
    LCD_TX_DMA_FLAG = 1;
#else
   // osSemaphoreRelease(LCD_BinarySemHandle);
    portYIELD_FROM_ISR(pdTRUE);
#endif
  }
}
