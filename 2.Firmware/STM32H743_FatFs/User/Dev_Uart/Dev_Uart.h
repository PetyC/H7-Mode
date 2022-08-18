/*
 * @Descripttion:串口接收数据处理 DMA+双缓存+空闲中断+环形队列
 * @version: HAL STM32Cubemx
 * @Author: Pi
 * @Date: 2021-07-06 16:34:00
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2022-04-28 22:23:51
 */
#ifndef DEV_UART_H
#define DEV_UART_H

#include "main.h"
#include "usart.h"
#include "string.h"
#include "Fifo.h"



extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_tx;
extern DMA_HandleTypeDef hdma_usart1_rx;





/* 串口设备数据结构 */
typedef struct
{
	uint8_t TX_Status;		/* 发送状态 */
	uint8_t RX_Status;	/*接收状态*/
	_fifo_t tx_fifo;	/* 发送fifo */
	_fifo_t rx_fifo;	/* 接收fifo */
	uint8_t *dmarx_buf;	/* dma接收缓存 */
	uint16_t dmarx_buf_size;/* dma接收缓存大小*/
	uint8_t *dmatx_buf;	/* dma发送缓存 */
	uint16_t dmatx_buf_size;/* dma发送缓存大小 */
	uint16_t last_dmarx_size;/* dma上一次接收数据大小 */
}Uart_Device_Str;



/*放入相应串口初始化处*/
void User_UART_Init(UART_HandleTypeDef *huart);

/*放入相应中断函数里*/
void User_UART_IRQHandler(UART_HandleTypeDef *huart);


/*串口读写函数*/
uint16_t User_UART_Write(UART_HandleTypeDef *huart, const uint8_t *buf, uint16_t size);
uint16_t User_UART_Read(UART_HandleTypeDef *huart, uint8_t *buf, uint16_t size);

/*判断是否接收到消息*/
uint8_t User_UART_Get_RX_Flag(UART_HandleTypeDef *huart);

/*发送Fifo中的消息*/
void User_UART_Poll_DMA_TX(UART_HandleTypeDef *huart);














#endif
