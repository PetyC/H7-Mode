/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-09-10 04:30:49
 * @LastEditTime: 2022-09-13 14:21:46
 */
#include "USB_Task.h"

#include "rl_usb.h"

	
osThreadId_t USB_TaskHandle;
const osThreadAttr_t USBTask_attributes = {
    .name = "USB_Task",
    .stack_size = 1024 * 2,
    .priority = (osPriority_t)osPriorityNormal3,
    .attr_bits = osThreadDetached,
};


/**
 * @brief USB任务
 * @param {void} *argument
 * @return {*}
 */
void USB_Task(void *argument)
{
	/*USB Drivers*/
	USBD_Initialize(0U);                 
	USBD_Connect   (0U); 
	
	for(;;)
	{
		osDelay(800);
	};
		
}