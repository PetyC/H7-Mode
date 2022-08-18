/*
 * @Description: 自定义FatFs Flash操作
 * @Autor: Pi
 * @Date: 2022-04-02 19:46:40
 * @LastEditTime: 2022-04-26 01:54:40
 */
#ifndef USER_FATFS_H
#define USER_FATFS_H


#include "fatfs.h"



void test(void);



uint8_t User_FatFs_Init(void);

uint8_t exf_getfree(uint8_t *drv,uint32_t *total,uint32_t *free);
uint8_t f_typetell(uint8_t *fname);
uint8_t char_upper(uint8_t c);

void User_FatFs_Demo(void);

#endif
