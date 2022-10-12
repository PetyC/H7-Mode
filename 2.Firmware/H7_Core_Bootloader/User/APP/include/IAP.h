/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-10-12 14:43:10
 * @LastEditTime: 2022-10-12 18:40:05
 */
#ifndef IAP_H_
#define IAP_H_

#include "stm32h7xx_hal.h"
#include "Bsp_w25qxx.h"
#include "Bsp_MCU_Flash.h"

/*内部Flash*/
#define MCU_FLASH_IAP_SIZE  (uint32_t)(1024 * 1024)                      //bootloader所用容量大小(KB)
#define MCU_FLASH_APP_ADDR  (MCU_FLASH_BASE_ADDR + MCU_FLASH_IAP_SIZE)   //app程序运行地址:FLASH的起始地址 + bootloader所用程序大小
#define MCU_FLASH_USER_SIZE (MCU_FLASH_SIZE - MCU_FLASH_IAP_SIZE)        //app程序大小(KB) = (总FLASH容量 - bootloader所用容量大小)

/*外部Flash*/      
#define FLASH_DATA_SIZE    (0X1000)                                        //用户数据区大小 4096 单位:字节     
#define FLASH_DATA_ADDR    (FLASH_BEGIN_ADDR)                              //数据区地址 
#define FLASH_BACKUP_SIZE  (MCU_FLASH_USER_SIZE)                           //app备份区大小
#define FLASH_BACKUP_ADDR  (FLASH_DATA_ADDR + FLASH_DATA_SIZE)             //app备份区起始地址
#define FLASH_BIN_SIZE     (MCU_FLASH_USER_SIZE)                           //app存储区大小 单位:字节    
#define FLASH_BIN_ADDR     (FLASH_BACKUP_ADDR + FLASH_BACKUP_ADDR)         //app区起始地址



/*APP跳转标志需要跳转的值*/
#define APP_JUMP_VALUE   0X11223344

/*CRC句柄*/
extern CRC_HandleTypeDef hcrc;


/*是否跳入APP*/
void IAP_Jump_Init(void);

/*跳转到APP*/
void IAP_Jump_Start(void);

/*擦除APP Flash空间*/
uint8_t IAP_App_Erase(uint8_t Space);

/*写入APP到外部Flash*/
uint8_t IAP_App_Write(uint8_t *Data, uint16_t Len);

/*备份APP*/
uint8_t IAP_App_Backup(void);

/*升级APP*/
uint8_t IAP_App_Updata(void);

/*校验APP*/
uint8_t IAP_App_CRC(uint32_t APP_File_Size);






#endif

