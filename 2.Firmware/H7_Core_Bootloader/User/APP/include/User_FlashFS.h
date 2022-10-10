/*
 * @Description: FLASHFS文件系统相关操作
 * @Autor: Pi
 * @Date: 2022-09-09 19:19:14
 * @LastEditTime: 2022-09-10 03:31:37
 */
#ifndef USER_FLASHFS_H
#define USER_FLASHFS_H

#include "main.h"

/*依赖驱动文件*/
#include "Bsp_Nand_Flash.h"

/*Flashfs库*/
#include "rl_fs.h"

/*C库相关*/
#include <stdio.h>
#include <string.h>

/*挂载文件系统*/
uint8_t User_FlashFS_Load(void);

/*显示文件系统相关内容*/
void User_FlashFS_ViewCapacity(void);

/*测试文件读写速度*/
void User_FlashFS_WriteFileTest(void);
#endif
