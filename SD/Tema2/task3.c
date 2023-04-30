#include "quadtree.h"

TQuad getQT(FILE *input) {
	TQuad qtree = (TQuad) calloc(1, sizeof(TCellQuad));
	if (!qtree) {
		printf ("Error at qtree calloc\n");
		return NULL;
	}
	fread(&qtree->type, sizeof(char), 1, input);
	if (qtree->type) {
		fread(&qtree->info.R, sizeof(char), 1, input);
		fread(&qtree->info.G, sizeof(char), 1, input);
		fread(&qtree->info.B, sizeof(char), 1, input);
	} else {
		qtree->topL = getQT(input);
		qtree->topR = getQT(input);
		qtree->botR = getQT(input);
		qtree->botL = getQT(input);
	}
	return qtree;
}

void writePPM(TQuad qtree, int x, int y, unsigned int size, FILE *output) {
	if(!qtree) return;
	if (qtree->type) {
		for (int i = x; i < x + size; i++) {
			for (int j = y; j < y + size; j++) {
				fwrite(&qtree->info.R, sizeof(char), 1, output);
				fwrite(&qtree->info.G, sizeof(char), 1, output);
				fwrite(&qtree->info.B, sizeof(char), 1, output);
			}
			fseek(output, size, ftell(output));
		}
		return;
	}
	writePPM(qtree->topL, x, y, size / 2, output);
	writePPM(qtree->topR, x, y + size / 2, size / 2, output);
	writePPM(qtree->botR, x + size / 2, y + size / 2, size / 2, output);
	writePPM(qtree->botL, x + size / 2, y, size / 2, output);
}

void task3(TQuad qtree, FILE *output, unsigned int size) {
	fprintf(output, "P6\n");
	fprintf(output, "%d %d\n", size, size);
	fprintf(output, "255\n");
	writePPM(qtree, 0 , 0, size, size, output);
}