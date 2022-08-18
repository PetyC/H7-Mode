/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "LCD_Task.h"
#include "KEY_Task.h"
#include "Network_Task.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId KEY_TaskHandle;
osThreadId LCD_TaskHandle;
osThreadId Network_TaskHandle;
osMutexId Uart_MutexHandle;
osSemaphoreId Key_Binary_SemHandle;
osSemaphoreId Network_BinarySemHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void Start_KEY_Task(void const * argument);
void Start_LCD_Task(void const * argument);
void Start_Network_Task(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* Hook prototypes */
void configureTimerForRunTimeStats(void);
unsigned long getRunTimeCounterValue(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 1 */
/* Functions needed when configGENERATE_RUN_TIME_STATS is on */
#if (configGENERATE_RUN_TIME_STATS == 1)
volatile uint32_t ulHighFrequencyTimerTicks;
#endif

__weak void configureTimerForRunTimeStats(void)
{
#if (configGENERATE_RUN_TIME_STATS == 1)
  ulHighFrequencyTimerTicks = 0;
#endif
}

__weak unsigned long getRunTimeCounterValue(void)
{
#if (configGENERATE_RUN_TIME_STATS == 1)
  return ulHighFrequencyTimerTicks;
#else
  return 0;
#endif
}
/* USER CODE END 1 */

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
  /* Run time stack overflow checking is performed if
  configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
  called if a stack overflow is detected. */

  uint8_t Buff[50] = "Task:";
  strcat((char *)Buff, (char *)pcTaskName);
  strcat((char *)Buff, " Stack is overflow!\r\n");

  Bsp_UART_Write(&huart1, Buff, sizeof(Buff));
  Bsp_UART_Poll_DMA_TX(&huart1);
}
/* USER CODE END 4 */

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory(StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize)
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* definition and creation of Uart_Mutex */
  osMutexDef(Uart_Mutex);
  Uart_MutexHandle = osMutexCreate(osMutex(Uart_Mutex));

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of Key_Binary_Sem */
  osSemaphoreDef(Key_Binary_Sem);
  Key_Binary_SemHandle = osSemaphoreCreate(osSemaphore(Key_Binary_Sem), 1);

  /* definition and creation of Network_BinarySem */
  osSemaphoreDef(Network_BinarySem);
  Network_BinarySemHandle = osSemaphoreCreate(osSemaphore(Network_BinarySem), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of KEY_Task */
  osThreadDef(KEY_Task, Start_KEY_Task, osPriorityAboveNormal, 0, 256);
  KEY_TaskHandle = osThreadCreate(osThread(KEY_Task), NULL);

  /* definition and creation of LCD_Task */
  osThreadDef(LCD_Task, Start_LCD_Task, osPriorityNormal, 0, 256);
  LCD_TaskHandle = osThreadCreate(osThread(LCD_Task), NULL);

  /* definition and creation of Network_Task */
  osThreadDef(Network_Task, Start_Network_Task, osPriorityIdle, 0, 512);
  Network_TaskHandle = osThreadCreate(osThread(Network_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */

  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for (;;)
  {
    HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
    osDelay(800);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_Start_KEY_Task */
/**
 * @brief Function implementing the KEY_Task thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_Start_KEY_Task */
void Start_KEY_Task(void const * argument)
{
  /* USER CODE BEGIN Start_KEY_Task */
 
  /* Infinite loop */
  KEY_Task(argument);

  /* USER CODE END Start_KEY_Task */
}

/* USER CODE BEGIN Header_Start_LCD_Task */
/**
* @brief Function implementing the LCD_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_LCD_Task */
void Start_LCD_Task(void const * argument)
{
  /* USER CODE BEGIN Start_LCD_Task */

  /* Infinite loop */
  LCD_Task(argument);
  
  /* USER CODE END Start_LCD_Task */
}

/* USER CODE BEGIN Header_Start_Network_Task */
/**
* @brief Function implementing the Network_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Start_Network_Task */
void Start_Network_Task(void const * argument)
{
  /* USER CODE BEGIN Start_Network_Task */
  /* Infinite loop */
    Network_Task(argument);
  /* USER CODE END Start_Network_Task */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
