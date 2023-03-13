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

/* Insereaza dupa o celula */
int InserareDupa (TLista L, int x, int ref)
{
    TLista aux, p;
    for (p = L; p != NULL; p = p->urm)
        if(p->info == ref)
            break;
        if(!p) return 0;
        aux = AlocCelula(x);
        if(!aux) return 0;
        aux->urm = p->urm;
        p->urm = aux;
        return 1;
}

/* Insereaza inaintea unei celule */
int InserareInainte (TLista *L, int x, int ref)
{
    TLista aux, ant, p;
    for (ant = NULL, p = *L; p != NULL; ant = p, p = p->urm)
        if(p->info == ref)
            break;
    if(!p) return 0;
    aux = AlocCelula(x);
    if(!aux) return 0;
    aux->urm = p;
    if(ant == NULL)
        *L = aux;
    else
        ant->urm = aux;
    return 1;
}

/* Insereaza la inceputul listei */
int InserareInceput (TLista *L, int x)
{
    TLista aux = AlocCelula(x);
    if(!aux) return 0;
    aux->urm = *L;
    *L = aux;
    return 1;
}

/* Insereaza la sfarsitul listei */
int InserareSf (TLista *L, int x)
{
    TLista p, aux, ultim = NULL;
    p = *L;
    while(p!=NULL)
    {
        ultim = p;
        p = p->urm;
    }
    aux = AlocCelula(x);
    if(!aux) return 0;
    if(ultim)
        ultim->urm = aux;
    else
        *L = aux;
    return 1;
}

/* eliminare element */
int EliminaL (TLista *L, int x)
{
    TLista aux, ant;
    for ( ant = NULL, aux = *L; aux != NULL; ant = aux, aux = aux->urm)
        if(aux->info == x)
            break;
    if(aux == NULL)
        return 0;
    if(ant)
        ant->urm = aux->urm;
    else
        *L = aux->urm;
    free(aux);
    return 1;
}

/* Exercitii laborator1 */
void L1Ex1(TLista L)
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

void L1Ex2(TLista L)
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

/* Exercitii Laboratorul 2 */
TLista L2Ex1 (TLista *L, int k, int *dim)
{
    //functia face o noua lista prin mutare a ele, div cu k
    TLista aux, Lnou, p, ant;
    for (aux = *L; aux->urm != NULL; aux = aux->urm)
        if (aux->info % k == 0) {

            if (Lnou == NULL) {
                InserareInceput(&Lnou, aux->info);
                EliminaL(L, aux->info);
            } else {
                for(ant = NULL, p = Lnou; p && p->info < aux->info; ant = p, p = p->urm) {
                    InserareInainte(&Lnou, aux->info, p->info);
                    EliminaL(L,aux->info);
                }
            }
            (*dim++);
        }
    return Lnou;
}

TLista L2Ex2 (TLista L, int a, int b, int *dim)
{
    TLista aux, Lnou = NULL, ant;
    for (aux = L; aux->urm != NULL; aux = aux->urm) {
        if (aux->info >= a && aux->info <= b) {
            if (Lnou == NULL) {
                InserareInceput(&Lnou, aux->info);
                ant = aux;
            } else {
                InserareDupa(Lnou, aux->info, ant->info);
                ant = aux;
            }
            (*dim)++;
        }
        if (aux->info >= b)
            break;
    }
    if(!dim)
        return NULL;
    else
        return Lnou;
}