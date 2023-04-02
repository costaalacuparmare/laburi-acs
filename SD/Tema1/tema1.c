/* CONSTANTINESCU Vlad - 314CB */

#include "tema1.h"

/* functii auxiliare */

/* banda */

TBanda InitB() {

    /* creem banda returnand santinela si
    inseram primul element # catre care va pointa degetul*/
    TBanda aux = (TBanda) malloc(sizeof(TBanda));
    if (!aux) return NULL;
    aux->santinela = (TListaB) malloc(sizeof(TCelulaB));
    if (!aux->santinela) return NULL;
    TListaB aux2= (TListaB) malloc(sizeof(TCelulaB));
    if (!aux2) return NULL;
    aux->santinela->pre = NULL;
    aux->santinela->urm = aux2;
    aux2->info = '#';
    aux2->pre = aux->santinela;
    aux2->urm = NULL;
    aux->deget = aux2;
    return aux;
}

TListaB PushB(char x) {
    TListaB aux = (TListaB) malloc(sizeof(TCelulaB));
    if (!aux) return NULL;
    aux->info = x;
    aux->pre = aux->urm = NULL;
    return aux;
}

void FreeB (TBanda *B) {
    TListaB p = NULL;
    TListaB aux = NULL;
    p = (*B)->santinela;
    while(p)
    {
        aux = p;
        p = p->urm;
        free(aux);
    }
    free(*B);
    *B = NULL;
}

/* coada */

TCoada InitQ () {
    TCoada Q = (TCoada) malloc(sizeof(TCoada));
    if (!Q) return NULL;
    Q->inc = Q->sf = NULL;
    return Q;
}

void PushQ(TCoada *Q, TCmd x) {
    TListaC aux = (TListaC) malloc(sizeof(TCelulaC));
    if (!aux) return;
    aux->info = (TCmd) malloc(sizeof(TCmd));
    if (!aux->info) return;
    aux->info->cod = x->cod;
    aux->info->param = x->param;
    aux->urm = NULL;
    if ((*Q)->inc != NULL)
        (*Q)->sf->urm = aux;
    else
        (*Q)->inc = aux;
    (*Q)->sf = aux;
}

void PopQ(TCoada *Q)
{
    TListaC aux = NULL;
    if((*Q)->inc == NULL)
        return;
    aux = (*Q)->inc;
    (*Q)->inc = (*Q)->inc->urm;
    free(aux);
}

void FreeQ(TCoada *Q)
{
    TListaC p = NULL;
    TListaC aux = NULL;
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

/* stiva */

TStiva InitS() {
    TStiva s = (TStiva) malloc(sizeof(TStiva));
    if (!s) return NULL;
    s->vf = NULL;
    return s;
}

void PopS(TStiva *S)
{
    TListaS aux = NULL;
    if((*S)->vf == NULL) return;
    aux = (*S)->vf;
    (*S)->vf = (*S)->vf->urm;
    free(aux);
}

void PushS(TStiva *S, TListaB x) {
    TListaS aux = (TListaS) malloc(sizeof(TCelulaS));
    if (!aux) return;
    aux->info = (TListaB) malloc(sizeof(TCelulaS));
    if (!aux->info) return;
    aux->info = x;
    if ((*S)->vf != NULL)
        aux->urm = (*S)->vf;
    else
        aux->urm = NULL;
    (*S)->vf = aux;
}

void FreeS(TStiva *S) {
    TListaS p = NULL;
    TListaS aux = NULL;
    p = (*S)->vf;
    while (p) {
        aux = p;
        p = p->urm;
        free(aux);
    }
    free(*S);
    *S = NULL;
}
void Init(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo) {
    *B = InitB();
    *Q = InitQ();
    *Undo = InitS();
    *Redo = InitS();
}

/* functiile comenzi */

void EXECUTE(TBanda *B, TCoada *Q, TStiva *Undo, FILE *output) {
    char param = (*Q)->inc->info->param;
    switch ((*Q)->inc->info->cod) {
        case ONE: {
            MOVE_LEFT(B, Undo);
            break;
        }
        case TWO: {
            MOVE_RIGHT(B, Undo);
            break;
        }
        case THREE: {
            MOVE_LEFT_CHAR(B, param, output);
            break;
        }
        case FOUR: {
            MOVE_RIGHT_CHAR(B, param);
            break;
        }
        case FIVE: {
            WRITE(B, param);
            break;
        }
        case SIX: {
            INSERT_LEFT(B, param, output);
            break;
        }
        case SEVEN: {
            INSERT_RIGHT(B, param);
            break;
        }
    }
    PopQ(Q);
}

void MOVE_LEFT(TBanda *B, TStiva *Undo) {
    if ((*B)->deget->pre->pre == NULL) return;
    (*B)->deget = (*B)->deget->pre;
    PushS(Undo, (*B)->deget->urm);
}

void MOVE_RIGHT(TBanda *B, TStiva *Undo) {
    TListaB aux = NULL;
    if((*B)->deget->urm == NULL) {
        aux = PushB('#');
        if (!aux) return;
        aux->urm = NULL;
        aux->pre = (*B)->deget;
        (*B)->deget->urm = aux;
    }
    (*B)->deget = (*B)->deget->urm;
    PushS(Undo, (*B)->deget->pre);
}

void MOVE_LEFT_CHAR (TBanda *B, char param, FILE *output) {
    TListaB p = NULL;
    int verif = 0;
    if ((*B)->deget->info == param)
        return;
    for(p = (*B)->deget; p != (*B)->santinela; p = p->pre)
        if(p->info == param) {
            (*B)->deget = p;
            verif = 1;
            break;
        }
    if(!verif)
        fprintf(output, "ERROR\n");
}

void MOVE_RIGHT_CHAR (TBanda *B, char param) {
    TListaB p = NULL;
    int verif = ZERO;
    if((*B)->deget->info == param)
        return;
    for(p = (*B)->deget; p != NULL; p = p->urm)
        if(p->info == param) {
            (*B)->deget = p;
            verif = ONE;
            break;
        }
    if(!verif) {
        TListaB aux = PushB('#');
        if (!aux) return;
        aux->urm = NULL;
        for(;(*B)->deget->urm != NULL; (*B)->deget =(*B)->deget->urm);
        aux->pre = (*B)->deget;
        (*B)->deget->urm = aux;
        (*B)->deget = (*B)->deget->urm;
    }
}

void WRITE (TBanda *B, char param) {
    (*B)->deget->info = param;
}

void INSERT_LEFT(TBanda *B, char param, FILE *output) {
    if((*B)->deget->pre->pre == NULL) {
        fprintf(output, "ERROR\n");
        return;
    }
    TListaB aux = PushB(param);
    if(!aux) return;
    aux->urm = (*B)->deget;
    aux->pre = (*B)->deget->pre;
    (*B)->deget->pre->urm = aux;
    (*B)->deget->pre = aux;
    (*B)->deget = aux;
}

void INSERT_RIGHT(TBanda *B, char param) {
    TListaB aux = PushB(param);
    if ((*B)->deget->urm == NULL) {
        (*B)->deget->urm = aux;
        aux->pre = (*B)->deget;
        (*B)->deget = aux;
        return;
    }
    aux->urm = (*B)->deget->urm;
    aux->pre = (*B)->deget;
    (*B)->deget->urm->pre = aux;
    (*B)->deget->urm = aux;
    (*B)->deget = aux;
}

void SHOW_CURRENT(TBanda *B, FILE *output) {
    fprintf(output,"%c\n",(*B)->deget->info);
}

void SHOW(TBanda *B, FILE *output) {
    TListaB p = NULL;
    for (p = (*B)->santinela->urm; p != NULL; p = p->urm)
        if (p == (*B)->deget)
            fprintf(output, "|%c|", p->info);
        else
            fprintf(output, "%c",p->info);
    fprintf(output, "\n");
}

void UNDO(TBanda *B, TStiva *Undo, TStiva *Redo) {
    PushS(Redo,(*B)->deget);
    (*B)->deget = (*Undo)->vf->info;
    PopS(Undo);
}

void REDO(TBanda *B, TStiva *Undo, TStiva *Redo) {
    if (!(*Redo)->vf->info->urm)
        PushS(Undo,(*Redo)->vf->info->pre);
    else
        PushS(Undo,(*Redo)->vf->info->urm);
    (*B)->deget = (*Redo)->vf->info;
    PopS(Redo);
}

/* functii de implementare */

int Code(char *cmd, char *param) {
    if (strcmp(cmd,"EXECUTE\n") == ZERO ||
        strcmp(cmd,"EXECUTE") == ZERO)
        return ZERO;
    if (strcmp(cmd,"MOVE_LEFT\n") == ZERO ||
        strcmp(cmd,"MOVE_LEFT") == ZERO)
        return ONE;
    if (strcmp(cmd,"MOVE_RIGHT\n") == ZERO ||
        strcmp(cmd,"MOVE_RIGHT") == ZERO)
        return TWO;
    if (cmd[TEN] == 'C' || cmd[ELEVEN] == 'C') {
        *param = cmd[strlen(cmd) - TWO];
        if(cmd[FIVE] == 'L') {

            return THREE;
        }
        else
            return FOUR;
    }
    if (cmd[ZERO] == 'W') {
        *param = cmd[strlen(cmd) - TWO];
        return FIVE;
    }
    if (cmd[ZERO] == 'I') {
        *param = cmd[strlen(cmd) - TWO];
        if (cmd[SEVEN] == 'L') {
            return SIX;
        } else
            return SEVEN;
    }
    if (strcmp(cmd,"SHOW_CURRENT\n") == ZERO ||
        strcmp(cmd,"SHOW_CURRENT") == ZERO)
        return EIGHT;
    if (strcmp(cmd,"SHOW\n") == ZERO ||
        strcmp(cmd,"SHOW") == ZERO)
        return NINE;
    if (strcmp(cmd,"UNDO\n") == ZERO ||
        strcmp(cmd,"UNDO") == ZERO)
        return TEN;
    if (strcmp(cmd,"REDO\n") == ZERO ||
        strcmp(cmd,"REDO") == ZERO)
        return ELEVEN;
}

TCmd Read(FILE *input) {
    char *cmd = (char *) malloc(MAX * sizeof(char));
    if (!cmd) return ZERO;
    TCmd CMD = (TCmd) malloc(sizeof(TCmd));
    fgets(cmd, MAX, input);
    CMD->param = '\0';
    CMD->cod = Code(cmd, &CMD->param);
    free(cmd);
    return CMD;
}

void Execute(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo,
             TCmd cmd, FILE *output) {
    if (cmd->cod >= ONE && cmd->cod <= SEVEN)
        PushQ(Q,cmd);
    switch(cmd->cod) {
        case ZERO: {
            EXECUTE(B,Q,Undo,output);
            break;
        }
        case EIGHT: {
            SHOW_CURRENT(B,output);
            break;
        }
        case NINE: {
            SHOW(B,output);
            break;
        }
        case TEN: {
            UNDO(B,Undo,Redo);
            break;
        }
        case ELEVEN: {
            REDO(B,Undo,Redo);
            break;
        }
    }
}

void Run(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo) {
    FILE *input = fopen("tema1.in", "rt");
    FILE *output = fopen("tema1.out", "w+");
    int cmd_nr = ZERO;
    fscanf(input, "%d", &cmd_nr);
    TCmd cmd = (TCmd) malloc(sizeof(TCmd));
    Read(input);
    int i = ZERO;
    for (; i < cmd_nr; i++) {
        cmd = Read(input);
        Execute(B, Q, Undo, Redo, cmd, output);
    }
    fclose(input);
    fclose(output);
    free(cmd);
}

void Free(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo) {
    FreeB(B);
    FreeQ(Q);
    FreeS(Undo);
    FreeS(Redo);
}