        .globl getcurrentEL

getcurrentEL:
        mrs x0, CurrentEL
        lsr x0, x0, #2
        ret

        .globl enable_irq
enable_irq:
        msr daifclr, #2
        ret


        .globl disable_irq
disable_irq:
        msr daifset, #2
        ret
