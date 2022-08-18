/*
 * @Description: 用于W25Q128JVSSIQ的驱动文件  
 * @Autor: Pi
 * @Date: 2022-04-12 21:18:45
 * @LastEditTime: 2022-04-13 16:54:32
 */
#ifndef W25QXX_H
#define W25QXX_H
 
#include "quadspi.h"
#include "stdio.h"

/* 宏定义 --------------------------------------------------------------------*/
#define FLASH_BEGIN_ADDRESS 0x00000

#define W25Q128JV_FLASH_SIZE                  0x1000000 /* 128 MBits => 16MBytes */
#define W25Q128JV_BLOCK_SIZE                  0x10000   /* 256 Blocks of 64KBytes */
#define W25Q128JV_HALF_BLOCK_SIZE             0x8000    /* 128 Blocks  of 32KBytes */
#define W25Q128JV_SECTOR_SIZE                 0x1000    /* 4096 sectors of 4kBytes */
#define W25Q128JV_PAGE_SIZE                   0x100     /* 65536 pages of 256 bytes */

#define W25Q128JV_DUMMY_CYCLES_READ           4
#define W25Q128JV_DUMMY_CYCLES_READ_QUAD      10

#define W25Q128JV_BULK_ERASE_MAX_TIME         250000//ms
#define W25Q128JV_SECTOR_ERASE_MAX_TIME       3000
#define W25Q128JV_SUBSECTOR_ERASE_MAX_TIME    800

#define W25Q128JV_FLASH_ID                    0XEF4018
/*  W25Q128JV 指令  */
/* 复位操作 */
#define RESET_ENABLE_CMD                      0x66
#define RESET_MEMORY_CMD                      0x99

#define ENTER_QPI_MODE_CMD                    0x38
#define EXIT_QPI_MODE_CMD                     0xFF

/* 读取ID指令 */
#define READ_ID_CMD                           0x90
#define DUAL_READ_ID_CMD                      0x92
#define QUAD_READ_ID_CMD                      0x94
#define READ_JEDEC_ID_CMD                     0x9F

/* 读操作指令 */
#define READ_CMD                              0x03
#define FAST_READ_CMD                         0x0B
#define DUAL_OUT_FAST_READ_CMD                0x3B
#define DUAL_INOUT_FAST_READ_CMD              0xBB
#define QUAD_OUT_FAST_READ_CMD                0x6B
#define QUAD_INOUT_FAST_READ_CMD              0xEB

/* 写使能操作指令 */
#define WRITE_ENABLE_CMD                      0x06
#define WRITE_DISABLE_CMD                     0x04

/* 读写状态寄存器操作指令 */
#define READ_STATUS_REG1_CMD                  0x05
#define READ_STATUS_REG2_CMD                  0x35
#define READ_STATUS_REG3_CMD                  0x15

#define WRITE_STATUS_REG1_CMD                 0x01
#define WRITE_STATUS_REG2_CMD                 0x31
#define WRITE_STATUS_REG3_CMD                 0x11

/* 编程指令 */
#define PAGE_PROG_CMD                         0x02
#define QUAD_INPUT_PAGE_PROG_CMD              0x32

/* 擦除Flash指令 */
#define SECTOR_ERASE_CMD                      0x20
#define BLOCK_32KB_ERASE_CMD                  0x52
#define BLOCK_64KB_ERASE_CMD                  0xD8
#define CHIP_ERASE_CMD                        0xC7

#define PROG_ERASE_RESUME_CMD                 0x7A
#define PROG_ERASE_SUSPEND_CMD                0x75

/* 状态寄存器标志位 */
#define W25Q128JV_FSR_BUSY                    ((uint8_t)0x01) /* busy */
#define W25Q128JV_FSR_WREN                    ((uint8_t)0x02) /* write enable */
#define W25Q128JV_FSR_QE                      ((uint8_t)0x02) /* quad enable */

/* Flash 状态码*/
#define FLASH_OK                          ((uint8_t)0x00)
#define FLASH_ERROR                       ((uint8_t)0x01)
#define FLASH_BUSY                        ((uint8_t)0x02)
#define FLASH_NOT_SUPPORTED               ((uint8_t)0x04)
#define FLASH_SUSPENDED                   ((uint8_t)0x08)


/* 是否使用DMA方式 */
#define QSPI_FLASH_DMA_ENABLE        1  //0:阻塞方式  1:使用DMA方式


 
uint8_t QSPI_W25Qx_Init(void);

uint32_t QSPI_W25Qx_ReadID(void);

uint32_t QSPI_W25Qx_Read_Type(void);

void QSPI_W25Qx_Reset_Memory(void);

void QSPI_W25Qx_EraseSector(uint32_t _SectorAddr);

uint8_t QSPI_W25Qx_Write_Buffer(uint8_t *_pBuf, uint32_t _write_Addr, uint16_t _write_Size);

void QSPI_W25Qx_Read_Buffer(uint8_t *_pBuf, uint32_t _read_Addr, uint32_t _read_Size);






#endif /* BSP_QSPI_W25Q128_H_ */
