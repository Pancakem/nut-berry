#include "gpio.h"
#include "cpu.h"
#include "mmio.h"

void gpio_set_mode(uint32_t pin, uint32_t function) {
  uint32_t reg_offset = (pin / 10) << 2;
  uint32_t bit = (pin % 10) * 3; // bit offset
  volatile uint32_t val = read_mmio(GPFSEL0 + reg_offset);
  write_mmio(GPFSEL0 + reg_offset,
             ((val & ~(0x7 << bit)) | ((function & 0x7) << bit)));
}

void gpio_pullupdown(uint32_t pin, uint32_t pud) {
  write_mmio(GPPUD, pud);
  spin_for_cpu_cyles(150);

  write_mmio(GPPUDCLK0 + (pin >> 5), (1 << (pin & 0x1F)));
  spin_for_cpu_cyles(150);

  write_mmio(GPPUD, 0);
  write_mmio(GPPUDCLK0 + (pin >> 5), 0);
}
