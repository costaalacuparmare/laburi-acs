#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX(a,b) ((a > b) ? a : b)

typedef struct pixel {
	unsigned char R;
	unsigned char G;
	unsigned char B;
} TPixel;

typedef struct quad {
	unsigned int type;
	TPixel info;
	struct quad *topL;
	struct quad *topR;
	struct quad *botL;
	struct quad *botR;
} TCellQuad, *TQuad;

FILE *openIn(char const *argv[]);
FILE *openOut(char const *argv[]);
TPixel **readPPM(TPixel **grid, unsigned int *size, FILE* input);
TPixel **InitGrid(unsigned int *size);
void FreeGrid(TPixel **grid, unsigned int size);
TQuad buildQT (TPixel **grid, unsigned int size, int x, int y, int factor);
TPixel getAverage(TPixel **grid, int x, int y, unsigned int size);
long int getMean(TPixel **grid, TPixel avg, int x, int y, unsigned int size);
void FreeQT(TQuad *qtree);
void freeQT(TQuad qtree);
void Parcurgere (TQuad r, FILE *output);

void task1(TQuad qtree, FILE *output, unsigned int size);