#include "quadtree.h"

int main(int argc, char const *argv[]) {

	FILE *input = openIn(argv);
	FILE *output = openOut(argv);

	unsigned int size = 0;
	TPixel **grid = readPPM(grid, &size, input);
	if (!grid) {
		printf("Error at reading .ppm\n");
		return 0;
	}

	TQuad QTree = InitQT();
		//	Init(&QTree);
//	Run(&QTree);
//	Free(&QTree);
	fclose(input);
	fclose(output);
	return 0;
}