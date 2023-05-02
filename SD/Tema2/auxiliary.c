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
		stats(qtree, output, size);
	if (strstr(argv[1], "-c2"))
		compress(qtree, output, size);
	if(strstr(argv[1], "-d"))
		decompress(qtree, output, size);
}