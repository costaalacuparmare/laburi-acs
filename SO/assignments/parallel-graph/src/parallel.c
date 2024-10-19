// SPDX-License-Identifier: BSD-3-Clause

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

#include "os_graph.h"
#include "os_threadpool.h"
#include "log/log.h"
#include "utils.h"

#define NUM_THREADS		4

static int sum;
static os_graph_t *graph;
static os_threadpool_t *tp;
static pthread_mutex_t graph_mutex;
static pthread_mutex_t sum_mutex;

static void process_neighbours(void *arg)
{
	int idx = *(int *) arg;
	os_node_t *node = graph->nodes[idx];

	pthread_mutex_lock(&sum_mutex);
	sum += node->info;
	pthread_mutex_unlock(&sum_mutex);
	graph->visited[idx] = DONE;
	for (unsigned int i = 0; i < node->num_neighbours; i++) {
		pthread_mutex_lock(&graph_mutex);
		if (graph->visited[node->neighbours[i]] == NOT_VISITED) {
			int *node_idx = malloc(sizeof(int));

			*node_idx = node->neighbours[i];
			graph->visited[node->neighbours[i]] = PROCESSING;
			pthread_mutex_unlock(&graph_mutex);
			os_task_t *task = create_task(process_neighbours, (void *) node_idx,
										  free);
			enqueue_task(tp, task);
		}
		pthread_mutex_unlock(&graph_mutex);
	}
}

static void process_node(unsigned int idx)
{
	int *node_idx = malloc(sizeof(int));

	*node_idx = idx;
	graph->visited[idx] = PROCESSING;
	os_task_t *task = create_task(process_neighbours, (void *) node_idx, free);

	enqueue_task(tp, task);
}

int main(int argc, char *argv[])
{
	FILE *input_file;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s input_file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	input_file = fopen(argv[1], "r");
	DIE(input_file == NULL, "fopen");

	graph = create_graph_from_file(input_file);
	pthread_mutex_init(&graph_mutex, NULL);
	pthread_mutex_init(&sum_mutex, NULL);
	tp = create_threadpool(NUM_THREADS);
	process_node(0);
	wait_for_completion(tp);
	destroy_threadpool(tp);
	pthread_mutex_destroy(&graph_mutex);
	pthread_mutex_destroy(&sum_mutex);
	printf("%d", sum);

	return 0;
}
