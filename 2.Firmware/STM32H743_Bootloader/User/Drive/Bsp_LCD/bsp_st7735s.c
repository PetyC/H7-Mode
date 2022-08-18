/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-06-09 18:54:44
 * @LastEditTime: 2022-06-27 15:04:14
 */
#include "bsp_st7735s.h"

/*SPI句柄*/
extern SPI_HandleTypeDef hspi1;

/*TIM句柄*/
extern TIM_HandleTypeDef htim1;




/**
 * @brief LCD背光调整
 * @param {uint8_t} pct 亮度百分比 0~100 
 * @return {*}
 */
void Backlight_Pct(uint8_t pct)
{
   static uint8_t Flag = 0;

   if(Flag == 0)
   {
    Flag = 1;
    HAL_TIM_PWM_Start(&htim1 , TIM_CHANNEL_1);
   }
  
    if(pct > 100)
    {
        return;
    }
    
    uint16_t New_CCR = 0 + (1000 - 0)/(100 - 0) * (pct - 0);

    /*调整PWM占空比*/
    __HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 , New_CCR);
}

/**
 * @brief 发送命令
 * @param {uint16_t} len
 * @param {uint8_t} *data
 * @return {*}
 */
void SPI_TransmitCmd(uint8_t *data, uint16_t len)
{
    Pin_DC_Low();
    HAL_SPI_Transmit(&hspi1, data, len, 0xFF);
    //HAL_SPI_Transmit_DMA(&hspi1, data, len);
}

/**
 * @brief 发送数据
 * @param {uint16_t} len
 * @param {uint8_t} *data
 * @return {*}
 */
void SPI_TransmitData(uint8_t *data, uint16_t len)
{
    Pin_DC_High();
    HAL_SPI_Transmit(&hspi1, data, len, 0xFF);
    //HAL_SPI_Transmit_DMA(&hspi1, data, len);
}

/**
 * @brief SPI单命令数据
 * @param {uint16_t} len
 * @param {uint8_t} *data
 * @return {*}
 */
void SPI_Transmit(uint8_t *data, uint16_t len)
{

    SPI_TransmitCmd(data++, 1);

    if (--len)
        SPI_TransmitData(data, len);
}

/**
 * @brief 延时
 * @param {uint32_t} d
 * @return {*}
 */
void _Delay(uint32_t d)
{
    HAL_Delay(d);
}
