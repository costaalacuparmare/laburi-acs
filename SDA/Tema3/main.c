/* CONSTANTINESCU Vlad - 314CB */

#include "functions.h"

int main(int argc, char const *argv[])
{
	/* opens the I/O files */
	FILE *input = openIn();
	FILE *output = openOut();

	/* reads the graph from the input file and uses and vertices array
	 * to associate the names of the vertices with the codification */
	TVertices *vertices_array = NULL;
	TGraph graph = getGraph(input, &vertices_array);

	/* solves the task given as argument in the command line */
	int task = atoi(argv[1]);
	switch (task) {
		case 1: {
			task1(&graph, output);
			break;
		}
		case 2: {
			/* the function return the weight of the treasure and
			 * fills the vertices array with depth values for each vertex */
			int treasure_weight = addVerticesDepth(input, vertices_array, graph->nr_vertices);

			 task2(&graph, vertices_array, treasure_weight, output);
			break;
		}
	}

	/* Frees memory and closes files */
	FreeV(vertices_array, graph->nr_vertices);
	FreeG(&graph);
	fclose(input);
	fclose(output);

	return 0;
}