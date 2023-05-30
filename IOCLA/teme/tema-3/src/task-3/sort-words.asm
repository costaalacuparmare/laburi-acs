global get_words
global compare_func
global sort
extern strtok
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
	push edx
	push delimiters
    push esi
    call strtok
    add esp, 8
	pop edx
    cmp eax, 0
    je end_get_words

    mov [edi + edx * 4], eax
    inc edx
    dec ecx

strtok_loop:
	push edx
	push delimiters
    push 0
    call strtok
    add esp, 8
	pop edx
	cmp eax, 0
	jz end_get_words

	mov [edi + edx * 4], eax
	inc edx

	dec ecx
	cmp ecx, 0
	jg strtok_loop

end_get_words:
	popa
    leave
    ret
    delimiters db " .,", 10, 0 ; defines the delimiter string

;; sort(char **words, int number_of_words, int size)
;  functia va trebui sa apeleze qsort pentru soratrea cuvintelor
;  dupa lungime si apoi lexicografix
sort:
	enter 0, 0
	pusha

	popa
    leave
    ret

