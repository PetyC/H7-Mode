/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-08-18 18:50:19
 * @LastEditTime: 2022-08-19 19:23:58
 */
#include "bsp_Demo.h"

#if USE_FreeRTOS == 1
#include "FreeRTOS.h"
#include "task.h"
#endif

/*内部使用函数*/
static void Bsp_LCD_Delay(uint16_t delay);
 

/**
 * @brief LCD延时函数
 * @param {uint16_t} delay
 * @return {*}
 */
static void Bsp_LCD_Delay(uint16_t delay)
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
void Bsp_LCD_Reset(void)
{
  LCD_RES_Low();
  Bsp_LCD_Delay(100);
  LCD_RES_High();
  Bsp_LCD_Delay(50);
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
  CMD[1] = data & 0XFF;

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
  CMD[1] = data & 0XFF;

  LCD_DC_High();
  HAL_SPI_Transmit(&SPI_HANDLE, CMD, 2, 0xFF);
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
  // __HAL_DMA_GET_FLAG(&DMA_HANDLE ,DMA_FLAG_TCIF0_4);//传输完成返回1，否则返回0
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
 * @brief LCD初始化工作,适用芯片ST7735S
 * @param {*}
 * @return {*}
 */
void Bsp_LCD_Init(void)
{

  Bsp_LCD_Reset();
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
void Bsp_LCD_SetRegion(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end)
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
void Bsp_LCD_SetXY(uint16_t x, uint16_t y)
{
  Bsp_LCD_SetRegion(x,y,x,y);
}

/**
 * @brief 画一个点
 * @param {uint16_t} x
 * @param {uint16_t} y
 * @param {uint16_t} Data
 * @return {*}
 */
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data)
{
	Bsp_LCD_SetRegion(x,y,x+1,y+1);
  Bsp_LCD_SendData_16B(Data);
} 


#define LCD_Buff_Len (uint16_t)(X_MAX_PIXEL * Y_MAX_PIXEL * 2)
static uint16_t LCD_Buff[LCD_Buff_Len] __attribute__((section(".ARM.__at_0x24000000")));

/**
 * @brief 全屏填充颜色 
 * @param {uint16_t} Color 
 * @return {*}
 */
void Bsp_LCD_FullColor(uint16_t Color)               
{	
	//memset(LCD_Buff , Color , sizeof(LCD_Buff));

  for(uint16_t i = 0 ; i < LCD_Buff_Len ; i++)
  {
    LCD_Buff[i] = Color;
  }
  
	Bsp_LCD_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);

  LCD_DC_High();

  //Bsp_LCD_Send_DMA( (uint8_t *)LCD_Buff, LCD_Buff_Len);
   //HAL_SPI_Transmit(&SPI_HANDLE, (uint8_t *)LCD_Buff, LCD_Buff_Len , 0xff);
  
  HAL_SPI_Transmit_DMA(&SPI_HANDLE, (uint8_t *)LCD_Buff, LCD_Buff_Len);
  //HAL_SPI_Transmit_DMA(&SPI_HANDLE, LCD_Buff, LCD_Buff_Len);
  
 
  /*等待发送完成*/
  while(HAL_DMA_GetState(&DMA_HANDLE) != HAL_DMA_STATE_READY);
  
  /*发送完毕后拉低命令引脚*/
  LCD_DC_Low();
}
