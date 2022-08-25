/*
 * @Description: NetWork相关
 * @Autor: Pi
 * @Date: 2022-08-08 18:24:13
 * @LastEditTime: 2022-08-24 02:05:51
 */
#include "Network_Task.h"
#include "Bsp_Uart.h"

extern osMutexId Uart_MutexHandle;
extern osMessageQId KEY_QueueHandle;

/**
 * @brief FreeRTOS运行的任务
 * @param {void*} argument
 * @return {*}
 */
void Network_Task(void const *argument)
{
  char Buff[255];
  static uint8_t KEY_Value = 4;
  // static uint16_t rx_occupy = 0;
  static uint8_t WIFI_Connect_Flag = 0; // WIFI连接标志

  osMutexWait(Uart_MutexHandle, osWaitForever);

  /*ESP8266上电*/
  Bsp_ESP8266_PowerOn();
  
  osDelay(2000);
  
  /*关闭回显*/
  Bsp_ESP8266_Echo(0);

  /*开启按键功能*/
  Bsp_ESP8266_KEY_Enable(1);


  osMutexRelease(Uart_MutexHandle);

  // vTaskSuspend(NULL);

  for (;;)
  {
    //osMutexWait(Uart_MutexHandle, osWaitForever);

    while (Bsp_UART_Get_RX_Buff_Occupy(&huart1) != 0)
    {
      Bsp_ESP8266_ReadLine(Buff, sizeof(Buff), 1);

      if (memcmp(Buff, "KEY:", 4) == 0) //收到按键消息
      {
        KEY_Value = str_to_int(&Buff[4]);

        osMessagePut(KEY_QueueHandle , KEY_Value , osWaitForever) ;
      }
      else if ((memcmp(Buff, "WIFI CONNECTED\r\n", 4) == 0) || (memcmp(Buff, "WIFI GOT IP\r\n", 4) == 0)) // WIFI连接成功
      {
        WIFI_Connect_Flag = 1;
      }
      else if (memcmp(Buff, "WIFI DISCONNECTED\r\n", 4) == 0) // WIFI连接断开
      {
        WIFI_Connect_Flag = 0;
      }

      memset(Buff, NULL, sizeof(Buff));
    }

    //osMutexRelease(Uart_MutexHandle);
    osDelay(50);
  }
}
