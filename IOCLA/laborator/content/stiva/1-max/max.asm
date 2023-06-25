%include "../utils/printf32.asm"

section .text

extern printf
global main
main:
    ; numbers are placed in these two registers
    mov eax, 6
    mov ebx, 8

    ; TODO: get maximum value. You are only allowed to use one conditional jump and push/pop instructions.
	cmp ebx, eax
	jg stack
print:
    PRINTF32 `Max value is: %d\n\x0`, eax ; print maximum value
    ret

stack:
	Push ebx
	Pop eax
	jmp print