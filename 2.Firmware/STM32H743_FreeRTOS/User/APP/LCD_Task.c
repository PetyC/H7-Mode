/*
 * @Description: LCD显示任务
 * @Autor: Pi
 * @Date: 2022-06-27 15:14:05
 * @LastEditTime: 2022-08-24 02:04:36
 */
#include "LCD_Task.h"
#include "stdio.h"

/*FreeRTOS相关变量*/
extern osSemaphoreId Key_Binary_SemHandle;
extern osSemaphoreId LCD_BinarySemHandle;

/**
 * @brief LCD任务
 * @param {void*} argument
 * @return {*}
 */
void LCD_Task(void const *argument)
{
  /*初始值为1，防止未阻塞运行*/
  osSemaphoreWait(LCD_BinarySemHandle, osWaitForever);
  
  lv_init();
  lv_port_disp_init();
  
  lv_demo_benchmark();
  //lv_ui guider_ui;
  
  //setup_ui(&guider_ui);
  //events_init(&guider_ui);

  /* Infinite loop */
  for (;;)
  {
    
    lv_task_handler();
    osDelay(1);
  }
}



///**
// * @brief 显示任务相关状态
// * @return {*}
// */
//static void LCD_Task_Display(uint8_t Type)
//{

//  uint32_t ulTotalRunTime;
//  char LCD_Buffer[20];

//  /*获取任务数量*/
//  volatile UBaseType_t uxArraySize = uxTaskGetNumberOfTasks();

//  /*为每个任务分配一个TaskStatus_t结构*/
//  TaskStatus_t *pxTaskStatusArray = pvPortMalloc(uxArraySize * sizeof(TaskStatus_t));

//  /*任务分配失败*/
//  if (pxTaskStatusArray == NULL)
//  {
//    return;
//  }

//  /*生成有关每个任务的原始状态信息*/
//  uxArraySize = uxTaskGetSystemState(pxTaskStatusArray, uxArraySize, &ulTotalRunTime);

//  /*LCD显示*/
//  setColor(0, 0xff, 00);
//  setbgColor(0, 0, 0);
//  setFont(ter_u12b);

//  static uint8_t Type_Last;
//  
//  /*非同一页面*/
//  if (Type != Type_Last)
//  {
//    setColor(0, 0, 0);
//    fillScreen();
//    Type_Last = Type;
//  }

//  setColor(0, 0xff, 00);

//  for (uint8_t x = 0; x < uxArraySize; x++)
//  {

//    /*显示任务*/
//    Task_Name_Handle(LCD_Buffer, pxTaskStatusArray[x].pcTaskName);
//    drawText(0, 12 + x * 12, LCD_Buffer);
//    memset(LCD_Buffer, 0, sizeof(LCD_Buffer));

//    switch (Type)
//    {
//    case 0:
//      /*显示CPU占用率*/
//      Task_CPU_Handle(LCD_Buffer, pxTaskStatusArray[x].ulRunTimeCounter, ulTotalRunTime);
//      drawText(0, 0, "name             Use");
//      drawText(102, 12 + x * 12, LCD_Buffer);
//      break;
//    case 1:
//      /*显示任务状态*/
//      Task_Current_Handle(LCD_Buffer, pxTaskStatusArray[x].eCurrentState);
//      drawText(0, 0, "name           State");
//      drawText(108, 12 + x * 12, LCD_Buffer);
//      break;
//    case 2:
//      /*显示任务水位线*/
//      sprintf(LCD_Buffer, "%-3d", pxTaskStatusArray[x].usStackHighWaterMark);
//      drawText(0, 0, "name          Stack");
//      drawText(102, 12 + x * 12, LCD_Buffer);
//      break;
//    case 3:
//      /*显示任务优先级*/
//      sprintf(LCD_Buffer, "%-2d", pxTaskStatusArray[x].uxCurrentPriority);
//      drawText(0, 0, "name             Pir");
//      drawText(102, 12 + x * 12, LCD_Buffer);
//      break;

//    default:
//      break;
//    }

//    flushBuffer();
//  }

//  /*释放内存*/
//  vPortFree(pxTaskStatusArray);
//}

///**
// * @brief 任务名格式处理函数
// * @param {char} *Name_Buff
// * @param {char} *Get_Name
// * @return {*}
// */
//static void Task_Name_Handle(char *Name_Buff, const char *pcTaskName)
//{
//  /*显示任务*/
//  sprintf(Name_Buff, "%-16s", pcTaskName);

//  /*替换下划线'-'*/
//  char *ret = strchr(Name_Buff, '_');
//  if (ret != NULL)
//  {
//    *ret = ' ';
//  }
//}

///**
// * @brief CPU占用率
// * @param {char} *CPU_Buff
// * @param {uint32_t} RunTimeCounter
// * @param {uint32_t} ulTotalRunTime
// * @return {*}
// */
//static void Task_CPU_Handle(char *CPU_Buff, const uint32_t RunTimeCounter, uint32_t ulTotalRunTime)
//{
//  ulTotalRunTime /= 100UL;

//  if (ulTotalRunTime <= 0)
//  {
//    return;
//  }

//  /* 任务使用了总运行时间的百分之几？这将始终向下舍入到最接近的整数。ulTotalRunTimeDiv100 已经除以 100。 */
//  uint32_t ulStatsAsPercentage = RunTimeCounter / ulTotalRunTime;

//  //显示CPU使用情况
//  if (ulStatsAsPercentage > 0UL)
//  {
//    sprintf(CPU_Buff, "%d%% ", ulStatsAsPercentage);
//  }
//  else
//  {
//    sprintf(CPU_Buff, "<1%% ");
//  }
//}

///**
// * @brief 任务状态名称处理
// * @param {char} *CurrentState_Buff
// * @param {eTaskState } eCurrentState
// * @return {*}
// */
//static void Task_Current_Handle(char *CurrentState_Buff, eTaskState eCurrentState)
//{
//  char Task_State;

//  switch (eCurrentState)
//  {
//  case eRunning:
//    Task_State = 'X';
//    break;

//  case eReady:
//    Task_State = 'R';
//    break;

//  case eBlocked:
//    Task_State = 'B';
//    break;

//  case eSuspended:
//    Task_State = 'S';
//    break;

//  case eDeleted:
//    Task_State = 'D';
//    break;

//  case eInvalid:
//  default:
//    break;
//  }

//  /*显示任务*/
//  sprintf(CurrentState_Buff, "%c", Task_State);
//}



