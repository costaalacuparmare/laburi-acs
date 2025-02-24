#include <mpi.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macros for various constants
#define TRACKER_RANK 0
#define MAX_FILES 10
#define MAX_FILENAME 15
#define HASH_SIZE 32
#define MAX_CHUNKS 100
#define MAX_CHUNKS_UPDATE 10

// Tags from thread communication
#define DOWNLOAD_TAG 0
#define UPLOAD_TAG 1
#define TRACKER_UPDATE_TAG 2
#define FILE_COMPLETE_TAG 3
#define ALL_COMPLETE_TAG 4

// Structure for files used with owned and requested files
typedef struct {
    int file_id;
    int nr_segments;
    int received_segments[MAX_CHUNKS];
    char segments[MAX_CHUNKS][HASH_SIZE + 1];
} FileData;

// Structure for peer data used in threads
typedef struct {
    int nr_clients;
    int rank;
    pthread_mutex_t mutex;
    int nr_owned_files;
    FileData owned_files[MAX_FILES];
    int nr_requested_files;
    FileData requested_files[MAX_FILES];
} PeerData;