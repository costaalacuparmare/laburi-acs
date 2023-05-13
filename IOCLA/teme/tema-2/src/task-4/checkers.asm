section .data

section .text
	global checkers

checkers:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; table

   	;; DO NOT MODIFY
	;; FREESTYLE STARTS HERE

	;; compares for each position possible if the
	;; original position is at the limits of the
	;; table, otherwise adds 1 in every possible move
check_left_up:
	cmp eax, 7
	je check_left_down
	cmp ebx, 0
	je check_left_down
	;; add in edx the left-up position
	xor edx, edx
	add edx, eax
	;; increments edx to place to the upper line
	inc edx
    ;; multiplies by 8 to move through lines
	shl edx, 3
	add edx, ebx
	;; decrements edx to place diagonally in the upper line
	dec edx
	add byte [ecx + edx] , 1

check_left_down:
	cmp eax, 0
	je check_right_up
	cmp ebx, 0
	je check_right_up
	;; add in edx the left-down position
	xor edx, edx
	add edx, eax
	;; decrements edx to place to the line below
	dec edx
    ;; multiplies by 8 to move through lines
	shl edx, 3
	add edx, ebx
	;; decrements edx to place diagonally in the line below
	dec edx
	add byte [ecx + edx] , 1

check_right_up:
	cmp eax, 7
	je check_right_down
	cmp ebx, 7
	je check_right_down
	;; add in edx the right-up position
	xor edx, edx
	add edx, eax
	;; increments edx to place to the upper line
	inc edx
    ;; multiplies by 8 to move through lines
	shl edx, 3
	add edx, ebx
	;; increments edx to place diagonally in the upper line
	inc edx
	add byte [ecx + edx] , 1

check_right_down:
	cmp eax, 0
	je leave
	cmp ebx, 7
	je leave
	;; add in edx the right-down position
	xor edx, edx
	add edx, eax
	;; decrements edx to place to the line below
	dec edx
    ;; multiplies by 8 to move through lines
	shl edx, 3
	add edx, ebx
	;; increments edx to place diagonally in the line below
	inc edx
	add byte [ecx + edx] , 1

leave:
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY