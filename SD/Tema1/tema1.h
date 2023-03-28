#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/* FUNCTIILE PENTRU BANDA */

/* definirea benzii ca o lista dublu
 inlantuita cu santinela */

typedef struct celulaB {
    char info;
    struct celulaB *pre, *urm;
} TCelulaB, *TBanda;

/* functiile folosite pentru crearea benzii */

TBanda AlocCelulaB(char x);
TBanda InitBanda(TBanda * deget);

//COADA

#define _COADA_DINAMICA_

typedef struct celula
{
    char info;
    struct celula* urm;
} TCelula, *TLista;

typedef struct coada
{
    TLista inc, sf;       /* adresa primei si ultimei celule */
} TCoada;

TCoada* InitQ () ;
int ExtrQ(TCoada*c, int *x);
int IntrQ(TCoada *c, int x);
void DistrQ(TCoada **c);

void AfisareQ(TCoada *c);