#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20

/* FUNCTIILE PENTRU BANDA */

/* definirea benzii ca o lista dublu
 inlantuita cu santinela */

typedef struct celulaB {
    char info;
    struct celulaB *pre, *urm;
} TCelulaB, *TBanda;

/* functiile folosite pentru crearea benzii */

void Citire();

TBanda AlocCelulaB(char x);
TBanda InitBanda(TBanda * deget);

void MOVE_LEFT(TBanda *deget);
void MOVE_RIGHT(TBanda *deget);
void MOVE_LEFT_CHAR(TBanda *deget, char x);
void MOVE_RIGHT_CHAR(TBanda *deget, char x);
void WRITE (TBanda *B, char x);
void INSERT_LEFT(TBanda *deget, char c);

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