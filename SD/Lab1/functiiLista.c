#include "lista.h"
/* Aloca un element de tip Celula si returneaza pointerul aferent */
TLista AlocCelula(int elem) {
    TLista aux = (TLista) malloc(sizeof(TCelula));   /* alocare */
    if (aux) {                                    /* aux != NULL */
        aux->info = elem;
        aux->urm = NULL;
    }
    return aux;                                   /* returnare adresa sau NULL */
}

/* Citeste de la tastatura numere de adaugat in lista */
TLista CitireLista(int *dimLista) {
    TLista L = NULL, aux, ultim;
    int x;
    char ch;
    *dimLista = 0;
    
    printf("Introduceti numerele de adaugat in lista:\n");
    while (scanf("%i", &x) == 1) {   /* se citesc numere pana cand se citeste un caracter */
        
        aux = AlocCelula(x);
        if (!aux) {                  /* aux == NULL, !aux != NULL */
            return L;
        }

        if (L == NULL) {             /* initializare cap de lista */
            L = aux;
        } else {                     /* adaugare celula la final de lista */
            ultim->urm = aux;
        }

        ultim = aux;                 /* pointerul pentru ultima celula este actualizat */
        (*dimLista)++;
    }

    return L;
}

/* Afisare continut lista */
void AfisareLista(TLista L) {
    printf("Lista: [");
    while (L) {                   /* L != NULL */
        printf("%d ", L->info);   
        L = L->urm;
    }
    printf("]\n");
}

/* Dezalocare memorie lista */
void DistrugeLista(TLista* aL) {
    TLista aux;
    while (*aL) {           /* *aL != NULL, dereferentiere adresa aL */
        aux = *aL;
        *aL = (*aL)->urm;   
        free(aux);
    }
}
/* Exercitii laborator */
void Ex1(TLista L)
{
    TLista aux = (TLista) malloc(sizeof(TLista));
    if(!aux) return;
    int i, nr_per = 0;
    for (aux = L, i = 1; aux->urm != NULL; aux = aux->urm, i++)
        if (aux->info % 2 == aux->urm->info % 2) {
            printf("(%d,%d): %d %d\n", i, i + 1, aux->info, aux->urm->info);
            nr_per++;
        }
    printf("%d\n",nr_per);
    free(aux);
}

void Ex2(TLista L)
{
    TLista aux;
    int i, new_sec = 0, ind1 = 0;
    for (aux = L, i = 1; aux->urm != NULL; aux = aux->urm, i++) {
        if (!new_sec) {
            ind1 = i;
        }
        if (aux->info > aux->urm->info) {
            if(new_sec > 1)
                printf("inceput: %d sfarsit: %d\n",ind1,i);
            new_sec = 0;
        }
        else {
            new_sec++;
        }
    }
}