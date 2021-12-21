#include "pl011.h"

void kmain() {
  pl011_uart_init();
  pl011_uart_write_str("Booting Nut Berry on Rpi3\n");
  pl011_uart_write_str("Hello Universe!");

  while (1) {
    pl011_uart_write_byte(pl011_uart_read_byte());
  }
}
