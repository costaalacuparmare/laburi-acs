/**-- test-ab.c --  prelucreaza arbori binari cu chei intregi --*/
#include "tarb.h"


int main ()
{
	TArb arb = NULL;
	
	randomize();
	arb = ConstrAA (5, random(16), -50, 50);

	AfiArb (arb);
	printf ("noduri: %i\n", NrNoduri(arb));

	/*-- se completeaza cu apelurile functiilor implementate --*/

	DistrArb (&arb);
	return 0;
}
