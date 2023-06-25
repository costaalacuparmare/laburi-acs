%include "../utils/printf32.asm"

section .data
	N dd 9 ; compute the sum of the first N fibonacci numbers
	print_format_1 db "Sum first %d", 10, 0
	print_format_2 db "fibo is %d", 10, 0

section .text
extern printf
global main
main:
	push ebp
	mov ebp, esp

	push dword [N]
	push print_format_1
	call printf
	add esp, 8

	; TODO: calculate the sum of first N fibonacci numbers
	;       (f(0) = 0, f(1) = 1)
	xor eax, eax     ;store the sum in eax
	xor esi, esi
	xor ebx, ebx		; 0
	xor edx, edx		; 1
	mov ecx, [N]		; 9
	inc edx
	inc esi
	inc eax
	mov ebx, edx		; 1
    mov edx, esi		; 1
	add eax, esi
fibo:
	xor esi, esi
	add esi, ebx		; 1
	add esi, edx		; 3
	mov ebx, edx		; 2
	mov edx, esi
	add eax, esi
	dec ecx
	cmp ecx, 0
	je print
	cmp ecx, 8
	jne l
	inc ecx
l:
	loop fibo
	; use loop instruction
print:
	push eax
	push print_format_2
	call printf
	add esp, 8
	xor eax, eax
	leave
	ret
