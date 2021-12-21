#ifndef MEMORY_MAPPED_IO_H
#define MEMORY_MAPPED_IO_H

unsigned int read_mmio(unsigned int addr);
void write_mmio(unsigned int addr, unsigned int data);

#endif
