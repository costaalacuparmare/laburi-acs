/* CONSTANTINESCU Vlad - 314CB */

#include "tema1.h"

int main ()
{
    TBanda deget, B = NULL;

    deget = (TBanda) malloc(sizeof(TCelulaB));
    if (!deget) return 0;

    B = InitBanda(&deget);
    if (!B) return 0;

    printf("%c\n",  B->info);

    printf("Deget e mouse in pula mea\n");
    return 0;
}