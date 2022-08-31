/*
 * @Description: 用于W25Q128JVSSIQ的驱动文件  
 * @Autor: Pi
 * @Date: 2022-04-12 21:18:45
 * @LastEditTime: 2022-08-31 19:30:56
 */
#ifndef BSP_W25QXX_H
#define BSP_W25QXX_H
 
#include "quadspi.h"
#include "stdio.h"

/*QSPI句柄*/
#define HQSPI_HANDLE (hqspi)
extern QSPI_HandleTypeDef HQSPI_HANDLE;


/*用户自定义数据*/
#define FLASH_BEGIN_ADDR 0x00000                    //FLASH起始地址

/*W25Q128 芯片相关参数*/
#define QSPI_FLASH_SIZE                  0x1000000 /* 128 MBits => 16MBytes */
#define QSPI_BLOCK_SIZE                  0x10000   /* 256 Blocks of 64KBytes */
#define QSPI_HALF_BLOCK_SIZE             0x8000    /* 128 Blocks  of 32KBytes */
#define QSPI_SECTOR_SIZE                 0x1000    /* 4096 sectors of 4kBytes */
#define QSPI_PAGE_SIZE                   0x100     /* 65536 pages of 256 bytes */


/*  W25Q128JVSSIQ 指令  */

/* 复位操作 */
#define RESET_ENABLE_CMD                      0x66
#define RESET_MEMORY_CMD                      0x99

/* 读取ID指令 */
#define READ_ID_CMD                           0x90
#define READ_JEDEC_ID_CMD                     0x9F

/* 读操作指令 */
#define QUAD_INOUT_FAST_READ_CMD              0xEB

/* 编程指令 */
#define QUAD_INPUT_PAGE_PROG_CMD              0x32

/* 擦除Flash指令 */
#define SECTOR_ERASE_CMD                      0x20

/* 写使能操作指令 */
#define WRITE_ENABLE_CMD                      0x06
#define WRITE_DISABLE_CMD                     0x04

/* 读写状态寄存器操作指令 */
#define READ_STATUS_REG1_CMD                  0x05
#define READ_STATUS_REG2_CMD                  0x35
#define READ_STATUS_REG3_CMD                  0x15

/* 状态寄存器标志位 */
#define W25Q128JV_FSR_BUSY                    ((uint8_t)0x01) /* busy */
#define W25Q128JV_FSR_WREN                    ((uint8_t)0x02) /* write enable */
#define W25Q128JV_FSR_QE                      ((uint8_t)0x02) /* quad enable */



/*Flash初始化*/
uint8_t QSPI_W25Qx_Init(void);

/*读取Flash ID*/
uint32_t QSPI_W25Qx_ReadID(void);

/*读取Flash 类型*/
uint32_t QSPI_W25Qx_Read_Type(void);

/*复位Flash*/
void QSPI_W25Qx_Reset_Memory(void);

/*擦除扇区*/
void QSPI_W25Qx_EraseSector(uint32_t _SectorAddr);

/*写入Flash*/
uint8_t QSPI_W25Qx_Write_Buffer(uint32_t _write_Addr ,uint8_t *_pBuf, uint16_t _write_Size);

/*读出Flash*/
void QSPI_W25Qx_Read_Buffer(uint32_t _read_Addr , uint8_t *_pBuf, uint32_t _read_Size);

void sfTestReadSpeed(void);
void sfErase(void);
#endif /* BSP_QSPI_W25Q128_H_ */
