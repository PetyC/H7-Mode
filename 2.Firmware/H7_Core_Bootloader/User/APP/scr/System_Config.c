/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-10-12 13:56:28
 * @LastEditTime: 2022-10-12 15:12:11
 */
#include "System_Config.h"

/*系统设置*/
static System_Config Config;

/**
 * @brief 初始化系统配置信息
 * @return {*}
 */
void System_Config_Init(void)
{
  /*读取存储的系统信息*/
  QSPI_W25Qx_Read_Buffer(FLASH_DATA_ADDR, (uint8_t *)&Config, sizeof(System_Config));

  /*信息未初始化则进行初始化*/
  if (Config.Init != 0x67)
  {
    Config.Init = 0x67;
    Config.Updata = 0;
    Config.Error = 0;

    System_Config_Erase();
    System_Config_Set(Config);
  }
}

/**
 * @brief 擦除系统信息
 * @return {*}
 */
void System_Config_Erase(void)
{
  QSPI_W25Qx_EraseSector(FLASH_DATA_ADDR);
}

/**
 * @brief 设置新的系统信息
 * @param {Config_Str} info
 * @return {*}
 */
void System_Config_Set(System_Config Config)
{
  System_Config_Erase();

  /*以256字节 写入FLASH*/
  uint32_t Offset_Add = 0;
  for (uint32_t i = 0; i < sizeof(Config) / 256; i++)
  {
    QSPI_W25Qx_Write_Buffer(FLASH_DATA_ADDR + Offset_Add, (uint8_t *)&Config + Offset_Add, 256);
    Offset_Add += 256;
  }
  if (sizeof(Config) % 256 != 0)
  {
    QSPI_W25Qx_Write_Buffer(FLASH_DATA_ADDR + Offset_Add, (uint8_t *)&Config + Offset_Add, 256);
  }
}

/**
 * @brief 获取系统信息
 * @return {*}
 */
System_Config System_Config_Get(void)
{
  /*读取存储的系统信息*/
  QSPI_W25Qx_Read_Buffer(FLASH_DATA_ADDR, (uint8_t *)&Config, sizeof(System_Config));

  return Config;
}



 