/*
 * @Description: Bootloader跳转到APP程序
 * @Autor: Pi
 * @Date: 2022-07-01 16:53:36
 * @LastEditTime: 2022-07-25 20:44:00
 */
#include "IAP.h"
#include <stdio.h>

/*HAL库相关句柄*/
extern CRC_HandleTypeDef hcrc;

/*APP跳转标志*/
uint32_t APP_Jump_Flag __attribute__((at(0x20000000), zero_init));

/*系统升级状态*/
Flash_State_Str Flash_State = {0,0};



/**
 * @brief 启动跳转到APP
 * @return {*}
 */
void User_App_Jump_Start(void)
{
  /*设置全局标志*/
  APP_Jump_Flag = APP_JUMP_VALUE;

  /* 复位CPU */
  NVIC_SystemReset();
}


/**
 * @brief 跳转到APP应用
 * @return {*}
 */
void User_App_Jump_Init(void)
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
 * @brief 擦除APP占用扇区
 * @param {uint32_t} APP_File_Size    APP Bin文件大小(单位 字节)
 * @return {uint8_t} 0:成功  1:失败
 */
uint8_t User_App_MCU_Flash_Erase(uint32_t APP_File_Size)
{
  /*APP Bin文件占用几个整数扇区*/
  uint32_t APP_File_Sector_Count = APP_File_Size / (128 * 1024);

  /*APP Bin文件占用整数扇区剩余数*/
  uint32_t APP_File_Sector_Remain = APP_File_Size % (128 * 1024);

  if (APP_File_Sector_Remain != 0)
  {
    APP_File_Sector_Count++;
  }

  /*擦除APP占有扇区*/
  if (Bsp_MCU_Flash_Erase(MCU_FLASH_APP_ADDR, APP_File_Sector_Count) == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}


/**
 * @brief 从串口接收APP数据 并写入内部FALSH中
 * @param {uint8_t} *data
 * @param {uint16_t} len
 * @return {*}
 */
void User_App_MCU_Flash_Updata(uint8_t *data , uint16_t len)
{
  /*APP写入偏移地址*/
  static uint32_t Offset_ADDR = 0;

  /*写入MCU Flash*/
  uint8_t Error = Bsp_MCU_Flash_Write(MCU_FLASH_APP_ADDR + Offset_ADDR, data, len);

  /*写入地址自增*/
  Offset_ADDR += len;

  /*写入地址大于解析地址，则也说明固件下载完成*/
  if(Offset_ADDR >= System_Config.Info.Bin_Size)   //System_Config.Info.Bin_Size
  {
    Flash_State.Finish = 1;
  }	
	
	
  /*FLASH写入出错*/
  if(Error == 1)
  {
    Flash_State.Error = 1;
  }

}




/**
 * @brief 将APP备份至外部Flash中
 * @return {uint8_t}0:成功    1:失败
 */
uint8_t User_App_MCU_Flash_Copy(void)
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
 * @brief 将外部Flash备份数据写入内部Flash
 * @return {*}
 */
uint8_t User_App_Flash_Copy(void)
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
 * @brief CRC校验写入FLASH数据
 * @param {uint32_t} APP_File_Size: app bin文件的大小 单位:字节
 * @return {uint8_t} 0:正确  1:错误
 */
uint8_t User_App_MCU_Flash_CRC(uint32_t APP_File_Size)
{
  __IO uint32_t Bin_CRC_Value;
  __IO uint32_t Ret_CRC_Value;

  /* 读取bin文件的CRC */
  Bin_CRC_Value = *(__IO uint32_t *)(MCU_FLASH_APP_ADDR + APP_File_Size - 4);

  /* 计算是否与硬件CRC一致 */
  Ret_CRC_Value = HAL_CRC_Calculate(&hcrc, ( uint32_t *)MCU_FLASH_APP_ADDR, APP_File_Size/4 - 1);

  if (Ret_CRC_Value != Bin_CRC_Value)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}




/**
 * @brief IAP初始化，判断是否需要跳转
 * @return {*}
 */
void User_IAP_Init(void)
{
  
}

