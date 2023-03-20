#include "lista2.h"

/* Aloca un element de tip TCelula2 si returneaza pointerul aferent */
TLista2 AlocCelula2(int x) {
    TLista2 aux = (TLista2) malloc(sizeof(TCelula2));
    if (!aux) {
        return NULL;
    }

    aux->info = x;
    aux->pre = aux->urm = NULL;

    return aux;
}

/* Creeaza santinela pentru lista folosita */
TLista2 InitLista2() {
    TLista2 aux = (TLista2) malloc(sizeof(TCelula2));
    if (!aux) {
        return NULL;
    }

    aux->info = 0;                  /* informatia din santinela are valoarea 0 */
    aux->pre = NULL;
    aux->urm = NULL;

    return aux;
}

/* Citeste de la tastatura numere de adaugat in lista */
TLista2 CitireLista2(int* dimLista) {
    TLista2 L = NULL, aux, ultim;
    int x;
    
    *dimLista = 0;
    L = InitLista2();   /* creeaza santinela */
    if(!L) return NULL;

    ultim = L;
    printf("Introduceti numerele de adaugat in lista:\n");
    while (scanf("%i", &x) == 1) {   /* se citesc numere pana cand se citeste un caracter */
        aux = AlocCelula2(x);
        if(!aux) return L;

        ultim->urm = aux;
        aux->pre = ultim;
        ultim = aux;

        (*dimLista)++;
    }

    return L;
}

/* Afisare continut lista */
void AfisareLista2(TLista2 L) {
    TLista2 p = L->urm;    

    printf("Lista: [");
    while (p != NULL) {         /* parcurgere lista */
        printf("%d ", p->info);   
        p = p->urm;
    }
    printf("]\n");
}

/* Distrugere lista */
void DistrugeLista2(TLista2 *aL) {
    TLista2 p = (*aL)->urm, aux;
    while (p != NULL) {         /* distrugere elementele listei */
        aux = p;
        p = p->urm;
        free(aux);
    }

    free(*aL);                  /* distrugere santinela */
    *aL = NULL;
}

// Lab3 Ex 2 - inserare in fata celulei ref pentru toate celulele cu val ref

int InsrX (TLista2 *aL, int x, int ref)
{
    TLista2 aux, ant, p;
    int nr = 0;
    for (p = *aL; p != NULL; p = p->urm)
        if(p->info == ref) {
            aux = AlocCelula2(x);
            if(!aux) return 0;
            aux->urm = p;
            aux->pre = p->pre;
            p->pre->urm = aux;
            aux->urm->pre = p;
            nr++;
        }
    return nr;
}