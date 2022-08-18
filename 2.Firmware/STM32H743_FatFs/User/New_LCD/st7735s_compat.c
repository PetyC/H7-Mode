/*
 * @Description:
 * @Autor: Pi
 * @Date: 2022-06-09 18:54:44
 * @LastEditTime: 2022-06-10 17:10:23
 */
#include "st7735s_compat.h"


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
    LCD_BLK_Set();
    /*
    backlight_pct = pct;
    tim_pulse = pct * tim_period / 100;
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, tim_pulse);
    */


}

/**
 * @brief SPI发送函数
 * @param {uint16_t} len
 * @param {uint8_t} *data
 * @return {*}
 */
void SPI_send(uint16_t len, uint8_t *data)
{
    HAL_SPI_Transmit(&hspi1, data, len, 0xFF);
}



/**
 * @brief 发送命令
 * @param {uint16_t} len
 * @param {uint8_t} *data
 * @return {*}
 */
void SPI_TransmitCmd(uint16_t len, uint8_t *data)
{
    Pin_DC_Low();
    SPI_send(len, data);
}


/**
 * @brief 发送数据
 * @param {uint16_t} len
 * @param {uint8_t} *data
 * @return {*}
 */
void SPI_TransmitData(uint16_t len, uint8_t *data)
{
    Pin_DC_High();
    SPI_send(len, data);
}


/**
 * @brief SPI发送函数
 * @param {uint16_t} len
 * @param {uint8_t} *data
 * @return {*}
 */
void SPI_Transmit(uint16_t len, uint8_t *data)
{
    SPI_TransmitCmd(1, data++);

    if (--len)
        SPI_TransmitData(len, data);
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
