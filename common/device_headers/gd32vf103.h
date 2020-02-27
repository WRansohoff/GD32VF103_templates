#ifndef GD32VF103xB
#define GD32VF103xB
/*
 * GD32VF103CB device header file.
 * Written to be as compatible as possible with STM32F1 code.
 * These definitions are incomplete and application-specific.
 */
#include <stdint.h>

/**
 * Compatibility definitions and RISC-V specific values.
 */
extern volatile uint32_t SystemCoreClock;

/**
 * Interrupt handler enumeration.
 */
typedef enum IRQn {
  CLIC_INT_RESERVED = 0,
  CLIC_INT_SFT = 3,
  CLIC_INT_TMR = 7,
  CLIC_INT_BWEI = 17,
  CLIC_INT_PMOVI = 18,
  WWDG_IRQn = 19,
  PVD_IRQn = 20,
  TAMPER_IRQn = 21,
  RTC_IRQn = 22,
  FLASH_IRQn = 23,
  RCC_IRQn = 24,
  EXTI0_IRQn = 25,
  EXTI1_IRQn = 26,
  EXTI2_IRQn = 27,
  EXTI3_IRQn = 28,
  EXTI4_IRQn = 29,
  DMA1_Channel1_IRQn = 30,
  DMA1_Channel2_IRQn = 31,
  DMA1_Channel3_IRQn = 32,
  DMA1_Channel4_IRQn = 33,
  DMA1_Channel5_IRQn = 34,
  DMA1_Channel6_IRQn = 35,
  DMA1_Channel7_IRQn = 36,
  ADC1_2_IRQn = 37,
  // These two interrupts aren't connected to the USB peripheral
  // on GD32 chips, but names are maintained for STM32F1 compatibility.
  USB_HP_CAN1_TX_IRQn = 38,
  CAN1_TX_IRQn = 38,
  USB_LP_CAN1_RX0_IRQn = 39,
  CAN1_RX0_IRQn = 39,
  CAN1_RX1_IRQn = 40,
  CAN1_SCE_IRQn = 41,
  EXTI9_5_IRQn = 42,
  TIM1_BRK_IRQn = 43,
  TIM1_UP_IRQn = 44,
  TIM1_TRG_COM_IRQn = 45,
  TIM1_CC_IRQn = 46,
  TIM2_IRQn = 47,
  TIM3_IRQn = 48,
  TIM4_IRQn = 49,
  I2C1_EV_IRQn = 50,
  I2C1_ER_IRQn = 51,
  I2C2_EV_IRQn = 52,
  I2C2_ER_IRQn = 53,
  SPI1_IRQn = 54,
  SPI2_IRQn = 55,
  USART1_IRQn = 56,
  USART2_IRQn = 57,
  USART3_IRQn = 58,
  EXTI15_10_IRQn = 59,
  RTC_Alarm_IRQn = 60,
  USBWakeUp_IRQn = 61,
  // Extra interrupts not available on STM32F1 chips:
  // (Numbered peripherals are still 1-indexed)
  EXMC_IRQn = 67,
  TIM5_IRQn = 69,
  SPI3_IRQn = 70,
  UART4_IRQn = 71,
  UART5_IRQn = 72,
  TIM6_IRQn = 73,
  TIM7_IRQn = 74,
  DMA2_Channel1_IRQn = 75,
  DMA2_Channel2_IRQn = 76,
  DMA2_Channel3_IRQn = 77,
  DMA2_Channel4_IRQn = 78,
  DMA2_Channel5_IRQn = 79,
  CAN2_TX_IRQn = 82,
  CAN2_RX0_IRQn = 83,
  CAN2_RX1_IRQn = 84,
  CAN2_SCE_IRQn = 85,
  USBFS_IRQn = 86,
  ECLIC_NUM_INTERRUPTS
} IRQn_Type;

/**
 * RCC / RCU peripheral struct.
 */
typedef struct
{
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSTR;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  /* The following registers differ from STM32F1: */
  volatile uint32_t RSTSCK;
  volatile uint32_t AHBRSTR;
  volatile uint32_t CFGR1;
  volatile uint32_t DSV;
} RCC_TypeDef;

/**
 * GPIO peripheral struct.
 */
typedef struct
{
  volatile uint32_t CRL;
  volatile uint32_t CRH;
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR;
} GPIO_TypeDef;

/**
 * AFIO peripheral struct.
 */
typedef struct
{
  volatile uint32_t EVCR;
  volatile uint32_t MAPR;
  volatile uint32_t EXTICR[ 4 ];
  uint32_t RESERVED0;
  volatile uint32_t MAPR2;
} AFIO_TypeDef;

/**
 * DMA peripheral struct (global).
 */
typedef struct
{
  volatile uint32_t ISR;
  volatile uint32_t IFCR;
} DMA_TypeDef;

/**
 * DMA peripheral struct (per-channel).
 */
typedef struct
{
  volatile uint32_t CCR;
  volatile uint32_t CNDTR;
  volatile uint32_t CPAR;
  volatile uint32_t CMAR;
} DMA_Channel_TypeDef;

/**
 * SPI peripheral struct.
 */
typedef struct
{
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t CRCPR;
  volatile uint32_t RXCRCR;
  volatile uint32_t TXCRCR;
  volatile uint32_t I2SCFGR;
  volatile uint32_t I2SPR;
} SPI_TypeDef;

/* Global register block address definitions. */
#define RCC           ( ( RCC_TypeDef * )         0x40021000 )
#define GPIOA         ( ( GPIO_TypeDef * )        0x40010800 )
#define GPIOB         ( ( GPIO_TypeDef * )        0x40010C00 )
#define GPIOC         ( ( GPIO_TypeDef * )        0x40011000 )
#define GPIOD         ( ( GPIO_TypeDef * )        0x40011400 )
#define GPIOE         ( ( GPIO_TypeDef * )        0x40011800 )
#define AFIO          ( ( AFIO_TypeDef * )        0x40010000 )
#define DMA1          ( ( DMA_TypeDef * )         0x40020000 )
#define DMA2          ( ( DMA_TypeDef * )         0x40020400 )
#define DMA1_Channel1 ( ( DMA_Channel_TypeDef * ) 0x40020008 )
#define DMA1_Channel2 ( ( DMA_Channel_TypeDef * ) 0x4002001C )
#define DMA1_Channel3 ( ( DMA_Channel_TypeDef * ) 0x40020030 )
#define DMA1_Channel4 ( ( DMA_Channel_TypeDef * ) 0x40020044 )
#define DMA1_Channel5 ( ( DMA_Channel_TypeDef * ) 0x40020058 )
#define DMA1_Channel6 ( ( DMA_Channel_TypeDef * ) 0x4002006C )
#define DMA1_Channel7 ( ( DMA_Channel_TypeDef * ) 0x40020080 )
#define DMA2_Channel1 ( ( DMA_Channel_TypeDef * ) 0x40020408 )
#define DMA2_Channel2 ( ( DMA_Channel_TypeDef * ) 0x4002041C )
#define DMA2_Channel3 ( ( DMA_Channel_TypeDef * ) 0x40020430 )
#define DMA2_Channel4 ( ( DMA_Channel_TypeDef * ) 0x40020444 )
#define DMA2_Channel5 ( ( DMA_Channel_TypeDef * ) 0x40020458 )
#define SPI1          ( ( SPI_TypeDef * )         0x40013000 )
#define SPI2          ( ( SPI_TypeDef * )         0x40003800 )
#define SPI3          ( ( SPI_TypeDef * )         0x40003C00 )

/* RCC register bit definitions. */
/* APB2RSTR */
#define RCC_APB2RSTR_AFIORST_Pos   ( 0U )
#define RCC_APB2RSTR_AFIORST_Msk   ( 0x1UL << RCC_APB2RSTR_AFIORST_Pos )
#define RCC_APB2RSTR_AFIORST       ( RCC_APB2RSTR_AFIORST_Msk )
#define RCC_APB2RSTR_IOPARST_Pos   ( 2U )
#define RCC_APB2RSTR_IOPARST_Msk   ( 0x1UL << RCC_APB2RSTR_IOPARST_Pos )
#define RCC_APB2RSTR_IOPARST       ( RCC_APB2RSTR_IOPARST_Msk )
#define RCC_APB2RSTR_IOPBRST_Pos   ( 3U )
#define RCC_APB2RSTR_IOPBRST_Msk   ( 0x1UL << RCC_APB2RSTR_IOPBRST_Pos )
#define RCC_APB2RSTR_IOPBRST       ( RCC_APB2RSTR_IOPBRST_Msk )
#define RCC_APB2RSTR_IOPCRST_Pos   ( 4U )
#define RCC_APB2RSTR_IOPCRST_Msk   ( 0x1UL << RCC_APB2RSTR_IOPCRST_Pos )
#define RCC_APB2RSTR_IOPCRST       ( RCC_APB2RSTR_IOPCRST_Msk )
#define RCC_APB2RSTR_IOPDRST_Pos   ( 5U )
#define RCC_APB2RSTR_IOPDRST_Msk   ( 0x1UL << RCC_APB2RSTR_IOPDRST_Pos )
#define RCC_APB2RSTR_IOPDRST       ( RCC_APB2RSTR_IOPDRST_Msk )
#define RCC_APB2RSTR_IOPERST_Pos   ( 6U )
#define RCC_APB2RSTR_IOPERST_Msk   ( 0x1UL << RCC_APB2RSTR_IOPERST_Pos )
#define RCC_APB2RSTR_IOPERST       ( RCC_APB2RSTR_IOPERST_Msk )
#define RCC_APB2RSTR_ADC1RST_Pos   ( 9U )
#define RCC_APB2RSTR_ADC1RST_Msk   ( 0x1UL << RCC_APB2RSTR_ADC1RST_Pos )
#define RCC_APB2RSTR_ADC1RST       ( RCC_APB2RSTR_ADC1RST_Msk )
#define RCC_APB2RSTR_ADC2RST_Pos   ( 10U )
#define RCC_APB2RSTR_ADC2RST_Msk   ( 0x1UL << RCC_APB2RSTR_ADC2RST_Pos )
#define RCC_APB2RSTR_ADC2RST       ( RCC_APB2RSTR_ADC2RST_Msk )
#define RCC_APB2RSTR_TIM1RST_Pos   ( 11U )
#define RCC_APB2RSTR_TIM1RST_Msk   ( 0x1UL << RCC_APB2RSTR_TIM1RST_Pos )
#define RCC_APB2RSTR_TIM1RST       ( RCC_APB2RSTR_TIM1RST_Msk )
#define RCC_APB2RSTR_SPI1RST_Pos   ( 12U )
#define RCC_APB2RSTR_SPI1RST_Msk   ( 0x1UL << RCC_APB2RSTR_SPI1RST_Pos )
#define RCC_APB2RSTR_SPI1RST       ( RCC_APB2RSTR_SPI1RST_Msk )
#define RCC_APB2RSTR_USART1RST_Pos ( 14U )
#define RCC_APB2RSTR_USART1RST_Msk ( 0x1UL << RCC_APB2RSTR_USART1RST_Pos )
#define RCC_APB2RSTR_USART1RST     ( RCC_APB2RSTR_USART1RST_Msk )
/* AHBENR */
#define RCC_AHBENR_DMA1EN_Pos    ( 0U )
#define RCC_AHBENR_DMA1EN_Msk    ( 0x1UL << RCC_AHBENR_DMA1EN_Pos )
#define RCC_AHBENR_DMA1EN        ( RCC_AHBENR_DMA1EN_Msk )
// Note: DMA2 not present on STM32F103 chips.
#define RCC_AHBENR_DMA2EN_Pos    ( 1U )
#define RCC_AHBENR_DMA2EN_Msk    ( 0x1UL << RCC_AHBENR_DMA2EN_Pos )
#define RCC_AHBENR_DMA2EN        ( RCC_AHBENR_DMA2EN_Msk )
#define RCC_AHBENR_SRAMEN_Pos    ( 2U )
#define RCC_AHBENR_SRAMEN_Msk    ( 0x1UL << RCC_AHBENR_SRAMEN_Pos )
#define RCC_AHBENR_SRAMEN        ( RCC_AHBENR_SRAMEN_Msk )
#define RCC_AHBENR_FLITFEN_Pos   ( 4U )
#define RCC_AHBENR_FLITFEN_Msk   ( 0x1UL << RCC_AHBENR_FLITFEN_Pos )
#define RCC_AHBENR_FLITFEN       ( RCC_AHBENR_FLITFEN_Msk )
#define RCC_AHBENR_CRCEN_Pos     ( 6U )
#define RCC_AHBENR_CRCEN_Msk     ( 0x1UL << RCC_AHBENR_CRCENEN_Pos )
#define RCC_AHBENR_CRCEN         ( RCC_AHBENR_CRCENEN_Msk )
// Note: EXMC not present on STM32F103 chips.
#define RCC_AHBENR_EXMCEN_Pos    ( 8U )
#define RCC_AHBENR_EXMCEN_Msk    ( 0x1UL << RCC_AHBENR_EXMCEN_Pos )
#define RCC_AHBENR_EXMCEN        ( RCC_AHBENR_EXMCEN_Msk )
// Note: USB handled differently on STM32F103 chips.
#define RCC_AHBENR_USBFSEN_Pos   ( 12U )
#define RCC_AHBENR_USBFSEN_Msk   ( 0x1UL << RCC_AHBENR_USBFSEN_Pos )
#define RCC_AHBENR_USBFSEN       ( RCC_AHBENR_USBFSEN_Msk )
/* APB2ENR */
#define RCC_APB2ENR_AFIOEN_Pos   ( 0U )
#define RCC_APB2ENR_AFIOEN_Msk   ( 0x1UL << RCC_APB2ENR_AFIOEN_Pos )
#define RCC_APB2ENR_AFIOEN       ( RCC_APB2ENR_AFIOEN_Msk )
#define RCC_APB2ENR_IOPAEN_Pos   ( 2U )
#define RCC_APB2ENR_IOPAEN_Msk   ( 0x1UL << RCC_APB2ENR_IOPAEN_Pos )
#define RCC_APB2ENR_IOPAEN       ( RCC_APB2ENR_IOPAEN_Msk )
#define RCC_APB2ENR_IOPBEN_Pos   ( 3U )
#define RCC_APB2ENR_IOPBEN_Msk   ( 0x1UL << RCC_APB2ENR_IOPBEN_Pos )
#define RCC_APB2ENR_IOPBEN       ( RCC_APB2ENR_IOPBEN_Msk )
#define RCC_APB2ENR_IOPCEN_Pos   ( 4U )
#define RCC_APB2ENR_IOPCEN_Msk   ( 0x1UL << RCC_APB2ENR_IOPCEN_Pos )
#define RCC_APB2ENR_IOPCEN       ( RCC_APB2ENR_IOPCEN_Msk )
#define RCC_APB2ENR_IOPDEN_Pos   ( 5U )
#define RCC_APB2ENR_IOPDEN_Msk   ( 0x1UL << RCC_APB2ENR_IOPDEN_Pos )
#define RCC_APB2ENR_IOPDEN       ( RCC_APB2ENR_IOPDEN_Msk )
#define RCC_APB2ENR_IOPEEN_Pos   ( 6U )
#define RCC_APB2ENR_IOPEEN_Msk   ( 0x1UL << RCC_APB2ENR_IOPEEN_Pos )
#define RCC_APB2ENR_IOPEEN       ( RCC_APB2ENR_IOPEEN_Msk )
#define RCC_APB2ENR_ADC1EN_Pos   ( 9U )
#define RCC_APB2ENR_ADC1EN_Msk   ( 0x1UL << RCC_APB2ENR_ADC1EN_Pos )
#define RCC_APB2ENR_ADC1EN       ( RCC_APB2ENR_ADC1EN_Msk )
#define RCC_APB2ENR_ADC2EN_Pos   ( 10U )
#define RCC_APB2ENR_ADC2EN_Msk   ( 0x1UL << RCC_APB2ENR_ADC2EN_Pos )
#define RCC_APB2ENR_ADC2EN       ( RCC_APB2ENR_ADC2EN_Msk )
#define RCC_APB2ENR_TIM1EN_Pos   ( 11U )
#define RCC_APB2ENR_TIM1EN_Msk   ( 0x1UL << RCC_APB2ENR_TIM1EN_Pos )
#define RCC_APB2ENR_TIM1EN       ( RCC_APB2ENR_TIM1EN_Msk )
#define RCC_APB2ENR_SPI1EN_Pos   ( 12U )
#define RCC_APB2ENR_SPI1EN_Msk   ( 0x1UL << RCC_APB2ENR_SPI1EN_Pos )
#define RCC_APB2ENR_SPI1EN       ( RCC_APB2ENR_SPI1EN_Msk )
#define RCC_APB2ENR_USART1EN_Pos ( 14U )
#define RCC_APB2ENR_USART1EN_Msk ( 0x1UL << RCC_APB2ENR_USART1EN_Pos )
#define RCC_APB2ENR_USART1EN     ( RCC_APB2ENR_USART1EN_Msk )

/* AFIO register bit definitions. */

/* GPIO register bit definitions. */
/* CRL */
#define GPIO_CRL_MODE_Pos   ( 0U )
#define GPIO_CRL_MODE_Msk   ( 0x33333333UL << GPIO_CRL_MODE_Pos )
#define GPIO_CRL_MODE       ( GPIO_CRL_MODE_Msk )
#define GPIO_CRL_MODE0_Pos  ( 0U )
#define GPIO_CRL_MODE0_Msk  ( 0x3UL << GPIO_CRL_MODE0_Pos )
#define GPIO_CRL_MODE0      ( GPIO_CRL_MODE0_Msk )
#define GPIO_CRL_MODE1_Pos  ( 4U )
#define GPIO_CRL_MODE1_Msk  ( 0x3UL << GPIO_CRL_MODE1_Pos )
#define GPIO_CRL_MODE1      ( GPIO_CRL_MODE1_Msk )
#define GPIO_CRL_MODE2_Pos  ( 8U )
#define GPIO_CRL_MODE2_Msk  ( 0x3UL << GPIO_CRL_MODE2_Pos )
#define GPIO_CRL_MODE2      ( GPIO_CRL_MODE2_Msk )
#define GPIO_CRL_MODE3_Pos  ( 12U )
#define GPIO_CRL_MODE3_Msk  ( 0x3UL << GPIO_CRL_MODE3_Pos )
#define GPIO_CRL_MODE3      ( GPIO_CRL_MODE3_Msk )
#define GPIO_CRL_MODE4_Pos  ( 16U )
#define GPIO_CRL_MODE4_Msk  ( 0x3UL << GPIO_CRL_MODE4_Pos )
#define GPIO_CRL_MODE4      ( GPIO_CRL_MODE4_Msk )
#define GPIO_CRL_MODE5_Pos  ( 20U )
#define GPIO_CRL_MODE5_Msk  ( 0x3UL << GPIO_CRL_MODE5_Pos )
#define GPIO_CRL_MODE5      ( GPIO_CRL_MODE5_Msk )
#define GPIO_CRL_MODE6_Pos  ( 24U )
#define GPIO_CRL_MODE6_Msk  ( 0x3UL << GPIO_CRL_MODE6_Pos )
#define GPIO_CRL_MODE6      ( GPIO_CRL_MODE6_Msk )
#define GPIO_CRL_MODE7_Pos  ( 28U )
#define GPIO_CRL_MODE7_Msk  ( 0x3UL << GPIO_CRL_MODE7_Pos )
#define GPIO_CRL_MODE7      ( GPIO_CRL_MODE7_Msk )
#define GPIO_CRL_CNF_Pos    ( 2U )
#define GPIO_CRL_CNF_Msk    ( 0x33333333UL << GPIO_CRL_CNF_Pos )
#define GPIO_CRL_CNF        ( GPIO_CRL_CNF_Msk )
#define GPIO_CRL_CNF0_Pos   ( 2U )
#define GPIO_CRL_CNF0_Msk   ( 0x3UL << GPIO_CRL_CNF0_Pos )
#define GPIO_CRL_CNF0       ( GPIO_CRL_CNF0_Msk )
#define GPIO_CRL_CNF1_Pos   ( 6U )
#define GPIO_CRL_CNF1_Msk   ( 0x3UL << GPIO_CRL_CNF1_Pos )
#define GPIO_CRL_CNF1       ( GPIO_CRL_CNF1_Msk )
#define GPIO_CRL_CNF2_Pos   ( 10U )
#define GPIO_CRL_CNF2_Msk   ( 0x3UL << GPIO_CRL_CNF2_Pos )
#define GPIO_CRL_CNF2       ( GPIO_CRL_CNF2_Msk )
#define GPIO_CRL_CNF3_Pos   ( 14U )
#define GPIO_CRL_CNF3_Msk   ( 0x3UL << GPIO_CRL_CNF3_Pos )
#define GPIO_CRL_CNF3       ( GPIO_CRL_CNF3_Msk )
#define GPIO_CRL_CNF4_Pos   ( 18U )
#define GPIO_CRL_CNF4_Msk   ( 0x3UL << GPIO_CRL_CNF4_Pos )
#define GPIO_CRL_CNF4       ( GPIO_CRL_CNF4_Msk )
#define GPIO_CRL_CNF5_Pos   ( 22U )
#define GPIO_CRL_CNF5_Msk   ( 0x3UL << GPIO_CRL_CNF5_Pos )
#define GPIO_CRL_CNF5       ( GPIO_CRL_CNF5_Msk )
#define GPIO_CRL_CNF6_Pos   ( 26U )
#define GPIO_CRL_CNF6_Msk   ( 0x3UL << GPIO_CRL_CNF6_Pos )
#define GPIO_CRL_CNF6       ( GPIO_CRL_CNF6_Msk )
#define GPIO_CRL_CNF7_Pos   ( 30U )
#define GPIO_CRL_CNF7_Msk   ( 0x3UL << GPIO_CRL_CNF7_Pos )
#define GPIO_CRL_CNF7       ( GPIO_CRL_CNF7_Msk )
/* CRH */
#define GPIO_CRH_MODE_Pos   ( 0U )
#define GPIO_CRH_MODE_Msk   ( 0x33333333UL << GPIO_CRH_MODE_Pos )
#define GPIO_CRH_MODE       ( GPIO_CRH_MODE_Msk )
#define GPIO_CRH_MODE8_Pos  ( 0U )
#define GPIO_CRH_MODE8_Msk  ( 0x3UL << GPIO_CRH_MODE8_Pos )
#define GPIO_CRH_MODE8      ( GPIO_CRH_MODE8_Msk )
#define GPIO_CRH_MODE9_Pos  ( 4U )
#define GPIO_CRH_MODE9_Msk  ( 0x3UL << GPIO_CRH_MODE9_Pos )
#define GPIO_CRH_MODE9      ( GPIO_CRH_MODE9_Msk )
#define GPIO_CRH_MODE10_Pos ( 8U )
#define GPIO_CRH_MODE10_Msk ( 0x3UL << GPIO_CRH_MODE10_Pos )
#define GPIO_CRH_MODE10     ( GPIO_CRH_MODE10_Msk )
#define GPIO_CRH_MODE11_Pos ( 12U )
#define GPIO_CRH_MODE11_Msk ( 0x11UL << GPIO_CRH_MODE11_Pos )
#define GPIO_CRH_MODE11     ( GPIO_CRH_MODE11_Msk )
#define GPIO_CRH_MODE12_Pos ( 16U )
#define GPIO_CRH_MODE12_Msk ( 0x3UL << GPIO_CRH_MODE12_Pos )
#define GPIO_CRH_MODE12     ( GPIO_CRH_MODE12_Msk )
#define GPIO_CRH_MODE13_Pos ( 20U )
#define GPIO_CRH_MODE13_Msk ( 0x3UL << GPIO_CRH_MODE13_Pos )
#define GPIO_CRH_MODE13     ( GPIO_CRH_MODE13_Msk )
#define GPIO_CRH_MODE14_Pos ( 24U )
#define GPIO_CRH_MODE14_Msk ( 0x3UL << GPIO_CRH_MODE14_Pos )
#define GPIO_CRH_MODE14     ( GPIO_CRH_MODE14_Msk )
#define GPIO_CRH_MODE15_Pos ( 28U )
#define GPIO_CRH_MODE15_Msk ( 0x3UL << GPIO_CRH_MODE15_Pos )
#define GPIO_CRH_MODE15     ( GPIO_CRH_MODE15_Msk )
#define GPIO_CRH_CNF_Pos    ( 2U )
#define GPIO_CRH_CNF_Msk    ( 0x33333333UL << GPIO_CRH_CNF_Pos )
#define GPIO_CRH_CNF        ( GPIO_CRH_CNF_Msk )
#define GPIO_CRH_CNF8_Pos   ( 2U )
#define GPIO_CRH_CNF8_Msk   ( 0x3UL << GPIO_CRH_CNF8_Pos )
#define GPIO_CRH_CNF8       ( GPIO_CRH_CNF8_Msk )
#define GPIO_CRH_CNF9_Pos   ( 6U )
#define GPIO_CRH_CNF9_Msk   ( 0x3UL << GPIO_CRH_CNF9_Pos )
#define GPIO_CRH_CNF9       ( GPIO_CRH_CNF9_Msk )
#define GPIO_CRH_CNF10_Pos  ( 10U )
#define GPIO_CRH_CNF10_Msk  ( 0x3UL << GPIO_CRH_CNF10_Pos )
#define GPIO_CRH_CNF10      ( GPIO_CRH_CNF10_Msk )
#define GPIO_CRH_CNF11_Pos  ( 14U )
#define GPIO_CRH_CNF11_Msk  ( 0x11UL << GPIO_CRH_CNF11_Pos )
#define GPIO_CRH_CNF11      ( GPIO_CRH_CNF11_Msk )
#define GPIO_CRH_CNF12_Pos  ( 18U )
#define GPIO_CRH_CNF12_Msk  ( 0x3UL << GPIO_CRH_CNF12_Pos )
#define GPIO_CRH_CNF12      ( GPIO_CRH_CNF12_Msk )
#define GPIO_CRH_CNF13_Pos  ( 22U )
#define GPIO_CRH_CNF13_Msk  ( 0x3UL << GPIO_CRH_CNF13_Pos )
#define GPIO_CRH_CNF13      ( GPIO_CRH_CNF13_Msk )
#define GPIO_CRH_CNF14_Pos  ( 214U )
#define GPIO_CRH_CNF14_Msk  ( 0x3UL << GPIO_CRH_CNF14_Pos )
#define GPIO_CRH_CNF14      ( GPIO_CRH_CNF14_Msk )
#define GPIO_CRH_CNF15_Pos  ( 30U )
#define GPIO_CRH_CNF15_Msk  ( 0x3UL << GPIO_CRH_CNF15_Pos )
#define GPIO_CRH_CNF15      ( GPIO_CRH_CNF15_Msk )

/* Global DMA register bit definitions. */

/* Per-channel DMA register bit definitions. */
/* CCR / CHCTL */
#define DMA_CCR_EN_Pos      ( 0U )
#define DMA_CCR_EN_Msk      ( 0x1UL << DMA_CCR_EN_Pos )
#define DMA_CCR_EN          ( DMA_CCR_EN_Msk )
#define DMA_CCR_TCIE_Pos    ( 1U )
#define DMA_CCR_TCIE_Msk    ( 0x1UL << DMA_CCR_TCIE_Pos )
#define DMA_CCR_TCIE        ( DMA_CCR_TCIE_Msk )
#define DMA_CCR_HTIE_Pos    ( 2U )
#define DMA_CCR_HTIE_Msk    ( 0x1UL << DMA_CCR_HTIE_Pos )
#define DMA_CCR_HTIE        ( DMA_CCR_HTIE_Msk )
#define DMA_CCR_TEIE_Pos    ( 3U )
#define DMA_CCR_TEIE_Msk    ( 0x1UL << DMA_CCR_TEIE_Pos )
#define DMA_CCR_TEIE        ( DMA_CCR_TEIE_Msk )
#define DMA_CCR_DIR_Pos     ( 4U )
#define DMA_CCR_DIR_Msk     ( 0x1UL << DMA_CCR_DIR_Pos )
#define DMA_CCR_DIR         ( DMA_CCR_DIR_Msk )
#define DMA_CCR_CIRC_Pos    ( 5U )
#define DMA_CCR_CIRC_Msk    ( 0x1UL << DMA_CCR_CIRC_Pos )
#define DMA_CCR_CIRC        ( DMA_CCR_CIRC_Msk )
#define DMA_CCR_PINC_Pos    ( 6U )
#define DMA_CCR_PINC_Msk    ( 0x1UL << DMA_CCR_PINC_Pos )
#define DMA_CCR_PINC        ( DMA_CCR_PINC_Msk )
#define DMA_CCR_MINC_Pos    ( 7U )
#define DMA_CCR_MINC_Msk    ( 0x1UL << DMA_CCR_MINC_Pos )
#define DMA_CCR_MINC        ( DMA_CCR_MINC_Msk )
#define DMA_CCR_PSIZE_Pos   ( 8U )
#define DMA_CCR_PSIZE_Msk   ( 0x3UL << DMA_CCR_PSIZE_Pos )
#define DMA_CCR_PSIZE       ( DMA_CCR_PSIZE_Msk )
#define DMA_CCR_MSIZE_Pos   ( 10U )
#define DMA_CCR_MSIZE_Msk   ( 0x3UL << DMA_CCR_MSIZE_Pos )
#define DMA_CCR_MSIZE       ( DMA_CCR_MSIZE_Msk )
#define DMA_CCR_PL_Pos      ( 12U )
#define DMA_CCR_PL_Msk      ( 0x3UL << DMA_CCR_PL_Pos )
#define DMA_CCR_PL          ( DMA_CCR_PL_Msk )
#define DMA_CCR_MEM2MEM_Pos ( 14U )
#define DMA_CCR_MEM2MEM_Msk ( 0x1UL << DMA_CCR_MEM2MEM_Pos )
#define DMA_CCR_MEM2MEM     ( DMA_CCR_MEM2MEM_Msk )

/* SPI register bit definitions. */
/* CR1 */
#define SPI_CR1_CPHA_Pos     ( 0U )
#define SPI_CR1_CPHA_Msk     ( 0x1UL << SPI_CR1_CPHA_Pos )
#define SPI_CR1_CPHA         ( SPI_CR1_CPHA_Msk )
#define SPI_CR1_CPOL_Pos     ( 1U )
#define SPI_CR1_CPOL_Msk     ( 0x1UL << SPI_CR1_CPOL_Pos )
#define SPI_CR1_CPOL         ( SPI_CR1_CPOL_Msk )
#define SPI_CR1_MSTR_Pos     ( 2U )
#define SPI_CR1_MSTR_Msk     ( 0x1UL << SPI_CR1_MSTR_Pos )
#define SPI_CR1_MSTR         ( SPI_CR1_MSTR_Msk )
#define SPI_CR1_BR_Pos       ( 3U )
#define SPI_CR1_BR_Msk       ( 0x7UL << SPI_CR1_BR_Pos )
#define SPI_CR1_BR           ( SPI_CR1_BR_Msk )
#define SPI_CR1_SPE_Pos      ( 6U )
#define SPI_CR1_SPE_Msk      ( 0x1UL << SPI_CR1_SPE_Pos )
#define SPI_CR1_SPE          ( SPI_CR1_SPE_Msk )
#define SPI_CR1_LSBFIRST_Pos ( 7U )
#define SPI_CR1_LSBFIRST_Msk ( 0x1UL << SPI_CR1_LSBFIRST_Pos )
#define SPI_CR1_LSBFIRST     ( SPI_CR1_LSBFIRST_Msk )
#define SPI_CR1_SSI_Pos      ( 8U )
#define SPI_CR1_SSI_Msk      ( 0x1UL << SPI_CR1_SSI_Pos )
#define SPI_CR1_SSI          ( SPI_CR1_SSI_Msk )
#define SPI_CR1_SSM_Pos      ( 9U )
#define SPI_CR1_SSM_Msk      ( 0x1UL << SPI_CR1_SSM_Pos )
#define SPI_CR1_SSM          ( SPI_CR1_SSM_Msk )
#define SPI_CR1_RXONLY_Pos   ( 10U )
#define SPI_CR1_RXONLY_Msk   ( 0x1UL << SPI_CR1_RXONLY_Pos )
#define SPI_CR1_RXONLY       ( SPI_CR1_RXONLY_Msk )
#define SPI_CR1_DFF_Pos      ( 11U )
#define SPI_CR1_DFF_Msk      ( 0x1UL << SPI_CR1_DFF_Pos )
#define SPI_CR1_DFF          ( SPI_CR1_DFF_Msk )
#define SPI_CR1_CRCNEXT_Pos  ( 12U )
#define SPI_CR1_CRCNEXT_Msk  ( 0x1UL << SPI_CR1_CRCNEXT_Pos )
#define SPI_CR1_CRCNEXT      ( SPI_CR1_CRCNEXT_Msk )
#define SPI_CR1_CRCEN_Pos    ( 13U )
#define SPI_CR1_CRCEN_Msk    ( 0x1UL << SPI_CR1_CRCEN_Pos )
#define SPI_CR1_CRCEN        ( SPI_CR1_CRCEN_Msk )
#define SPI_CR1_BIDIOE_Pos   ( 14U )
#define SPI_CR1_BIDIOE_Msk   ( 0x1UL << SPI_CR1_BIDIOE_Pos )
#define SPI_CR1_BIDIOE       ( SPI_CR1_BIDIOE_Msk )
#define SPI_CR1_BIDIMODE_Pos ( 15U )
#define SPI_CR1_BIDIMODE_Msk ( 0x1UL << SPI_CR1_BIDIMODE_Pos )
#define SPI_CR1_BIDIMODE     ( SPI_CR1_BIDIMODE_Msk )
/* CR2 */
#define SPI_CR2_RXDMAEN_Pos ( 0U )
#define SPI_CR2_RXDMAEN_Msk ( 0x1UL << SPI_CR2_RXDMAEN_Pos )
#define SPI_CR2_RXDMAEN     ( SPI_CR2_RXDMAEN_Msk )
#define SPI_CR2_TXDMAEN_Pos ( 1U )
#define SPI_CR2_TXDMAEN_Msk ( 0x1UL << SPI_CR2_TXDMAEN_Pos )
#define SPI_CR2_TXDMAEN     ( SPI_CR2_TXDMAEN_Msk )
#define SPI_CR2_SSOE_Pos    ( 2U )
#define SPI_CR2_SSOE_Msk    ( 0x1UL << SPI_CR2_SSOE_Pos )
#define SPI_CR2_SSOE        ( SPI_CR2_SSOE_Msk )
// Note: 'NSS pulse mode' and 'TI mode' bits don't show up in
// STM32F103 reference documents.
#define SPI_CR2_NSSP_Pos    ( 3U )
#define SPI_CR2_NSSP_Msk    ( 0x1UL << SPI_CR2_NSSP_Pos )
#define SPI_CR2_NSSP        ( SPI_CR2_NSSP_Msk )
#define SPI_CR2_TIMOD_Pos   ( 4U )
#define SPI_CR2_TIMOD_Msk   ( 0x1UL << SPI_CR2_TIMOD_Pos )
#define SPI_CR2_TIMOD       ( SPI_CR2_TIMOD_Msk )
#define SPI_CR2_ERRIE_Pos   ( 5U )
#define SPI_CR2_ERRIE_Msk   ( 0x1UL << SPI_CR2_ERRIE_Pos )
#define SPI_CR2_ERRIE       ( SPI_CR2_ERRIE_Msk )
#define SPI_CR2_RXNEIE_Pos  ( 6U )
#define SPI_CR2_RXNEIE_Msk  ( 0x1UL << SPI_CR2_RXNEIE_Pos )
#define SPI_CR2_RXNEIE      ( SPI_CR2_RXNEIE_Msk )
#define SPI_CR2_TXEIE_Pos   ( 7U )
#define SPI_CR2_TXEIE_Msk   ( 0x1UL << SPI_CR2_TXEIE_Pos )
#define SPI_CR2_TXEIE       ( SPI_CR2_TXEIE_Msk )
/* SR / STAT */
#define SPI_SR_RXNE_Pos   ( 0U )
#define SPI_SR_RXNE_Msk   ( 0x1UL << SPI_SR_RXNE_Pos )
#define SPI_SR_RXNE       ( SPI_SR_RXNE_Msk )
#define SPI_SR_TXE_Pos    ( 1U )
#define SPI_SR_TXE_Msk    ( 0x1UL << SPI_SR_TXE_Pos )
#define SPI_SR_TXE        ( SPI_SR_TXE_Msk )
#define SPI_SR_CHSIDE_Pos ( 2U )
#define SPI_SR_CHSIDE_Msk ( 0x1UL << SPI_SR_CHSIDE_Pos )
#define SPI_SR_CHSIDE     ( SPI_SR_CHSIDE_Msk )
#define SPI_SR_UDR_Pos    ( 3U )
#define SPI_SR_UDR_Msk    ( 0x1UL << SPI_SR_UDR_Pos )
#define SPI_SR_UDR        ( SPI_SR_UDR_Msk )
#define SPI_SR_CRCERR_Pos ( 4U )
#define SPI_SR_CRCERR_Msk ( 0x1UL << SPI_SR_CRCERR_Pos )
#define SPI_SR_CRCERR     ( SPI_SR_CRCERR_Msk )
#define SPI_SR_MODF_Pos   ( 5U )
#define SPI_SR_MODF_Msk   ( 0x1UL << SPI_SR_MODF_Pos )
#define SPI_SR_MODF       ( SPI_SR_MODF_Msk )
#define SPI_SR_OVR_Pos    ( 6U )
#define SPI_SR_OVR_Msk    ( 0x1UL << SPI_SR_OVR_Pos )
#define SPI_SR_OVR        ( SPI_SR_OVR_Msk )
#define SPI_SR_BSY_Pos    ( 7U )
#define SPI_SR_BSY_Msk    ( 0x1UL << SPI_SR_BSY_Pos )
#define SPI_SR_BSY        ( SPI_SR_BSY_Msk )
// Note: "Format error" bit doesn't show up in STM32F1 documentation.
#define SPI_SR_FERR_Pos   ( 8U )
#define SPI_SR_FERR_Msk   ( 0x1UL << SPI_SR_FERR_Pos )
#define SPI_SR_FERR       ( SPI_SR_FERR_Msk )

#endif
