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
;;	void pwd(char **directories, int n, char *output)
;	Adauga in parametrul output path-ul rezultat din
;	parcurgerea celor n foldere din directories
pwd:
	enter 0, 0
	pusha
	xor eax, eax       ; current position in directories array
	xor ebx, ebx       ; current position in output
	xor edx, edx       ; temporary register

	; get arguments
	mov esi, [ebp + 8] ; directories
	mov ecx, [ebp + 12] ; n
	mov edi, [ebp + 16] ; output

add_directory:

	; check if all directories have been processed
	cmp ecx, 0
	je end_pwd

	; decrement the number of directories
	dec ecx

	; get the current directory name
	mov edx, dword [esi + eax * 4]

	; push values modified by strcmp
	push eax
	push ecx
	push edx

	; call strcmp
	push edx
	push curr
	call strcmp
	add esp, 8

	; check if the current directory is "."
	cmp eax, 0
	je next_directory

	; get back the current directory
	pop edx
	push edx

	; call strcmp
    push edx
    push back
    call strcmp
    add esp, 8
	; check if the current directory is ".."
	cmp eax, 0
    je prev_directory

	; add '/' in output
    push edi
    push slash
    call strcat
    add esp, 8
    mov edi, eax

	; get back the current directory
	;pop edx
    ;push edx

	; add current directory in output
	;push edi
	;push edx
	;call strcat
	;add esp, 8
	;mov edi, eax

	pop edx
    pop ecx
    pop eax

	inc eax
	jmp add_directory



next_directory:
	; pop values modified by strcmp
	pop edx
    pop ecx
    pop eax

	inc eax
	jmp add_directory

prev_directory:
	; pop values modified by strcmp
	pop edx
	pop ecx
	pop eax

	inc eax
    jmp add_directory

end_pwd:
	popa
	leave
	ret