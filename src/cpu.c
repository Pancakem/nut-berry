#include "cpu.h"

void spin_for_cpu_cyles(unsigned long ms) {
  for (; ms > 0; ms--) {
    asm("nop");
  }
}

void cpu_nop(void) { asm("nop"); }
