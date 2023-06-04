#include "lista2.h"

int main() {
    TLista2 L = NULL;
    int dim;

    L = CitireLista2(&dim);
    printf("Numar elemente citite: %d\n", dim);
    AfisareLista2(L);
    int x = 3;
    int ref = 5;
    InsrX(&L,x,ref);
    AfisareLista2(L);
    DistrugeLista2(&L);
    return 0;
}