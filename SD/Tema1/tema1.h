#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/* definire lista dublu inlantuita cu santinela */

typedef struct celula2 {
    int info;
    struct celula2 *pre, *urm;
} TCelula2, *TLista2;

TLista2 AlocCelula2(int x);
TLista2 InitLista2();
