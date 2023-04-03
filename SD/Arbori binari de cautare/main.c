#include "arbBC.h"

int main() {
    int v[] = {5, 3, 9, 1, 6, 7, 2};
    int nrNoduri = sizeof(v)/sizeof(v[0]);
    TArb arbore = NULL;
    
    for (int i = 0; i < nrNoduri; i++) {
        InserareABC(&arbore, v[i]);
    }

    AfiArb(arbore);

    /* Ex1 Lab5 */
    int x = 16;
//    printf("Numarul de numere: %d\n",Numara(arbore,x));
    /* Ex2 Lab5 */
    printf("%d\n",Verif(arbore,x));
    DistrugeArb(&arbore);
    return 0;
}