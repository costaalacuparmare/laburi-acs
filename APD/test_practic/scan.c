#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_N 100
int N, P;
pthread_barrier_t barrier;
pthread_mutex_t mutex;

typedef struct {
    int id;
    int partial_sums[MAX_N];
    int *v;
} scan_args;

void *scan(void *args) {
    scan_args *info = (scan_args *) args;

    int start = info->id * N / P;
    int end = (info->id + 1) * N / P;
    if (info->id == P - 1) {
        end = N;
    }

    printf("Thread %d: start %d, end %d\n", info->id, start, end);

    int first = 0;
    int local_sums[MAX_N];

    if (start == 0) {
        info->partial_sums[start] = info->v[start];
    }

    pthread_barrier_wait(&barrier);

    for (int i = start; i < end; i++) {
        if (first == 1) {
            first = 0;
            continue;
        }
        local_sums[i] = local_sums[i - 1] + info->v[i];
    }

    pthread_mutex_lock(&mutex);
    for (int i = start; i < end; i++) {
        info->partial_sums[i] = local_sums[i];
    }
    pthread_mutex_unlock(&mutex);

    pthread_barrier_wait(&barrier);

    if (info->id == P - 1) {
        printf("Partial sums: ");
        for (int i = 0; i < N; i++) {
            printf("%d ", info->partial_sums[i]);
        }
        printf("\n");
    }

    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Usage: %s <N> <P> <values...>\n", argv[0]);
        return -1;
    }

    N = atoi(argv[1]);
    P = atoi(argv[2]);
    if (N > MAX_N) {
        printf("N should be less than or equal to %d\n", MAX_N);
        return -1;
    }

    int v[N];
    for (int i = 0; i < N; i++) {
        v[i] = atoi(argv[i + 3]);
    }

    scan_args args[P];
    pthread_mutex_init(&mutex, NULL);
    pthread_barrier_init(&barrier, NULL, P);
    pthread_t threads[P];

    for (int i = 0; i < P; i++) {
        args[i].id = i;
        args[i].v = v;
        for (int j = 0; j < MAX_N; j++) {
            args[i].partial_sums[j] = -1;
        }
        int r = pthread_create(&threads[i], NULL, scan, &args[i]);
        if (r) {
            printf("Error creating thread %d\n", i);
            return -1;
        }
    }

    for (int i = 0; i < P; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);
    return 0;
}