%include "../include/io.mac"

;; defining constants, you can use these as immediate values in your code
LETTERS_COUNT EQU 26

section .data
    extern len_plain
	config db 10 dup (26 dup (0))
section .text
    global rotate_x_positions
    global enigma
    extern printf

; void rotate_x_positions(int x, int rotor, char config[10][26], int forward);
rotate_x_positions:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]  ; x
    mov ebx, [ebp + 12] ; rotor
    mov ecx, [ebp + 16] ; config (address of first element in matrix)
    mov edx, [ebp + 20] ; forward
    ;; DO NOT MODIFY
    ;; TODO: Implement rotate_x_positions
    ;; FREESTYLE STARTS HERE
;; Calculate the effective number of shifts based on the forward direction
    ;; and the rotor number
    mov esi, ebx
    mul esi
    mov ecx, eax

    ;; Get the address of the rotor configuration row
    lea edx, [ecx + ecx * 4]
    lea edx, [edx * 2 + config]

    ;; Perform the rotation
    mov edi, esi
    neg edi
    and edi, LETTERS_COUNT
    jz skip_rotation

    ;; Rotate to the left (forward = 0)
    cmp edx, 0
    je rotate_left

    ;; Rotate to the right (forward = 1)
    rotate_right:
        mov al, byte [edx]
        mov ah, al
        rol al, cl
        mov byte [edx], al
        inc edx
        loop rotate_right_loop
        jmp end_rotation

    rotate_left:
        mov al, byte [edx]
        mov ah, al
        ror al, cl
        mov byte [edx], al
        inc edx
        loop rotate_left_loop
        jmp end_rotation

    rotate_right_loop:
        mov al, byte [edx]
        mov ah, al
        ror al, cl
        mov byte [edx], al
        inc edx

    rotate_left_loop:
        mov al, byte [edx]
        mov ah, al
        rol al, cl
        mov byte [edx], al
        inc edx
        loop rotate_left_loop

    end_rotation:
    skip_rotation:
    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY

; void enigma(char *plain, char key[3], char notches[3], char config[10][26], char *enc);
enigma:
    ;; DO NOT MODIFY
    push ebp
    mov ebp, esp
    pusha

    mov eax, [ebp + 8]  ; plain (address of first element in string)
    mov ebx, [ebp + 12] ; key
    mov ecx, [ebp + 16] ; notches
    mov edx, [ebp + 20] ; config (address of first element in matrix)
    mov edi, [ebp + 24] ; enc
    ;; DO NOT MODIFY
    ;; TODO: Implement enigma
    ;; FREESTYLE STARTS HERE


    ;; FREESTYLE ENDS HERE
    ;; DO NOT MODIFY
    popa
    leave
    ret
    ;; DO NOT MODIFY