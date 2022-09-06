/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-06 22:01:08
 * @LastEditTime: 2022-09-07 01:15:52
 */
#ifndef BSP_NAND_H_
#define BSP_NAND_H_

#include "main.h"




/* 定义NAND Flash的物理地址。这个是由硬件决定的 */
#define Bank_NAND_ADDR     ((uint32_t)0x80000000)

/* 定义操作NAND Flash用到3个宏 */
#define NAND_CMD_AREA		*(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA)
#define NAND_ADDR_AREA		*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA)
#define NAND_DATA_AREA		*(__IO uint8_t *)(Bank_NAND_ADDR | DATA_AREA)

#define DATA_AREA                  ((uint32_t)0x00000000)

#define NAND_ADDR_5					1			/* 0表示只用发送4个字节的地址，1表示5个 */

uint8_t NAND_Format(void);
uint32_t NAND_ReadID(void);
	
void ViewSDCapacity(void);

#endif
