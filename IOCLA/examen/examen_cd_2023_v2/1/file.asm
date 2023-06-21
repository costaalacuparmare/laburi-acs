%include "../utils/printf32.asm"
extern printf

section .data

int_arr dd 11, 20, 39, 57, 99, 100, 88, 19, 29, 42
len equ 10
limit dd 3000

section .bss
	; TODO a: Reserve space for an array of `len` integers. The array name is `res_arr`

section .text
global main

main:
	push ebp
	mov ebp, esp

	; TODO a: Fill in the first `len` elements of `res_array` using the folloing formula:
	; res_arr[i] = 65 * int_arr[i] + 7
	; Print res_arr with all elements on the same line separated by a space

	; TODO b: Find the number of all the elements of `res_arr` that are strictly greater than `limit`

	; TODO c: Find the largest number from `res_arr` that is strictly smaller than `limit`

	; Return 0.
	xor eax, eax
	leave
	ret
