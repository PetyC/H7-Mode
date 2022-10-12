#include "IAP.h"

/*APP跳转标志*/
static uint32_t APP_Jump_Flag __attribute__((section(".bss.NoInit")));

/**
 * @brief 判断是否需要跳转至APP(需要放在main最前面)
 * @return {*}
 */
void IAP_Jump_Init(void)
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
void IAP_Jump_Start(void)
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
uint8_t IAP_App_Backup(void)
{
  uint8_t Data[256];

  /*擦除外置FLASH APP备份区 2MB*/
  IAP_App_Erase(0);

  /*将MCU内部APP备份到外置FLASH上*/
  for (uint32_t i = 0; i < FLASH_BACKUP_SIZE / 256; i++)
  {
    if (Bsp_MCU_FLASH_Read(MCU_FLASH_APP_ADDR + (i * 256), Data, sizeof(Data)) == 0) //读取一页256字节
    {
      QSPI_W25Qx_Write_Buffer(FLASH_BACKUP_ADDR + (i * 256), Data, sizeof(Data)); //写入外置Flash
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
uint8_t IAP_App_Updata(void)
{
  uint8_t Data[512];
  uint8_t Flash_Error = 0;

  /*擦除内部Flash*/
  IAP_App_Erase(2);

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
 * @brief 将待升级APP程序写入外部Flash
 * @param {uint8_t} First 是否首次写入
 * @param {uint8_t} *Data 写入数据
 * @param {uint16_t} Len  写入数据长度 最大不超过256
 * @return {uint8_t} 0:成功   1:失败
 */
uint8_t IAP_App_Write(uint8_t *Data, uint16_t Len)
{
  /*写入外部Flash*/
  QSPI_W25Qx_Write_Buffer(FLASH_BIN_ADDR, Data, Len);

  return 0;
}

/**
 * @brief 擦除FLASH空间
 * @param {uint8_t} Space  0:备份空间  1:升级空间  2:MCU内部APP运行空间
 * @return {uint8_t} 0:成功   1:失败
 */
uint8_t IAP_App_Erase(uint8_t Space)
{
  uint8_t Error = 0;

  if (Space == 0)
  {
    /*擦除外置FLASH APP备份区 2MB*/
    for (uint32_t i = 0; i < (FLASH_BACKUP_SIZE / 4096); i++)
    {
      QSPI_W25Qx_EraseSector(FLASH_BACKUP_ADDR + (i * 4096));
    }
  }
  else if (Space == 1)
  {
    /*擦除外置Flash APP升级区 2MB*/
    for (uint32_t i = 0; i < (FLASH_BIN_SIZE / 4096); i++)
    {
      QSPI_W25Qx_EraseSector(FLASH_BIN_ADDR + (i * 4096));
    }
  }
  else if (Space == 2)
  {
    /*APP Bin文件占用几个整数扇区*/
    uint32_t APP_File_Sector_Count = MCU_FLASH_USER_SIZE / (128 * 1024);
    /*APP Bin文件占用整数扇区剩余数*/
    uint32_t APP_File_Sector_Remain = MCU_FLASH_USER_SIZE % (128 * 1024);
    if (APP_File_Sector_Remain != 0)
    {
      APP_File_Sector_Count++;
    }
    /*擦除APP占有扇区*/
    Error = Bsp_MCU_Flash_Erase(MCU_FLASH_APP_ADDR, APP_File_Sector_Count);
  }
  else
  {
    Error = 1;
  }

  return Error;
}



/**
 * @brief 将外部flash备份APP 写入内部Flash完成恢复
 * @return {*}
 */
uint8_t IAP_App_Renew(void)
{
  uint8_t Data[512];
  uint8_t Flash_Error = 0;

  /*擦除内部Flash*/
  IAP_App_Erase(2);

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
uint8_t IAP_App_CRC(uint32_t APP_File_Size)
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
