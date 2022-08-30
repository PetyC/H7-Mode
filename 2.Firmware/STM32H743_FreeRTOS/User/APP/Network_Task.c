/*
 * @Description: NetWork相关
 * @Autor: Pi
 * @Date: 2022-08-08 18:24:13
 * @LastEditTime: 2022-08-30 19:55:24
 */
#include "Network_Task.h"
#include "Bsp_Uart.h"

extern osMutexId Uart_MutexHandle;
extern osMessageQId KEY_QueueHandle;
extern osThreadId LCD_TaskHandle;


/**
 * @brief FreeRTOS运行的任务
 * @param {void*} argument
 * @return {*}
 */
void Network_Task(void const *argument)
{
  char Buff[255];
  static uint8_t KEY_Value = 4;

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

  uint32_t Network_EventGroup = 0;
  uint8_t Network_EventGroup_Last = 0;

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
        Network_EventGroup = NETWORK_CONNECT_BIT0;
      }
      else if (memcmp(Buff, "WIFI DISCONNECTED\r\n", 4) == 0) // WIFI连接断开
      {
        Network_EventGroup = NETWORK_DISCONNECT_BIT1;
      }

      memset(Buff, NULL, sizeof(Buff));
    }

    /*如果任务事件组不一样，则发出通知*/
    if(Network_EventGroup != Network_EventGroup_Last)
    {
      xTaskNotify( LCD_TaskHandle, Network_EventGroup, eSetBits);
      Network_EventGroup_Last = Network_EventGroup;
    }

                       
    //osMutexRelease(Uart_MutexHandle);
    osDelay(50);
  }
}
