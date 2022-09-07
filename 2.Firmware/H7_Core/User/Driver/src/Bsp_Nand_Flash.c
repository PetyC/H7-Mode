/*
 * @Description: Nand Flash
 * @Autor: Pi
 * @Date: 2022-04-11 16:40:52
 * @LastEditTime: 2022-09-08 02:02:17
 */
#include "Bsp_Nand_Flash.h"

/*Flashfs库*/
#include "rl_fs.h" 

/*C库相关*/
#include  <stdio.h>
#include <string.h>





/**
 * @brief 初始化Nand Flash 通过判断ID是否正确
 * @param {*}
 * @return {uint8_t}    0:成功  1:失败
 */
uint8_t Bsp_Nand_Init(void)
{

  HAL_NAND_Reset(&NAND_HANDLE);

	/* 检查操作状态 */
	if (HAL_NAND_GetState(&NAND_HANDLE) != HAL_NAND_STATE_READY)
	{
		return 1;
	}

  uint32_t Nand_Flash_ID = 0;
  NAND_IDTypeDef NAND_ID = {0};
  HAL_NAND_Read_ID(&NAND_HANDLE, &NAND_ID);

  Nand_Flash_ID = NAND_ID.Device_Id << 16;
  Nand_Flash_ID |= NAND_ID.Third_Id << 8;
  Nand_Flash_ID |= NAND_ID.Fourth_Id;

  if (Nand_Flash_ID != MT29F4G08ABADA)
  {
    return 1;
  }

  return 0;
}



/**
 * @brief 擦除整个NAND FLASH
 * @return {*}
 */
uint8_t Bsp_Nand_Erase(void)
{
  NAND_AddressTypeDef Nand_Add = {0,0,0};
  HAL_StatusTypeDef Status = HAL_ERROR;

  for(uint16_t i = 0 ; i < NAND_HANDLE.Config.BlockNbr ; i++)
  {
    Nand_Add.Block = i;
    Status = HAL_NAND_Erase_Block(&NAND_HANDLE , &Nand_Add);
  }

  Nand_Add.Plane = 1;
  Nand_Add.Block = 0;
  for(uint16_t i = 0 ; i < NAND_HANDLE.Config.BlockNbr ; i++)
  {
    Nand_Add.Block = i;
    Status = HAL_NAND_Erase_Block(&NAND_HANDLE , &Nand_Add);
  }


  return Status;
}
	
  
/* FlashFS API的返回值 */
static const char * ReVal_Table[]= 
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


void Nand_Demo(void)
{
  uint8_t result;
	fsMediaInfo info;
	uint64_t ullSdCapacity;
	int32_t id;  
	uint8_t buf[15];
	uint32_t ser_num;
	fsStatus restatus;
	char *opt;
	
	result = finit("N0:");
	
	/* 加载SD卡 */
	result = fmount("N0:");
	if(result != NULL)
	{
		/* 如果挂载失败，务必不要再调用FlashFS的其它API函数，防止进入硬件异常 */
		printf("挂载文件系统失败 (%s)\r\n", ReVal_Table[result]);
	}
	else
	{
		printf("挂载文件系统成功 (%s)\r\n", ReVal_Table[result]);
	}

	/* 格式化 */
	opt = "/LL /L nand /FAT16";
	printf("文件系统格式中......\r\n");
	result = fformat ("N0:", opt);
	printf("文件系统格式化 (%s)\r\n", ReVal_Table[result]);
	
	printf("------------------------------------------------------------------\r\n");
	
	/* 获取volume label */
	if (fvol ("N0:", (char *)buf, &ser_num) == 0) 
	{
		if (buf[0]) 
		{
			printf ("NAND的volume label是 %s\r\n", buf);
		}
		else 
		{
			printf ("NAND没有volume label\r\n");
		}
		
		printf ("NAND的volume serial number是 %d\r\n", ser_num);
	}
	else 
	{
		printf ("Volume访问错误\r\n");
	}

	/* 获取SD卡剩余容量 */
	ullSdCapacity = ffree("N0:");
	DotFormat(ullSdCapacity, (char *)buf);
	printf("NAND剩余容量 = %10s字节\r\n", buf);
	
	/* 获取相应存储设备的句柄，注意挂载后操作下面的IO控制才是有效的 */
	id = fs_ioc_get_id("N0");          
   
	/* 访问的时候要加上锁 */
	fs_ioc_lock (id);
	
	/* 初始化FAT文件系统格式的存储设备 */

	/* 获取存储设备的扇区信息 */
	restatus = fs_ioc_read_info (id, &info);
	if(restatus == fsOK)
	{
		/* 总的扇区数 * 扇区大小，SD卡的扇区大小是512字节 */
		ullSdCapacity = (uint64_t)info.block_cnt << 9;
		DotFormat(ullSdCapacity, (char *)buf);
		printf("NAND总容量 = %10s字节\r\nSD卡的总扇区数 = %d \r\n", buf, info.block_cnt);
	}
	else
	{
		printf("获取配置信息失败 %s\r\n", ReVal_Table[restatus]);
	}
	
	/* 访问结束要解锁 */
	fs_ioc_unlock (id);

	printf("NAND读扇区大小 = %d字节\r\n", info.read_blen);
	printf("NAND写扇区大小 = %d字节\r\n", info.write_blen);
	
	/* 卸载SD卡 */
	result = funmount("N0:");
	if(result != NULL)
	{
		printf("卸载文件系统失败\r\n");
	}
	else
	{
		printf("卸载文件系统成功\r\n");
	}

	printf("------------------------------------------------------------------\r\n");
}






void DotFormat(uint64_t _ullVal, char *_sp) 
{
	/* 数值大于等于10^9 */
	if (_ullVal >= (uint64_t)1e9) 
	{
		_sp += sprintf (_sp, "%d.", (uint32_t)(_ullVal / (uint64_t)1e9));
		_ullVal %= (uint64_t)1e9;
		_sp += sprintf (_sp, "%03d.", (uint32_t)(_ullVal / (uint64_t)1e6));
		_ullVal %= (uint64_t)1e6;
		sprintf (_sp, "%03d.%03d", (uint32_t)(_ullVal / 1000), (uint32_t)(_ullVal % 1000));
		return;
	}
	
	/* 数值大于等于10^6 */
	if (_ullVal >= (uint64_t)1e6) 
	{
		_sp += sprintf (_sp,"%d.", (uint32_t)(_ullVal / (uint64_t)1e6));
		_ullVal %= (uint64_t)1e6;
		sprintf (_sp,"%03d.%03d", (uint32_t)(_ullVal / 1000), (uint32_t)(_ullVal % 1000));
		return;
	}
	
	/* 数值大于等于10^3 */
	if (_ullVal >= 1000) 
	{
		sprintf (_sp, "%d.%03d", (uint32_t)(_ullVal / 1000), (uint32_t)(_ullVal % 1000));
		return;
	}
	
	/* 其它数值 */
	sprintf (_sp,"%d",(uint32_t)(_ullVal));
}


/* 必须等待，否则读出数据异常, 此处应该判断超时*/
int32_t Driver_NAND0_GetDeviceBusy (uint32_t dev_num)
{
	uint16_t k; 	
	for (k = 0; k < 200; k++)	
	{	
		if ((GPIOD->IDR & GPIO_PIN_6) == 0) break;	
	}	
	for (k = 0; k < 2000; k++)	
	{	
		if ((GPIOD->IDR & GPIO_PIN_6) != 0) break;	
	}	
	
	return 0;
}

