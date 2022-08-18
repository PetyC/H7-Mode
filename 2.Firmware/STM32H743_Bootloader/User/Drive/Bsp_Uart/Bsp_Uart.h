/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-07-01 17:44:02
 * @LastEditTime: 2022-07-12 03:02:59
 */

#ifndef DEV_UART_H
#define DEV_UART_H

#include "main.h"
#include "usart.h"
#include "string.h"
#include "Fifo.h"

/*是否使用了FreeRTOS*/
#define USE_FreeRTOS  0

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
void Bsp_UART_Init(UART_HandleTypeDef *huart);

/*串口设备复位*/
void Uart_UART_MspDeInit(UART_HandleTypeDef *huart);

/*放入相应中断函数里*/
void Bsp_UART_IRQHandler(UART_HandleTypeDef *huart);


/*串口读写函数*/
uint16_t Bsp_UART_Write(UART_HandleTypeDef *huart, const uint8_t *buf, uint16_t size);
uint16_t Bsp_UART_Read(UART_HandleTypeDef *huart, uint8_t *buf, uint16_t size);

/*判断是否接收到消息*/
uint8_t Bsp_UART_Get_RX_Flag(UART_HandleTypeDef *huart);

/*发送Fifo中的消息*/
void Bsp_UART_Poll_DMA_TX(UART_HandleTypeDef *huart);

/*TX Buff空闲空间*/
uint16_t Bsp_UART_Get_TX_Buff_Free(UART_HandleTypeDef *huart);

/*TX Buff已用空间*/
uint16_t Bsp_UART_Get_TX_Buff_Occupy(UART_HandleTypeDef *huart);

/*TX Buff空闲空间*/
uint16_t Bsp_UART_Get_RX_Buff_Free(UART_HandleTypeDef *huart);

/*RX Buff已用空间*/
uint16_t Bsp_UART_Get_RX_Buff_Occupy(UART_HandleTypeDef *huart);

/*串口接收使能*/
void Bsp_UART_RX_Enable(UART_HandleTypeDef *huart , uint8_t Enable);

/*串口波特率设置*/
void Bsp_UART_Set_BRR(UART_HandleTypeDef *huart , uint8_t Sw);

#endif
