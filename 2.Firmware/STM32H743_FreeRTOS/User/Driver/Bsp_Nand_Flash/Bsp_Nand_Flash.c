/*
 * @Description: Nand Flash
 * @Autor: Pi
 * @Date: 2022-04-11 16:40:52
 * @LastEditTime: 2022-09-02 04:13:06
 */
#include "Bsp_Nand_Flash.h"
#include <string.h>



/*内部使用函数*/
static uint32_t Bsp_Nand_ReadStatus(void);
static uint32_t Bsp_Nand_GetStatus(void);

/**
 * @brief 初始化Nand Flash 通过判断ID是否正确
 * @param {*}
 * @return {uint8_t}    0:成功  1:失败
 */
uint8_t Bsp_Nand_Init(void)
{
  NAND_IDTypeDef NAND_ID = {0};

  HAL_NAND_Reset(&hnand1);

	/* 检查操作状态 */
	if (Bsp_Nand_GetStatus() != NAND_READY)
	{
		return 1;
	}

  HAL_NAND_Read_ID(&hnand1, &NAND_ID);

  uint32_t Nand_Flash_ID = 0;

  Nand_Flash_ID = NAND_ID.Device_Id << 16;

  Nand_Flash_ID |= NAND_ID.Third_Id << 8;

  Nand_Flash_ID |= NAND_ID.Fourth_Id;

  if (Nand_Flash_ID != MT29F4G08ABADA)
  {
    return 1;
  }

  return 0;
}




/**
 * @brief 获取NAND Flash操作状态
 * @return {*}NAND_TIMEOUT_ERROR:超时错误    NAND_READY:操作成功    NAND_ERROR:先前的命令执行失败
 */
static uint32_t Bsp_Nand_GetStatus(void)
{
	uint32_t ulTimeout = 0x10000;
	uint32_t ucStatus = NAND_READY;

	ucStatus = Bsp_Nand_ReadStatus();

	/* 等待NAND操作结束，超时后会退出 */
	while ((ucStatus != NAND_READY) &&( ulTimeout != 0x00))
	{
		ucStatus = Bsp_Nand_ReadStatus();
		if(ucStatus == NAND_ERROR)
		{
			/* 返回操作状态 */
			return (ucStatus);
		}
		ulTimeout--;
	}

	if(ulTimeout == 0x00)
	{
		ucStatus =  NAND_TIMEOUT_ERROR;
	}

	/* 返回操作状态 */
	return (ucStatus);
}



/**
 * @brief 使用Read statuc 命令读NAND Flash内部状态
 * @return {*}NAND_BUSY: 内部正忙   NAND_READY: 内部空闲，可以进行下步操作    NAND_ERROR: 先前的命令执行失败
 */
static uint32_t Bsp_Nand_ReadStatus(void)
{
	uint8_t ucData;
	uint8_t ucStatus = NAND_BUSY;

	/* 读状态操作 */
	NAND_CMD_AREA = NAND_CMD_STATUS;
	ucData = *(__IO uint8_t *)(Bank_NAND_ADDR);

	if((ucData & NAND_ERROR) == NAND_ERROR)
	{
		ucStatus = NAND_ERROR;
	}
	else if((ucData & NAND_READY) == NAND_READY)
	{
		ucStatus = NAND_READY;
	}
	else
	{
		ucStatus = NAND_BUSY;
	}

	return (ucStatus);
}



#include "Bsp_Uart.h"
#include <stdio.h>
#include <string.h>

#define NAND_PAGE_SIZE (2048 * 32)
static  uint8_t Nand_Buff[NAND_PAGE_SIZE];
static  uint8_t Nand_Buff2[NAND_PAGE_SIZE];

static void Demo_Print(void);
double Tick_0 = 0;
double Tick_1 = 0;
double Tick = 0;

void NAND_Demo(void)
{
  NAND_AddressTypeDef Nand_Add;
  Nand_Add.Plane = 0;
  Nand_Add.Block = 0;
  Nand_Add.Page = 0;

  HAL_StatusTypeDef Status = HAL_ERROR;

  /*擦除数据*/
  for(uint8_t i = 0 ; i<32 ; i++)
  {
    Nand_Add.Page = i;
    Status = HAL_NAND_Erase_Block(&NAND_HANDLE , &Nand_Add);
  }
  Nand_Add.Page = 0;

  /*准备写入数据*/
  for(uint16_t i = 0; i < NAND_PAGE_SIZE; i++)
  {
    Nand_Buff[i] = i & 0x00FF;
  }

  /*写入数据*/
  __set_PRIMASK(1);
  Tick_0 = HAL_GetTick();
  Status = HAL_NAND_Write_Page_8b(&hnand1, &Nand_Add, Nand_Buff, 32);
  Tick_1 = HAL_GetTick();
  __set_PRIMASK(0);



  Tick = Tick_1 - Tick_0;
  uint8_t TX_Buff[128] = {0};
  uint8_t len = 0;
  len = sprintf((char *)TX_Buff , "写入总用时:%f\r\n" , Tick );
  Bsp_UART_Write(&huart1 , TX_Buff , len);
  memset(Nand_Buff2, 0, NAND_PAGE_SIZE);

  __set_PRIMASK(1);
  Tick_0 = HAL_GetTick();
  Status = HAL_NAND_Read_Page_8b(&hnand1, &Nand_Add, Nand_Buff2, 32);
  Tick_1 = HAL_GetTick();
  __set_PRIMASK(0);
  
  Tick = Tick_1 - Tick_0;
  len = sprintf((char *)TX_Buff , "读取总用时:%f\r\n" , Tick );
  Bsp_UART_Write(&huart1 , TX_Buff , len);
  //Demo_Print();
  
  for(uint32_t i = 0 ; i < NAND_PAGE_SIZE; i++)
  {
    if(Nand_Buff2[i] != Nand_Buff[i])
    {
      while(1);
      len = sprintf((char *)TX_Buff , "写入数据出现错误\r\n" );
      Bsp_UART_Write(&huart1 , TX_Buff , len); 
      Bsp_UART_Poll_DMA_TX(&huart1);
    }
  }
 
  len = sprintf((char *)TX_Buff , "写入数据无错误\r\n" );
  Bsp_UART_Write(&huart1 , TX_Buff , len); 
  Bsp_UART_Poll_DMA_TX(&huart1);
}


 
static void Demo_Print(void)
{
  uint8_t TX_Buff[128] = {0};

  for(uint16_t i = 0; i < NAND_PAGE_SIZE; i++)
  {
    uint16_t len = sprintf((char *)TX_Buff , "Data[%04d]=0x%02X " , i ,Nand_Buff2[i]);
    Bsp_UART_Write(&huart1 , TX_Buff , len);

    if((i+1) % 5 == 0 && i != 0)
    {
      Bsp_UART_Write(&huart1 , "\r\n" , 2);
    }

    if(Bsp_UART_Get_TX_Buff_Occupy(&huart1) >= 1024)
    {
      Bsp_UART_Poll_DMA_TX(&huart1);
      HAL_Delay(10);
    }

    memset(TX_Buff , 0 , sizeof(TX_Buff));
  }


  while(Bsp_UART_Get_TX_Buff_Occupy(&huart1) != 0)
  {
    Bsp_UART_Poll_DMA_TX(&huart1);
    HAL_Delay(10);
  }
  
  Bsp_UART_Write(&huart1 , "\r\n" , 2);
  Bsp_UART_Poll_DMA_TX(&huart1);
}
