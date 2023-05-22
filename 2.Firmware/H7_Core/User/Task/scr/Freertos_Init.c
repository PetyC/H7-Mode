/*
 * @Description:Freertos任务初始化
 * @Autor: Pi
 * @Date: 2022-09-06 01:28:00
 * @LastEditTime: 2022-10-10 18:05:02
 */
#include "freertos_Init.h"

/**
 * @brief 创建相关信号量
 * @return {*}
 */
static void Create_Sem(void)
{
  /*LCD二进制信号量*/
  LCD_BinarySemHandle = osSemaphoreNew(1, 0, &LCD_BinarySem_attributes);
 
}

/**
 * @brief 创建相关消息队列
 * @return {*}
 */
static void Create_Queue(void)
{
  /*按键消息*/
  KEY_QueueHandle = osMessageQueueNew(1, sizeof(uint8_t), &KEY_Queue_attributes);
		
	Network_QueueHandle = osMessageQueueNew(1, sizeof(uint8_t), &Network_Queue_attributes);
 
	Wifi_Set_QueueHandle = osMessageQueueNew(1, sizeof(uint8_t), &Wifi_Set_attributes);
	

}

/**
 * @brief 用于创建其他任务
 * @return {*}
 */
static void Create_Task(void)
{

  /*LED任务*/
  LED_TaskHandle = osThreadNew(LED_Task, NULL, &LEDTask_attributes);

  /*串口任务*/
  //Uart_TaskHandle = osThreadNew(Uart_Task, NULL, &UartTask_attributes);

  /*测试任务*/
  //Test_TaskHandle = osThreadNew(Test_Task, NULL, &TestTask_attributes);

  /*LCD任务*/
  LCD_TaskHandle  =  osThreadNew(LCD_Task, NULL, &LCDTask_attributes);

  /*网络任务*/
  NetWork_TaskHandle = osThreadNew(NetWork_Task, NULL, &NetWorkTask_attributes);

  /*更新检测任务*/
  //IAP_TaskHandle = osThreadNew(IAP_Task, NULL, &IAPTask_attributes);
}

/**
 * @brief Freertos初始化
 * @return {*}
 */
void Freertos_Init(void)
{
  /*配置MPU相关*/
  Bsp_MPU_Config();

  /*EventRecorder相关配置*/
#ifdef RTE_Compiler_EventRecorder
  EventRecorderInitialize(EventRecordAll, 1U);
  EventRecorderStart();
#endif

  /*挂起滴答定时器*/
  HAL_SuspendTick();

  /*初始化OS内核*/
  osKernelInitialize();

  /*恢复滴答定时器*/
  HAL_ResumeTick();

  /*创建信号量*/
  Create_Sem();

  /*创建消息队列*/
  Create_Queue();

  /*创建任务*/
  Create_Task();

  /*DWT定时器初始化*/
  DWT_Init();

  /*启动内核调度*/
  osKernelStart();

  /*正常情况不会运行到这*/
  for (;;)
  {
  };
}