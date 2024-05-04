// SPDX-License-Identifier: BSD-3-Clause

#include <stddef.h>
#include <stdio.h>
#include <pthread.h>

#include "utils/utils.h"

#define NUM_ITER 10000000

/* Add the `__thread` keyword to the declaration below. */
__thread
static int var;


void *increment_var(void *arg)
{
	(void)arg;

	for (size_t i = 0; i < NUM_ITER; i++)
		var++;

	/**
	 * Print the value of `var` after it's incremented. Also print
	 * the ID of the thread. Use `pthread_self()` to get it.
	 */

    printf("var = %d; %p\n", var, &var);

    int id = pthread_self();
    printf("Thread ID: %d\n", id);

    return NULL;
}

void *decrement_var(void *arg)
{
	(void)arg;

	for (size_t i = 0; i < NUM_ITER; i++)
		var--;

	/**
	 *  Print the value of `var` after it's incremented. Also print
	 * the ID of the thread. Use `pthread_self()` to get it.
	 */

    printf("var = %d; %p\n", var, &var);

    int id = pthread_self();
    printf("Thread ID: %d\n", id);

	return NULL;
}

int main(void)
{
	int rc;
	pthread_t tids[2];

	/**
	 * Modify the value of `var` here and see if the threads record
	 * this modification or not.
	 */

    var = 0;

	rc = pthread_create(tids, NULL, increment_var, NULL);
	DIE(rc < 0, "pthread_create");
	rc = pthread_create(tids + 1, NULL, decrement_var, NULL);
	DIE(rc < 0, "pthread_create");

	rc = pthread_join(tids[0], NULL);
	DIE(rc < 0, "pthread_join");
	rc = pthread_join(tids[1], NULL);
	DIE(rc < 0, "pthread_join");

	printf("var = %d; %p\n", var, &var);

	return 0;
}
