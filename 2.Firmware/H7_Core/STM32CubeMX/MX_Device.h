/******************************************************************************
 * File Name   : MX_Device.h
 * Date        : 20/05/2023 01:02:37
 * Description : STM32Cube MX parameter definitions
 * Note        : This file is generated by STM32CubeMX (DO NOT EDIT!)
 ******************************************************************************/

#ifndef __MX_DEVICE_H
#define __MX_DEVICE_H

/*---------------------------- Clock Configuration ---------------------------*/

#define MX_LSI_VALUE                            32000
#define MX_LSE_VALUE                            32768
#define MX_HSI_VALUE                            64000000
#define MX_HSE_VALUE                            25000000
#define MX_EXTERNAL_CLOCK_VALUE                 12288000
#define MX_PLLDSIFreq_Value                     500000000
#define MX_SYSCLKFreq_VALUE                     400000000
#define MX_HCLKFreq_Value                       200000000
#define MX_CortexFreq_Value                     400000000
#define MX_APB1Freq_Value                       100000000
#define MX_APB2Freq_Value                       100000000
#define MX_CECFreq_Value                        32000
#define MX_RTCFreq_Value                        32000
#define MX_USBFreq_Value                        48000000
#define MX_WatchDogFreq_Value                   32000
#define MX_DSIFreq_Value                        96000000
#define MX_DSIPHYCLKFreq_Value                  96000000
#define MX_DSITXEscFreq_Value                   20000000
#define MX_SPDIFRXFreq_Value                    400000000
#define MX_MCO1PinFreq_Value                    64000000
#define MX_MCO2PinFreq_Value                    400000000

/*-------------------------------- CORTEX_M7  --------------------------------*/

#define MX_CORTEX_M7                            1

/* GPIO Configuration */

/*-------------------------------- CRC        --------------------------------*/

#define MX_CRC                                  1

/* GPIO Configuration */

/*-------------------------------- DEBUG      --------------------------------*/

#define MX_DEBUG                                1

/* GPIO Configuration */

/* Pin PA14 (JTCK/SWCLK) */
#define MX_DEBUG_JTCK_SWCLK_Pin                 PA14_JTCK_SWCLK

/* Pin PA13 (JTMS/SWDIO) */
#define MX_DEBUG_JTMS_SWDIO_Pin                 PA13_JTMS_SWDIO

/*-------------------------------- DMA        --------------------------------*/

#define MX_DMA                                  1

/* NVIC Configuration */

/* NVIC DMA1_Stream1_IRQn */
#define MX_DMA1_Stream1_IRQn_interruptPremptionPriority 0
#define MX_DMA1_Stream1_IRQn_PriorityGroup      NVIC_PRIORITYGROUP_4
#define MX_DMA1_Stream1_IRQn_Subriority         0

/* NVIC DMA1_Stream2_IRQn */
#define MX_DMA1_Stream2_IRQn_interruptPremptionPriority 0
#define MX_DMA1_Stream2_IRQn_PriorityGroup      NVIC_PRIORITYGROUP_4
#define MX_DMA1_Stream2_IRQn_Subriority         0

/* NVIC DMA1_Stream0_IRQn */
#define MX_DMA1_Stream0_IRQn_interruptPremptionPriority 0
#define MX_DMA1_Stream0_IRQn_PriorityGroup      NVIC_PRIORITYGROUP_4
#define MX_DMA1_Stream0_IRQn_Subriority         0

/*-------------------------------- DMA        --------------------------------*/

#define MX_DMA                                  1

/* NVIC Configuration */

/* NVIC DMA1_Stream1_IRQn */
#define MX_DMA1_Stream1_IRQn_interruptPremptionPriority 0
#define MX_DMA1_Stream1_IRQn_PriorityGroup      NVIC_PRIORITYGROUP_4
#define MX_DMA1_Stream1_IRQn_Subriority         0

/* NVIC DMA1_Stream2_IRQn */
#define MX_DMA1_Stream2_IRQn_interruptPremptionPriority 0
#define MX_DMA1_Stream2_IRQn_PriorityGroup      NVIC_PRIORITYGROUP_4
#define MX_DMA1_Stream2_IRQn_Subriority         0

/* NVIC DMA1_Stream0_IRQn */
#define MX_DMA1_Stream0_IRQn_interruptPremptionPriority 0
#define MX_DMA1_Stream0_IRQn_PriorityGroup      NVIC_PRIORITYGROUP_4
#define MX_DMA1_Stream0_IRQn_Subriority         0

/*-------------------------------- FMC        --------------------------------*/

#define MX_FMC                                  1

/* GPIO Configuration */

/* Pin PD14 */
#define MX_FMC_D0_DA0_Pin                       PD14
#define MX_FMC_D0_DA0_GPIOx                     GPIOD
#define MX_FMC_D0_DA0_GPIO_PuPd                 GPIO_NOPULL
#define MX_FMC_D0_DA0_GPIO_Speed_High_Default   GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_D0_DA0_GPIO_Pin                  GPIO_PIN_14
#define MX_FMC_D0_DA0_GPIO_AF                   GPIO_AF12_FMC
#define MX_FMC_D0_DA0_GPIO_Mode                 GPIO_MODE_AF_PP

/* Pin PD12 */
#define MX_FMC_A17_ALE_Pin                      PD12
#define MX_FMC_A17_ALE_GPIOx                    GPIOD
#define MX_FMC_A17_ALE_GPIO_PuPd                GPIO_NOPULL
#define MX_FMC_A17_ALE_GPIO_Speed_High_Default  GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_A17_ALE_GPIO_Pin                 GPIO_PIN_12
#define MX_FMC_A17_ALE_GPIO_Mode                GPIO_MODE_AF_PP

/* Pin PD6 */
#define MX_FMC_NWAIT_Pin                        PD6
#define MX_FMC_NWAIT_GPIOx                      GPIOD
#define MX_FMC_NWAIT_GPIO_PuPd                  GPIO_PULLUP
#define MX_FMC_NWAIT_GPIO_Speed_High_Default    GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_NWAIT_GPIO_Pin                   GPIO_PIN_6
#define MX_FMC_NWAIT_GPIO_AF                    GPIO_AF12_FMC
#define MX_FMC_NWAIT_GPIO_Mode                  GPIO_MODE_AF_PP

/* Pin PE8 */
#define MX_FMC_D5_DA5_Pin                       PE8
#define MX_FMC_D5_DA5_GPIOx                     GPIOE
#define MX_FMC_D5_DA5_GPIO_PuPd                 GPIO_NOPULL
#define MX_FMC_D5_DA5_GPIO_Speed_High_Default   GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_D5_DA5_GPIO_Pin                  GPIO_PIN_8
#define MX_FMC_D5_DA5_GPIO_AF                   GPIO_AF12_FMC
#define MX_FMC_D5_DA5_GPIO_Mode                 GPIO_MODE_AF_PP

/* Pin PD1 */
#define MX_FMC_D3_DA3_Pin                       PD1
#define MX_FMC_D3_DA3_GPIOx                     GPIOD
#define MX_FMC_D3_DA3_GPIO_PuPd                 GPIO_NOPULL
#define MX_FMC_D3_DA3_GPIO_Speed_High_Default   GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_D3_DA3_GPIO_Pin                  GPIO_PIN_1
#define MX_FMC_D3_DA3_GPIO_AF                   GPIO_AF12_FMC
#define MX_FMC_D3_DA3_GPIO_Mode                 GPIO_MODE_AF_PP

/* Pin PD5 */
#define MX_FMC_NWE_Pin                          PD5
#define MX_FMC_NWE_GPIOx                        GPIOD
#define MX_FMC_NWE_GPIO_PuPd                    GPIO_NOPULL
#define MX_FMC_NWE_GPIO_Speed_High_Default      GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_NWE_GPIO_Pin                     GPIO_PIN_5
#define MX_FMC_NWE_GPIO_AF                      GPIO_AF12_FMC
#define MX_FMC_NWE_GPIO_Mode                    GPIO_MODE_AF_PP

/* Pin PE7 */
#define MX_FMC_D4_DA4_Pin                       PE7
#define MX_FMC_D4_DA4_GPIOx                     GPIOE
#define MX_FMC_D4_DA4_GPIO_PuPd                 GPIO_NOPULL
#define MX_FMC_D4_DA4_GPIO_Speed_High_Default   GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_D4_DA4_GPIO_Pin                  GPIO_PIN_7
#define MX_FMC_D4_DA4_GPIO_AF                   GPIO_AF12_FMC
#define MX_FMC_D4_DA4_GPIO_Mode                 GPIO_MODE_AF_PP

/* Pin PD11 */
#define MX_FMC_A16_CLE_Pin                      PD11
#define MX_FMC_A16_CLE_GPIOx                    GPIOD
#define MX_FMC_A16_CLE_GPIO_PuPd                GPIO_NOPULL
#define MX_FMC_A16_CLE_GPIO_Speed_High_Default  GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_A16_CLE_GPIO_Pin                 GPIO_PIN_11
#define MX_FMC_A16_CLE_GPIO_Mode                GPIO_MODE_AF_PP

/* Pin PE10 */
#define MX_FMC_D7_DA7_Pin                       PE10
#define MX_FMC_D7_DA7_GPIOx                     GPIOE
#define MX_FMC_D7_DA7_GPIO_PuPd                 GPIO_NOPULL
#define MX_FMC_D7_DA7_GPIO_Speed_High_Default   GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_D7_DA7_GPIO_Pin                  GPIO_PIN_10
#define MX_FMC_D7_DA7_GPIO_AF                   GPIO_AF12_FMC
#define MX_FMC_D7_DA7_GPIO_Mode                 GPIO_MODE_AF_PP

/* Pin PD15 */
#define MX_FMC_D1_DA1_Pin                       PD15
#define MX_FMC_D1_DA1_GPIOx                     GPIOD
#define MX_FMC_D1_DA1_GPIO_PuPd                 GPIO_NOPULL
#define MX_FMC_D1_DA1_GPIO_Speed_High_Default   GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_D1_DA1_GPIO_Pin                  GPIO_PIN_15
#define MX_FMC_D1_DA1_GPIO_AF                   GPIO_AF12_FMC
#define MX_FMC_D1_DA1_GPIO_Mode                 GPIO_MODE_AF_PP

/* Pin PD4 */
#define MX_FMC_NOE_Pin                          PD4
#define MX_FMC_NOE_GPIOx                        GPIOD
#define MX_FMC_NOE_GPIO_PuPd                    GPIO_NOPULL
#define MX_FMC_NOE_GPIO_Speed_High_Default      GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_NOE_GPIO_Pin                     GPIO_PIN_4
#define MX_FMC_NOE_GPIO_AF                      GPIO_AF12_FMC
#define MX_FMC_NOE_GPIO_Mode                    GPIO_MODE_AF_PP

/* Pin PE9 */
#define MX_FMC_D6_DA6_Pin                       PE9
#define MX_FMC_D6_DA6_GPIOx                     GPIOE
#define MX_FMC_D6_DA6_GPIO_PuPd                 GPIO_NOPULL
#define MX_FMC_D6_DA6_GPIO_Speed_High_Default   GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_D6_DA6_GPIO_Pin                  GPIO_PIN_9
#define MX_FMC_D6_DA6_GPIO_AF                   GPIO_AF12_FMC
#define MX_FMC_D6_DA6_GPIO_Mode                 GPIO_MODE_AF_PP

/* Pin PC8 */
#define MX_FMC_NCE_Pin                          PC8
#define MX_FMC_NCE_GPIOx                        GPIOC
#define MX_FMC_NCE_GPIO_PuPd                    GPIO_NOPULL
#define MX_FMC_NCE_GPIO_Speed_High_Default      GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_NCE_GPIO_Pin                     GPIO_PIN_8
#define MX_FMC_NCE_GPIO_AF                      GPIO_AF9_FMC
#define MX_FMC_NCE_GPIO_Mode                    GPIO_MODE_AF_PP

/* Pin PD0 */
#define MX_FMC_D2_DA2_Pin                       PD0
#define MX_FMC_D2_DA2_GPIOx                     GPIOD
#define MX_FMC_D2_DA2_GPIO_PuPd                 GPIO_NOPULL
#define MX_FMC_D2_DA2_GPIO_Speed_High_Default   GPIO_SPEED_FREQ_VERY_HIGH
#define MX_FMC_D2_DA2_GPIO_Pin                  GPIO_PIN_0
#define MX_FMC_D2_DA2_GPIO_AF                   GPIO_AF12_FMC
#define MX_FMC_D2_DA2_GPIO_Mode                 GPIO_MODE_AF_PP

/*-------------------------------- MDMA       --------------------------------*/

#define MX_MDMA                                 1

/* NVIC Configuration */

/* NVIC MDMA_IRQn */
#define MX_MDMA_IRQn_interruptPremptionPriority 0
#define MX_MDMA_IRQn_PriorityGroup              NVIC_PRIORITYGROUP_4
#define MX_MDMA_IRQn_Subriority                 0

/*-------------------------------- QUADSPI    --------------------------------*/

#define MX_QUADSPI                              1

/* GPIO Configuration */

/* Pin PB2 */
#define MX_QUADSPI_CLK_GPIO_Speed               GPIO_SPEED_FREQ_VERY_HIGH
#define MX_QUADSPI_CLK_Pin                      PB2
#define MX_QUADSPI_CLK_GPIOx                    GPIOB
#define MX_QUADSPI_CLK_GPIO_PuPd                GPIO_NOPULL
#define MX_QUADSPI_CLK_GPIO_Pin                 GPIO_PIN_2
#define MX_QUADSPI_CLK_GPIO_AF                  GPIO_AF9_QUADSPI
#define MX_QUADSPI_CLK_GPIO_Mode                GPIO_MODE_AF_PP

/* Pin PB6 */
#define MX_QUADSPI_BK1_NCS_GPIO_Speed           GPIO_SPEED_FREQ_VERY_HIGH
#define MX_QUADSPI_BK1_NCS_GPIO_FM6             __NULL
#define MX_QUADSPI_BK1_NCS_Pin                  PB6
#define MX_QUADSPI_BK1_NCS_GPIOx                GPIOB
#define MX_QUADSPI_BK1_NCS_GPIO_PuPd            GPIO_NOPULL
#define MX_QUADSPI_BK1_NCS_GPIO_Pin             GPIO_PIN_6
#define MX_QUADSPI_BK1_NCS_GPIO_AF              GPIO_AF10_QUADSPI
#define MX_QUADSPI_BK1_NCS_GPIO_Mode            GPIO_MODE_AF_PP

/* Pin PA1 */
#define MX_QUADSPI_BK1_IO3_GPIO_Speed           GPIO_SPEED_FREQ_VERY_HIGH
#define MX_QUADSPI_BK1_IO3_Pin                  PA1
#define MX_QUADSPI_BK1_IO3_GPIOx                GPIOA
#define MX_QUADSPI_BK1_IO3_GPIO_PuPd            GPIO_NOPULL
#define MX_QUADSPI_BK1_IO3_GPIO_Pin             GPIO_PIN_1
#define MX_QUADSPI_BK1_IO3_GPIO_AF              GPIO_AF9_QUADSPI
#define MX_QUADSPI_BK1_IO3_GPIO_Mode            GPIO_MODE_AF_PP

/* Pin PE2 */
#define MX_QUADSPI_BK1_IO2_GPIO_Speed           GPIO_SPEED_FREQ_VERY_HIGH
#define MX_QUADSPI_BK1_IO2_Pin                  PE2
#define MX_QUADSPI_BK1_IO2_GPIOx                GPIOE
#define MX_QUADSPI_BK1_IO2_GPIO_PuPd            GPIO_NOPULL
#define MX_QUADSPI_BK1_IO2_GPIO_Pin             GPIO_PIN_2
#define MX_QUADSPI_BK1_IO2_GPIO_AF              GPIO_AF9_QUADSPI
#define MX_QUADSPI_BK1_IO2_GPIO_Mode            GPIO_MODE_AF_PP

/* Pin PC10 */
#define MX_QUADSPI_BK1_IO1_GPIO_Speed           GPIO_SPEED_FREQ_VERY_HIGH
#define MX_QUADSPI_BK1_IO1_Pin                  PC10
#define MX_QUADSPI_BK1_IO1_GPIOx                GPIOC
#define MX_QUADSPI_BK1_IO1_GPIO_PuPd            GPIO_NOPULL
#define MX_QUADSPI_BK1_IO1_GPIO_Pin             GPIO_PIN_10
#define MX_QUADSPI_BK1_IO1_GPIO_AF              GPIO_AF9_QUADSPI
#define MX_QUADSPI_BK1_IO1_GPIO_Mode            GPIO_MODE_AF_PP

/* Pin PC9 */
#define MX_QUADSPI_BK1_IO0_GPIO_Speed           GPIO_SPEED_FREQ_VERY_HIGH
#define MX_QUADSPI_BK1_IO0_Pin                  PC9
#define MX_QUADSPI_BK1_IO0_GPIOx                GPIOC
#define MX_QUADSPI_BK1_IO0_GPIO_PuPd            GPIO_NOPULL
#define MX_QUADSPI_BK1_IO0_GPIO_Pin             GPIO_PIN_9
#define MX_QUADSPI_BK1_IO0_GPIO_AF              GPIO_AF9_QUADSPI
#define MX_QUADSPI_BK1_IO0_GPIO_Mode            GPIO_MODE_AF_PP

/* DMA Configuration */

/* DMA MDMA_Channel40_QUADSPI_FIFO_TH_0 */
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_MaskAddress 0
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_Instance MDMA_Channel0
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_TransferTriggerMode MDMA_BUFFER_TRANSFER
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_SourceDataSize MDMA_SRC_DATASIZE_BYTE
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_DestBurst MDMA_DEST_BURST_SINGLE
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_DestBlockAddressOffset 0
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_pNewNode
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_DestDataSize MDMA_DEST_DATASIZE_BYTE
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_Endianness MDMA_LITTLE_ENDIANNESS_PRESERVE
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_DMA_Handle
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_SourceInc MDMA_SRC_INC_BYTE
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_BlockCount 0
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_DstAddress 0
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_DataAlignment MDMA_DATAALIGN_PACKENABLE
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_BlockDataLength 0
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_BufferTransferLength 128
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_DestinationInc MDMA_DEST_INC_BYTE
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_SourceBurst MDMA_SOURCE_BURST_SINGLE
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_Priority MDMA_PRIORITY_VERY_HIGH
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_Request MDMA_REQUEST_QUADSPI_FIFO_TH
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_Rank First
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_MaskData 0
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_IpInstance
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_CircularMode MDMA_LINEAR_LIST
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_node
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_SourceBlockAddressOffset 0
#define MX_MDMA_Channel40_QUADSPI_FIFO_TH_0_DMA_SrcAddress 0

/* NVIC Configuration */

/* NVIC QUADSPI_IRQn */
#define MX_QUADSPI_IRQn_interruptPremptionPriority 0
#define MX_QUADSPI_IRQn_PriorityGroup           NVIC_PRIORITYGROUP_4
#define MX_QUADSPI_IRQn_Subriority              0

/*-------------------------------- SPI1       --------------------------------*/

#define MX_SPI1                                 1

/* GPIO Configuration */

/* Pin PA4 */
#define MX_SPI1_NSS_GPIO_Speed                  GPIO_SPEED_FREQ_LOW
#define MX_SPI1_NSS_Pin                         PA4
#define MX_SPI1_NSS_GPIOx                       GPIOA
#define MX_SPI1_NSS_GPIO_PuPd                   GPIO_NOPULL
#define MX_SPI1_NSS_GPIO_Pin                    GPIO_PIN_4
#define MX_SPI1_NSS_GPIO_AF                     GPIO_AF5_SPI1
#define MX_SPI1_NSS_GPIO_Mode                   GPIO_MODE_AF_PP

/* Pin PD7 */
#define MX_SPI1_MOSI_GPIO_Speed                 GPIO_SPEED_FREQ_LOW
#define MX_SPI1_MOSI_Pin                        PD7
#define MX_SPI1_MOSI_GPIOx                      GPIOD
#define MX_SPI1_MOSI_GPIO_PuPd                  GPIO_NOPULL
#define MX_SPI1_MOSI_GPIO_Pin                   GPIO_PIN_7
#define MX_SPI1_MOSI_GPIO_AF                    GPIO_AF5_SPI1
#define MX_SPI1_MOSI_GPIO_Mode                  GPIO_MODE_AF_PP

/* Pin PB3 (JTDO/TRACESWO) */
#define MX_SPI1_SCK_GPIO_Speed                  GPIO_SPEED_FREQ_LOW
#define MX_SPI1_SCK_Pin                         PB3_JTDO_TRACESWO
#define MX_SPI1_SCK_GPIOx                       GPIOB
#define MX_SPI1_SCK_GPIO_PuPd                   GPIO_NOPULL
#define MX_SPI1_SCK_GPIO_Pin                    GPIO_PIN_3
#define MX_SPI1_SCK_GPIO_AF                     GPIO_AF5_SPI1
#define MX_SPI1_SCK_GPIO_Mode                   GPIO_MODE_AF_PP

/* DMA Configuration */

/* DMA SPI1_TX */
#define MX_SPI1_TX_DMA_Instance                 DMA1_Stream0
#define MX_SPI1_TX_DMA_FIFOMode                 DMA_FIFOMODE_DISABLE
#define MX_SPI1_TX_DMA_Priority                 DMA_PRIORITY_LOW
#define MX_SPI1_TX_DMA_MemDataAlignment         DMA_MDATAALIGN_HALFWORD
#define MX_SPI1_TX_DMA_Mode                     DMA_NORMAL
#define MX_SPI1_TX_DMA_SyncRequestNumber        1
#define MX_SPI1_TX_DMA_Request                  DMA_REQUEST_SPI1_TX
#define MX_SPI1_TX_DMA_SyncPolarity             HAL_DMAMUX_SYNC_NO_EVENT
#define MX_SPI1_TX_DMA_Direction                DMA_MEMORY_TO_PERIPH
#define MX_SPI1_TX_DMA_SignalID                 NONE
#define MX_SPI1_TX_DMA_MemInc                   DMA_MINC_ENABLE
#define MX_SPI1_TX_DMA_IpInstance
#define MX_SPI1_TX_DMA_RequestNumber            1
#define MX_SPI1_TX_DMA_EventEnable              DISABLE
#define MX_SPI1_TX_DMA_SyncEnable               DISABLE
#define MX_SPI1_TX_DMA_DMA_Handle
#define MX_SPI1_TX_DMA_PeriphDataAlignment      DMA_PDATAALIGN_HALFWORD
#define MX_SPI1_TX_DMA_Polarity                 HAL_DMAMUX_REQ_GEN_RISING
#define MX_SPI1_TX_DMA_SyncSignalID             NONE
#define MX_SPI1_TX_DMA_PeriphInc                DMA_PINC_DISABLE

/* NVIC Configuration */

/* NVIC SPI1_IRQn */
#define MX_SPI1_IRQn_interruptPremptionPriority 0
#define MX_SPI1_IRQn_PriorityGroup              NVIC_PRIORITYGROUP_4
#define MX_SPI1_IRQn_Subriority                 0

/*-------------------------------- SYS        --------------------------------*/

#define MX_SYS                                  1

/* GPIO Configuration */

/*-------------------------------- TIM1       --------------------------------*/

#define MX_TIM1                                 1

/* GPIO Configuration */

/* Pin PA8 */
#define MX_S_TIM1_CH1_GPIO_ModeDefaultPP        GPIO_MODE_AF_PP
#define MX_S_TIM1_CH1_GPIO_Speed                GPIO_SPEED_FREQ_LOW
#define MX_S_TIM1_CH1_Pin                       PA8
#define MX_S_TIM1_CH1_GPIOx                     GPIOA
#define MX_S_TIM1_CH1_GPIO_PuPd                 GPIO_NOPULL
#define MX_LCD_BLK                              S_TIM1_CH1
#define MX_S_TIM1_CH1_GPIO_Pin                  GPIO_PIN_8
#define MX_S_TIM1_CH1_GPIO_AF                   GPIO_AF1_TIM1

/*-------------------------------- TIM1       --------------------------------*/

#define MX_TIM1                                 1

/* GPIO Configuration */

/* Pin PA8 */
#define MX_S_TIM1_CH1_GPIO_ModeDefaultPP        GPIO_MODE_AF_PP
#define MX_S_TIM1_CH1_GPIO_Speed                GPIO_SPEED_FREQ_LOW
#define MX_S_TIM1_CH1_Pin                       PA8
#define MX_S_TIM1_CH1_GPIOx                     GPIOA
#define MX_S_TIM1_CH1_GPIO_PuPd                 GPIO_NOPULL
#define MX_LCD_BLK                              S_TIM1_CH1
#define MX_S_TIM1_CH1_GPIO_Pin                  GPIO_PIN_8
#define MX_S_TIM1_CH1_GPIO_AF                   GPIO_AF1_TIM1

/*-------------------------------- TIM13      --------------------------------*/

#define MX_TIM13                                1

/* GPIO Configuration */

/* NVIC Configuration */

/* NVIC TIM8_UP_TIM13_IRQn */
#define MX_TIM8_UP_TIM13_IRQn_interruptPremptionPriority 0
#define MX_TIM8_UP_TIM13_IRQn_PriorityGroup     NVIC_PRIORITYGROUP_4
#define MX_TIM8_UP_TIM13_IRQn_Subriority        0

/*-------------------------------- USART1     --------------------------------*/

#define MX_USART1                               1

#define MX_USART1_VM                            VM_ASYNC

/* GPIO Configuration */

/* Pin PB14 */
#define MX_USART1_TX_GPIO_ModeDefaultPP         GPIO_MODE_AF_PP
#define MX_USART1_TX_GPIO_Speed                 GPIO_SPEED_FREQ_LOW
#define MX_USART1_TX_Pin                        PB14
#define MX_USART1_TX_GPIOx                      GPIOB
#define MX_USART1_TX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART1_TX_GPIO_Pin                   GPIO_PIN_14
#define MX_USART1_TX_GPIO_AF                    GPIO_AF4_USART1

/* Pin PB15 */
#define MX_USART1_RX_GPIO_ModeDefaultPP         GPIO_MODE_AF_PP
#define MX_USART1_RX_GPIO_Speed                 GPIO_SPEED_FREQ_LOW
#define MX_USART1_RX_Pin                        PB15
#define MX_USART1_RX_GPIOx                      GPIOB
#define MX_USART1_RX_GPIO_PuPd                  GPIO_PULLUP
#define MX_USART1_RX_GPIO_Pin                   GPIO_PIN_15
#define MX_USART1_RX_GPIO_AF                    GPIO_AF4_USART1

/* DMA Configuration */

/* DMA USART1_TX */
#define MX_USART1_TX_DMA_Instance               DMA1_Stream1
#define MX_USART1_TX_DMA_FIFOMode               DMA_FIFOMODE_DISABLE
#define MX_USART1_TX_DMA_Priority               DMA_PRIORITY_LOW
#define MX_USART1_TX_DMA_MemDataAlignment       DMA_MDATAALIGN_BYTE
#define MX_USART1_TX_DMA_Mode                   DMA_NORMAL
#define MX_USART1_TX_DMA_SyncRequestNumber      1
#define MX_USART1_TX_DMA_Request                DMA_REQUEST_USART1_TX
#define MX_USART1_TX_DMA_SyncPolarity           HAL_DMAMUX_SYNC_NO_EVENT
#define MX_USART1_TX_DMA_Direction              DMA_MEMORY_TO_PERIPH
#define MX_USART1_TX_DMA_SignalID               NONE
#define MX_USART1_TX_DMA_MemInc                 DMA_MINC_ENABLE
#define MX_USART1_TX_DMA_IpInstance
#define MX_USART1_TX_DMA_RequestNumber          1
#define MX_USART1_TX_DMA_EventEnable            DISABLE
#define MX_USART1_TX_DMA_SyncEnable             DISABLE
#define MX_USART1_TX_DMA_DMA_Handle
#define MX_USART1_TX_DMA_PeriphDataAlignment    DMA_PDATAALIGN_BYTE
#define MX_USART1_TX_DMA_Polarity               HAL_DMAMUX_REQ_GEN_RISING
#define MX_USART1_TX_DMA_SyncSignalID           NONE
#define MX_USART1_TX_DMA_PeriphInc              DMA_PINC_DISABLE

/* DMA USART1_RX */
#define MX_USART1_RX_DMA_Instance               DMA1_Stream2
#define MX_USART1_RX_DMA_FIFOMode               DMA_FIFOMODE_DISABLE
#define MX_USART1_RX_DMA_Priority               DMA_PRIORITY_LOW
#define MX_USART1_RX_DMA_MemDataAlignment       DMA_MDATAALIGN_BYTE
#define MX_USART1_RX_DMA_Mode                   DMA_CIRCULAR
#define MX_USART1_RX_DMA_SyncRequestNumber      1
#define MX_USART1_RX_DMA_Request                DMA_REQUEST_USART1_RX
#define MX_USART1_RX_DMA_SyncPolarity           HAL_DMAMUX_SYNC_NO_EVENT
#define MX_USART1_RX_DMA_Direction              DMA_PERIPH_TO_MEMORY
#define MX_USART1_RX_DMA_SignalID               NONE
#define MX_USART1_RX_DMA_MemInc                 DMA_MINC_ENABLE
#define MX_USART1_RX_DMA_IpInstance
#define MX_USART1_RX_DMA_RequestNumber          1
#define MX_USART1_RX_DMA_EventEnable            DISABLE
#define MX_USART1_RX_DMA_SyncEnable             DISABLE
#define MX_USART1_RX_DMA_DMA_Handle
#define MX_USART1_RX_DMA_PeriphDataAlignment    DMA_PDATAALIGN_BYTE
#define MX_USART1_RX_DMA_Polarity               HAL_DMAMUX_REQ_GEN_RISING
#define MX_USART1_RX_DMA_SyncSignalID           NONE
#define MX_USART1_RX_DMA_PeriphInc              DMA_PINC_DISABLE

/* NVIC Configuration */

/* NVIC USART1_IRQn */
#define MX_USART1_IRQn_interruptPremptionPriority 0
#define MX_USART1_IRQn_PriorityGroup            NVIC_PRIORITYGROUP_4
#define MX_USART1_IRQn_Subriority               0

/*-------------------------------- USB_OTG_FS --------------------------------*/

#define MX_USB_OTG_FS                           1

#define MX_USB_OTG_FS_DEVICE                    1

/* GPIO Configuration */

/* Pin PA11 */
#define MX_USB_OTG_FS_DM_GPIO_Speed             GPIO_SPEED_FREQ_VERY_HIGH
#define MX_USB_OTG_FS_DM_Pin                    PA11
#define MX_USB_OTG_FS_DM_GPIOx                  GPIOA
#define MX_USB_OTG_FS_DM_GPIO_PuPd              GPIO_NOPULL
#define MX_USB_OTG_FS_DM_GPIO_Pin               GPIO_PIN_11
#define MX_USB_OTG_FS_DM_GPIO_AF                GPIO_AF10_OTG1_FS
#define MX_USB_OTG_FS_DM_GPIO_Mode              GPIO_MODE_AF_PP

/* Pin PA12 */
#define MX_USB_OTG_FS_DP_GPIO_Speed             GPIO_SPEED_FREQ_VERY_HIGH
#define MX_USB_OTG_FS_DP_Pin                    PA12
#define MX_USB_OTG_FS_DP_GPIOx                  GPIOA
#define MX_USB_OTG_FS_DP_GPIO_PuPd              GPIO_NOPULL
#define MX_USB_OTG_FS_DP_GPIO_Pin               GPIO_PIN_12
#define MX_USB_OTG_FS_DP_GPIO_AF                GPIO_AF10_OTG1_FS
#define MX_USB_OTG_FS_DP_GPIO_Mode              GPIO_MODE_AF_PP

/* NVIC Configuration */

/* NVIC OTG_FS_IRQn */
#define MX_OTG_FS_IRQn_interruptPremptionPriority 5
#define MX_OTG_FS_IRQn_PriorityGroup            NVIC_PRIORITYGROUP_4
#define MX_OTG_FS_IRQn_Subriority               0

/*-------------------------------- NVIC       --------------------------------*/

#define MX_NVIC                                 1

/*-------------------------------- GPIO       --------------------------------*/

#define MX_GPIO                                 1

/* GPIO Configuration */

/* Pin PC4 */
#define MX_PC4_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PC4_Pin                              PC4
#define MX_PC4_GPIOx                            GPIOC
#define MX_PC4_PinState                         GPIO_PIN_SET
#define MX_PC4_GPIO_PuPd                        GPIO_PULLUP
#define MX_LED1                                 PC4
#define MX_PC4_GPIO_Pin                         GPIO_PIN_4
#define MX_PC4_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

/* Pin PC5 */
#define MX_PC5_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PC5_Pin                              PC5
#define MX_PC5_GPIOx                            GPIOC
#define MX_PC5_PinState                         GPIO_PIN_SET
#define MX_PC5_GPIO_PuPd                        GPIO_PULLUP
#define MX_LED2                                 PC5
#define MX_PC5_GPIO_Pin                         GPIO_PIN_5
#define MX_PC5_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

/* Pin PD8 */
#define MX_PD8_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PD8_Pin                              PD8
#define MX_PD8_GPIOx                            GPIOD
#define MX_PD8_PinState                         GPIO_PIN_RESET
#define MX_PD8_GPIO_PuPd                        GPIO_PULLDOWN
#define MX_ESP_POW                              PD8
#define MX_PD8_GPIO_Pin                         GPIO_PIN_8
#define MX_PD8_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

/* Pin PA0 */
#define MX_PA0_Pin                              PA0
#define MX_PA0_GPIOx                            GPIOA
#define MX_PA0_GPIO_PuPd                        GPIO_PULLDOWN
#define MX_KEY                                  PA0
#define MX_PA0_GPIO_Pin                         GPIO_PIN_0
#define MX_PA0_GPIO_Mode                        GPIO_MODE_INPUT

/* Pin PB1 */
#define MX_PB1_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PB1_Pin                              PB1
#define MX_PB1_GPIOx                            GPIOB
#define MX_PB1_PinState                         GPIO_PIN_RESET
#define MX_PB1_GPIO_PuPd                        GPIO_NOPULL
#define MX_LCD_RES                              PB1
#define MX_PB1_GPIO_Pin                         GPIO_PIN_1
#define MX_PB1_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

/* Pin PB0 */
#define MX_PB0_GPIO_Speed                       GPIO_SPEED_FREQ_LOW
#define MX_PB0_Pin                              PB0
#define MX_PB0_GPIOx                            GPIOB
#define MX_PB0_PinState                         GPIO_PIN_RESET
#define MX_PB0_GPIO_PuPd                        GPIO_NOPULL
#define MX_LCD_DC                               PB0
#define MX_PB0_GPIO_Pin                         GPIO_PIN_0
#define MX_PB0_GPIO_ModeDefaultOutputPP         GPIO_MODE_OUTPUT_PP

#endif  /* __MX_DEVICE_H */

