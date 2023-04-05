%include "printf32.asm"

section .text
    global main
    extern printf

main:
    mov ecx, 3       ; vrem sa aflam al N-lea numar; N = 7
    mov eax, 1
    mov ebx, 1
    sub ecx, 1
fibonacci:
    sub ecx, 1
    test ecx, ecx
    je print

    add eax, ebx
    xchg eax, ebx
    jmp fibonacci

print:
    PRINTF32 `%d\n\x0`, ebx
    xor eax, eax
    ret
