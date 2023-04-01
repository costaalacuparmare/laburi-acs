/* CONSTANTINESCU Vlad - 314CB */

#include "tema1.h"

int main()
{
    TBanda B;
    TCoada Q;
    TStiva Undo;
    TStiva Redo;
    TCmd CMD = (TCmd) malloc(sizeof(TCmd));
    /*Init(&B,&Q,&Undo,&Redo);
    CMD = CitireFisier(&B,&Q,&Undo,&Redo);
    Execute(&B,&Q,&Undo,&Redo,CMD);
    Free(&B,&Q,&Undo,&Redo,CMD);*/
    char *s = "WRITE X";
    printf("cod: %d, param: %s, cmd: %s\n",CMD->cod,CMD->param,s);
    CMD->cod = Codificare(s,&CMD->param);
    printf("cod: %d, param: %s, cmd: %s\n",CMD->cod,CMD->param,s);

    return 0;
}