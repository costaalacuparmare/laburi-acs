#include "quadtree.h"

TQuad readQT(FILE *input) {
	TQuad qtree = (TQuad) calloc(1, sizeof(TCellQuad));
	if (!qtree) {
		printf("Error at qtree malloc\n");
		return NULL;
	}
	fread(&qtree->type, sizeof(char), 1, input);
	if (qtree->type) {
		fread(&qtree->info.R, sizeof(char), 1, input);
		fread(&qtree->info.G, sizeof(char), 1, input);
		fread(&qtree->info.B, sizeof(char), 1, input);
	}
	return qtree;
}

void getQTfromQ(TQueue *Q, FILE *input) {
	while ((*Q)->front) {
		if (!(*Q)->front->info->type) {
			(*Q)->front->info->topL = readQT(input);
			PushQ(Q, (*Q)->front->info->topL);
			(*Q)->front->info->topR = readQT(input);
			PushQ(Q, (*Q)->front->info->topR);
			(*Q)->front->info->botR = readQT(input);
			PushQ(Q, (*Q)->front->info->botR);
			(*Q)->front->info->botL = readQT(input);
			PushQ(Q, (*Q)->front->info->botL);
		}
		PopQ(Q);
	}
}

TQuad getQT(FILE* input) {
	TQueue Q = InitQ();
	TQuad qtree = readQT(input);
	PushQ(&Q, qtree);
	getQTfromQ(&Q, input);
	FreeQ(&Q);
	return qtree;
}

void getGrid(TPixel **grid, TQuad qtree, int x, int y, unsigned int size) {
	if(!qtree) return;
	if (qtree->type) {
		for (int i = x; i < x + size; i++)
			for (int j = y; j < y + size; j++) {
				grid[i][j].R = qtree->info.R;
				grid[i][j].G = qtree->info.G;
				grid[i][j].B = qtree->info.B;
			}
		return;
	}
	getGrid(grid, qtree->topL, x, y, size / 2);
	getGrid(grid, qtree->topR, x, y + size / 2, size / 2);
	getGrid(grid, qtree->botR, x + size / 2, y + size / 2, size / 2);
	getGrid(grid, qtree->botL, x + size / 2, y, size / 2);
}

void writePPM(TPixel **grid, unsigned int size, FILE *output) {
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++) {
				fwrite(&grid[i][j].R, sizeof(char), 1, output);
				fwrite(&grid[i][j].G, sizeof(char), 1, output);
				fwrite(&grid[i][j].B, sizeof(char), 1, output);
			}
		return;
}

void decompress(TQuad qtree, FILE *output, unsigned int size) {
	fprintf(output, "P6\n");
	fprintf(output, "%d %d\n", size, size);
	fprintf(output, "255\n");
	TPixel **grid = InitGrid(size);
	getGrid(grid, qtree, 0 , 0, size);
	writePPM(grid, size, output);
	FreeGrid(grid, size);
}