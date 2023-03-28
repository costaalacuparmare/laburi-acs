#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/* definire lista dublu inlantuita cu santinela */

typedef struct celulaB {
    char info;
    struct celula *pre, *urm;
} TCelulaB, *TBanda;

TLista2 AlocCelula2(int x);
TLista2 InitLista2();

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