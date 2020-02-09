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

/* Global register block address definitions. */
#define RCC   ( ( RCC_TypeDef * )  0x40021000 )
#define GPIOA ( ( GPIO_TypeDef * ) 0x40010800 )
#define GPIOB ( ( GPIO_TypeDef * ) 0x40010C00 )
#define GPIOC ( ( GPIO_TypeDef * ) 0x40011000 )
#define GPIOD ( ( GPIO_TypeDef * ) 0x40011400 )
#define GPIOE ( ( GPIO_TypeDef * ) 0x40011800 )

/* RCC register bit definitions. */
/* APB2ENR */
#define RCC_APB2ENR_AFIOEN_Pos ( 0U )
#define RCC_APB2ENR_AFIOEN_Msk ( 0x1UL << RCC_APB2ENR_AFIOEN_Pos )
#define RCC_APB2ENR_AFIOEN     ( RCC_APB2ENR_AFIOEN_Msk )
#define RCC_APB2ENR_IOPAEN_Pos ( 2U )
#define RCC_APB2ENR_IOPAEN_Msk ( 0x1UL << RCC_APB2ENR_IOPAEN_Pos )
#define RCC_APB2ENR_IOPAEN     ( RCC_APB2ENR_IOPAEN_Msk )
#define RCC_APB2ENR_IOPBEN_Pos ( 3U )
#define RCC_APB2ENR_IOPBEN_Msk ( 0x1UL << RCC_APB2ENR_IOPBEN_Pos )
#define RCC_APB2ENR_IOPBEN     ( RCC_APB2ENR_IOPBEN_Msk )
#define RCC_APB2ENR_IOPCEN_Pos ( 4U )
#define RCC_APB2ENR_IOPCEN_Msk ( 0x1UL << RCC_APB2ENR_IOPCEN_Pos )
#define RCC_APB2ENR_IOPCEN     ( RCC_APB2ENR_IOPCEN_Msk )
#define RCC_APB2ENR_IOPDEN_Pos ( 5U )
#define RCC_APB2ENR_IOPDEN_Msk ( 0x1UL << RCC_APB2ENR_IOPDEN_Pos )
#define RCC_APB2ENR_IOPDEN     ( RCC_APB2ENR_IOPDEN_Msk )
#define RCC_APB2ENR_IOPEEN_Pos ( 6U )
#define RCC_APB2ENR_IOPEEN_Msk ( 0x1UL << RCC_APB2ENR_IOPEEN_Pos )
#define RCC_APB2ENR_IOPEEN     ( RCC_APB2ENR_IOPEEN_Msk )

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

/* AFIO register bit definitions. */
