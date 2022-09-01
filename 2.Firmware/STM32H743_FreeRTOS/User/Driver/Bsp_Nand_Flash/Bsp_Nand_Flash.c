/*
 * @Description: Nand Flash
 * @Autor: Pi
 * @Date: 2022-04-11 16:40:52
 * @LastEditTime: 2022-09-01 19:58:35
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

#define NAND_PAGE_SIZE (2048)
uint8_t Nand_Buff[NAND_PAGE_SIZE];
uint8_t TX_Buff[15];

void NAND_Demo(void)
{
  NAND_AddressTypeDef Nand_Add;
  Nand_Add.Plane = 0;
  Nand_Add.Block = 0;
  Nand_Add.Page = 0;

  /*擦除数据*/
  HAL_NAND_Erase_Block(&NAND_HANDLE , &Nand_Add);

  /*读取数据*/
  HAL_NAND_Read_Page_8b(&hnand1, &Nand_Add, Nand_Buff, 1);
  

  for(uint16_t i = 0; i < NAND_PAGE_SIZE; i++)
  {
    sprintf((char *)TX_Buff , "Data[%d]=0x%02X " , i ,Nand_Buff[i]);
    Bsp_UART_Write(&huart1 , TX_Buff , sizeof(TX_Buff));
    Bsp_UART_Poll_DMA_TX(&huart1);

    if(i % 10 == 0 && i != 0)
    {
      Bsp_UART_Write(&huart1 , "\r\n" , 2);
    }
    if(Bsp_UART_Get_TX_Buff_Free(&huart1) <= 512)
    {
      Bsp_UART_Poll_DMA_TX(&huart1);
      HAL_Delay(10);
    }
  }

  Bsp_UART_Poll_DMA_TX(&huart1);
  
  for(uint16_t i = 0; i < NAND_PAGE_SIZE; i++)
  {
    Nand_Buff[i] = i & 0x00FF;
  }

  HAL_NAND_Write_Page_8b(&hnand1, &Nand_Add, Nand_Buff, 1);

  memset(Nand_Buff, 0, NAND_PAGE_SIZE);

  HAL_NAND_Read_Page_8b(&hnand1, &Nand_Add, Nand_Buff, 1);
  

}


 

