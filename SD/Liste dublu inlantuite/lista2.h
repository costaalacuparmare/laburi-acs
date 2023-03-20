#include <stdio.h>
#include <stdlib.h>

/* definire lista dublu inlantuita cu santinela */

typedef struct celula2 {
  int info;              
  struct celula2 *pre, *urm;
} TCelula2, *TLista2;

TLista2 AlocCelula2(int x);
TLista2 InitLista2();
TLista2 CitireLista2();
void AfisareLista2(TLista2 L);
void DistrugeLista2(TLista2 *aL);