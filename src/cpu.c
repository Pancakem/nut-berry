#include "cpu.h"

void cpu_nop(void) { asm volatile("nop"); }
