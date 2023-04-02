#include "arbBC.h"

int main() {
    int v[] = {15, 3, 31, 14, 7, 28, 16};
    int nrNoduri = sizeof(v)/sizeof(v[0]);
    TArb arbore = NULL;
    
    for (int i = 0; i < nrNoduri; i++) {
        InserareABC(&arbore, v[i]);
    }

    AfiArb(arbore);
    RSD(arbore);
    printf("\n");

    DistrugeArb(&arbore);
    return 0;
}