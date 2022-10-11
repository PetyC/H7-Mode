/*
 * @Description: IAP升级
 * @Autor: Pi
 * @Date: 2022-10-11 14:19:34
 * @LastEditTime: 2022-10-11 19:41:11
 */
#include "User_Boot.h"

/*APP跳转标志*/
uint32_t APP_Jump_Flag __attribute__((section(".bss.NoInit")));

/**
 * @brief 判断是否需要跳转至APP(需要放在main最前面)
 * @return {*}
 */
void User_Boot_Jump(void)
{
  /*判断是否跳转*/
  if (APP_Jump_Flag != APP_JUMP_VALUE)
  {
    return;
  }

  /* 声明一个函数指针 */
  void (*AppJump)(void);

  /* 跳转到应用程序，首地址是MSP，地址+4是复位中断服务程序地址 */
  AppJump = (void (*)(void))(*((uint32_t *)(MCU_FLASH_APP_ADDR + 4)));

  /* 设置主堆栈指针 */
  __set_MSP(*(uint32_t *)MCU_FLASH_APP_ADDR);

  /* 跳转到系统BootLoader */
  AppJump();

  /* 跳转成功的话，不会执行到这里，用户可以在这里添加代码 */
  while (1)
  {
  }
}

/**
 * @brief 设置跳转到APP
 * @return {*}
 */
void User_Boot_Set(void)
{
  /*设置全局标志*/
  APP_Jump_Flag = APP_JUMP_VALUE;

  /* 复位CPU */
  NVIC_SystemReset();
}

/**
 * @brief 将APP备份至外部Flash中
 * @return {uint8_t}0:成功    1:失败
 */
uint8_t User_Boot_App_Backup(void)
{
  uint8_t Data[256];

  /*擦除外置FLASH APP备份区 2MB*/
  for (uint32_t i = 0; i < (FLASH_BIN_SIZE / 4096); i++)
  {
    QSPI_W25Qx_EraseSector(FLASH_BIN_ADDR + (i * 4096));
  }

  /*将MCU内部APP备份到外置FLASH上*/
  for (uint32_t i = 0; i < MCU_FLASH_USER_SIZE / 256; i++)
  {
    if (Bsp_MCU_FLASH_Read(MCU_FLASH_APP_ADDR + (i * 256), Data, sizeof(Data)) == 0) //读取一页256字节
    {
      QSPI_W25Qx_Write_Buffer(FLASH_BIN_ADDR + (i * 256), Data, sizeof(Data)); //写入外置Flash
    }
    else
    {
      return 1;
    }
  }
  return 0;
}

/**
 * @brief 将外部Flash 待更新APP写入内部Flash完成更新
 * @return {uint8_t} 0:成功   1:失败
 */
uint8_t User_Boot_App_Updata(void)
{
  uint8_t Data[512];
  uint8_t Flash_Error = 0;

  /*将外部Flash数据写入内部FLASH*/
  for (uint32_t i = 0; i < FLASH_BIN_SIZE / 512; i++)
  {
    QSPI_W25Qx_Read_Buffer(FLASH_BIN_ADDR + (i * 512), Data, sizeof(Data));

    Flash_Error = Bsp_MCU_Flash_Write(MCU_FLASH_APP_ADDR + (i * 512), Data, sizeof(Data));

    if (Flash_Error == 1)
    {
      return 1;
    }
  }

  return 0;
}

/**
 * @brief CRC校验 APP数据
 * @param {uint32_t} APP_File_Size: app bin文件的大小 单位:字节
 * @return {uint8_t} 0:正确  1:错误
 */
uint8_t User_Boot_App_CRC(uint32_t APP_File_Size)
{
  __IO uint32_t Bin_CRC_Value;
  __IO uint32_t Ret_CRC_Value;

  /* 读取bin文件的CRC */
  Bin_CRC_Value = *(__IO uint32_t *)(MCU_FLASH_APP_ADDR + APP_File_Size - 4);

  /* 计算是否与硬件CRC一致 */
  Ret_CRC_Value = HAL_CRC_Calculate(&hcrc, (uint32_t *)MCU_FLASH_APP_ADDR, APP_File_Size / 4 - 1);

  if (Ret_CRC_Value != Bin_CRC_Value)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

#if 0
void User_App_Jump_Set_Demo(void)
{
  if(HAL_GPIO_ReadPin(KEY_GPIO_Port , KEY_Pin) == 1)
  {
    HAL_Delay(10);
    if(HAL_GPIO_ReadPin(KEY_GPIO_Port , KEY_Pin) == 1)
    {
      User_App_Jump_Set();
    }
  }
}

void User_App_Jump_Demo(void)
{
  /*判断是否跳转*/
  if (APP_Jump_Flag != APP_JUMP_VALUE)
  {
    HAL_GPIO_WritePin(LED2_GPIO_Port , LED2_Pin , 0);
    return;
  }

  /*模拟跳转*/
  HAL_GPIO_WritePin(LED1_GPIO_Port , LED1_Pin , 0);

  while(1);
}
#endif