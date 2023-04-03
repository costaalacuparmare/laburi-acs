#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nod {
    int info;
    struct nod *st, *dr;
} TNod, *TArb;

TArb Constr_Frunza(int elem);
int InserareABC(TArb *a, int elem);
void RSD(TArb a);
void PrintareArbore(TArb arbore, int spatiu);
void DistrugeArb(TArb *adrArbore);
void AfiArb(TArb r);
void DRS(TArb a);

void DRS_Num(TArb a, int x, int *nr);
int Numara(TArb r, int x);

int NrNiv (TArb r);
int Verif(TArb r, int x);