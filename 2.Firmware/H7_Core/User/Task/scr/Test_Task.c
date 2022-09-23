/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-09-08 14:31:33
 * @LastEditTime: 2022-09-23 16:56:32
 */
#include "Test_Task.h"

osThreadId_t Test_TaskHandle;
const osThreadAttr_t TestTask_attributes = {
    .name = "Test_Task",
    .stack_size = 1024 * 8,
    .priority = (osPriority_t)osPriorityHigh3,
    .attr_bits = osThreadDetached,
};

#include "Bsp_MCU_Flash.h"

uint8_t Flash_R[500] = {0};

/**
 * @brief 测试任务
 * @param {void} *argument
 * @return {*}
 */
void Test_Task(void *argument)
{
  /*NAND*/
  Bsp_Nand_Init();
	
	//User_FlashFS_Load();
	
	//User_FlashFS_ViewCapacity();

 // User_FlashFS_WriteFileTest();
  
  /*QSPI*/
  QSPI_W25Qx_Init();

 // QSPI_FLASH_Test_ReadSpeed();

	/*USB Drivers*/
	USBD_Initialize(0U);                 
	USBD_Connect   (0U); 

	taskENTER_CRITICAL();
	SCB_CleanInvalidateDCache();
  Bsp_MCU_FLASH_Read(0x08060000 , Flash_R , sizeof(Flash_R)); 

  Bsp_MCU_Flash_Erase(0x08060000 , 1);
  memset(Flash_R , 0 , sizeof(Flash_R));
	 SCB_CleanInvalidateDCache();
  Bsp_MCU_FLASH_Read(0x08060000 , Flash_R , sizeof(Flash_R));
  memset(Flash_R , 0 , sizeof(Flash_R));

 
  for(uint16_t i = 0 ; i< sizeof(Flash_R) ; i++)
  {
    Flash_R[i] = i & 0x00ff;
  }

  Bsp_MCU_Flash_Write(0x08060000 , Flash_R , sizeof(Flash_R));

  memset(Flash_R , 0 , sizeof(Flash_R));
	SCB_CleanInvalidateDCache();
  Bsp_MCU_FLASH_Read(0x08060000 , Flash_R , sizeof(Flash_R));
	Bsp_MCU_Flash_Erase(0x08060000 , 1);
	memset(Flash_R , 0 , sizeof(Flash_R));
	SCB_CleanInvalidateDCache();
	Bsp_MCU_FLASH_Read(0x08060000 , Flash_R , sizeof(Flash_R));
	taskEXIT_CRITICAL();
	
  for (;;)
  {
    osDelay(800);
  }
}



