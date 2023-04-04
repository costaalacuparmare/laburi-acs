%include "printf32.asm"

section .text
    global main
    extern printf

main:
    ;cele doua multimi se gasesc in eax si ebx
    mov eax, 139
    mov ebx, 169
    PRINTF32 `%u\n\x0`, eax ; afiseaza prima multime
    PRINTF32 `%u\n\x0`, ebx ; afiseaza cea de-a doua multime

    ; TODO1: reuniunea a doua multimi
    mov edx, eax
    or edx, ebx
    PRINTF32 `Reuniunea este: \x0`
    PRINTF32 `%u\n\x0`, edx

    ; TODO2: adaugarea unui element in multime
    or eax, 0x300
        PRINTF32 `Adaugare element 0x300: \x0`
    PRINTF32 `%u\n\x0`, eax

    ; TODO3: intersectia a doua multimi
    mov edx, eax
    and edx, ebx
    PRINTF32 `Intersectia este: \x0`
    PRINTF32 `%u\n\x0`, edx

    ; TODO4: complementul unei multimi
    mov edx, eax
    not edx
    PRINTF32 `Complementul multimii \x0`
    PRINTF32 `%u\n\x0`, edx

    ; TODO5: eliminarea unui element
    mov edx, 1
    shl edx, 3
    not edx
    and eax, edx
    PRINTF32 `Dupa eliminarea unui element: \x0`
    PRINTF32 `%u\n\x0`, eax

    ; TODO6: diferenta de multimi EAX-EBX
    mov eax, 139
    mov ebx, 169
    not ebx
    and eax, ebx
    PRINTF32 `Diferenta eax si ebx initiale: \x0`
    PRINTF32 `%u\n\x0`, eax

    xor eax, eax
    ret