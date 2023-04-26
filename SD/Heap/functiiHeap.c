#include "heap.h"

THeap* AlocaHeap(int nrMax, TFCmp comp) {
    THeap* h = (THeap*) malloc(sizeof(struct Heap));
    if (!h) {
        return NULL;
    }

    h->v = (int *) malloc(nrMax * sizeof(int));
    if (!h->v) {
		free(h);
		return NULL;
	}

    h->nrMax = nrMax;
    h->nrElem = 0;
    h->comp = comp;

    return h;
}

int RelMinHeap(int a, int b) {
	return a < b;
}

int RelMaxHeap(int a, int b) {
	return a > b;
}

void AfisareHeap(THeap* h, int pos) {
    if (pos >= h->nrMax) {      
        printf("-"); 
        return;
    }
    
    printf(" %d ", h->v[pos]);
	printf("(");
	
    AfisareHeap(h, 2 * pos + 1);
	printf(",");
	
    AfisareHeap(h, 2 * pos + 2);
	printf(")");
}

void DistrugeHeap(THeap **h) {
	free((*h)->v);
	free(*h);
	*h = NULL; 
}

void Heapify(THeap *h, int c_id) {
	int p_id = 0;
	if (c_id != 0) {
		p_id = (c_id - 1) / 2;
		if (!h->comp(h->v[p_id], h->v[c_id])) {
			int tmp = h->v[p_id];
			h->v[p_id] = h->v[c_id];
			h->v[c_id] = tmp;
			Heapify(h, p_id);
		}
	}
}

//Lab 7 ex 1 -

//Lab 7 ex 2 -