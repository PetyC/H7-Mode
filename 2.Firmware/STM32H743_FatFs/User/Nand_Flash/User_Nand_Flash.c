/*
 * @Description: Nand Flash
 * @Autor: Pi
 * @Date: 2022-04-11 16:40:52
 * @LastEditTime: 2022-04-15 16:15:35
 */
#include "User_Nand_Flash.h"
#include <string.h>

/**
 * @brief 初始化Nand Flash 通过判断ID是否正确
 * @param {*}
 * @return {uint8_t}    0:成功  1:失败
 */
uint8_t User_Nand_Flash_Init(void)
{
    NAND_IDTypeDef NAND_ID = {0};

    HAL_NAND_Reset(&hnand1);

    HAL_NAND_Read_ID(&hnand1, &NAND_ID);

    uint32_t Nand_Flash_ID = 0;

    Nand_Flash_ID = NAND_ID.Device_Id << 16;

    Nand_Flash_ID |= NAND_ID.Third_Id << 8;

    Nand_Flash_ID |= NAND_ID.Fourth_Id;

    if (Nand_Flash_ID != MT29F4G08ABADA)
    {   
        return 1;
    }

//    if(NAND_ModeSet(4) != 0)			        //设置为MODE4,高速模式 
//    {
//        return 1;
//    }


    return 0;
}



/**
 * @brief 读NAND状态
 * @param {*}
 * @return {uint8_t} NAND状态值 bit0:0,成功;1,错误(编程/擦除/READ)     bit6:0,Busy;1,Ready
 */
uint8_t NAND_ReadStatus(void)
{
    uint8_t data = 0;
    *(uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_READSTA; //发送读状态命令
    data++;
    data++;
    data++;
    data++;
    data++;                          //加延时,防止-O2优化,导致的错误.
    data = *(uint8_t *)NAND_ADDRESS; //读取状态值
    return data;
}

//等待NAND准备好
//返回值:NSTA_TIMEOUT 等待超时了
//      NSTA_READY    已经准备好
uint8_t NAND_WaitForReady(void)
{
    uint8_t status = 0;
    uint32_t time = 0;
    while (1) //等待ready
    {
        status = NAND_ReadStatus(); //获取状态值
        if (status & NSTA_READY)
            break;
        time++;
        if (time >= 0X1FFFF)
            return NSTA_TIMEOUT; //超时
    }
    return NSTA_READY; //准备好
}



/**
 * @brief 设置NAND 模式
 * @param {uint8_t} mode
 * @return {uint8_t} 0:成功     1:失败
 */
uint8_t NAND_ModeSet(uint8_t mode)
{
    *(uint8_t *)(NAND_ADDRESS | NAND_CMD) = NAND_FEATURE; //发送设置特性命令
    *(uint8_t *)(NAND_ADDRESS | NAND_ADDR) = 0X01;        //地址为0X01,设置mode
    *(uint8_t *)NAND_ADDRESS = mode;                      // P1参数,设置mode
    *(uint8_t *)NAND_ADDRESS = 0;
    *(uint8_t *)NAND_ADDRESS = 0;
    *(uint8_t *)NAND_ADDRESS = 0;

    if (NAND_WaitForReady() == NSTA_READY)
        return 0; //成功
    else
        return 1; //失败
}



#define NAND_PAGE_SIZE 2048
uint8_t buf[NAND_PAGE_SIZE] = {0};


static uint8_t buffer[2048];

void NAND_Demo(void)
{
    /*
    NAND_AddressTypeDef temp;
    temp.Plane = 0;
    temp.Block = 0;
    temp.Page = 0;

    HAL_StatusTypeDef State = HAL_OK;
    
    User_Nand_Flash_Init();

    State = HAL_NAND_Erase_Block(&hnand1, &temp);

    memset(buf, 0, NAND_PAGE_SIZE);

    State = HAL_NAND_Read_Page_8b(&hnand1, &temp, buf, 1);


    for(uint32_t i = 0; i < NAND_PAGE_SIZE; i++)
    {
        buf[i] = i & 0x00FF;
    }

    State = HAL_NAND_Write_Page_8b(&hnand1, &temp, buf, 1);

    memset(buf, 0, NAND_PAGE_SIZE);

    State = HAL_NAND_Read_Page_8b(&hnand1, &temp, buf, 1);
*/

  uint32_t ecc[2];
  NAND_AddressTypeDef addr;
  
  memset(buffer, 0, sizeof(buffer));
  
  addr.Plane = 0;
  addr.Block = 0;
  addr.Page = 0;
  HAL_NAND_ECC_Enable(&hnand1);

  HAL_NAND_Read_Page_8b(&hnand1, &addr, buffer, 1);

  HAL_NAND_GetECC(&hnand1, &ecc[0], HAL_MAX_DELAY);

  HAL_NAND_ECC_Disable(&hnand1);

  HAL_NAND_Read_SpareArea_8b(&hnand1, &addr, (uint8_t *)&ecc[1], 1);


  if (ecc[0] != ecc[1])
  {
    while (1);      //ECC校验错误
           
  }


   




}
