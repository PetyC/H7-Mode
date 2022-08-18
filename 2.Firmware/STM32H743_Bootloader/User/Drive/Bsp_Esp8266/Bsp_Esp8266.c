/*
 * @Description: 重构
 * @Autor: Pi
 * @Date: 2022-07-19 21:58:01
 * @LastEditTime: 2022-07-26 19:39:11
 */
#include "Bsp_ESP8266.h"

/*目标回复结构体*/
struct
{
  uint8_t Timeout_Flag;
  uint8_t Find_Flag;
  uint8_t *Target0;
  uint8_t *Target1;
} Reply_Target;

/*ESP8266状态*/
enum 
{
  OFF,          //关机
  ON,           //开机
}ESP8266_State = OFF;




/*内部使用函数*/
static void Bsp_ESP8266_RX_Fun(uint8_t *Data, uint16_t Len);
static void Bsp_ESP8266_RX_Finished(uint8_t *Data, uint16_t Len);
//static void Bsp_ESP8266_RX_None(void);

/**
 * @brief 发送AT消息到ESP8266
 * @param {uint8_t} *Data
 * @param {uint8_t} Len
 * @return {*}
 */
void Bsp_ESP8266_TX(uint8_t *Data, uint8_t Len)
{
  if (Len > 255 || Data == NULL)
  {
    return;
  }

  Bsp_UART_Write(&huart1, Data, Len);
  Bsp_UART_Poll_DMA_TX(&huart1);
}


/**
 * @brief 发送指令配置模块,阻塞版
 * @param {uint8_t} *Data       发送的数据
 * @param {uint8_t} Len         发送的数据的长度
 * @param {uint8_t} *Reply0     预期返回的数据
 * @param {uint8_t} *Reply1     预期返回的数据
 * @param {uint16_t} Time_Out   等待最大值 和定时器时基有关 当前 100ms*Time_Out = 超时时间(ms)
 * @param {uint8_t} Retry       最大重试次数
 * @return {uint8_t} 0:成功   1:失败
 */
uint8_t Bsp_ESP8266_Config(uint8_t *Data, uint8_t Len, uint8_t *Reply0, uint8_t *Reply1,  uint16_t Timeout , uint8_t Retry)
{
  /*设置等待目标*/
  Reply_Target.Target0 = Reply0;
  Reply_Target.Target1 = Reply1;

  /*设置超时时间*/
  User_Uart_RX_Timeout_Set(Timeout);

  /*设置串口函数功能*/
  User_UART_RX_Fun = Bsp_ESP8266_RX_Fun;
  User_UART_RX_Finished = Bsp_ESP8266_RX_Finished;
 
  
  for(uint8_t i = 0 ; i < Retry ; i++)
  {
    /*发送数据*/
    Bsp_ESP8266_TX(Data , Len);
    
    /*轮询*/
    do
    {
      User_UART_RX_Loop();
    } while ((Reply_Target.Find_Flag != 1) && (Reply_Target.Timeout_Flag != 1));

     /*回复正确*/
    if(Reply_Target.Find_Flag == 1)
    {
      Reply_Target.Find_Flag = 0;
      return 0;
    }

    /*若是超时*/
    if (Reply_Target.Timeout_Flag == 1)
    {
      Reply_Target.Timeout_Flag = 0;
    }

  }

  /*设置超时时间*/
  User_Uart_RX_Timeout_Set(1);

  /*超时未找到*/

  return 1;

}


/**
 * @brief 串口数据接收处理
 * @param {uint8_t} *Data
 * @param {uint8_t} Len
 * @return {*}
 */
static void Bsp_ESP8266_RX_Fun(uint8_t *Data, uint16_t Len)
{
  
  if(strstr((char *)Data, (char *)Reply_Target.Target0) || strstr((char *)Data, (char *)Reply_Target.Target1))
  {
    /*目标找到*/
    Reply_Target.Find_Flag = 1;
    Reply_Target.Timeout_Flag = 0;
  }
  

}


/**
 * @brief 串口数据接收完毕处理
 * @param {uint8_t} *Data
 * @param {uint8_t} Len
 * @return {*}
 */
static void Bsp_ESP8266_RX_Finished(uint8_t *Data, uint16_t Len)
{

  if(strstr((char *)Data, (char *)Reply_Target.Target0) || strstr((char *)Data, (char *)Reply_Target.Target1))
  {
      /*目标找到*/
    Reply_Target.Find_Flag = 1;
    Reply_Target.Timeout_Flag = 0;
  }
  else
  {
    Reply_Target.Find_Flag = 0;
    Reply_Target.Timeout_Flag = 1;
  }



}

/**
 * @brief 串口无数据
 * @return {*}
 */
//static void Bsp_ESP8266_RX_None(void)
//{
////  Reply_Target.Timeout_Flag = 1;

//}

/**
 * @brief esp8266电源控制
 * @param {uint8_t} Enabel  1:上电    0:下电
 * @return {uint8_t} 0:成功   1:失败
 */
void Bsp_ESP8266_Power(uint8_t Enabel)
{
  if (Enabel == 0)
  {
    /*失能ESP8266 芯片*/
    HAL_GPIO_WritePin(ESP_POW_GPIO_Port, ESP_POW_Pin, GPIO_PIN_RESET);

    ESP8266_State = OFF;
    return;
  }


  Bsp_UART_RX_Enable(&huart1, 0);

   
  HAL_GPIO_WritePin(ESP_POW_GPIO_Port, ESP_POW_Pin, GPIO_PIN_SET);

  ESP8266_State = ON;

  HAL_Delay(1000);

  Bsp_UART_RX_Enable(&huart1, 1);
  
   
  
}



/**
 * @brief 恢复出厂设置
 * @return {*}
 */
void Bsp_ESP8266_Reset(void)
{

  uint8_t CMD[] = "AT+RESTORE\r\n";
  
  Bsp_UART_RX_Enable(&huart1, 0);

  Bsp_ESP8266_TX(CMD , sizeof(CMD));

  ESP8266_State = ON;

  HAL_Delay(2000);

  Bsp_UART_RX_Enable(&huart1, 1);

}




/**
 * @brief 重启ESP8266
 * @return {*}
 */
void Bsp_ESP8266_RST(void)
{
  Bsp_UART_RX_Enable(&huart1, 0);
  /*恢复出厂设置*/
  Bsp_ESP8266_TX((uint8_t *)"AT+RST\r\n", 8);

  HAL_Delay(1000);
  Bsp_UART_RX_Enable(&huart1, 1);
}





/**
 * @brief ESP8266 WIFI连接
 * @param {uint8_t} *SSID
 * @param {uint8_t} *PAW
 * @return {*}
 */
uint8_t Bsp_ESP8266_Connect_AP(uint8_t *SSID, uint8_t *PAW)
{
  /*复位模组*/
  Bsp_ESP8266_RST();

  Bsp_ESP8266_Reset();                                             //恢复出厂设置
  Bsp_ESP8266_Config("ATE0\r\n", 7, "OK", NULL, 10, 3);             //关闭回显
  Bsp_ESP8266_Config("AT+CWMODE_DEF=1\r\n", 18, "OK", NULL, 10, 3); // WIFI模式1 单station模式
  Bsp_ESP8266_Config("AT+CWAUTOCONN=1\r\n", 18, "OK", NULL, 10, 3); //自动连接路由器

  uint8_t Data[100] = {0};
  uint8_t Len = sprintf((char *)Data, "AT+CWJAP_DEF=\"%s\",\"%s\"\r\n", SSID, PAW);
  Bsp_ESP8266_Config(Data, Len, "OK", NULL, 10, 3); //设置连接的路由器

  uint8_t Ret = Bsp_ESP8266_Config("AT+CIPSTATUS\r\n", 15, "STATUS:2", NULL, 50, 5); //等待连接成功

  return Ret;
}



/**
 * @brief 连接TCP服务器
 * @param {uint8_t} *IP
 * @param {uint8_t} Port
 * @param {uint8_t} Https_Enable
 * @return {uint8_t} 0:连接成功   1:连接失败
 */
uint8_t Bsp_ESP8266_Connect_TCP(uint8_t *IP, uint8_t Port, uint8_t Https_Enable)
{

  
  if (Bsp_ESP8266_Config("AT\r\n", 5, "OK", NULL, 10, 3) != 0) //测试是否正常
  {
    return 1;
  }

  if (Bsp_ESP8266_Config("AT+CIPSTATUS\r\n", 15, "STATUS:2", NULL, 50, 5) != 0) //测试是否连接上wifi
  {
    return 1;
  }

  uint8_t Data[100] = {0};
  uint8_t Len = 0;

  Bsp_ESP8266_Config("ATE0\r\n", 7, "OK", NULL, 10, 3);          //关闭回显
  Bsp_ESP8266_Config("AT+CIPMODE=0\r\n", 15, "OK", NULL, 10, 3); //非透传模式

  if (Https_Enable == 1)
  {
    Bsp_ESP8266_Config("AT+CIPSSLSIZE=4096\r\n", 21, "OK", NULL, 10, 3); //设置SSL缓存
    Len = sprintf((char *)Data, "AT+CIPSTART=\"SSL\",\"%s\",%d\r\n", IP, Port);
    Data[Len] = 0;
  }
  else
  {
    Bsp_ESP8266_Config("AT+CIPMUX=1\r\n", 14, "OK", NULL, 10, 3); //设置多连接
    Len = sprintf((char *)Data, "AT+CIPSTART=%d,\"TCP\",\"%s\",%d\r\n", 0, IP, Port);
    Data[Len] = 0;
  }

  uint8_t flag = Bsp_ESP8266_Config(Data, Len, "CONNECT", NULL, 10, 3); //建立TCP连接

  return flag;
}

/**
 * @brief 关闭TCP连接
 * @return {uint8_t}0:成功   1:失败
 */
uint8_t Bsp_ESP8266_Connect_TCP_Close(void)
{
  if(Bsp_ESP8266_Config("AT+CIPCLOSE=0\r\n", 16, "0,CLOSED", NULL, 10, 3) == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/**
 * @brief ESP8266发送GET请求      
 * @param {uint8_t} *IP
 * @param {uint8_t} *Path
 * @param {uint8_t} SSLEN
 * @return {uint8_t} 0:成功   1:失败
 */
uint8_t Bsp_ESP8266_Send_Get_Request(uint8_t *IP, uint8_t *Path, uint8_t SSLEN)
{
  uint8_t tcp_buff[100] = {0};
  uint8_t tcp_buff_Len = 0;

  uint8_t AT_Buff[200];
  uint8_t AT_Len = 0;

  uint8_t tcp_http_index = 0;

  //组合 get 指令
  tcp_buff_Len = sprintf((char *)tcp_buff, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", Path, IP);

  /*使用SSL*/
  if (SSLEN == 1)
  {
    AT_Len = sprintf((char *)AT_Buff, "AT+CIPSEND=%d\r\n", tcp_buff_Len);
  }
  else
  {
    AT_Len = sprintf((char *)AT_Buff, "AT+CIPSEND=%d,%d\r\n", tcp_http_index, tcp_buff_Len);
  }

  /*设置连接ID和数据长度*/
  if(Bsp_ESP8266_Config(AT_Buff, AT_Len, "OK", ">", 10, 5) == 0)
  {
    HAL_Delay(50);
    /*发送Get请求到服务器*/
    Bsp_ESP8266_TX(tcp_buff , tcp_buff_Len);
    return 0;
  }

  return 1;

}
