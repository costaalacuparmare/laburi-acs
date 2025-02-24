#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int numtasks, rank;

    int flag;

    MPI_Status status;
    MPI_Request request;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int recv_num;

    // First process starts the circle.
    if (rank == 0) {
        // First process starts the circle.
        // Generate a random number.
        // Send the number to the next process.
        srand(42);
        int num = rand();

        MPI_Isend(&num, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &request);

        MPI_Irecv(&recv_num, 1, MPI_INT, numtasks - 1, 0, MPI_COMM_WORLD, &request);
        MPI_Test(&request, &flag, &status);

        if (flag) {
            printf("Process with rank [%d], received %d with tag %d.\n",
                   rank, recv_num, status.MPI_TAG);
        } else {
            MPI_Wait(&request, &status);
            printf("Process with rank [%d], not received %d with tag %d.\n",
                   rank, recv_num, status.MPI_TAG);
        }

    } else if (rank == numtasks - 1) {
        // Last process close the circle.
        // Receives the number from the previous process.
        // Increments the number.
        // Sends the number to the first process.
        MPI_Irecv(&recv_num, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &request);

        MPI_Test(&request, &flag, &status);

        if (flag) {
            printf("Process with rank [%d], received %d with tag %d.\n",
                   rank, recv_num, status.MPI_TAG);
        } else {
            MPI_Wait(&request, &status);
            printf("Process with rank [%d], not received %d with tag %d.\n",
                   rank, recv_num, status.MPI_TAG);
        }
        recv_num++;

        MPI_Isend(&recv_num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);

    } else {
        // Middle process.
        // Receives the number from the previous process.
        // Increments the number.
        // Sends the number to the next process.
        MPI_Irecv(&recv_num, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &request);

        MPI_Test(&request, &flag, &status);

        if (flag) {
            printf("Process with rank [%d], received %d with tag %d.\n",
                   rank, recv_num, status.MPI_TAG);
        } else {
            MPI_Wait(&request, &status);
            printf("Process with rank [%d], not received %d with tag %d.\n",
                   rank, recv_num, status.MPI_TAG);
        }

        recv_num++;
        MPI_Isend(&recv_num, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, &request);
    }

    MPI_Finalize();

}
