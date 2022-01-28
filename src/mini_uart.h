#ifndef MINI_UART_H
#define MINI_UART_H

#include "periph_base.h"

#define AUX_BASE (BASE + 0x0021500)
#define AUX_ENABLES (AUX_BASE + 4)
#define AUX_MU_IO_REG (AUX_BASE + 0x40)
#define AUX_MU_IER_REG (AUX_BASE + 0x44)
#define AUX_MU_IIR_REG AUX_BASE + 0x48
#define AUX_MU_LCR_REG (AUX_BASE + 0x4C)
#define AUX_MU_MCR_REG (AUX_BASE + 0x50)
#define AUX_MU_LSR_REG (AUX_BASE + 0x54)
#define AUX_MU_CNTL_REG (AUX_BASE + 0x60)
#define AUX_MU_BAUD_REG (AUX_BASE + 0x68)
#define AUX_UART_CLOCK 500000000
#define UART_MAX_QUEUE 16 * 1024

void mini_uart_init(void);
unsigned int mini_uart_is_full(void);
unsigned int mini_uart_is_empty(void);
void mini_uart_write_byte(unsigned char ch);
void mini_uart_write_str(char *buffer);
char mini_uart_read(void);
#endif
