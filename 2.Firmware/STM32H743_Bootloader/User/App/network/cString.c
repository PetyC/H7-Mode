#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cString.h"

char *StringStr = NULL;
void cStringFree(void)
{
  free(StringStr);
}

/**
 * @brief  获取两个字符串之间的字符串
 * @param  Str  源字符串
 * @param  StrBegin  开始的字符串
 * @param  StrEnd    结束的字符串
 * @retval 字符串首地址
 * @example  printf("%s",StrBetwString("wqe5w4ew46e5w","5w","6e"));cStringFree(Str);  输出:4ew4
 **/
char *StrBetwStringMalloc(char *Str, char *StrBegin, char *StrEnd)
{
  char *StrStart = 0, *StrStop = 0, len = 0;
  len = strlen(StrBegin); //字符串长度

  StrStart = strstr(Str, StrBegin); //第一个字符串开始的地址
  if (StrStart)
  {
    StrStop = strstr(StrStart + len + 1, StrEnd); //第二个字符串开始的地址
    if (StrStop)
    {
      StringStr = (char *)malloc(((StrStop - (StrStart + len)) + 1) * sizeof(char)); //多分配一个空间,防止其它数据干扰
      memset(StringStr, NULL, (StrStop - (StrStart + len)) + 1);
      memcpy(StringStr, StrStart + len, (StrStop - (StrStart + len)));
      return StringStr;
    }
    else
    {
      return NULL;
    }
  }
  else
  {
    return NULL;
  }
}

char *StrStop = NULL;
char StringValue;
void cStringRestore(void)
{
  if (StrStop != NULL)
  {
    *StrStop = StringValue; //补上当时截断的字符串
  }
}

/**
 * @brief  获取两个字符串之间的字符串
 * @param  Str  源字符串
 * @param  StrBegin  开始的字符串
 * @param  StrEnd    结束的字符串
 * @retval 字符串首地址
 * @example  printf("%s",StrBetwString("wqe5w4ew46e5w","5w","6e"));cStringRestore();  输出:4ew4
 **/
char *StrBetwString(char *Str, char *StrBegin, char *StrEnd)
{
  char *StrStart = 0, len = 0;
  len = strlen(StrBegin);           //字符串长度
  StrStart = strstr(Str, StrBegin); //第一个字符串开始的地址
  if (StrStart)
  {
    StrStop = strstr(StrStart + len + 1, StrEnd); //第二个字符串开始的地址
    if (StrStop)
    {
      StringValue = *StrStop;
      *StrStop = 0; //截断
      return StrStart + len;
    }
    else
      return NULL;
  }
  else
    return NULL;
}

/**舍弃
 * @brief  分割字符串
 * @param  src        源字符串
 * @param  separator  分割
 * @param  dest       接收子串的数组
 * @param  num        子字符串的个数
 * @retval None
 * @example split("42,uioj,dk4,56",",",temp,&cnt);  temp[0]=42,...temp[3]=56  cnt=4
 **/
/*
void split(char *src,const char *separator,char **dest,int *num)
{
  char *pNext;
  int count = 0;
  if (src == NULL || strlen(src) == 0)
    return;
  if (separator == NULL || strlen(separator) == 0)
    return;
  pNext = (char *)strtok(src,separator);
  while(pNext != NULL)
  {
    if(dest != NULL)
    *dest++ = pNext;
    ++count;
    pNext = (char *)strtok(NULL,separator);
  }
  *num = count;
}
*/

/**
 * @brief  分割字符串
 * @param  src        源字符串
 * @param  separator  分割
 * @param  dest       接收子串的数组
 * @param  DestLen    预期子字符串的最大个数
 * @retval 实际子字符串的个数
 * @example split("42,uioj,dk4,56",",",temp,4);  temp[0]=42,...temp[3]=56
 **/
int split(char *src, const char *separator, char **dest, int DestLen)
{
  char *pNext;
  int count = 0;
  if (src == NULL || strlen(src) == 0)
    return 0;
  if (separator == NULL || strlen(separator) == 0)
    return 0;
  pNext = (char *)strtok(src, separator);
  while (pNext != NULL)
  {
    if (dest != NULL)
      *dest++ = pNext;
    ++count;
    pNext = (char *)strtok(NULL, separator);
    if (count >= DestLen)
    {
      break;
    }
  }
  //	*num = count;
  return count;
}

/**
* @brief  字符串转16进制表示的字符串
* @param  pbSrc   源地址
* @param  pbDest  目的地址
* @param  nlen    源字符串长度
* @param  None
* @retval None
* @example
    temp[0] = 'AA';
    temp[1] = '8';
    temp[2] = 8;
    temp[3] = 0x0F;
    HexToStr(temp,temp1,4)
    temp1= "414138080F";
**/
void HexToStr(char *pbSrc, char *pbDest, int nlen)
{
  char ddl, ddh;
  int i;
  for (i = 0; i < nlen; i++)
  {
    ddh = 48 + pbSrc[i] / 16;
    ddl = 48 + pbSrc[i] % 16;
    if (ddh > 57)
      ddh = ddh + 7;
    if (ddl > 57)
      ddl = ddl + 7;
    pbDest[i * 2] = ddh;
    pbDest[i * 2 + 1] = ddl;
  }
  pbDest[nlen * 2] = '\0';
}

/**
 * @brief  16进制表示的字符串转字符串(和以上的相反)
 * @param  pbSrc   源地址
 * @param  pbDest  目的地址
 * @param  nlen    源字符串长度
 * @param  None
 * @retval None
 * @example
 **/
void StrToHex(char *pbSrc, char *pbDest, int nLen)
{
  char h1, h2;
  char s1, s2;
  int i;

  for (i = 0; i < nLen; i++)
  {
    h1 = pbSrc[2 * i];
    h2 = pbSrc[2 * i + 1];

    s1 = toupper(h1) - 0x30;
    if (s1 > 9)
      s1 -= 7;

    s2 = toupper(h2) - 0x30;
    if (s2 > 9)
      s2 -= 7;

    pbDest[i] = s1 * 16 + s2;
  }
}

/**
 *@brief		检查字符串地址是IP还是域名
 *@param		str 要转换的数据
 *@param		ip  转换后存储的位置
 *@return 	0:转换失败,可能是域名   1:转换成功
 *@example  net_dns_str_ip("192.168.0.1", &ip) ip[0]=192;ip[1]=168;ip[2]=0;ip[3]=1;
 */
uint8_t net_dns_str_ip(const char *str, void *ip)
{
  /* The count of the number of bytes processed. */
  int i;
  /* A pointer to the next digit to process. */
  const char *start;

  start = str;
  for (i = 0; i < 4; i++)
  {
    /* The digit being processed. */
    char c;
    /* The value of this byte. */
    int n = 0;
    while (1)
    {
      c = *start;
      start++;
      if (c >= '0' && c <= '9')
      {
        n *= 10;
        n += c - '0';
      }
      /* We insist on stopping at "." if we are still parsing
         the first, second, or third numbers. If we have reached
         the end of the numbers, we will allow any character. */
      else if ((i < 3 && c == '.') || i == 3)
      {
        break;
      }
      else
      {
        return 0;
      }
    }
    if (n >= 256)
    {
      return 0;
    }
    ((uint8_t *)ip)[i] = n;
  }
  return 1;
}
