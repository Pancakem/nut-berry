#include "timer.h"
#include "mm.h"
#include "pl011_uart.h"
#include "printf.h"
#include "util.h"

const unsigned int interval = 200000;
unsigned int curVal = 0;

void enable_timer(void) {
  curVal = mmio_read((unsigned int *)TIMER_CLO);
  curVal += interval;
  mmio_write((unsigned int *)TIMER_C1, curVal);
}

void handle_timer_irq(void) {
  curVal += interval;
  mmio_write((unsigned int *)TIMER_C1, curVal);
  mmio_write((unsigned int *)TIMER_CS, TIMER_CS_M1);
  printf("Timer interrupt received\n\r");
}
