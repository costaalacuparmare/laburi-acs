section .rodata:
	; taken from fnctl.h
	O_RDONLY	equ 00000  ;  flaguri deschide fisier
	O_WRONLY	equ 00001
	O_TRUNC		equ 01000
	O_CREAT		equ 00100
	S_IRUSR		equ 00400  ;  flaguri permisiuni la creare
	S_IRGRP		equ 00040
	S_IROTH		equ 00004

section .text
	global	replace_marco

%macro macro_comparare 2           ;  macro copiat din ../task-1/
	cmp al, %1                 ;  compara al cu arg 1, se duce in label
	jz %2                      ;  daca sunt egale
%endmacro

%macro macro_necomparare 2         ;  la fel ca mai sus, daca nu sunt egale
	cmp al, %1                 ;  ambele sunt folosite pentru a gasi
	jnz %2                     ;  "Marco".
%endmacro

;; void replace_marco(const char *in_file_name, const char *out_file_name)
;  it replaces all occurences of the word "Marco" with the word "Polo",
;  using system calls to open, read, write and close files.

extern calloc
extern free
extern strlen

replace_marco:                  ;
	push	ebp             ;
	mov 	ebp, esp        ;
	push ebx                ;  pastram registrele care trebuiesc pastrate
	push edi                ;
	push esi                ;
                                ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                             DESCHIDE READ                                ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov eax, 5              ;  cod apel pentru a deschide un fisier
	mov ebx, [ebp + 8]      ;  nume fisier input
	mov ecx, O_RDONLY       ;  flag citire
	mov edx, O_RDONLY       ;  nu stiu, l-am pus sa fie
	int 0x80                ;  apel de sistem
                                ;
	mov ebx, eax            ;  mutam file handler in ebx pentru apelul
	                        ;  urmator de sistem
	push dword 1            ;
	push dword 100          ;
	call calloc             ;  alocam memorie pentru a citi un string de
	add esp, 8	        ;  100 de caractere.
	mov esi, eax            ;  pastram stringul in esi (adresa de inceput)
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                               CITESTE                                    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov eax, 3              ;  apel de sistem pentru a citi dintr-un fisier
	mov ecx, esi            ;  char *destination
	mov edx, 100            ;  size_t numar de octeti de citit
	int 0x80                ;
                                ;
	call inlocuieste_marco  ;  dupa apel, in esi se afla string-ul bun
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                            DESCHIDE WRITE                                ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov eax, 5              ;  cod deschide
	mov ebx, [ebp + 12]     ;  char *numele (fisierul de output)
	mov ecx, O_CREAT        ;  optiune de creare a fisierului
	or ecx, O_WRONLY        ;  deschiderea sa in write
	mov edx, S_IRUSR        ;  permisiuni de citire de catre toti
	or edx, S_IRGRP         ;  utilizatori
	or edx, S_IROTH         ;
	int 0x80                ;
	mov ebx, eax            ;  in ebx, file handler
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                SCRIE                                     ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	push dword esi          ;  verificam cati octeti are string-ul nostru
	call strlen             ;
	add esp, 4              ;
	mov edx, eax            ;  size_t (num octeti de scriere)
                                ;
	mov eax, 4              ;  cod scrie
	mov ecx, esi            ;  char *sursa de scris
	int 0x80                ;
                                ;
	push esi                ;  eliberam memoria pentru ca suntem cetateni
	call free               ;  model
	add esp, 4              ;
                                ;
	pop esi                 ;
	pop edi                 ;  restauram si plecam
	pop ebx                 ;
	leave                   ;
	ret                     ;
                                ;
                                ;
inlocuieste_marco:              ;
	push dword 1            ;  se creeaza un string nou de 100 de octeti
	push dword 100          ;
	call calloc             ;
	add esp, 8	        ;
	mov edi, eax            ;  se pune in edi si in edx
	mov edx, edi            ;  esi si edi vor fi folosite pe post de
	mov ecx, esi            ;  iteratori, astfel incat la final sa am
                                ;  acces la ambii pointeri originali.
loop_inlocuire:	                ;
	mov al, byte[esi]       ;  se ia prima litera din string-ul original
	mov ah, al              ;  litera se pune in ah pentru a fi preluata
	macro_comparare 0, gata_inlocuire
	macro_comparare "M", gasit_inceput_marco
                                ;
gata_verificare:                ;
	mov byte [edi], ah      ;  se preia valoarea si se pune in stringul 2
	inc edi                 ;  se incrementeaza ambele stringuri
	inc esi                 ;
	jmp loop_inlocuire      ;
                                ;
gata_inlocuire:                 ;
	mov esi, edx            ;  esi devine pointer la noul string (cel cu
	push ecx                ;  Polo)
	call free               ;  ecx se elibereaza (cel original)
	add esp, 4              ;
	ret                     ;
                                ;
                                ;
gasit_inceput_marco:            ;
	mov al, byte[esi + 1]   ;  se verifica toate cele cinci litere din
	macro_necomparare "a", gata_verificare
	mov al, byte[esi + 2]   ;  "Marco" si, daca una nu coincide, se sare la
	macro_necomparare "r", gata_verificare
	mov al, byte[esi + 3]   ;  gata_verificare
	macro_necomparare "c", gata_verificare
	mov al, byte[esi + 4]   ;  altfel,
	macro_necomparare "o", gata_verificare
	add esi, 5              ;  trecem 5 octeti (peste Marco) in original
	mov dword[edi], "Polo"  ;  punem 4 octeti ("Polo") in string-ul nou
	add edi, 4              ;  trecem 4 octetei in cel nou
	jmp loop_inlocuire      ;
