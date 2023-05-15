%include "../include/io.mac"

    ;;
    ;;   TODO: Declare 'avg' struct to match its C counterpart
    ;;
struc avg
    .quo: resw 1
    .remain: resw 1
endstruc

struc proc
    .pid: resw 1
    .prio: resb 1
    .time: resw 1
endstruc

    ;; Hint: you can use these global arrays
section .data
	prio_result dd 0, 0, 0, 0, 0
    time_result dd 0, 0, 0, 0, 0

section .text
    global run_procs

run_procs:
    ;; DO NOT MODIFY

    push ebp
    mov ebp, esp
    pusha

    xor ecx, ecx

clean_results:
    mov dword [time_result + 4 * ecx], dword 0
    mov dword [prio_result + 4 * ecx],  0

    inc ecx
    cmp ecx, 5
    jne clean_results

    mov ecx, [ebp + 8]      ; processes
    mov ebx, [ebp + 12]     ; length
    mov eax, [ebp + 16]     ; proc_avg
    ;; DO NOT MODIFY
   
    ;; Your code starts here

    ;; 'esi' points to the first element of the average array
    mov esi, eax

    ;; 'edi' is the counter
    mov edi, ebx
    sub edi, 1
    xor ebx, ebx


get_total:
    ;; similar to sort_procs, calculates the offset
    mov eax, proc_size
    mul edi
    mov edx, eax

	;; stores in the given arrays the time and priorities
    xor eax, eax
    mov al, byte [ecx + edx + proc.prio]
    dec al
    mov bx, word [ecx + edx + proc.time]
    add dword [prio_result + 4 * eax], 1
    add dword [time_result + 4 * eax], ebx
    dec edi
    cmp edi, -1
    jne get_total

    ;; highest priority
    mov edi, 4

get_avg:

	;; if the proccess count is zero
    ;; pushes the values in the stack
    ;; otherwise, calculates the average
    ;; by division using 'div'
    ;; and puts the result in the stack
    xor edx, edx
    mov eax, [time_result + 4 * edi]
    mov ebx, [prio_result + 4 * edi]
    cmp ebx, 0
    jz push_avg
    mov edx, eax
    shr edx, 16
    div ebx

push_avg:
    mov word [esi + edi*avg_size + avg.quo], ax
    mov word [esi + edi*avg_size + avg.remain], dx
    dec edi
    cmp edi, -1
    jne get_avg

    ;; Your code ends here
    
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY