/*
 * @Description: 
 * @Autor: Pi
 * @Date: 2022-10-12 15:13:14
 * @LastEditTime: 2022-10-12 16:07:50
 */
#include "Demo.h"


void Demo()
{
  System_Config_Init();

  System_Config config = System_Config_Get();

  if(config.Updata == 0)
  {
    IAP_App_Jump_Start();
  }

  uint8_t Error = 1;
  /*备份APP*/
  Error = IAP_App_Backup();

  if(Error == 1)
  {
    config.Error = 1;
    IAP_App_Jump_Start();
  }

  /*更新APP*/
  Error = IAP_App_Updata();

  if(Error == 1)
  {
    config.Error = 1;
    
  }
}