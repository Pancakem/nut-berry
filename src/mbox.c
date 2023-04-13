#include "mbox.h"
#include "gpio.h"
#include "printf.h"

#include <stdint.h>

/* mailbox message buffer */
volatile uint32_t __attribute__((aligned(16))) mbox[36];

#define VIDEOCORE_MBOX (MMIO_BASE + 0x0000B880)
#define MBOX_READ ((volatile unsigned int *)(VIDEOCORE_MBOX + 0x0))
#define MBOX_POLL ((volatile unsigned int *)(VIDEOCORE_MBOX + 0x10))
#define MBOX_SENDER ((volatile unsigned int *)(VIDEOCORE_MBOX + 0x14))
#define MBOX_STATUS ((volatile unsigned int *)(VIDEOCORE_MBOX + 0x18))
#define MBOX_CONFIG ((volatile unsigned int *)(VIDEOCORE_MBOX + 0x1C))
#define MBOX_WRITE ((volatile unsigned int *)(VIDEOCORE_MBOX + 0x20))
#define MBOX_RESPONSE 0x80000000
#define MBOX_FULL 0x80000000
#define MBOX_EMPTY 0x40000000

/* map struct to the base address  */
static mailbox_t *mbx = (mailbox_t *)VIDEOCORE_MBOX;

int mailbox_read(uint8_t channel) {
  uint32_t val;

  while (1) {
    while (mbx->status & MBOX_EMPTY)
      ;
    val = mbx->read;
    if ((val & 0xF) == channel)
      break;
  }

  // return upper 28 bits of val
  return val >> 4;
}

void mailbox_write(uint8_t channel, uint32_t value) {
  value &= ~(0xF);
  value |= channel;

  // wait till it is available
  while ((mbx->status & MBOX_FULL) != 0)
    ;

  mbx->write = value;
}

/**
 * Make a mailbox call. Returns 0 on failure, non-zero on success
 */
int mbox_call(uint8_t ch) {
  // uint32_t array_addr = 0;
  // printf("Mbox address %p", mbox);
  mailbox_write(ch, (uint32_t)mbox);
  return mailbox_read(ch);
}
