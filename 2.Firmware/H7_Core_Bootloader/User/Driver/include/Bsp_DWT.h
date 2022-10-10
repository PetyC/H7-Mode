/*
 * @Description: DWT定时器
 * @Autor: Pi
 * @Date: 2022-10-10 16:44:25
 * @LastEditTime: 2022-10-10 17:28:51
 */
#ifndef BSP_DWT_H_
#define BSP_DWT_H_

#include "stm32h7xx_hal.h"



/*相关宏定义*/
#define DWT_CR *(volatile unsigned int *)       0xE0001000
#define DEM_CR *(volatile unsigned int *)       0xE000EDFC
#define DBGMCU_CR *(volatile unsigned int *)    0xE0042004
#define DWT_CYCCNT *(volatile unsigned int *)   0xE0001004      //显示或设置处理器的周期计数值
#define DEM_CR_TRCENA                           (1 << 24)       // DEMCR的DWT使能位
#define DWT_CR_CYCCNTENA                        (1 << 0)        // DWT的SYCCNT使能位

/*DWT初始化*/
void DWT_Init(void);
/*DWT US延时 */
void Bsp_DWT_DelayUS(uint32_t Delay);





#endif
