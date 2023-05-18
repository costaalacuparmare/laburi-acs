/* CONSTANTINESCU Vlad - 314CB */

typedef struct cellE {
	char *dest;
	int cost;
	struct cellE *next;
} TCellE, *TEdge;

typedef struct graph {
	int nr_vertices;
	TEdge *list_array;
} *TGraph;

