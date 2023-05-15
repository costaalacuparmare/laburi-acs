#include "lg.h"

void afisareInt(void *elem) {
    int *aux = elem;
    printf("%d ", *aux);
}

int main() {
    int lg = 0;
    TLG L = NULL;
    
    L = CitireLG(&lg);
    printf("Dimensiune lista: %d\n", lg);
    AfisareLG(L, afisareInt);

    DistrugeLG(&L, free);
    return 0;
}