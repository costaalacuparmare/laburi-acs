/* CONSTANTINESCU Vlad - 314CB */

#include "tema1.h"

int main ()
{
    TBanda deget, B = NULL;

    char X;

    deget = (TBanda) malloc(sizeof(TCelulaB));
    if (!deget) return 0;

    B = InitBanda(&deget);
    if (!B) return 0;
    Citire();
    printf("%c\n", deget->info);
    INSERT_LEFT(&deget,X);
    printf("%c\n",  deget->info);
    printf("Deget e mouse in pula mea\n");
    return 0;
}