%include "../utils/printf32.asm"
extern printf

section .data

int_arr dd 11, 20, 39, 57, 99, 100, 88, 19, 29, 42
len equ 10
limit dd 3000
format db '%d ', 0
newline db 10, 0

section .bss
	; TODO a: Reserve space for an array of `len` integers. The array name is `res_arr`
res_arr resb len
section .text
global main

main:
	push ebp
	mov ebp, esp

	; TODO a: Fill in the first `len` elements of `res_array` using the folloing formula:
	; res_arr[i] = 65 * int_arr[i] + 7
	; Print res_arr with all elements on the same line separated by a space
	xor ebx, ebx
	mov ecx, 7
loop_a:
	mov eax, 65
	mov edx, dword [int_arr + 4 * ebx]
	cmp ebx, len
	je check_a
	mul edx
	add eax, ecx
	mov [res_arr + 4 * ebx], eax
	inc ebx
	jmp loop_a

check_a:
	xor ebx, ebx

check_a_loop:
	push dword [res_arr + 4 * ebx]
	push format
	call printf
	add esp, 8
	inc ebx
	cmp ebx, len
	jne check_a_loop

	push newline
	call printf
	add esp, 4

	; TODO b: Find the number of all the elements of `res_arr` that are strictly greater than `limit`
	xor ebx, ebx
	xor ecx, ecx
loop_b:
	mov eax, [res_arr + 4 * ebx]
	cmp eax, limit
	jle not_greater
greater:
	inc ecx
not_greater:
	inc ebx
	cmp ebx, len
	jne loop_b

	push ecx
	push format
	call printf
	add esp, 8

	push newline
	call printf
	add esp, 4

	; TODO c: Find the largest number from `res_arr` that is strictly smaller than `limit`

	; Return 0.
	xor eax, eax
	leave
	ret
