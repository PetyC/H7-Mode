/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-08-03 16:38:56
 * @LastEditTime: 2022-08-31 14:34:33
 */
#include "Bsp_ESP8266.h"

#if USE_FreeRTOS == 1
#include "FreeRTOS.h"
#include "task.h"
#endif



struct
{
  uint16_t Tick;
  uint16_t Max;
  uint8_t Flag;
  uint8_t Enable;
} ESP8266_Timer = {0};





/*内部使用函数*/
uint8_t Bsp_ESP8266_Timer_Check(void);
void Bsp_ESP8266_Timer_Start(uint16_t Timerout);


/**
 * @brief 定时器服务函数
 * @return {*}
 */
void Bsp_ESP8266_Timer(void)
{
  if (ESP8266_Timer.Enable)
  {
    ESP8266_Timer.Tick++;
    if (ESP8266_Timer.Tick > ESP8266_Timer.Max)
    {
      ESP8266_Timer.Tick = 0;
      ESP8266_Timer.Flag = 1;
      ESP8266_Timer.Enable = 0;
      HAL_TIM_Base_Stop(&TIMER_HANDLE);
      __HAL_TIM_SetCounter(&TIMER_HANDLE , 0);
    }
  }
}

/**
 * @brief 超时查询
 * @return {uint8_t} 0:超时   1:未超时
 */
uint8_t Bsp_ESP8266_Timer_Check(void)
{
  if (ESP8266_Timer.Flag == 1)
  {
    ESP8266_Timer.Flag = 0;
    return 0;
  }
  else
  {
    return 1;
  }
}

/**
 * @brief 定时器使能
 * @param {uint8_t} Timerout   0:关中断
 * @return {*}
 */
void Bsp_ESP8266_Timer_Start(uint16_t Timerout)
{
  if (Timerout)
  {
    ESP8266_Timer.Tick = 0;
    ESP8266_Timer.Max = Timerout;
    ESP8266_Timer.Enable = 1;
    /*开中断*/
    __HAL_TIM_CLEAR_FLAG(&TIMER_HANDLE , TIM_FLAG_UPDATE);
    HAL_TIM_Base_Start_IT(&TIMER_HANDLE);
  }
  else
  {
    ESP8266_Timer.Tick = 0;
    ESP8266_Timer.Enable = 0;
    /*关中断*/
    HAL_TIM_Base_Stop(&TIMER_HANDLE);
    __HAL_TIM_SetCounter(&TIMER_HANDLE , 0);
  }
}


/**
 * @brief 初始化ESP8266
 * @return {*}
 */
void Bsp_ESP8266_Init(void)
{
  
}


/**
 * @brief 给ESP8266模块上电
 * @return {*}
 */
void Bsp_ESP8266_PowerOn(void)
{
  Bsp_UART_Set_BRR(&huart1, 1);

  HAL_GPIO_WritePin(ESP_POW_GPIO_Port, ESP_POW_Pin, GPIO_PIN_SET);

  Bsp_ESP8266_WaitResponse("csum 0xdb\r\n", 3000);

  Bsp_UART_Set_BRR(&huart1, 0);

  if (Bsp_ESP8266_WaitResponse("ready\r\n", 3000) == 1)
  {
//    while (1);
  }

  Bsp_ESP8266_Clear_RxBuffer();     //防止还有杂乱数据
}

/**
 * @brief 给ESP8266模块下电
 * @return {*}
 */
void Bsp_ESP8266_PowerOff(void)
{
  HAL_GPIO_WritePin(ESP_POW_GPIO_Port, ESP_POW_Pin, GPIO_PIN_RESET);
}

/**
 * @brief 重置ESP8266
 * @return {*}
 */
void Bsp_ESP8266_Restore(void)
{
  Bsp_UART_RX_Enable(&huart1 , 0);
  Bsp_ESP8266_SendAT("AT+RESTORE");  

#if USE_FreeRTOS == 1
  vTaskDelay(1000);
#else
  HAL_Delay(1000);
#endif

  Bsp_UART_RX_Enable(&huart1 , 1);
}

/**
 * @brief 等待ESP8266返回指定的应答字符串, 可以包含任意字符。只要接收齐全即可返回。
 * @param {char} *_pAckStr     应答的字符串， 长度不得超过255
 * @param {uint16_t} _usTimeOut  命令执行超时，0表示一直等待. >０表示超时时间，单位1ms
 * @return {uint8_t} 0:成功   1:失败
 */
uint8_t Bsp_ESP8266_WaitResponse(char *_pAckStr, uint16_t _usTimeOut)
{
  uint8_t ucData;
  uint16_t pos = 0;
  uint32_t len;
  uint8_t ret;

  len = strlen(_pAckStr);
  if (len > 255)
  {
    return 1;
  }

  /* _usTimeOut == 0 表示无限等待 */
  if (_usTimeOut > 0)
  {
    Bsp_ESP8266_Timer_Start(_usTimeOut / 100); /* 使用定时器，作为超时控制 */
  }

  while (1)
  {
    // bsp_Idle(); /* CPU空闲执行的操作， 见 bsp.c 和 bsp.h 文件 */

   
    if (Bsp_ESP8266_Timer_Check() == 0)
    {
      ret = 1; /* 超时 */
      break;
    }
    
    /*判断是否收到消息*/
    if (Bsp_UART_Read(&huart1, &ucData, 1))
    {
      if (ucData == _pAckStr[pos])
      {
        pos++;

        if (pos == len)
        {
          ret = 0; /* 收到指定的应答数据，返回成功 */
          break;
        }
      }
      else
      {
        pos = 0;
      }
    }
  }

  /*关中断*/
  if(ret == 0)
  {
    Bsp_ESP8266_Timer_Start(0);
  }

  return ret;
}

/**
 * @brief 读取ESP8266返回的一行应答字符串(0x0D 0x0A结束)。该函数根据字符间超时判断结束。 本函数需要紧跟AT命令发送函数。
 * @param {char} *_pBuf    存放模块返回的完整字符串
 * @param {uint16_t} _usBufSize   缓冲区最大长度
 * @param {uint16_t} _usTimeOut    命令执行超时，0表示一直等待. >0 表示超时时间，单位1ms
 * @return {uint16_t} 实际读取到数据长度
 */
uint16_t Bsp_ESP8266_ReadLine(char *_pBuf, uint16_t _usBufSize, uint16_t _usTimeOut)
{
  uint8_t ucData;
  uint16_t pos = 0;
  uint8_t ret;

  /* _usTimeOut == 0 表示无限等待 */
  if (_usTimeOut > 0)
  {
    Bsp_ESP8266_Timer_Start(_usTimeOut); /* 使用软件定时器作为超时控制 */
  }

  while (1)
  {
    // bsp_Idle(); /* CPU空闲执行的操作， 见 bsp.c 和 bsp.h 文件 */

    if (Bsp_ESP8266_Timer_Check() == 0)
    {
      _pBuf[pos] = 0; /* 结尾加0， 便于函数调用者识别字符串结束 */
      ret = pos;       
      break;
    }

    if (Bsp_UART_Read(&huart1, &ucData, 1))
    {

      Bsp_ESP8266_Timer_Start(500);

      _pBuf[pos++] = ucData; /* 保存接收到的数据 */

      if (ucData == 0x0A)
      {
        _pBuf[pos] = 0;
        ret = pos; /* 成功。 返回数据长度 */
        break;
      }
    }
  }

  /*关中断*/
  Bsp_ESP8266_Timer_Start(0);
  
  
  return ret;
}







/**
 * @brief 向模块发送AT命令。 本函数自动在AT字符串口增加<\r\n>字符
 * @param {char} *_Cmd
 * @return {*}
 */
void Bsp_ESP8266_SendAT(char *_Cmd)
{
  Bsp_UART_Write(&huart1, (uint8_t *)_Cmd, strlen(_Cmd));
  Bsp_UART_Write(&huart1, (uint8_t *)"\r\n", 2);

  Bsp_UART_Poll_DMA_TX(&huart1);
}

/**
 * @brief 清空RX的缓存
 * @return {*}
 */
void Bsp_ESP8266_Clear_RxBuffer(void)
{
  Bsp_UART_Get_RX_Buff_Occupy(&huart1);
}


/**
 * @brief 设置WiFi模块工作模式
 * @param {uint8_t} _mode 1 = Station模式,  2 = AP模式,  3 = AP兼Station模式
 * @return {uint8_t} 1 表示失败。 0表示成功
 */
uint8_t Bsp_ESP8266_SetWiFiMode(uint8_t _mode)
{
  char cmd_buf[30];

  if (_mode == 0 || _mode > 3)
  {
    _mode = 3;
  }
  sprintf(cmd_buf, "AT+CWMODE_DEF=%d", _mode);
  Bsp_ESP8266_SendAT(cmd_buf);
  if (Bsp_ESP8266_WaitResponse("OK\r\n", 2000) == 1)
  {
    return 1;
  }

  return 0;
}

/**
 * @brief 启动多连接模式
 * @param {uint8_t} _mode   0,表示关闭， 1表示启动
 * @return {uint8_t}1 表示失败。 0表示成功
 */
uint8_t Bsp_ESP8266_CIPMUX(uint8_t _mode)
{
  char cmd_buf[30];

  if (_mode > 0)
  {
    _mode = 1;
  }
  sprintf(cmd_buf, "AT+CIPMUX=%d", _mode);
  Bsp_ESP8266_SendAT(cmd_buf);
  if (Bsp_ESP8266_WaitResponse("OK\r\n", 1000) == 1)
  {
    return 1;
  }

  return 0;
}

/**
 * @brief AT+CIPAP 设置 AP 的 IP 地
 * @param {char} *_ip AP的IP地址，标准字符串
 * @return {uint8_t}1 表示失败。 0表示成功
 */
uint8_t Bsp_ESP8266_Set_AP_IP(char *_ip)
{
  char cmd_buf[30];

  sprintf(cmd_buf, "AT+CIPAP=\"%s\"", _ip);
  Bsp_ESP8266_SendAT(cmd_buf);
  if (Bsp_ESP8266_WaitResponse("OK\r\n", 500) == 1)
  {
    return 1;
  }

  return 0;
}

/**
 * @brief 设置SoftAP的名字，加密方式和密码.  加密方式为 。  保存到Flash
 * @param {char} *_name   AP的名字，字符串参数，密码最长 64 字节 ASCII
 * @param {char *} _pwd   AP的密码，字符串参数，密码最长 64 字节 ASCII
 * @param {uint8_t} _ch   通道号
 * @param {uint8_t} _ecn  加密方式  0:不加密 2:WPA 3:WPA2 4:WPA_WPA2
 * @return {uint8_t}1 表示失败。 0表示成功
 */
uint8_t Bsp_ESP8266_Set_AP_NamePass(char *_name, char *_pwd, uint8_t _ch, uint8_t _ecn)
{
  char cmd_buf[40];

  /* AT+CWSAP="ESP8266","1234567890",5,3 */
  sprintf(cmd_buf, "AT+CWSAP_DEF=\"%s\",\"%s\",%d,%d", _name, _pwd, _ch, _ecn);
  Bsp_ESP8266_SendAT(cmd_buf);
  if (Bsp_ESP8266_WaitResponse("OK\r\n", 500) == 1)
  {
    return 1;
  }

  return 0;
}

/**
 * @brief 设置上电是否自动连接WIFI
 * @param {uint8_t} Enable
 * @return {*}
 */
uint8_t Bsp_ESP8266_Set_AutoLink(uint8_t Enable)
{
  if(Enable == 1)
  {
    Bsp_ESP8266_SendAT("AT+CWAUTOCONN=1");  
  }
  else
  {
    Bsp_ESP8266_SendAT("AT+CWAUTOCONN=0");  
  }

  if (Bsp_ESP8266_WaitResponse("OK\r\n", 1000) == 1)
  {
    return 1;
  }

  return 0;
}


/**
 * @brief 是否开启回显
 * @param {uint8_t} Enable  1:开启  0:关闭
 * @return {uint8_t}1 表示失败。 0表示成功
 */
uint8_t Bsp_ESP8266_Echo(uint8_t Enable)
{
 
  if(Enable == 1)
  {
    Bsp_ESP8266_SendAT("ATE1");  
  }
  else
  {
    Bsp_ESP8266_SendAT("ATE0");  
  }

  if (Bsp_ESP8266_WaitResponse("OK\r\n", 1000) == 1)
  {
    return 1;
  }
  
  return 0;
}

/**
 * @brief 上电是否自动连接WIFI
 * @param {uint8_t} Enable
 * @return {*}
 */
uint8_t Bsp_ESP8266_Auto_LinkWifi(uint8_t Enable)
{
 
  if(Enable == 1)
  {
    Bsp_ESP8266_SendAT("AT+CWAUTOCONN=1");  
  }
  else
  {
    Bsp_ESP8266_SendAT("AT+CWAUTOCONN=0");  
  }

  if (Bsp_ESP8266_WaitResponse("OK\r\n", 1000) == 1)
  {
    return 1;
  }

  return 0;
}


/**
 * @brief 按键反馈功能使能
 * @param {uint8_t} Enable
 * @return {*}
 */
uint8_t Bsp_ESP8266_KEY_Enable(uint8_t Enable)
{
    if(Enable == 1)
  {
    Bsp_ESP8266_SendAT("AT+KEY=1");  
  }
  else
  {
    Bsp_ESP8266_SendAT("AT+KEY=0");  
  }

  if (Bsp_ESP8266_WaitResponse("OK\r\n", 1000) == 1)
  {
    return 1;
  }

  return 0;
}


/**
 * @brief 创建TCP服务器。 必须在连接到AP之后才行。 需要先启用多连接
 * @param {uint16_t} _TcpPort   TCP 端口号
 * @return {uint8_t}1 表示失败。 0表示成功
 */
uint8_t Bsp_ESP8266_CreateTCPServer(uint16_t _TcpPort)
{
  char cmd_buf[30];

  /* 启动多连接 */
  if (Bsp_ESP8266_CIPMUX(1) == 1)
  {
    return 1;
  }

  /* 开启TCP server, 端口为 _TcpPort */
  sprintf(cmd_buf, "AT+CIPSERVER=1,%d", _TcpPort);
  Bsp_ESP8266_SendAT(cmd_buf);
  if (Bsp_ESP8266_WaitResponse("OK\r\n", 2000) == 1)
  {
    return 1;
  }

  Bsp_ESP8266_Echo(0);

  return 0;
}

/**
 * @brief 创建UDP服务器。 必须在连接到AP之后才行。 需要先启用多连接
 * @param {uint8_t} _id 连接ID, 0-4
 * @param {uint16_t} _Far_Port  UDP远端端口号
 * @param {uint16_t} _LaocalPort  UDP本地端口号
 * @return {uint8_t}1 表示失败。 0表示成功
 */
uint8_t Bsp_ESP8266_CreateUDPServer(uint8_t _id, uint16_t _Far_Port , uint16_t _LaocalPort)
{
  char cmd_buf[64];

  /* 启动多连接 */
  if (Bsp_ESP8266_CIPMUX(1) == 1)
  {
    return 1;
  }

  /* 多连接 UDP */
  // AT+CIPSTART=0,"UDP","255.255.255.255",8080,8080,0
  sprintf(cmd_buf, "AT+CIPSTART=%d,\"UDP\",\"255.255.255.255\",%d,%d,2", _id,_Far_Port ,_LaocalPort);

  // AT+CIPSTART="UDP","255.255.255.255",8080,8080,1
  // sprintf(cmd_buf, "AT+CIPSTART=\"UDP\",\"255.255.255.255\",8080,%d,2", _LaocalPort);

  Bsp_ESP8266_SendAT(cmd_buf);
  if (Bsp_ESP8266_WaitResponse("OK\r\n", 3000) == 1)
  {
    return 1;
  }

  Bsp_ESP8266_Echo(0);

  return 0;
}

/**
 * @brief 连接到TCP服务器 多连接模式。
 * @param {uint8_t} _id 连接的id号
 * @param {char} *_server_ip  服务器域名或IP地址
 * @param {uint16_t} _TcpPort TCP 端口号
 * @return {uint8_t}1 表示失败。 0表示成功
 */
uint8_t Bsp_ESP8266_LinkTCPServer(uint8_t _id, char *_server_ip, uint16_t _TcpPort)
{
  char cmd_buf[30];

  /* 启动多连接 */
  if (Bsp_ESP8266_CIPMUX(1) == 1)
  {
    return 1;
  }

#if 0 /* 单连接 */
	//AT+CIPSTART="TCP","192.168.101.110",1000
	sprintf(cmd_buf, "AT+CIPSTART=\"TCP\",\"%s\",%d",_server_ip, _TcpPort);
#else /* 多连接 */
  // AT+CIPSTART=0, "TCP","192.168.101.110",1000
  sprintf(cmd_buf, "AT+CIPSTART=%d,\"TCP\",\"%s\",%d", _id, _server_ip, _TcpPort);
#endif

  Bsp_ESP8266_SendAT(cmd_buf);
  if (Bsp_ESP8266_WaitResponse("OK\r\n", 3000) == 0)
  {
    return 0;
  }

  Bsp_ESP8266_Echo(0);

  return 1;
}

/**
 * @brief 发送TCP或UDP数据包
 * @param {uint8_t} _id 多连接时，连接ID （0-4）
 * @param {uint8_t} *_databuf 数据
 * @param {uint16_t} _len 数据长度
 * @return {uint8_t}1 表示失败。 0表示成功
 */
uint8_t Bsp_ESP8266_SendTcpUdp(uint8_t _id, uint8_t *_databuf, uint16_t _len)
{
  char buf[32];
 
  if (_len > 2048)
  {
    _len = 2048;
  }

  sprintf(buf, "AT+CIPSEND=%d,%d\r\n", _id, _len);

  Bsp_UART_Write(&huart1, (uint8_t *)buf, strlen(buf));
  Bsp_UART_Poll_DMA_TX(&huart1);

  if (Bsp_ESP8266_WaitResponse(">\r\n", 1000) == 1)
  {
    return 1;
  }

  Bsp_UART_Write(&huart1, (uint8_t *)_databuf, _len);
  Bsp_UART_Poll_DMA_TX(&huart1);

  if (Bsp_ESP8266_WaitResponse("SEND OK\r\n", 8000) == 1)
  {
    return 1;
  }

  return 0;
}

/**
 * @brief 关闭TCP或UDP连接. 用于多路连接
 * @param {uint8_t} _id 连接ID （0-4）
 * @return {*}
 */
void Bsp_ESP8266_CloseTcpUdp(uint8_t _id)
{
  char buf[32];

  sprintf(buf, "AT+CIPCLOSE=%d", _id);
  Bsp_ESP8266_SendAT(buf);
  Bsp_ESP8266_WaitResponse("OK\r\n", 200);
}

/**
 * @brief 查询本机IP地址和MAC
 * @param {char} *_ip 
 * @param {char} *_mac  
 * @return {uint8_t} 0:成功   1:失败
 */
uint8_t Bsp_ESP8266_GetLocalIP(char *_ip, char *_mac)
{
  char buf[64] = {0};
  uint8_t i, m;
  uint8_t ret = 1;
  uint8_t temp;

  Bsp_ESP8266_SendAT("AT+CIFSR");

  /*　模块将应答:

  +CIFSR:STAIP,"192.168.1.18"
  +CIFSR:STAMAC,"18:fe:34:a6:44:75"

  OK
  */

  _ip[0] = 0;
  _mac[0] = 0;
  for (i = 0; i < 4; i++)
  {
    Bsp_ESP8266_ReadLine(buf, sizeof(buf), 500);
    if (memcmp(buf, "+CIFSR:STAIP", 12) == 0)
    {

      for (m = 0; m < 20; m++)
      {
        temp = buf[14 + m];
        _ip[m] = temp;
        if (temp == '"')
        {
          _ip[m] = 0;
          ret = 0;
          break;
        }
      }
    }
    else if (memcmp(buf, "+CIFSR:STAMAC,", 14) == 0)
    {
      for (m = 0; m < 20; m++)
      {
        temp = buf[15 + m];
        _mac[m] = temp;
        if (temp == '"')
        {
          _mac[m] = 0;
          break;
        }
      }
    }
    else if (memcmp(buf, "OK", 2) == 0)
    {
      break;
    }
  }
  return ret;
}

/**
 * @brief 加入AP(保存到Flash)
 * @param {char} *_ssid AP名字字符串
 * @param {char} *_pwd  密码字符串
 * @param {uint16_t} _timeout
 * @return {uint8_t} 0:成功   1:失败
 */
uint8_t Bsp_ESP8266_JoinAP(char *_ssid, char *_pwd, uint16_t _timeout)
{
  char buf[100];
  uint8_t ret;

  sprintf(buf, "AT+CWJAP_DEF=\"%s\",\"%s\"", _ssid, _pwd);
  Bsp_ESP8266_SendAT(buf);

  ret = Bsp_ESP8266_WaitResponse("OK\r\n", _timeout);
  if (ret == 1)
  {
    return 1;
  }


  return 0;
}

/**
 * @brief 退出当前的AP连接
 * @return {*}
 */
void Bsp_ESP8266_QuitAP(void)
{
  Bsp_ESP8266_SendAT("AT+CWQAP");
  Bsp_ESP8266_WaitResponse("OK\r\n", 300);
}

/**
 * @brief 扫描AP。结果存放在_pList 结构体数组. 此函数会占用最长5秒时间。直到收到OK或ERROR。
 * @param {WIFI_AP_T} *_pList   AP列表数组;
 * @param {uint16_t} _MaxNum  搜索的最大AP个数。主要是防止缓冲区溢出。
 * @return {*}-1 表示失败; 0 表示搜索到0个; 1表示1个。
 */
int16_t Bsp_ESP8266_ScanAP(WIFI_AP_T *_pList, uint16_t _MaxNum)
{
  uint16_t i;
  uint16_t count;
  char buf[128];
  WIFI_AP_T *p;
  char *p1, *p2;
  uint16_t timeout;

  buf[127] = 0;

  /*设置WIFI模式*/
  if (Bsp_ESP8266_SetWiFiMode(1) == 1)
  {
    return 1;
  }

  Bsp_ESP8266_SendAT("AT+CWLAP");

  p = (WIFI_AP_T *)_pList;
  count = 0;
  timeout = 8000;

  for (i = 0; i < _MaxNum; i++)
  {
    Bsp_ESP8266_ReadLine(buf, 128, timeout);
    if (memcmp(buf, "OK", 2) == 0)
    {
      break;
    }
    else if (memcmp(buf, "ERROR", 5) == 0)
    {
      break;
    }
    else if (memcmp(buf, "+CWLAP:", 7) == 0)
    {
      p1 = buf;

      /* +CWLAP:(4,"BaiTu",-87,"9c:21:6a:3c:89:52",1) */
      /* 解析加密方式 */
      p1 = strchr(p1, '('); /* 搜索到(*/
      p1++;
      p->ecn = str_to_int(p1);

      /* 解析ssid */
      p1 = strchr(p1, '"'); /* 搜索到第1个分号 */
      p1++;
      p2 = strchr(p1, '"'); /* 搜索到第2个分号 */
      memcpy(p->ssid, p1, p2 - p1);
      p->ssid[p2 - p1] = 0;

      /* 解析 rssi */
      p1 = strchr(p2, ','); /* 搜索到逗号*/
      p1++;
      p->rssi = str_to_int(p1);

      /* 解析mac */
      p1 = strchr(p1, '"'); /* 搜索到分号*/
      p1++;
      p2 = strchr(p1, '"'); /* 搜索到分号*/
      memcpy(p->mac, p1, p2 - p1);
      p->mac[p2 - p1] = 0;

      /* 解析ch */
      p1 = strchr(p2, ','); /* 搜索到逗号*/
      p1++;
      p->ch = str_to_int(p1);

      /* 有效的AP名字 */
      count++;

      p++;

      timeout = 2000;
    }
  }

  return count;
}


/**
 * @brief 查询当前连接状态
 * @return {*}
 */
uint8_t Bsp_ESP8266_QueryLink(void)
{
  char Buff[32]={0};
  char *p;
  uint8_t state = 0;
  Bsp_ESP8266_SendAT("AT+CIPSTATUS");


  for(uint8_t i = 0 ; i < 4 ; i++)
  {
    Bsp_ESP8266_ReadLine(Buff, sizeof(Buff), 2000);

    if(memcmp(Buff , "STATUS:" , 7) == 0)
    {
      p = Buff;
      p = strchr(Buff, ':');    //搜索到冒号
      p++;
      state = str_to_int(p);
    }

    if(memcmp(Buff , "OK\r\n" , 4) == 0)
    {
      break;
    }

  }

  
  return state;
}





