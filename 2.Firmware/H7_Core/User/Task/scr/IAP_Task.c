/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-10-10 17:58:05
 * @LastEditTime: 2022-10-10 18:04:20
 */
#include "IAP_Task.h"

osThreadId_t IAP_TaskHandle;
const osThreadAttr_t IAPTask_attributes = {
    .name = "IAP_Task",
    .stack_size = 1024 * 4,
    .priority = (osPriority_t)osPriorityNormal,
    .attr_bits = osThreadDetached,
};


/**
 * @brief 定期检测更新
 * @return {*}
 */
void IAP_Task(void *argument)
{

  User_Config_Init();
  
	Config_Str Config;
  User_Config_Set(Config);
  for(;;)
  {
    osDelay(800);
  }
}