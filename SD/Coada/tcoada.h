/*-- tcoada.h -- coada este reprezentata ca Lista DESCHISA --*/
#include <stdlib.h>
#include <stdio.h>

#define _COADA_DINAMICA_

typedef struct celula
{ 
  int info;
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