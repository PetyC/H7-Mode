/*
 * @Description: 网络任务
 * @Autor: Pi
 * @Date: 2022-09-22 19:54:11
 * @LastEditTime: 2022-09-23 15:37:38
 */
#include "Network_Task.h"


osThreadId_t NetWork_TaskHandle;
const osThreadAttr_t NetWorkTask_attributes = {
    .name = "NetWork_Task",
    .stack_size = 1024 * 4,
    .priority = (osPriority_t)osPriorityNormal7,
    .attr_bits = osThreadDetached,
};


osMessageQueueId_t KEY_QueueHandle;
const osMessageQueueAttr_t KEY_Queue_attributes = {
  .name = "KEY_Queue"
};


static void NetWork_Core(void);

/**
 * @brief 网络任务
 * @param {void} *argument
 * @return {*}
 */
void NetWork_Task(void *argument)
{
  NetWork_Init();
  
  for (;;)
  {
		NetWork_Core();
    osDelay(5);

    if(Network.AP_Connect == Link)
    {
      HAL_GPIO_WritePin(LED2_GPIO_Port , LED2_Pin , GPIO_PIN_RESET);
    }
    else
    {
      HAL_GPIO_WritePin(LED2_GPIO_Port , LED2_Pin , GPIO_PIN_SET);
    }
  }
}



/**
 * @brief 网络核心 需要放在循环中
 * @return {*}
 */
void NetWork_Core(void)
{
  char Buff[255];

  while (Bsp_UART_Get_RX_Buff_Occupy(&huart1) != 0)
  {
    Bsp_ESP8266_ReadLine(Buff, sizeof(Buff), 1);

    if (memcmp(Buff, "KEY:", 4) == 0) //收到按键消息
    {
      uint8_t KEY_Value = str_to_int(&Buff[4]);
      /*发送按键消息*/
      osMessageQueuePut(KEY_QueueHandle , &KEY_Value , NULL , NULL);
    }
    else if ((memcmp(Buff, "WIFI CONNECTED\r\n", 4) == 0) || (memcmp(Buff, "WIFI GOT IP\r\n", 4) == 0)) // WIFI连接成功
    {
      Network.AP_Connect = Link;
    
    }
    else if (memcmp(Buff, "WIFI DISCONNECTED\r\n", 4) == 0) // WIFI连接断开
    {
      Network.AP_Connect = UnLink;
    }
  }

}