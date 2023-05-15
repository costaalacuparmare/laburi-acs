section .data

section .text
    global bonus

bonus:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]	; x
    mov ebx, [ebp + 12]	; y
    mov ecx, [ebp + 16] ; board

    ;; DO NOT MODIFY
    ;; FREESTYLE STARTS HERE

	;; testing, I have discovered the correlation
	;; between the rows and the addresses where they are found
    ; 7 = ecx + 3 => offset = eax - 4
    ; 6 = ecx + 2 => offset = eax - 4
    ; 5 = ecx + 1 => offset = eax - 4
    ; 4 = ecx => offset = 0
    ; 3 = ecx + 7 => offset = eax + 4
    ; 2 = ecx + 6 => offset = eax + 4
	; 1 = ecx + 5 => offset = eax + 4
	; 0 = ecx + 4 => offset = eax + 4

	;; compares for each position possible if the
	;; original position is at the limits of the
	;; table, otherwise calculates the numbers above
	;; and below the original position by shifting
	;; the number of columns required

	;; similar to the checkers function, but with a
	;; couple changes

    push ebx
    mov edx, 1

	;; label is used to get the original
	;; number on the 'eax' row
get_column:
	cmp ebx, 0
	je check_limits_left_up
	shl edx, 1
	dec ebx
	jmp get_column

	;; further down are used repetitive
	;; labels that verify limits and
	;; positioning for each possible move

	;; checks the limits of the table
check_limits_left_up:
	;; used the stack to store the y value
	pop ebx
	cmp eax, 7
	je check_limits_left_down
	cmp ebx, 0
	je check_limits_left_down

	;; checks the plasement of the row
	;; since the codification discovered
	;; earlier to calculate the correct
	;; numbers above and below
check_left_up:
	shr edx, 1
	cmp eax, 5
	jge high_rows_left_up
	cmp eax, 4
	je start_line_left_up

	;; label for when a possible position is on
	;; the starting line
below_start_line_left_up:
	cmp eax, 3
	jne low_rows_left_up
	add byte [ecx], dl
	shl edx, 1
	jmp check_limits_left_down

	;; label for the lower values of 'eax'
low_rows_left_up:
    add byte [ecx + (eax + 4) + 1], dl
	shl edx, 1
	jmp check_limits_left_down

	;; label for the upper values of 'eax'
high_rows_left_up:
	add byte [ecx + (eax - 4) + 1], dl
	shl edx, 1
	jmp check_limits_left_down

	;; label for the starting line
start_line_left_up:
	add byte [ecx + 1], dl
	shl edx, 1

	;; checks the limits of the table
check_limits_left_down:
	cmp eax, 0
	je check_limits_right_up
	cmp ebx, 0
	je check_limits_right_up

	;; checks the plasement of the row
	;; since the codification discovered
	;; earlier to calculate the correct
	;; numbers above and below
check_left_down:
	shr edx, 1
	cmp eax, 5
	jge high_rows_left_down
	cmp eax, 4
	je start_line_left_down

	;; label for the lower values of 'eax'
low_rows_left_down:
    add byte [ecx + (eax + 4) - 1], dl
	shl edx, 1
	jmp check_limits_right_up

	;; label for the upper values of 'eax'
high_rows_left_down:
	add byte [ecx + (eax - 4) - 1], dl
	shl edx, 1
	jmp check_limits_right_up

	;; label for the starting line
start_line_left_down:
	add byte [ecx + 7], dl
	shl edx, 1

	;; checks the limits of the table
check_limits_right_up:
	cmp eax, 7
	je check_limits_right_down
	cmp ebx, 7
	je check_limits_right_down

	;; checks the plasement of the row
	;; since the codification discovered
	;; earlier to calculate the correct
	;; numbers above and below
check_right_up:
	shl edx, 1
	cmp eax, 5
	jge high_rows_right_up
	cmp eax, 4
	je start_line_right_up

	;; label for when a possible position is on
    ;; the starting line
below_start_line_right_up:
    cmp eax, 3
    jne low_rows_right_up
    add byte [ecx], dl
    shr edx, 1
    jmp check_limits_right_down

	;; label for the lower values of 'eax'
low_rows_right_up:
    add byte [ecx + (eax + 4) + 1], dl
	shr edx, 1
	jmp check_limits_right_down

	;; label for the upper values of 'eax'
high_rows_right_up:
	add byte [ecx + (eax - 4) + 1], dl
	shr edx, 1
	jmp check_limits_right_down

	;; label for the starting line
start_line_right_up:
	add byte [ecx + 1], dl
	shr edx, 1

	;; checks the limits of the table
check_limits_right_down:
	cmp eax, 0
	je leave
	cmp ebx, 7
	je leave

	;; checks the plasement of the row
	;; since the codification discovered
	;; earlier to calculate the correct
	;; numbers above and below
check_right_down:
	shl edx, 1
	cmp eax, 5
	jge high_rows_right_down
	cmp eax, 4
	je start_line_right_down

	;; label for the lower values of 'eax'
low_rows_right_down:
    add byte [ecx + (eax + 4) - 1], dl
	shr edx, 1
	jmp leave

	;; label for the upper values of 'eax'
high_rows_right_down:
	add byte [ecx + (eax - 4) - 1], dl
	shr edx, 1
	jmp leave

	;; label for the starting line
start_line_right_down:
	add byte [ecx + 7], dl
	shr edx, 1

leave:
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY