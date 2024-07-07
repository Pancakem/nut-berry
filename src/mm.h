#ifndef __MM_H__
#define __MM_H__

#include <stdint.h>

extern void memzero(void *src, uint32_t size);
void mmio_write(volatile unsigned int *addr, unsigned int value);
unsigned int mmio_read(volatile unsigned int *addr);

#endif
