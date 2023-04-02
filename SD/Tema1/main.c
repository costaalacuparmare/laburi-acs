/* CONSTANTINESCU Vlad - 314CB */

#include "tema1.h"

int main()
{
    TBanda B = NULL;
    TCoada Q  = NULL;
    TStiva Undo  = NULL;
    TStiva Redo  = NULL;

    Init(&B,&Q,&Undo,&Redo);
    Run(&B,&Q,&Undo,&Redo);
    /*Free(&B,&Q,&Undo,&Redo,CMD);*/
    return 0;
}