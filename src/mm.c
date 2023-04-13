#include "mm.h"

void mmio_write(volatile unsigned int *addr, unsigned int value) {
  *addr = value;
}

unsigned int mmio_read(volatile unsigned int *addr) { return *addr; }
