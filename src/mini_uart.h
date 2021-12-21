#ifndef UART_H
#define UART_H

#include "periph_base.h"
#include <stdint.h>

enum {
  AUX_BASE = BASE + 0x00215000,
  AUX_ENABLES = AUX_BASE + 4,
  AUX_MU_IO_REG = AUX_BASE + 0x40,
  AUX_MU_IER_REG = AUX_BASE + 0x44,
  AUX_MU_IIR_REG = AUX_BASE + 0x48,
  AUX_MU_LCR_REG = AUX_BASE + 0x4C,
  AUX_MU_MCR_REG = AUX_BASE + 0x50,
  AUX_MU_LSR_REG = AUX_BASE + 0x54,
  AUX_MU_CNTL_REG = AUX_BASE + 0x60,
  AUX_MU_BAUD_REG = AUX_BASE + 0x68,
  AUX_UART_CLOCK = 500000000,
  UART_MAX_QUEUE = 16 * 1024
};

void mini_uart_init(void);
uint32_t mini_uart_is_full(void);
uint32_t mini_uart_is_empty(void);
void mini_uart_write_byte(unsigned char ch);
void mini_uart_write_str(char *buffer);
char mini_uart_read(void);
#endif
