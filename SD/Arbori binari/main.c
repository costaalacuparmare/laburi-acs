/**-- test-ab.c --  prelucreaza arbori binari cu chei intregi --*/
#include "tarb.h"


int main ()
{
	TArb arb = NULL;
	int nr_info = 0;
	randomize();
	arb = ConstrAA (5, random(16), -50, 50);

	AfiArb (arb);
	printf ("noduri: %i\n", NrNoduri(arb));
    printf("Numar de noduri pt ex 1 %d\n", Numara(arb));
    Parcurgere(arb,&nr_info);
    printf("Numar de noduri pt ex 2 %d\n", nr_info);
    if (Verifica(arb))
        printf("Toate au\n");
    else
        printf("N-au\n");
	/*-- se completeaza cu apelurile functiilor implementate --*/

	DistrArb (&arb);
	return 0;
}
