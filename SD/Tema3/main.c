/* CONSTANTINESCU Vlad - 314CB */
#include "functions.h"

int main(int argc, char const *argv[])
{
	FILE *input = openIn();
	FILE *output = openOut();
	TGraph graph = getGraph(input);
	FreeG(&graph);
	fclose(input);
	fclose(output);
	return 0;
}