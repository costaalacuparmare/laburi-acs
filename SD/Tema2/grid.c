#include "quadtree.h"

TPixel **InitGrid(unsigned int size) {
	TPixel **grid = (TPixel **) malloc(size * sizeof(TPixel *));
	if (!grid) {
		printf("Error at malloc of grid\n");
		return NULL;
	}
	for (int i = 0; i < size; i++)  {
		grid[i] = (TPixel *) malloc(size * sizeof(TPixel));
		if (!grid[i]) {
			printf("Error at malloc of grid[%d]\n", i);
			return NULL;
		}
	}
	return grid;
}

TPixel **readPPM(TPixel **grid, unsigned int *size, FILE* input) {
	char *dump_char = (char *) malloc(4 * sizeof(char));
	unsigned int dump_int = 0;
	if (!dump_char) {
		printf("Error at malloc of dump\n");
		return NULL;
	}
	fread(dump_char, sizeof(char), 3, input);
	fscanf(input, "%d", size);
	fscanf(input, "%d", size);
	fscanf(input, "%d", &dump_int);
	fread(dump_char, sizeof(char), 1, input);
	free(dump_char);
	grid = InitGrid((*size));
	for (int i = 0; i < (*size); i++)
		for (int j = 0; j < (*size); j++) {
			fread(&grid[i][j].R, sizeof(char), 1, input);
			fread(&grid[i][j].G, sizeof(char), 1, input);
			fread(&grid[i][j].B, sizeof(char), 1, input);
		}
	return grid;
}

void FreeGrid(TPixel **grid, unsigned int size) {
	for (int i = 0; i < size; i++)
		free(grid[i]);
	free(grid);
}