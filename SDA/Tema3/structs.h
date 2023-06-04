/* CONSTANTINESCU Vlad - 314CB */

/* structure for vertices array */
typedef struct cellV {
	char *name;
	int code;
	int depth;
} TCellV, *TVertices;

/* structure for an edge of the graph */
typedef struct cellE {
	int dest;
	int cost;
	struct cellE *next;
} TCellE, *TEdge;

/* structure for simple chained list used
 * for the lazy prim algorithm, equivalent to
 * a priority queue, used for algorithm */
typedef struct cellPrim {
	TEdge edge;
	struct cellPrim *next;
} TCellPrim, *TListPrim;

/* structure for graph */
typedef struct graph {
	int nr_vertices;
	TEdge *list_array;
} TCellG, *TGraph;

