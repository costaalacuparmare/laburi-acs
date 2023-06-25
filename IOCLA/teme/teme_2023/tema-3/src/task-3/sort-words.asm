global get_words
global compare_func
global sort
extern strtok
extern strlen
extern strcmp
extern qsort
section .text

;; get_words(char *s, char **words, int number_of_words)
;  separa stringul s in cuvinte si salveaza cuvintele in words
;  number_of_words reprezinta numarul de cuvinte
get_words:
    enter 0, 0
	pusha

	; get arguments
	mov esi, [ebp + 8] ; s
	mov edi, [ebp + 12] ; words
	mov ecx, [ebp + 16] ; nr_words

	xor edx, edx ; counter for words array

first_strtok:

	; edx is modified by strtok function
	push edx

	; delimits the first word
	push delimiters
    push esi
    call strtok
    add esp, 8

	pop edx

	; check if the words are finished
    cmp eax, 0
    je end_get_words

	; adds the word in the array
    mov [edi + edx * 4], eax
    inc edx
    dec ecx

strtok_loop:
	; edx is modified by strtok function
	push edx

	; delimits the rest of the words
	push delimiters
    push 0
    call strtok
    add esp, 8

	pop edx

	; check if the words are finished
	cmp eax, 0
	jz end_get_words

	; adds the word in the array
	mov [edi + edx * 4], eax
	inc edx
	dec ecx

	; check if the number of words is 0
	cmp ecx, 0
	jg strtok_loop

end_get_words:
	popa
    leave
    ret
    delimiters db " .,", 10, 0 ; defines the delimiter string

compare_func:
    enter 0, 0
    push esi
    push edi
    push ebx

	; get parameters
    mov esi, [ebp + 8] ; 1st word
    mov esi, [esi]
    mov edi, [ebp + 12] ; 2nd word
    mov edi, [edi]

	; get length
    push esi
    call strlen
    add esp, 4

    mov ebx, eax

	; get length
    push edi
    call strlen
    add esp, 4

    sub ebx, eax
    jnz end_compare

	; compare the numbers
    push edi
    push esi
    call strcmp
    add esp, 8

    jmp finish

end_compare:
    mov eax, ebx

finish:
    pop ebx
    pop edi
    pop esi
    leave
    ret


;; sort(char **words, int number_of_words, int size)
;  functia va trebui sa apeleze qsort pentru soratrea cuvintelor
;  dupa lungime si apoi lexicografix
sort:
	enter 0, 0
	pusha

	; get parameters
	mov esi, [ebp + 8] ; words
	mov ecx, [ebp + 12] ; nr_words
	mov edx, [ebp + 16] ; size

	; call for qsort function
	push compare_func
	push edx
	push ecx
	push esi
	call qsort
	add esp, 16

	popa
    leave
    ret