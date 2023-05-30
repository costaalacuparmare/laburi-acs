extern array_idx_1      ;; int array_idx_1

section .text
    global inorder_parc

;   struct node {
;       int value;
;       struct node *left;
;       struct node *right;
;   } __attribute__((packed));

;;  inorder_parc(struct node *node, int *array);
;       functia va parcurge in inordine arborele binar de cautare, salvand
;       valorile nodurilor in vectorul array.
;    @params:
;        node  -> nodul actual din arborele de cautare;
;        array -> adresa vectorului unde se vor salva valorile din noduri;

; ATENTIE: vectorul array este INDEXAT DE LA 0!
;          Cititi SI fisierul README.md din cadrul directorului pentru exemple,
;          explicatii mai detaliate!
; HINT: folositi variabila importata array_idx_1 pentru a retine pozitia
;       urmatorului element ce va fi salvat in vectorul array.
;       Este garantat ca aceasta variabila va fi setata pe 0 la fiecare
;       test.

inorder_parc:
    enter 0, 0
    pusha

    ; get function parameters
    mov esi, [ebp + 8]   ; node
    mov edi, [ebp + 12]  ; array

    ; traverse the binary search tree in inorder
    push esi
    push edi
    call inorder_recursion
	add esp, 8

    popa
    leave
    ret

inorder_recursion:
    push ebp
    mov ebp, esp

	; pushes esi because the function modifies it
	push esi

	mov edi, [ebp + 8] ; array
	mov esi, [ebp + 12] ; node

    ; check if the node is NULL
    cmp esi, 0
    je end_inorder_recursion

    ; traverse the left subtree

    ; load the left child pointer
    mov eax, [esi + 4]
    push eax ; node
    push edi ; array
    call inorder_recursion
    add esp, 8

    ; process the current node
    ; load the value of the current node
    mov eax, [esi]
    mov ebx, dword [array_idx_1]
    ; store the value in the array at the specified index
    mov [edi + ebx * 4], eax
    inc dword [array_idx_1]

    ; traverse the right subtree
    ; load the right child pointer
    mov eax, [esi + 8]
    push eax
    push edi
    call inorder_recursion
    add esp, 8

end_inorder_recursion:

	; resets esi
    pop esi

    leave
    ret
