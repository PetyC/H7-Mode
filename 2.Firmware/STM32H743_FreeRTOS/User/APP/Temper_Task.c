/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-08-27 22:05:04
 * @LastEditTime: 2022-08-27 22:19:11
 */
#include "Temper_Task.h"

/*Freertos相关*/
extern osMessageQId Temper_QueueHandle;

/*HAL相关*/
extern ADC_HandleTypeDef hadc3;


void Temper_Task(void const * argument)
{
  HAL_ADCEx_Calibration_Start(&hadc3 , ADC_CALIB_OFFSET,ADC_SINGLE_ENDED);//校准ADC 
  osDelay(10);
 
  HAL_ADC_Start_IT(&hadc3);	//启动ADC转换

  vTaskDelete(NULL);    //删除本任务
 
  for(;;)
  {
    osDelay(10);
  }
}

 
/**
 * @brief ADC转换完成中断
 * @param {ADC_HandleTypeDef} *hadc
 * @return {*}
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
  uint16_t TS_CAL1 = 0;
  uint16_t TS_CAL2 = 0;
  uint16_t mpu_temp = 0;

  /*读取ADC转换数据（16位数据）*/
  TS_CAL1 = *(__IO uint16_t *)(0x1FF1E820);
  TS_CAL2 = *(__IO uint16_t *)(0x1FF1E840);
  mpu_temp = HAL_ADC_GetValue(&hadc3);	
  mpu_temp = ((110.0f - 30.0f) / (TS_CAL2 - TS_CAL1)) * (mpu_temp - TS_CAL1) + 30.0f;

  /*塞入队列*/
  osMessagePut(Temper_QueueHandle , mpu_temp , 0);

  HAL_ADC_Start_IT(&hadc3);	
}
