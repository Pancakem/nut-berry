#ifndef MAILBOX_H
#define MAILBOX_H

#include "periph_base.h"

#define MAILBOX_BASE (BASE + 0xB880)
#define READ (MAILBOX_BASE + 0x00)
#define STATUS (MAILBOX_BASE + 0x18)
#define WRITE (MAILBOX_BASE + 0x20)

#define EMPTY 0x40000000
#define FULL 0x80000000
#define RESPONSE 0x80000000

int mailbox_call(unsigned int *message, unsigned char channel);

#endif
