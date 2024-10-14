#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct timespec start, finish;
double elapsed;

/*
    schelet pentru exercitiul 5
*/

#define MIN(a,b) (((a)<(b))?(a):(b))

int *arr;
int array_size;
int num_threads;

void *adder(void *arg) {
    clock_gettime(CLOCK_MONOTONIC, &start);
    long id = *(long *) arg;
    int strt = id * (double)array_size / num_threads;
    int end = MIN((id + 1) * (double)array_size / num_threads, array_size);
    for (int i = strt; i < end; i++) {
        arr[i] *= 1000;
    }
    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
    printf("%f\n", elapsed);
    return NULL;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Specificati dimensiunea array-ului si numarul de thread-uri\n");
    exit(-1);
  }

  array_size = atoi(argv[1]);
  num_threads = atoi(argv[2]);

  arr = malloc(array_size * sizeof(int));
  for (int i = 0; i < array_size; i++) {
    arr[i] = i;
  }

  for (int i = 0; i < array_size; i++) {
    printf("%d", arr[i]);
    if (i != array_size - 1) {
      printf(" ");
    } else {
      printf("\n");
    }
  }

  long id;
  long args[num_threads];
  void *status;
  int rc;

  // aceasta operatie va fi paralelizata cu num_threads fire de executie
  pthread_t threads[num_threads];
  for (id = 0; id < num_threads; id++) {
      args[id] = id;
      rc = pthread_create(&threads[id], NULL, adder, &args[id]);
      if (rc) {
          printf("error\n");
          exit(-1);
      }

  }

  for (id = 0; id < num_threads; id++) {
      rc = pthread_join(threads[id], &status);
      if (rc) {
          printf("error\n");
          exit(-1);
      }
  }

  printf("\n");

  for (int i = 0; i < array_size; i++) {
    printf("%d", arr[i]);
    if (i != array_size - 1) {
      printf(" ");
    } else {
      printf("\n");
    }
  }

  return 0;
}
