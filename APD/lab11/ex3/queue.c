#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

typedef struct {
    int size;
    int arr[1000];
} queue;

int main (int argc, char *argv[]) {
    int numtasks, rank;

    queue q;
    // TODO: declare the types and arrays for offsets and block counts
    MPI_Datatype queue_type, types[2] = {MPI_INT, MPI_INT};
    int blockcounts[2] = {1, 1000};
    MPI_Aint offsets[2];
    offsets[0] = offsetof(queue, size);
    offsets[1] = offsetof(queue, arr);
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // TODO: create the MPI data type, using offsets and block counts, and commit the data type
    MPI_Type_create_struct(2, blockcounts, offsets, types, &queue_type);
    MPI_Type_commit(&queue_type);

 
    // First process starts the circle.
    if (rank == 0) {
        // First process starts the circle.
        // Generate a random number and add it in queue.
        // Sends the queue to the next process.
        q.size = 1;
        q.arr[0] = rank;
        MPI_Send(&q, 1, queue_type, 1, 0, MPI_COMM_WORLD);
    } else if (rank == numtasks - 1) {
        // Last process close the circle.
        // Receives the queue from the previous process.
        // Generate a random number and add it in queue.
        // Sends the queue to the first process.
        MPI_Recv(&q, 1, queue_type, rank - 1, 0, MPI_COMM_WORLD, &status);
        q.arr[q.size++] = rank;
        MPI_Send(&q, 1, queue_type, 0, 0, MPI_COMM_WORLD);
    } else {
        // Middle process.
        // Receives the queue from the previous process.
        // Generate a random number and add it in queue.
        // Sends the queue to the next process.
        MPI_Recv(&q, 1, queue_type, rank - 1, 0, MPI_COMM_WORLD, &status);
        q.arr[q.size++] = rank;
        MPI_Send(&q, 1, queue_type, rank + 1, 0, MPI_COMM_WORLD);
    }

    // TODO: Process 0 prints the elements from queue
    if (rank == 0) {
        MPI_Recv(&q, 1, queue_type, numtasks - 1, 0, MPI_COMM_WORLD, &status);
        for (int i = 0; i < q.size; i++) {
            printf("%d ", q.arr[i]);
        }
        printf("\n");
    }

    // TODO: free the newly created MPI data type
    MPI_Type_free(&queue_type);
    MPI_Finalize();
}