# Introduction

Nut-berry is a Raspberry Pi 3 kernel.

## The Hardware


## Boot process
The BCM2385 has GPU that is the first to be woken up. This GPU has a bootloader that reads the contents of a FAT32 partition of an SD card. The bootloader reads the necessary configuration files and 'prepares' them.
Then it boots up the CPU waking one core in a working state that is ready to start loading a kernel - the kernel image read from the card, in our case `kernel8.img`.