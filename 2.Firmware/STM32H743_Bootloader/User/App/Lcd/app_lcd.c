/*
 * @Description: LCD显示APP
 * @Autor: Pi
 * @Date: 2022-07-04 14:40:53
 * @LastEditTime: 2022-07-04 15:56:11
 */
#include "app_lcd.h"

/**
 * @brief 系统UI界面初始化显示
 * @return {*}
 */
void UI_Init_Display(void)
{
  setOrientation(R0);
  setColor(0, 0, 0);
  fillScreen();

  setColor(0, 0xff, 00);
  setbgColor(0, 0, 0);
  setFont(ter_u12b);
  drawText(0, 0, "BootLoader");
  drawText(0, STATE_DISPLAY_LINE, "System:Update_APP");
  drawText(0, ADD_DISPLAY_LINE, "APP Addr:Wait");
  drawText(0, SIZE_DISPLAY_LINE, "APP Size:Wait");
  drawText(0, ERASE_DISPLAY_LINE, "Flash Erase:Wait");
  drawText(0, WRITE_DISPLAY_LINE, "Flash Write:Wait");
  //drawText(0, 12 * 6, "Jump APP:");
  flushBuffer();
}

/**
 * @brief App Bin文件相关显示
 * @return {*}
 */
void UI_File_Display(uint32_t ADDR , uint32_t File_Size)
{
  char Temp[30];
  /*显示APP起始地址*/
  sprintf(Temp, "0X%x", ADDR);
  drawText(10 * 6, ADD_DISPLAY_LINE , Temp);

  memset(Temp, 0, sizeof(Temp));

  /*显示APP文件大小*/
  sprintf(Temp, "%d", File_Size);
  drawText(10 * 6, SIZE_DISPLAY_LINE, Temp);

  flushBuffer();
}


/**
 * @brief Flash相关状态显示
 * @param {uint8_t} Erase_State 擦除状态
 * @param {uint8_t} Write_State 写入状态
 * @return {*}
 */
void UI_Falsh_Display(uint8_t Erase_State , uint8_t Write_State)
{
  /*FLASH 擦除*/
  //drawText(13 * 6, ERASE_DISPLAY_LINE, "Wait");

  /*FLASH 写入*/
  //drawText(13 * 6, WRITE_DISPLAY_LINE, "Wait");

  /*FLASH擦状态*/
  if(Erase_State == 0)
  {
    drawText(13 * 6, ERASE_DISPLAY_LINE, "OK     ");
  }
  else
  {
    drawText(13 * 6, ERASE_DISPLAY_LINE, "Error");
  }


  /*FLASH写状态*/
  if(Write_State == 0)
  {
    drawText(13 * 6, WRITE_DISPLAY_LINE, "OK     ");
  }
  else
  {
     drawText(13 * 6, WRITE_DISPLAY_LINE, "Error");
  }

  flushBuffer();
}






/**
 * @brief UI 跳转倒计时 阻塞方式
 * @param {uint8_t} Count   倒计时数
 * @return {*}
 */
void UI_Count_Down_Display(uint8_t Count)
{
  for (uint8_t i = Count; i > 0; i--)
  {
    char Number;
    sprintf(&Number, "%d", i);
    drawText(10 * 6, 12 * 6, &Number);
    flushBuffer();
    HAL_Delay(1000);
  }
}
