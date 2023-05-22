/* CONSTANTINESCU Vlad - 314CB */

typedef struct cellV {
	char *name;
	int code;
	int depth;
} TCellV, *TVertices;

typedef struct cellE {
	int dest;
	int cost;
	struct cellE *next;
} TCellE, *TEdge;

typedef struct cellPrim {
	TEdge edge;
	struct cellPrim *next;
} TCellPrim, *TListPrim;


typedef struct graph {
	int nr_vertices;
	TEdge *list_array;
} TCellG, *TGraph;

