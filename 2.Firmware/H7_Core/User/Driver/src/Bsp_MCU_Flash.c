#include "Bsp_MCU_Flash.h"
#include "string.h"


/*内部调用的函数*/
static uint16_t Bsp_MCU_FLASH_Get_Sector(uint32_t addr);

/**
 * @brief 获取某个地址所在的flash扇区
 * @param {uint32_t} addr	flash地址
 * @return {uint16_t}	扇区值
 */
static uint16_t Bsp_MCU_FLASH_Get_Sector(uint32_t addr)
{
  if (addr < ADDR_FLASH_SECTOR_1_BANK1)
    return FLASH_SECTOR_0;
  else if (addr < ADDR_FLASH_SECTOR_2_BANK1)
    return FLASH_SECTOR_1;
  else if (addr < ADDR_FLASH_SECTOR_3_BANK1)
    return FLASH_SECTOR_2;
  else if (addr < ADDR_FLASH_SECTOR_4_BANK1)
    return FLASH_SECTOR_3;
  else if (addr < ADDR_FLASH_SECTOR_5_BANK1)
    return FLASH_SECTOR_4;
  else if (addr < ADDR_FLASH_SECTOR_6_BANK1)
    return FLASH_SECTOR_5;
  else if (addr < ADDR_FLASH_SECTOR_7_BANK1)
    return FLASH_SECTOR_6;
  else if (addr < ADDR_FLASH_SECTOR_0_BANK2)
    return FLASH_SECTOR_7;
  else if (addr < ADDR_FLASH_SECTOR_1_BANK2)
    return FLASH_SECTOR_0;
  else if (addr < ADDR_FLASH_SECTOR_2_BANK2)
    return FLASH_SECTOR_1;
  else if (addr < ADDR_FLASH_SECTOR_3_BANK2)
    return FLASH_SECTOR_2;
  else if (addr < ADDR_FLASH_SECTOR_4_BANK2)
    return FLASH_SECTOR_3;
  else if (addr < ADDR_FLASH_SECTOR_5_BANK2)
    return FLASH_SECTOR_4;
  else if (addr < ADDR_FLASH_SECTOR_6_BANK2)
    return FLASH_SECTOR_5;
  else if (addr < ADDR_FLASH_SECTOR_7_BANK2)
    return FLASH_SECTOR_6;
  else
    return FLASH_SECTOR_7;
}


/**
 * @brief 比较Flash指定地址的数据
 * @param {uint32_t} ReadAddr   Flash地址
 * @param {uint8_t} *pBuffer    比较的数据
 * @param {uint32_t} pBuffer_Len  数据大小(单位字节)
 * @return {uint8_t} 			
 *                    MCU_FLASH_IS_EQU		  0   Flash内容和待写入的数据相等，不需要擦除和写操作
 *		              	MCU_FLASH_REQ_WRITE		1	Flash不需要擦除，直接写
 *		                MCU_FLASH_REQ_ERASE		2	Flash需要先擦除,再写
 *		               	MCU_FLASH_PARAM_ERR		3	函数参数错误
 */
static uint8_t Bsp_MCU_Flash_Compare(uint32_t ReadAddr, uint8_t *pBuffer, uint32_t pBuffer_Len)
{
  /*判断地址是否超出*/
  if (ReadAddr + pBuffer_Len > MCU_FLASH_BASE_ADDR + MCU_FLASH_SIZE)
  {
    return MCU_FLASH_PARAM_ERR;
  }

  /* 长度为0时返回正确 */
	if (pBuffer_Len == 0)
	{
		return MCU_FLASH_IS_EQU;
	}

  /* 相等标志 默认相等*/
  uint8_t Equ_Flag = 1;
  uint8_t Temp_Byte;

  /*遍历读取数据判断状态*/
  for (uint32_t i = 0; i < pBuffer_Len; i++)
	{
		Temp_Byte = *(uint8_t *)ReadAddr;

		if (Temp_Byte != *pBuffer)
		{
			if (Temp_Byte != 0xFF)
			{
        /* 需要擦除后再写 */
				return MCU_FLASH_REQ_ERASE;	
			}
			else
			{
        /* 不相等，需要写 */
				Equ_Flag = 0;	
			}
		}

		ReadAddr++;
		pBuffer++;
	}

  if (Equ_Flag == 1)
	{
    /* Flash内容和待写入的数据相等，不需要擦除和写操作 */
		return MCU_FLASH_IS_EQU;	
	}
	else
	{
    /* Flash不需要擦除，直接写 */
		return MCU_FLASH_REQ_WRITE;	
	}

}



/**
 * @brief 读取CPU Flash的内容
 * @param {uint32_t} ReadAddr  起始地址
 * @param {uint8_t} *pBuffer  目标缓冲区
 * @param {uint32_t} pBuffer_Len  数据大小（单位是字节）
 * @return {uint8_t}0:成功 1:失败
 */
uint8_t Bsp_MCU_FLASH_Read(uint32_t ReadAddr, uint8_t *pBuffer, uint32_t pBuffer_Len)
{
  /*判断地址是否超出*/
  if (ReadAddr + pBuffer_Len > MCU_FLASH_BASE_ADDR + MCU_FLASH_SIZE)
  {
    return 1;
  }

  /* 长度为0时不继续操作,否则起始地址为奇地址会出错 */
	if (pBuffer_Len == 0)
	{
		return 1;
	}

  for (uint32_t i = 0; i < pBuffer_Len; i++)
	{
		*pBuffer++ = *(uint8_t *)ReadAddr++;
	}
	
	return 0;

}






/**
 * @brief 擦除地址所在扇区
 * @param {uint32_t} Addr	需要擦除数据所在地址
 * @param {uint32_t} Sectors_Number	擦除扇区数(1扇区128KB)
 * @return {uint8_t} 0:成功   1:失败
 */
uint8_t Bsp_MCU_Flash_Erase(uint32_t Addr, uint32_t Sectors_Number)
{

  if (Addr < MCU_FLASH_BASE_ADDR || Addr % 4)
    return 1; //非法地址

  FLASH_EraseInitTypeDef FlashEraseInit;
  HAL_StatusTypeDef FlashStatus = HAL_OK;
  uint32_t SectorError = 0;

  uint16_t BANK_Number = 1;

  if (Addr >= ADDR_FLASH_SECTOR_0_BANK2) //判断BANK
  {
    BANK_Number = FLASH_BANK_2; //操作BANK2
  }
  else
  {
    BANK_Number = FLASH_BANK_1; //操作BANK1
  }

  __set_PRIMASK(1); //关闭STM32总中断

  HAL_FLASH_Unlock(); //解锁

  FlashEraseInit.Banks = BANK_Number;                       //操作BANK
  FlashEraseInit.TypeErase = FLASH_TYPEERASE_SECTORS;       //擦除类型，扇区擦除
  FlashEraseInit.Sector = Bsp_MCU_FLASH_Get_Sector(Addr);      //要擦除的扇区
  FlashEraseInit.NbSectors = Sectors_Number;                //擦除页数
  FlashEraseInit.VoltageRange = FLASH_VOLTAGE_RANGE_3;      //电压范围，VCC=2.7~3.6V之间!!
  FLASH_WaitForLastOperation(FLASH_WAITETIME, BANK_Number); //等待上次操作完成

  FlashStatus = HAL_FLASHEx_Erase(&FlashEraseInit, &SectorError); //进行擦除
  FLASH_WaitForLastOperation(FLASH_WAITETIME, BANK_Number);       //等待上次操作完成

  HAL_FLASH_Lock(); //上锁

  __set_PRIMASK(0); //开启STM32总中断

  if (SectorError == 0xFFFFFFFF && FlashStatus == HAL_OK)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/**
 * @brief 擦除后写入数据 必须按32字节整数倍写，不支持跨扇区，扇区大小128KB
 * 写之前需要擦除扇区，长度不是32位整数倍时，最后几个字节补0写入
 * @param {uint32_t} WriteAddr	写入地址
 * @param {uint32_t} *pBuffer		写入数据
 * @param {uint32_t} pBuffer_Len	数据长度(单位字节，必须32字节整数倍)
 * @return {uint8_t} 0:成功			1:失败
 */
uint8_t Bsp_MCU_Flash_Write(uint32_t Write_Addr, uint8_t *pBuffer, uint32_t pBuffer_Len)
{
  /*地址小于芯片起始地址*/
  if (Write_Addr < MCU_FLASH_BASE_ADDR || Write_Addr % 4)
  {
    return 1; //非法地址
  }
  /*偏移地址超过芯片容量*/
  if (Write_Addr + pBuffer_Len > MCU_FLASH_BASE_ADDR + MCU_FLASH_SIZE)
  {
    return 1; //非法地址
  }
  /*长度为0则不继续操作*/
  if (pBuffer_Len == 0)
  {
    return 0;
  }


  /*判断FLash状态*/
  uint8_t MCU_FLASH_State = Bsp_MCU_Flash_Compare(Write_Addr , pBuffer , pBuffer_Len);

  if (MCU_FLASH_State == MCU_FLASH_IS_EQU)
	{
		return 0;
	}


  __set_PRIMASK(1); //关闭STM32总中断

  HAL_FLASH_Unlock(); //解锁

  /*pBuffer 字节转换为字  32Byte = 1 word*/
  for(uint32_t i = 0 ;i < pBuffer_Len / 32 ; i++)
  {
    /*uint64_t 占用8字节，4*8字节 = 32字节 = 1字 */
    uint64_t FlashWord[4];
    /*char 占用1字节，32个字节即为1字*/
    memcpy((char *)FlashWord, pBuffer, 32);
		pBuffer += 32;

    /*一次写入1字*/
    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, Write_Addr, (uint64_t)((uint32_t)FlashWord)) != HAL_OK) //以字(32位)写入数据
    {
      HAL_FLASH_Lock(); //上锁
      __set_PRIMASK(0); //打开STM32总中断
      return 1;         //写入异常
    }

    Write_Addr += 32; //地址递增32位即1字
    FLASH_WaitForLastOperation(FLASH_WAITETIME, FLASH_BANK_1); //等待上次操作完成
  }


  /*写入数据长度不是32字节的整数倍则后续补0*/
  if(pBuffer_Len % 32 != 0)
  {
    uint64_t FlashWord[4] = {0,0,0,0};
    memcpy((char *)FlashWord, pBuffer, pBuffer_Len % 32);

    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_FLASHWORD, Write_Addr, (uint64_t)((uint32_t)FlashWord)) != HAL_OK)
    {
      HAL_FLASH_Lock(); //上锁
      __set_PRIMASK(0); //打开STM32总中断
      return 1;         //写入异常
    }

  }


  HAL_FLASH_Lock(); //上锁

  __set_PRIMASK(0); //打开STM32总中断

  return 0;
}
