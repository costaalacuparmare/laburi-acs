section .text
	global get_rand

get_rand:                 ;
    push    ebp       ;
    mov     ebp, esp  ;
    push ebx          ;
    push edi          ;
                          ;
    xor eax, eax      ;  se golesc eax, edx de reziduuri
    xor edx, edx      ;
    rdtsc             ;  se genereaza nr de cicluri in eax:edx
    mov ecx, eax      ;  se muta in ecx:dbx
    mov ebx, edx      ;
rdrand_here:              ;
    rdrand edi        ;  se genereaza nr aleator in edi
    rdtsc             ;  se regenereaza nr de cicluri in eax:edx
    sub eax, ecx      ;  se afla cate ticuri au trecut de la ultima
    sub edx, ebx      ;  verificare. initial am vrut sa compar si edx dar
    cmp eax, 54       ;  nu am reusit. maximul pe care l-am avut pe masina
    jle gata          ;  mea virtuala de iocla a fost 54 de cicluri.
    mov edi, 0        ;  daca nu se incadreaza in timp, edi devine 0
                          ;
gata:                     ;
    xchg edi, eax     ;  se returneaza val lui edi
    pop edi           ;
    pop ebx           ;
    ;;push eax        ;
    ;;push prt_form   ;
    ;;call printf     ;
    ;;add esp, 4      ;
    ;;pop eax         ;
    leave             ;
    ret               ;