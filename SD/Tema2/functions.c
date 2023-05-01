#include "quadtree.h"

FILE *openIn(char const *argv[]) {
	FILE *input = NULL;
	if (!strstr(argv[1], "-d")) {
		input = fopen(argv[3], "r");
		if (!input) {
			printf("Error at input open\n");
			return NULL;
		}
	} else {
		input = fopen(argv[2], "r");
		if (!input) {
			printf("Error at input open\n");
			return NULL;
		}
	}
	return input;
}

FILE *openOut(char const *argv[]) {
	FILE *output = NULL;
	if (strstr(argv[1], "-c1")) {
		output = fopen(argv[4], "w+");
		if (!output) {
			printf("Error at output open\n");
			return NULL;
		}
	} else {
		if (strstr(argv[1], "-c2")) {
			output = fopen(argv[4], "wb+");
			if (!output) {
				printf("Error at output open\n");
				return NULL;
			}
		} else {
			output = fopen(argv[3], "wb+");
			if (!output) {
				printf("Error at output open\n");
				return NULL;
			}
		}
	}
	return output;
}

/*FILE *openIn(char const *argv[]) {
	FILE *input = NULL;
	if (!strstr("-d", "-d")) {
		input = fopen("tests/input/test0.ppm", "r");
		if (!input) {
			printf("Error at input open\n");
			return NULL;
		}
	} else {
		input = fopen("tests/input/test0_c2.out", "r");
		if (!input) {
			printf("Error at input open\n");
			return NULL;
		}
	}
	return input;
}

FILE *openOut(char const *argv[]) {
	FILE *output = NULL;
	if (strstr("-d", "-c1")) {
		output = fopen("quadtree.out", "w+");
		if (!output) {
			printf("Error at output open\n");
			return NULL;
		}
	} else {
		if (strstr("-d", "-c2")) {
			output = fopen("quadtree.out", "wb+");
			if (!output) {
				printf("Error at output open\n");
				return NULL;
			}
		} else {
			output = fopen("quadtree.out", "w+");
			if (!output) {
				printf("Error at output open\n");
				return NULL;
			}
		}
	}
	return output;
}*/

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

void FreeGrid(TPixel **grid, unsigned int size) {
	for (int i = 0; i < size; i++)
		free(grid[i]);
	free(grid);
}

TPixel getAverage(TPixel **grid, int x, int y, unsigned int size) {
	TPixel avg;
	long int R = 0;
	long int G = 0;
	long int B = 0;
	for (int i = x; i < x + size; i++)
		for (int j = y; j < y + size; j++) {
			R += grid[i][j].R;
			G += grid[i][j].G;
			B += grid[i][j].B;
		}
	avg.R = R/(size * size);
	avg.G = G/(size * size);
	avg.B = B/(size * size);
	return avg;
}

long int getMean(TPixel **grid, TPixel avg, int x, int y, unsigned int size) {
	unsigned long long mean = 0;
	for (int i = x; i < x + size; i++)
		for ( int j = y; j < y + size; j++) {
			mean += (avg.R - grid[i][j].R) * (avg.R - grid[i][j].R);
			mean += (avg.G - grid[i][j].G) * (avg.G - grid[i][j].G);
			mean += (avg.B - grid[i][j].B) * (avg.B - grid[i][j].B);
		}
	mean /= (3 * size * size);
	return mean;
}

TQuad buildQT (TPixel **grid, unsigned int size, int x, int y, int factor) {
	TQuad qtree = (TQuad) calloc(1, sizeof(TCellQuad));
	if (!qtree) {
		printf ("Error at qtree calloc\n");
		return NULL;
	}
	TPixel avg = getAverage(grid,x,y,size);
	long int mean = getMean(grid,avg,x,y,size);
	if (mean <= factor) {
		qtree->type = 1;
		qtree->info.R = avg.R;
		qtree->info.G = avg.G;
		qtree->info.B = avg.B;
	} else {
	qtree->type = 0;
	qtree->topL = buildQT(grid, size / 2, x, y, factor);
	qtree->topR = buildQT(grid, size / 2, x, y + size / 2, factor);
	qtree->botR = buildQT(grid, size / 2, x + size / 2, y + size / 2, factor);
	qtree->botL = buildQT(grid, size / 2, x + size / 2, y, factor);
	}
	return qtree;
}

void freeQT(TQuad qtree) {
	if (!qtree) return;
	freeQT(qtree->topL);
	freeQT((qtree->topR));
	freeQT((qtree->botL));
	freeQT((qtree->botR));
	free(qtree);
}

void FreeQT(TQuad *qtree) {
	if (!(*qtree)) return;
	freeQT((*qtree));
	(*qtree) = NULL;
}

void Free(TQuad *qtree, FILE *input, FILE *output) {
	FreeQT(qtree);
	fclose(input);
	fclose(output);
}

void getTask(char const *argv[], TQuad qtree, FILE *output, unsigned int size) {
	if (strstr(argv[1], "-c1"))
		task1(qtree, output, size);
	if (strstr(argv[1], "-c2"))
		task2(qtree, output, size);
	if(strstr(argv[1], "-d"))
		task3(qtree, output, size);
}

void Parcurgere (TQuad r, FILE *output) {
	if (!r)
		return;
	if (r->topL == NULL && r->topR == NULL
		&& r->botL == NULL && r->botR == NULL)
		fprintf(output, "[%d %d %d] ", r->info.R, r->info.G, r->info.B);
	Parcurgere(r->topL, output);
	Parcurgere(r->topR, output);
	Parcurgere(r->botL, output);
	Parcurgere(r->botR, output);
}