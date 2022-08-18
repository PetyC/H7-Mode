/*
 * @Description: 网络返回数据解析
 * @Autor: Pi
 * @Date: 2022-07-22 00:01:24
 * @LastEditTime: 2022-07-26 20:08:12
 */
#include "Network_Analy.h"

/*内部使用函数*/
static void User_Network_Url_Process(uint8_t *pStr, Info_Str *Info);

/**
 * @brief Inof文本数据解析
 * @param {uint8_t} *data   Info数据
 * @param {uint16_t} len    数据长度
 * @return {*}
 */
Info_Str User_Network_Info_Process(uint8_t *data, uint16_t len)
{

  Info_Str Info = {0};
  char *pStr;

  /*获取版本号*/
  pStr = StrBetwString((char *)data, "\"Version\":\"", "\",\"");

  /*获取版本号长度*/
  uint8_t pStr_len = strlen(pStr);

  /*判断版本号是否合法*/
  if (pStr_len > 20 || pStr == NULL)
  {
    return Info;
  }

  /*缓存版本号到结构体*/
  sprintf((char *)Info.Version, "%s", pStr);

  cStringRestore();

  /*获取Bin文件大小*/
  pStr = StrBetwString((char *)data, "\"Size\":\"", "\",\"");

  /*缓存Bin文件大小到结构体*/
  Info.Bin_Size = atoi(pStr);

  cStringRestore();

  /*Url数据处理*/
  User_Network_Url_Process(data, &Info);

  /*端口号*/
  pStr = StrBetwString((char *)data, "\"Port\":\"", "\",\"");

  Info.Port = atoi(pStr);

  cStringRestore();

  /*Info文件存放路径 */
  pStr = StrBetwString((char *)data, "\"Info_Path\":\"", ".txt\"");

  /*存入结构体*/
  sprintf((char *)Info.Info_Path, "%s.txt", pStr);

  cStringRestore();

  /*Bin文件存放路径 */
  pStr = StrBetwString((char *)data, "\"Bin_Path\":\"", ".bin\"");

  /*存入结构体*/
  sprintf((char *)Info.Bin_Path, "%s.bin", pStr);

  cStringRestore();
  return Info;
}

/**
 * @brief Url数据处理
 * @param {uint8_t} *pStr   Url字符串
 * @param {Info_Str} *Info  返回数据结构体
 * @return {*}
 */
static void User_Network_Url_Process(uint8_t *data, Info_Str *Info)
{
  char *pStr;
  uint8_t pStr_Pos = 0;
  /*服务器文件存放路径 */
  pStr = StrBetwString((char *)data, "\"IP\":\"", "\",\"");

  if (pStr == NULL || ((strlen((char *)pStr) < 5)))
  {
    return;
  }
  /*https */
  if (memcmp(pStr, "https", 5) == 0)
  {
    Info->SSLEN = 1;
    pStr_Pos = 5;
  }
  /*http*/
  else if (memcmp(pStr, "http", 4) == 0)
  {
    Info->SSLEN = 0;
    pStr_Pos = 4;
  }
  /*缓存IP*/
  sprintf((char *)Info->IP, "%s", (char *)pStr + pStr_Pos + 3);

  cStringRestore();
}

/**
 * @brief 网络数据处理，剔除+IPD的标号
 * @param {uint8_t} data  接收的数据
 * @param {uint8_t} *return_data  处理后的数据
 * @param {uint8_t} *ID   收到的网络连接ID号
 * @return {uint8_t} 0:有效数据   1:无效数据
 */
uint8_t User_Networt_IPD_Process(uint8_t data, uint8_t *return_data, uint8_t *ID)
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
 * @brief 判断是否收到HTTP消息头 需要放在最前面进行解析
 * @param {uint8_t} data    单个数据
 * @return {uint8_t}  0:成功  1:失败
 */
uint8_t User_Networt_HTTP_Process(uint8_t data)
{
  uint8_t http_End[] = "Accept-Ranges: bytes\r\n\r\n";

  static uint8_t RX_Count = 0;

  /*HTTP头消息未收到*/
  if (http_End[RX_Count] == data)
  {
    RX_Count++;
    if (RX_Count >= 24)
    {
      RX_Count = 0;
      return 0;
    }
  }

  return 1;
}

/**
 * @brief 获取模组MAC地址
 * @param {uint8_t} *data  接收到的数据
 * @param {uint16_t} length
 * @return {uint8_t} 0: 成功    1:失败
 */
void User_Networt_Get_Mac(uint8_t *data, uint16_t length)
{

  char *str;

  str = StrBetwString((char *)data, "MAC_CUR:\"", "\""); //得到MAC

  if (str != NULL)
  {
    if (strlen(str) == 17)
    {
      memset((char *)Network_Info.MAC, 0, sizeof(Network_Info.MAC));
      memcpy((char *)Network_Info.MAC, str, 17);
    }

  }

  cStringRestore();

  
}

/**
 * @brief 解析UDP数据
 * @param {uint8_t} *data
 * @param {uint16_t} length
 * @return {uint8_t} 0: 成功    1:失败
 */
void User_Networt_Udp_Data(uint8_t *data, uint16_t length)
{
 
  char *str;

  str = StrBetwString((char *)data, "\"ssid\":\"", "\""); //获取ssid
  if (str != NULL)
  {
    memset((char *)Network_Info.SSID, 0, sizeof(Network_Info.SSID));
    sprintf((char *)Network_Info.SSID, "%s", str);
    cStringRestore();

    str = StrBetwString((char *)data, "\"pwd\":\"", "\""); //获取pwd
    if (str != NULL)
    {
      memset((char *)Network_Info.PAW, 0, sizeof(Network_Info.PAW));
      sprintf((char *)Network_Info.PAW, "%s", str);
     
    }
  }
  cStringRestore();
}
