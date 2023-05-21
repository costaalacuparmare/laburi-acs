/* CONSTANTINESCU Vlad - 314CB */
#include "functions.h"

int main(int argc, char const *argv[])
{
	FILE *input = openIn();
	FILE *output = openOut();
	TVertices *vertices_array = NULL;
	TGraph graph = getGraph(input, &vertices_array);
	//int task = atoi(argv[1]);
	switch (1) {
		case 1: {
			task1(&graph, output);
			break;
		}
		case 2: {
			task2();
			break;
		}
	}
	/*int k = 0;
	for (int i = 0 ; i < graph->nr_vertices; i++) {
		TEdge temp = graph->list_array[i];
		while (temp) {
			printf("%d %d %d\n", i, temp->dest, temp->cost);
			k++;
			temp = temp->next;
		}
	}
	printf("%d\n", k);*/
	FreeV(vertices_array, graph->nr_vertices);
	FreeG(&graph);
	fclose(input);
	fclose(output);
	return 0;
}