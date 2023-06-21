%include "../utils/printf32.asm"
extern printf

section .data
format db '%d ', 0
format2 db '%d', 10, 0
newline db 10, 0
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
	xor ebx, ebx
a_loop:
	cmp ebx, len
	je check_a
	mov eax, 17
	mul ebx
	add eax, 3
	mov [int_arr + 4 * ebx], eax
	inc ebx
	jmp a_loop

check_a:
	xor ebx, ebx

check_a_loop:
	mov eax, dword [int_arr + 4 * ebx]
	push eax
	push format
	call printf
	add esp, 8
	inc ebx
	cmp ebx, len
	jne check_a_loop

	push newline
	call printf
	add esp, 4

    ; TODO b: Count the number of elements strictly smaller than number pointed by `limit`
	xor ebx, ebx ;; used to count the number
	xor ecx, ecx ;; used to parse the array
loop_b:
	mov eax, dword [int_arr + 4 * ecx]
	cmp eax, [limit]
	jge check_b
	inc ebx
	inc ecx
	cmp ecx, len
	je check_b
	jmp loop_b

check_b:
	push ebx
	push format2
	call printf
	add esp, 8

    ; TODO c: Find and print the smallest number strictly greater than number pointed by `limit`
label_c:
	cmp eax, [limit]
	jg check_c
	inc ecx
	mov eax, [int_arr + 4 * ecx]
	jmp label_c

check_c:
	push eax
	push format2
	call printf
	add esp, 8

    ; Return 0.
    xor eax, eax
    leave
    ret
