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

/* implementation of the dijkstra algorithm using the score given
 * and returns path length */
int dijkstra(TGraph graph, int start, int end, int *path, int *distance, TVertices *vertices_array)
{
	/* used to check the visitation of vertices */
	int *visited = get_size_array(graph->nr_vertices);

	/* memorises the vertex before the current one in order to return to it */
	int *previous = get_size_array(graph->nr_vertices);

	/* contains the added up score until the index vertex */
	float *score = (float *) get_size_array(graph->nr_vertices);

	/* initialization of arrays */
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
		/* verifies the minimal score to update it each iteration */
		min_score = INT_MAX;
		for (int i = 0; i < graph->nr_vertices; i++) {
			if (!visited[i] && score[i] < min_score) {
				min_score = score[i];
				next = i;
			}
		}
		visited[next] = 1;

		/* if the score of the next edge is and the previous scores are below
		 * the added up score in the destination, it replaces it */
		TEdge edge = graph->list_array[next];
		while (edge != NULL) {
		 	/* calculate s edge's score */
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

	/* if for no path was found */
	if (distance[end] == INT_MAX) {
		free(visited);
		free(previous);
		free(score);
		return -1;
	}

	/* calculates the length of the path and returns it */
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

/* uses the dijkstra algorithm to calculate the shortest path from the island to
 * the ship, prints the path, the overall cost of the path, the maximum depth of
 * the ship and the trips needed to carry the whole treasure to the ship
 * as well as determines if the path exists */
void task2(TGraph *graph, TVertices *vertices_array, int treasure_weight, FILE *output)
{
	/* contains the codification of the start vertex */
	int start = 0;
	for (int i = 0; i < (*graph)->nr_vertices; i++)
		if (strstr("Insula\n", vertices_array[i]->name))
			start = vertices_array[i]->code;

	/* contains the codification of the end vertex */
	int end = 0;
	for (int i = 0; i < (*graph)->nr_vertices; i++)
		if (strstr("Corabie\n", vertices_array[i]->name))
			end = vertices_array[i]->code;

	/* contains the added up cost for the path */
	int *distance = get_size_array((*graph)->nr_vertices);

	/* contains the codifications of the vertices that compose the path */
	int *path = get_size_array((*graph)->nr_vertices);

	int path_length = dijkstra((*graph), end, start, path, distance, vertices_array);
	/* verifies that the path from end to start exists */
	if (path_length == -1) {
		fprintf(output, "Echipajul nu poate ajunge la insula\n");
		free(distance);
		free(path);
		return;
	}

	/* resets the arrays */
	for (int i = 0 ; i < (*graph)->nr_vertices; i++) {
		distance[i] = 0;
		path[i] = 0;
	}


	path_length = dijkstra((*graph), start, end, path, distance, vertices_array);
	/* verifies that the path from start to end exists */
	if (path_length == -1) {
		fprintf(output, "Echipajul nu poate transporta comoara inapoi la corabie\n");
		free(distance);
		free(path);
		return;
	}

	/* prints the path in the output file */
	for (int i = path_length - 1; i >= 0; i--) {
		fprintf(output, "%s ", vertices_array[path[i]]->name);
	}

	/* prints the overall costs of the path */
	fprintf(output, "\n");
	fprintf(output, "%d\n", distance[end]);


	/* calculates and prints the max depth of the boat */
	int minDepth = INT_MAX;
	for (int i = path_length -2; i > 0; i--)
		if (vertices_array[path[i]]->depth < minDepth)
			minDepth = vertices_array[path[i]]->depth;
	fprintf(output, "%d\n", minDepth);

	/* prints the number of trips required to get the treasure to the ship */
	fprintf(output, "%d\n", treasure_weight / minDepth);

	/* frees heap allocated memory */
	free(distance);
	free(path);
}