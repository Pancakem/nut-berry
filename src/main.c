#include "framebuffer.h"
#include "mbox.h"
#include "pl011_uart.h"
#include "util.h"

int device_serial(char *serial) {
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
    char val[9];
    bin_to_hex(val, mbox[6]);
    strcat(serial, val);
    bin_to_hex(val, mbox[5]);
    strcat(serial, val);
    return 0;
  }

  return 1;
}

char *uname() { return "Nut Berry"; }

void kmain() {
  pl011_uart_init();

  pl011_uart_puts("Booting Nut Berry!\n");

  char serial[20] = {0};
  if (device_serial(serial) == 0) {
    pl011_uart_puts("Device serial: ");
    pl011_uart_puts(serial);
    pl011_uart_puts("\n");
  } else {
    pl011_uart_puts("Unable to query serial!\n");
  }

  struct framebuffer fb;
  pl011_uart_puts("Initializing framebuffer");
  init_framebuffer(&fb);

  // echo everything back
  while (1) {
    char command[10] = {0};
    unsigned int i = 0;
    while (1) {
      char str = pl011_uart_getc();
      if (str != '\n') {
        command[i] = str;
        i++;
        continue;
      }
      break;
    }

    /* pl011_uart_puts("Echoing "); */
    /* pl011_uart_send(str); */
    if (strcmp(command, "uname") == 0)
      pl011_uart_puts(uname());
  }
}
