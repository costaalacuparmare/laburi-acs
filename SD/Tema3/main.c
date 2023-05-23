/* CONSTANTINESCU Vlad - 314CB */
#include "functions.h"

int main(int argc, char const *argv[])
{
	FILE *input = openIn();
	FILE *output = openOut();
	TVertices *vertices_array = NULL;
	TGraph graph = getGraph(input, &vertices_array);
	int task = atoi(argv[1]);
	switch (task) {
		case 1: {
			task1(&graph, output);
			break;
		}
		case 2: {
			int treasure_weight = getVerticesDepth(input, vertices_array, graph->nr_vertices);
			task2(&graph, vertices_array, treasure_weight, output);
			break;
		}
	}

	FreeV(vertices_array, graph->nr_vertices);
	FreeG(&graph);
	fclose(input);
	fclose(output);
	return 0;
}