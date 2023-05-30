%include "../printf32.asm"

section .data
	back db "..", 0
	curr db ".", 0
	slash db "/", 0
	; declare global vars here

section .text
	global pwd
	extern strcmp
	extern printf
	extern strcat
	extern strlen
;;	void pwd(char **directories, int n, char *output)
;	Adauga in parametrul output path-ul rezultat din
;	parcurgerea celor n foldere din directories
pwd:
	enter 0, 0
	pusha
	xor eax, eax       ; current position in directories array
	xor ebx, ebx       ; counter for directories in output
	xor edx, edx       ; temporary register

	; get arguments
	mov esi, [ebp + 8] ; directories
	mov ecx, [ebp + 12] ; n
	mov edi, [ebp + 16] ; output

add_directory:

	; check if all directories have been processed
	cmp ecx, 0
	je prep_strcat

	; decrement the number of directories
	dec ecx

	; get the current directory name
	mov edx, dword [esi + eax * 4]

	; push counter for directories in output
	push ebx

	; push values modified by strcmp
	push eax
	push ecx
	push edx

	; call strcmp
	push edx
	push curr
	call strcmp
	add esp, 8

	xor ebx, ebx
	mov ebx, eax

	; gets back values modified by strcmo
	pop edx
    pop ecx
    pop eax

	; check if the current directory is "."
	cmp ebx, 0
	je next_directory


	; push values modified by strcmp
	push eax
	push ecx
	push edx

	; call strcmp
    push edx
    push back
    call strcmp
    add esp, 8

	xor ebx, ebx
	mov ebx, eax

	; gets back values modified by strcmo
	pop edx
    pop ecx
    pop eax

	; check if the current directory is ".."
	cmp ebx, 0
    je prev_directory

	; counter for directories to be added in output
    pop ebx

	; adds the current directory in the stack to use later
	push edx

	inc ebx
	inc eax
	jmp add_directory

next_directory:
	; counter for directories to be added in output
    pop ebx

	inc eax
	jmp add_directory

prev_directory:
	; counter for directories to be added in output
    pop ebx
	cmp ebx, 0
	je no_prev_directory

	dec ebx

	; pop the last pushed directory from the stack
	pop edx
	xor edx, edx

no_prev_directory:
	inc eax
    jmp add_directory

prep_strcat:
	mov esi, ebx
strcat_loop:
	; exit if all directories were added
	cmp ebx, 0
	je prep_reverse

	; strcat modifies edx
	pop edx
	push edx

	; add '/' in output
    push slash
    push edi
    call strcat
   	add esp, 8

	pop edx
	; add directory in output
    push edx
    push edi
    call strcat
    add esp, 8

    dec ebx
    jmp strcat_loop

prep_reverse:
	; add last '/' in output
    push slash
    push edi
    call strcat
    add esp, 8

	; stores the number of directories from output in ebx
	mov ebx, esi
    xor esi, esi
    inc ebx

    PRINTF32 `%s\n\x0`, edi
    ; Reverse the string
    mov esi, edi

    ; get length
    push edi
    call strlen
    add esp, 4
    mov ecx, eax
	dec ecx
    add edi, ecx

    PRINTF32 `%s\n\x0`, edi
    shr ebx, 1

reverse_loop:
	mov dl, byte [edi]
	mov dh, byte [esi]
	mov byte [edi], dh
	mov byte [esi], dl
	dec edi
	inc esi
	loop reverse_loop

end_pwd:
	popa
	leave
	ret