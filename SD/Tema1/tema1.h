#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX 20
/* MOVE_LEFT / 1
 * MOVE_RIGHT / 2
 * MOVE_LEFT_CHAR / 3 + param
 * MOVE_RIGHT_CHAR / 4 + param
 * INSERT_LEFT / 5 + param
 * INSERT_RIGHT / 6 + param
 * WRITE / 7 + param
 * SHOW_CURRENT / 8
 * SHOW / 9
 * UNDO / 10
 * REDO / 11
*/

/* FUNCTIILE PENTRU COMENZI */

typedef struct command {
    int cod;
    char *param;
} *TCmd;

int Codificare(char *cmd, char **param);

/* FUNCTIILE PENTRU BANDA */

/* definirea benzii ca o lista dublu
 inlantuita cu santinela si un deget */

typedef struct celulaB {
    char info;
    struct celulaB *pre, *urm;
} TCelulaB, *TListaB;

typedef struct banda {
    TListaB santinela;
    TListaB deget;
} *TBanda;


/* functiile folosite pentru crearea benzii */

TBanda AlocCelulaB(char x);
TBanda InitB();

void MOVE_LEFT(TBanda *deget);
void MOVE_RIGHT(TBanda *deget);
void MOVE_LEFT_CHAR(TBanda *deget, char x);
void MOVE_RIGHT_CHAR(TBanda *deget, char x);
void WRITE (TBanda *B, char x);
void INSERT_LEFT(TBanda *deget, char c);
void SHOW_CURRENT(TBanda *deget);

//FUNCTIILE PENTRU COADA

#define _COADA_DINAMICA_

typedef struct celula {
    TCmd info;
    struct celula* urm;
} TCelula, *TLista;

typedef struct coada {
    TLista inc, sf;       /* adresa primei si ultimei celule */
} *TCoada;

TCoada InitQ ();

int ExtrQ(TCoada*c, int *x);
int IntrQ(TCoada *c, TCmd x);
void DistrQ(TCoada **c);

void AfisareQ(TCoada *c);

//STIVA

typedef struct stiva {
    TLista vf;
} *TStiva;

TStiva InitS();

//Functii

void Init(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo);

void Run(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo);

void Read(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo);

