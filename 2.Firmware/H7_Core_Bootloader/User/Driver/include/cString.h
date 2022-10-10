/*
 * @Description:字符串处理功能
 * @Autor: Pi
 * @Date: 2022-07-08 16:47:11
 * @LastEditTime: 2022-09-23 14:09:20
 */
#ifndef CSTRING_H_
#define CSTRING_H_

#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void cStringFree(void);
void cStringRestore(void);
char *StrBetwString(char *Str, char *StrBegin, char *StrEnd);
int split(char *src, const char *separator, char **dest, int DestLen);
void HexToStr(char *pbSrc, char *pbDest, int nlen);
void StrToHex(char *pbSrc, char *pbDest, int nLen);
uint8_t net_dns_str_ip(const char *str, void *ip);

int str_to_int(char *_pStr);
void int_to_str(int _iNumber, char *_pBuf, unsigned char _len);

#endif
