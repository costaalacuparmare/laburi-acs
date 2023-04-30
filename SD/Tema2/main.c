#include "quadtree.h"

int main(int argc, char const *argv[]) {

	FILE *input = openIn(argv);
	FILE *output = openOut(argv);
	unsigned int size = 0;
	TQuad qtree = NULL;

	if(!strstr(argv[1], "-d")) {
		TPixel **grid = readPPM(grid, &size, input);
		int factor = 0;//atoi(argv[2]);
		qtree = buildQT(grid, size, 0, 0, factor);
		FreeGrid(grid, size);
	} else {
		fread(&size, sizeof(unsigned int), 1, input);
		qtree = getQT(input);
	}

	getTask(argv, qtree, output, size);

	Free(&qtree, input, output);

	return 0;
}