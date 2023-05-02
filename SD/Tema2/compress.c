#include "quadtree.h"

void addQ(TQueue *Q, TQuad qtree) {
	if (!qtree) return;
	PushQ(Q, qtree);
	addQ(Q, qtree->topL);
	addQ(Q, qtree->topR);
	addQ(Q, qtree->botR);
	addQ(Q, qtree->botL);
}

void compress(TQuad qtree, FILE *output, unsigned int size) {
	fwrite(&size, sizeof(unsigned int), 1, output);
	TQueue Q = InitQ();
	PushQ(&Q, qtree);
	while (Q->front != NULL) {
		if (Q->front->info->type) {
			fwrite(&Q->front->info->type, sizeof(char), 1, output);
			fwrite(&Q->front->info->info.R, sizeof(char), 1, output);
			fwrite(&Q->front->info->info.G, sizeof(char), 1, output);
			fwrite(&Q->front->info->info.B, sizeof(char), 1, output);
		} else {
			fwrite(&Q->front->info->type, sizeof(char), 1, output);
			PushQ(&Q, Q->front->info->topL);
			PushQ(&Q, Q->front->info->topR);
			PushQ(&Q, Q->front->info->botR);
			PushQ(&Q, Q->front->info->botL);
		}
		PopQ(&Q);
	}
	FreeQ(&Q);
}