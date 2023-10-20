/* SPDX-License-Identifier: BSD-3-Clause */

#include <stdlib.h>
#include <stdio.h>
int main(void)
{
	void *p;

	/*
	 * TODO: Use malloc() to allocate memory of different sizes.
	 * Store result in p.
	 * Use free() to deallocate memory.
	 * Use ltrace and strace command line tools to monitor library
	 * and system calls.
	 */

    p = malloc(5 * sizeof(int));
    ((int *)p)[1] = 5;
    printf("bla: %d\n", ((int *)p)[1]);
    free(p);
	return 0;
}
