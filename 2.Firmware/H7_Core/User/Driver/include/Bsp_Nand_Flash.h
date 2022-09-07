/*
 * @Description: nand flash
 * @Autor: Pi
 * @Date: 2022-04-11 16:41:05
 * @LastEditTime: 2022-09-08 02:03:44
 */
#ifndef BSP_NAND_FLASH_H
#define BSP_NAND_FLASH_H

#include "main.h"



/*NAND句柄*/
#define NAND_HANDLE (hnand1)
extern NAND_HandleTypeDef NAND_HANDLE;
 

/*NAND型号*/
#define MT29F4G08ABADA   0XDC9095




uint8_t Bsp_Nand_Init(void);

uint8_t Bsp_Nand_Erase(void);


void Nand_Demo(void);

void DotFormat(uint64_t _ullVal, char *_sp);


#endif
