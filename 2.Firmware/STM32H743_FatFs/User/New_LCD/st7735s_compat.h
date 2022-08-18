/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-06-09 18:54:44
 * @LastEditTime: 2022-06-10 17:10:29
 */
#ifndef  ST7735S_COMPAT_H
#define  ST7735S_COMPAT_H

#include <inttypes.h>
#include "main.h"

/* this may differ from the default 80x160 */
#define defWIDTH   128
#define defHEIGHT  128
#define defXSTART  0
#define defYSTART  0

/* #define BUFFER */
 #define BUFFER1 
//#define HVBUFFER


/*IO操作*/
#define Pin_RES_Low() HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_RESET) // RES
#define Pin_RES_High() HAL_GPIO_WritePin(LCD_RES_GPIO_Port, LCD_RES_Pin, GPIO_PIN_SET)

#define Pin_DC_Low() LCD_DC_GPIO_Port->BSRR = (uint32_t)LCD_DC_Pin << 16U //置0
#define Pin_DC_High() LCD_DC_GPIO_Port->BSRR = LCD_DC_Pin                 //置1		写数据

#define LCD_BLK_Clr() HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_RESET) // BLK
#define LCD_BLK_Set() HAL_GPIO_WritePin(LCD_BLK_GPIO_Port, LCD_BLK_Pin, GPIO_PIN_SET)




void Pin_BLK_Pct(uint8_t);

void SPI_TransmitCmd(uint16_t len, uint8_t *data);
void SPI_TransmitData(uint16_t len, uint8_t *data);


/*意义不明*/
void SPI_Transmit(uint16_t len, uint8_t *data);
void _Delay(uint32_t d);



#endif
