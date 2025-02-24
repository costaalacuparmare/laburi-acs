#include "tema2.h"

// Function for download thread
void *download_thread_func(void *arg) {
    PeerData *data = (PeerData *) arg;

    // Inform tracker that the client has finished downloading all files
    if (data->nr_requested_files == 0) {
        MPI_Send(&data->rank, 1, MPI_INT, TRACKER_RANK, 4, MPI_COMM_WORLD);
        return NULL;
    }

    // Count the total number of segments to be downloaded
    int requested_segments = 0;
    for (int i = 0; i < data->nr_requested_files; i++) {
        requested_segments += data->requested_files[i].nr_segments;
    }

    // Keep track of downloaded segments to update regularly
    int nr_downloaded_segments = 0;

    // Keep track of previous client for equal distribution of tasks
    int prev_client = -1;

    // Request the list of peers from the tracker for the requested files
    MPI_Send(&data->nr_requested_files, 1, MPI_INT, TRACKER_RANK, 2,
             MPI_COMM_WORLD);
    for (int i = 0; i < data->nr_requested_files; i++) {
        MPI_Send(&data->requested_files[i].file_id, 1, MPI_INT, TRACKER_RANK,
                 TRACKER_UPDATE_TAG, MPI_COMM_WORLD);
    }
    int peers[data->nr_requested_files][data->nr_clients];
    MPI_Recv(&peers, data->nr_requested_files * data->nr_clients,
             MPI_INT, TRACKER_RANK, TRACKER_UPDATE_TAG, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);

    // Using a while loop for downloading segments for all files
    // for efficient use of threads and peer logic
    while (1) {
        // Keep track of the segments that are finished downloading
        int finished_file[data->nr_requested_files];
        for (int i = 0; i < data->nr_requested_files; i++) {
            finished_file[i] = 0;
        }

        // Download a segment at a time for each file
        for (int i = 0; i < data->nr_requested_files; i++) {
            // Get current file so that it is easier to work with
            FileData requested_file = data->requested_files[i];

            // Find a segment to download
            int current_segment = -1;
            for (int j = 0; j < requested_file.nr_segments; j++) {
                if (requested_file.received_segments[j] == 0) {
                    current_segment = j;
                    break;
                }
            }

            // If no segment was found, then the file is complete
            if (current_segment == -1) {
                // Create file path
                char filename[MAX_FILENAME];
                sprintf(filename, "client%d_file%d", data->rank,
                        requested_file.file_id);

                FILE *file = fopen(filename, "w");
                if (file == NULL) {
                    printf("Error at opening file for peer %d\n",
                           data->rank);
                    exit(-1);
                }

                // Write the segments to the file
                for (int j = 0; j < requested_file.nr_segments; j++) {
                    fprintf(file, "%s\n",
                            requested_file.segments[j]);
                }

                fclose(file);

                // Add finished file to owned files
                pthread_mutex_lock(&data->mutex);
                data->owned_files[data->nr_owned_files] = requested_file;
                data->nr_owned_files++;
                pthread_mutex_unlock(&data->mutex);

                // mark so that after all iterations the file is removed
                finished_file[i] = 1;

                // Inform tracker that the file is complete
                MPI_Send(&data->owned_files[data->nr_owned_files - 1], 1,
                         MPI_INT, TRACKER_RANK, FILE_COMPLETE_TAG,
                         MPI_COMM_WORLD);

                // Check if all files are downloaded
                if (requested_segments == 0) {
                    // Inform tracker that the client has finished downloading
                    MPI_Send(&data->rank, 1, MPI_INT, TRACKER_RANK,
                             ALL_COMPLETE_TAG, MPI_COMM_WORLD);
                    return NULL;
                }

                continue;
            }

            // Find a peer to download from that is not the previous client
            int seed = -1;
            int current_client = -1;

            for (int j = 0; j < data->nr_clients; j++) {
                if (peers[i][j] == 1 && j != prev_client - 1 &&
                    j != data->rank - 1) {
                    current_client = j + 1;
                    prev_client = current_client;
                    break;
                } else if (peers[i][j] == 2) {
                    seed = j + 1;
                    break;
                }
            }

            // If no peer was found, download from seed
            if (current_client == -1) {
                current_client = seed;
                prev_client = current_client;
            }

            // Request the segment from the peer
            char hash[HASH_SIZE + 1] = "0";
            strcpy(hash,requested_file.segments[current_segment]);
            int confirmation;

            // Send request to a peer / seed
            MPI_Send(&hash, HASH_SIZE + 1, MPI_CHAR, current_client,
                     DOWNLOAD_TAG, MPI_COMM_WORLD);
            MPI_Recv(&confirmation, 1, MPI_INT, current_client, UPLOAD_TAG,
                     MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Update the downloaded file list
            if (confirmation == 1) {
                requested_file.received_segments[current_segment] = 1;
                nr_downloaded_segments++;

                // Update the total number of segments to be downloaded
                requested_segments--;
            } else {
                // Peer did not have the segment, the client moves to next file
                continue;
            }

            // Request the updated list of peers from the tracker
            if (nr_downloaded_segments == MAX_CHUNKS_UPDATE) {
                // Specify which files are requested
                MPI_Send(&data->nr_requested_files, 1, MPI_INT, TRACKER_RANK, 2,
                         MPI_COMM_WORLD);
                for (int i = 0; i < data->nr_requested_files; i++) {
                    MPI_Send(&data->requested_files[i].file_id, 1, MPI_INT,
                             TRACKER_RANK, TRACKER_UPDATE_TAG, MPI_COMM_WORLD);
                }
                MPI_Recv(&peers, data->nr_requested_files * data->nr_clients,
                         MPI_INT, TRACKER_RANK, TRACKER_UPDATE_TAG,
                         MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                // Reset the downloaded segments for update counter
                nr_downloaded_segments = 0;
            }

            // Update the requested files with the new segment
            pthread_mutex_lock(&data->mutex);
            data->requested_files[i] = requested_file;
            pthread_mutex_unlock(&data->mutex);
        }

        // Remove finished file from requested files
        for (int i = 0; i < data->nr_requested_files; i++) {
            if (finished_file[i] == 1) {
                pthread_mutex_lock(&data->mutex);
                for (int j = i; j < data->nr_requested_files - 1; j++) {
                    data->requested_files[j] = data->requested_files[j + 1];
                }
                data->nr_requested_files--;
                pthread_mutex_unlock(&data->mutex);
            }
        }
    }

    return NULL;
}

// Function for upload thread
void *upload_thread_func(void *arg) {
    PeerData *data = (PeerData *) arg;

    // Loop waiting for requests
    while (1) {
        MPI_Status status;
        char hash[HASH_SIZE + 1];
        MPI_Recv(&hash, HASH_SIZE + 1, MPI_CHAR, MPI_ANY_SOURCE, DOWNLOAD_TAG,
                 MPI_COMM_WORLD, &status);

        // Shutdown when tracker knows that all clients finished downloading
        if (status.MPI_SOURCE == TRACKER_RANK) {
            return NULL;
        }

        // used for ACKs
        int found = 0;

        // Check if the client as seed has the requested segment
        pthread_mutex_lock(&data->mutex);
        for (int i = 0; i < data->nr_owned_files; i++) {
            for (int j = 0; j < data->owned_files[i].nr_segments; j++) {
                if (strcmp(data->owned_files[i].segments[j], hash) == 0) {
                    found = 1;
                    break;
                }
            }
        }
        pthread_mutex_unlock(&data->mutex);

        // Check if the client as peer has the requested segment
        if (!found) {
            pthread_mutex_lock(&data->mutex);
            for (int i = 0; i < data->nr_requested_files; i++) {
                for (int j = 0; j < data->requested_files[i].nr_segments; j++) {
                    if (strcmp(data->requested_files[i].segments[j], hash) ==
                        0) {
                        found = 1;
                        break;
                    }
                }
            }
            pthread_mutex_unlock(&data->mutex);
        }

        // Send ACK / NACK to the client
        MPI_Send(&found, 1, MPI_INT, status.MPI_SOURCE, UPLOAD_TAG,
                 MPI_COMM_WORLD);
    }

    return NULL;
}

void tracker(int numtasks, int rank) {
    MPI_Status status;

    int nr_clients = numtasks - 1;
    int nr_files = 0;

    // Swarm with the segments that each client has for each file
    // 0 - nothing, 1 - peer, 2 - seed
    int swarm[MAX_FILES][nr_clients];
    for (int i = 0; i < MAX_FILES; i++) {
        for (int j = 0; j < nr_clients; j++) {
            for (int k = 0; k < MAX_CHUNKS; k++) {
                swarm[i][j] = 0;
            }
        }
    }

    // swarm_segment_count[i] = number of segments for file i
    int swarm_segment_count[MAX_FILES];
    for (int i = 0; i < MAX_FILES; i++) {
        swarm_segment_count[i] = 0;
    }

    // swarm_hashes[i][j] = hash of segments j for file i
    char swarm_hashes[MAX_FILES][MAX_CHUNKS][HASH_SIZE + 1];
    for (int i = 0; i < MAX_FILES; i++) {
        for (int j = 0; j < MAX_CHUNKS; j++) {
            swarm_hashes[i][j][0] = '\0';
        }
    }

    // Receive the number of files for each client
    for (int i = 0; i < nr_clients; i++) {
        int client_segment_count[MAX_FILES];
        for (int j = 0; j < MAX_FILES; j++) {
            client_segment_count[j] = 0;
        }

        // Receive the number of files for the client
        int nr_client_files;
        MPI_Recv(&nr_client_files, 1, MPI_INT, i + 1, DOWNLOAD_TAG,
                 MPI_COMM_WORLD, &status);

        for (int j = 0; j < nr_client_files; j++) {

            // Receive the file id
            int file_id = 0;
            MPI_Recv(&file_id, 1, MPI_INT, i + 1, DOWNLOAD_TAG, MPI_COMM_WORLD,
                     &status);

            // Receive the number of segments for the file
            MPI_Recv(&client_segment_count[file_id], 1, MPI_INT, i + 1,
                     DOWNLOAD_TAG, MPI_COMM_WORLD, &status);

            // Receive the hashes for the segments
            MPI_Recv(&swarm_hashes[file_id],
                     client_segment_count[file_id] * (HASH_SIZE + 1),
                     MPI_CHAR, i + 1, DOWNLOAD_TAG, MPI_COMM_WORLD, &status);

            // Update the number of total files
            if (nr_files < file_id) {
                nr_files = file_id;
            }
        }

        // Mark the files that each client is seed for and their segment count
        int client_rank = status.MPI_SOURCE;
        for (int j = 0; j < MAX_FILES; j++) {
            if (client_segment_count[j] != 0) {
                swarm_segment_count[j] = client_segment_count[j];
                swarm[j][client_rank - 1] = 2;
            }
        }
    }

    // Send the total number of segments for each file and the hashes
    // marking the end of the initialization
    for (int i = 0; i < nr_clients; i++) {
        MPI_Send(&swarm_segment_count, MAX_FILES, MPI_INT, i + 1, UPLOAD_TAG,
                 MPI_COMM_WORLD);
        MPI_Send(&swarm_hashes, MAX_FILES * MAX_CHUNKS * (HASH_SIZE + 1),
                 MPI_CHAR, i + 1, UPLOAD_TAG, MPI_COMM_WORLD);
    }

    // Used to monitor clients that are downloading
    int active_clients = nr_clients;

    // Tracker loop for waiting requests
    while (1) {

        // Receive requests from clients
        int info;
        MPI_Status status;
        MPI_Recv(&info, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD,
                 &status);

        switch (status.MPI_TAG) {
            // Client requests current swarm info about a certain file
            case TRACKER_UPDATE_TAG: {
                // Send the list of peers for the requested files
                int peers[info][nr_clients];
                for (int i = 0; i < info; i++) {
                    int file_id;
                    MPI_Recv(&file_id, 1, MPI_INT, status.MPI_SOURCE, 2,
                             MPI_COMM_WORLD, &status);
                    for (int j = 0; j < nr_clients; j++) {
                        peers[i][j] = swarm[file_id][j];
                    }
                    swarm[file_id][status.MPI_SOURCE - 1] = 1;
                }
                // Send all peers and the segments info to the client
                MPI_Send(&peers, info * nr_clients, MPI_INT, status.MPI_SOURCE,
                         TRACKER_UPDATE_TAG, MPI_COMM_WORLD);
                break;
            }
            // Client informs tracker that it has finished downloading a file
            case FILE_COMPLETE_TAG: {
                // Updates to the swarm that the
                // client has all the segments for the file
                swarm[info][status.MPI_SOURCE - 1] = 2;
                break;
            }
            case ALL_COMPLETE_TAG: {
                // Client has finished downloading all files
                active_clients--;
                if (active_clients == 0) {
                    // All clients have finished downloading
                    char final_message[HASH_SIZE + 1] = "0";
                    for (int i = 0; i < nr_clients; i++) {
                        MPI_Send(&final_message, HASH_SIZE + 1, MPI_CHAR, i + 1,
                                 DOWNLOAD_TAG, MPI_COMM_WORLD);
                    }
                    return;
                }
                break;
            }
        }

        // Check if all clients have finished downloading
        if (active_clients == 0) {
            return;
        }
    }
}

// Function for reading input for each peer
void read_input(int rank, PeerData *peer_info) {
    // Create the filename for the peer
    char filename[MAX_FILENAME];
    sprintf(filename, "in%d.txt", rank);

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error at opening file for peer %d\n", rank);
        exit(-1);
    }

    // Owned files reading
    fscanf(file, "%d", &peer_info->nr_owned_files);
    for (int i = 0; i < peer_info->nr_owned_files; i++) {
        // Read the filename, the number of segments, and the segments
        char filename[MAX_FILENAME];
        fscanf(file, "%s", filename);
        peer_info->owned_files[i].file_id =
                filename[strlen(filename) - 1] - '0';
        fscanf(file, "%d", &peer_info->owned_files[i].nr_segments);
        for (int j = 0; j < peer_info->owned_files[i].nr_segments; j++) {
            fscanf(file, "%s", peer_info->owned_files[i].segments[j]);
        }
    }

    // Requested files reading
    fscanf(file, "%d", &peer_info->nr_requested_files);
    for (int i = 0; i < peer_info->nr_requested_files; i++) {
        // Read the filename and initialize the requested segments
        char filename[MAX_FILENAME];
        fscanf(file, "%s", filename);
        peer_info->requested_files[i].file_id =
                filename[strlen(filename) - 1] - '0';
        for (int j = 0; j < MAX_CHUNKS; j++) {
            peer_info->requested_files[i].received_segments[j] = 0;
        }
    }
    fclose(file);
}

void peer(int numtasks, int rank) {

    // Reads input
    PeerData peer_info;
    read_input(rank, &peer_info);

    // Send the number of files the peer has and their info
    MPI_Send(&peer_info.nr_owned_files, 1, MPI_INT, TRACKER_RANK, 0,
             MPI_COMM_WORLD);
    for (int i = 0; i < peer_info.nr_owned_files; i++) {
        MPI_Send(&peer_info.owned_files[i].file_id, 1, MPI_INT, TRACKER_RANK,
                 DOWNLOAD_TAG, MPI_COMM_WORLD);
        MPI_Send(&peer_info.owned_files[i].nr_segments, 1, MPI_INT,
                 TRACKER_RANK, DOWNLOAD_TAG, MPI_COMM_WORLD);
        MPI_Send(&peer_info.owned_files[i].segments,
                 peer_info.owned_files[i].nr_segments * (HASH_SIZE + 1),
                 MPI_CHAR, TRACKER_RANK, DOWNLOAD_TAG, MPI_COMM_WORLD);
    }

    // For init confirmation, client receives the number of segments
    // for each requested file and their hashes
    int local_file_segment_count[MAX_FILES];
    char local_file_hashes[MAX_FILES][MAX_CHUNKS][HASH_SIZE + 1];
    MPI_Recv(&local_file_segment_count, MAX_FILES, MPI_INT, TRACKER_RANK,
             UPLOAD_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&local_file_hashes, MAX_FILES * MAX_CHUNKS * (HASH_SIZE + 1),
             MPI_CHAR, TRACKER_RANK, UPLOAD_TAG, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);

    // Updates for download the number of segments for each requested files
    // And the hashes for the segments for requested files
    for (int i = 0; i < peer_info.nr_requested_files; i++) {
        peer_info.requested_files[i].nr_segments =
                local_file_segment_count[peer_info.requested_files[i].file_id];
        for (int j = 0; j < peer_info.requested_files[i].nr_segments; j++) {
            strcpy(peer_info.requested_files[i].segments[j],
                   local_file_hashes[peer_info.requested_files[i].file_id][j]);
        }
    }


    // Add info in the peer structure for threads
    peer_info.nr_clients = numtasks - 1;
    peer_info.rank = rank;
    pthread_mutex_init(&peer_info.mutex, 0);

    pthread_t download_thread;
    pthread_t upload_thread;
    void *status;
    int r;

    r = pthread_create(&download_thread, NULL, download_thread_func,
                       (void *) &peer_info);
    if (r) {
        printf("Error at creating download thread\n");
        exit(-1);
    }

    r = pthread_create(&upload_thread, NULL, upload_thread_func,
                       (void *) &peer_info);
    if (r) {
        printf("Error at creating upload thread\n");
        exit(-1);
    }

    r = pthread_join(download_thread, &status);
    if (r) {
        printf("Error at joining download thread\n");
        exit(-1);
    }

    r = pthread_join(upload_thread, &status);
    if (r) {
        printf("Error at joining upload thread\n");
        exit(-1);
    }

    pthread_mutex_destroy(&peer_info.mutex);
}

int main(int argc, char *argv[]) {
    int numtasks, rank;
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    if (provided < MPI_THREAD_MULTIPLE) {
        fprintf(stderr, "MPI doesn't support multi-threading\n");
        exit(-1);
    }
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == TRACKER_RANK) {
        tracker(numtasks, rank);
    } else {
        peer(numtasks, rank);
    }

    MPI_Finalize();
}
