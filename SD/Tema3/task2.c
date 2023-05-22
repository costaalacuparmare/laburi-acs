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

void task2(TGraph *graph, TVertices *vertices_array, int treasure_weight, FILE *output)
{
	printf("%d\n", treasure_weight);
}