/* CONSTANTINESCU Vlad 314CB */
#include "quadtree.h"

int main(int argc, char const *argv[])
{

	/* creates the I/O functions */
	FILE *input = openIn(argv);
	FILE *output = openOut(argv);

	/* initialization of used values */
	unsigned int size = 0;
	TQuad qtree = NULL;

	/* based on the option specified in the arguments
	 * builds the compression tree for the corespondent
	 * case */
	if(!strstr(argv[1], "-d")) {
		/* initialization of the grid/ pixel array */
		TPixel **grid = readPPM(grid, &size, input);

		/* using atoi determines the factor wanted
		 * for the compression */
		int factor = atoi(argv[2]);

		/* builds the quad tree */
		qtree = buildQT(grid, size, 0, 0, factor);

		/* frees the grid/ pixel array because it won't
		 * be used anymore in the main function */
		FreeGrid(grid, size);
	} else {
		/* reads the size of the compressed image */
		fread(&size, sizeof(unsigned int), 1, input);

		/* gets the quad tree from the compressed form */
		qtree = getQT(input);
	}

	/* based on the argument from the command line, runs the requested task */
	getTask(argv, qtree, output, size);

	/* frees the memory allocated for the quad tree and closes the opened files */
	Free(&qtree, input, output);

	return 0;
}