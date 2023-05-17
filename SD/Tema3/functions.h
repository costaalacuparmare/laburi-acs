/* CONSTANTINESCU Vlad - 314CB */
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>

FILE *openIn();
FILE *openOut();
TGraph InitG(int nr_vertices);
void FreeG(TGraph* graph);
TGraph getGraph(FILE *input);