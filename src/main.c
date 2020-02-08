// Standard library includes.
#include <stdint.h>
#include <string.h>

// Device header files.
#include "gd32vf103.h"
#include "riscv_encoding.h"

// Pre-boot reset handler: disable interrupts, set the
// global and stack pointers, then call the 'main' method.
__attribute__( ( naked ) ) void reset_handler( void ) {
  // Disable interrupts until they are needed.
  clear_csr( mstatus, MSTATUS_MIE );
  // Set the stack pointer.
  __asm__( "la sp, _sp" );
  // Call main(0, 0) in case 'argc' and 'argv' are present.
  __asm__( "li a0, 0\n\t"
           "li a1, 0\n\t"
           "call main" );
}

// Simple 'busy loop' delay method.
// TODO: Use the RISC-V equivalent of the "SysTick" peripheral.
__attribute__( ( optimize( "O0" ) ) )
void delay_cycles( uint32_t cyc ) {
  uint32_t d_i;
  for ( d_i = 0; d_i < cyc; ++d_i ) {
    __asm__( "nop" );
  }
}

// Pre-defined memory locations for program initialization.
extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss;
// 'main' method which gets called from the boot code.
int main( void ) {
  // Copy initialized data from .sidata (Flash) to .data (RAM)
  memcpy( &_sdata, &_sidata, ( ( void* )&_edata - ( void* )&_sdata ) );
  // Clear the .bss RAM section.
  memset( &_sbss, 0x00, ( ( void* )&_ebss - ( void* )&_sbss ) );

  // Enable the GPIOA and GPIOC peripherals.
  RCC->APB2ENR |=  ( RCC_APB2ENR_IOPAEN |
                     RCC_APB2ENR_IOPCEN );

  // Configure pins A1, A2, and C13 as low-speed push-pull outputs.
  GPIOA->CRL   &= ~( GPIO_CRL_MODE1 | GPIO_CRL_CNF1 |
                     GPIO_CRL_MODE2 | GPIO_CRL_CNF2 );
  GPIOA->CRL   |=  ( ( 0x2 << GPIO_CRL_MODE1_Pos ) |
                     ( 0x2 << GPIO_CRL_MODE2_Pos ) );
  GPIOC->CRH   &= ~( GPIO_CRH_MODE13 | GPIO_CRH_CNF13 );
  GPIOC->CRH   |=  ( 0x2 << GPIO_CRH_MODE13_Pos );

  // Turn all three LEDs off.
  // The pins are connected to the LED cathodes, so pulling
  // the pin high turns the LED off, and low turns it on.
  GPIOA->ODR   |=  ( 0x1 << 1 |
                     0x1 << 2 );
  GPIOC->ODR   |=  ( 0x1 << 13 );

  // Cycle the RGB LED through a pattern of colors.
  #define DELAY_CYCLES ( 300000 )
  while( 1 ) {
    // Green on (Green)
    GPIOA->ODR &= ~( 0x1 << 1 );
    delay_cycles( DELAY_CYCLES );
    // Red on (Yellow)
    GPIOC->ODR &= ~( 0x1 << 13 );
    delay_cycles( DELAY_CYCLES );
    // Blue on (White)
    GPIOA->ODR &= ~( 0x1 << 2 );
    delay_cycles( DELAY_CYCLES );
    // Green off (Purple)
    GPIOA->ODR |=  ( 0x1 << 1 );
    delay_cycles( DELAY_CYCLES );
    // Red off (Blue)
    GPIOC->ODR |=  ( 0x1 << 13 );
    delay_cycles( DELAY_CYCLES );
    // Blue off (Off)
    GPIOA->ODR |=  ( 0x1 << 2 );
    delay_cycles( DELAY_CYCLES );
  }
  return 0;
}
