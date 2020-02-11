// Standard library includes.
#include <stdint.h>
#include <string.h>

// Device header files.
#include "gd32vf103.h"
#include "n200_func.h"
#include "riscv_encoding.h"

// Pre-defined memory locations for program initialization.
extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss;
// Current system core clock speed.
volatile uint32_t SystemCoreClock = 8000000;
// Global 'tick' value.
volatile uint32_t systick = 0;
// Framebuffer for the TFT display.
#define TFT_W ( 160 )
#define TFT_H ( 80 )
#define TFT_A ( TFT_W * TFT_H )
volatile uint16_t fb[ TFT_A ];

// Simple "millisecond delay" function.
void delay_ms( uint32_t ms ) {
  // Calculate the 'system tick' value to wait until.
  uint32_t done = systick + ms;
  // Wait until the 'systick' value ticks up enough.
  while ( systick < done ) { __WFI(); }
}

// 'Switch mode' display helper function.
#define MODE_CMD ( 0 )
#define MODE_DAT ( 1 )
void display_mode( int type ) {
  // Wait for any ongoing transfers to finish.
  while ( SPI1->SR & SPI_SR_BSY ) {};
  // Set the 'data / command' pin level.
  if ( type ) { GPIOB->ODR |=  ( 0x1 << 0 ); }
  else        { GPIOB->ODR &= ~( 0x1 << 0 ); }
}

// 'Write SPI byte' display helper function.
void spi_w8( SPI_TypeDef* SPIx, uint8_t byte ) {
  // Wait for the transmit buffer to have space.
  while ( !( SPI1->SR & SPI_SR_TXE ) ) {};
  // Send the next byte of data.
  *( uint8_t * )&( SPIx->DR ) = byte;
}

// 'Write SPI half-word' display helper function.
void spi_w16( SPI_TypeDef* SPIx, uint16_t hword ) {
  spi_w8( SPIx, hword >> 8 );
  spi_w8( SPIx, hword & 0xFF );
}

// 'main' method which gets called from the boot code.
int main( void ) {
  // Copy initialized data from .sidata (Flash) to .data (RAM)
  memcpy( &_sdata, &_sidata, ( ( void* )&_edata - ( void* )&_sdata ) );
  // Clear the .bss RAM section.
  memset( &_sbss, 0x00, ( ( void* )&_ebss - ( void* )&_sbss ) );

  // Reset the SPI1 peripheral.
  RCC->APB2RSTR |=  ( RCC_APB2RSTR_SPI1RST );
  RCC->APB2RSTR &= ~( RCC_APB2RSTR_SPI1RST );
  // Clear the DMA channel 3 configuration.
  DMA1_Channel3->CCR = 0x00000000;
  // Enable the GPIOA, GPIOB, GPIOC, SPI1, and DMA1 peripherals.
  RCC->APB2ENR  |=  ( RCC_APB2ENR_IOPAEN |
                      RCC_APB2ENR_IOPBEN |
                      RCC_APB2ENR_IOPCEN |
                      RCC_APB2ENR_SPI1EN );
  RCC->AHBENR   |=  ( RCC_AHBENR_DMA1EN );

  // Configure pins A1, A2, and C13 as low-speed push-pull outputs.
  GPIOA->CRL   &= ~( GPIO_CRL_MODE1 | GPIO_CRL_CNF1 |
                     GPIO_CRL_MODE2 | GPIO_CRL_CNF2 );
  GPIOA->CRL   |=  ( ( 0x2 << GPIO_CRL_MODE1_Pos ) |
                     ( 0x2 << GPIO_CRL_MODE2_Pos ) );
  GPIOC->CRH   &= ~( GPIO_CRH_MODE13 | GPIO_CRH_CNF13 );
  GPIOC->CRH   |=  ( 0x2 << GPIO_CRH_MODE13_Pos );
  // Configure pins A5 and A7 as high-speed alternate-function outputs.
  GPIOA->CRL   &= ~( GPIO_CRL_MODE5 | GPIO_CRL_CNF5 |
                     GPIO_CRL_MODE7 | GPIO_CRL_CNF7 );
  GPIOA->CRL   |=  ( ( 0x3 << GPIO_CRL_MODE5_Pos ) |
                     ( 0x3 << GPIO_CRL_MODE7_Pos ) |
                     ( 0x2 << GPIO_CRL_CNF5_Pos ) |
                     ( 0x2 << GPIO_CRL_CNF7_Pos ) );
  // Configure pins B0, B1, and B2 as low-speed push-pull outputs.
  GPIOB->CRL   &= ~( ( GPIO_CRL_MODE0 | GPIO_CRL_CNF0 ) |
                     ( GPIO_CRL_MODE1 | GPIO_CRL_CNF1 ) |
                     ( GPIO_CRL_MODE2 | GPIO_CRL_CNF2 ) );
  GPIOB->CRL   |=  ( ( 0x2 << GPIO_CRL_MODE0_Pos ) |
                     ( 0x2 << GPIO_CRL_MODE1_Pos ) |
                     ( 0x2 << GPIO_CRL_MODE2_Pos ) );

  // Turn the green LED off, and the red/blue LEDs on.
  // The pins are connected to the LED cathodes, so pulling
  // the pin high turns the LED off, and low turns it on.
  GPIOA->ODR   |=  ( 0x1 << 1 );
  GPIOA->ODR   &= ~( 0x1 << 2 );
  GPIOC->ODR   &= ~( 0x1 << 13 );

  // DMA configuration:
  // - Memory-to-peripheral mode.
  // - Circular mode enabled for continuous transfer.
  // - Increment source ptr, don't increment destination ptr.
  // - 8-bit transfer length.
  // - High-priority. Not that priority matters; it's the only one.
  DMA1_Channel3->CCR  &= ~( DMA_CCR_MEM2MEM |
                            DMA_CCR_PL |
                            DMA_CCR_MSIZE |
                            DMA_CCR_PSIZE |
                            DMA_CCR_PINC |
                            DMA_CCR_EN );
  DMA1_Channel3->CCR  |=  ( ( 0x2 << DMA_CCR_PL_Pos ) |
                            DMA_CCR_MINC |
                            DMA_CCR_CIRC |
                            DMA_CCR_DIR );
  // Set source memory address to the framebuffer array.
  DMA1_Channel3->CMAR  =  ( uint32_t )&( fb );
  // Set destination peripheral address to the SPI1 data register.
  DMA1_Channel3->CPAR  =  ( uint32_t )&( SPI1->DR );
  // Set the number of bits to transfer. In this case, it's the
  // number of 16-bit colors multiplied by two.
  DMA1_Channel3->CNDTR =  ( uint32_t )( TFT_A * 2 );

  // SPI1 setup: host mode, no baud rate division, sw cs pin control,
  // TX DMA enabled, 8-bit frames, msb-first, enable the peripheral.
  // Some of those settings are the default state after a reset.
  SPI1->CR2  |=  ( SPI_CR2_TXDMAEN );
  SPI1->CR1  &= ~( SPI_CR1_BR );
  SPI1->CR1  |=  ( SPI_CR1_SSM |
                   SPI_CR1_SSI |
                   SPI_CR1_MSTR |
                   SPI_CR1_SPE );

  // Set up the global timer to generate an interrupt every ms.
  // Figure out how many interrupts are available.
  uint32_t max_irqn = *( volatile uint32_t * )( ECLIC_ADDR_BASE + ECLIC_INFO_OFFSET );
  max_irqn &= ( 0x00001FFF );
  // Initialize the 'ECLIC' interrupt controller.
  eclic_init( max_irqn );
  eclic_mode_enable();
  // Set 'vector mode' so the timer interrupt uses the vector table.
  eclic_set_vmode( CLIC_INT_TMR );
  // Enable the timer interrupt (#7) with low priority and 'level'.
  eclic_enable_interrupt( CLIC_INT_TMR );
  eclic_set_irq_lvl_abs( CLIC_INT_TMR, 1 );
  eclic_set_irq_priority( CLIC_INT_TMR, 1 );
  // Set the timer's comparison value to (frequency / 1000).
  *( volatile uint64_t * )( TIMER_CTRL_ADDR + TIMER_MTIMECMP ) = ( TIMER_FREQ / 1000 );
  // Reset the timer value to zero.
  *( volatile uint64_t * )( TIMER_CTRL_ADDR + TIMER_MTIME ) = 0;
  // Re-enable interrupts globally.
  set_csr( mstatus, MSTATUS_MIE );

  // Set initial SPI pin positions.
  // Pull the 'chip select' pin high to de-select the display.
  GPIOB->ODR |=  ( 0x1 << 2 );
  // Pull the 'reset' pin low to reset the display.
  GPIOB->ODR &= ~( 0x1 << 1 );
  // Wait 100ms and pull the 'reset' pin high.
  delay_ms( 100 );
  GPIOB->ODR |=  ( 0x1 << 1 );
  // Pull the 'chip select' pin low to get the display's attention.
  GPIOB->ODR &= ~( 0x1 << 2 );

  // Send initialization commands to the display before starting DMA.
  // Software reset.
  display_mode( MODE_CMD );
  spi_w8( SPI1, 0x01 );
  delay_ms( 100 );
  // Display off.
  spi_w8( SPI1, 0x28 );
  // 'Inverted' color mode, so that 0 is 'off' and 1 is 'on':
  spi_w8( SPI1, 0x21 );
  // Color mode: 16bpp.
  spi_w8( SPI1, 0x3A );
  display_mode( MODE_DAT );
  spi_w8( SPI1, 0x05 );
  // Memory access control.
  display_mode( MODE_CMD );
  spi_w8( SPI1, 0x36 );
  display_mode( MODE_DAT );
  spi_w8( SPI1, 0x20 );
  // Exit sleep mode.
  display_mode( MODE_CMD );
  spi_w8( SPI1, 0x11 );
  delay_ms( 100 );
  // Display on.
  spi_w8( SPI1, 0x29 );
  delay_ms( 100 );
  // Set drawing window.
  // Column set
  spi_w8( SPI1, 0x2A );
  display_mode( MODE_DAT );
  spi_w16( SPI1, 1 );
  spi_w16( SPI1, TFT_W );
  // Row set
  display_mode( MODE_CMD );
  spi_w8( SPI1, 0x2B );
  display_mode( MODE_DAT );
  spi_w16( SPI1, 26 );
  spi_w16( SPI1, TFT_H + 25 );
  // Set 'write to RAM' mode.
  display_mode( MODE_CMD );
  spi_w8( SPI1, 0x2C );
  // Set 'data' transfer mode to start sending pixel data.
  display_mode( MODE_DAT );

  // Set 'LSBFIRST' mode to make it easier to set color values.
  SPI1->CR1          |=  ( SPI_CR1_LSBFIRST );
  // Enable the circular DMA transfer.
  DMA1_Channel3->CCR |=  ( DMA_CCR_EN );

  // Cycle the display through a few patterns.
  // For now, just solid colors, and set the on-board
  // LED to the current display color.
  #define PATTERN_DELAY ( 1000 )
  while( 1 ) {
    // TODO: Less code re-use. Also, the DMA transfer seems to send
    // each byte 'backwards', so the raw hex values are a little
    // tricky to figure out. Maybe seeting `LSBFIRST` could help?
    // Red (5 most-significant bits)
    for ( uint32_t i = 0; i < TFT_A; ++i ) {
      fb[ i ] = 0xF800;
    }
    GPIOA->ODR |=  ( 0x1 << 1 |
                     0x1 << 2 );
    GPIOC->ODR &= ~( 0x1 << 13 );
    delay_ms( PATTERN_DELAY );
    // Yellow
    for ( uint32_t i = 0; i < TFT_A; ++i ) {
      fb[ i ] = 0xFFE0;
    }
    GPIOA->ODR &= ~( 0x1 << 1 );
    GPIOA->ODR |=  ( 0x1 << 2 );
    GPIOC->ODR &= ~( 0x1 << 13 );
    delay_ms( PATTERN_DELAY );
    // Green (6 middle bits)
    for ( uint32_t i = 0; i < TFT_A; ++i ) {
      fb[ i ] = 0x03E0;
    }
    GPIOA->ODR &= ~( 0x1 << 1 );
    GPIOA->ODR |=  ( 0x1 << 2 );
    GPIOC->ODR |=  ( 0x1 << 13 );
    delay_ms( PATTERN_DELAY );
    // Purple
    for ( uint32_t i = 0; i < TFT_A; ++i ) {
      fb[ i ] = 0xF81F;
    }
    GPIOA->ODR |=  ( 0x1 << 1 );
    GPIOA->ODR &= ~( 0x1 << 2 );
    GPIOC->ODR &= ~( 0x1 << 13 );
    delay_ms( PATTERN_DELAY );
    // Blue (5 least-significant bits)
    for ( uint32_t i = 0; i < TFT_A; ++i ) {
      fb[ i ] = 0x001F;
    }
    GPIOA->ODR |=  ( 0x1 << 1 );
    GPIOA->ODR &= ~( 0x1 << 2 );
    GPIOC->ODR |=  ( 0x1 << 13 );
    delay_ms( PATTERN_DELAY );
  }
  return 0;
}

// System timer interrupt.
__attribute__( ( interrupt ) )
void eclic_mtip_handler( void ) {
  // Increment the global 'tick' value.
  systick++;
  // Reset the 'mtime' value to zero.
  *( volatile uint64_t * )( TIMER_CTRL_ADDR + TIMER_MTIME ) = 0;
}
