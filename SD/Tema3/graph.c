/* CONSTANTINESCU Vlad - 314CB */

#include "functions.h"

void addEdge(int temp_dest, int temp_cost, int code, TGraph *graph)
{
	TEdge *edge_temp = (*graph)->list_array + code;
	while ((*edge_temp) && (*edge_temp)->dest < temp_dest)
		edge_temp = &((*edge_temp)->next);
	TEdge aux = NULL;
	aux = (TEdge) calloc(1, sizeof(TCellE));
	if (!aux) {
		printf("Error at aux calloc\n");
		return;
	}
	aux->next = (*edge_temp);
	(*edge_temp) = aux;
	aux->dest = temp_dest;
	aux->cost = temp_cost;
}

void getEdge(char *temp_char1, char *temp_char2, int temp_cost, TVertices *vertices_array, TGraph *graph)
{
	int code = getVerticesCode(temp_char1, vertices_array, (*graph)->nr_vertices);
	int temp_dest = getVerticesCode(temp_char2, vertices_array, (*graph)->nr_vertices);
	addEdge(temp_dest, temp_cost, code, graph);
}

TGraph InitG(int nr_vertices)
{
	TGraph graph = (TGraph) malloc(sizeof(TCellG));
	if (!graph) {
		printf("Error at graph malloc\n");
		return NULL;
	}
	graph->list_array = (TEdge *) calloc(nr_vertices, sizeof(TCellE));
	if(!graph->list_array){
		printf("Error at list_array calloc\n");
		free(graph);
		return NULL;
	}
	graph->nr_vertices = nr_vertices;
	return graph;
}

TGraph getGraph(FILE *input, TVertices **vertices_array)
{
	int nr_vertices = 0;
	fscanf(input, "%d", &nr_vertices);
	int nr_edges_given = 0;
	fscanf(input, "%d", &nr_edges_given);
	TGraph graph = InitG(nr_vertices);
	(*vertices_array) = InitV(nr_vertices);
	char *temp_char1 = (char *) malloc(CHAR_MAX * sizeof(char));
	if (!temp_char1) {
		printf("error at temp_char1 malloc\n");
		return NULL;
	}
	char *temp_char2 = (char *) malloc(CHAR_MAX * sizeof(char));
	if (!temp_char2) {
		printf("error at temp_char2 malloc\n");
		return NULL;
	}
	int temp_cost = 0;
	for (int i = 0; i < nr_edges_given; i++) {
		fscanf(input, "%s %s %d", temp_char1, temp_char2, &temp_cost);
		int code = getVerticesCode(temp_char1, (*vertices_array), nr_vertices);
		getEdge(temp_char1, temp_char2, temp_cost, (*vertices_array), &graph);
	}
	free(temp_char1);
	free(temp_char2);
	return graph;
}

void FreeG(TGraph* graph)
{
	TEdge p, aux;
	for (int i = 0; i < (*graph)->nr_vertices; i++) {
		p = (*graph)->list_array[i];
		while (p) {
			aux = p;
			p = p->next;
			free(aux);
		}
	}
	free((*graph)->list_array);
	free(*graph);
	(*graph) = NULL;
}