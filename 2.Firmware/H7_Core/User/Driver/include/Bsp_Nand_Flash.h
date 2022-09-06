/*
 * @Description: nand flash
 * @Autor: Pi
 * @Date: 2022-04-11 16:41:05
 * @LastEditTime: 2022-09-07 01:15:41
 */
#ifndef BSP_NAND_FLASH_H
#define BSP_NAND_FLASH_H

#include "main.h"


/*NAND句柄*/
#define NAND_HANDLE (hnand1)
extern NAND_HandleTypeDef NAND_HANDLE;
 

/* 定义NAND Flash的物理地址。这个是由硬件决定的 */
#define Bank_NAND_ADDR     ((uint32_t)0x80000000)

/* 定义操作NAND Flash用到3个宏 */
#define NAND_CMD_AREA		  *(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA)    //nand flash的访问地址,接NCE3,地址为:0X8000 0000
#define NAND_ADDR_AREA		*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA)   //发送命令
#define NAND_DATA_AREA		*(__IO uint8_t *)(Bank_NAND_ADDR | DATA_AREA)   //发送地址


/*NAND型号*/
#define MT29F4G08ABADA   0XDC9095





HAL_StatusTypeDef Bsp_Nand_Flash_Erase(void);

uint8_t Bsp_Nand_Init(void);


#if 0
void NAND_Demo(void);
#endif


#endif
