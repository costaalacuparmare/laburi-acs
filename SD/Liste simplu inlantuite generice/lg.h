#include <stdio.h>
#include <stdlib.h>

typedef struct celGenerica {
    void *info;
    struct celGenerica *urm;
}TCelulaG, *TLG;
/* La fel ca in laboratorul 1, numai ca retinem 'void*' in loc de 'int' */

//Ex1
typedef int (*TFCond) (void *elem);
int nr_pare (TLG L, TFCond VerifPar);

//Ex2
typedef struct carti {
	char *autor;
	char *titlu;
	x
};
typedef int (*TFComp) (void *elem1, void *elem2);
void ElimPer (void *elem, TFComp Comp);

TLG AlocCelulaG(void *elem);
int InserareLG(TLG* aL, void *elem);
TLG CitireLG(int *dimLista);
void AfisareLG(TLG L, void (*afisareElem)(void *));
void DistrugeLG(TLG* aL, void (*stergeElem)(void *));