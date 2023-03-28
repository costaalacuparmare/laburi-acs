/* CONSTANTINESCU Vlad - 314CB */

#include "tema1.h"

void Citire() {
    char *cmd_arr = (char *) malloc(MAX*sizeof(char));
    if (!cmd_arr) return;
    int cmd_nr;
    FILE *input = fopen("tema1.in","rt");
    FILE *output = fopen("tema1.out","w+");
    fscanf(input,"%d",&cmd_nr);
    fprintf(output, "%d", cmd_nr);
}

/* FUNCTIILE PENTRU BANDA */

/* Aloca un element de tip TCelulaB si returneaza pointerul aferent */

TBanda AlocCelulaB(char x) {
    TBanda aux = (TBanda) malloc(sizeof(TCelulaB));
    if (!aux) {
        return NULL;
    }
    aux->info = x;
    aux->pre = aux->urm = NULL;
    return aux;
}

/* Creeaza santinela pentru banda */

TBanda InitBanda(TBanda *deget) {

    /* creem banda returnand santinela si
    inseram primul element # catre care va pointa degetul*/

    TBanda aux = (TBanda) malloc(sizeof(TCelulaB));
    if (!aux)
        return NULL;
    TBanda aux2 = (TBanda) malloc(sizeof(TCelulaB));
    if (!aux2)
        return NULL;

    aux->info = 0;
    aux->pre = NULL;
    aux->urm = aux2;
    aux2->info = '#';
    aux2->pre = aux;
    aux2->urm = NULL;
    (*deget) = aux2;
    return aux;
}

TBanda CitireBanda(TBanda *deget) {

    /* initializam banda si verificam */


    //ultim = L;

}

void MOVE_LEFT(TBanda *deget) {
    if ((*deget)->pre->pre == NULL)
        return;
    (*deget) = (*deget)->pre;
}


void MOVE_RIGHT(TBanda *deget) {
    TBanda aux;
    if((*deget)->urm == NULL) {
        aux = AlocCelulaB('#');
        if (!aux) return;
        aux->urm = NULL;
        aux->pre = (*deget);
        (*deget)->urm = aux;
    }
    (*deget) = (*deget)->urm;
}

void MOVE_RIGHT_CHAR (TBanda *deget, char x) {
    TBanda p, aux;
    int verif = 0;
    for(p = (*deget); p != NULL; p = p->pre)
        if(p->info == x) {
            (*deget) = p;
            verif = 1;
            break;
        }
    if(!verif) {
        aux = AlocCelulaB('#');
        if (!aux) return;
        aux->urm = NULL;
        aux->pre = (*deget);
        (*deget)->urm = aux;
        (*deget) = (*deget)->urm;
    }
}

void MOVE_LEFT_CHAR (TBanda *deget, char c) {
    TBanda p;
    int verif = 0;
    for(p = (*deget); p != NULL; p = p->urm)
        if(p->info == c) {
            (*deget) = p;
            verif = 1;
            break;
        }
    if(!verif)
        printf("ERROR\n");
}

void WRITE (TBanda *deget, char c) {
    (*deget)->info = c;
}

void INSERT_LEFT(TBanda *deget, char c) {
    if((*deget)->pre->pre == NULL)
        printf("ERROR\n");
    TBanda aux = AlocCelulaB(c);
    aux->urm = (*deget);
    aux->pre = (*deget)->pre;
    (*deget)->pre->urm = aux;
    (*deget)->pre = aux;

}

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
