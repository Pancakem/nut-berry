#include "irq.h"
#include "mbox.h"
#include "mm.h"
#include "pl011_uart.h"
#include "printf.h"
#include "screen.h"
#include "timer.h"
#include "util.h"

int device_serial(char *serial) {
  memcpy(serial, "serial<>number", 15);
  return 0;
}

char *uname() { return "\nNut Berry"; }

void kmain() {
  pl011_uart_init();
  init_printf(NULL, putc);

  printf("Booting Nut Berry!\n");

  /* printf("Sizeof mailbox_t %d\n", sizeof(mailbox_t)); */

  char serial[20] = {0};
  if (device_serial(serial) == 0) {
    printf("Device serial: %s\n", serial);
  } else {
    printf("Unable to query serial!\n");
  }

  int el = getcurrentEL();
  printf("Current EL is %d\n", el);

  printf("Initializing IRQ Vector\n");
  irq_vector_init();

  printf("Initializing timer\n");
  enable_timer();

  printf("Initializing screen\n");
  init_screen();

  screen_print("Hello from Nut Berry\n");

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
