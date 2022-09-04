/*
 * @Description: nand flash
 * @Autor: Pi
 * @Date: 2022-04-11 16:41:05
 * @LastEditTime: 2022-09-01 18:13:18
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

//NAND FLASH命令
#define NAND_READID         	0X90    	//读ID指令
#define NAND_FEATURE			    0XEF    	//设置特性指令
#define NAND_RESET          	0XFF    	//复位NAND
#define NAND_READSTA        	0X70   	 	//读状态
#define NAND_AREA_A         	0X00   
#define NAND_AREA_TRUE1     	0X30  
#define NAND_WRITE0        	 	0X80
#define NAND_WRITE_TURE1    	0X10
#define NAND_ERASE0        	 	0X60
#define NAND_ERASE1         	0XD0
#define NAND_MOVEDATA_CMD0  	0X00
#define NAND_MOVEDATA_CMD1  	0X35
#define NAND_MOVEDATA_CMD2  	0X85
#define NAND_MOVEDATA_CMD3  	0X10






uint8_t Bsp_Nand_Init(void);


#if 0
void NAND_Demo(void);
#endif


#endif
