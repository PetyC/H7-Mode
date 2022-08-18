/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-08-05 21:54:16
 * @LastEditTime: 2022-08-09 01:29:20
 */
#ifndef NETWORK_H
#define NETWORK_H

#include "main.h"
#include "cString.h"
#include "Bsp_ESP8266.h"

/*Station信息*/
typedef struct 
{
  char ssid[33];
  char pwd[20];
}WIFI_Station_T;


/*连接状态*/
enum
{
  Link = 2,
  NetLink = 3,
  UnNetLink = 4,
  UnLink = 5,
};

extern uint8_t NetWork_State;


uint8_t NetWork_APUconfig(void);
uint8_t NetWork_QueryLink(void);


#endif
