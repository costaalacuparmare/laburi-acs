/* CONSTANTINESCU Vlad - 314CB */
#include "functions.h"

FILE *openIn()
{
	FILE *input = fopen("tema3.in", "r");
	if (!input) {
		printf("Error at input\n");
		return NULL;
	}
	return input;
}

FILE *openOut()
{
	FILE *output = fopen("tema3.out", "w+");
	if (!output) {
		printf("Error at output\n");
		return NULL;
	}
	return output;
}

int *get_size_array(int nr_elements)
{
	int *array = (int *) calloc(nr_elements, sizeof(int));
	if (!array) {
		printf("Error at array calloc\n");
		return NULL;
	}
	return array;
}