/*--- graf-L.h --- Graf reprezentat cu liste --*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef _GRAF_L_
#define _GRAF_L_

typedef struct celarc 
{ int d;           /* destinatie arc */
  int c;            /* cost arc */
  struct celarc *urm; /* adresa urmatorul adiacent */
} TCelArc, *AArc;

typedef struct 
{ int n;     /* numar noduri */
  AArc* x;    /* vector adrese liste arce */
} TGL;

TGL* CitGraf();  /* citeste descriere graf */
void AfiGrafL(TGL *); /* afisare liste de adiacente */
void DistrG(TGL** ag);
#endif
