/*
 * @Description:Freertos任务初始化
 * @Autor: Pi
 * @Date: 2022-09-06 01:28:00
 * @LastEditTime: 2022-09-08 04:12:45
 */
#include "freertos_Init.h"

/*默认任务*/
static osThreadId_t Default_TaskHandle;
const osThreadAttr_t DefaultTask_attributes = {
    .name = "Default_Task",
    .stack_size = 1024 * 4,
    .priority = (osPriority_t)osPriorityNormal,
    .attr_bits = osThreadDetached,
};

#define DWT_CYCCNT *(volatile unsigned int *)0xE0001004
#define DWT_CR *(volatile unsigned int *)0xE0001000
#define DEM_CR *(volatile unsigned int *)0xE000EDFC
#define DBGMCU_CR *(volatile unsigned int *)0xE0042004
#define DEM_CR_TRCENA (1 << 24)
#define DWT_CR_CYCCNTENA (1 << 0)

#include "Bsp_Nand_Flash.h"
/**
 * @brief 默认任务，用于创建其他任务
 * @param {void} *argument
 * @return {*}
 */
static void Default_Task(void *argument)
{
  HAL_ResumeTick();

  //	DEM_CR         |= (unsigned int)DEM_CR_TRCENA;   /* Enable Cortex-M7's DWT CYCCNT reg. */
  //	DWT_CYCCNT      = (unsigned int)0u;
  //	DWT_CR         |= (unsigned int)DWT_CR_CYCCNTENA;

  /*创建其他任务*/
  LED_TaskHandle = osThreadNew(LED_Task, NULL, &LEDTask_attributes);

  Uart_TaskHandle = osThreadNew(Uart_Task, NULL, &UartTask_attributes);

  /*删除自身任务*/
  vTaskDelete(NULL);

  while (1)
    ;
}

void Freertos_Init(void)
{

#ifdef RTE_Compiler_EventRecorder
  EventRecorderInitialize(EventRecordAll, 1U);
  EventRecorderStart();
#endif

  HAL_SuspendTick();

  osKernelInitialize();

  /*创建默认任务*/
  Default_TaskHandle = osThreadNew(Default_Task, NULL, &DefaultTask_attributes);

  osKernelStart();

  while (1)
    ;
}