/*
 * @Description:ESP8266驱动，需要提供一个定时器
 * @Autor: Pi
 * @Date: 2022-08-03 16:39:00
 * @LastEditTime: 2022-09-23 14:42:09
 */
#ifndef BSP_ESP8266_H
#define BSP_ESP8266_H

#include "main.h"
#include "Bsp_Uart.h"
#include "cString.h"

/*是否使用了FreeRTOS*/
#define USE_FreeRTOS 0

/* 加密方式 */
enum
{
  ECN_OPEN = 0,
  ECN_WEP = 1,
  ECN_WPA_PSK = 2,
  ECN_WPA2_PSK = 3,
  ECN_WPA_WPA2_PSK = 4,
};

/*AP信息*/
typedef struct
{
  char ssid[33];   /* SSID是一个无线局域网络（WLAN）的名称。SSID是区分大小写的文本字符串，最大长度32个字符 */
  uint8_t ecn;     /* 加密方式 */
  int32_t rssi;    /* 信号强度 */
  uint8_t mac[20]; /* MAC地址字符串*/
  uint8_t ch;      /* 信道 */
} WIFI_AP_T;

/*定时器Handle*/
#define TIMER_HANDLE (htim13)
extern TIM_HandleTypeDef TIMER_HANDLE;

/*定时器*/
void Bsp_ESP8266_Timer(void);
uint8_t Bsp_ESP8266_Timer_Check(void);
void Bsp_ESP8266_Timer_Start(uint16_t Timerout);

/*ESP8266 电源相关*/
void Bsp_ESP8266_PowerOff(void);
void Bsp_ESP8266_PowerOn(void);
void Bsp_ESP8266_Restore(void);

/*数据相关*/
uint8_t Bsp_ESP8266_WaitResponse(char *_pAckStr, uint16_t _usTimeOut);
uint16_t Bsp_ESP8266_ReadLine(char *_pBuf, uint16_t _usBufSize, uint16_t _usTimeOut);
void Bsp_ESP8266_SendAT(char *_Cmd);
void Bsp_ESP8266_Clear_RxBuffer(void);

/*esp8266相关功能函数*/
uint8_t Bsp_ESP8266_Echo(uint8_t Enable);
uint8_t Bsp_ESP8266_Auto_LinkWifi(uint8_t Enable);
uint8_t Bsp_ESP8266_KEY_Enable(uint8_t Enable);

/*WIFI相关*/
uint8_t Bsp_ESP8266_SetWiFiMode(uint8_t _mode);
uint8_t Bsp_ESP8266_Set_AP_IP(char *_ip);
uint8_t Bsp_ESP8266_Set_AP_NamePass(char *_name, char *_pwd, uint8_t _ch, uint8_t _ecn);
uint8_t Bsp_ESP8266_JoinAP(char *_ssid, char *_pwd, uint16_t _timeout);
int16_t Bsp_ESP8266_ScanAP(WIFI_AP_T *_pList, uint16_t _MaxNum);
uint8_t Bsp_ESP8266_Set_AutoLink(uint8_t Enable);
void Bsp_ESP8266_QuitAP(void);
uint8_t Bsp_ESP8266_GetLocalIP(char *_ip, char *_mac);
uint8_t Bsp_ESP8266_QueryLink(void);


/*网络相关*/
uint8_t Bsp_ESP8266_CIPMUX(uint8_t _mode);
uint8_t Bsp_ESP8266_CreateTCPServer(uint16_t _TcpPort);
uint8_t Bsp_ESP8266_CreateUDPServer(uint8_t _id, uint16_t _Far_Port, uint16_t _LaocalPort);
uint8_t Bsp_ESP8266_LinkTCPServer(uint8_t _id, char *_server_ip, uint16_t _TcpPort);
uint8_t Bsp_ESP8266_SendTcpUdp(uint8_t _id, uint8_t *_databuf, uint16_t _len);
void Bsp_ESP8266_CloseTcpUdp(uint8_t _id);

#endif
