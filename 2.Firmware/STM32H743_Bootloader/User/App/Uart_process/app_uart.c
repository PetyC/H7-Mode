/*
 * @Description: 串口数据处理
 * @Autor: Pi
 * @Date: 2022-07-04 19:10:36
 * @LastEditTime: 2022-07-20 19:56:15
 */
#include "App_Uart.h"

/*相关句柄*/
extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim12;

/*内部使用变量*/
#define UART_BUFFER_LEN 1024 //串口接收缓存长度
#define UART_BUFFER_HALF (uint16_t)(UART_BUFFER_LEN / 2)
uint8_t Uart_Buffer[UART_BUFFER_LEN]; //串口接收缓存

static uint16_t Overflow_Max = UART_BUFFER_HALF;
static uint16_t RX_Size_Max = UART_BUFFER_LEN; //单次读取长度

static uint16_t Timeout_Max = 1; //串口接收超时最大时间   5ms * Timeout_Max = Timeout
static uint8_t Timeout_Flag = 0; //串口接收超时标志

static uint8_t Full_Flag = 0;      //接收数据满一帧长度标志
static uint8_t Full_Half_Flag = 0; //接收数据满一半长度标志

/*外部使用变量*/
void (*User_UART_RX_Fun)(uint8_t *data, uint16_t len);
void (*User_UART_RX_Finished)(uint8_t *data, uint16_t len);
void (*User_UART_RX_None)(void);

/*内部使用函数*/
static uint8_t User_UART_Query_Timeout(void);
static void User_UART_Timer_Enable(uint8_t Enable);

/**
 * @brief 串口接收 数据处理状态机 循环调用
 * @return {*}
 */
void User_UART_RX_Loop(void)
{
  uint16_t RX_Reality_Size = Bsp_UART_Get_RX_Buff_Occupy(&huart1);

  if (RX_Reality_Size > 0 && RX_Reality_Size < UART_BUFFER_HALF)
  {
    if (Full_Flag == 0)
    {
      Full_Half_Flag = 0;
      Full_Flag = 1;
      User_UART_Timer_Enable(1); //开启定时器
    }
  }
  else if (RX_Reality_Size >= UART_BUFFER_HALF)
  {
    if (Full_Half_Flag == 0)
    {
      Full_Flag = 0;
      Full_Half_Flag = 1;
      User_UART_Timer_Enable(1); //开启定时器
    }

    uint16_t size = Bsp_UART_Read(&huart1, Uart_Buffer, RX_Size_Max);
    User_UART_RX_Fun(Uart_Buffer, size); //调用数据处理函数
  }

  /*若收到数据 则查询是否超时*/
  if (User_UART_Query_Timeout() == 1)
  {
    Full_Flag = 0;
    Full_Half_Flag = 0;
    uint16_t size = Bsp_UART_Read(&huart1, Uart_Buffer, RX_Size_Max);
    User_UART_RX_Finished(Uart_Buffer, size); //则调用完成函数
  }
  else if((Full_Flag != 1) && (Full_Half_Flag != 1))
  {
    if(User_UART_RX_None != NULL)
    {
      User_UART_RX_None();  
    }
 
  }
}



/**
 * @brief 定时中断服务函数
 * @return {*}
 */
void User_UART_Timer(void)
{
  static uint16_t Count = 0;
  Count++;

  if (Count >= Timeout_Max)
  {
    Count = 0;
    Timeout_Flag = 1;

    HAL_TIM_Base_Stop_IT(&htim13);
    __HAL_TIM_SetCounter(&htim13, 0);
  }
}

/**
 * @brief 定时器使能
 * @param {uint8_t} Enable
 * @return {*}
 */
void User_UART_Timer_Enable(uint8_t Enable)
{
  if (Enable)
  {
    __HAL_TIM_CLEAR_FLAG(&htim13, TIM_FLAG_UPDATE);
    HAL_TIM_Base_Start_IT(&htim13);
  }
  else
  {
    HAL_TIM_Base_Stop_IT(&htim13);
    __HAL_TIM_SetCounter(&htim13, 0);
  }
}

/**
 * @brief 循环查询是否超时
 * @return {uint8_t} 1:已超时     0:未超时
 */
uint8_t User_UART_Query_Timeout(void)
{
  if (Timeout_Flag == 1)
  {
    Timeout_Flag = 0;
    return 1;
  }
  else
  {
    return 0;
  }
}

/**
 * @brief 设置从串口读取数据长度最大值
 * @param {uint16_t} Size
 * @return {*}
 */
void User_UART_RX_Size_Max(uint16_t Size)
{
  if (Size < UART_BUFFER_LEN)
  {
    RX_Size_Max = Size;
  }
  else
  {
    RX_Size_Max = UART_BUFFER_LEN;
  }
}


/**
 * @brief 单帧最短长度
 * @param {uint16_t} Size
 * @return {*}
 */
void User_UART_RX_Overflow_Max(uint16_t Size)
{
  if(Overflow_Max > UART_BUFFER_LEN)
  {
    
  }
  else
  {
    Overflow_Max = Size;
  }
}


/**
 * @brief 设置串口超时最大时间 默认5ms 5ms*Timeout=Timeout_Max
 * @param {uint16_t} Timeout  最大超时时间    5ms * Timeout = Timeout_Max
 * @return {*}
 */
void User_Uart_RX_Timeout_Set(uint16_t Timeout)
{
  Timeout_Max = Timeout;
}

/************************测试用函数********************/

/**
 * @brief 串口回显 测试用
 * @param {uint8_t} *data
 * @param {uint16_t} len
 * @return {*}
 */
void User_UART_Echo(uint8_t *data, uint16_t len)
{
  Bsp_UART_Write(&huart1, data, len);
  // Bsp_UART_Poll_DMA_TX(&huart1);
}

/**
 * @brief 串口接收完成 测试用
 * @return {*}
 */
void User_UART_Finished_Demo(uint8_t *data, uint16_t len)
{
  // Bsp_UART_Write(&huart1, "Uart RX is finished!\r\n", 21);
  // Bsp_UART_Poll_DMA_TX(&huart1);
  Bsp_UART_Write(&huart1, data, len);
}

static uint8_t Time_Out_Flag = 0;

/**
 * @brief 将FIFO中的数据循环发送出去
 * @return {*}
 */
void User_UART_TX_Loop(void)
{
  uint16_t Buff_Occupy = Bsp_UART_Get_TX_Buff_Occupy(&huart1);

  if (Buff_Occupy > 0 && Buff_Occupy < 512)
  {
    //串口超时定时器开启
    if (Time_Out_Flag == 0)
    {
      Time_Out_Flag = 1;
      __HAL_TIM_CLEAR_FLAG(&htim12, TIM_FLAG_UPDATE);
      HAL_TIM_Base_Start_IT(&htim12);
    }
    //定时器超时
    if (Time_Out_Flag == 1)
    {
      Time_Out_Flag = 0;
      Bsp_UART_Poll_DMA_TX(&huart1);
    }
  }
  else if (Buff_Occupy > 256)
  {
    Bsp_UART_Poll_DMA_TX(&huart1);

    if (Time_Out_Flag == 1)
    {
      Time_Out_Flag = 0;

      HAL_TIM_Base_Stop(&htim12);
      __HAL_TIM_SetCounter(&htim12, 0);
    }
  }
}

/**
 * @brief 串口发送中断服务函数
 * @return {*}
 */
void User_UART_TX_Timer(void)
{
  Time_Out_Flag = 1;
}
