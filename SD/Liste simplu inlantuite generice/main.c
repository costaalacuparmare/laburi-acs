#include "lg.h"

void afisareInt(void *elem) {
    int *aux = elem;
    printf("%d ", *aux);
}

void afisareCarte(void *elem) {
	TCarte *aux = elem;
	printf("%s ", (*aux).titlu);
	printf("%s ", (*aux).autor);
	printf("%d\n", (*aux).an_aparitie);
}

int VerifPar (void *elem) {
	int *nr = elem;
	return (*nr % 2 == 0);
}

int VerifPar2 (void *elem) {
	int *nr = &(((TCarte *) elem)->an_aparitie);
	return (*nr % 2 == 0);
}

int main() {
    int lg = 0;
    TLG L = NULL;
    
    //L = CitireLG(&lg);
    //printf("Dimensiune lista: %d\n", lg);
    //AfisareLG(L, afisareInt);
	L = CitireLG2(&lg);
	AfisareLG(L, afisareCarte);
	printf("Lab9 Ex1:  %d\n", nr_pare(L, VerifPar));
    DistrugeLG(&L, free);
    return 0;
}