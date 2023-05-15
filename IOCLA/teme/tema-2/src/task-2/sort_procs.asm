%include "../include/io.mac"

struc proc
	.pid: resw 1
	.prio: resb 1
    .time: resw 1
endstruc

section .text
    global sort_procs

sort_procs:
    ;; DO NOT MODIFY
    enter 0,0
    pusha

    mov edx, [ebp + 8]      ; processes
    mov eax, [ebp + 12]     ; length
    ;; DO NOT MODIFY

    ;; Your code starts here

    ;; ebx is first loop index, frees eax to use for mul
    dec eax
    mov ebx, eax

first_loop:
    ;; ecx is second loop index
    mov ecx, ebx
	dec ecx

    ;; calculates the offset for the element in the first loop
    ;; and stores it in the 'edi' register
    mov edi, edx
    mov eax, proc_size
    ;; multiplies eax with the index to determine the offset
    mul ebx
    mov edx, edi
    mov edi, eax

second_loop:
    ;; calculates the offset for the element in the second loop
    ;; and stores it in the 'esi' register
    mov esi, edx
    mov eax, proc_size
    ;; multiplies eax with the index to determine the offset
    mul ecx
    mov edx, esi
    mov esi, eax

    ;; compares the two elements
    xor eax, eax
    mov al, byte [edx + edi + proc.prio]
    cmp al, byte [edx + esi + proc.prio]
    jg no_swap
    jl swap_procs
    mov ax, word [edx + edi + proc.time]
    cmp ax, word [edx + esi + proc.time]
    jg no_swap
    jl swap_procs
    mov ax, word [edx + edi + proc.pid]
    cmp ax, word [edx + esi + proc.pid]
    jge no_swap

swap_procs:
	;; uses xchg to interchange the two elements
    mov al, byte [edx + edi + proc.prio]
    xchg al, byte [edx + esi + proc.prio]
    mov byte [edx + edi + proc.prio], al

    mov ax, word [edx + edi + proc.pid]
    xchg ax, word [edx + esi + proc.pid]
    mov word [edx + edi + proc.pid], ax

    mov ax, word [edx + edi + proc.time]
    xchg ax, word [edx + esi + proc.time]
    mov word [edx + edi + proc.time], ax
no_swap:
	dec ecx
	cmp ecx, -1
	jnz second_loop
	dec ebx
    jnz first_loop

    ;; Your code ends here
    
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY