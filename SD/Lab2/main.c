#include "lista.h"

int main(){
    int lg = 0;
    TLista L = NULL;

    L = CitireLista(&lg);
    //Ex1(L);
    Ex2(L);
    //printf("Dimensiune lista: %d\n", lg);
    //AfisareLista(L);
    //DistrugeLista(&L);
    return 0;
}