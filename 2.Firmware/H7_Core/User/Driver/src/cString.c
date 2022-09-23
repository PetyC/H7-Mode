/*
 * @Description:字符串处理功能
 * @Autor: Pi
 * @Date: 2022-08-05 19:40:12
 * @LastEditTime: 2022-09-23 14:09:40
 */
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

/****************************************************************************************************/

/**
 * @brief 将整数转换为ASCII数组。支持负数。
 * @param {int} _iNumber  整数
 * @param {char} *_pBuf 目标缓冲区, 存放转换后的结果。以0结束的字符串
 * @param {unsigned char} _len   ASCII字符个数, 字符串长度
 * @return {*}
 */
void int_to_str(int _iNumber, char *_pBuf, unsigned char _len)
{
  unsigned char i;
  int iTemp;

  if (_iNumber < 0) /* 负数 */
  {
    iTemp = -_iNumber; /* 转为正数 */
  }
  else
  {
    iTemp = _iNumber;
  }

  memset(_pBuf, ' ', _len);

  /* 将整数转换为ASCII字符串 */
  for (i = 0; i < _len; i++)
  {
    _pBuf[_len - 1 - i] = (iTemp % 10) + '0';
    iTemp = iTemp / 10;
    if (iTemp == 0)
    {
      break;
    }
  }
  _pBuf[_len] = 0;

  if (_iNumber < 0) /* 负数 */
  {
    for (i = 0; i < _len; i++)
    {
      if ((_pBuf[i] == ' ') && (_pBuf[i + 1] != ' '))
      {
        _pBuf[i] = '-';
        break;
      }
    }
  }
}

/**
 * @brief 将ASCII码字符串转换成整数。 遇到小数点自动越过。
 * @param {char} *_pStr 待转换的ASCII码串. 可以以逗号，#或0结束。 2014-06-20 修改为非0-9的字符。
 * @return {*}  二进制整数值
 */
int str_to_int(char *_pStr)
{
  unsigned char flag;
  char *p;
  int ulInt;
  unsigned char i;
  unsigned char ucTemp;

  p = _pStr;
  if (*p == '-')
  {
    flag = 1; /* 负数 */
    p++;
  }
  else
  {
    flag = 0;
  }

  ulInt = 0;
  for (i = 0; i < 15; i++)
  {
    ucTemp = *p;
    if (ucTemp == '.') /* 遇到小数点，自动跳过1个字节 */
    {
      p++;
      ucTemp = *p;
    }
    if ((ucTemp >= '0') && (ucTemp <= '9'))
    {
      ulInt = ulInt * 10 + (ucTemp - '0');
      p++;
    }
    else
    {
      break;
    }
  }

  if (flag == 1)
  {
    return -ulInt;
  }
  return ulInt;
}
