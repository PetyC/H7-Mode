/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-07-08 16:47:11
 * @LastEditTime: 2022-07-08 17:07:20
 */
#ifndef CSTRING_H_
#define CSTRING_H_

 

#include <stdint.h>

void cStringFree(void);
void cStringRestore(void);
char *StrBetwString(char *Str,char *StrBegin,char *StrEnd);
int split(char *src,const char *separator,char **dest,int DestLen);
void HexToStr(char *pbSrc,char *pbDest,int nlen);
void StrToHex(char *pbSrc, char *pbDest, int nLen);
uint8_t net_dns_str_ip(const char* str, void *ip);
#endif

