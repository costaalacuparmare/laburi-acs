#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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