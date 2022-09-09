/*
 * @Description: Nand Flash
 * @Autor: Pi
 * @Date: 2022-04-11 16:40:52
 * @LastEditTime: 2022-09-09 19:28:23
 */
#include "Bsp_Nand_Flash.h"



/**
 * @brief 初始化Nand Flash 通过判断ID是否正确
 * @param {*}
 * @return {uint8_t}    0:成功  1:失败
 */
uint8_t Bsp_Nand_Init(void)
{
  /*重置NAND*/
  HAL_NAND_Reset(&NAND_HANDLE);

  /* 检查操作状态 */
  if (HAL_NAND_GetState(&NAND_HANDLE) != HAL_NAND_STATE_READY)
  {
    return 1;
  }

  uint32_t Nand_Flash_ID = 0;
  NAND_IDTypeDef NAND_ID = {0};
  HAL_NAND_Read_ID(&NAND_HANDLE, &NAND_ID);

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
 * @brief 擦除整个NAND (低格)
 * @return {*}
 */
uint8_t Bsp_Nand_Erase(void)
{
  NAND_AddressTypeDef nand = {0, 0, 0};
  HAL_StatusTypeDef nand_state = HAL_ERROR;

  for (uint16_t i = 0; i < 2; i++)
  {
    nand.Plane = i;
    for (uint16_t j = 0; j < 2048; j++)
    {
      nand.Block = j;
      nand_state = HAL_NAND_Erase_Block(&NAND_HANDLE, &nand);
    }
  }

  return nand_state;
}

/**
 * @brief 供CMSIS-Driver调用的FMC函数
 * @param {uint32_t} dev_num
 * @return {*}
 */
int32_t Driver_NAND0_GetDeviceBusy(uint32_t dev_num)
{

  for (uint16_t k = 0; k < 200; k++)
  {
    if ((GPIOD->IDR & GPIO_PIN_6) == 0) // NAWAIT引脚
    {
      break;
    }
  }

  for (uint16_t k = 0; k < 2000; k++)
  {
    if ((GPIOD->IDR & GPIO_PIN_6) != 0)
    {
      break;
    }
  }

  return 0;
}
