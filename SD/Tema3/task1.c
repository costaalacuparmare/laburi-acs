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

int getZones(TGraph graph, int *visited)
{
	int nr_zones = 0;
	for (int i = 0; i < graph->nr_vertices; i++) {
		if (!visited[i]) {
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
	TEdge edge = NULL;
	edge = first_cell->edge;
	(*list_prim) = (*list_prim)->urm;
	free(first_cell);
	return edge;
}

int cmp(const void *a, const void *b)
{
	return (*(int *)a) - (*(int *)b);
}

/*
 * algoritm_prim:
 *         graf      - graful pe care aplicam algoritmul lui prim
 *         nr_conexe - numarul de elemente conexe din graf
 *         masca     - vector ce contine pentru fiecare nod indexul componentei
 *                     conexe din care face parte
 *         componente_conexe - vector ce contine pentru fiecare componenta
 *                             conexa primul nod din aceasta
 * Returneaza:
 *         sume      - vectorul sortat ce contine suma costurilor drumurilor
 *                     pentru fiecare componenta conexa in parte
 *         NULL      - nu s-a reusit alocarea
 * Variabile:
 *         lista     - lista de prioritati pentru muchii
 *         vizitati  - vector ce tine cont de ce noduri au fost vizitate
 *         sume      - vectorul sortat ce contine suma costurilor drumurilor
 *                     pentru fiecare componenta conexa in parte
 *         min       - valoarea cu care se va gasi muchia cu cel mai mic cost
 *         start     - nodul de la care se porneste
 *         i         - iterator clasic
 *         p         - variabila auxiliar cu care se parcurge lista muchiilor
 * 1. start devine nod din fiecare componenta conexa.
 * 2. vizitati[start] devine 1
 * 3. adaugam in lista de muchii toate muchiile ce pornesc de la start si
 *    nu au ca destinatie un nod deja vizitat
 * 4. alegem din lista de muchii cea mai buna muchie
 * 5. start devine nodul catre care se duce aceasta muchie
 * 6. eliminam din lista de muchii toate muchiile ce duc la start
 * 7. adaugam in componenta conexa corespunzatoare acelui nod costul muchiei
 * 8. daca muchia extrasa este catre un nod deja vizitat, implicit am terminat
 *    pentru componenta conexa actuala. daca nu, ne intoarcem la pasul 2.
 */

// visited = masca

int *lazy_prim(TGraph *graph, int nr_zones, int *visited, unsigned int *componente_conexe)
{
	lista_prim lista = NULL;
	int *vizitati = NULL;
	unsigned int *sume = NULL;
	int min = INT_MAX;
	unsigned int start = 0;
	unsigned int i = 0;
	lista_adiacenta p = NULL;
/******************************************************************************
 *                              STOP INITIALIZARI                             *
 * ***************************************************************************/
	vizitati = calloc(graf->nr_noduri, sizeof(int));
	if (!vizitati)
		return NULL;
	sume = calloc(nr_conexe, sizeof(int));
	if (!sume) {
		free(vizitati);
		return NULL;
	}
	for (; i < nr_conexe; i++) {
		start = componente_conexe[i];                           //  1.
		do {                                                    //
			vizitati[start] = 1;                                //  2.
			p = graf->lista_arce[start];                        //  3.
			while (p) {                                         //  3.
				if (vizitati[p->destinatie] == 0)               //  3.
					lista_prim_adauga(&lista, p);               //  3.
				p = p->urm;                                     //  3.
			}                                                   //  3.
			p = lista_extrage_min(&lista);                      //  4.
			if (!p)                                             //
				break;                                          //
			start = p->destinatie;                              //  5.
			lista_purifica(&lista, start);                      //  6.
			sume[masca[start] - 1] += p->cost;                  //  7.
			if (vizitati[start] == 1)                           //  8.
				p = NULL;                                       //  8.
		} while (lista || p);                                   //  8.
	}
	free(vizitati);
	qsort(sume, nr_conexe, sizeof(int), fcomp);
	return sume;
}

void task1(TGraph *graph, FILE *output)
{
	double_edges(graph);
	int *visited = (int *) calloc((*graph)->nr_vertices, sizeof(int));
	if (!visited) {
		printf("Error at visited calloc\n");
		return;
	}
	int nr_zones = getZones((*graph), visited);
	for (int i = 0; i < (*graph)->nr_vertices; i++)
		printf("%d ", visited[i]);
	printf("\n");
	fprintf(output, "%d\n", nr_zones);
	free(visited);
}

void task2()
{
	printf("2\n");
}