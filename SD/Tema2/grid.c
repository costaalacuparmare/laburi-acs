/* CONSTANTINESCU Vlad 314CB */
#include "quadtree.h"

/* initializes the grid / pixel array to size * size */
TPixel **InitGrid(unsigned int size)
{
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

/* reads the size and grid from the ppm input file */
TPixel **readPPM(TPixel **grid, unsigned int *size, FILE* input)
{
	/* uses dump_char to read the characters
	 * between the values from the header */
	char *dump_char = (char *) malloc(4 * sizeof(char));
	unsigned int max_pixel_value = 0;
	if (!dump_char) {
		printf("Error at malloc of dump\n");
		return NULL;
	}
	fread(dump_char, sizeof(char), 3, input);
	fscanf(input, "%d", size);
	fscanf(input, "%d", size);
	fscanf(input, "%d", &max_pixel_value);
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

/* frees the memory allocated for the grid/ pixel array */
void FreeGrid(TPixel **grid, unsigned int size)
{
	for (int i = 0; i < size; i++)
		free(grid[i]);
	free(grid);
}