extern array_idx_2      ;; int array_idx_2

section .text
    global inorder_intruders

;   struct node {
;       int value;
;       struct node *left;
;       struct node *right;
;   } __attribute__((packed));

;;  inorder_intruders(struct node *node, struct node *parent, int *array)
;       functia va parcurge in inordine arborele binar de cautare, salvand
;       valorile nodurilor care nu respecta proprietatea de arbore binar
;       de cautare: |node->value > node->left->value, daca node->left exista
;                   |node->value < node->right->value, daca node->right exista
;
;    @params:
;        node   -> nodul actual din arborele de cautare;
;        parent -> tatal/parintele nodului actual din arborele de cautare;
;        array  -> adresa vectorului unde se vor salva valorile din noduri;

; ATENTIE: DOAR in frunze pot aparea valori gresite!
;          vectorul array este INDEXAT DE LA 0!
;          Cititi SI fisierul README.md din cadrul directorului pentru exemple,
;          explicatii mai detaliate!

; HINT: folositi variabila importata array_idx_2 pentru a retine pozitia
;       urmatorului element ce va fi salvat in vectorul array.
;       Este garantat ca aceasta variabila va fi setata pe 0 la fiecare
;       test al functiei inorder_intruders.      

inorder_intruders:
    enter 0, 0
  	pusha

    ; get function parameters
    mov esi, [ebp + 8]   ; node
    mov ebx, [ebp + 12]  ; parent
    mov edi, [ebp + 16] ; array

    ; traverse the binary search tree in inorder
    push esi
    push ebx
    push edi
    call inorder_recursion
	add esp, 12

    popa
    leave
    ret

inorder_recursion:
    push ebp
    mov ebp, esp

	push esi
	push ebx

	mov edi, [ebp + 8] ; array
    mov ebx, [ebp + 12]  ; parent
    mov esi, [ebp + 16] ; node

    ; check if the node is NULL
    cmp esi, 0
    je end_inorder_recursion


    ; traverse the left subtree
    ; load the left child pointer
    mov eax, [esi + 4]

    ; check if left subtree exits
    cmp eax, 0
    je maybe_leaf

    push eax ; node
    push esi ; parent
    push edi ; array
    call inorder_recursion
    add esp, 12

	jmp right_subtree

	; checks right subtree
maybe_leaf:
    cmp dword [esi + 8], 0
    je definitely_leaf

	jmp right_subtree

    ; process the current node
definitely_leaf:
	; checks if the curent node is the left subtree
	cmp [ebx + 4], esi
	je compare_left

	; if it doesn't come from the left side, it's from the right
	; load the value of the current node
	mov eax, [esi]
 	cmp [ebx], eax
 	jge store_leaf

	jmp end_inorder_recursion

compare_left:
	mov eax, [esi]
	cmp [ebx], eax
	jle store_leaf

	jmp end_inorder_recursion

store_leaf:
 	mov ecx, dword [array_idx_2]
 	; store the value in the array at the specified index
 	mov [edi + ecx * 4], eax
 	inc dword [array_idx_2]

	jmp end_inorder_recursion

    ; traverse the right subtree
right_subtree:
    ; load the right child pointer
    mov eax, [esi + 8]
    push eax
    push esi
    push edi
    call inorder_recursion
    add esp, 12

end_inorder_recursion:

    pop ebx
	pop esi
    leave
    ret
