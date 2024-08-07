#include "pl011_uart.h"
#include "gpio.h"
#include "mbox.h"
#include "util.h"

/* PL011 UART registers */
#define UART0_DR ((volatile unsigned int *)(MMIO_BASE + 0x00201000))
#define UART0_FR ((volatile unsigned int *)(MMIO_BASE + 0x00201018))
#define UART0_IBRD ((volatile unsigned int *)(MMIO_BASE + 0x00201024))
#define UART0_FBRD ((volatile unsigned int *)(MMIO_BASE + 0x00201028))
#define UART0_LCRH ((volatile unsigned int *)(MMIO_BASE + 0x0020102C))
#define UART0_CR ((volatile unsigned int *)(MMIO_BASE + 0x00201030))
#define UART0_IMSC ((volatile unsigned int *)(MMIO_BASE + 0x00201038))
#define UART0_ICR ((volatile unsigned int *)(MMIO_BASE + 0x00201044))

/**
 * Set baud rate and characteristics (115200 8N1) and map to GPIO
 */
void pl011_uart_init() {
  register unsigned int r;

  /* initialize UART */
  *UART0_CR = 0; // turn off UART0

  /* set up clock for consistent divisor values */
  /* mbox[0] = 9 * 4; */
  /* mbox[1] = MBOX_REQUEST; */
  /* mbox[2] = MBOX_TAG_SETCLKRATE; // set clock rate */
  /* mbox[3] = 12; */
  /* mbox[4] = 8; */
  /* mbox[5] = 2;       // UART clock */
  /* mbox[6] = 4000000; // 4Mhz */
  /* mbox[7] = 0;       // clear turbo */
  /* mbox[8] = MBOX_TAG_LAST; */
  /* mbox_call(MBOX_CH_PROP); */

  /* map UART0 to GPIO pins */
  r = *GPFSEL1;
  r &= ~((7 << 12) | (7 << 15)); // gpio14, gpio15
  r |= (4 << 12) | (4 << 15);    // alt0
  *GPFSEL1 = r;
  *GPPUD = 0; // enable pins 14 and 15
  r = 150;
  while (r--) {
    __asm__ volatile("nop");
  }
  *GPPUDCLK0 = (1 << 14) | (1 << 15);
  r = 150;
  while (r--) {
    __asm__ volatile("nop");
  }
  *GPPUDCLK0 = 0; // flush GPIO setup

  *UART0_ICR = 0x7FF; // clear interrupts
  *UART0_IBRD = 2;    // 115200 baud
  *UART0_FBRD = 0xB;
  *UART0_LCRH = 0x7 << 4; // 8n1, enable FIFOs
  *UART0_CR = 0x301;      // enable Tx, Rx, UART
}

/**
 * Send a character
 */
void pl011_uart_send(unsigned int c) {
  /* wait until we can send */
  do {
    __asm__ volatile("nop");
  } while (*UART0_FR & 0x20);
  /* write the character to the buffer */
  *UART0_DR = c;
}

/**
 * Receive a character
 */
char pl011_uart_getc() {
  char r;
  /* wait until something is in the buffer */
  do {
    __asm__ volatile("nop");
  } while (*UART0_FR & 0x10);
  /* read it and return */
  r = (char)(*UART0_DR);
  /* convert carrige return to newline */
  return r == '\r' ? '\n' : r;
}

/**
 * Display a string
 */
void pl011_uart_puts(char *s) {
  while (*s) {
    /* convert newline to carrige return + newline */
    if (*s == '\n')
      pl011_uart_send('\r');
    pl011_uart_send(*s++);
  }
}

/**
 * Display a binary value in hexadecimal
 */
void pl011_uart_hex(unsigned int d) {
  char hex[9];
  bin_to_hex(hex, d);
  pl011_uart_puts(hex);
}
