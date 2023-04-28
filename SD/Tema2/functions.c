#include "tema2.h"

TArg InitArg(char const *argv[]) {
	TArg arg = (TArg) malloc(sizeof(TCellArg));
	if (!arg) {
		printf("Error at argument malloc");
		return NULL;
	}
	arg->option = argv[1];
	if (strstr(arg->option,"-d") == NULL) {
		arg->factor = atoi(argv[2]);
		arg->input = fopen(argv[3], "r");
		arg->output = fopen(argv[4], "w+");
	} else {
		arg->input = fopen(argv[2], "r");
		arg->output = fopen(argv[3], "w+");
	}
}

void FreeArg(TArg *arg) {
	fclose((*arg)->input);
	fclose((*arg)->output);
}

/*TQuad InitTQ(TQuad *QTree) {
	TQuad aux = (TQuad) malloc(sizeof(TCellQuad));
	if (!aux) {
		printf("Error at Quad Tree malloc");
		return NULL;
	}
	aux->botLeft = (TCellQuad) malloc (sizeof(TCellQuad));
	struct quad *topRight;
	struct quad *botLeft;
	struct quad *botRight;


}

TPixel InitGrid() {
	TPixel *grid
}

READ */