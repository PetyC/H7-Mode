/*
 * @Description:提供相关网络功能
 * @Autor: Pi
 * @Date: 2022-08-05 21:54:16
 * @LastEditTime: 2022-09-23 14:47:59
 */
#ifndef NETWORK_H_
#define NETWORK_H_

#include "main.h"
#include "Bsp_ESP8266.h"

/*Station信息*/
typedef struct 
{
  char ssid[33];
  char pwd[20];
}WIFI_Station_T;


/*连接状态*/
typedef enum 
{
  Link = 2,
  UnLink = 5,
  NetLink = 3,
  UnNetLink = 4,
}AP_Connect_E;

 
/*网络相关结构体*/
typedef struct 
{
  WIFI_Station_T AP;
  AP_Connect_E AP_Connect;
}Network_T;


extern Network_T Network;

void NetWork_Init(void);
uint8_t NetWork_APUconfig(void);
uint8_t NetWork_QueryLink(void);









#endif
