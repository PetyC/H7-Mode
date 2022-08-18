/*
 * @Description: IAP升级程序 适用于F103系列 
 * @Autor: Pi
 * @Date: 2022-04-19 20:54:24
 * @LastEditTime: 2022-04-25 03:09:30
 */
#ifndef __IAP_H__
#define __IAP_H__

#include <stm32f1xx.h>



typedef  void (*iapfun)(void);				//定义一个函数类型的参数.  			   
void iap_load_app(uint32_t appxaddr);			//跳转到APP程序执行

void Reset_MCU(void);
#endif

