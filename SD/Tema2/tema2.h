#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct argument {
	char const *option;
	unsigned int factor;
	FILE *input;
	FILE *output;
} TCellArg, *TArg;

typedef struct pixel {
	unsigned int R;
	unsigned int G;
	unsigned int B;
} TPixel;

typedef struct quad {
	TPixel info;
	struct quad *topLeft;
	struct quad *topRight;
	struct quad *botLeft;
	struct quad *botRight;
} TCellQuad, *TQuad;

void Init();
void Run();
void Free();

TArg InitArg(char const *argv[]);
void FreeArg(TArg *arg);
