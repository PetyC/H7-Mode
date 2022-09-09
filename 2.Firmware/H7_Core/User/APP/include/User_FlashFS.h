/*
 * @Description: FLASHFS文件系统相关操作
 * @Autor: Pi
 * @Date: 2022-09-09 19:19:14
 * @LastEditTime: 2022-09-09 19:23:39
 */
#ifndef USER_FLASHFS_H
#define USER_FLASHFS_H

#include "main.h"

/*依赖驱动文件*/
#include "Bsp_Nand_Flash.h"


/*挂载文件系统*/
uint8_t User_FlashFS_Load(void);

#endif
