#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
