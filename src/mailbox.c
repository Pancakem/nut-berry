#include "mailbox.h"
#include "cpu.h"
#include "mmio.h"
#include <assert.h>

int mailbox_call(unsigned int *message, unsigned char channel) {
  unsigned int addr = (unsigned int)message;
  addr &= ~0xF;
  addr |= channel & 0xF;

  // wait while status full
  while (read_mmio(STATUS) & FULL)
    cpu_nop();

  write_mmio(WRITE, addr);

  while (1) {
    // wait while status is empty
    while (read_mmio(STATUS) & EMPTY)
      cpu_nop();

    if (addr == read_mmio(READ))
      return message[1] == RESPONSE;
  }
}
