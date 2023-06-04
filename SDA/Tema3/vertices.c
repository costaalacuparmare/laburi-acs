/* CONSTANTINESCU Vlad - 314CB */

#include "functions.h"

/* initialises the vertices array */
TVertices *InitV(int nr_vertices)
{
	TVertices *vertices_array = (TVertices *) malloc(nr_vertices * sizeof(TCellV));
	if (!vertices_array) {
		printf("Error at vertices_array malloc\n");
		return NULL;
	}
	for (int i = 0; i < nr_vertices; i++) {
		vertices_array[i] = (TVertices) malloc(sizeof(TCellV));
		if (!vertices_array[i]) {
			printf("Error at vertices_array, element %d\n", i);
			for (int j = 0; j < i; j++)
				free(vertices_array[j]);
			free(vertices_array);
			return NULL;
		}
		/* adding codifications */
		vertices_array[i]->code = i;
		vertices_array[i]->name = (char *) calloc(CHAR_MAX, sizeof(char));
		if (!vertices_array[i]->name) {
			printf("Error at name calloc nr %d\n", i);
			for (int j = 0; j < i; j++) {
				free(vertices_array[j]->name);
				free(vertices_array[j]);
			}
			free(vertices_array);
			return NULL;
		}
	}
	return vertices_array;
}

/* return the codification of the vertex and adds the vertex
 * in the vertices array if it wasn't already added */
int getVerticesCode(char *temp_char, TVertices *vertices_array, int nr_vertices)
{
	for (int i = 0; i < nr_vertices; i++) {
		if (strlen(vertices_array[i]->name) == 0) {
			strcpy(vertices_array[i]->name, temp_char);
			return vertices_array[i]->code;
		} else {
			if (strcmp(vertices_array[i]->name, temp_char) == 0)
				return vertices_array[i]->code;
		}
	}
}

/* frees the heap memory allocated for the vertices array */
void FreeV(TVertices *vertices_array, int nr_vertices)
{
	for (int i = 0; i < nr_vertices; i++) {
		free(vertices_array[i]->name);
		free(vertices_array[i]);
	}
	free(vertices_array);
	vertices_array = NULL;
}