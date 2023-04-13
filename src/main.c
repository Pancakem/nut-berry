#include "framebuffer.h"
#include "mbox.h"
#include "pl011_uart.h"
#include "printf.h"
#include "timer.h"
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

char *uname() { return "\nNut Berry"; }

void kmain() {
  pl011_uart_init();
  init_printf(NULL, putc);

  printf("Booting Nut Berry!\n");

  char serial[20] = {0};
  if (device_serial(serial) == 0) {
    printf("Device serial: %s\n", serial);
  } else {
    printf("Unable to query serial!\n");
  }

  int el = getcurrentEL();
  printf("Current EL is %d\n", el);

  printf("\nEnabling timer\n");
  enable_timer();

  framebuffer_t fb;
  printf("Initializing framebuffer\n");
  // int res =
  init_framebuffer(&fb);
  /* if (res != 0) */
  /*   printf("framebuffer init failed %d\n", res); */
  /* else */
  /* printf("Resolution:\n \t Height: %d\n\t Width: %d\n\t Pitch: %d",
   * fb.height, */
  /*        fb.width, fb.pitch); */

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

    if (strcmp(command, "uname") == 0)
      printf(uname());
    memzero(command, 10);
  }
}
