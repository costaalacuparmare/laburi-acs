#include <stdio.h>
#include <stdlib.h>

typedef struct celGenerica {
    void *info;
    struct celGenerica *urm;
}TCelulaG, *TLG;
/* La fel ca in laboratorul 1, numai ca retinem 'void*' in loc de 'int' */

TLG AlocCelulaG(void *elem);
int InserareLG(TLG* aL, void *elem);
TLG CitireLG(int *dimLista);
void AfisareLG(TLG L, void (*afisareElem)(void *));
void DistrugeLG(TLG* aL, void (*stergeElem)(void *));