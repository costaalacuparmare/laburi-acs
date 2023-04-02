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
    aux->santinela = (TListaB) malloc(sizeof(TCelulaB));
    if (!aux->santinela)
        return NULL;
    TListaB aux2= (TListaB) malloc(sizeof(TCelulaB));
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
    TCoada Q;
    Q = (TCoada) malloc(sizeof(TCoada));
    if (!Q) return NULL;
    Q->inc = Q->sf = NULL;
    return Q;
}

TStiva InitS() {
    TStiva s;
    s = (TStiva) malloc(sizeof(TStiva));
    if (!s) return NULL;
    s->vf = NULL;
    return s;
}

int Code(char *cmd, char **param) {

    char *p = (char *) malloc (MAX);
    strcpy(p,cmd);
    if (strcmp(cmd,"EXECUTE\n") == 0)
        return 0;
    if (strcmp(cmd,"MOVE_LEFT\n") == 0)
        return 1;
    if (strcmp(cmd,"MOVE_RIGHT\n") == 0)
        return 2;
    if (cmd[11] == 'C' || cmd[10] == 'C') {
        *param = strtok(p," ");
        *param = strtok(NULL,"\n");
        if(cmd[5] == 'L') {

            return 3;
        }
        else
            return 4;
    }
    if (cmd[0] == 'I') {
        *param = strtok(p, " ");
        *param = strtok(NULL, "\n");
        if (cmd[7] == 'L') {
            return 5;
        } else
            return 6;
    }
    if (cmd[0] == 'W') { // de rez cu strchr
        *param = strtok(p," ");
        *param = strtok(NULL,"\n");
        return 7;
    }
    if (strcmp(cmd,"SHOW_CURRENT\n") == 0)
        return 8;
    if (strcmp(cmd,"SHOW\n") == 0)
        return 9;
    if (strcmp(cmd,"UNDO\n") == 0)
        return 10;
    if (strcmp(cmd,"REDO\n") == 0)
        return 11;
}

void PushQ(TCoada *Q, TCmd x) {
    TListaC aux;
    aux = (TListaC) malloc(sizeof(TCelulaC));
    if (!aux) return;
    aux->info = (TCmd) malloc(sizeof(TCmd));
    if (!aux->info) return;
    aux->info->cod = x->cod;
    aux->info->param = x->param;
    aux->urm = NULL;
    if ((*Q)->sf != NULL)
        (*Q)->sf->urm = aux;
    else
        (*Q)->inc = aux;
    (*Q)->sf = aux;
}

void PopQ(TCoada *Q)
{
    TListaC aux;
    if((*Q)->inc == NULL)
        return;
    aux = (*Q)->inc;
    (*Q)->inc = (*Q)->inc->urm;
    free(aux);
}

TCmd Read(FILE *input) {
    char *cmd = (char *) malloc(MAX * sizeof(char));
    if (!cmd) return 0;
    TCmd CMD = (TCmd) malloc(sizeof(TCmd));
    fgets(cmd, MAX, input);
    CMD->param = NULL;
    CMD->cod = Code(cmd, &CMD->param);
    return CMD;
}

void Execute(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo,
             TCmd cmd, FILE *output) {
    if (cmd->cod >)
}

void Run(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo) {
    FILE *input = fopen("tema1.in", "rt");
    FILE *output = fopen("tema1.out", "w+");
    int cmd_nr = 0;
    fscanf(input, "%d", &cmd_nr);
    int i;
    TCmd cmd = (TCmd) malloc(sizeof(TCmd));
    Read(input);
    for (i = 0; i < cmd_nr; i++) {
        cmd = Read(input);
        Execute(B, Q, Undo, Redo, cmd, output);
    }
    fclose(input);
    fclose(output);
}


// FUNCTIILE PENTRU BANDA

/* Aloca un element de tip TCelulaB si returneaza pointerul aferent */

TListaB AddCellB(char x) {
    TListaB aux = (TListaB) malloc(sizeof(TCelulaB));
    if (!aux) {
        return NULL;
    }
    aux->pre = x;
    aux->pre = aux->urm = NULL;
    return aux;
}


void MOVE_LEFT(TBanda *B, TStiva *Undo) {
    if ((*B)->deget->pre->pre == NULL)
        return;
    AddCellS()
    (*B)->deget = (*B)->deget->pre;
}

void MOVE_RIGHT(TBanda *B, TStiva *Undo) {
    TListaB aux;
    if((*B)->deget->urm == NULL) {
        aux = AddCellB('#');
        if (!aux) return;
        aux->urm = NULL;
        aux->pre = (*B)->deget;
        (*B)->deget->urm = aux;
    }
    (*B)->deget = (*B)->deget->urm;
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

void WRITE (TBanda *B, char param) {
    (*B)->deget->info = param;
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

void SHOW_CURRENT (TBanda *B, FILE *output) {
    fprintf(output,"%c\n",(*B)->deget->info);
}

void DistrQ(TCoada *Q)
{
    TListaC p, aux;
    p = (*Q)->inc;
    while(p)
    {
        aux = p;
        p = p->urm;
        free(aux);
    }
    free(*Q);
    *Q = NULL;
}

void AfisareQ(TCoada *Q) {
    TListaC p;
    if((*Q)->inc == NULL)
    {
        printf("Coada vida\n");
        return;
    }
    printf("Elementele cozii: ");
    for(p = (*Q)->inc; p != NULL; p = p->urm)
        printf("cod: %d param: %s\n",p->info->cod, p->info->param);
    printf("\n");
}