/*
 * @Description:Freertos任务初始化
 * @Autor: Pi
 * @Date: 2022-09-06 01:28:00
 * @LastEditTime: 2022-09-22 20:00:46
 */
#include "freertos_Init.h"

#define DWT_CR *(volatile unsigned int *)0xE0001000
#define DEM_CR *(volatile unsigned int *)0xE000EDFC
#define DBGMCU_CR *(volatile unsigned int *)0xE0042004
#define DWT_CYCCNT *(volatile unsigned int *)0xE0001004 //显示或设置处理器的周期计数值
#define DEM_CR_TRCENA (1 << 24)                         // DEMCR的DWT使能位
#define DWT_CR_CYCCNTENA (1 << 0)                       // DWT的SYCCNT使能位

void DWT_Init(void)
{
  DEM_CR |= (unsigned int)DEM_CR_TRCENA;
  DWT_CYCCNT = (unsigned int)0u;
  DWT_CR |= (unsigned int)DWT_CR_CYCCNTENA;
}

/**
 * @brief 配置MPU
 * @return {*}
 */
void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* 禁止 MPU */
  HAL_MPU_Disable();

#if 1
  /* 配置AXI SRAM的MPU属性为Write through, read allocate，no write allocate */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x24000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_512KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
#else
  /*Normal 性能最差 但可以随意操作SRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x24000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_512KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL1;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
#endif

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* 用于NAND Flash */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x80000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_512MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /*使能 MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}

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
  KEY_QueueHandle = osMessageQueueNew (3, sizeof(uint8_t), &KEY_Queue_attributes);

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
  Uart_TaskHandle = osThreadNew(Uart_Task, NULL, &UartTask_attributes);

  /*测试任务*/
  Test_TaskHandle = osThreadNew(Test_Task, NULL, &TestTask_attributes);

  /*LCD任务*/
  LCD_TaskHandle  =  osThreadNew(LCD_Task, NULL, &LCDTask_attributes);

  /*网络任务*/
  NetWork_TaskHandle = osThreadNew(NetWork_Task, NULL, &NetWorkTask_attributes);
 
}

/**
 * @brief Freertos初始化
 * @return {*}
 */
void Freertos_Init(void)
{
	/*配置MPU相关*/
  MPU_Config();

  /* 使能 I-Cache */
  SCB_EnableICache();

  /* 使能 D-Cache */
  SCB_EnableDCache();

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

  // DWT_Init();
  
  /*创建信号量*/
  Create_Sem();

  /*创建消息队列*/
  Create_Queue();

  
  /*创建任务*/
  Create_Task();

  osKernelStart();
																				
  for (;;)
  {
  };
}