/* CONSTANTINESCU Vlad - 314CB */

#include "tema1.h"

void Init(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo) {
    *B = InitB();
    *Q = InitQ();
    *Undo = InitS();
    *Redo = InitS();
}

TBanda InitB() {

    /* creem banda returnand santinela si
    inseram primul element # catre care va pointa degetul*/
    TBanda aux;
    aux = (TBanda) malloc(sizeof(TBanda));
    if (!aux)
        return NULL;
    TListaB aux2 = (TListaB) malloc(sizeof(TCelulaB));
    if (!aux2)
        return NULL;

    aux->santinela->pre = NULL;
    aux->santinela->urm = aux2;
    aux2->info = '#';
    aux2->pre = aux->santinela;
    aux2->urm = NULL;
    aux->deget = aux2;
    return aux;
}

TCoada InitQ () {
    TCoada c;
    c = (TCoada) malloc(sizeof(TCoada));
    if (!c) return NULL;
    c->inc = c->sf = NULL;
    return c;
}

TStiva InitS() {
    TStiva s;
    s = (TStiva) malloc(sizeof(TStiva));
    if (!s) return NULL;
    s->vf = NULL;
    return s;
}

/*int Codificare(char *cmd, char *param) {

    char *p = (char *) malloc (sizeof(MAX));
    strcpy(p,cmd);
    if (strcmp(cmd,"MOVE_LEFT") == 0)
        return 1;
    if (strcmp(cmd,"MOVE_RIGHT") == 0)
        return 2;
    if (cmd[MAX/2+1] == 'C') {
        param = strtok(p," ");
        param = strtok(NULL,"\0");
        if(cmd[MAX/4] == 'L') {

            return 3;
        }
        else
            return 4;
    }
    if (cmd[0] == 'I') {
        param = strtok(p, " ");
        param = strtok(NULL, "\0");
        if (cmd[7] == 'L') {
            return 5;
        } else
            return 6;
    }
    if (cmd[0] == 'W') { // de rez cu strchr
        *param = (char) strtok(p," ");
        *param = (char) strtok(NULL,"\0");
        return 7;
    }
    if (strcmp(cmd,"SHOW_CURRENT") == 0)
        return 8;
    if (strcmp(cmd,"SHOW") == 0)
        return 9;
    if (strcmp(cmd,"UNDO") == 0)
        return 10;
    if (strcmp(cmd,"REDO") == 0)
        return 11;
}*/

void CitireFisier(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo) {
    char *cmd = (char *) malloc(MAX*sizeof(char));
    if (!cmd) return;
    int cmd_nr;

    FILE *input = fopen("tema1.in","rt");
    FILE *output = fopen("tema1.out","w+");

    fscanf(input,"%d",&cmd_nr);
    fprintf(output, "%d\n", cmd_nr);

    for (int i = 0; i < cmd_nr; i++) {
        //fgets(cmd_arr,MAX,input);
        fscanf(input, "%s", cmd);
        //if (strchr(cmd,'_')
        fprintf(output, "%s\n", cmd);
    }
}
/*
/* FUNCTIILE PENTRU BANDA */

/* Aloca un element de tip TCelulaB si returneaza pointerul aferent */
/*
TBanda AlocCelulaB(char x) {
    TBanda aux = (TBanda) malloc(sizeof(TBanda));
    if (!aux) {
        return NULL;
    }
    aux->sant = x;
    aux->pre = aux->urm = NULL;
    return aux;
}

/* Creeaza santinela pentru banda */


/*
TBanda CitireBanda(TBanda *deget) {

    /* initializam banda si verificam */


    //ultim = L;

//}
/*
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

void SHOW_CURRENT (TBanda *deget) {
    fprintf(output,"%c\n",(*deget)->info);
}


int IntrQ(TCoada *c, int x)
{
    TLista aux;
    aux = (TLista)malloc(sizeof(TCelula));
    if ( ! aux) return 0;

    aux->info = x; aux->urm = NULL;

    if (c->sf != NULL)
        c->sf->urm = aux;
    else
        c->inc = aux;
    c->sf = aux;
    return 1;
}

int ExtrQ(TCoada *c, int *x)
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

void DistrQ(TCoada **c)
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

void AfisareQ(TCoada *c)
{
    TLista p;
    if(c->inc == NULL)
    {
        printf("Coada vida\n");
        return;
    }
    printf("Elementele cozii: ");
    for(p = c->inc; p != NULL; p = p->urm)
        printf("%d ", p->info);
    printf("\n");
}
 */