/*
 * @Description: 系统配置文件
 * @Autor: Pi
 * @Date: 2022-07-14 15:41:44
 * @LastEditTime: 2022-10-09 00:47:49
 */
#include "User_config.h"

/*系统信息存储*/
Config_Str System_Config;

/**
 * @brief Boot初始化，读取外置FLASH判断是否需要升级，若不需要升级则跳入APP
 * @return {*}
 */
void User_Config_Init(void)
{
  /*读取存储的系统信息*/
  QSPI_W25Qx_Read_Buffer(FLASH_DATA_ADDR, (uint8_t *)&System_Config, sizeof(Config_Str));

  /*信息未初始化则进行初始化*/
  if ((System_Config.Init != 1) && (System_Config.Init != 0))
  {
    QSPI_W25Qx_EraseSector(FLASH_DATA_ADDR);

    System_Config.Init = 1;
    System_Config.Updata = 0;
    System_Config.Inquire = 1;
    System_Config.Error = 0;
    System_Config.Info.Bin_Size = 0;
    System_Config.Info.Port = 80;
    System_Config.Info.SSLEN = 0;

    memcpy(System_Config.Info.Version, "0.0.0", 6);
    memcpy(System_Config.Info.IP, "www.qiandpi.com", 16);
    // memcpy(System_Config.Info.Bin_Path , NULL , 0);
    memcpy(System_Config.Info.Info_Path, "/ota/hardware/H7-Core/info.txt", 31);

    uint16_t Len = sizeof(Config_Str);
    uint32_t Offset_Add = 0;

    /*以256字节 写入FLASH*/
    for (uint32_t i = 0; i < Len / 256; i++)
    {
      QSPI_W25Qx_Write_Buffer(FLASH_DATA_ADDR + Offset_Add, (uint8_t *)&System_Config + Offset_Add, 256);
      Offset_Add += 256;
    }
    if (Len % 256 != 0)
    {
      QSPI_W25Qx_Write_Buffer(FLASH_DATA_ADDR + Offset_Add, (uint8_t *)&System_Config + Offset_Add, 256);
    }
  }
}

/**
 * @brief 将新的INFO信息写入FALSH
 * @param {Config_Str} info
 * @return {*}
 */
void User_Config_Set(Config_Str System_Config)
{
  QSPI_W25Qx_EraseSector(FLASH_DATA_ADDR);

  uint16_t Len = sizeof(Config_Str);
  uint32_t Offset_Add = 0;

  /*以256字节 写入FLASH*/
  for (uint32_t i = 0; i < Len / 256; i++)
  {
    QSPI_W25Qx_Write_Buffer(FLASH_DATA_ADDR + Offset_Add, (uint8_t *)&System_Config + Offset_Add, 256);
    Offset_Add += 256;
  }
  if (Len % 256 != 0)
  {
    QSPI_W25Qx_Write_Buffer(FLASH_DATA_ADDR + Offset_Add, (uint8_t *)&System_Config + Offset_Add, 256);
  }
}
