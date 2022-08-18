/*
 * @Description: nand flash
 * @Autor: Pi
 * @Date: 2022-04-11 16:41:05
 * @LastEditTime: 2022-04-11 19:54:33
 */
#ifndef USER_NAND_FLASH_H
#define USER_NAND_FLASH_H

#include "main.h"

#define MT29F4G08ABADA   0XDC9095


extern NAND_HandleTypeDef hnand1;


#define NAND_ADDRESS			0X80000000	//nand flash的访问地址,接NCE3,地址为:0X8000 0000
#define NAND_CMD				1<<16		//发送命令
#define NAND_ADDR				1<<17		//发送地址


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


//NAND FLASH状态
#define NSTA_READY       	   	0X40		//nand已经准备好
#define NSTA_ERROR				0X01		//nand错误
#define NSTA_TIMEOUT        	0X02		//超时
#define NSTA_ECC1BITERR       	0X03		//ECC 1bit错误
#define NSTA_ECC2BITERR       	0X04		//ECC 2bit以上错误




uint8_t NAND_ReadStatus(void);
uint8_t NAND_WaitForReady(void);
uint8_t NAND_ModeSet(uint8_t mode);


uint8_t User_Nand_Flash_Init(void);

void NAND_Demo(void);
#endif
