/*
 * @Description: FIFO缓存
 * @Autor: Pi
 * @Date: 2022-04-24 14:59:32
 * @LastEditTime: 2022-06-08 19:46:53
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <stdbool.h>
#include <stdint.h>

typedef void (*lock_fun)(void);

typedef struct
{
  uint8_t *buf;         /* 缓冲区 */
  uint32_t buf_size;    /* 缓冲区大小 */
  uint32_t occupy_size; /* 有效数据大小 */
  uint8_t *pwrite;      /* 写指针 */
  uint8_t *pread;       /* 读指针 */
  void (*lock)(void);   /* 互斥上锁 */
  void (*unlock)(void); /* 互斥解锁 */
} _fifo_t;

void fifo_register(_fifo_t *pfifo, uint8_t *pfifo_buf, uint32_t size, lock_fun lock, lock_fun unlock);
void fifo_release(_fifo_t *pfifo);

uint32_t fifo_write(_fifo_t *pfifo, const uint8_t *pbuf, uint32_t size);
uint32_t fifo_read(_fifo_t *pfifo, uint8_t *pbuf, uint32_t size);
uint32_t fifo_get_total_size(_fifo_t *pfifo);
uint32_t fifo_get_free_size(_fifo_t *pfifo);
uint32_t fifo_get_occupy_size(_fifo_t *pfifo);

#endif
