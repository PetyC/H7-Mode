/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-06-09 18:54:44
 * @LastEditTime: 2022-06-14 21:15:47
 */
#include "bsp_st7735s.h"

/*SPI句柄*/
extern SPI_HandleTypeDef hspi1;

uint32_t tim_period = 32768;
uint32_t tim_pulse;

extern uint8_t backlight_pct;

/**
 * @brief LCD背光调整
 * @param {uint8_t} pct
 * @return {*}
 */
void Pin_BLK_Pct(uint8_t pct)
{
    Pin_BLK_High();
    /*
    backlight_pct = pct;
    tim_pulse = pct * tim_period / 100;
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, tim_pulse);
    */
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
