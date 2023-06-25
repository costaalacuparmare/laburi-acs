section .data
	; declare global vars here
section .text
	global reverse_vowels

;;	void reverse_vowels(char *string)
;	Cauta toate vocalele din string-ul `string` si afiseaza-le
;	in ordine inversa. Consoanele raman nemodificate.
;	Modificare se va face in-place
reverse_vowels:

	; modifies stack pointer and pops the string
	add esp, 4
	pop eax ; string
	sub esp, 8

	; saves the string pointer in ecx for the second loop
	push eax
	pop ecx

	; saves in the stack the vowels found in the string
push_loop:
	; uses dx to save the first to chars from the string
	; dl contains the first char and verifies that it isn't
	; the null terminator
	push word [eax]
	pop dx
	cmp dl, 0
	je pop_setup

push_check:
	; check if the current character is a vowel by comparing it with the vowels
	cmp dl, "a"
	je push_vowel
	cmp dl, "e"
	je push_vowel
	cmp dl, "i"
	je push_vowel
	cmp dl, "o"
	je push_vowel
	cmp dl, "u"
	je push_vowel
	; moves eax to point to the second char in the string
	inc eax
	jmp push_loop

push_vowel:
	; resets the second char, in dh, to push only the vowel found
	xor dh, dh
	push dx
	; moves eax to point to the second char in the string
	inc eax
	jmp push_loop

	; uses the ecx register to reset eax
pop_setup:
	push ecx
	pop eax

pop_loop:
	; verifies that the string did not reach the null terminator
	; same as the first loop
	push word [eax]
	pop dx
	cmp dl, 0
	je reverse_end

pop_check:
	; check if the current character is a vowel by comparing it with the vowels
	cmp dl, "a"
	je reverse
	cmp dl, "e"
	je reverse
	cmp dl, "i"
	je reverse
	cmp dl, "o"
	je reverse
	cmp dl, "u"
	je reverse
	inc eax
	jmp pop_loop

reverse:
	; pops the memories vowels and reverses the current one with the one popped
	; using ecx and edx registers to save in cx the reversed vowels and the
	; next char, replacing the current ones from eax
	xor dl, dl
	pop cx
	add cx, dx
	push cx
	pop word [eax]
	inc eax
	jmp pop_loop

reverse_end:

	ret