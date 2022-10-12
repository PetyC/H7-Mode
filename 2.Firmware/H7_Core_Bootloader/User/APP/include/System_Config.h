/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-10-12 13:56:31
 * @LastEditTime: 2022-10-12 14:28:44
 */
#ifndef SYSTEM_CONFIG_H_
#define SYSTEM_CONFIG_H_


#include "stm32h7xx_hal.h"
#include "IAP.h"
#include "Bsp_w25qxx.h"


typedef struct 
{
  uint8_t Init;    //是否已初始化
  uint8_t Updata;  //是否需要升级
  uint8_t Error;   //是否升级出错
}System_Config;


/*初始化系统配置信息*/
void System_Config_Init(void);

/*擦除系统信息*/
void System_Config_Erase(void);

/*设置新的系统信息*/
void System_Config_Set(System_Config Config);

/*获取系统信息*/
System_Config System_Config_Get(void);

#endif
