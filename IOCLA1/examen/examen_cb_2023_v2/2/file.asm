section .data
    int_fmt: db "%d", 10, 0
    newline_fmt: db 10, 0
	global_var: dw 6

section .text
global main
extern printf
extern scanf
extern stdout
extern fprintf

; TODO b: Define a function that returns the sum of all elements <= func argument
;         e.g. get_sum(10) = 55
get_sum:
    push ebp
    mov ebp, esp
	mov eax, [ebp + 8]
	cmp eax, 0
	jle end
	xor edx, edx
	xor ebx, ebx
sum_loop:
	inc ebx
	add edx, ebx
	cmp ebx, eax
	jne sum_loop
	jmp end2
end:
	mov eax, 0
end2:
	mov eax, edx
    leave
    ret

; TODO d: Define a funcion that expects an argument and will return the number from
;         the Fibonacci sequence placed at the received index
;         e.g. get_fib(6) = 8 (Fib. seq: 1, 1, 2, 3, 5, 8)
;              get_fib(2) = 1 (Fib. seq: 1, 1)
get_fib:
    push ebp
    mov ebp, esp

    mov ecx, [ebp + 8]      ; idx

    cmp ecx, 0
    jle end_d

    mov eax, 1
    mov ebx, 1
    sub ecx, 1
fibonacci:
    sub ecx, 1
    test ecx, ecx
    je end_pbn

    add eax, ebx
    xchg eax, ebx
    jmp fibonacci

end_d:
	mov eax, 0
	leave
    ret

end_pbn:
	mov eax, ebx
    leave
    ret

main:
    push ebp
    mov ebp, esp

    ; TODO a: Read 2 integers, save them on the stack and print them

	;push global_var
	;push int_fmt
	;call scanf
	;add esp, 8

	mov eax, 6
	mov ebx, 7
	push ebx
	push eax

	push eax
	push int_fmt
	call printf
	add esp, 8

	push ebx
	push int_fmt
	call printf
	add esp, 8

    ; TODO c: Call get_sum with the 2 numbers you saved on the stack
    pop ebx
    push ebx
    push ebx
    call get_sum
    add esp, 4

	mov ecx, dword [stdout]

   	push eax
   	push int_fmt
   	push ecx
   	call fprintf
   	add esp, 12

    pop eax
    pop ebx
    push ebx
    push eax
    push ebx
    call get_sum
    add esp, 4

	mov ecx, dword [stdout]

   	push eax
   	push int_fmt
   	push ecx
   	call fprintf
   	add esp, 12

    ;         Print the results using **`fprintf`**.
    ;         Check the arguments `fprintf` expects (man fprintf).
    ; TODO d: Call get_fib with the 2 numbers you saved on the stack.
    ;         Print the results after that.
	pop ebx
	push ebx
	call get_fib
	add esp, 4

	push eax
	push int_fmt
	call printf
	add esp, 8

	pop ebx
	push ebx
	call get_fib
	add esp, 4

	push eax
	push int_fmt
	call printf
	add esp, 8

    ; Return 0.
    xor eax, eax
    leave
    ret
