/* CONSTANTINESCU Vlad 314CB */
#include "functions.h"

int getVerticesDepth(FILE *input, TVertices *vertices_array, int nr_vertices)
{
	char *temp_char = (char *) malloc(CHAR_MAX * sizeof(char));
	if (!temp_char) {
		printf("error at temp_char malloc\n");
		return -1;
	}
	for (int i = 0; i < nr_vertices; i++) {
		fscanf(input, "%s", temp_char);
		int code = getVerticesCode(temp_char, vertices_array, nr_vertices);
		fscanf(input, "%d", &(vertices_array[code]->depth));
	}
	free(temp_char);
	int treasure_weight = 0;
	fscanf(input, "%d", &treasure_weight);
	return treasure_weight;
}

#define INFINITE 9999
#define MAX_VERTICES 100

void Dijkstra(TGraph G, int startVertex, int endVertex, TVertices *vertices_array, FILE *output) {
	int distance[MAX_VERTICES];
	int visited[MAX_VERTICES];
	int previous[MAX_VERTICES];
	int path[MAX_VERTICES];
	int pathLength = 0;
	int i, minDist, nextVertex;

	for (i = 0; i < G->nr_vertices; i++) {
		distance[i] = INFINITE;
		visited[i] = 0;
		previous[i] = -1;
	}

	distance[startVertex] = 0;

	while (!visited[endVertex]) {
		minDist = INFINITE;

		for (i = 0; i < G->nr_vertices; i++) {
			if (!visited[i] && distance[i] < minDist) {
				minDist = distance[i];
				nextVertex = i;
			}
		}

		visited[nextVertex] = 1;

		TEdge edge = G->list_array[nextVertex];
		while (edge != NULL) {
			int neighbor = edge->dest;
			int cost = edge->cost;

			if (!visited[neighbor] && distance[nextVertex] + cost < distance[neighbor]) {
				distance[neighbor] = distance[nextVertex] + cost;
				previous[neighbor] = nextVertex;
			}

			edge = edge->next;
		}
	}

	int currentVertex = endVertex;
	while (currentVertex != startVertex) {
		path[pathLength] = currentVertex;
		pathLength++;
		currentVertex = previous[currentVertex];
	}
	path[pathLength] = startVertex;
	pathLength++;

	for (i = pathLength - 1; i >= 0; i--) {
		fprintf(output, "%s ", vertices_array[path[i]]->name);
	}
	fprintf(output, "\n");
	fprintf(output, "%d\n", distance[endVertex]);
}


void task2(TGraph *graph, TVertices *vertices_array, int treasure_weight, FILE *output)
{
	printf("%d\n", treasure_weight);
	int startVertex = 0;
	int endVertex = 0;
	for (int i = 0; i < (*graph)->nr_vertices; i++)
		if (strstr("Corabie\n", vertices_array[i]->name))
			endVertex = vertices_array[i]->code;

	Dijkstra((*graph), startVertex, endVertex, vertices_array, output);
}