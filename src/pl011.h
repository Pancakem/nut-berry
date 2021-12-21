#ifndef PLL011_H
#define PLL011_H

#include "periph_base.h"

enum {
  UART_BASE = BASE + 0x20100,
  DR = UART_BASE,
  FR = UART_BASE + 0x18,
  IBRD = UART_BASE + 0x24,
  FRBD = UART_BASE + 0x28,
  LCRH = UART_BASE + 0x2C,
  CR = UART_BASE + 0x30,
  ICR = UART_BASE + 0x44,
};

// FR
#define PL011_BUSY (1 << 3)
#define PL011_RX_FIFO_EMPTY (1 << 4)
#define PL011_TX_FIFO_FULL (1 << 5)

// LCRH
#define LCR_BREAK (1 << 0)
#define LCR_PARITY_EN (1 << 1)
#define LCR_EVEN_PARITY (1 << 2)
#define LCR_2_STOP (1 << 3)
#define LCR_FIFO_EN (1 << 4)
#define LCR_8_BITS (3 << 5)
#define LCR_STICK_PARITY (1 << 7)

// CR
#define CR_UART_ENABLE (1 << 0)
#define CR_LOOPBACK (1 << 7)
#define CR_TX_ENABLE (1 << 8)
#define CR_RX_ENABLE (1 << 9)
#define CR_RTS (1 << 11)

void map_pl011_uart(void);
void pl011_uart_init(void);
void pl011_uart_flush(void);
void pl011_uart_write_byte(unsigned char);
unsigned char pl011_uart_read_byte(void);
void pl011_uart_write_str(char *str);
#endif
