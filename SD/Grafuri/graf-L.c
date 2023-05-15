/*--- graf-L.c --- Graf implementat cu liste --*/
#include "graf-L.h"

TGL* AlocG(int nr) /* aloca spatiu pentru descriptor graf si
	                      vector de (n+1) adrese liste arce */
{
  TGL* g = (TGL*)malloc(sizeof(TGL));    /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (AArc*)calloc((nr+1), sizeof(AArc)); /* spatiu vector adr.liste arce */
  if(!g->x) { free(g); return NULL; }
  g->n = nr;
  return g;
}

void DistrG(TGL** ag)
{ 
  int i;
  AArc p, aux;
  for(i = 1; i <= (*ag)->n; i++){ 
    p = (*ag)->x[i];
    while(p)
    { aux = p; p = p->urm;
      free(aux);
    }
  }
  free((*ag)->x);
  free(*ag);
  *ag = NULL;
}

TGL* CitGraf()
{ 
  FILE * f;
  char numefis[21];
  TGL* g = NULL;
  int s, d;
  int x;
  AArc *p, aux;
  int n;

  printf("Numele fisierului de descriere a grafului = ");
  if (!scanf("%s", numefis)) return NULL;
  f = fopen (numefis, "rt");
  if (!f) return NULL;
  if (!fscanf (f, "%i", &n) || n <= 0) return NULL;
  g = AlocG(n);
  if (!g) return 0;
  while (fscanf(f, "%i%i%i", &s, &d, &x) == 3)
  { if (s < 1 || s > n || d < 1 || d > n){ 
      fclose(f); return NULL;
    }
    p = g->x + s;
    while (*p && (*p)->d < d) p = &(*p)->urm;
    aux = (TCelArc*)calloc(sizeof(TCelArc),1);
    if (!aux) {
      DistrG(&g); return NULL;
    }                     
    aux->urm = *p; *p = aux;
    aux->d = d; aux->c = x;
  }
  fclose(f);
  return g;
}

void AfiGrafL(TGL * g)
{
  AArc l;
  int i;

  for(i = 1; i <= g->n; i++){
    l = g->x[i];
    if(!l)
      printf("%d: - \n", i);
    else
      printf("%d: ", i);
    for(; l != NULL; l = l->urm)
      printf(" %d (%d)", l->d, l->c);
    printf("\n");
  }
}