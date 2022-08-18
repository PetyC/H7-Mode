/*
 * @Description: FatFs
 * @Autor: Pi
 * @Date: 2022-04-02 19:46:34
 * @LastEditTime: 2022-04-06 22:26:39
 */
#include "User_FatFs.h"

#include "string.h"

static FATFS sysFs;

static BYTE gFsWork[_MAX_SS]; /* Work area (larger is better for processing time) */



/**
 * @msg: 初始化分区并挂载
 * @param {void}
 * @return {uint8_t} 0:挂载成功   1:挂载失败
 */
uint8_t User_FatFs_Init(void)
{
	FRESULT res = FR_NO_FILESYSTEM;

	res = f_mount(&sysFs, "0:", 1);				

	if (res == FR_OK)
	{
		return 0;
	}

	res = f_mkfs("0:", FM_FAT, 0, gFsWork, _MAX_SS);

	if (res != FR_OK)
	{
		return 1;
	}

	res = f_mount(&sysFs, "0:", 1);

	if (res == FR_OK)
	{
		// f_setlabel((const TCHAR *)"0:W25Q128");	//设置Flash磁盘的名字为：ALIENTEK
		return 0;
	}
	else
	{
		return 1;
	}
}



uint32_t Flie_Typedef = 0;
FIL fil;
unsigned int count = 0;
uint8_t read_buf[50] = {0};
uint8_t write_buf[50] = {0};

void User_FatFs_Demo(void)
{
	for(uint16_t i = 0 ; i< 50 ; i++)
	{
		write_buf[i] = i;
	}

	FRESULT res;
	
	Flie_Typedef = f_typetell("0:/sudaroot");			//存在问题
	
	res = f_open(&fil, "0:/Demo.bin", FA_READ);
				
	if(res != FR_OK)
	{
		return;
	}

	res = f_read(&fil, read_buf, sizeof(read_buf), &count);
	

	if(res != FR_OK)
	{
		count = 0;
		f_close(&fil);
		return;
	}
	


	

	count = 0;
	f_close(&fil);

}













/**
 * @msg:返回磁盘剩余容量
 * @param {uint8_t} *drv   磁盘编号("0:"/"1:")
 * @param {uint32_t} *total  总容量	 （单位KB）
 * @param {uint32_t} *free   （单位KB）
 * @return {uint8_t} 0:正常   1:错误
 */
uint8_t exf_getfree(uint8_t *drv, uint32_t *total, uint32_t *free)
{
	FATFS *fs1;
	uint8_t res;
	uint32_t fre_clust = 0, fre_sect = 0, tot_sect = 0;

	//得到磁盘信息及空闲簇数量
	res = (uint32_t)f_getfree((const TCHAR *)drv, (DWORD *)&fre_clust, &fs1);

	if (res == 0)
	{
		tot_sect = (fs1->n_fatent - 2) * fs1->csize; //得到总扇区数
		fre_sect = fre_clust * fs1->csize;			 //得到空闲扇区数
#if FF_MAX_SS != 512								 //扇区大小不是512字节,则转换为512字节
		tot_sect *= fs1->ssize / 512;
		fre_sect *= fs1->ssize / 512;
#endif
		*total = tot_sect >> 1; //单位为KB
		*free = fre_sect >> 1;	//单位为KB
	}
	return res;
}

/**
 * @msg: 将小写字母转为大写字母,如果是数字,则保持不变.
 * @param {uint8_t} c
 * @return {*}
 */
uint8_t char_upper(uint8_t c)
{
	if (c < 'A')
		return c; //数字,保持不变.
	if (c >= 'a')
		return c - 0x20; //变为大写.
	else
		return c; //大写,保持不变
}

#define FILE_MAX_TYPE_NUM 7 //最多FILE_MAX_TYPE_NUM个大类
#define FILE_MAX_SUBT_NUM 4 //最多FILE_MAX_SUBT_NUM个小类
uint8_t *const FILE_TYPE_TBL[FILE_MAX_TYPE_NUM][FILE_MAX_SUBT_NUM] =
	{
		{"BIN"},					   // BIN文件
		{"LRC"},					   // LRC文件
		{"NES", "SMS"},				   // NES/SMS文件
		{"TXT", "C", "H"},			   //文本文件
		{"WAV", "MP3", "APE", "FLAC"}, //支持的音乐文件
		{"BMP", "JPG", "JPEG", "GIF"}, //图片文件
		{"AVI"},					   //视频文件
};
/**
 * @msg: 返回文件的类型
 * @param {uint8_t} *fname   文件名
 * @return {uint8_t} 0XFF: 表示无法识别的文件类型编号  其他,高四位表示所属大类,低四位表示所属小类.
 */
uint8_t f_typetell(uint8_t *fname)
{
	uint8_t tbuf[5];
	uint8_t *attr = '\0'; //后缀名
	uint8_t i = 0, j;
	while (i < 250)
	{
		i++;
		if (*fname == '\0')
			break; //偏移到了最后了.
		fname++;
	}
	if (i == 250)
		return 0XFF;		//错误的字符串.
	for (i = 0; i < 5; i++) //得到后缀名
	{
		fname--;
		if (*fname == '.')
		{
			fname++;
			attr = fname;
			break;
		}
	}
	if (attr == 0)
		return 0XFF;
	strcpy((char *)tbuf, (const char *)attr); // copy
	for (i = 0; i < 4; i++)
		tbuf[i] = char_upper(tbuf[i]);		//全部变为大写
	for (i = 0; i < FILE_MAX_TYPE_NUM; i++) //大类对比
	{
		for (j = 0; j < FILE_MAX_SUBT_NUM; j++) //子类对比
		{
			if (*FILE_TYPE_TBL[i][j] == 0)
				break;																//此组已经没有可对比的成员了.
			if (strcmp((const char *)FILE_TYPE_TBL[i][j], (const char *)tbuf) == 0) //找到了
			{
				return (i << 4) | j;
			}
		}
	}
	return 0XFF; //没找到
}
