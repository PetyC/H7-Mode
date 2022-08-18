/*
 * @Description: LCD初始化文件
 * @Autor: Pi
 * @Date: 2022-01-24 13:59:34
 * @LastEditTime: 2022-06-14 21:40:56
 */

#include "lcd_init.h"
#include "pic.h"
#include "w25qxx.h"
extern SPI_HandleTypeDef hspi1;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*相关命令参数*/
uint8_t Set_Frame_Rate_CMD0[] = {0xB1, 0x02, 0x35, 0x36};                   // Frame rate 80Hz   全色正常模式
uint8_t Set_Frame_Rate_CMD1[] = {0xB2, 0x02, 0x35, 0x36};                   // Frame rate 80Hz   空闲模式8色
uint8_t Set_Frame_Rate_CMD2[] = {0xB3, 0x02, 0x35, 0x36, 0x02, 0x35, 0x36}; // Frame rate 80Hz   局部模式全色

uint8_t Set_Display_Inversion_CMD[] = {0xB4, 0x03}; //开启反转

//------------------------------------ST7735S Power Sequence-----------------------------------------//
uint8_t Set_Power_Sequence_CMD0[] = {0xC0, 0xA2, 0x02, 0x84}; //电源控制1
uint8_t Set_Power_Sequence_CMD1[] = {0xC1, 0xC5};             //电源控制2
uint8_t Set_Power_Sequence_CMD2[] = {0xC2, 0x0D, 0x00};       //电源控制3  正常全色模式
uint8_t Set_Power_Sequence_CMD3[] = {0xC3, 0x8D, 0x2A};       //电源控制3  正常全色模式
uint8_t Set_Power_Sequence_CMD4[] = {0xC4, 0x8D, 0xEE};       //电源控制3  正常全色模式
//---------------------------------End ST7735S Power Sequence---------------------------------------//

// VCOM
uint8_t Set_VCOM_CMD[] = {0xC5, 0x0a};

//内存数据访问控制  通过设置此选项来改变屏幕方向
#if (USE_HORIZONTAL == 0)
uint8_t Set_Memory_Data_Access_CMD[] = {0x36, 0x08}; // 0x08 0xC8 0x78 0xA8
#elif (USE_HORIZONTAL == 1)
uint8_t Set_Memory_Data_Access_CMD[] = {0x36, 0xC8}; // 0x08 0xC8 0x78 0xA8
#elif (USE_HORIZONTAL == 2)
uint8_t Set_Memory_Data_Access_CMD[] = {0x36, 0x78}; // 0x08 0xC8 0x78 0xA8
#else
uint8_t Set_Memory_Data_Access_CMD[] = {0x36, 0xA8}; // 0x08 0xC8 0x78 0xA8
#endif

//------------------------------------ST7735S Gamma Sequence-----------------------------------------//
uint8_t Set_Gamma_Sequence_CMD0[] = {0XE0, 0x12, 0x1C, 0x10, 0x18, 0x33, 0x2C, 0x25, 0x28, 0x28, 0x27, 0x2F, 0x3C, 0x00, 0x03, 0x03, 0x10}; //伽马 + 矫正
uint8_t Set_Gamma_Sequence_CMD1[] = {0XE1, 0x12, 0x1C, 0x10, 0x18, 0x2D, 0x28, 0x23, 0x28, 0x28, 0x26, 0x2F, 0x3B, 0x00, 0x03, 0x03, 0x10}; //伽马 - 矫正
//------------------------------------End ST7735S Gamma Sequence-----------------------------------------//

// 65k mode
uint8_t Set_Interface_Pixel_CMD[] = {
    0x3A,
    0x05,
}; // 16-Bit
// Display on
uint8_t Set_Display_on_CMD[] = {0x29};
// Sleep out
uint8_t Set_Sleep_Out_CMD[] = {0x11};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* LCD Buffer */
#define BUFFER_LEN (uint16_t)32768
#define SRAMD4 __attribute__((section(".RAM_D3")))

SRAMD4 uint8_t LCD_Buffer0[BUFFER_LEN];
SRAMD4 uint8_t LCD_Buffer1[BUFFER_LEN];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief LCD写入8位数据
 * @param {uint8_t} dat 写入的数据
 * @return {*}
 */
void LCD_WR_DATA8(uint8_t dat)
{
    Set_SPI_DATASIZE_8BIT();
    HAL_SPI_Transmit(&hspi1, &dat, 1, 0Xff);
    // HAL_SPI_Transmit_IT(&hspi1, &dat, 1);
}

/**
 * @brief LCD写入16位数据
 * @param {uint16_t} dat  写入的数据
 * @return {*}
 */
void LCD_WR_DATA(uint16_t dat)
{

    Set_SPI_DATASIZE_16BIT();
    HAL_SPI_Transmit(&hspi1, (uint8_t *)&dat, 1, 0Xff);
    // HAL_SPI_Transmit_IT(&hspi1, (uint8_t *)&dat, 1);
}

/**
 * @brief LCD写入命令
 * @param {uint8_t} dat 写入的命令
 * @return {*}
 */
void LCD_WR_REG(uint8_t dat)
{
    LCD_DC_Clr(); //写命令

    LCD_WR_DATA8(dat);

    LCD_DC_Set(); //写数据
}

/**
 * @brief 设置起始和结束地址
 * @param {uint16_t} x1  设置列的起始地址
 * @param {uint16_t} y1  设置行的起始地址
 * @param {uint16_t} x2  设置列的结束地址
 * @param {uint16_t} y2  设置行的结束地址
 * @return {*}
 */
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if (USE_HORIZONTAL == 0)
    {
        LCD_WR_REG(0x2a); //列地址设置
        LCD_WR_DATA(x1 + 2);
        LCD_WR_DATA(x2 + 2);
        LCD_WR_REG(0x2b); //行地址设置
        LCD_WR_DATA(y1 + 1);
        LCD_WR_DATA(y2 + 1);
        LCD_WR_REG(0x2c); //储存器写
    }
    else if (USE_HORIZONTAL == 1)
    {
        LCD_WR_REG(0x2a); //列地址设置
        LCD_WR_DATA(x1 + 2);
        LCD_WR_DATA(x2 + 2);
        LCD_WR_REG(0x2b); //行地址设置
        LCD_WR_DATA(y1 + 3);
        LCD_WR_DATA(y2 + 3);
        LCD_WR_REG(0x2c); //储存器写
    }
    else if (USE_HORIZONTAL == 2)
    {
        LCD_WR_REG(0x2a); //列地址设置
        LCD_WR_DATA(x1 + 1);
        LCD_WR_DATA(x2 + 1);
        LCD_WR_REG(0x2b); //行地址设置
        LCD_WR_DATA(y1 + 2);
        LCD_WR_DATA(y2 + 2);
        LCD_WR_REG(0x2c); //储存器写
    }
    else
    {

        LCD_WR_REG(0x2a); //列地址设置
        LCD_WR_DATA(x1 + 3);
        LCD_WR_DATA(x2 + 3);
        LCD_WR_REG(0x2b); //行地址设置
        LCD_WR_DATA(y1 + 2);
        LCD_WR_DATA(y2 + 2);
        LCD_WR_REG(0x2c); //储存器写
    }
}

/**
 * @brief
 * @param {uint8_t} CMD         命令
 * @param {uint8_t} *Parameter  参数数组
 * @param {uint8_t} Len         参数长度
 * @return {*}
 */
void LCD_WR_CMD(uint8_t *CMD, uint8_t Len)
{

    LCD_DC_Clr();

    HAL_SPI_Transmit(&hspi1, (uint8_t *)&CMD[0], 1, 0Xff);

    LCD_DC_Set();

    if (Len <= 1)
    {
        return;
    }
    else
    {
        HAL_SPI_Transmit(&hspi1, &CMD[1], (Len - 1), 0Xff);
    }
}

/**
 * @brief LCD初始化工作
 * @param {*}
 * @return {*}
 */
void LCD_Init(void)
{

    LCD_RES_Clr(); //复位
    HAL_Delay(100);
    LCD_RES_Set();
    HAL_Delay(100);
    LCD_BLK_Set(); //打开背光
    HAL_Delay(100);

    LCD_WR_CMD(Set_Sleep_Out_CMD, sizeof(Set_Sleep_Out_CMD));
    HAL_Delay(120); // Delay 120ms

    LCD_WR_CMD(Set_Frame_Rate_CMD0, sizeof(Set_Frame_Rate_CMD0));
    LCD_WR_CMD(Set_Frame_Rate_CMD1, sizeof(Set_Frame_Rate_CMD1));
    LCD_WR_CMD(Set_Frame_Rate_CMD2, sizeof(Set_Frame_Rate_CMD2));

    LCD_WR_CMD(Set_Display_Inversion_CMD, sizeof(Set_Display_Inversion_CMD));

    LCD_WR_CMD(Set_Power_Sequence_CMD0, sizeof(Set_Power_Sequence_CMD0));
    LCD_WR_CMD(Set_Power_Sequence_CMD1, sizeof(Set_Power_Sequence_CMD1));
    LCD_WR_CMD(Set_Power_Sequence_CMD2, sizeof(Set_Power_Sequence_CMD2));
    LCD_WR_CMD(Set_Power_Sequence_CMD3, sizeof(Set_Power_Sequence_CMD3));
    LCD_WR_CMD(Set_Power_Sequence_CMD4, sizeof(Set_Power_Sequence_CMD4));

    LCD_WR_CMD(Set_VCOM_CMD, sizeof(Set_VCOM_CMD));

    LCD_WR_CMD(Set_Memory_Data_Access_CMD, sizeof(Set_Memory_Data_Access_CMD));

    LCD_WR_CMD(Set_Gamma_Sequence_CMD0, sizeof(Set_Gamma_Sequence_CMD0));
    LCD_WR_CMD(Set_Gamma_Sequence_CMD1, sizeof(Set_Gamma_Sequence_CMD1));

    LCD_WR_CMD(Set_Interface_Pixel_CMD, sizeof(Set_Interface_Pixel_CMD));

    LCD_WR_CMD(Set_Display_on_CMD, sizeof(Set_Display_on_CMD));


}

/**
 * @brief 清除对应区域显示
 * @param {uint16_t} x_start
 * @param {uint16_t} y_start
 * @param {uint16_t} x_end
 * @param {uint16_t} y_end
 * @return {*}
 */
void LCD_Clear(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end)
{
    LCD_WR_REG(0x2a);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(x_start);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(x_end);

    LCD_WR_REG(0x2b);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(y_start);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(y_end);

    LCD_WR_REG(0x2c);
}

/**
 * @brief 设置SPI传输数据长度16位
 * @param {*}
 * @return {*}
 */
void Set_SPI_DATASIZE_16BIT(void)
{

    SPI1->CFG1 &= ~(0x0000001f); //置0

    SPI1->CFG1 |= SPI_DATASIZE_16BIT; //再赋值

    hspi1.Init.DataSize = SPI_DATASIZE_16BIT; // 此处赋值为了正确使用HAL_SPI_Transmit() 函数
}

/**
 * @brief 设置SPI传输数据长度8位
 * @param {*}
 * @return {*}
 */
void Set_SPI_DATASIZE_8BIT(void)
{

    SPI1->CFG1 &= ~(0x0000001f); //置0

    SPI1->CFG1 |= SPI_DATASIZE_8BIT; //再赋值

    hspi1.Init.DataSize = SPI_DATASIZE_8BIT; //(0x00000007UL)
}





/**
 * @brief 设置写入地址
 * @param {uint16_t} x1
 * @param {uint16_t} y1
 * @param {uint16_t} x2
 * @param {uint16_t} y2
 * @return {*}
 */
void User_LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    uint8_t CMD = 0X2A;
    uint16_t Data[2];

    LCD_DC_Clr(); //写命令
    Set_SPI_DATASIZE_8BIT();
    HAL_SPI_Transmit(&hspi1, &CMD, 1, 0Xff);
    LCD_DC_Set(); //写数据

    Set_SPI_DATASIZE_16BIT();
    Data[0] = x1 + 3;
    Data[1] = x2 + 3;
    HAL_SPI_Transmit(&hspi1, (uint8_t *)Data, 2, 0Xff);

    CMD = 0x2b;
    LCD_DC_Clr(); //写命令
    Set_SPI_DATASIZE_8BIT();
    HAL_SPI_Transmit(&hspi1, &CMD, 1, 0Xff);
    LCD_DC_Set(); //写数据

    Set_SPI_DATASIZE_16BIT();
    Data[0] = y1 + 2;
    Data[1] = y2 + 2;
    HAL_SPI_Transmit(&hspi1, (uint8_t *)&Data, 2, 0Xff);

    CMD = 0x2c;
    LCD_DC_Clr(); //写命令
    Set_SPI_DATASIZE_8BIT();
    HAL_SPI_Transmit(&hspi1, &CMD, 1, 0Xff);
    LCD_DC_Set(); //写数据
}


/**
 * @brief 刷新图片
 * @param {uint8_t} pic   存放图片的数组
 * @param {uint32_t} len        数组长度
 * @return {*}
 */
void User_LCD_ShowPicture(const uint8_t pic[], uint32_t len)
{
    User_LCD_Address_Set(0,0,127,127);
    Set_SPI_DATASIZE_8BIT();
    HAL_SPI_Transmit_DMA(&hspi1, (uint8_t *)pic, len);
	  
}





uint8_t Images_Fish_Flag = 1;


extern DMA_HandleTypeDef hdma_spi1_tx;
extern TIM_HandleTypeDef htim15;

void Demo_Images_Show(void)
{
   memcpy(LCD_Buffer0 , gImage_1 , BUFFER_LEN);
	
	 User_LCD_ShowPicture(LCD_Buffer0, BUFFER_LEN);
	
	
   // memcpy(LCD_Buffer1 , gImage_2 , BUFFER_LEN);
 /*  
    while (1)
    {
        while (HAL_DMA_GetState(&hdma_spi1_tx) != HAL_DMA_STATE_READY);	
				
			  memset(LCD_Buffer0 , 0 , BUFFER_LEN);	
			        switch (gImage_count)
        {
        case 1:
            
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS , BUFFER_LEN);
				break;

				case 2:
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN , BUFFER_LEN);
				break;
				case 3:
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 2 , BUFFER_LEN);
				break;
				case 4 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 3  , BUFFER_LEN);
				break;
				case 5 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN *  4 , BUFFER_LEN);
				break;
				case 6 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 5  , BUFFER_LEN);
				break;
				case 7 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 6  , BUFFER_LEN);
				break;
				case 8 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 7  , BUFFER_LEN);
				break;
				case 9 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 8  , BUFFER_LEN);
				break;			
				case 10 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 9  , BUFFER_LEN);
				break;
				case 11 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 10  , BUFFER_LEN);
				break;
				case 12 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 11  , BUFFER_LEN);
				break;
				case 13 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 12  , BUFFER_LEN);
				break;
				case 14 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 13  , BUFFER_LEN);
				break;
				case 15 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 14  , BUFFER_LEN);
				break;
				case 16 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 15  , BUFFER_LEN);
				break;
				case 17 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 16  , BUFFER_LEN);
				break;
				case 18 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 17  , BUFFER_LEN);
				break;
				case 19 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 18  , BUFFER_LEN);
				break;
				case 20 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 19  , BUFFER_LEN);
				break;
				case 21 :
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 20  , BUFFER_LEN);
				break;									
				case  22:
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 21  , BUFFER_LEN);
				break;
				case  23:
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 22  , BUFFER_LEN);
				break;
				case  24:
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 23  , BUFFER_LEN);
				break;
				case  25:
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 24  , BUFFER_LEN);
				break;
				case  26:
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 25  , BUFFER_LEN);
				break;
				case  27:
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 26  , BUFFER_LEN);
				break;	
				case  28:
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 27  , BUFFER_LEN);
				break;
				case  29:
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 28  , BUFFER_LEN);
				break;
				case  30:
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 29  , BUFFER_LEN);
				break;
				case  31:
				QSPI_W25Qx_Read_Buffer(LCD_Buffer0 , FLASH_BEGIN_ADDRESS + BUFFER_LEN * 30  , BUFFER_LEN);
				break;
				      			
        default:
            break;
        }
				
				User_LCD_ShowPicture(LCD_Buffer0, BUFFER_LEN);
				
				//HAL_Delay(100);
				
        FPS_Tick++;

        gImage_count++;

        if (gImage_count > 31)
        {
            gImage_count = 2;
        }
				
				
    }
		*/
}



/**
 * @brief 发送完成中断回调函数
 * @param {SPI_HandleTypeDef} *hspi
 * @return {*}
 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
}

/**
 * @brief 定时器中断回调函数
 * @param {TIM_HandleTypeDef} *htim
 * @return {*}
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM15)
    {
     
    }
}
