/*
 * @Description: FLASHFS文件系统相关操作
 * @Autor: Pi
 * @Date: 2022-09-09 19:17:35
 * @LastEditTime: 2022-09-09 19:44:04
 */
#include "User_FlashFS.h"

/*Flashfs库*/
#include "rl_fs.h"

/*C库相关*/
#include <stdio.h>
#include <string.h>


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
  if(Result != NULL)
  {
    return Result;
  }

  /*加载NAND*/
  Result = fmount("N0:");
  if(Result != NULL)
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
  uint32_t ser_num = 0;   //序列号
  uint64_t Capacity = 0;
  int32_t id;
  fsMediaInfo info;
  fsStatus restatus;

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
  Result = funmount("N0:");

  return 0;
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



