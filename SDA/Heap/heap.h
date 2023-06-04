#include <stdio.h>
#include <stdlib.h>

typedef int (*TFCmp)(int, int);

typedef struct Heap {
    int nrMax, nrElem;
    int *v;
    TFCmp comp;
} THeap;

THeap* AlocaHeap(int nrMax, TFCmp comp);
int RelMinHeap(int a, int b);
int RelMaxHeap(int a, int b);
void AfisareHeap(THeap *h, int pos);
void DistrugeHeap(THeap **h);

void Heapify(THeap *h, int c_id);