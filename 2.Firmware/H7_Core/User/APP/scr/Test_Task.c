/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-09-08 14:31:33
 * @LastEditTime: 2022-09-10 18:45:13
 */
#include "Test_Task.h"

osThreadId_t Test_TaskHandle;
const osThreadAttr_t TestTask_attributes = {
    .name = "Test_Task",
    .stack_size = 1024 * 8,
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
  /*NAND*/
  Bsp_Nand_Init();
//	
//	User_FlashFS_Load();
	
//	User_FlashFS_ViewCapacity();

 // User_FlashFS_WriteFileTest();
  
  /*QSPI*/
  QSPI_W25Qx_Init();

//  QSPI_FLASH_Test_ReadSpeed();
  
	/*USB Drivers*/

	
 
	/*LCD*/
	LCD_Init();
	
  for (;;)
  {
    osDelay(800);
  }
}



