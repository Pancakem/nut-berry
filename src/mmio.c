#include "mmio.h"

unsigned int read_mmio(unsigned int addr) { return *(unsigned int *)addr; }

void write_mmio(unsigned int addr, unsigned int data) {
  *(volatile unsigned int *)addr = data;
}
