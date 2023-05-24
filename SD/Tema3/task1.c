/* CONSTANTINESCU Vlad - 314CB */

#include "functions.h"

void double_edges(TGraph *graph)
{
	for (int i = 0; i < (*graph)->nr_vertices; i++) {
		TEdge edge_temp1 = (*graph)->list_array[i];
		while (edge_temp1) {
			TEdge edge_temp2 = (*graph)->list_array[edge_temp1->dest];
			while (edge_temp2 && edge_temp2->dest != i)
				edge_temp2 = edge_temp2->next;
			if (!edge_temp2)
				addEdge(i, edge_temp1->cost, edge_temp1->dest, graph);
			edge_temp1 = edge_temp1->next;
		}
	}
}

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

int cmp(const void *a, const void *b)
{
	return (*(int *)a) - (*(int *)b);
}

int *lazy_prim(TGraph graph, int nr_zones, int *zone_vertices, unsigned int *start_zones)
{
	int *visited = get_size_array(graph->nr_vertices);
	int *min_cost = get_size_array(nr_zones);
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
			p = PopFirstEdge(&list_prim);
			if (!p)
				break;
			start = p->dest;
			PopListPrim(&list_prim, start);
			min_cost[zone_vertices[start] - 1] += p->cost;
			if (visited[start] == 1)
				p = NULL;
		} while (list_prim || p);
	}
	free(visited);
	qsort(min_cost, nr_zones, sizeof(int), cmp);
	return min_cost;
}

void task1(TGraph *graph, FILE *output)
{
	double_edges(graph);
	int *zone_vertices = get_size_array((*graph)->nr_vertices);
	int *start_zones = get_size_array((*graph)->nr_vertices);
	int nr_zones = getZones((*graph), zone_vertices, start_zones);
	int *min_cost = lazy_prim((*graph), nr_zones, zone_vertices, start_zones);
	fprintf(output, "%d\n", nr_zones);
	for (int i = 0; i < nr_zones; i++)
		fprintf(output, "%d\n", min_cost[i]);
	free(zone_vertices);
	free(start_zones);
	free(min_cost);
}