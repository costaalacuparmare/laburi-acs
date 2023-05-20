/* CONSTANTINESCU Vlad - 314CB */

typedef struct cellV {
	char *vertices_char;
	int vertices_code;
} TCellV, *TVertices;

typedef struct cellE {
	int dest;
	int cost;
	struct cellE *next;
} TCellE, *TEdge;

typedef struct graph {
	int nr_vertices;
	TEdge *list_array;
} TCellG, *TGraph;

