/*
 * @Description: DWT定时器
 * @Autor: Pi
 * @Date: 2022-10-10 16:44:21
 * @LastEditTime: 2022-10-10 17:27:42
 */
#include "Bsp_DWT.h"

/*DWT初始化标志*/
static uint8_t DWT_Init_Flag = 0;

/**
 * @brief 初始化DWT定时器
 * @return {*}
 */
void DWT_Init(void)
{
  if (DWT_Init_Flag == 1)
  {
    return;
  }

  /*先使能DWT外设,由内核调试寄存器DEM_CR的位24控制 写1使能*/
  DEM_CR |= (unsigned int)DEM_CR_TRCENA;
  /*使能CYCCNT寄存器之前 先清0*/
  DWT_CYCCNT = (unsigned int)0u;
  /*使能CYCCNT寄存器,由DWT_CTRL的位0控制,写1使能*/
  DWT_CR |= (unsigned int)DWT_CR_CYCCNTENA;
  /*标志已初始化*/
  DWT_Init_Flag = 1;
}

/**
 * @brief DWT US延时
 * @param {uint32_t} Delay
 * @return {*}
 */
void Bsp_DWT_DelayUS(uint32_t Delay)
{
  if (DWT_Init_Flag == 0)
  {
    DWT_Init();
  }

  uint32_t tCnt = 0;
  uint32_t tStart = DWT_CYCCNT;                             /* 刚进入时的计数器值 */
  uint32_t tDelayCnt = Delay * (SystemCoreClock / 1000000); /* 需要的节拍数 */

  while (tCnt < tDelayCnt)
  {
    tCnt = DWT_CYCCNT - tStart; /* 求减过程中，如果发生第一次32位计数器重新计数，依然可以正确计算 */
  }
}