
    .text
    .global _PowerON_Reset
    .type _PowerON_Reset, @function

_PowerON_Reset:
# Initialize global pointer
    .option push
    .option norelax
    la		gp, __global_pointer$
    .option pop

# Initialize the stack and frame pointers
    la      sp, __stack
    mv 		s0, sp

# Initialize interrupt vectors
    li t0, 0x202
    csrw mtvec, t0    /* Set mtvec. */

    li t0, 0x100
    csrw mtvt, t0    /* Set mtvt. */

# Clear the bss segment
    la      a0, __bss
    la      a2, __ebss
    sub     a2, a2, a0
    li      a1, 0
    call    memset

# Init the data segment
    la      a0, __datastart
    la      a1, __romdatastart
    la      a2, __romdatacopysize
    call    memcpy

    li      a0, 0                  # a0 = argc
    li      a1, 0                  # a1 = argv
    li      a2, 0                  # a2 = envp = NULL
    call    main

    .size  _PowerON_Reset, .-_PowerON_Reset

