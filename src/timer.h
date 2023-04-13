#ifndef TIMER_H
#define TIMER_H

#include "gpio.h"

/* #include <stdint.h> */

/* #define ARM_TIMER_BASE (MMIO_BASE + 0xB400) */

/* #define ARM_TIMER_CTRL_23Bit (1 << 1) */

/* #define ARM_TIMER_CTRL_PRESCALE_1 (0 << 2) */
/* #define ARM_TIMER_CTRL_PRESCALE_16 (1 << 2) */
/* #define ARM_TIMER_CTRL_PRESCALE_256 (2 << 2) */

/* #define ARM_TIMER_CTRL_INT_ENABLE (1 << 5) */
/* #define ARM_TIMER_CTRL_INT_DISABLE (0 << 5) */

/* #define ARM_TIMER_CTRL_ENABLE (1 << 7) */
/* #define ARM_TIMER_CTRL_DISABLE (0 << 7) */

/* #define ARM_TIMER_REGISTER_BASE 0x7E00B000 */

/* // timer registers */
/* typedef struct { */
/*   /\* the timer load register sets the time for the timer to count down *\/
 */
/*   volatile uint32_t load; */
/*   /\* this is a read-only register that the value of the timer register load
 * is */
/*    * put into *\/ */
/*   volatile uint32_t value; */
/*   /\* used to enable/disable timer, timer interrupt, prescale etc *\/ */
/*   volatile uint32_t control; */
/*   /\* write-only register that when wrote to clears the interrupt-pending bit
 * *\/ */
/*   volatile uint32_t irq_clear; */
/*   /\* read-only register that shows the status of the pending bit. */
/*      the interrupt pending bit is set each time the value register is counted
 */
/*      down to 0 */
/*    *\/ */
/*   volatile uint32_t raw_irq; */
/*   /\* read-only register that shows the status of the interrupt signal *\/ */
/*   volatile uint32_t masked_irq; */
/*   /\* is a copy of the timer load register. The difference is that a write to
 */
/*      this register does not trigger an immediate reload of the timer value */
/*      register, instead the timer load register value is only accessed if the
 */
/*      value has finished counting down to 0 */
/*   *\/ */
/*   volatile uint32_t reload; */
/*   /\* has a 10-bit R/W pre-divider value */
/*      timer_clock = apb_clock/(pre-divider+1) */
/*    *\/ */
/*   volatile uint32_t predivider; */
/*   /\* is a 32-bit read-only register, enabled by setting bit 9 */
/*      of the timer control register */
/*    *\/ */
/*   volatile uint32_t free_running_counter; */
/* } arm_timer_t; */

/* void enable_timer(void); */
/* arm_timer_t *get_arm_timer(void); */
/* uint32_t read_milliseconds(void); */
/* void handle_timer_irq(void); */

#define TIMER_CS (MMIO_BASE + 0x00003000)
#define TIMER_CLO (MMIO_BASE + 0x00003004)
#define TIMER_CHI (MMIO_BASE + 0x00003008)
#define TIMER_C0 (MMIO_BASE + 0x0000300C)
#define TIMER_C1 (MMIO_BASE + 0x00003010)
#define TIMER_C2 (MMIO_BASE + 0x00003014)
#define TIMER_C3 (MMIO_BASE + 0x00003018)

#define TIMER_CS_M0 (1 << 0)
#define TIMER_CS_M1 (1 << 1)
#define TIMER_CS_M2 (1 << 2)
#define TIMER_CS_M3 (1 << 3)

void enable_timer(void);
void handle_timer_irq(void);

#endif
