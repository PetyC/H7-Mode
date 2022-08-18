/*
 * @Description: ESP8266板级支持包
 * @Autor: Pi
 * @Date: 2022-07-19 21:58:08
 * @LastEditTime: 2022-07-20 16:48:09
 */
#ifndef BSP_ESP8266_H
#define BSP_ESP8266_H

#include "main.h"
#include "string.h"
#include "stdio.h"

#include "Bsp_Uart.h"
#include "app_uart.h"


/*堵塞式配置ESP8266*/
uint8_t Bsp_ESP8266_Config(uint8_t *Data, uint8_t Len, uint8_t *Reply0, uint8_t *Reply1, uint16_t Timeout , uint8_t Retry);

/*ESP8266 电源控制*/
void Bsp_ESP8266_Power(uint8_t Enabel);

/*恢复出厂设置*/
void Bsp_ESP8266_Reset(void);

/*重启ESP8266*/
void Bsp_ESP8266_RST(void);

/*发送数据到ESP8266*/
void Bsp_ESP8266_TX(uint8_t *Data, uint8_t Len);

/*ESP8266 WIFI连接*/
uint8_t Bsp_ESP8266_Connect_AP(uint8_t *SSID, uint8_t *PAW);

/*连接TCP服务器*/
uint8_t Bsp_ESP8266_Connect_TCP(uint8_t *IP, uint8_t Port, uint8_t Https_Enable); 

/*关闭TCP连接*/
uint8_t Bsp_ESP8266_Connect_TCP_Close(void);

/*发送GET请求*/
uint8_t Bsp_ESP8266_Send_Get_Request(uint8_t *IP, uint8_t *Path, uint8_t SSLEN);

#endif
