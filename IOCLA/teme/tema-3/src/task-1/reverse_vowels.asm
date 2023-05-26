section .data
	; declare global vars here
	vowels db "AEIOUaeiou", 0
section .text
	global reverse_vowels

;;	void reverse_vowels(char *string)
;	Cauta toate vocalele din string-ul `string` si afiseaza-le
;	in ordine inversa. Consoanele raman nemodificate.
;	Modificare se va face in-place
reverse_vowels:
     push ebp
     mov ebp, esp
     push edi
     push esi

     mov edi, dword [ebp + 8]   ; edi points to the input string

     xor ecx, ecx              ; ecx will store the length of the string
     mov esi, edi              ; esi will be used for string traversal
     mov al, byte [esi]        ; load the first character

     ; calculate the length of the string
     find_string_length:
         cmp al, 0
         je end_find_string_length
         inc ecx
         inc esi
         mov al, byte [esi]
         jmp find_string_length
     end_find_string_length:

     dec esi                   ; esi points to the last character of the string
     mov edx, ecx              ; edx will be used for vowel reversal loop

     ; reverse the vowels
     reverse_loop:
         mov al, byte [edi]     ; load the current character
         cmp al, 0
         je end_reverse_loop

         ; check if the character is a vowel
         movzx eax, al
         cmp al, 'A'
         jl not_a_vowel
         cmp al, 'Z'
         jle is_a_vowel
         cmp al, 'a'
         jl not_a_vowel
         cmp al, 'z'
         jg not_a_vowel

     is_a_vowel:
         ; check if the current character is a vowel by comparing it with the vowels string
         mov esi, vowels
         movzx edi, al

     check_vowel:
         lodsb                 ; load the next vowel from the vowels string
         cmp al, 0
         je not_a_vowel
         cmp al, dil
         je reverse_vowel
         jmp check_vowel

     reverse_vowel:
         xchg al, byte [esi-1]  ; swap the current vowel with the last vowel found
         dec esi
         dec edx

     not_a_vowel:
         inc edi               ; move to the next character
         jmp reverse_loop

     end_reverse_loop:
     pop esi
     pop edi
     mov esp, ebp
     pop ebp
     ret