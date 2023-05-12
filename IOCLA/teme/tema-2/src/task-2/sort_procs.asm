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
    sub eax, 1
    ; ebx = First loop index
    mov ebx, eax
    ; eax = Used for multiplication
first_loop:
    ; ecx = Second loop index
    mov ecx, ebx
    sub ecx, 1

    ; esi = Used to calculate the offset for the element in the first loop

    mov esi, edx
    mov eax, proc_size
    mul ebx
    mov edx, esi
    mov esi, eax
second_loop:
      ; edi = Used to calculate the offset for the element in the second loop

      mov edi, edx
      mov eax, proc_size
      mul ecx
      mov edx, edi
      mov edi, eax

      xor eax, eax
      mov al, byte [edx + esi + proc.prio]
      cmp al, byte [edx + edi + proc.prio]
      jg skip_swap
      jl swap
      mov ax, word [edx + esi + proc.time]
      cmp ax, word [edx + edi + proc.time]
      jg skip_swap
      jl swap
      mov ax, word [edx + esi + proc.pid]
      cmp ax, word [edx + edi + proc.pid]
      jge skip_swap
swap:
      mov al, byte [edx + esi + proc.prio]
      xchg al, byte [edx + edi + proc.prio]
      mov [edx + esi + proc.prio], al

      mov ax, word [edx + esi + proc.pid]
      xchg ax, word [edx + edi + proc.pid]
      mov [edx + esi + proc.pid], ax

      mov ax, word [edx + esi + proc.time]
      xchg ax, word [edx + edi + proc.time]
      mov [edx + esi + proc.time], ax
skip_swap:
      sub ecx, 1
      jns second_loop
    sub ebx, 1
    jnz first_loop



    ;; Your code ends here
    
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY