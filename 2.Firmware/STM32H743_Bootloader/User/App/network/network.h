/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-07-06 21:19:17
 * @LastEditTime: 2022-07-26 20:34:39
 */
#ifndef NETWORK_H
#define NETWORK_H


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "app_uart.h"
#include "Bsp_Esp8266.h"
#include "User_config.h"
#include "Network_Analy.h"

typedef struct 
{
  uint8_t MAC[18];      //记录设备MAC
  uint8_t IP[21];       //记录设备连接路由器分得的IP
  uint8_t SSID[32];     //记录路由器名称
  uint8_t PAW[64];      //记录密码
}Network_Info_Str;


extern Network_Info_Str Network_Info;


/*设置默认连接路由器*/
uint8_t User_Network_Connect_AP(uint8_t *SSID, uint8_t *PAW);

/*连接TCP服务器*/
uint8_t User_Network_Connect_Tcp(uint8_t *IP , uint8_t Port , uint8_t Https_Enable);

/*发送Get请求获取版本信息*/
uint8_t User_Network_Get_Info(uint8_t *IP, uint8_t *Info_Path, uint8_t SSLEN, Info_Str *Info);

/*下载BIN文件至MCU内置FLASH中*/
void User_Network_Down_Bin(uint8_t *IP, uint8_t *Bin_Path, uint8_t SSLEN);

/*中断超时服务函数*/
void User_Networt_Timer(void);

/*APU WIFI配置*/
void User_Networt_Apuconfig(void);

/*堵塞处理网络数据*/
uint8_t User_Network_RX_Block(void (*Fun)(uint8_t *data, uint16_t length) , uint8_t NetWork_Flag , uint16_t Timeout);
#endif
