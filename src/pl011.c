#include "pl011.h"
#include "cpu.h"
#include "gpio.h"
#include "mailbox.h"
#include "mmio.h"
#include <assert.h>

void map_pl011_uart(void) {
  // set GPIO 14 and 15 to altfunc0
  gpio_set_mode(14, GPIO_FUN_ALT0);
  gpio_set_mode(15, GPIO_FUN_ALT0);
  gpio_pullupdown(14, PULL_OFF);
  gpio_pullupdown(15, PULL_OFF);
}

void pl011_uart_flush(void) {
  // spin until busy bit is cleared
  while (read_mmio(FR) & PL011_BUSY) {
    cpu_nop();
  }
}

void pl011_uart_init(void) {
  write_mmio(CR, 0);

  /* unsigned int message[16]; */
  /* message[0] = 9 * 4; */
  /* message[1] = 0; */
  /* message[2] = 0x38002; // set clock rate */
  /* message[3] = 12; */
  /* message[4] = 8; */
  /* message[5] = 2;       // UART clock */
  /* message[6] = 4000000; // 4Mhz */
  /* message[7] = 0;       // end tag */
  /* mailbox_call(message, 8); */

  map_pl011_uart();
  pl011_uart_flush();

  // clear all pending interrupts
  write_mmio(ICR, 0x7FF);

  write_mmio(IBRD, 2);
  write_mmio(FRBD, 0xB);

  // 8 bit and enable fifo
  write_mmio(LCRH, LCR_8_BITS | LCR_FIFO_EN);

  // Turn on UART
  write_mmio(CR, CR_UART_ENABLE | CR_TX_ENABLE | CR_RX_ENABLE);
}

void pl011_uart_write_byte(unsigned char c) {
  // spin while tx fifo is full
  while (read_mmio(FR) & PL011_TX_FIFO_FULL) {
    cpu_nop();
  }

  write_mmio(DR, (unsigned int)c);
}
unsigned char pl011_uart_read_byte(void) {
  // wait until char is received
  while (read_mmio(FR) & PL011_RX_FIFO_EMPTY) {
    cpu_nop();
  }

  unsigned char c = (unsigned char)read_mmio(DR);
  if (c == '\r') {
    c = '\n';
  }

  return c;
}
void pl011_uart_write_str(char *str) {
  while (*str) {
    pl011_uart_write_byte(*str++);
  }
}
