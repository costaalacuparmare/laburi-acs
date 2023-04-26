#include "heap.h"

int main() {
    int v[] = {2, 5, 3};
    int dimVec = sizeof(v) / sizeof(v[0]);
    THeap* h = NULL;

    h = AlocaHeap(dimVec, RelMinHeap);
    for (int i = 0; i < dimVec; i++) {
        h->nrElem++;
        h->v[i] = v[i];
		Heapify(h,i);
    }

    AfisareHeap(h, 0);
    printf("\n");
    DistrugeHeap(&h);
}