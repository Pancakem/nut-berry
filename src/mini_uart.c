#include "mini_uart.h"
#include "cpu.h"
#include "gpio.h"
#include "mmio.h"

void mini_uart_init() {
  write_mmio(AUX_ENABLES, 1); // enable UART1
  write_mmio(AUX_MU_IER_REG, 0);
  write_mmio(AUX_MU_CNTL_REG, 0);
  write_mmio(AUX_MU_LCR_REG, 3); // 8 bits
  write_mmio(AUX_MU_MCR_REG, 0);
  write_mmio(AUX_MU_IER_REG, 0);
  write_mmio(AUX_MU_IIR_REG, 0xC6); // disable interrupts
  unsigned int baud = (AUX_UART_CLOCK / (115200 * 8)) - 1;
  write_mmio(AUX_MU_BAUD_REG, baud);
  gpio_set_mode(14, GPIO_FUN_ALT5);
  gpio_set_mode(15, GPIO_FUN_ALT5);
  write_mmio(AUX_MU_CNTL_REG, 3); // enable RX/TX
}

unsigned int mini_uart_is_full() { return read_mmio(AUX_MU_LSR_REG) & 0x20; }

void mini_uart_write_byte(unsigned char ch) {
  while (!mini_uart_is_full())
    ;
  write_mmio(AUX_MU_IO_REG, (unsigned int)ch);
}

void mini_uart_write_str(char *bytes) {
  while (*bytes) {
    if (*bytes == '\n')
      mini_uart_write_byte('\r');
    mini_uart_write_byte(*bytes++);
  }
}

unsigned int mini_uart_is_empty(void) {
  return read_mmio(AUX_MU_LSR_REG) & 0x01;
}

char mini_uart_read(void) {
  while (!mini_uart_is_empty())
    ;
  return read_mmio(AUX_MU_IO_REG) & 0xFF;
}
