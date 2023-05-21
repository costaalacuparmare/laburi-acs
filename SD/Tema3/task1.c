/* CONSTANTINESCU Vlad - 314CB */
#include "functions.h"

void double_edges(TGraph *graph)
{
	for (int i = 0; i < (*graph)->nr_vertices; i++) {
		TEdge edge_temp1 = (*graph)->list_array[i];
		while (edge_temp1) {
			TEdge edge_temp2 = (*graph)->list_array[edge_temp1->dest];
			while (edge_temp2 && edge_temp2->dest != i)
				edge_temp2 = edge_temp2->next;
			if (!edge_temp2)
				addEdge(i, edge_temp1->cost, edge_temp1->dest, graph);
			edge_temp1 = edge_temp1->next;
		}
	}
}

void DFS(TGraph graph, int code, int *visited, int zone)
{
	visited[code] = zone;
	TEdge edge = graph->list_array[code];
	while (edge) {
		if (!visited[edge->dest])
			DFS(graph, edge->dest, visited, zone);
		edge = edge->next;
	}
}

int getZones(TGraph graph, int *visited)
{
	int nr_zones = 0;
	for (int i = 0; i < graph->nr_vertices; i++) {
		if (!visited[i]) {
			nr_zones++;
			DFS(graph, i, visited, nr_zones);
		}
	}
	return nr_zones;
}

void task1(TGraph *graph, FILE *output)
{
	double_edges(graph);
	int *visited = (int *) calloc((*graph)->nr_vertices, sizeof(int));
	if (!visited) {
		printf("Error at visited calloc\n");
		return;
	}
	int nr_zones = getZones((*graph), visited);
	for (int i = 0; i < (*graph)->nr_vertices; i++)
		printf("%d ", visited[i]);
	printf("\n");
	fprintf(output, "%d\n", nr_zones);
	free(visited);
}

void task2()
{
	printf("2\n");
}