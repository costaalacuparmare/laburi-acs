/* CONSTANTINESCU Vlad - 314CB */
#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256

FILE *openIn();
FILE *openOut();
TGraph InitG(int nr_vertices);
TVertices *InitV(int nr_vertices);
int getVerticesCode(char *temp_char, TVertices *vertices_array, int nr_vertices);
void FreeV(TVertices *vertices_array, int nr_vertices);
void getEdge(char *temp_char1, char *temp_char2, int temp_cost, TVertices *vertices_array, TGraph *graph);
void FreeG(TGraph* graph);
TGraph getGraph(FILE *input, TVertices **vertices_array);
void addEdge(int temp_dest, int temp_cost, int code, TGraph *graph);