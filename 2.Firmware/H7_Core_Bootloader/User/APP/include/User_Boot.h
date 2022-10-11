/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-10-11 14:19:38
 * @LastEditTime: 2022-10-11 19:36:24
 */
#ifndef USER_BOOT_H_
#define USER_BOOT_H_

#include "stm32h7xx_hal.h"
#include "Bsp_MCU_Flash.h"
#include "Bsp_w25qxx.h"

/*内部Flash*/
#define MCU_FLASH_IAP_SIZE (uint32_t)(1024 * 1024)                      //bootloader所用容量大小(KB)
#define MCU_FLASH_APP_ADDR (MCU_FLASH_BASE_ADDR + MCU_FLASH_IAP_SIZE)   //app程序运行地址:FLASH的起始地址 + bootloader所用程序大小
#define MCU_FLASH_USER_SIZE (MCU_FLASH_SIZE - MCU_FLASH_IAP_SIZE)       //app程序大小(KB) = (总FLASH容量 - bootloader所用容量大小)

/*外部Flash*/
#define FLASH_DATA_SIZE  0X1000                                         //用户数据区大小 4096 单位:字节     
#define FLASH_DATA_ADDR (FLASH_BEGIN_ADDR)                              //数据区地址 
#define FLASH_BIN_SIZE   MCU_FLASH_USER_SIZE                            //app存储区大小 单位:字节    
#define FLASH_BIN_ADDR  (FLASH_DATA_ADDR + FLASH_DATA_SIZE)             //app区起始地址

/*APP跳转标志需要跳转的值*/
#define APP_JUMP_VALUE 0X11223344

/*是否跳入APP*/
void User_Boot_Judge(void);

/*设置跳转*/
void User_Boot_Set(void);

/*备份APP*/
uint8_t User_Boot_App_Backup(void);

/*升级APP*/
uint8_t User_Boot_App_Updata(void);

/*校验APP*/
uint8_t User_Boot_App_CRC(uint32_t APP_File_Size);

/*CRC句柄*/
extern CRC_HandleTypeDef hcrc;

#if 0
void User_App_Jump_Demo(void);
void User_App_Jump_Set_Demo(void);
#endif

#endif
