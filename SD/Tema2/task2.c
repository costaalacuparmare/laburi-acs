#include "quadtree.h"

/* queue functions */

/* initializes the queue */
TQueue InitQ() {
	TQueue Q = (TQueue) malloc(sizeof(struct queue));
	if (!Q) return NULL;
	Q->front = Q->rear = NULL;
	return Q;
}

/* adds a command to the queue */
void PushQ(TQueue *Q, TQuad x) {
	TListQ aux = (TListQ) malloc(sizeof(TCellQ));
	if (!aux) return;
	aux->info = x;
	aux->next = NULL;
	if ((*Q)->front != NULL)
		(*Q)->rear->next = aux;
	else
		(*Q)->front = aux;
	(*Q)->rear = aux;
}

/* removes a command from the queue */
void PopQ(TQueue *Q) {
	TListQ aux = NULL;
	if ((*Q)->front == NULL)
		return;
	aux = (*Q)->front;
	(*Q)->front = (*Q)->front->next;
	free(aux);
}

/* frees the heap memory space used for the queue */
void FreeQ(TQueue *Q) {
	TListQ p = NULL;
	TListQ aux = NULL;
	p = (*Q)->front;
	while (p) {
		aux = p;
		p = p->next;
		free(aux);
	}
	free(*Q);
	*Q = NULL;
}

void addQ(TQueue *Q, TQuad qtree) {
	if (!qtree) return;
	PushQ(Q, qtree);
	addQ(Q, qtree->topL);
	addQ(Q, qtree->topR);
	addQ(Q, qtree->botR);
	addQ(Q, qtree->botL);
}

void task2(TQuad qtree, FILE *output, unsigned int size) {
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