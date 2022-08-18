#include <w25qXX.h>

/* 本文件使用的全局变量 */
static __IO uint8_t cmd_Completed, rx_Completed, tx_Completed, status_Match, timeout;

/* 仅限本文件使用的函数 */
static void QSPI_W25Qx_Write_Enable(QSPI_HandleTypeDef *hqspi);
static uint8_t QSPI_W25Qx_AutoPollingMemRead(uint32_t Timeout);
static void QSPI_W25Qx_Enter(QSPI_HandleTypeDef *hqspi);
static void QSPI_W25Qx_Exit(QSPI_HandleTypeDef *hqspi);
static void Flash_Error_Handler(void);



/**
 * @brief 初始化W25QXX
 * @param {*}
 * @return {uint8_t} 0:成功  1:失败
 */
uint8_t QSPI_W25Qx_Init(void)
{	
	uint32_t FLASH_ID = 0;
	uint32_t FLASH_Type = 0;
	
	QSPI_W25Qx_Reset_Memory();
	
	FLASH_ID = QSPI_W25Qx_ReadID();
	FLASH_Type = QSPI_W25Qx_Read_Type();

	if(FLASH_ID == 0XEF4018 && FLASH_Type == 0XEF17)
	{
		return 0;
	}
	else
	{
		return 1;
	}
	
}


/**
 * @brief 读取外部FLASH的型号  (使用SPI模式的指令)
 * @param {*}
 * @return {uint32_t}  FLASH的ID
 */
uint32_t QSPI_W25Qx_Read_Type(void)
{
	uint32_t Type;

	QSPI_CommandTypeDef s_command = {0};
	uint8_t buf[3];

	/* 基本配置 */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;	 // 1线方式发送指令
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;			 // 24位地址
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; //无交替字节
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;				 // W25Q128JV不支持DDR模式
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;	 // DDR模式，数据输出延迟
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;			 //每次传输都发指令

	/* 读取JEDEC ID */
	s_command.Instruction = READ_ID_CMD; 	//读取命令: 0x90
	s_command.AddressMode = QSPI_ADDRESS_1_LINE; //没有地址
	s_command.DataMode = QSPI_DATA_1_LINE;	   // 1线数据
	s_command.DummyCycles = 0;				   //无空周期
	s_command.NbData = 2;					   //读取三个数据

	/* 发送指令 */
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}

#if QSPI_FLASH_DMA_ENABLE
	cmd_Completed = 0;
	rx_Completed = 0;
	/* MDMA方式读取 */
	if (HAL_QSPI_Receive_DMA(&hqspi, buf) != HAL_OK)
	{
		Flash_Error_Handler();
	}

	/* 等待读取完毕 */
	while (rx_Completed == 0)
		;
	rx_Completed = 0;
#else
	/* 启动接收 */
	if (HAL_QSPI_Receive(&hqspi, buf, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}
#endif

	
	Type = (buf[0] << 8) | buf[1];
	
	return Type;
}



/**
 * @brief 读取外部FLASH的ID  (使用SPI模式的指令)
 * @param {*}
 * @return {uint32_t}  FLASH的ID
 */
uint32_t QSPI_W25Qx_ReadID(void)
{
	uint32_t uiID;

	QSPI_CommandTypeDef s_command = {0};
	uint8_t buf[3];

	/* 基本配置 */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;	 // 1线方式发送指令
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;			 // 24位地址
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; //无交替字节
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;				 // W25Q128JV不支持DDR模式
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;	 // DDR模式，数据输出延迟
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;			 //每次传输都发指令

	/* 读取JEDEC ID */
	s_command.Instruction = READ_JEDEC_ID_CMD; //读取ID命令: 0x9F
	s_command.AddressMode = QSPI_ADDRESS_NONE; //没有地址
	s_command.DataMode = QSPI_DATA_1_LINE;	   // 1线数据
	s_command.DummyCycles = 0;				   //无空周期
	s_command.NbData = 3;					   //读取三个数据

	/* 发送指令 */
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}

#if QSPI_FLASH_DMA_ENABLE
	cmd_Completed = 0;
	rx_Completed = 0;
	/* MDMA方式读取 */
	if (HAL_QSPI_Receive_DMA(&hqspi, buf) != HAL_OK)
	{
		Flash_Error_Handler();
	}

	/* 等待读取完毕 */
	while (rx_Completed == 0)
		;
	rx_Completed = 0;
#else
	/* 启动接收 */
	if (HAL_QSPI_Receive(&hqspi, buf, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}
#endif

	uiID = (buf[0] << 16) | (buf[1] << 8) | buf[2];

	return uiID;
}

/**
 * @brief 复位外部Flash
 * @param {*}
 * @return {*}
 */
void QSPI_W25Qx_Reset_Memory(void)
{
	QSPI_CommandTypeDef s_command = {0};

	/* 基本配置 */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;	 // 1线方式发送指令
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;			 // 24位地址
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; //无交替字节
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;				 // W25Q128JV不支持DDR模式
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;	 // DDR模式，数据输出延迟
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;			 //每次传输都发指令

	/* 复位使能W25x */
	s_command.Instruction = RESET_ENABLE_CMD;  //复位使能命令
	s_command.AddressMode = QSPI_ADDRESS_NONE; //没有地址
	s_command.DataMode = QSPI_DATA_NONE;	   //没有数据
	s_command.DummyCycles = 0;				   //无空周期

	/* 发送复位使能命令 */
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}

	/* 发送复位命令 */
	s_command.Instruction = RESET_MEMORY_CMD; //复位命令
	/* 发送复位使能命令 */
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}

	/* 自动轮询模式等待等待完成 */
	if (QSPI_W25Qx_AutoPollingMemRead(HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}
}

/**
 * @brief 擦除外部FLASH的扇区（大小：4KB)
 * @param {uint32_t} _sectorAddr 扇区地址，以4KB为单位的地址，比如0，4096，8192等
 * @return {*}
 */
void QSPI_W25Qx_EraseSector(uint32_t _sectorAddr)
{
	QSPI_CommandTypeDef s_command = {0};

	/* 写使能 */
	QSPI_W25Qx_Write_Enable(&hqspi);

	/* 基本配置 */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;	 // 1线方式发送指令
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;			 // 24位地址
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; //无交替字节
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;				 // W25Q128JV不支持DDR模式
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;	 // DDR模式，数据输出延迟
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;			 //每次传输都发指令

	/* 擦除扇区配置 */
	s_command.Instruction = SECTOR_ERASE_CMD;	 //扇区擦除指令
	s_command.AddressMode = QSPI_ADDRESS_1_LINE; // 1线地址方式
	s_command.DataMode = QSPI_DATA_NONE;		 //没有数据
	s_command.Address = _sectorAddr;			 //扇区的首地址，保证是4KB整数倍
	s_command.DummyCycles = 0;					 //无空周期

#if QSPI_FLASH_DMA_ENABLE
	cmd_Completed = 0;

	/* 发送指令 */
	if (HAL_QSPI_Command_IT(&hqspi, &s_command) != HAL_OK)
	{
		Flash_Error_Handler();
	}

	/* 等待命令发送完毕 */
	while (cmd_Completed == 0)
		;
	cmd_Completed = 0;

	/* 等待擦写结束 */
	status_Match = 0;
	QSPI_W25Qx_AutoPollingMemRead(0);
	while (status_Match == 0)
		;
	status_Match = 0;

#else
	/* 发送指令 */
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}

	/* 自动轮询模式等待编程结束 */
	if (QSPI_W25Qx_AutoPollingMemRead(W25Q128JV_SUBSECTOR_ERASE_MAX_TIME) != HAL_OK)
	{
		Flash_Error_Handler();
	}
#endif
}

/**
 * @brief 连续读取若干字节，字节的个数不能超出芯片容量  (从SPI模式切换到QSPI模式，读取完毕后切换回SPI模式（其他函数仅仅支持SPI模式）。)
 * @param {uint8_t} *_pBuf 读取数据的存放地址
 * @param {uint32_t} _read_Addr 起始的地址
 * @param {uint32_t} _read_Size  数据个数，可以大于W25Q128JV_PAGE_SIZE,但不能超出芯片总容量
 * @return {*}
 */
void QSPI_W25Qx_Read_Buffer(uint8_t *_pBuf, uint32_t _read_Addr, uint32_t _read_Size)
{
	QSPI_CommandTypeDef s_command = {0};

	/* 进入QSPI模式 */
	QSPI_W25Qx_Enter(&hqspi);

	/* 开始从FLASH读取数据 */
	/* 基本配置 */
	s_command.InstructionMode = QSPI_INSTRUCTION_4_LINES;	 // 1线方式发送指令
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;			 // 24位地址
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; //无交替字节
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;				 // W25Q128JV不支持DDR模式
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;	 // DDR模式，数据输出延迟
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;			 //每次传输都发指令

	/*读取序列配置 */
	s_command.Instruction = QUAD_INOUT_FAST_READ_CMD; // 24位四线快速写入指令
	s_command.AddressMode = QSPI_ADDRESS_4_LINES;	  // 4线地址方式
	s_command.DataMode = QSPI_DATA_4_LINES;			  // 4线数据方式
	s_command.Address = _read_Addr;					  //写入数据的地址
	s_command.NbData = _read_Size;					  //写入数据的大小
	s_command.DummyCycles = 2;						  //两个空闲状态周期（4个时钟周期），结合时序理解

	/* 发送指令 */
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}

#if QSPI_FLASH_DMA_ENABLE
	rx_Completed = 0;
	cmd_Completed = 0;

	/*	while(cmd_Completed == 0);
		cmd_Completed = 0;*/

	/* 读取数据（DMA方式） */
	if (HAL_QSPI_Receive_DMA(&hqspi, _pBuf) != HAL_OK)
	{
		Flash_Error_Handler();
	}

	/* 等待DMA读取完毕 */
	while (rx_Completed == 0)
		;
	rx_Completed = 0;

#else

	/* 读取数据 */
	if (HAL_QSPI_Receive(&hqspi, _pBuf, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}

#endif

	/* 退出QSPI模式 */
	QSPI_W25Qx_Exit(&hqspi);
}

/**
 * @brief 页编程，通过QSPI将数据写入外部FALSH (华邦的W25Q128JV仅仅支持SPI模式写入)
 * @param {uint8_t} *_pBuf 需要存入数据的指针
 * @param {uint32_t} _write_Addr 目标区域首地址，即页首地址，比如0，256，512等。
 * @param {uint16_t} _write_Size 数据个数，不能超过页的大小，可以填入（1 ~ 256）
 * @return {*}
 */
uint8_t QSPI_W25Qx_Write_Buffer(uint8_t *_pBuf, uint32_t _write_Addr, uint16_t _write_Size)
{
	QSPI_CommandTypeDef s_command = {0};

	/* 防止写入的大小超过256字节 */
	if (_write_Size > W25Q128JV_PAGE_SIZE)
	{
		/* 进入断言，提示错误 */
		Flash_Error_Handler();
	}

	QSPI_W25Qx_Write_Enable(&hqspi); //写使能

	/* 基本配置 */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;	 // 1线方式发送指令
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;			 // 24位地址
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; //无交替字节
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;				 // W25Q128JV不支持DDR模式
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;	 // DDR模式，数据输出延迟
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;			 //每次传输都发指令

	/*写入序列配置 */
	s_command.Instruction = QUAD_INPUT_PAGE_PROG_CMD; // 24位四线快速写入指令
	s_command.AddressMode = QSPI_ADDRESS_1_LINE;	  // 1线地址方式
	s_command.DataMode = QSPI_DATA_4_LINES;			  // 4线数据方式
	s_command.Address = _write_Addr;				  //写入数据的地址
	s_command.NbData = _write_Size;					  //写入数据的大小
	s_command.DummyCycles = 0;						  //无空周期

	/* 发送指令 */
	if (HAL_QSPI_Command(&hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}

#if QSPI_FLASH_DMA_ENABLE
	tx_Completed = 0;
	status_Match = 0;

	/* 启动传输 */
	if (HAL_QSPI_Transmit_DMA(&hqspi, _pBuf) != HAL_OK)
	{
		Flash_Error_Handler();
	}

	/* 等待发送完毕 */
	while (tx_Completed == 0)
		;
	tx_Completed = 0;

	/* 等待写入结束 */
	QSPI_W25Qx_AutoPollingMemRead(0);
	while (status_Match == 0)
		;
	status_Match = 0;

#else
	/* 启动传输 */
	if (HAL_QSPI_Transmit(&hqspi, _pBuf, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}

	/* 自动轮询模式等待编程结束 */
	if (QSPI_W25Qx_AutoPollingMemRead(W25Q128JV_SUBSECTOR_ERASE_MAX_TIME) != HAL_OK)
	{
		Flash_Error_Handler();
	}

#endif

	return 1;
}



/**
 * @brief 外部FLASH写使能 (使用SPI模式的指令)
 * @param {QSPI_HandleTypeDef} *hqspi
 * @return {*}
 */
static void QSPI_W25Qx_Write_Enable(QSPI_HandleTypeDef *hqspi)
{
	QSPI_CommandTypeDef s_command = {0};

	/* 基本配置 */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE; // 1线方式发送指令
	// s_command.AddressSize       = QSPI_ADDRESS_24_BITS;       //24位地址
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; //无交替字节
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;				 // W25Q128JV不支持DDR模式
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;	 // DDR模式，数据输出延迟
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;			 //每次传输都发指令

	/* 写入使能配置 */
	s_command.Instruction = WRITE_ENABLE_CMD;  //写使能命令
	s_command.AddressMode = QSPI_ADDRESS_NONE; //没有地址
	s_command.DataMode = QSPI_DATA_NONE;	   //没有数据
	s_command.DummyCycles = 0;				   //无空周期
	s_command.NbData = 0;					   //空数据

#if QSPI_FLASH_DMA_ENABLE

	if (HAL_QSPI_Command_IT(hqspi, &s_command) != HAL_OK)
	{
		Flash_Error_Handler();
	}

	while (cmd_Completed == 0)
		;
	cmd_Completed = 0;

#else
	/* 发送指令 */
	if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}

	QSPI_AutoPollingTypeDef s_config = {0};
	/* 配置自动轮询模式等待操作完成 */
	s_config.Match = W25Q128JV_FSR_WREN;
	s_config.Mask = W25Q128JV_FSR_WREN;
	s_config.MatchMode = QSPI_MATCH_MODE_AND;
	s_config.StatusBytesSize = 1;
	s_config.Interval = 0x10;
	s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	s_command.Instruction = READ_STATUS_REG1_CMD;
	s_command.DataMode = QSPI_DATA_1_LINE;
	s_command.NbData = 1;

	if (HAL_QSPI_AutoPolling(hqspi, &s_command, &s_config, HAL_QSPI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}

#endif
}

/**
 * @brief 外部FLASH芯片进入QSPI模式
 * @param {QSPI_HandleTypeDef} *hqspi
 * @return {*}
 */
static void QSPI_W25Qx_Enter(QSPI_HandleTypeDef *hqspi)
{
	QSPI_CommandTypeDef s_command = {0};
	/* 配置FLASH进入QPSI模式 */
	/* 基本配置 */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;	 // 1线方式发送指令
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;			 // 24位地址
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; //无交替字节
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;				 // W25Q128JV不支持DDR模式
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;	 // DDR模式，数据输出延迟
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;			 //每次传输都发指令

	/* 写入序列配置 */
	s_command.Instruction = ENTER_QPI_MODE_CMD; //进入QSPI模式
	s_command.AddressMode = QSPI_ADDRESS_NONE;	//无地址方式
	s_command.DataMode = QSPI_DATA_NONE;		//无数据方式
	s_command.DummyCycles = 0;					// 0空闲状态周期

	/* 发送指令 */
	if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}
}

/**
 * @brief  外部FLASH芯片退出QSPI模式
 * @param {QSPI_HandleTypeDef} *hqspi
 * @return {*}
 */
static void QSPI_W25Qx_Exit(QSPI_HandleTypeDef *hqspi)
{
	QSPI_CommandTypeDef s_command = {0};

	/* 基本配置 */
	s_command.InstructionMode = QSPI_INSTRUCTION_4_LINES;	 // 4线方式发送指令
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;			 // 24位地址
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; //无交替字节
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;				 // W25Q128JV不支持DDR模式
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;	 // DDR模式，数据输出延迟
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;			 //每次传输都发指令

	/* 写入序列配置 */
	s_command.Instruction = EXIT_QPI_MODE_CMD; //进入QSPI模式
	s_command.AddressMode = QSPI_ADDRESS_NONE; //无地址方式
	s_command.DataMode = QSPI_DATA_NONE;	   //无数据方式
	s_command.DummyCycles = 0;				   // 0空闲状态周期

	/* 发送指令 */
	if (HAL_QSPI_Command(hqspi, &s_command, HAL_QPSI_TIMEOUT_DEFAULT_VALUE) != HAL_OK)
	{
		Flash_Error_Handler();
	}
}

/**
 * @brief 等待QSPI Flash就绪
 * @param {uint32_t} Timeout   超时时间
 * @return {uint8_t}Flash的状态
 */
static uint8_t QSPI_W25Qx_AutoPollingMemRead(uint32_t Timeout)
{
	QSPI_CommandTypeDef s_command = {0};
	QSPI_AutoPollingTypeDef s_config = {0};

	/* 基本配置 */
	s_command.InstructionMode = QSPI_INSTRUCTION_1_LINE;	 // 1线方式发送指令
	s_command.AddressSize = QSPI_ADDRESS_24_BITS;			 // 24位地址
	s_command.AlternateByteMode = QSPI_ALTERNATE_BYTES_NONE; //无交替字节
	s_command.DdrMode = QSPI_DDR_MODE_DISABLE;				 // W25Q128JV不支持DDR模式
	s_command.DdrHoldHalfCycle = QSPI_DDR_HHC_ANALOG_DELAY;	 // DDR模式，数据输出延迟
	s_command.SIOOMode = QSPI_SIOO_INST_EVERY_CMD;			 //每次传输都发指令

	/* 配置自动轮询模式 */
	s_command.Instruction = READ_STATUS_REG1_CMD; //读取状态寄存器
	s_command.AddressMode = QSPI_ADDRESS_NONE;	  //没有地址
	s_command.DataMode = QSPI_DATA_1_LINE;		  // 1线数据
	s_command.DummyCycles = 0;					  //无空周期

	/* 配置自动轮询寄存器（不断查询状态寄存器bit0，等待其为0） */
	s_config.Match = 0x00;					  //等待其为0
	s_config.Mask = W25Q128JV_FSR_BUSY;		  //状态寄存器bit0
	s_config.MatchMode = QSPI_MATCH_MODE_AND; //逻辑与
	s_config.StatusBytesSize = 1;
	s_config.Interval = 0x10;
	s_config.AutomaticStop = QSPI_AUTOMATIC_STOP_ENABLE;

	/* 自动轮询模式等待编程结束 */
#if QSPI_FLASH_DMA_ENABLE
	if (HAL_QSPI_AutoPolling_IT(&hqspi, &s_command, &s_config) != HAL_OK)
	{
		Flash_Error_Handler();
	}
#else
	if (HAL_QSPI_AutoPolling(&hqspi, &s_command, &s_config, Timeout) != HAL_OK)
	{
		Flash_Error_Handler();
	}
#endif

	return FLASH_OK;
}

/**
 * @brief QSPI命令完成中断回调函数，
 * @param {QSPI_HandleTypeDef} *hqspi
 * @return {*}
 */
void HAL_QSPI_CmdCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	cmd_Completed++;
}

/**
 * @brief QSPI接收完成中断回调函数
 * @param {*}
 * @return {*}
 */
void HAL_QSPI_RxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	rx_Completed++;
}

/**
 * @brief  QSPI发送完成中断回调函数
 * @param {QSPI_HandleTypeDef} *hqspi
 * @return {*}
 */
void HAL_QSPI_TxCpltCallback(QSPI_HandleTypeDef *hqspi)
{
	tx_Completed++;
}

/**
 * @brief QSPI状态匹配回调中断回调函数
 * @param {QSPI_HandleTypeDef} *hqspi
 * @return {*}
 */
void HAL_QSPI_StatusMatchCallback(QSPI_HandleTypeDef *hqspi)
{
	status_Match++;
}

/**
 * @brief 当FLASH发生错误时进入
 * @param {*}
 * @return {*}
 */
static void Flash_Error_Handler(void)
{

	__disable_irq();
	while (1)
	{
	}
}
