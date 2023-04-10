%include "../utils/printf32.asm"

section .text
extern printf
global main
main:
    push ebp
    mov ebp, esp

    mov eax, 211    ; to be broken down into powers of 2
    mov ebx, 1      ; stores the current power
    cmp eax, ebx
    jl print

print:
    PRINTF32 `%u\n\x0`, ebx
    shl ebx, 1
    cmp eax, ebx
    jge print

    leave
    ret
