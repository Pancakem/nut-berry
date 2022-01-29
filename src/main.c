#include "mbox.h"
#include "pl011_uart.h"

void kmain() {
  pl011_uart_init();

  pl011_uart_puts("Booting Nut Berry!\n");

  mbox[0] = 8 * 4;        // length of the message
  mbox[1] = MBOX_REQUEST; // this is a request message

  mbox[2] = MBOX_TAG_GETSERIAL; // get serial number command
  mbox[3] = 8;                  // buffer size
  mbox[4] = 8;
  mbox[5] = 0; // clear output buffer
  mbox[6] = 0;

  mbox[7] = MBOX_TAG_LAST;

  // send the message to the GPU and receive answer
  if (mbox_call(MBOX_CH_PROP)) {
    pl011_uart_puts("Device serial: ");
    pl011_uart_hex(mbox[6]);
    pl011_uart_hex(mbox[5]);
    pl011_uart_puts("\n");
  } else {
    pl011_uart_puts("Unable to query serial!\n");
  }

  // echo everything back
  while (1) {
    pl011_uart_send(pl011_uart_getc());
  }
}
