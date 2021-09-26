        .section ".text.boot"

        .global _start

_start:
        mrs x0, mpidr_el1
        and x0, x0, #3
	cbz x0, booting // hang all CPUs apart from the primary one
	b park_cpu

park_cpu:
        b park_cpu

booting:
        // here we go ahead to boot the core and jump into the kernel

        // initialize RAM
        ldr x1, =_start
        mov sp, x1

        // clean BSS section
        ldr x1, =__bss_start
        ldr w1, =__bss_size

bss_zero:
        cbz w2, jump_to_kernel
        str xzr, [x1], #8
        sub w2, w2, #1
        cbnz w2, bss_zero

jump_to_kernel:
        bl kmain
        b park_cpu // incase kmain returns
