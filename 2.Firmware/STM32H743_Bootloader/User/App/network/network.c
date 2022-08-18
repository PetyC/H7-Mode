/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-07-06 21:19:14
 * @LastEditTime: 2022-07-26 20:49:30
 */
#include "network.h"

/*HAL库句柄*/
extern TIM_HandleTypeDef htim12;

/*内部使用函数*/
static void User_Networt_Timer_Enable(uint8_t Enable);

/*内部使用变量*/
struct
{
  uint16_t Count;
  uint16_t Max;       //10ms * number = Timeout
  uint8_t Flag;
  uint8_t Enable;
} Network_Timer = {0, 20, 0, 0};


Network_Info_Str Network_Info = {0};

/*公共缓存*/
#define PUBLIC_BUFF_LEN 1024
uint8_t Public_Buff[PUBLIC_BUFF_LEN];
uint16_t Public_Buff_Count = 0;

/**
 * @brief 设置默认连接路由器
 * @param {uint8_t} *SSID   连接的路由器名称
 * @param {uint8_t} *PAW    连接的路由器密码
 * @return {*}
 */
uint8_t User_Network_Connect_AP(uint8_t *SSID, uint8_t *PAW)
{
  if (Bsp_ESP8266_Connect_AP(SSID, PAW) == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/**
 * @brief 连接TCP服务器
 * @param {uint8_t} *IP
 * @param {uint8_t} Port
 * @param {uint8_t} Https_Enable
 * @return {uint8_t} 0:连接成功   1:连接失败
 */
uint8_t User_Network_Connect_Tcp(uint8_t *IP, uint8_t Port, uint8_t Https_Enable)
{
  if (Bsp_ESP8266_Connect_TCP(IP, Port, Https_Enable) == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/**
 * @brief 发送Get请求获取版本信息
 * @param {uint8_t} *IP
 * @param {uint8_t} *Bin_Path
 * @param {uint8_t} SSLEN
 * @param {uint8_t} Info
 * @return {*}
 */
uint8_t User_Network_Get_Info(uint8_t *IP, uint8_t *Info_Path, uint8_t SSLEN, Info_Str *Info)
{
  memset(Public_Buff, 0, PUBLIC_BUFF_LEN);
  Public_Buff_Count = 0;

  /*发送失败*/
  if (Bsp_ESP8266_Send_Get_Request(IP, Info_Path, SSLEN) == 1)
  {
    return 1;
  }

  uint8_t Temp_Data;

  /*循环找到HTTP头部*/
  while (1)
  {
    uint8_t Data = 0;
    uint16_t Occup_Size = Bsp_UART_Get_RX_Buff_Occupy(&huart1);

    if (Occup_Size > 0)
    {
      if (Network_Timer.Enable == 1)
      {
        User_Networt_Timer_Enable(0);
      }

      Bsp_UART_Read(&huart1, &Temp_Data, 1);

      if (User_Networt_IPD_Process(Temp_Data, &Data, NULL) == 0)
      {
        if (User_Networt_HTTP_Process(Data) == 0)
        {
          break;
        }
      }
    }
    else
    {
      /*打开定时器*/
      if (Network_Timer.Enable == 0)
      {
        User_Networt_Timer_Enable(1);
      }

      /*定时器超时*/
      if (Network_Timer.Flag == 1)
      {
        Network_Timer.Flag = 0;
        Bsp_ESP8266_Connect_TCP_Close();
        return 1;
      }
    }
  }

  /*数据部分*/
  while (1)
  {
    uint8_t Data = 0;
    uint16_t Occup_Size = Bsp_UART_Get_RX_Buff_Occupy(&huart1);

    if (Occup_Size > 0)
    {
      if (Network_Timer.Enable == 1)
      {
        User_Networt_Timer_Enable(0);
      }

      Bsp_UART_Read(&huart1, &Temp_Data, 1);

      if (User_Networt_IPD_Process(Temp_Data, &Data, NULL) == 0)
      {
        Public_Buff[Public_Buff_Count] = Data;
        Public_Buff_Count++;

        if (Public_Buff_Count == PUBLIC_BUFF_LEN)
        {
          Public_Buff_Count = 0;
          *Info = User_Network_Info_Process(Public_Buff, PUBLIC_BUFF_LEN);
          memset(Public_Buff, 0, PUBLIC_BUFF_LEN);
        }
      }
    }
    else
    {
      /*打开定时器*/
      if (Network_Timer.Enable == 0)
      {
        User_Networt_Timer_Enable(1);
      }

      /*定时器超时*/
      if (Network_Timer.Flag == 1)
      {
        Network_Timer.Flag = 0;

        if (Public_Buff_Count > 0)
        {
          Public_Buff_Count = 0;
          *Info = User_Network_Info_Process(Public_Buff, PUBLIC_BUFF_LEN);
          memset(Public_Buff, 0, PUBLIC_BUFF_LEN);
        }

        /*关闭连接*/
        Bsp_ESP8266_Connect_TCP_Close();
        return 0;
      }
    }
  }
}

/**
 * @brief 下载BIN文件至MCU内置FLASH中
 * @param {uint8_t} *IP
 * @param {uint8_t} *Bin_Path
 * @param {uint8_t} SSLEN
 * @return {*}
 */
void User_Network_Down_Bin(uint8_t *IP, uint8_t *Bin_Path, uint8_t SSLEN)
{

  memset(Public_Buff, 0, PUBLIC_BUFF_LEN);
  Public_Buff_Count = 0;

  if (Bsp_ESP8266_Send_Get_Request(IP, Bin_Path, SSLEN) == 1)
  {
    return;
  }

  uint8_t Temp_Data;

  /*循环找到HTTP头部*/
  while (1)
  {
    uint8_t Data = 0;
    uint16_t Occup_Size = Bsp_UART_Get_RX_Buff_Occupy(&huart1);

    if (Occup_Size > 0)
    {
      if (Network_Timer.Enable == 1)
      {
        User_Networt_Timer_Enable(0);
      }

      Bsp_UART_Read(&huart1, &Temp_Data, 1);

      if (User_Networt_IPD_Process(Temp_Data, &Data, NULL) == 0)
      {
        if (User_Networt_HTTP_Process(Data) == 0)
        {
          break;
        }
      }
    }
    else
    {
      /*打开定时器*/
      if (Network_Timer.Enable == 0)
      {
        User_Networt_Timer_Enable(1);
      }

      /*定时器超时*/
      if (Network_Timer.Flag == 1)
      {
        Network_Timer.Flag = 0;
        Bsp_ESP8266_Connect_TCP_Close();
        return;
      }
    }
  }

  /*数据部分*/
  while (1)
  {
    uint8_t Data = 0;
    uint16_t Occup_Size = Bsp_UART_Get_RX_Buff_Occupy(&huart1);

    if (Flash_State.Error == 1)
    {
      return;
    }

    if (Flash_State.Finish == 1)
    {
      return;
    }

    if (Occup_Size > 0)
    {
      if (Network_Timer.Enable == 1)
      {
        User_Networt_Timer_Enable(0);
      }

      Bsp_UART_Read(&huart1, &Temp_Data, 1);

      if (User_Networt_IPD_Process(Temp_Data, &Data, NULL) == 0)
      {
        Public_Buff[Public_Buff_Count] = Data;
        Public_Buff_Count++;

        if (Public_Buff_Count == PUBLIC_BUFF_LEN)
        {
          Public_Buff_Count = 0;
          User_App_MCU_Flash_Updata(Public_Buff, PUBLIC_BUFF_LEN);
          memset(Public_Buff, 0, PUBLIC_BUFF_LEN);
        }
      }
    }
    else
    {
      /*打开定时器*/
      if (Network_Timer.Enable == 0)
      {
        User_Networt_Timer_Enable(1);
      }

      /*定时器超时*/
      if (Network_Timer.Flag == 1)
      {
        Network_Timer.Flag = 0;

        if (Public_Buff_Count > 0)
        {
          Public_Buff_Count = 0;
          User_App_MCU_Flash_Updata(Public_Buff, PUBLIC_BUFF_LEN);
          memset(Public_Buff, 0, PUBLIC_BUFF_LEN);
        }

        /*关闭连接*/
        Bsp_ESP8266_Connect_TCP_Close();
        return;
      }
    }
  }
}

/**
 * @brief 超时服务函数 放中断
 * @return {*}
 */
void User_Networt_Timer(void)
{
  Network_Timer.Count++;

  if (Network_Timer.Count >= Network_Timer.Max)
  {
    Network_Timer.Count = 0;
    Network_Timer.Flag = 1;
    HAL_TIM_Base_Stop_IT(&htim12);
    __HAL_TIM_SET_COUNTER(&htim12, 0);
  }
}

/**
 * @brief 定时器使能
 * @param {uint8_t} Enable
 * @return {*}
 */
static void User_Networt_Timer_Enable(uint8_t Enable)
{
  if (Enable)
  {
    Network_Timer.Count = 0;
    Network_Timer.Enable = 1;
    __HAL_TIM_CLEAR_FLAG(&htim12, TIM_FLAG_UPDATE);
    HAL_TIM_Base_Start_IT(&htim12);
  }
  else
  {
    Network_Timer.Enable = 0;
    Network_Timer.Count = 0;
    HAL_TIM_Base_Stop_IT(&htim12);
    __HAL_TIM_SET_COUNTER(&htim12, 0);
  }
}

/**
 * @brief 微信小程序配网
 * @return {*}
 */
void User_Networt_Apuconfig(void)
{
  Bsp_ESP8266_RST();
  Bsp_ESP8266_Reset();

  Bsp_ESP8266_Config("ATE0\r\n", 6, "OK", NULL, 10, 3);             //关闭回显
  Bsp_ESP8266_Config("AT+CWMODE_DEF=3\r\n", 17, "OK", NULL, 10, 3); // WIFI模式3

  Bsp_ESP8266_TX("AT+CIPSTAMAC_CUR?\r\n", 19);    //MAC
  /*解析MAC数据*/
  User_Network_RX_Block(User_Networt_Get_Mac ,0, 500);


  uint8_t data[100];
  uint8_t len = sprintf((char *)data, "AT+CWSAP_DEF=\"Core-H7\",\"11223344\",11,4,4\r\n");

  Bsp_ESP8266_Config(data, len, "OK", NULL, 10, 3); //配置发出无线

  len = sprintf((char *)data, "%s", "AT+CIPSTART=\"UDP\",\"192.168.4.2\",5555,5556,2\r\n");

  Bsp_ESP8266_TX(data, len);

  uint8_t Temp[32];
  memcpy(Temp ,  Network_Info.SSID , 32);
  
  uint16_t Count = 0;
  while (1)
  {
  /*收到的解析UDP数据*/
    if( User_Network_RX_Block(User_Networt_Udp_Data , 1 ,50) == 1)
    {
      Count++;
    }
		else
		{
			break;
		}


    if(Count > 1000)
    {
      Count = 0;
      break;
    }
  }
  
  for(uint8_t i = 0 ; i<3 ; i++)
  {
    len = sprintf((char *)data,"{\"mac\":\"%s\",\"ip\":\"%s\"}",Network_Info.MAC, Network_Info.IP);
    len = sprintf((char *)data,"AT+CIPSEND=%d\r\n",len);
    Bsp_ESP8266_Config(data, len, ">", NULL, 10, 3);             //发送一次数据

    len = sprintf((char *)data,"{\"mac\":\"%s\",\"ip\":\"%s\"}",Network_Info.MAC, Network_Info.IP);
    Bsp_ESP8266_TX(data , len);
    HAL_Delay(50);
  }

  Bsp_ESP8266_Connect_AP(Network_Info.SSID , Network_Info.PAW);

  Bsp_ESP8266_RST();

  Bsp_ESP8266_Config("AT+CWMODE_DEF=1\r\n", 17, "OK", NULL, 10, 3); // WIFI模式1
}





/**
 * @brief 堵塞处理网络数据
 * @param {void } (*Fun)      数据处理函数
 * @param {uint8_t} NetWork_Flag    是否是网络数据(带+IPD标识)
 * @param {uint16_t} Timeout    超时时间
 * @return {uint8_t} 0:数据处理完毕 1:无数据
 */
uint8_t User_Network_RX_Block(void (*Fun)(uint8_t *data, uint16_t length) , uint8_t NetWork_Flag , uint16_t Timeout)
{
  uint8_t Ret = 1;
  Network_Timer.Max = Timeout/10;
  
  while (1)
  {
    uint8_t Temp_Data = 0;
    uint8_t Data = 0;
    uint16_t Occup_Size = Bsp_UART_Get_RX_Buff_Occupy(&huart1);

    if (Occup_Size > 0)
    {
      if (Network_Timer.Enable == 1)
      {
        User_Networt_Timer_Enable(0);
      }

      if(NetWork_Flag == 1)
      {
        Bsp_UART_Read(&huart1, &Temp_Data, 1);

        if (User_Networt_IPD_Process(Temp_Data, &Data, NULL) == 0)
        {
          Public_Buff[Public_Buff_Count] = Data;
          Public_Buff_Count++;

          if (Public_Buff_Count == PUBLIC_BUFF_LEN)
          {
            Public_Buff_Count = 0;
            Fun(Public_Buff, PUBLIC_BUFF_LEN);
            memset(Public_Buff, 0, PUBLIC_BUFF_LEN);
          }
        }
      }
      else
      {
        uint16_t len = Bsp_UART_Read(&huart1, (Public_Buff+Public_Buff_Count), PUBLIC_BUFF_LEN);
        Public_Buff_Count += len;
        
        if (Public_Buff_Count >= PUBLIC_BUFF_LEN)
        {
          Public_Buff_Count = 0;
          Fun(Public_Buff, PUBLIC_BUFF_LEN);
          memset(Public_Buff, 0, PUBLIC_BUFF_LEN);
        }

      }
      Ret = 0;
    }
    else
    {
      /*打开定时器*/
      if (Network_Timer.Enable == 0)
      {
        User_Networt_Timer_Enable(1);
      }

      /*定时器超时*/
      if (Network_Timer.Flag == 1)
      {
        Network_Timer.Flag = 0;

        if (Public_Buff_Count > 0)
        {
          Public_Buff_Count = 0;
          Fun(Public_Buff, PUBLIC_BUFF_LEN);
          memset(Public_Buff, 0, PUBLIC_BUFF_LEN);
        }
        Ret = 0;
        break;
      }
    }
  }


  Network_Timer.Max = 20;

  return Ret;
}




