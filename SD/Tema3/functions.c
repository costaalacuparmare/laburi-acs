/* CONSTANTINESCU Vlad - 314CB */
#include "functions.h"

FILE *openIn()
{
	FILE *input = fopen("tema3.in", "r");
	if (!input) {
		printf("Error at input\n");
		return NULL;
	}
	return input;
}

FILE *openOut()
{
	FILE *output = fopen("tema3.out", "w+");
	if (!output) {
		printf("Error at output\n");
		return NULL;
	}
	return output;
}

TGraph InitG(int nr_vertices)
{
	TGraph graph = (TGraph) malloc(sizeof(struct graph));
	if (!graph) {
		printf("Error at graph malloc\n");
		return NULL;
	}
	graph->list_array = (TEdge *) calloc((nr_vertices + 1), sizeof(struct cellE));
	if(!graph->list_array){
		printf("Error at list_array calloc\n");
		free(graph);
		return NULL;
	}
	graph->nr_vertices = nr_vertices;
	return graph;
}

void FreeG(TGraph* graph)
{
	int i;
	TEdge p, aux;
	for(i = 1; i <= (*graph)->nr_vertices; i++){
		p = (*graph)->list_array[i];
		while(p)
		{ aux = p; p = p->next;
			free(aux);
		}
	}
	free((*graph)->list_array);
	free(*graph);
	*graph = NULL;
}

TGraph getGraph(FILE *input)
{
	int nr_vertices = 0;
	fscanf(input, "%d", &nr_vertices);
	TGraph graph = InitG(nr_vertices);
	return graph;
}