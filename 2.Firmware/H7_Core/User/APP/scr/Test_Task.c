/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-09-08 14:31:33
 * @LastEditTime: 2022-09-09 19:43:39
 */
#include "Test_Task.h"

osThreadId_t Test_TaskHandle;
const osThreadAttr_t TestTask_attributes = {
    .name = "Test_Task",
    .stack_size = 1024 * 5,
    .priority = (osPriority_t)osPriorityHigh3,
    .attr_bits = osThreadDetached,
};

/**
 * @brief 测试任务
 * @param {void} *argument
 * @return {*}
 */
void Test_Task(void *argument)
{

  Bsp_Nand_Init();

  for (;;)
  {
    osDelay(800);
  }
}