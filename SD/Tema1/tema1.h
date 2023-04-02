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

int Code(char *cmd, char **param);

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


//STIVA

typedef struct celulaS {
    TlistaB info;
    struct celulaS* urm;
} TCelulaS, *TListaS;

typedef struct stiva {
    TListaS vf;
} *TStiva;

TStiva InitS();

/* functiile folosite pentru crearea benzii */

TListaB AddCellB(char x);
TBanda InitB();

void MOVE_LEFT(TBanda *B, TStiva *Undo);
void MOVE_RIGHT(TBanda *B, TStiva *Undo);
void MOVE_LEFT_CHAR(TBanda *deget, char x);
void MOVE_RIGHT_CHAR(TBanda *deget, char x);
void WRITE (TBanda *B, char x);
void INSERT_LEFT(TBanda *deget, char c);
void SHOW_CURRENT(TBanda *B, FILE *output);

//FUNCTIILE PENTRU COADA

typedef struct celulaC {
    TCmd info;
    struct celulaC* urm;
} TCelulaC, *TListaC;

typedef struct coada {
    TListaC inc, sf;       /* adresa primei si ultimei celule */
} *TCoada;

TCoada InitQ ();

void PopQ(TCoada *c);
void PushQ(TCoada *c, TCmd x);
void DistrQ(TCoada *c);
void AfisareQ(TCoada *c);

//Functii

void Init(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo);

TCmd Read(FILE *input);

void Execute(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo,
             TCmd cmd, FILE *output);

void Run(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo);


