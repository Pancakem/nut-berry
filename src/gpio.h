#ifndef GPIO_H
#define GPIO_H

#include "periph_base.h"

#define GPIO_BASE (BASE + 0x0020000)
#define GPFSEL0 GPIO_BASE
#define GPSET0 (GPIO_BASE + 0x1C)
#define GPCLR0 (GPIO_BASE + 0x28)
#define GPPUD (GPIO_BASE + 0x94)
#define GPPUDCLK0 (GPIO_BASE + 0x98)

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1
#define GPIO_FUN_ALT0 4
#define GPIO_FUN_ALT1 5
#define GPIO_FUN_ALT2 6
#define GPIO_FUN_ALT3 7
#define GPIO_FUN_ALT4 3
#define GPIO_FUN_ALT5 2

#define PULL_OFF 0
#define PULL_DOWN 1
#define PULL_UP 2

void gpio_set_mode(unsigned int pin, unsigned int function);
void gpio_pullupdown(unsigned int pin, unsigned int pud);
#endif
