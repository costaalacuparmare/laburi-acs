#include "quadtree.h"

int main(int argc, char const *argv[]) {

	FILE *input = openIn(argv);
	FILE *output = openOut(argv);

	unsigned int size = 0;
	TPixel **grid = readPPM(grid, &size, input);

	int factor = atoi(argv[2]);
	TQuad qtree = buildQT(grid, size, 0, 0, factor);
	task1(qtree, output, size);
	FreeGrid(grid,size);
	FreeQT(&qtree);
	fclose(input);
	fclose(output);

	return 0;
}