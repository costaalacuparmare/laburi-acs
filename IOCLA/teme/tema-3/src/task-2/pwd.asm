section .data
	back db "..", 0
	curr db ".", 0
	slash db "/", 0
	; declare global vars here

section .bss
	 output resb 256

section .text
	global pwd

;;	void pwd(char **directories, int n, char *output)
;	Adauga in parametrul output path-ul rezultat din
;	parcurgerea celor n foldere din directories
pwd:
	enter 0, 0

    xor ecx, ecx ; initialize counter

    ; iterate through the directories
    mov esi, [esp + 4] ; load the address of the directories array
    mov eax, [esp + 8] ; load the number of directories
    mov edi, output ; load the address of the output buffer

    add_directories:
        ; check if all directories have been processed
        cmp ecx, eax
        je end_pwd

        ; get the current directory name
        mov edx, [esi + ecx * 4] ; assuming each directory name is a null-terminated string

        ; check if the current directory is "."
        cmp byte [edx], '.'
        je increment_counter

        ; check if the current directory is ".."
        cmp byte [edx], '.'
        je decrement_counter

        ; append the current directory to the output path
        ; find the end of the current output path
        mov esi, edi ; point to the end of the output buffer
        find_end_of_output:
            cmp byte [esi], 0
            je append_directory

            inc esi
            jmp find_end_of_output

        append_directory:
            ; append a slash character before the current directory
            cmp edi, output ; check if the output address is not at the beginning
            je skip_slash
            mov byte [esi], '/'
            inc esi

            skip_slash:
            ; append the characters of the current directory to the output
            append_directory_characters:
                mov al, [edx]
                mov [esi], al
                cmp al, 0
                je increment_counter
                inc edx
                inc esi
                jmp append_directory_characters

        increment_counter:
            inc ecx
            jmp add_directories

        decrement_counter:
            cmp ecx, 0
            je add_directories
            dec ecx
            jmp add_directories

    end_pwd:
    mov byte [esi], 0 ; null-terminate the output path
    leave
    ret