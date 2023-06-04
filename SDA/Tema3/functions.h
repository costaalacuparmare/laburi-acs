/* CONSTANTINESCU Vlad - 314CB */

#include "structs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/* Auxiliary functions */

/* opens the input file and checks if it was opened correctly */
FILE *openIn();

/* opens the input file and checks if it was opened correctly */
FILE *openOut();

/* allocates memory with calloc using the given dimension and
 * verifies correct allocation */
int *get_size_array(int nr_elements);

/* Vertices functions */

/* initialises the vertices array */
TVertices *InitV(int nr_vertices);

/* return the codification of the vertex and adds the vertex
 * in the vertices array if it wasn't already added */
int getVerticesCode(char *temp_char, TVertices *vertices_array, int nr_vertices);

/* return the codification of the vertex and adds the vertex
 * in the vertices array if it wasn't already added */
int addVerticesDepth(FILE *input, TVertices *vertices_array, int nr_vertices);

/* frees the heap memory allocated for the vertices array */
void FreeV(TVertices *vertices_array, int nr_vertices);

/* Edge functions */

/* adds the edge in the list of the vertex from where it is originated, sorting
 * upwards based on the codification of the vertices */
void addEdge(int temp_dest, int temp_cost, int code, TGraph *graph);

/* uses vertices function to determine the codification of the
 * current vertex and the destination of the edge
 * and then uses the function above to add the edge */
void getEdge(char *temp_char1, char *temp_char2, int temp_cost, TVertices *vertices_array, TGraph *graph);

/* Graph functions */

/* initialises the graph variable and the edge lists */
TGraph InitG(int nr_vertices);

/* uses temporary strings to read the names and fills the graph
 * with the edges and the cost using edge functions */
TGraph getGraph(FILE *input, TVertices **vertices_array);

/* frees the heap memory allocated for the graph */
void FreeG(TGraph* graph);

/* Implementation functions */

/* implements the following steps: doubles the edges, calculates the
 * number of connected zones, the minimal cost for each and prints them
 * in the output file */
void task1(TGraph *graph, FILE *output);

/* uses the dijkstra algorithm to calculate the shortest path from the
 * island to the ship, prints the path, the overall cost of the path, the maximum
 * depth of the ship and the trips needed to carry the whole treasure to the ship
 * as well as determines if the path exists */
void task2(TGraph *graph, TVertices *vertices_array, int treasure_weight, FILE *output);