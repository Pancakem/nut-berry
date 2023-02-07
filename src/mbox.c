#include "mbox.h"
#include "gpio.h"

/* mailbox message buffer */
volatile unsigned int __attribute__((aligned(16))) mbox[36];

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

int mailbox_read(unsigned char channel) {
  int val = -1;

  while ((val & 0xF) != channel) {
    /* is there a response to our message */
    while ((mbx->status & MBOX_EMPTY) != 0)
      ;

    val = mbx->read;
  }

  // return upper 28 bits of val
  return val >> 4;
}

void mailbox_write(unsigned char channel, unsigned int value) {
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
int mbox_call(unsigned char ch) {

  // unsigned int r = (((unsigned int)((unsigned long)&mbox) & ~0xF) | (ch &
  // 0xF));

  mailbox_write(ch, (unsigned int)mbox);

  return mailbox_read(ch);

  /* /\* wait until we can write to the mailbox *\/ */
  /* do { */
  /*   asm volatile("nop"); */
  /* } while (*MBOX_STATUS & MBOX_FULL); */
  /* /\* write the address of our message to the mailbox with channel identifier
   * *\/ */
  /* *MBOX_WRITE = r; */
  /* /\* now wait for the response *\/ */
  /* while (1) { */
  /*   /\* is there a response? *\/ */
  /*   do { */
  /*     asm volatile("nop"); */
  /*   } while (*MBOX_STATUS & MBOX_EMPTY); */
  /*   /\* is it a response to our message? *\/ */
  /*   if (r == *MBOX_READ) */
  /*     /\* is it a valid successful response? *\/ */
  /*     return mbox[1] == MBOX_RESPONSE; */
  /* } */
  // return 0;
}
