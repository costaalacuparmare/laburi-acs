section .text
    global inorder_fixing

;   struct node {
;       int value;
;       struct node *left;
;       struct node *right;
;   } __attribute__((packed));

;;  inorder_fixing(struct node *node, struct node *parent)
;       functia va parcurge in inordine arborele binar de cautare, modificand
;       valorile nodurilor care nu respecta proprietatea de arbore binar
;       de cautare: |node->value > node->left->value, daca node->left exista
;                   |node->value < node->right->value, daca node->right exista.
;
;       Unde este nevoie de modificari se va aplica algoritmul:
;           - daca nodul actual este fiul stang, va primi valoare tatalui - 1,
;                altfel spus: node->value = parent->value - 1;
;           - daca nodul actual este fiul drept, va primi valoare tatalui + 1,
;                altfel spus: node->value = parent->value + 1;

;    @params:
;        node   -> nodul actual din arborele de cautare;
;        parent -> tatal/parintele nodului actual din arborele de cautare;

; ATENTIE: DOAR in frunze pot aparea valori gresite! 
;          Cititi SI fisierul README.md din cadrul directorului pentru exemple,
;          explicatii mai detaliate!

inorder_fixing:
    enter 0, 0

 	pusha

    ; get function parameters
    mov esi, [ebp + 8]   ; node
    mov ebx, [ebp + 12]  ; parent

    ; traverse the binary search tree in inorder
    push esi
    push ebx
    call inorder_recursion
	add esp, 8

    popa
    leave
    ret

inorder_recursion:
    push ebp
    mov ebp, esp

	push esi
	push ebx

    mov ebx, [ebp + 8]  ; parent
    mov esi, [ebp + 12] ; node

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
    call inorder_recursion
    add esp, 8

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
 	mov ecx, [ebx]
    ; +1 because it's in the right
    inc ecx
 	cmp [ebx], eax
 	jge correct_leaf

	jmp end_inorder_recursion

compare_left:
	mov eax, [esi]
	mov ecx, [ebx]
	; -1 because it's in the left
    dec ecx
	cmp [ebx], eax
	jle correct_leaf

	jmp end_inorder_recursion

correct_leaf:
 	; update node
 	mov [esi], ecx

	jmp end_inorder_recursion

    ; traverse the right subtree
right_subtree:
    ; load the right child pointer
    mov eax, [esi + 8]
    push eax
    push esi
    call inorder_recursion
    add esp, 8

end_inorder_recursion:

    pop ebx
	pop esi
    leave
    ret
    leave
    ret
