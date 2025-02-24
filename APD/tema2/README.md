# Parallel and Distributed Algorithms - 2nd Homework

### Constantinescu Vlad 333CB

The archive contains:

- `tema2.h` - the header file containing the constants and the structures used in the project
- `tema2.c` - the implementation for peer, peer threads and tracker
- `Makefile` - the makefile used to compile the project

## Peer Structures
- Structure used to store the information about a peer useful for threads

```C
typedef struct {     
    int nr_clients;
    int rank;
    pthread_mutex_t mutex;
    int nr_owned_files;
    FileData owned_files[MAX_FILES];
    int nr_requested_files;
    FileData requested_files[MAX_FILES];
} PeerData;
```

- `FileData` - structure used to store information about owned or requested files

```C
typedef struct {
    int file_id;
    int nr_segments;
    int received_segments[MAX_CHUNKS];
    char segments[MAX_CHUNKS][HASH_SIZE + 1];
} FileData;
```

## Tracker Logic

### Initialization

Initialize the tracker with seeds, the number of segments / file and the hashes

Tracker receives from peers the number of files each client owns, the number of segments each file has and the hashes for each segment

- `swarm[MAX_FILES][nr_client]`: which client has which file


- `swarm_segment_count[MAX_FILES]`: how many segments each file has


- `swarm_hashes[MAX_FILES][MAX_CHUNKS][HASH_SIZE + 1]`: the hashes for each segment of each file

As the tracker receives the information from client, it updates the structures

After all the information is received, the tracker sends the cumulated information to all clients

### Awaiting Requests
Considers all clients as active clients that are downloading files

The tracker listens for requests from the peers. For each type of message

- `Update request`: receives which files the peer is interested in
and send the clients from the swarm that are peers / seeds for the requested files.
Also memorises the source of the request as a peer for the requested files


- `Finished file request`: receives the file id for the file that the peer has finished downloading
and marks the peer as a seed for the file


- `Finished all files request`: decreases the number of active clients.
If the number of active clients is 0, the tracker sends a message to all
peers / seeds to shut down their upload threads and return `NULL` itself


## Peer Logic

### Initialization

- `read_input`: reads the input file and initializes the peer data structure
with the number of owned files, their ids, the number of segments for each file and the hashes for each segment,
as well as the number of requested files, their ids and marks the received segments (used for download) as 0

```C
void read_input(int rank, PeerData *peer_info) {
    // Create the filename for the peer
    ...
    // Open file
    ...
    // Owned files reading
    fscanf(file, "%d", &peer_info->nr_owned_files);
    for (int i = 0; i < peer_info->nr_owned_files; i++) {
        // Read the filename, the number of segments, and the segments
        ...
    }
    // Requested files reading
    fscanf(file, "%d", &peer_info->nr_requested_files);
    for (int i = 0; i < peer_info->nr_requested_files; i++) {
        // Read the filename and initialize the requested segments
        ...
        for (int j = 0; j < MAX_CHUNKS; j++) {
            peer_info->requested_files[i].received_segments[j] = 0;
        }
    }
    // Close file
}
```

Send the information to the tracker, then receive the cumulated information from the tracker

From the received information, the peer stores the number of segments and the hashes for all
requested files

Initializes the number of clients, the rank and the mutex

### Download Thread

Received the PeerData structure as a parameter

If the peer is a seed, meaning it has 0 requested files, it informs the tracker
that it finished downloading all files and shuts down

Computes the total number of file segments for all files to track the download progress

Requests the peers from the tracker for the requested files

Iterates through the requested files and downloads a segment for each file at a time


- `Segment selection`: Iterates sequentially through the segments of each file.
If there are no segments left, it moves the file to the owned files and writes
the hashes in the output file, marking the current file as finished to be
removed from the requested files after current iteration so that indices don't get messed up


- `Peer / Seed selection`: Uses a version of Round Robin to select the peer for the file.
Makes sure the next peer is different from the previous one and if it doesn't find a peer
it sends the request to a seed


- `Segment download`: Sends the request to the selected peer / seed and waits for the response.
If the response is positive, it updates the received segments for the file and the total
number of received segments, otherwise it skips to the next segment


- `Update request`: Sends the request to the tracker once every 10 segments
to update own peers/ seeds list for the requested files


_Efficiency_: The download thread opts for a segmented download of each file
to increase chances of other peers downloading from them to avoid seed selection
as well as implements a Round Robin selection of peers to download from to avoid
overloading a single peer

### Upload Thread

Received the PeerData structure as a parameter

Listens for requests from any source, if the request is from the tracker, it shuts down


- `Search as seed`: searches for the requested file in the owned files and marks
if the received hash is found in the owned file


- `Search as peer`: searches for the requested file in the requested files that
are partially downloaded and marks if the received hash is found


- `Send response`: if the hash is found, sends an ACk as value `1`, otherwise sends `0`

## Synchronization of Peer Threads

the PeerData structure holds a mutex that is used to synchronize the threads

- `Download Thread`: locks the mutex before updating the received segments for
  every segment for every file that is downloaded, before moving completed files to the owned files
  and before removing the file from the requested files so that the upload thread can't access the
  files while they are being modified. Also uses local variables for current file to
  eliminate potential race conditions

```C
// Update the requested files with the new segment
pthread_mutex_lock(&data->mutex);
data->requested_files[i] = requested_file;
pthread_mutex_unlock(&data->mutex);
```

```C
// Add finished file to owned files
pthread_mutex_lock(&data->mutex);
data->owned_files[data->nr_owned_files] = requested_file;
data->nr_owned_files++;
pthread_mutex_unlock(&data->mutex);
```
```C
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
```


- `Upload Thread`: locks the mutex before searching for the requested file in the owned files
  or requested files, so that the upload thread can't access the files while they are being modified

```C
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
```

```C
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
```