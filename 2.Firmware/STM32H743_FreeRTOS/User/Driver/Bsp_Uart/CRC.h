/*
 * @Descripttion: 
 * @version: HAL STM32Cubemx
 * @Author: Pi
 * @Date: 2021-06-30 10:36:10
 * @LastEditors: Pi
 * @LastEditTime: 2021-06-30 11:00:58
 */
#ifndef CRC_H
#define CRC_H

#include "STM32H7XX.h"

uint16_t crc16_modbus(uint8_t *modbusdata, uint16_t length);
uint16_t crc16_flage(uint8_t *modbusdata, int length);


#endif
