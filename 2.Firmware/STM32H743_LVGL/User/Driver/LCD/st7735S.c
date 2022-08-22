#include "st7735s.h"


#define LCD_Buff_Len (uint16_t)(X_MAX_PIXEL * Y_MAX_PIXEL)
static uint16_t LCD_Buff[LCD_Buff_Len] __attribute__((section(".ARM.__at_0x24000000")));

/*发送完成标志*/
uint8_t LCD_TX_DMA_FLAG = 0;


/**
 * @brief LCD背光控制
 * @param {uint8_t} pct
 * @return {*}
 */
void LCD_BacklightPct(uint8_t pct)
{
  Bsp_LCD_BacklightPct(pct);
}

/**
 * @brief LCD复位
 * @return {*}
 */
void LCD_Reset(void)
{
  LCD_RES_Low();
  Bsp_LCD_Delay(100);
  LCD_RES_High();
  Bsp_LCD_Delay(50);
}

/**
 * @brief LCD初始化工作,适用芯片ST7735S
 * @param {*}
 * @return {*}
 */
void LCD_Init(void)
{

  LCD_Reset();
  Bsp_LCD_SendCmd_8B(0x11); //退出休眠
  Bsp_LCD_Delay(120);

  /*ST7735S Frame Rate*/
  Bsp_LCD_SendCmd_8B(0xB1);
  Bsp_LCD_SendData_8B(0x02);
  Bsp_LCD_SendData_8B(0x35);
  Bsp_LCD_SendData_8B(0x36);

  Bsp_LCD_SendCmd_8B(0xB2);
  Bsp_LCD_SendData_8B(0x02);
  Bsp_LCD_SendData_8B(0x35);
  Bsp_LCD_SendData_8B(0x36);

  Bsp_LCD_SendCmd_8B(0xB3);
  Bsp_LCD_SendData_8B(0x02);
  Bsp_LCD_SendData_8B(0x35);
  Bsp_LCD_SendData_8B(0x36);
  Bsp_LCD_SendData_8B(0x02);
  Bsp_LCD_SendData_8B(0x35);
  Bsp_LCD_SendData_8B(0x36);

  /*开启反转*/
  Bsp_LCD_SendCmd_8B(0xB4);
  Bsp_LCD_SendData_8B(0x03);

  /*电源设置*/
  Bsp_LCD_SendCmd_8B(0xC0);
  Bsp_LCD_SendData_8B(0xA2);
  Bsp_LCD_SendData_8B(0x02);
  Bsp_LCD_SendData_8B(0x84);

  Bsp_LCD_SendCmd_8B(0xC1);
  Bsp_LCD_SendData_8B(0xC5);

  Bsp_LCD_SendCmd_8B(0xC2);
  Bsp_LCD_SendData_8B(0x0D);
  Bsp_LCD_SendData_8B(0x00);

  Bsp_LCD_SendCmd_8B(0xC3);
  Bsp_LCD_SendData_8B(0x8D);
  Bsp_LCD_SendData_8B(0x2A);

  Bsp_LCD_SendCmd_8B(0xC4);
  Bsp_LCD_SendData_8B(0x8D);
  Bsp_LCD_SendData_8B(0xEE);

  /*VCOM*/
  Bsp_LCD_SendCmd_8B(0xC5);
  Bsp_LCD_SendData_8B(0x0a);

  /*显示方向*/
  Bsp_LCD_SendCmd_8B(0x36);
#if (USE_HORIZONTAL == 0)
  Bsp_LCD_SendData_8B(0x08);
#elif (USE_HORIZONTAL == 1)
  Bsp_LCD_SendData_8B(0xC8);
#elif (USE_HORIZONTAL == 2)
  Bsp_LCD_SendData_8B(0x78);
#else
  Bsp_LCD_SendData_8B(0xA8);
#endif

  /*ST7735S Gamma Sequence*/
  uint8_t Set_Gamma_Sequence_CMD0[] = {0x12, 0x1C, 0x10, 0x18, 0x33, 0x2C, 0x25, 0x28, 0x28, 0x27, 0x2F, 0x3C, 0x00, 0x03, 0x03, 0x10}; //伽马 + 矫正
  uint8_t Set_Gamma_Sequence_CMD1[] = {0x12, 0x1C, 0x10, 0x18, 0x2D, 0x28, 0x23, 0x28, 0x28, 0x26, 0x2F, 0x3B, 0x00, 0x03, 0x03, 0x10}; //伽马 - 矫正

  Bsp_LCD_SendCmd_8B(0XE0);
  Bsp_LCD_SendData(Set_Gamma_Sequence_CMD0, sizeof(Set_Gamma_Sequence_CMD0));

  Bsp_LCD_SendCmd_8B(0XE1);
  Bsp_LCD_SendData(Set_Gamma_Sequence_CMD1, sizeof(Set_Gamma_Sequence_CMD1));

  /*65k mode*/
  Bsp_LCD_SendCmd_8B(0x3A);
  Bsp_LCD_SendData_8B(0x05);

  /*显示启用*/
  Bsp_LCD_SendCmd_8B(0x29);

  Bsp_LCD_BacklightPct(70); //打开背光
}

/**
 * @brief 设置lcd显示区域，在此区域写点数据自动换行
 * @param {uint16_t} x_start
 * @param {uint16_t} y_start
 * @param {uint16_t} x_end
 * @param {uint16_t} y_end
 * @return {*}
 */
void LCD_SetRegion(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end)
{
  uint8_t Points_X[4] = {0x00, x_start, 0x00, x_end};
  uint8_t Points_Y[4] = {0x00, y_start, 0x00, y_end};

  Bsp_LCD_SendCmd_8B(0x2a);
  Bsp_LCD_SendData(Points_X, sizeof(Points_X));

  Bsp_LCD_SendCmd_8B(0x2b);
  Bsp_LCD_SendData(Points_Y, sizeof(Points_Y));

  Bsp_LCD_SendCmd_8B(0x2c);
}

/**
 * @brief 设置lcd显示起始点
 * @param {uint16_t} x
 * @param {uint16_t} y
 * @return {*}
 */
void LCD_SetXY(uint16_t x, uint16_t y)
{
  LCD_SetRegion(x, y, x, y);
}

/**
 * @brief 画一个点
 * @param {uint16_t} x
 * @param {uint16_t} y
 * @param {uint16_t} Data
 * @return {*}
 */
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t Data)
{
  LCD_SetRegion(x, y, x + 1, y + 1);
  Bsp_LCD_SendData_16B(Data);
}

/**
 * @brief 全屏填充颜色
 * @param {uint16_t} Color
 * @return {*}
 */
void LCD_FullColor(uint16_t Color)
{
  LCD_SetRegion(0, 0, X_MAX_PIXEL - 1, Y_MAX_PIXEL - 1);

  LCD_DC_High();

  LCD_TX_DMA_FLAG = 0;
  Bsp_LCD_SPI_SET16B();
  Bsp_LCD_DMA_SetMemInc(0);
  
  Bsp_LCD_Send_DMA( (uint8_t *)&Color, LCD_Buff_Len);
  
  /*等待发送完成*/
  while (LCD_TX_DMA_FLAG == 0);
  
  /*发送完毕后拉低命令引脚*/
  LCD_DC_Low();

  Bsp_LCD_SPI_SET8B();
}

/**
 * @brief 全屏显示图片
 * @param {uint16_t} *Images
 * @return {*}
 */
void LCD_DisplayImages(uint16_t *Images)
{
  LCD_SetRegion(0, 0, X_MAX_PIXEL - 1, Y_MAX_PIXEL - 1);
  LCD_DC_High();

  LCD_TX_DMA_FLAG = 0;
  Bsp_LCD_SPI_SET16B();
  Bsp_LCD_DMA_SetMemInc(1);

  Bsp_LCD_Send_DMA( (uint8_t *)&Images, LCD_Buff_Len);

  /*等待发送完成*/
  while (LCD_TX_DMA_FLAG == 0);

  
  /*发送完毕后拉低命令引脚*/
  LCD_DC_Low();

  Bsp_LCD_SPI_SET8B();
}


/**
 * @brief 某个区域填充颜色
 * @param {uint16_t} x_start
 * @param {uint16_t} y_start
 * @param {uint16_t} x_end
 * @param {uint16_t} y_end
 * @param {uint16_t} *data
 * @return {*}
 */
void LCD_FillColor(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end , uint16_t *data)
{
  LCD_SetRegion(x_start,  y_start,  x_end,  y_end);

  uint16_t height = 0;
  uint16_t width = 0;

  width = x_end- x_start + 1;
  height = y_end - y_start + 1;


  LCD_DC_High();
  //Bsp_LCD_DMA_SetMemInc(1);
  Bsp_LCD_SPI_SET16B();

  HAL_SPI_Transmit(&SPI_HANDLE , (uint8_t *)data, (width * height) , 0XFF);
 // Bsp_LCD_Send_DMA((uint8_t *)data, (width * height));
  /*发送完毕后拉低命令引脚*/
  LCD_DC_Low();

  Bsp_LCD_SPI_SET8B();

}