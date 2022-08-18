/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-04-14 16:11:43
 * @LastEditTime: 2022-04-28 22:10:00
 */
#include "Dev_Uart.h"

/* 串口缓存大小 */
#define UART1_TX_BUF_SIZE 512
#define UART1_RX_BUF_SIZE 512
#define UART1_DMA_RX_BUF_SIZE 512
#define UART1_DMA_TX_BUF_SIZE 512


/* 串口缓存 */
static uint8_t s_uart1_tx_buf[UART1_TX_BUF_SIZE];
static uint8_t s_uart1_rx_buf[UART1_RX_BUF_SIZE];
static uint8_t s_uart1_dmarx_buf[UART1_DMA_RX_BUF_SIZE];
static uint8_t s_uart1_dmatx_buf[UART1_DMA_TX_BUF_SIZE];



/* 串口设备实例 */
static Uart_Device_Str Uart_Dev_0 = {0};

 



/*内部使用函数*/
static void fifo_lock(void);
static void fifo_unlock(void);
static void User_UART_RxHalfCplt_Callback(UART_HandleTypeDef *huart);
static void User_UART_RxCplt_Callback(UART_HandleTypeDef *huart);
static void User_UART_IDLE_Callback(UART_HandleTypeDef *huart);
static void User_UART_TX_Cplt_Callback(UART_HandleTypeDef *huart);

/* fifo上锁函数 */
static void fifo_lock(void)
{
  __disable_irq();
}

/* fifo解锁函数 */
static void fifo_unlock(void)
{
  __enable_irq();
}




/**
 * @brief 串口设备实例化
 * @param {*}
 * @return {*}
 */
void Uart_Device_init(UART_HandleTypeDef *huart)
{
  if(huart == &huart1)
  {
    /* 配置串口1收发fifo */
    fifo_register(&Uart_Dev_0.tx_fifo, &s_uart1_tx_buf[0], sizeof(s_uart1_tx_buf), fifo_lock, fifo_unlock);
    fifo_register(&Uart_Dev_0.rx_fifo, &s_uart1_rx_buf[0], sizeof(s_uart1_rx_buf), fifo_lock, fifo_unlock);

    /* 配置串口1 DMA收发buf */
    Uart_Dev_0.dmarx_buf = &s_uart1_dmarx_buf[0];
    Uart_Dev_0.dmarx_buf_size = sizeof(s_uart1_dmarx_buf);
    Uart_Dev_0.dmatx_buf = &s_uart1_dmatx_buf[0];
    Uart_Dev_0.dmatx_buf_size = sizeof(s_uart1_dmatx_buf);

    /*初始化串口1状态*/
    Uart_Dev_0.TX_Status = 0;
    Uart_Dev_0.RX_Status = 0;

    /* 只需配置接收模式DMA，发送模式需发送数据时才配置 */
    HAL_UART_Receive_DMA(&huart1, Uart_Dev_0.dmarx_buf, sizeof(s_uart1_dmarx_buf));
  }
  
}

/**
 *
 * @brief 串口发送数据接口，实际是写入发送fifo，发送由dma处理
 * @param {uint8_t} uart_id
 * @param {uint8_t} *buf
 * @param {uint16_t} size
 * @return {*}
 */
uint16_t User_UART_Write(UART_HandleTypeDef *huart, const uint8_t *buf, uint16_t size)
{
  if(huart == &huart1)
  {
    return fifo_write(&Uart_Dev_0.tx_fifo, buf, size);
  }
	else
	{
		return 0;
	}
}

/**
 * @brief 串口读取数据接口，实际是从接收fifo读取
 * @param {uint8_t} uart_id  串口号
 * @param {uint8_t} *buf  读出数据缓存区
 * @param {uint16_t} size 长度
 * @return {uint16_t} 实际读大小
 */
uint16_t User_UART_Read(UART_HandleTypeDef *huart, uint8_t *buf, uint16_t size)
{
  if(huart == &huart1)
  {
    return fifo_read(&Uart_Dev_0.rx_fifo, buf, size);
  }
	else
	{
		return 0;
	}
}


/**
 * @brief 用户自定义 串口DMA接收一半的回调函数.
 * @param {UART_HandleTypeDef} *huart
 * @return {*}
 */
static void User_UART_RxHalfCplt_Callback(UART_HandleTypeDef *huart)
{

  if(huart == &huart1)
  {
    uint16_t recv_total_size;
    uint16_t recv_size;

    /*DMA通道接收总数据大小*/
    recv_total_size = Uart_Dev_0.dmarx_buf_size - __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);


    /*获取接收数据量*/
    recv_size = recv_total_size - Uart_Dev_0.last_dmarx_size;

    fifo_write(&Uart_Dev_0.rx_fifo, (const uint8_t *)&(Uart_Dev_0.dmarx_buf[Uart_Dev_0.last_dmarx_size]), recv_size);

    /*更新本次接收的数据长度*/
    Uart_Dev_0.last_dmarx_size = recv_total_size;
  
  }

}

/**
 * @brief  用户自定义串口DMA接收完成的回调函数.
 * @param {UART_HandleTypeDef} *huart
 * @return {*}
 */
static void User_UART_RxCplt_Callback(UART_HandleTypeDef *huart)
{
  
  if(huart == &huart1)
  {
    uint16_t recv_size;

    /*接收数据长度*/
    recv_size = Uart_Dev_0.dmarx_buf_size - Uart_Dev_0.last_dmarx_size;

    /*接着上次写入数据后面继续写入*/
    fifo_write(&Uart_Dev_0.rx_fifo, (const uint8_t *)&(Uart_Dev_0.dmarx_buf[Uart_Dev_0.last_dmarx_size]), recv_size);

    Uart_Dev_0.last_dmarx_size = 0;
  }

}



/**
 * @brief 用户自定义串口空闲中断服务函数
 * @param {UART_HandleTypeDef} *huart
 * @return {*}
 */
static void User_UART_IDLE_Callback(UART_HandleTypeDef *huart)
{

  if(huart == &huart1)
  {
    uint16_t recv_total_size;
    uint16_t recv_size;

    /*DMA通道接收总数据大小*/
    recv_total_size = Uart_Dev_0.dmarx_buf_size -  __HAL_DMA_GET_COUNTER(&hdma_usart1_rx);

    recv_size = recv_total_size - Uart_Dev_0.last_dmarx_size;

    fifo_write(&Uart_Dev_0.rx_fifo, (const uint8_t *)&(Uart_Dev_0.dmarx_buf[Uart_Dev_0.last_dmarx_size]), recv_size);

    Uart_Dev_0.last_dmarx_size = recv_total_size;

    /*接收到一条消息*/
    Uart_Dev_0.RX_Status = 1;
  }

}


/**
 * @brief 用户定义的串口DMA发送完成的回调函数.
 * @param {UART_HandleTypeDef} *huart
 * @return {*}
 */
static void User_UART_TX_Cplt_Callback(UART_HandleTypeDef *huart)
{
  if(huart == &huart1)
  {
    Uart_Dev_0.TX_Status = 0; /* DMA发送空闲 */
  }

}


/**
 * @brief 用户串口函数初始化
 * @param {*}
 * @return {*}
 */
void User_UART_Init(UART_HandleTypeDef *huart)
{

  Uart_Device_init(huart);
  __HAL_UART_ENABLE_IT(huart, UART_IT_IDLE); //开启空闲中断
  __HAL_UART_CLEAR_IDLEFLAG(huart);          //清除空闲中断标志 否者上电会进入中断
  
 
}


/**
 * @brief 用户自定义串口中断函数
 * @param {UART_HandleTypeDef} *huart
 * @return {*}
 */
void User_UART_IRQHandler(UART_HandleTypeDef *huart)
{

  if(huart == &huart1)
  {

    if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) == SET) //判断是否是空闲中断
    {
      __HAL_UART_CLEAR_IDLEFLAG(huart); //清除空闲中断标志（否则会一直不断进入中断）

      User_UART_IDLE_Callback(huart);
    }

  }
}



/**
 * @brief  循环从串口发送fifo读出数据，放置于dma发送缓存，并启动dma传输
 * @param
 * @retval
 */
void User_UART_Poll_DMA_TX(UART_HandleTypeDef *huart)
{

  uint16_t size = 0;

  if (0x01 == Uart_Dev_0.TX_Status)
  {
    return;
  }
  
  size = fifo_read(&Uart_Dev_0.tx_fifo, Uart_Dev_0.dmatx_buf, Uart_Dev_0.dmatx_buf_size);

  if (size != 0)
  {
    Uart_Dev_0.TX_Status = 0x01; /* DMA发送状态 */

    if(huart == &huart1)
    {
      HAL_UART_Transmit_DMA(&huart1, Uart_Dev_0.dmatx_buf, size);
    }
    
  }
}



/**
 * @brief 获取串口接收消息标志
 * @param {UART_HandleTypeDef} *huart
 * @return {uint8_t}0:接收到一条消息  1:没有消息
 */
uint8_t User_UART_Get_RX_Flag(UART_HandleTypeDef *huart)
{
  
  if( Uart_Dev_0.RX_Status == 1)
  {
    Uart_Dev_0.RX_Status = 0;
    return 0;
  }
  else
  {
    return 1;
  }
  
}



/**
 * @brief 串口DMA接收一半的回调函数.
 * @param None
 * @retval None
 */
void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart)
{
  User_UART_RxHalfCplt_Callback(huart);
}


/**
 * @brief 串口DMA接收完成的回调函数.
 * @param None
 * @retval None
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  User_UART_RxCplt_Callback(huart);
}


/**
 * @brief 串口DMA发送完成的回调函数.
 * @param None
 * @retval None
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  User_UART_TX_Cplt_Callback(huart);
}





