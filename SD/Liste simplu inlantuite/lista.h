#include <stdio.h>
#include <stdlib.h>

/* Test lista vida */
#define ListaVida(L) (L == NULL)

typedef struct Celula{
    int info;
    struct Celula *urm;
} TCelula, *TLista;
/* TCelula este un o variabila care retine 'info' si 'urm'
   TLista este un pointer catre tipul TCelula 
*/

TLista AlocCelula(int elem);
TLista CitireLista(int *dimLista);
void AfisareLista(TLista L);
void DistrugeLista(TLista* aL);
void L1Ex1(TLista L);
void L1Ex2(TLista L);
TLista L2Ex2(TLista L, int a, int b, int *dim);