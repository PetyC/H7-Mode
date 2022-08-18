/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-07-22 00:03:31
 * @LastEditTime: 2022-07-26 19:32:42
 */
#ifndef NETWORK_ANALY_H
#define NETWORK_ANALY_H




#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "User_config.h"
#include "cString.h"
#include "network.h"

/*Inof文本数据解析*/
Info_Str User_Network_Info_Process(uint8_t *data, uint16_t len);

/*网络数据处理，剔除+IPD的标号*/
uint8_t User_Networt_IPD_Process(uint8_t data , uint8_t *return_data , uint8_t *ID);

/*判断是否收到HTTP消息头 需要放在最前面进行解析*/
uint8_t User_Networt_HTTP_Process(uint8_t data);

/*获取模组MAC地址*/
void User_Networt_Get_Mac(uint8_t *data, uint16_t length);

/*解析UDP数据*/
void User_Networt_Udp_Data(uint8_t *data, uint16_t length);
#endif
