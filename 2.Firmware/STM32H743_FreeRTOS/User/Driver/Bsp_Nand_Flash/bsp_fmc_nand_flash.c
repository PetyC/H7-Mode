/*
*********************************************************************************************************
*
*	模块名称 : NAND Flash驱动模块
*	文件名称 : NAND_STM32F1xx.c
*	版    本 : V1.0
*	说    明 : 提供NAND Flash (HY27UF081G2A， 8bit 128K字节 大页)的底层接口函数。【安富莱原创】
*              基于bsp_nand_flash.c文件修改而来。
*
*	修改记录 :
*		版本号  日期        作者       说明
*		V1.0    2019-07-01  Eric2013  正式发布
*
*	Copyright (C), 2019-2030, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "bsp.h"


/* 引脚PG6的超时判断和使能 */
#define TIMEOUT_COUNT		400000000  
#define ENABLE_TIMEOUT		0


/*
	【NAND Flash 结构定义】
     备用区有16x4字节，每page 2048字节，每512字节一个扇区，每个扇区对应16自己的备用区：

	 每个PAGE的逻辑结构，前面512Bx4是主数据区，后面16Bx4是备用区
	┌──────┐┌──────┐┌──────┐┌──────┐┌──────┐┌──────┐┌──────┐┌──────┐
	│ Main area  ││ Main area  ││ Main area  ││Main area   ││ Spare area ││ Spare area ││ Spare area ││Spare area  │
	│            ││            ││            ││            ││            ││            ││            ││            │
	│   512B     ││    512B    ││    512B    ││    512B    ││    16B     ││     16B    ││     16B    ││    16B     │
	└──────┘└──────┘└──────┘└──────┘└──────┘└──────┘└──────┘└──────┘

	 每16B的备用区的逻辑结构如下:(FlashFS中的配置）
	┌───┐┌───┐┌───┐┌───┐┌──┐┌───┐┌───┐┌───┐┌──┐┌──┐┌──┐┌──┐┌───┐┌───┐┌───┐┌───┐
	│LSN0  ││LSN1  ││LSN2  ││LSN3  ││COR ││BBM   ││ECC0  ││ECC1  ││ECC2││ECC3││ECC4││ECC5││  ECC6││  ECC7││ ECC8 ││ ECC9 │
	│      ││      ││      ││      ││    ││      ││      ││      ││    ││    ││    ││    ││      ││      ││      ││      │
	└───┘└───┘└───┘└───┘└──┘└───┘└───┘└───┘└──┘└──┘└──┘└──┘└───┘└───┘└───┘└───┘

    - LSN0 ~ LSN3 : 逻辑扇区号(logical sector number) 。
	- COR         : 数据损坏标记（data corrupted marker）。
	- BBM         : 坏块标志(Bad Block Marker)。
    - ECC0 ~ ECC9 : 512B主数据区的ECC校验。

	K9F1G08U0A 和 HY27UF081G2A 是兼容的。芯片出厂时，厂商保证芯片的第1个块是好块。如果是坏块，则在该块的第1个PAGE的第1个字节
	或者第2个PAGE（当第1个PAGE坏了无法标记为0xFF时）的第1个字节写入非0xFF值。坏块标记值是随机的，软件直接判断是否等于0xFF即可。

	注意：网上有些资料说NAND Flash厂商的默认做法是将坏块标记定在第1个PAGE的第6个字节处。这个说法是错误。坏块标记在第6个字节仅针对部分小扇区（512字节）的NAND Flash
	并不是所有的NAND Flash都是这个标准。大家在更换NAND Flash时，请仔细阅读芯片的数据手册。

*/

/* 定义NAND Flash的物理地址。这个是由硬件决定的 */
#define Bank_NAND_ADDR     ((uint32_t)0x80000000)

/* 定义操作NAND Flash用到3个宏 */
#define NAND_CMD_AREA		*(__IO uint8_t *)(Bank_NAND_ADDR | CMD_AREA)
#define NAND_ADDR_AREA		*(__IO uint8_t *)(Bank_NAND_ADDR | ADDR_AREA)
#define NAND_DATA_AREA		*(__IO uint8_t *)(Bank_NAND_ADDR | DATA_AREA)


#define BUSY_GPIO	GPIOD
#define BUSY_PIN	GPIO_PIN_6

/* 必须等待，否则读出数据异常, 此处应该判断超时*/
#define WAIT_BUSY()	{	\
	uint16_t k; 	\
	for (k = 0; k < 200; k++)	\
	{	\
		if ((BUSY_GPIO->IDR & BUSY_PIN) == 0) break;	\
	}	\
	for (k = 0; k < 2000; k++)	\
	{	\
		if ((BUSY_GPIO->IDR & BUSY_PIN) != 0) break;	\
	}	\
}

static uint32_t FMC_NAND_GetStatus(void);

static uint32_t FMC_NAND_EraseBlock(uint32_t _ulBlockNo);
static void bsp_FMC_NAND_Init(void);
static uint8_t FMC_NAND_Reset(void);


/**
  \fn          int32_t Driver_NANDx_GetDeviceBusy (uint32_t dev_num)
  \brief       NAND Driver GetDeviceBusy callback.
               Needs to be implemented by user.
  \param[in]   dev_num   Device number
  \return      1=busy, 0=not busy, or error
*/
int32_t Driver_NAND0_GetDeviceBusy (uint32_t dev_num)
{
	WAIT_BUSY();
	
	return 0;
}
/*
*********************************************************************************************************
*	函 数 名: NAND_Init
*	功能说明: 初始化NAND Flash接口
*	形    参:  无
*	返 回 值: 执行结果：
*			  - NAND_FAIL 表示失败
*			  - NAND_OK 表示成功
*********************************************************************************************************
*/
uint8_t NAND_Init(void)
{
	bsp_FMC_NAND_Init();		/* 配置FSMC和GPIO用于NAND Flash接口 */

	FMC_NAND_Reset();			/* 通过复位命令复位NAND Flash到读状态 */

	return 0;
}

/*
*********************************************************************************************************
*	函 数 名: bsp_FMC_NAND_Init
*	功能说明: 配置FSMC和GPIO用于NAND Flash接口。这个函数必须在读写nand flash前被调用一次。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void bsp_FMC_NAND_Init(void)
{
	/* --NAND Flash GPIOs 配置  ------*/
	{
		/*
			PD0/FMC_D2
			PD1/FMC_D3
			PD4/FMC_NOE
			PD5/FMC_NWE
		
				PD7/FMC_NCE2  --替换为 PG9/FMC_NCE3
		
			PD11/FMC_A16/FMC_CLE
			PD12/FMC_A17/FMC_ALE
			PD14/FMC_D0
			PD15/FMC_D1

			PE7/FMC_D4
			PE8/FMC_D5
			PE9/FMC_D6
			PE10/FMC_D7

			PD6/FMC_NWAIT	(本例程用查询方式判忙，此口线作为普通GPIO输入功能使用)
		*/
		GPIO_InitTypeDef gpio_init_structure;

		/* 使能 GPIO时钟 */
		__HAL_RCC_GPIOD_CLK_ENABLE();
		__HAL_RCC_GPIOE_CLK_ENABLE();

		/* 使能FMC时钟 */
		__HAL_RCC_FMC_CLK_ENABLE();

		/* 设置 GPIOD 相关的IO为复用推挽输出 */
		gpio_init_structure.Mode = GPIO_MODE_AF_PP;
		gpio_init_structure.Pull = GPIO_PULLUP;
		gpio_init_structure.Speed = GPIO_SPEED_FREQ_MEDIUM;
		gpio_init_structure.Alternate = GPIO_AF12_FMC;
		
		/* 配置GPIOD */
		gpio_init_structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 |
									GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_14 |
									GPIO_PIN_15;
		HAL_GPIO_Init(GPIOD, &gpio_init_structure);

		/* 配置GPIOE */
		gpio_init_structure.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
		HAL_GPIO_Init(GPIOE, &gpio_init_structure);
		
		/* 配置GPIOG NAND 片选 */
		gpio_init_structure.Pin = GPIO_PIN_9;
		HAL_GPIO_Init(GPIOG, &gpio_init_structure);		

		/* busy R/B 设置为输入 */
		gpio_init_structure.Mode = GPIO_MODE_INPUT;			/* 设置输入 */
		gpio_init_structure.Pull = GPIO_NOPULL;				/* 上下拉电阻不使能 */
		gpio_init_structure.Speed = GPIO_SPEED_FREQ_MEDIUM;  	/* GPIO速度等级 */
		gpio_init_structure.Pin = BUSY_PIN;	
		HAL_GPIO_Init(BUSY_GPIO, &gpio_init_structure);	
	}

	{
		NAND_HandleTypeDef hNand = {0};
		
		FMC_NAND_PCC_TimingTypeDef CommonSpaceTiming;
		FMC_NAND_PCC_TimingTypeDef AttributeSpaceTiming;
		
		hNand.Instance = FMC_NAND_DEVICE;									
		hNand.Init.NandBank = FMC_NAND_BANK3;						/* 定义FSMC NAND BANK 号 */
		hNand.Init.Waitfeature = FMC_NAND_PCC_WAIT_FEATURE_DISABLE;	/* 插入等待时序使能, 禁止 */
		hNand.Init.MemoryDataWidth = FMC_NAND_PCC_MEM_BUS_WIDTH_8;	/* 数据宽度 8bit */
		hNand.Init.EccComputation = FMC_NAND_ECC_DISABLE;			/* ECC错误检查和纠正功能 - 禁止 */
		hNand.Init.ECCPageSize = FMC_NAND_ECC_PAGE_SIZE_2048BYTE;	/* ECC 页面大小 */
		hNand.Init.TCLRSetupTime = 0x03;							/* CLE低和RE低之间的延迟，HCLK周期数 */	
		hNand.Init.TARSetupTime = 0x03;                             /* ALE低和RE低之间的延迟，HCLK周期数 */
   
		/* 2-5-3-1 V6 OK   4-10-6-2 异常 */
		CommonSpaceTiming.SetupTime = 3;
		CommonSpaceTiming.WaitSetupTime = 5;
		CommonSpaceTiming.HoldSetupTime = 3;
		CommonSpaceTiming.HiZSetupTime = 3;
    
		AttributeSpaceTiming.SetupTime = 3;
		AttributeSpaceTiming.WaitSetupTime = 5;
		AttributeSpaceTiming.HoldSetupTime = 3;
		AttributeSpaceTiming.HiZSetupTime = 3;

		HAL_NAND_Init(&hNand, &CommonSpaceTiming, &AttributeSpaceTiming); 
	}
}

/*
*********************************************************************************************************
*	函 数 名: FMC_NAND_Reset
*	功能说明: 复位NAND Flash
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
static uint8_t FMC_NAND_Reset(void)
{
	NAND_CMD_AREA = NAND_CMD_RESET;

	/* 检查操作状态 */
	if (FMC_NAND_GetStatus() == NAND_READY)
	{
		return NAND_OK;
	}

	return NAND_FAIL;
}

/*
*********************************************************************************************************
*	函 数 名: FSMC_NAND_ReadStatus
*	功能说明: 使用Read statuc 命令读NAND Flash内部状态
*	形    参:  - Address: 被擦除的快内任意地址
*	返 回 值: NAND操作状态，有如下几种值：
*             - NAND_BUSY: 内部正忙
*             - NAND_READY: 内部空闲，可以进行下步操作
*             - NAND_ERROR: 先前的命令执行失败
*********************************************************************************************************
*/
static uint32_t FMC_NAND_ReadStatus(void)
{
	uint8_t ucData;
	uint8_t ucStatus = NAND_BUSY;

	/* 读状态操作 */
	NAND_CMD_AREA = NAND_CMD_STATUS;
	ucData = *(__IO uint8_t *)(Bank_NAND_ADDR);

	if((ucData & NAND_ERROR) == NAND_ERROR)
	{
		ucStatus = NAND_ERROR;
	}
	else if((ucData & NAND_READY) == NAND_READY)
	{
		ucStatus = NAND_READY;
	}
	else
	{
		ucStatus = NAND_BUSY;
	}

	return (ucStatus);
}

/*
*********************************************************************************************************
*	函 数 名: FSMC_NAND_GetStatus
*	功能说明: 获取NAND Flash操作状态
*	形    参:  - Address: 被擦除的快内任意地址
*	返 回 值: NAND操作状态，有如下几种值：
*             - NAND_TIMEOUT_ERROR  : 超时错误
*             - NAND_READY          : 操作成功
*             - NAND_ERROR: 先前的命令执行失败
*********************************************************************************************************
*/
static uint32_t FMC_NAND_GetStatus(void)
{
	uint32_t ulTimeout = 0x10000;
	uint32_t ucStatus = NAND_READY;

	ucStatus = FMC_NAND_ReadStatus();

	/* 等待NAND操作结束，超时后会退出 */
	while ((ucStatus != NAND_READY) &&( ulTimeout != 0x00))
	{
		ucStatus = FMC_NAND_ReadStatus();
		if(ucStatus == NAND_ERROR)
		{
			/* 返回操作状态 */
			return (ucStatus);
		}
		ulTimeout--;
	}

	if(ulTimeout == 0x00)
	{
		ucStatus =  NAND_TIMEOUT_ERROR;
	}

	/* 返回操作状态 */
	return (ucStatus);
}

/*
*********************************************************************************************************
*	函 数 名: NAND_ReadID
*	功能说明: 读NAND Flash的ID。ID存储到形参指定的结构体变量中。
*	形    参:  无
*	返 回 值: 32bit的NAND Flash ID
*********************************************************************************************************
*/
uint32_t NAND_ReadID(void)
{
	uint32_t data = 0;

	/* 发送命令 Command to the command area */
	NAND_CMD_AREA = 0x90;
	NAND_ADDR_AREA = 0x00;

	/* 顺序读取NAND Flash的ID */
	data = *(__IO uint32_t *)(Bank_NAND_ADDR | DATA_AREA);
	data =  ((data << 24) & 0xFF000000) |
			((data << 8 ) & 0x00FF0000) |
			((data >> 8 ) & 0x0000FF00) |
			((data >> 24) & 0x000000FF) ;
	return data;
}

/*
*********************************************************************************************************
*	函 数 名: FMC_NAND_EraseBlock
*	功能说明: 擦除NAND Flash一个块（block）
*	形    参:  - _ulBlockNo: 块号，范围为：0 - 1023,   0-4095
*	返 回 值: NAND操作状态，有如下几种值：
*             - NAND_TIMEOUT_ERROR  : 超时错误
*             - NAND_READY          : 操作成功
*********************************************************************************************************
*/
static uint32_t FMC_NAND_EraseBlock(uint32_t _ulBlockNo)
{
	uint8_t ucStatus;
	
	/* HY27UF081G2A  (128MB)
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		第1字节： A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr 的bit7 - bit0)
		第2字节： 0    0    0    0    A11  A10  A9   A8		(_usPageAddr 的bit11 - bit8, 高4bit必须是0)
		第3字节： A19  A18  A17  A16  A15  A14  A13  A12    A18以上是块号
		第4字节： A27  A26  A25  A24  A23  A22  A21  A20

		H27U4G8F2DTR (512MB)
				  Bit7 Bit6 Bit5 Bit4 Bit3 Bit2 Bit1 Bit0
		第1字节： A7   A6   A5   A4   A3   A2   A1   A0		(_usPageAddr 的bit7 - bit0)
		第2字节： 0    0    0    0    A11  A10  A9   A8		(_usPageAddr 的bit11 - bit8, 高4bit必须是0)
		第3字节： A19  A18  A17  A16  A15  A14  A13  A12    A18以上是块号
		第4字节： A27  A26  A25  A24  A23  A22  A21  A20
		第5字节： A28  A29  A30  A31  0    0    0    0
	*/

	/* 发送擦除命令 */
	NAND_CMD_AREA = NAND_CMD_ERASE0;

	_ulBlockNo <<= 6;	/* 块号转换为页编号 */

	#if NAND_ADDR_5 == 0	/* 128MB的 */
		NAND_ADDR_AREA = _ulBlockNo;
		NAND_ADDR_AREA = _ulBlockNo >> 8;
	#else		/* 512MB的 */
		NAND_ADDR_AREA = _ulBlockNo;
		NAND_ADDR_AREA = _ulBlockNo >> 8;
		NAND_ADDR_AREA = _ulBlockNo >> 16;
	#endif

	NAND_CMD_AREA = NAND_CMD_ERASE1;

	/* 返回状态 */
	ucStatus = FMC_NAND_GetStatus();
	
	return (ucStatus);
}

/*
*********************************************************************************************************
*	函 数 名: NAND_Format
*	功能说明: NAND Flash格式化，擦除所有的数据，重建LUT
*	形    参:  无
*	返 回 值: NAND_OK : 成功； NAND_Fail ：失败（一般是坏块数量过多导致）
*********************************************************************************************************
*/
uint8_t NAND_Format(void)
{
	uint16_t i;

	for (i = 0; i < NAND_BLOCK_COUNT; i++)
	{
		FMC_NAND_EraseBlock(i);
	}

	return NAND_OK;
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
