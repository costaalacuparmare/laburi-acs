%include "./utils/printf32.asm"
extern printf

section .data

limit dd  120
len equ   10

section .bss
    ; TODO a: Reserve space for an array of `len` integers. The array name is `int_arr`
    int_arr resd len
section .text
global main

main:
    push ebp
    mov ebp, esp

    ;TODO a: Generate first `len` elements of `int_arr` defined as follows:
    ; int_arr[i] = 17 * i + 3
    
    xor ecx, ecx
build_loop:
    xor eax, eax
    mov edi, int_arr
    mov al, 17
    mul cl
    add ax, 3
    add [edi + 4*ecx], ax
    inc ecx
    cmp ecx, len
    jl build_loop

    xor ecx, ecx
print_loop:
    mov edx, int_arr
    PRINTF32 `%u \x0`, [edx + 4*ecx]
    inc ecx
    cmp ecx, len
    jl print_loop
    ; TODO b: Count the number of elements strictly smaller than number pointed by `limit`

    xor eax, eax
    xor ecx, ecx
    xor edx, edx
count_loop:

    mov edx, int_arr
    mov esi, [limit]
    cmp [edx + 4*ecx], esi
    jge no_add
    inc eax
no_add:
    inc ecx
    cmp ecx, len
    jl count_loop
    PRINTF32 `\nCount: %d\n\x0`, eax
    ; TODO c: Find and print the smallest number strictly greater than number pointed by `limit`
    
    xor eax, eax
    xor ecx, ecx
    xor edx, edx
    xor esi, esi

find_loop:
    mov edx, int_arr
    mov esi, [limit]
    mov eax, [edx + 4*ecx]
    inc ecx
    cmp eax, esi
    jle find_loop
    PRINTF32 `Number: %d\n\x0`, eax
    ; Return 0.
    xor eax, eax
    leave
    ret
