/* CONSTANTINESCU Vlad - 314CB */

#include "tema1.h"

int main ()
{
    TBanda B;
    TCoada Q;
    TStiva Undo;
    TStiva Redo;
    TCmd *CMD;

    Init(&B,&Q,&Undo,&Redo);
    CMD = CitireFisier(&B,&Q,&Undo,&Redo);
    Execute(&B,&Q,&Undo,&Redo,CMD);
    Free(&B,&Q,&Undo,&Redo,CMD);

    return 0;
}