#ifndef _PL011_UART_H_
#define _PL011_UART_H_

void pl011_uart_init();
void pl011_uart_send(unsigned int c);
char pl011_uart_getc();
void pl011_uart_puts(char *s);
void pl011_uart_hex(unsigned int d);

#endif
