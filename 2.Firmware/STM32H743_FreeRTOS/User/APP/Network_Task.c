/*
 * @Description: NetWork相关
 * @Autor: Pi
 * @Date: 2022-08-08 18:24:13
 * @LastEditTime: 2022-08-30 23:51:15
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

  uint32_t Network_TX_EventGroup = 0;
  uint8_t Network_TX_EventGroup_Last = 0;

  
  uint32_t Network_RX_EventGroup = 0;
  uint8_t Network_RX_EventGroup_Last = 0;

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
        Network_TX_EventGroup |= NETWORK_CONNECT_BIT0;
      }
      else if (memcmp(Buff, "WIFI DISCONNECTED\r\n", 4) == 0) // WIFI连接断开
      {
        Network_TX_EventGroup &= (~NETWORK_CONNECT_BIT0);
      }

      memset(Buff, NULL, sizeof(Buff));
    }

    /*如果任务事件组不一样，则发出通知*/
    if(Network_TX_EventGroup != Network_TX_EventGroup_Last)
    {
      xTaskNotify( LCD_TaskHandle, Network_TX_EventGroup, eSetBits);
      Network_TX_EventGroup_Last = Network_TX_EventGroup;
    }


    /*如果有任务通知*/
    if(xTaskNotifyWait( pdFALSE, ULONG_MAX, &Network_RX_EventGroup, 0) == pdTRUE)    //使用后不清空任务通知
    {
      if((Network_RX_EventGroup & NETWORK_WIFI_BIT0) == 1)    //连接WIFI
      {
        Bsp_ESP8266_SetWiFiMode(1);
        Bsp_ESP8266_JoinAP("CP02" , "6231380dd" , 2000);
      }
      else if((Network_RX_EventGroup & NETWORK_WIFI_BIT0) != 1)    //断开WIFI 
      {
        Bsp_ESP8266_QuitAP();
      }
    }

                       
    //osMutexRelease(Uart_MutexHandle);
    osDelay(50);
  }
}
