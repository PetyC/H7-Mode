/*
 * @Description: 网络任务
 * @Autor: Pi
 * @Date: 2022-09-22 19:54:11
 * @LastEditTime: 2023-05-23 02:25:08
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

osSemaphoreId_t Network_QueueHandle;
const osMessageQueueAttr_t Network_Queue_attributes = {
    .name = "Network_Queue"};


osSemaphoreId_t Wifi_Set_QueueHandle;
const osMessageQueueAttr_t Wifi_Set_attributes = {
    .name = "Wifi_Set_Queue"};


static void NetWork_Core(void);

/**
 * @brief 网络任务
 * @param {void} *argument
 * @return {*}
 */
void NetWork_Task(void *argument)
{
  NetWork_Init();
  
  AP_Connect_E network_sta_last = UnNetLink;
  uint8_t wifi_set = 0;

  for (;;)
  {
		NetWork_Core();
    osDelay(50);

		if(osMessageQueueGet(Wifi_Set_QueueHandle , &wifi_set , 0 , 0) == osOK)
		{
			if(wifi_set == 1)
			{
				Bsp_ESP8266_JoinAP(Network.AP.ssid ,Network.AP.pwd , 2000);
				Network.AP_Connect = (AP_Connect_E)NetWork_QueryLink();
				
			}
			else
			{
				Bsp_ESP8266_QuitAP();  
				Network.AP_Connect = UnLink;
			}	
		}

		if(Network.AP_Connect != network_sta_last)
		{
			if(Network.AP_Connect == Link)
			{
				HAL_GPIO_WritePin(LED1_GPIO_Port , LED1_Pin , GPIO_PIN_SET);      
			}
			else
			{
				HAL_GPIO_WritePin(LED1_GPIO_Port , LED1_Pin , GPIO_PIN_RESET);
			}
			osMessageQueuePut(Network_QueueHandle , &Network.AP_Connect , NULL , NULL); 
		}
		network_sta_last = Network.AP_Connect;

  }
}



/**
 * @brief 网络核心 需要放在循环中
 * @return {*}
 */
void NetWork_Core(void)
{
  char Buff[255];

	char wifi_link_sta_cmd_0[] =  "WIFI CONNECTED";
  char wifi_link_sta_cmd_1[] =  "WIFI GOT IP";
	char wifi_unlink_sta_cmd[] =  "WIFI DISCONNECT";


  while (Bsp_UART_Get_RX_Buff_Occupy(&huart1) != 0)
  {
    uint16_t size = Bsp_ESP8266_ReadLine(Buff, sizeof(Buff), 1);

    if (memcmp(Buff, "KEY:", 4) == 0) //收到按键消息
    {
      uint8_t KEY_Value = str_to_int(&Buff[4]);
      /*发送按键消息*/
      osMessageQueuePut(KEY_QueueHandle , &KEY_Value , NULL , NULL);
    }
    else if ((memcmp(Buff, wifi_link_sta_cmd_0 , 14) == 0) || (memcmp(Buff, wifi_link_sta_cmd_1, 11) == 0)) // WIFI连接成功
    {
      Network.AP_Connect = Link;
    }
    else if (memcmp(Buff, wifi_unlink_sta_cmd , 15) == 0) // WIFI连接断开
    {
      Network.AP_Connect = UnLink;
    }
  }

}