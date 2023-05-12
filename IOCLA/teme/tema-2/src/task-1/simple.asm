%include "../include/io.mac"

section .text
    global simple
    extern printf

simple:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     ecx, [ebp + 8]  ; len
    mov     esi, [ebp + 12] ; plain
    mov     edi, [ebp + 16] ; enc_string
    mov     edx, [ebp + 20] ; step

    ;; DO NOT MODIFY
   
    ;; Your code starts here
    xor eax, eax
    mov ebx, [esi]

loop_start:
	;; verifies is string is gone through
	cmp eax, ecx
	je loop_end
	mov ebx, [esi+eax]
	add bl, dl
	;; verifies in case of surpassing Z in ASCII
	cmp bl, "Z"
	jng loop_cont
	;; used to loop around the ASCII between A and Z
	sub bl, "Z" - "A" + 1

loop_cont:
	mov byte [edi+eax], bl
	inc eax
	jmp loop_start

loop_end:

    ;; Your code ends here
    
    ;; DO NOT MODIFY

    popa
    leave
    ret
    
    ;; DO NOT MODIFY
