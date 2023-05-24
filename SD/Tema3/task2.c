/* CONSTANTINESCU Vlad 314CB */

#include "functions.h"

/* return the codification of the vertex and adds the vertex
 * in the vertices array if it wasn't already added */
int addVerticesDepth(FILE *input, TVertices *vertices_array, int nr_vertices)
{
	char *temp_char = (char *) malloc(CHAR_MAX * sizeof(char));
	if (!temp_char) {
		printf("error at temp_char malloc\n");
		return -1;
	}
	for (int i = 0; i < nr_vertices; i++) {
		fscanf(input, "%s", temp_char);
		int code = getVerticesCode(temp_char, vertices_array, nr_vertices);
		fscanf(input, "%d", &(vertices_array[code]->depth));
	}
	free(temp_char);
	int treasure_weight = 0;
	fscanf(input, "%d", &treasure_weight);
	return treasure_weight;
}

int dijkstra(TGraph graph, int start, int end, int *path, int *distance, TVertices *vertices_array)
{
	int *visited = get_size_array(graph->nr_vertices);
	int *previous = get_size_array(graph->nr_vertices);
	float *score = (float *) get_size_array(graph->nr_vertices);

	for (int i = 0; i < graph->nr_vertices; i++) {
		distance[i] = INT_MAX;
		score[i] = INT_MAX;
		visited[i] = 0;
		previous[i] = -1;
	}

	distance[start] = 0;
	score[start] = 0;
	int max_iter = graph->nr_vertices;
	int iter = 0;
	int next = 0;
	float edge_score = 0;
	float min_score = INT_MAX;

	while (!visited[end] && iter < max_iter) {
		min_score = INT_MAX;
		for (int i = 0; i < graph->nr_vertices; i++) {
			if (!visited[i] && score[i] < min_score) {
				min_score = score[i];
				next = i;
			}
		}
		visited[next] = 1;
		TEdge edge = graph->list_array[next];
		while (edge != NULL) {
			edge_score = (float) edge->cost / vertices_array[edge->dest]->depth;
			if (!visited[edge->dest] && score[next] + edge_score < score[edge->dest]) {
				score[edge->dest] = score[next] + edge_score;
				distance[edge->dest] = distance[next] + edge->cost;
				previous[edge->dest] = next;
			}
			edge = edge->next;
		}
		iter++;
	}
	if (distance[end] == INT_MAX) {
		free(visited);
		free(previous);
		free(score);
		return -1;
	}

	int path_length = 0;
	int current = end;
	while (current != start) {
		path[path_length++] = current;
		current = previous[current];
	}
	path[path_length++] = start;

	free(visited);
	free(previous);
	free(score);

	return path_length;
}

void task2(TGraph *graph, TVertices *vertices_array, int treasure_weight, FILE *output)
{
	int start = 0;
	int end = 0;
	for (int i = 0; i < (*graph)->nr_vertices; i++)
		if (strstr("Corabie\n", vertices_array[i]->name))
			end = vertices_array[i]->code;
	for (int i = 0; i < (*graph)->nr_vertices; i++)
		if (strstr("Insula\n", vertices_array[i]->name))
			start = vertices_array[i]->code;

	int *distance = get_size_array((*graph)->nr_vertices);
	int *path = get_size_array((*graph)->nr_vertices);

	int path_length = dijkstra((*graph), end, start, path, distance, vertices_array);
	if (path_length == -1) {
		fprintf(output, "Echipajul nu poate ajunge la insula\n");
		free(distance);
		free(path);
		return;
	}
	for (int i = 0 ; i < (*graph)->nr_vertices; i++) {
		distance[i] = 0;
		path[i] = 0;
	}
	path_length = dijkstra((*graph), start, end, path, distance, vertices_array);
	if (path_length == -1) {
		fprintf(output, "Echipajul nu poate transporta comoara inapoi la corabie\n");
		free(distance);
		free(path);
		return;
	}

	int minDepth = INT_MAX;
	for (int i = path_length - 1; i >= 0; i--) {
		fprintf(output, "%s ", vertices_array[path[i]]->name);
	}
	for (int i = path_length -2; i > 0; i--)
		if (vertices_array[path[i]]->depth < minDepth)
			minDepth = vertices_array[path[i]]->depth;
	fprintf(output, "\n");
	fprintf(output, "%d\n", distance[end]);
	fprintf(output, "%d\n", minDepth);
	fprintf(output, "%d\n", treasure_weight / minDepth);
	free(distance);
	free(path);
}