/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-04-20 00:11:15
 * @LastEditTime: 2022-07-03 04:12:12
 */
#ifndef MCU_FLASH_H
#define MCU_FLASH_H

#include "main.h"


/*FLASH起始地址  0x08000000*/
#define MCU_FLASH_BASE_ADDR         (uint32_t)(FLASH_BASE) 
/*FLASH结束地址*/
#define MCU_FLASH_END_ADDR       (uint32_t)(0x081FFFFF)

/*芯片等待超时时间*/
#define FLASH_WAITETIME  50000         

/*MCU内部FLASH大小*/
#define MCU_FLASH_SIZE       	(uint32_t)(2 * 1024 * 1024)	  /* FLASH总容量 */
#define MCU_FLASH_SECTOR_SIZE	(uint32_t)(128 * 1024)		    /* 扇区大小，字节 */


//STM32H7 FLASH 扇区的起始地址
//BANK1
#define ADDR_FLASH_SECTOR_0_BANK1     ((uint32_t)0x08000000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_1_BANK1     ((uint32_t)0x08020000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_2_BANK1     ((uint32_t)0x08040000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_3_BANK1     ((uint32_t)0x08060000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_4_BANK1     ((uint32_t)0x08080000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_5_BANK1     ((uint32_t)0x080A0000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6_BANK1     ((uint32_t)0x080C0000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_7_BANK1     ((uint32_t)0x080E0000) //扇区0起始地址, 128 Kbytes  

//BANK2
#define ADDR_FLASH_SECTOR_0_BANK2     ((uint32_t)0x08100000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_1_BANK2     ((uint32_t)0x08120000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_2_BANK2     ((uint32_t)0x08140000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_3_BANK2     ((uint32_t)0x08160000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_4_BANK2     ((uint32_t)0x08180000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_5_BANK2     ((uint32_t)0x081A0000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_6_BANK2     ((uint32_t)0x081C0000) //扇区0起始地址, 128 Kbytes  
#define ADDR_FLASH_SECTOR_7_BANK2     ((uint32_t)0x081E0000) //扇区0起始地址, 128 Kbytes  

/* Flash内容和待写入的数据相等，不需要擦除和写操作 */
#define MCU_FLASH_IS_EQU		  0  
/* Flash不需要擦除，直接写 */
#define MCU_FLASH_REQ_WRITE		1	
/* Flash需要先擦除,再写 */
#define MCU_FLASH_REQ_ERASE		2	
/* 函数参数错误 */
#define MCU_FLASH_PARAM_ERR		3	


uint8_t User_MCU_FLASH_Read(uint32_t ReadAddr, uint8_t *pBuffer, uint32_t pBuffer_Len);   //从指定地址开始读出指定长度的数据
uint8_t User_MCU_Flash_Erase(uint32_t Addr, uint32_t Sectors_Number);                     //擦除某页数据
uint8_t User_MCU_Flash_Write(uint32_t Write_Addr, uint8_t *pBuffer, uint32_t pBuffer_Len);   	//从指定地址开始写入指定长度的数据

#endif
