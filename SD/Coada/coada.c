/*-- TcoadaLD1.c -- coada este reprezentata ca Lista DESCHISA
                 -- Operatii de baza --*/
#include "tcoada.h"


TCoada* InitQ ()  /* creeaza coada vida cu elemente de dimensiune d;
				   anumite implementari pot necesita si alti parametri */
{ 
  TCoada* c;          /* spatiu pentru descriptor coada */
  c = (TCoada*)malloc(sizeof(TCoada));
  if ( ! c ) return NULL;                  /* nu exista spatiu -> "esec" */

  c->inc = c->sf = NULL;
  return c;          /* intoarce adresa descriptorului cozii */
}

int IntrQ(TCoada *c, int x)  /* adauga element la sfarsitul cozii */
{ 
  TLista aux;
  aux = (TLista)malloc(sizeof(TCelula));      /* aloca o noua celula */
  if ( ! aux) return 0;             /* alocare imposibila -> "esec" */

  aux->info = x; aux->urm = NULL;

  if (c->sf != NULL)          /* coada nevida */
    c->sf->urm = aux;                   /* -> leaga celula dupa ultima din coada */
  else                              /* coada vida */
    c->inc = aux;                    /* -> noua celula se afla la inceputul cozii */
  c->sf = aux;  	            /* actualizeaza sfarsitul cozii */
  return 1;                         /* operatie reusita -> "succes" */
}

int ExtrQ(TCoada *c, int *x)  /* extrage primul element din coada la adresa ae */
{
    TLista aux;
    if(c->inc == NULL)
        return 0;
    aux = c->inc;
    *x = c->inc->info;
    c->inc = c->inc->urm;
    free(aux);
    return 1;
}

void DistrQ(TCoada **c) /* distruge coada */
{
  TLista p, aux;
  p = (*c)->inc;
  while(p)
  {
    aux = p;
    p = p->urm;
    free(aux);
  }
  free(*c);
  *c = NULL;
}

void AfisareQ(TCoada *c)  /* afisare elementele cozii */
{
  TLista p;
  if(c->inc == NULL)  /* coada vida */
  {
    printf("Coada vida\n");
    return;
  } 
  printf("Elementele cozii: ");
  for(p = c->inc; p != NULL; p = p->urm)
    printf("%d ", p->info);
  printf("\n");
}

//Lab 3, Ex1, b)
TCoada *Qpar(TCoada *c)
{
    TCoada *r;
    r = InitQ();
    if(!r) return NULL;
    int x = 0;
    while(ExtrQ(c,&x)) {
        if (x % 2 == 0)
            IntrQ(r, x);
        return r;
    }
}