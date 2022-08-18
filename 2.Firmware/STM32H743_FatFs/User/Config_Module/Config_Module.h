/*
 * @Description: AT指令阻塞版本
 * @Autor: Pi
 * @Date: 2022-04-19 17:14:34
 * @LastEditTime: 2022-04-27 16:32:43
 */
#ifndef CONFIGMODULEBLOCK_H_
#define CONFIGMODULEBLOCK_H_

#include <main.h>



uint8_t Config_Module_Block(char *Dat, uint8_t Dat_Len , char *returnc, char *returncc);


uint8_t Config_Module(uint8_t *Send_Data , uint8_t Send_Data_Len , uint8_t *returnc);
#endif

