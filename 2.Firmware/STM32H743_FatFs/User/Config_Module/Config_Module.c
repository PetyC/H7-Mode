/*
 * @Description:AT指令阻塞版本
 * @Autor: Pi
 * @Date: 2022-04-19 17:14:34
 * @LastEditTime: 2022-04-27 16:32:03
 */

#include "Config_Module.h"
#include "Dev_Uart.h"


uint32_t ConfigModuleBlockDelay = 0;


char Config_Module_Buf[500];
/**
 * @brief  发送指令配置模块,阻塞版
 * @param  dat:      发送的数据
 * @param  returnc:  预期返回的数据1
 * @param  returncc: 预期返回的数据2
 * @retval 0:配置当前指令OK
 * @example
 **/
uint8_t Config_Module_Block(char *Dat, uint8_t Dat_Len , char *returnc, char *returncc)
{
	
	static uint8_t ConfigModuleBlockCnt = 0;

	uint8_t ConfigModuleBlockFlage = 1;

	static uint32_t Delay_Tick = 0;

	while (1)
	{
		if (ConfigModuleBlockFlage == 1) //发送指令
		{
			ConfigModuleBlockDelay = 0;

			memset(Config_Module_Buf, NULL, sizeof(Config_Module_Buf)); 							//清零,把自己的串口接收数组放在这里清零
			
			ConfigModuleBlockFlage = 0;

			/*发送指令*/
			HAL_UART_Transmit(&huart1 , (uint8_t *)Dat , Dat_Len , 0x500);

			Delay_Tick = HAL_GetTick();
		}
		
		if ( User_UART_Get_RX_Flag(&huart1) == 0) //串口接收到一条完整的数据
		{

			User_UART_Read(&huart1 , (uint8_t *)Config_Module_Buf , 500);
			
			if (returnc != NULL && strstr(Config_Module_Buf, returnc)) //比较数据
			{
				return 0;
			}
			if (returncc != NULL && strstr(Config_Module_Buf, returncc)) //比较数据
			{	
				return 0;
			}

		}


		if((HAL_GetTick() - Delay_Tick) > 5000 )		//超过5秒
		{
			Delay_Tick = 0;
			ConfigModuleBlockFlage = 1; //允许发送数据
			ConfigModuleBlockCnt++;
		}

		if (ConfigModuleBlockCnt >= 3) //超过三次继续发送下一条
		{
			ConfigModuleBlockCnt = 0;
			return 1;
		}


	}
	


}


/*AT命令流程*/
typedef enum 
{
	Send,
	Wait,
	Receive,
	Out_Time,
}Config_Process_En; 

Config_Process_En Config_Process;

/*ESP8266接收缓存*/
#define CONFIG_BUFFER_LEN	1500
uint8_t Config_Buffer[CONFIG_BUFFER_LEN];


uint8_t Config_Module(uint8_t *Send_Data , uint8_t Send_Data_Len , uint8_t *returnc)
{
	/*实际接收到的数据长度*/
	uint16_t Reality_Size = 0;
	static uint32_t Out_Time_Tick = 0;
	while(1)
	{
		switch (Config_Process)
		{
			/*发送指令*/
			case Send:
				HAL_UART_Transmit(&huart1 , Send_Data , Send_Data_Len , 0x500);
				Config_Process = Wait;

				/*更新超时计数*/
				Out_Time_Tick = HAL_GetTick();

			break;
			
			/*等待接收到指令*/
			case Wait:
				if( User_UART_Get_RX_Flag(&huart1) != 0)
				{
					/*超时超过5秒*/
					if((HAL_GetTick() - Out_Time_Tick) > 5000 )		
					{
						Config_Process = Out_Time;
					}
				
					break;
				}

				/*读出返回数据*/
				Reality_Size = User_UART_Read(&huart1 , Config_Buffer , CONFIG_BUFFER_LEN);

				/*判断是否返回期待数据*/
				if(strstr((char *)Config_Buffer, (char *)returnc))
				{
					/*接收到数据*/
					Config_Process = Receive;
				}

			
			break;

			/*接收到指令*/
			case Receive:
				return 0;


			/*超时*/
			case Out_Time:
				return 1;


			default:

			break;
		}
	}


}
