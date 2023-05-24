/* CONSTANTINESCU Vlad - 314CB */

#include "functions.h"

/* doubles the number of edges for the undirected graph */
void double_edges(TGraph *graph)
{
	for (int i = 0; i < (*graph)->nr_vertices; i++) {
		TEdge edge_temp1 = (*graph)->list_array[i];
		while (edge_temp1) {
			TEdge edge_temp2 = (*graph)->list_array[edge_temp1->dest];
			while (edge_temp2 && edge_temp2->dest != i)
				edge_temp2 = edge_temp2->next;
			/* if the edge already exists, it skips it */
			if (!edge_temp2)
				addEdge(i, edge_temp1->cost, edge_temp1->dest, graph);
			edge_temp1 = edge_temp1->next;
		}
	}
}

/* DFS algorithm used to determine the number of connected components
 * and the beginning of each connected zone */
void DFS(TGraph graph, int code, int *visited, int zone)
{
	visited[code] = zone;
	TEdge edge = graph->list_array[code];
	while (edge) {
		if (!visited[edge->dest])
			DFS(graph, edge->dest, visited, zone);
		edge = edge->next;
	}
}

/* determines the number of connected zones using DFS and
 * gets the first vertex of each zone */
int getZones(TGraph graph, int *visited, int *start_zones)
{
	int nr_zones = 0;
	for (int i = 0; i < graph->nr_vertices; i++) {
		if (!visited[i]) {
			start_zones[nr_zones] = i;
			nr_zones++;
			DFS(graph, i, visited, nr_zones);
		}
	}
	return nr_zones;
}

/* adds an edge to the priority queue, sorting the elements
 * by the cost */
void PushListPrim(TListPrim *list_prim, TEdge edge)
{
	TListPrim aux = calloc(1, sizeof(TCellPrim));
	if (!aux) {
		printf("Error at aux calloc\n");
		return;
	}
	TListPrim p = NULL, prev = NULL;
	aux->edge = edge;
	if ((!(*list_prim)) || edge->cost < (*list_prim)->edge->cost) {
		aux->next = (*list_prim);
		(*list_prim) = aux;
		return;
	}
	p = (*list_prim)->next;
	prev = (*list_prim);
	while (p) {
		if (edge->cost < p->edge->cost)
			break;
		prev = p;
		p = p->next;
	}
	prev->next = aux;
	aux->next = p;
	aux->edge = edge;
	return;
}

/* removes from the priority queue all the edges that point
 * to a given destination */
void PopListPrim(TListPrim *list_prim, int dest)
{
	TListPrim p = NULL, prev = NULL, aux = NULL;
	while ((*list_prim) && (*list_prim)->edge->dest == dest) {
		prev = (*list_prim);
		(*list_prim) = (*list_prim)->next;
		free(prev);
	}
	if (!(*list_prim))
		return;
	prev = (*list_prim);
	p = (*list_prim)->next;
	while (p) {
		if (p->edge->dest == dest) {
			prev->next = p->next;
			free(p);
			p = prev;
		}
		prev = p;
		p = p->next;
	}
}

/* extracts the edge with the highest priority. Because the list is sorted,
 * the edge will always be the first one */
TEdge PopFirstEdge(TListPrim *list_prim)
{
	TListPrim first_cell = (*list_prim);
	if (!first_cell)
		return NULL;
	TEdge edge = first_cell->edge;
	(*list_prim) = (*list_prim)->next;
	free(first_cell);
	return edge;
}

/* comparison function used for qsort */
int cmp(const void *a, const void *b)
{
	return (*(int *)a) - (*(int *)b);
}

/* implementation of lazy prim algorithm */
int *lazy_prim(TGraph graph, int nr_zones, int *zone_vertices, unsigned int *start_zones)
{
	/* used to memorise the visited vertices */
	int *visited = get_size_array(graph->nr_vertices);

	/* array of minimal cost for each connected zone */
	int *min_cost = get_size_array(nr_zones);

	/* start marks the beginning of each connected zone */
	int start = 0;

	TEdge p = NULL;
	TListPrim list_prim = NULL;
	for (int i = 0; i < nr_zones; i++) {
		start = start_zones[i];
		do {
			p = graph->list_array[start];
			visited[start] = 1;

			while (p) {
				if (visited[p->dest] == 0)
					PushListPrim(&list_prim, p);
				p = p->next;
			}

			/* chooses the highest priority edge */
			p = PopFirstEdge(&list_prim);
			if (!p)
				break;

			/* start becomes p's destination */
			start = p->dest;

			/* removes from priority queue all the edges which have
			 * as destination start */
			PopListPrim(&list_prim, start);

			/* adds the edge's cost */
			min_cost[zone_vertices[start] - 1] += p->cost;
			if (visited[start] == 1)
				p = NULL;
			/* if the edge points to an already visited vertex it returns
			 * the array of costs otherwise it repeats the algorithm */
		} while (list_prim || p);
	}

	free(visited);

	/* sort the minimal costs for each zone */
	qsort(min_cost, nr_zones, sizeof(int), cmp);

	return min_cost;
}

/* implements the following steps: doubles the edges, calculates the number of
 * connected zones, the minimal cost for each and prints them in the output
 * file */
void task1(TGraph *graph, FILE *output)
{
	/* double the edges for the undirected graph */
	double_edges(graph);

	int *zone_vertices = get_size_array((*graph)->nr_vertices);
	int *start_zones = get_size_array((*graph)->nr_vertices);

	/* calculates the number of connected zones */
	int nr_zones = getZones((*graph), zone_vertices, start_zones);

	/* determines the minimal cost of each connected zone */
	int *min_cost = lazy_prim((*graph), nr_zones, zone_vertices, start_zones);

	/* prints in the output file */
	fprintf(output, "%d\n", nr_zones);
	for (int i = 0; i < nr_zones; i++)
		fprintf(output, "%d\n", min_cost[i]);

	/* frees memory */
	free(zone_vertices);
	free(start_zones);
	free(min_cost);
}