/* CONSTANTINESCU Vlad 314CB */


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

/* macro-uri pentru codificarea
 * comenziilor */

#define MAX 20
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#define TEN 10
#define ELEVEN 11

/* MOVE_LEFT / 1
 * MOVE_RIGHT / 2
 * MOVE_LEFT_CHAR / 3 + param
 * MOVE_RIGHT_CHAR / 4 + param
 * WRITE / 5 + param
 * INSERT_LEFT / 6 + param
 * INSERT_RIGHT / 7 + param
 * SHOW_CURRENT / 8
 * SHOW / 9
 * UNDO / 10
 * REDO / 11
*/

/* declarearea structuriilor folosite */


/* banda ce contine deget si santinela de
 * tipul lista dubla inlantuita */
typedef struct celulaB {
    char info;
    struct celulaB *pre, *urm;
} TCelulaB, *TListaB;

typedef struct banda {
    TListaB santinela;
    TListaB deget;
} *TBanda;

/*structurile pentru stivele UNDO/ REDO */

typedef struct celulaS {
    TListaB info;
    struct celulaS* urm;
} TCelulaS, *TListaS;

typedef struct stiva {
    TListaS vf;
} *TStiva;

/* structura pentru comenzi */

typedef struct command {
    int cod;
    char param;
} *TCmd;

/*structurile pentru coada de
 * comenzi UPDATE */

typedef struct celulaC {
    TCmd info;
    struct celulaC* urm;
} TCelulaC, *TListaC;

typedef struct coada {
    TListaC inc, sf;
} *TCoada;

/* functiile auxiliare pentru structuri */

/*functii pentru coada */

TCoada InitQ ();

void PopQ(TCoada *c);

void PushQ(TCoada *c, TCmd x);

void FreeQ(TCoada *c);

/* functii pentru stiva */

TStiva InitS();

void PushS(TStiva *S, TListaB x);

void PopS(TStiva *S);

void FreeS(TStiva *S);

/* functii pentru banda */

TListaB PushB(char x);

TBanda InitB();

void FreeB(TBanda *B);

/* functii pentru comenzi */

int Code(char *cmd, char *param);

/* functiile comenzi */

void EXECUTE(TBanda *B, TCoada *Q, TStiva *Undo, FILE *output);

void MOVE_LEFT(TBanda *B, TStiva *Undo);

void MOVE_RIGHT(TBanda *B, TStiva *Undo);

void MOVE_LEFT_CHAR(TBanda *B, char param, FILE *output);

void MOVE_RIGHT_CHAR(TBanda *B, char param);

void WRITE(TBanda *B, char param);

void INSERT_LEFT(TBanda *B, char param, FILE *output);

void INSERT_RIGHT(TBanda *B, char param);

void SHOW_CURRENT(TBanda *B, FILE *output);

void SHOW(TBanda *B, FILE *output);

void UNDO(TBanda *B, TStiva *Undo, TStiva *Redo);

void REDO(TBanda *B, TStiva *Undo, TStiva *Redo);

/* functii de implementare */

void Init(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo);

TCmd Read(FILE *input);

void Execute(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo,
             TCmd cmd, FILE *output);

void Run(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo);

void Free(TBanda *B, TCoada *Q, TStiva *Undo, TStiva *Redo);

