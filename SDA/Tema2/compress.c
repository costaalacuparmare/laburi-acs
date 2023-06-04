/* CONSTANTINESCU Vlad 314CB */
#include "quadtree.h"


/* Compression/ Task2 = writes in a binary output file the size of the image,
 * as well as the types of nodes and the BFS of the tree using an auxiliary
 * queue to arrange the nodes in the BFS order */
void compress(TQuad qtree, FILE *output, unsigned int size)
{
	fwrite(&size, sizeof(unsigned int), 1, output);
	TQueue Q = InitQ();
	PushQ(&Q, qtree);
	while (Q->front != NULL) {
		/* type = 1 => node is leaf, writes the RGB value
		 * type = 0 => node is parent, pushes in the queue
		 * the children of the parent */
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