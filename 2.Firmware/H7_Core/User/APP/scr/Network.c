/*
 * @Description:网络相关
 * @Autor: Pi
 * @Date: 2022-08-05 21:54:09
 * @LastEditTime: 2022-09-23 15:30:05
 */
#include "Network.h"

#if USE_FreeRTOS == 1
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os2.h"
#endif

/*内部使用变量*/
Network_T Network;



/*内部使用函数*/
static uint8_t NetWork_IPD_Remove(uint8_t data, uint8_t *return_data, uint8_t *ID, uint16_t *return_len);
static uint8_t Networt_APU_DataAnalysis(uint8_t *data, uint16_t length, WIFI_Station_T *Wifi);


/**
 * @brief 网络数据处理，剔除+IPD的标号
 * @param {uint8_t} data  接收的数据
 * @param {uint8_t} *return_data  处理后的数据
 * @param {uint8_t} *ID   收到的网络连接ID号
 * @return {uint8_t} 0:有效数据   1:无效数据
 */
static uint8_t NetWork_IPD_Remove(uint8_t data, uint8_t *return_data, uint8_t *ID, uint16_t *return_len)
{
  static uint8_t IPD_Count0 = 0;
  static uint8_t IPD_Count = 0;
  static uint16_t Recv_Data_Len = 0;
  static uint8_t Recv_Start = 0;
  static uint8_t Recv_Flag = 0;  //是否是网络数据
  static uint8_t Recv_Count = 0; //接收到的数据长度 计数
  uint8_t Ret = 1;

  /*返回网络数据*/
  if (Recv_Flag == 1)
  {
    if (Recv_Data_Len > 0) //还没结束
    {
      Recv_Data_Len--;
      *return_data = data;
      Ret = 0;
    }
    else //数据结束
    {
      Recv_Flag = 0;
      Recv_Data_Len = 0;
      Recv_Start = 0;
    }
  }

  /*接收到的数据个数*/
  if (Recv_Start == 1)
  {
    if (Recv_Count <= 5)
    {
      Recv_Count++;
      if (data == ':') //接收到数据长度
      {
        Recv_Start = 0;
        Recv_Count = 0;
        Recv_Flag = 1;
      }
      else
      {
        if (data >= '0' && data <= '9') //取出数据长度
        {
          Recv_Data_Len = Recv_Data_Len * 10;
          Recv_Data_Len = Recv_Data_Len + (data - 0x30);
          *return_len = Recv_Data_Len; //返回数据长度
        }
      }
    }
    else
    {
      Recv_Count = 0;
    }
  }

  /*检测数据开头*/
  if (data == '+' && IPD_Count0 == 0)
    IPD_Count0++;
  else if (data == 'I' && IPD_Count0 == 1)
    IPD_Count0++;
  else if (data == 'P' && IPD_Count0 == 2)
    IPD_Count0++;
  else if (data == 'D' && IPD_Count0 == 3)
    IPD_Count0++;
  else if (data == ',' && IPD_Count0 == 4)
  {
    IPD_Count0 = 0;
    Recv_Start = 1;
    Recv_Count = 0;
    Recv_Data_Len = 0;
  }
  else
  {
    if (data == '+' && IPD_Count0 == 1)
    {
      IPD_Count0 = 1;
    }
    else
    {
      IPD_Count0 = 0;
    }
  }

  if (data == '+' && IPD_Count == 0)
    IPD_Count++;
  else if (data == 'I' && IPD_Count == 1)
    IPD_Count++;
  else if (data == 'P' && IPD_Count == 2)
    IPD_Count++;
  else if (data == 'D' && IPD_Count == 3)
    IPD_Count++;
  else if (data == ',' && IPD_Count == 4)
    IPD_Count++;
  else if (data >= '0' && data <= '9' && IPD_Count == 5)
  {
    IPD_Count++;
    if (ID != NULL)
    {
      *ID = data;
    }
  }
  else if (data == ',' && IPD_Count == 6)
  {
    IPD_Count = 0, Recv_Start = 1;
    Recv_Count = 0;
    Recv_Data_Len = 0;
  }
  else
  {
    if (data == '+' && IPD_Count == 1)
    {
      IPD_Count = 1;
    }
    else
    {
      IPD_Count = 0;
    }
  }

  return Ret;
}

/**
 * @brief 解析WIFI配网数据
 * @param {uint8_t} *data
 * @param {uint16_t} length
 * @return {uint8_t} 0: 成功    1:失败
 */
static uint8_t Networt_APU_DataAnalysis(uint8_t *data, uint16_t length, WIFI_Station_T *Wifi)
{
  uint8_t Ret = 1;
  char *str;

  str = StrBetwString((char *)data, "\"ssid\":\"", "\""); //获取ssid
  if (str != NULL)
  {
    memset((char *)Wifi->ssid, 0, sizeof(Wifi->ssid));
    sprintf((char *)Wifi->ssid, "%s", str);
    cStringRestore();

    str = StrBetwString((char *)data, "\"pwd\":\"", "\""); //获取pwd
    if (str != NULL)
    {
      memset((char *)Wifi->pwd, 0, sizeof(Wifi->pwd));
      sprintf((char *)Wifi->pwd, "%s", str);
      Ret = 0;
    }
  }
  cStringRestore();

  return Ret;
}

/**
 * @brief 堵塞处理网络数据
 * @param {void } (*Fun)      数据处理函数
 * @param {uint8_t} NetWork_Flag    是否是网络数据(带+IPD标识)
 * @param {uint16_t} Timeout    超时时间
 * @return {uint8_t} 0:无数据   其他:实际读取数据长度
 */
uint16_t Network_Read(uint8_t Network_ID, uint8_t *RX_Buffer, uint16_t RX_Buffer_Len, uint16_t Timeout)
{
  uint8_t RX_Data = 0;
  uint8_t RX_Data_Pro = 0;
  uint16_t RX_Data_Len = 0;

  uint16_t Pos = 0;
  uint8_t ID = 0;

  if (Timeout > 0)
  {
    Bsp_ESP8266_Timer_Start(Timeout / 100); /* 使用定时器，作为超时控制 */
  }

  while (1)
  {

    if (Timeout > 0)
    {
      if (Bsp_ESP8266_Timer_Check() == 0)
      {
        break;
      }
    }

    if (Bsp_UART_Read(&huart1, &RX_Data, 1)) //有数据
    {

      Bsp_ESP8266_Timer_Start(Timeout / 100);

      if (NetWork_IPD_Remove(RX_Data, &RX_Data_Pro, &ID, &RX_Data_Len) == 0)
      {
        if (Network_ID != str_to_int((char *)&ID)) //网络ID不符合
        {
          break;
        }

        RX_Buffer[Pos] = RX_Data_Pro;

        Pos++;

        if (Pos == RX_Buffer_Len) //到达缓存尾
        {
          break;
        }

        if (Pos >= RX_Data_Len) //接收完毕
        {
          break;
        }
      }
    }
  }

  return Pos;
}

/**
 * @brief 小程序网络配置
 * @return {uint8_t}0:连接成功  1:失败
 */
uint8_t NetWork_APUconfig(void)
{
  Bsp_ESP8266_Echo(0);

  /*设置WIFI模式3*/
  if (Bsp_ESP8266_SetWiFiMode(3) == 1)
  {
    return 1;
  }

      
  /*获取本机MAC地址*/
  char Mac[64] = {0};
  char IP[64] = {0};
  if (Bsp_ESP8266_GetLocalIP(IP, Mac) == 1)
  {
    return 1;
  }

      
  /*开机本地AP*/
  if (Bsp_ESP8266_Set_AP_NamePass("Core-H7", "11223344", 11, ECN_WPA_WPA2_PSK) == 1)
  {
    return 1;
  }


  /*启用多连接*/
  if (Bsp_ESP8266_CIPMUX(1) == 1)
  {
    return 1;
  }
      
  /*启用UDP服务器*/
  if (Bsp_ESP8266_CreateUDPServer(0, 5555, 5556) == 1)
  {
    return 1;
  }
        
  /*获取WIFI数据*/
  WIFI_Station_T WIFI;
  uint8_t Buffer[128] = {0};
  /*重复5次*/
  for(uint8_t i = 0; i<5 ; i++)
  {
    if (Network_Read(0, Buffer, sizeof(Buffer), 60000) == 0)
    {
      continue;
    }

    if (Networt_APU_DataAnalysis(Buffer, sizeof(Buffer), &WIFI) == 0)
    {
      memset(Buffer, 0, sizeof(Buffer));
      break;
    }

    memset(Buffer, 0, sizeof(Buffer));
  }


  /*发送回复*/
  uint16_t len = sprintf((char *)Buffer, "{\"mac\":\"%s\",\"ip\":\"%s\"}", Mac, IP);
  for(uint8_t i = 0 ; i < 3 ; i++)
  {
    Bsp_ESP8266_SendTcpUdp(0, Buffer, len);
  }

  /*关闭UDP*/
  Bsp_ESP8266_CloseTcpUdp(0);
      

  /*WIFI模式1*/
  Bsp_ESP8266_SetWiFiMode(1);
      
  /*加入WIFI*/
  if(Bsp_ESP8266_JoinAP(WIFI.ssid , WIFI.pwd , 15000) == 0)
  {
    /*更新信息*/
    memcpy(Network.AP.ssid , WIFI.ssid , sizeof(WIFI.ssid));
    memcpy(Network.AP.pwd , WIFI.pwd , sizeof(WIFI.pwd));
    return 0;
  }
      
  return 1;
}


/**
 * @brief 查询网络连接状态
 * @return {uint8_t} 2-5
 */
uint8_t NetWork_QueryLink(void)
{
  return Bsp_ESP8266_QueryLink();
}




/**
 * @brief 网络初始化
 * @return {*}
 */
void NetWork_Init(void)
{
  /*结构体初始化*/
  Network.AP_Connect = UnLink;
  memset(Network.AP.pwd , 0 , sizeof(Network.AP.pwd));      //应从Flash中读出保存的WIFI数据
  memset(Network.AP.ssid , 0 , sizeof(Network.AP.ssid));

  memcpy(Network.AP.pwd , "Mate" , 4);
  memcpy(Network.AP.ssid , "23333333" , 8);

  /*ESP8266上电*/
  Bsp_ESP8266_PowerOn();
  
#if USE_FreeRTOS == 1
  osDelay(2000);
#else
  HAL_Delay(2000);
#endif

  /*关闭回显*/
  Bsp_ESP8266_Echo(0);

  /*不自动连接WIFI*/
  Bsp_ESP8266_Set_AutoLink(0);

  /*开启按键功能*/
  Bsp_ESP8266_KEY_Enable(1);

  /*WIFI模式1*/
  Bsp_ESP8266_SetWiFiMode(1);
      
  /*加入WIFI*/
  Bsp_ESP8266_JoinAP(Network.AP.pwd ,Network.AP.ssid, 2000);

  /*查询网络状态*/
  Network.AP_Connect = (AP_Connect_E)NetWork_QueryLink();
}




