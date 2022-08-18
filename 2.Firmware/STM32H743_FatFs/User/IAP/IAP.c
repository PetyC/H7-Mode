/*
 * @Description: IAP升级程序 适用于F103系列 
 * @Autor: Pi
 * @Date: 2022-04-19 20:54:24
 * @LastEditTime: 2022-04-25 03:10:12
 */

#include "iap.h"

iapfun jump2app; 


//addr:栈顶地址
__asm void MSR_MSP(uint32_t addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}

//跳转到应用程序段
//appxaddr:用户代码起始地址.
void iap_load_app(uint32_t appxaddr)
{
	if(((*(__IO uint32_t*)appxaddr)&0x2FFE0000)==0x20000000)	//检查栈顶地址是否合法.
	{ 
		jump2app=(iapfun)*(__IO uint32_t*)(appxaddr+4);		//拷贝APP程序的复位中断函数地址
		MSR_MSP(*(__IO uint32_t*)appxaddr);					//初始化APP堆栈指针,对APP程序的堆栈进行重构,就是说重新分配RAM
		jump2app();									//执行APP的复位中断函数,最终便会跳转到APP的main函数
	}
}		 


/*复位芯片*/
void Reset_MCU(void)
{
  __disable_fault_irq();   
	NVIC_SystemReset();
}
