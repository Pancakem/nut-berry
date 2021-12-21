#ifndef GPIO_H
#define GPIO_H

#include "periph_base.h"
#include <stdint.h>

enum {
  GPFSEL0 = BASE + 0x00200000,
  GPFSEL1 = BASE + 0x00200004,
  GPSET0 = BASE + 0x0020001C,
  GPCLR0 = BASE + 0x00200028,
  GPPUD = BASE + 0x00200094,
  GPPUDCLK0 = BASE + 0x00200098,
};

enum {
  GPIO_INPUT = 0,
  GPIO_OUTPUT = 1,
  GPIO_FUN_ALT0 = 4,
  GPIO_FUN_ALT1 = 5,
  GPIO_FUN_ALT2 = 6,
  GPIO_FUN_ALT3 = 7,
  GPIO_FUN_ALT4 = 3,
  GPIO_FUN_ALT5 = 2,
  GPIO_MAX_PIN = 53,

};

enum {
  Pull_Off = 0,
  Pull_Down = 1,
  Pull_Up = 2,
};

void gpio_set_mode(uint32_t pin, uint32_t function);
void gpio_pullupdown(uint32_t pin, uint32_t pud);
#endif
