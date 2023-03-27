/*--- tarb.h ---*/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifndef ARBORE_BINAR
#define ARBORE_BINAR

typedef struct nod {
	int info;
	struct nod *st, *dr;
} TNod, *TArb;

/*-- Operatii elementare --*/
TArb InitA();           /* initializare arbore */
TArb ConstrNod(int x, TArb s, TArb d);  /* -> adresa nod (cu info x, fiu stanga s, fiu dreapta d)
sau NULL daca nu exista spatiu */
TArb ConstrFr(int x); /* -> adresa frunza cu informatia x, sau NULL daca nu exista spatiu */
TArb ConstrAA (int lim, int nn, int v1, int v2);
void DistrArb(TArb*);    /* distruge arbore */
int NrNoduri(TArb);     /* numar noduri */

/*-- Operatii suplimentare --*/
void AfiArb(TArb r); /*- afiseaza arborele r -*/

#endif

#ifndef _random_
#define _random_
#define random(n) (rand() % (n))
#define randomize() (srand((unsigned int)time(NULL)))
#endif
