#include "tcoada.h"

int main()
{
  TCoada* c;
  int x;
  c = InitQ();
  if(!c) return 1;

  printf("Introduceti elementele cozii: ");
  while(scanf("%d", &x) == 1)
  {
    if(!IntrQ(c, x))
      break;
  }

  AfisareQ(c);

  DistrQ(&c);
}
