/*
 * @Description: FLASHFS文件系统相关操作
 * @Autor: Pi
 * @Date: 2022-09-09 19:17:35
 * @LastEditTime: 2022-09-10 03:33:00
 */
#include "User_FlashFS.h"

/*内部调用函数*/
static void DotFormat(uint64_t _ullVal, char *_sp);

/**
 * @brief 挂载文件系统和NAND
 * @return {uint8_t} 0:成功 其他:失败
 */
uint8_t User_FlashFS_Load(void)
{
  uint8_t Result = 1;
  /*初始化文件系统*/
  Result = finit("N0:");
  if (Result != NULL)
  {
    return Result;
  }

  /*加载NAND*/
  Result = fmount("N0:");
  if (Result != NULL)
  {
    Bsp_Nand_Erase();
    Result = fformat("N0:", "/LL /L nand /FAT16");
    if (Result != 0)
    {
      return Result;
    }
    /*重新尝试挂载*/
    Result = finit("N0:");
    Result = fmount("N0:");
    if (Result != 0)
    {
      return Result;
    }
  }
  return 0;
}

/* FlashFS API的返回值 */
static const char *ReVal_Table[] =
    {
        "fsOK:成功",
        "fsError:未指定的错误",
        "fsUnsupported:操作不支持",
        "fsAccessDenied:资源访问被拒绝",

        "fsInvalidParameter:参数无效",
        "fsInvalidDrive:驱动无效或驱动不存在",
        "fsInvalidPath:路径无效",
        "fsUninitializedDrive:驱动未初始化 ",

        "fsDriverError:读写操作",
        "fsMediaError:媒介错误",
        "fsNoMedia:媒介不存在，或者未初始化",
        "fsNoFileSystem:文件系统未格式化",

        "fsNoFreeSpace:没有可用空间",
        "fsFileNotFound:文件未找到",
        "fsDirNotEmpty:文件夹非空",
        "fsTooManyOpenFiles:打开文件太多",
};

/**
 * @brief 查看NAND Flash容量相关信息
 * @return {*}
 */
void User_FlashFS_ViewCapacity(void)
{
  uint8_t Result = 1;
  uint8_t buf[15];
  uint32_t ser_num = 0; //序列号
  uint64_t Capacity = 0;
  int32_t id;
  fsMediaInfo info;
  fsStatus restatus;

  printf("\r\n\r\n");
  /* 获取volume label */
  if (fvol("N0:", (char *)buf, &ser_num) == 0)
  {
    if (buf[0])
    {
      printf("NAND的volume label是 %s\r\n", buf);
    }
    else
    {
      printf("NAND没有volume label\r\n");
    }
    printf("NAND的volume serial number是 %d\r\n", ser_num);
  }
  else
  {
    printf("Volume访问错误\r\n");
  }

  /* 获取SD卡剩余容量 */
  Capacity = ffree("N0:");
  DotFormat(Capacity, (char *)buf);
  printf("NAND剩余容量 = %10s字节\r\n", buf);

  /* 获取相应存储设备的句柄，注意挂载后操作下面的IO控制才是有效的 */
  id = fs_ioc_get_id("N0");

  /* 访问的时候要加上锁 */
  fs_ioc_lock(id);

  /* 初始化FAT文件系统格式的存储设备 */

  /* 获取存储设备的扇区信息 */
  restatus = fs_ioc_read_info(id, &info);
  if (restatus == fsOK)
  {
    /* 总的扇区数 * 扇区大小，SD卡的扇区大小是512字节 */
    Capacity = (uint64_t)info.block_cnt << 9;
    DotFormat(Capacity, (char *)buf);
    printf("NAND总容量 = %10s字节\r\nSD卡的总扇区数 = %d \r\n", buf, info.block_cnt);
  }
  else
  {
    printf("获取配置信息失败 %s\r\n", ReVal_Table[restatus]);
  }

  /* 访问结束要解锁 */
  fs_ioc_unlock(id);

  printf("NAND读扇区大小 = %d字节\r\n", info.read_blen);
  printf("NAND写扇区大小 = %d字节\r\n", info.write_blen);

  /* 卸载SD卡 */
  // Result = funmount("N0:");
  printf("\r\n\r\n");
  return;
}


/**
 * @brief 将数据规范化显示，方便用户查看
 * @param {uint64_t} _ullVal
 * @param {char} *_sp
 * @return {*}
 */
static void DotFormat(uint64_t _ullVal, char *_sp)
{
  /* 数值大于等于10^9 */
  if (_ullVal >= (uint64_t)1e9)
  {
    _sp += sprintf(_sp, "%d.", (uint32_t)(_ullVal / (uint64_t)1e9));
    _ullVal %= (uint64_t)1e9;
    _sp += sprintf(_sp, "%03d.", (uint32_t)(_ullVal / (uint64_t)1e6));
    _ullVal %= (uint64_t)1e6;
    sprintf(_sp, "%03d.%03d", (uint32_t)(_ullVal / 1000), (uint32_t)(_ullVal % 1000));
    return;
  }

  /* 数值大于等于10^6 */
  if (_ullVal >= (uint64_t)1e6)
  {
    _sp += sprintf(_sp, "%d.", (uint32_t)(_ullVal / (uint64_t)1e6));
    _ullVal %= (uint64_t)1e6;
    sprintf(_sp, "%03d.%03d", (uint32_t)(_ullVal / 1000), (uint32_t)(_ullVal % 1000));
    return;
  }

  /* 数值大于等于10^3 */
  if (_ullVal >= 1000)
  {
    sprintf(_sp, "%d.%03d", (uint32_t)(_ullVal / 1000), (uint32_t)(_ullVal % 1000));
    return;
  }

  /* 其它数值 */
  sprintf(_sp, "%d", (uint32_t)(_ullVal));
}






#if 1
/* 用于测试读写速度 */
#define TEST_FILE_LEN (2 * 1024 * 1024) /* 用于测试的文件长度 */
#define BUF_SIZE (4 * 1024)             /* 每次读写SD卡的最大数据长度 */

ALIGN_32BYTES(uint8_t g_TestBuf[BUF_SIZE]);
/**
 * @brief 测试文件读写速度
 * @return {*}
 */
void User_FlashFS_WriteFileTest(void)
{
  FILE *fout;
  uint32_t bw;
  uint32_t i, k;
  uint32_t runtime1, runtime2, timelen;
  uint8_t err = 0, result;
  char TestFileName[13];
  static uint8_t s_ucTestSn = 0;

  for (i = 0; i < sizeof(g_TestBuf); i++)
  {
    g_TestBuf[i] = (i / 512) + '0';
  }

  /* 加载SD卡 -----------------------------------------*/
  result = fmount("N0:");
  if (result != NULL)
  {
    /* 如果挂载失败，务必不要再调用FlashFS的其它API函数，防止进入硬件异常 */
    printf("挂载文件系统失败 (%s)\r\n", ReVal_Table[result]);
    goto access_fail;
  }
  else
  {
    printf("挂载文件系统成功 (%s)\r\n", ReVal_Table[result]);
  }

  /* 打开文件 -----------------------------------------*/
  sprintf(TestFileName, "Speed%02d.txt", s_ucTestSn++); /* 每写1次，序号递增 */
  fout = fopen(TestFileName, "w");
  if (fout == NULL)
  {
    printf("文件: %s创建失败\r\n", TestFileName);
    goto access_fail;
  }

  /* 写一串数据 测试写速度-----------------------------------------*/
  printf("开始写文件%s %dKB ...\r\n", TestFileName, TEST_FILE_LEN / 1024);
  runtime1 = HAL_GetTick(); /* 读取系统运行时间 */
  for (i = 0; i < TEST_FILE_LEN / BUF_SIZE; i++)
  {
    bw = fwrite(g_TestBuf, sizeof(uint8_t), BUF_SIZE, fout);
    if (bw == BUF_SIZE)
    {
      if (((i + 1) % 8) == 0)
      {
        printf(".");
      }
    }
    else
    {
      err = 1;
      printf("%s文件写失败\r\n", TestFileName);
      break;
    }
  }
  runtime2 = HAL_GetTick(); /* 读取系统运行时间 */

  if (err == 0)
  {
    timelen = (runtime2 - runtime1);
    printf("\r\n  写耗时 : %dms   平均写速度 : %dB/S (%dKB/S)\r\n",
           timelen,
           (TEST_FILE_LEN * 1000) / timelen,
           ((TEST_FILE_LEN / 1024) * 1000) / timelen);
  }

  /* 使用函数ferror再次检测是否发生过错误 -----------------------*/
  if (ferror(fout))
  {
    printf("写数据过程中出现过错误\r\n\n");
  }
  else
  {
    printf("写数据过程中未出现过错误\r\n\n");
  }

  fclose(fout); /* 关闭文件*/

  /* 开始读文件，测试读速度 ---------------------------------------*/
  fout = fopen(TestFileName, "r");
  if (fout == NULL)
  {
    printf("文件: %s读取失败\r\n", TestFileName);
    goto access_fail;
  }

  printf("开始读文件 %dKB ...\r\n", TEST_FILE_LEN / 1024);
  runtime1 = HAL_GetTick(); /* 读取系统运行时间 */
  for (i = 0; i < TEST_FILE_LEN / BUF_SIZE; i++)
  {
    bw = fread(g_TestBuf, sizeof(uint8_t), BUF_SIZE, fout);
    if (bw == BUF_SIZE)
    {
      if (((i + 1) % 8) == 0)
      {
        printf(".");
      }
      /* 比较写入的数据是否正确，此语句会导致读卡速度结果降低 */
      for (k = 0; k < sizeof(g_TestBuf); k++)
      {
        if (g_TestBuf[k] != (k / 512) + '0')
        {
          err = 1;
          printf("Speed1.txt 文件读成功，但是数据出错\r\n");
          break;
        }
      }
      if (err == 1)
      {
        break;
      }
    }
    else
    {
      err = 1;
      printf("Speed1.txt 文件读失败\r\n");
      break;
    }
  }
  runtime2 = HAL_GetTick(); /* 读取系统运行时间 */

  if (err == 0)
  {
    timelen = (runtime2 - runtime1);
    printf("\r\n  读耗时 : %dms   平均读速度 : %dB/S (%dKB/S)\r\n", timelen,
           (TEST_FILE_LEN * 1000) / timelen, ((TEST_FILE_LEN / 1024) * 1000) / timelen);
  }

  /* 使用函数ferror再次检测是否发生过错误 -----------------------*/
  if (ferror(fout))
  {
    printf("读数据过程中出现过错误\r\n");
  }
  else
  {
    printf("读数据过程中未出现过错误\r\n");
  }

  fclose(fout); /* 关闭文件*/

access_fail:
  /* 卸载SD卡 */
  result = funmount("N0:");
  if (result != NULL)
  {
    printf("卸载文件系统失败\r\n");
  }
  else
  {
    printf("卸载文件系统成功\r\n");
  }

}
#endif
