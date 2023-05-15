#include "lg.h"

void afisareInt(void *elem) {
    int *aux = elem;
    printf("%d ", *aux);
}

int VerifPar (void *elem) {
	int *nr = elem;
	return (*nr % 2 == 0);
}

int main() {
    int lg = 0;
    TLG L = NULL;
    
    L = CitireLG(&lg);
    //printf("Dimensiune lista: %d\n", lg);
    AfisareLG(L, afisareInt);
	printf("Lab9 Ex1:  %d\n", nr_pare(L, VerifPar));
    DistrugeLG(&L, free);
    return 0;
}