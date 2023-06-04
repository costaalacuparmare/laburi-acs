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
    printf("Numar de noduri pt lab 4 ex 1 %d\n", Numara(arb));
    Parcurgere(arb,&nr_info);
    printf("Numar de noduri pt lab 4 ex 2 %d\n", nr_info);
    printf("lab 4 ex3: ");
    if (Verifica(arb))
        printf("Toate au\n");
    else
        printf("N-au\n");
    printf("Niv cel mai mic cu frunza: %d\n",Check_Fr(arb,0));
	/*-- se completeaza cu apelurile functiilor implementate --*/
	printf("Procent de noduri pare in nivelele pana in %d: %.2f%%\n", 3, procent(arb,3));
	DistrArb (&arb);
	return 0;
}
