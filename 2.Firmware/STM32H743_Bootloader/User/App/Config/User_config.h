/*
 * @Description:系统配置文件 
 * @Autor: Pi
 * @Date: 2022-07-14 15:41:48
 * @LastEditTime: 2022-07-25 19:36:01
 */
#ifndef USER_CONFIG_H
#define USER_CONFIG_H

#include "main.h"
#include "Bsp_w25qxx.h"
#include "IAP.h"

typedef struct 
{
  uint8_t  Version[10];        //版本号
  uint32_t Bin_Size;           //固件大小
  uint8_t  Bin_Path[255];      //Bin文件路径        eg:ota/hardware/H7-Core/Demo.bin
  uint8_t  Info_Path[255];     //Info文件路径       eg:ota/hardware/H7-Core/Info.txt
  uint8_t  IP[255];            //服务器地址         eg:http://www.qiandpi.com/
  uint16_t Port;               //端口号
  uint8_t  SSLEN;              //1:ssl   0:非SSL
}Info_Str;


typedef struct
{
  uint8_t Init;           //是否已初始化
  uint8_t Updata;         //是否需要升级
  uint8_t Error;          //是否升级出错
  uint8_t Inquire;        //是否需要在Bootloader中查询升级信息
  Info_Str Info;          //Info数据
}System_Config_Str;


extern System_Config_Str System_Config;



/*初始化Boot*/
void User_Config_Init(void);


/*重新写入Config到FLASH*/
void User_Config_Set(System_Config_Str info);


















#endif
