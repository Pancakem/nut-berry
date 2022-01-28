#include "gpio.h"
#include "cpu.h"
#include "mmio.h"

void gpio_set_mode(unsigned int pin, unsigned int function) {
  unsigned int reg_offset = (pin / 10) << 2;
  unsigned int bit = (pin % 10) * 3; // bit offset
  volatile unsigned int val = read_mmio(GPFSEL0 + reg_offset);
  write_mmio(GPFSEL0 + reg_offset,
             ((val & ~(0x7 << bit)) | ((function & 0x7) << bit)));
}

void gpio_pullupdown(unsigned int pin, unsigned int pud) {
  write_mmio(GPPUD, pud);
  delay(150);

  write_mmio(GPPUDCLK0 + (pin >> 5), (1 << (pin & 0x1F)));
  delay(150);

  write_mmio(GPPUD, pud);
  write_mmio(GPPUDCLK0 + (pin >> 5), 0);
}
