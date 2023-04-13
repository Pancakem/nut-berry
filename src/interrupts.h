#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "gpio.h"
#include <stdint.h>

#define ARM_TIMER_IRQ (1 << 0)
#define ARM_MAILBOX_IRQ (1 << 1)
#define ARM_DOORBELL_0__IRQ (1 << 2)
#define ARM_DOORBELL_1_IRQ (1 << 3)
#define ARM_GPU_0_HALTED_IRQ (1 << 4)
#define ARM_GP_1_HALTED_IRQ (1 << 5)
#define ACCESS_ERROR_1_IRQ (1 << 6)
#define ACCESS_ERROR_0_IRQ (1 << 7)

#endif
