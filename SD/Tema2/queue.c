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