/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    user_diskio.c
 * @brief   This file includes a diskio driver skeleton to be completed by the user.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
 /* USER CODE END Header */

#ifdef USE_OBSOLETE_USER_CODE_SECTION_0
/*
 * Warning: the user section 0 is no more in use (starting from CubeMx version 4.16.0)
 * To be suppressed in the future.
 * Kept to ensure backward compatibility with previous CubeMx versions when
 * migrating projects.
 * User code previously added there should be copied in the new user sections before
 * the section contents can be deleted.
 */
/* USER CODE BEGIN 0 */
/* USER CODE END 0 */
#endif

/* USER CODE BEGIN DECL */

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "ff_gen_drv.h"

#include "w25qxx.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define SPI_FLASH 0
#define SPI_FLASH_SECTOR_SIZE (4096 / SPI_FLASH_BLOCK_SIZE)
#define SPI_FLASH_SECTOR_COUNT ((12 * 1024 * 1024) / SPI_FLASH_SECTOR_SIZE) // 12的单位是MB  挂载的总容量
#define SPI_FLASH_BLOCK_SIZE (1)                                            //每次擦除的块的个数
/*
FLASH_SECTOR_SIZE 	 设置为512或者4096都可以使用，但是在512的时候，文件系统认为FLASH中的扇区大小是512字节，在使用的时候，效率远没有4096高
FLASH_SECTOR_COUNT    挂载的总容量，根据自己需求
FLASH_BLOCK_SIZE   	  每次擦除的块的个数，原子哥写的是8，因为FLASH的最小擦除单位为扇区（4KB），原子哥的FLASH_SECTOR_SIZE 为512，所以是512*8，我们用1即可。
*/

/* Private variables ---------------------------------------------------------*/
/* Disk status */
static volatile DSTATUS Stat = STA_NOINIT;

/* USER CODE END DECL */

/* Private function prototypes -----------------------------------------------*/
DSTATUS USER_initialize (BYTE pdrv);
DSTATUS USER_status (BYTE pdrv);
DRESULT USER_read (BYTE pdrv, BYTE *buff, DWORD sector, UINT count);
#if _USE_WRITE == 1
  DRESULT USER_write (BYTE pdrv, const BYTE *buff, DWORD sector, UINT count);
#endif /* _USE_WRITE == 1 */
#if _USE_IOCTL == 1
  DRESULT USER_ioctl (BYTE pdrv, BYTE cmd, void *buff);
#endif /* _USE_IOCTL == 1 */

Diskio_drvTypeDef  USER_Driver =
{
  USER_initialize,
  USER_status,
  USER_read,
#if  _USE_WRITE
  USER_write,
#endif  /* _USE_WRITE == 1 */
#if  _USE_IOCTL == 1
  USER_ioctl,
#endif /* _USE_IOCTL == 1 */
};

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes a Drive
  * @param  pdrv: Physical drive number (0..)
  * @retval DSTATUS: Operation status
  */
DSTATUS USER_initialize (
	BYTE pdrv           /* Physical drive nmuber to identify the drive */
)
{
  /* USER CODE BEGIN INIT */
  Stat = STA_NOINIT;

  if (QSPI_W25Qx_Init() == 0)
  {
    Stat &= ~STA_NOINIT;
  }
  else
 {
    Stat = STA_NOINIT;
  }

  return Stat;
  /* USER CODE END INIT */
}

/**
  * @brief  Gets Disk Status
  * @param  pdrv: Physical drive number (0..)
  * @retval DSTATUS: Operation status
  */
DSTATUS USER_status (
	BYTE pdrv       /* Physical drive number to identify the drive */
)
{
  /* USER CODE BEGIN STATUS */
  Stat = STA_NOINIT;

  if (pdrv != 0)
    Stat = STA_NOINIT;
  else
    Stat &= ~STA_NOINIT;

  return Stat;
  /* USER CODE END STATUS */
}

/**
  * @brief  Reads Sector(s)
  * @param  pdrv: Physical drive number (0..)
  * @param  *buff: Data buffer to store read data
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to read (1..128)
  * @retval DRESULT: Operation result
  */
DRESULT USER_read (
	BYTE pdrv,      /* Physical drive nmuber to identify the drive */
	BYTE *buff,     /* Data buffer to store read data */
	DWORD sector,   /* Sector address in LBA */
	UINT count      /* Number of sectors to read */
)
{
  /* USER CODE BEGIN READ */

  switch (pdrv)
  {
    case SPI_FLASH:

      if (!count)
      {
        return RES_PARERR;
      }
 
     QSPI_W25Qx_Read_Buffer(buff, sector << 12, count<<12);

    return RES_OK;

    default:
    return RES_PARERR;
  }

  /* USER CODE END READ */
}

/**
  * @brief  Writes Sector(s)
  * @param  pdrv: Physical drive number (0..)
  * @param  *buff: Data to be written
  * @param  sector: Sector address (LBA)
  * @param  count: Number of sectors to write (1..128)
  * @retval DRESULT: Operation result
  */
#if _USE_WRITE == 1
DRESULT USER_write (
	BYTE pdrv,          /* Physical drive nmuber to identify the drive */
	const BYTE *buff,   /* Data to be written */
	DWORD sector,       /* Sector address in LBA */
	UINT count          /* Number of sectors to write */
)
{
  /* USER CODE BEGIN WRITE */
  /* USER CODE HERE */

  uint32_t addr;
  BYTE *p;

  p = (BYTE *)buff;

  switch (pdrv)
  {
  case SPI_FLASH:

    if (!count)
    {
      return RES_PARERR;
    }

    for(uint16_t i = 0; i < count; i++)
    {
      addr = (sector+i) << 12;
      
      QSPI_W25Qx_EraseSector(addr);

      QSPI_W25Qx_Write_Buffer(p + 256*0, addr + 256*0, 256);
      QSPI_W25Qx_Write_Buffer(p + 256*1, addr + 256*1, 256);
      QSPI_W25Qx_Write_Buffer(p + 256*2, addr + 256*2, 256);
      QSPI_W25Qx_Write_Buffer(p + 256*3, addr + 256*3, 256);	
      
      QSPI_W25Qx_Write_Buffer(p + 256*4, addr + 256*4, 256);
      QSPI_W25Qx_Write_Buffer(p + 256*5, addr + 256*5, 256);
      QSPI_W25Qx_Write_Buffer(p + 256*6, addr + 256*6, 256);
      QSPI_W25Qx_Write_Buffer(p + 256*7, addr + 256*7, 256);	
      
      QSPI_W25Qx_Write_Buffer(p + 256*8,  addr + 256*8, 256);
      QSPI_W25Qx_Write_Buffer(p + 256*9,  addr + 256*9, 256);
      QSPI_W25Qx_Write_Buffer(p + 256*10, addr + 256*10, 256);
      QSPI_W25Qx_Write_Buffer(p + 256*11, addr + 256*11, 256);	
      
      QSPI_W25Qx_Write_Buffer(p + 256*12, addr + 256*12, 256);
      QSPI_W25Qx_Write_Buffer(p + 256*13, addr + 256*13, 256);
      QSPI_W25Qx_Write_Buffer(p + 256*14, addr + 256*14, 256);
      QSPI_W25Qx_Write_Buffer(p + 256*15, addr + 256*15, 256);	
      
      p += 4096;					
    }

    return RES_OK;

  default:
    return RES_PARERR;
  }

  /* USER CODE END WRITE */
}
#endif /* _USE_WRITE == 1 */

/**
  * @brief  I/O control operation
  * @param  pdrv: Physical drive number (0..)
  * @param  cmd: Control code
  * @param  *buff: Buffer to send/receive control data
  * @retval DRESULT: Operation result
  */
#if _USE_IOCTL == 1
DRESULT USER_ioctl (
	BYTE pdrv,      /* Physical drive nmuber (0..) */
	BYTE cmd,       /* Control code */
	void *buff      /* Buffer to send/receive control data */
)
{
  /* USER CODE BEGIN IOCTL */
  DRESULT res = RES_ERROR;

  switch (pdrv)
  {
  case SPI_FLASH:
    switch (cmd)
    {
    case CTRL_SYNC:
      res = RES_OK;
      break;
    case GET_SECTOR_SIZE:
      *(WORD *)buff = SPI_FLASH_SECTOR_SIZE;
      res = RES_OK;
      break;
    case GET_BLOCK_SIZE:
      *(WORD *)buff = SPI_FLASH_BLOCK_SIZE;
      res = RES_OK;
      break;
    case GET_SECTOR_COUNT:
      *(DWORD *)buff = SPI_FLASH_SECTOR_COUNT;
      res = RES_OK;
      break;
    default:
      res = RES_PARERR;
      break;
    }
    break;

  default:
    res = RES_PARERR;

    break;
  }

  return res;
  /* USER CODE END IOCTL */
}
#endif /* _USE_IOCTL == 1 */

