# Parallel and Distributed Algorithms - 1st Homework

### Constantinescu Vlad 333CB

The archive contains:

- `header.h` - the header file containing the constants and the structures used in the project
- `main.cpp` - the implementation for thread creation and launching
- `mapper.cpp` - the implementation of the mapper function
- `reducer.cpp` - the implementation of the reducer function
- `queue.cpp` - the implementation of the FileQueue class
- `Makefile` - the makefile used to compile the project

### FileQueue Class
- Class used to store the filenames for mapper threads

```C++
    class FileQueue {
        public:
        FileQueue(const string &file_path);
        ~FileQueue();
        bool getNextFile(FileInfo &file);
        private:
        vector<FileInfo> files;
        // index of the next file to be processed
        size_t next_file = 0;
        pthread_mutex_t mutex{};
    };
```

- `FileInfo` - structure used to store the filename and the number of lines in the file

```C++
    struct FileInfo {
        string filename;
        size_t lines;
    };
```

- `Constructor` - reads the filenames from the file at `file_path` and 
  stores them in the `files` vector, initializes the mutex


- `Destructor` - destroys the mutex


- `getNextFile` - returns the next file to be processed by a mapper thread 
  using the mutex to avoid race conditions

### Thread Arguments Structure
- Structure used to pass the arguments to the threads

```C++
    struct ThreadArgs {
    FileQueue *queue{};
    vector<unordered_map<string, set<int>>> *results{};
    pthread_mutex_t *mutex{};
    pthread_barrier_t *barrier_threads{};
    stack<char> *alphabet{};
    };
```

- `queue` - pointer to the FileQueue object (used by the mapper threads)


- `results` - pointer to the vector of unordered_maps used to store the 
  results from mapper (used by the reducer threads)


- `mutex` - pointer to the mutex used by mapper to add the results to the vector
and by the reducer to access the alphabet queue (both)


- `barrier_threads` - pointer to the barrier used to synchronize the threads 
  so that the reducer threads start only after all the mapper threads have 
  finished (both)


- `alphabet` - pointer to the stack used to store the alphabet (used by the reducer threads)

### Mapper Function

- Basic structure of the mapper function

```C++
    void *mapper(void *arg) {
        MapperArgs *args = (MapperArgs *) arg;
        // get the next file to be processed
        FileInfo file;
        while (args->queue->getNextFile(file)) {
            // process the file
            // ...
            // read the words from the file
            // normalize the words
            // add the words to the local results map
        }
        
        // add the local results map to the global results vector
        // synchronize the threads with the barrier
        
        return nullptr;
    }
```

### Reducer Functions

- Basic structure of the reducer function

```C++
    void *reducer(void *arg) {
        ReducerArgs *args = (ReducerArgs *) arg;
        // get the next result to be processed
        while (letters in the alphabet stack) { 
            // process the result
            // ...
            // get all the words that start with the current letter
            // add the words local results map
            // sort as vector and write to the letter output file
        }
        
        return nullptr;
    }
```

### Tasks and Implementation Details
- Threads are created and launched in the `main.cpp` file
- The mapper threads read the words from the files, normalize them and add them to the local results map
- The reducer threads get the words that start with a certain letter from the local results map, sort them and write them to the output file
- for synchronization, the threads use a barrier to make sure that the reducer threads start only after all the mapper threads have finished
- the mapper threads use a mutex to add the local results map to the global results vector
- the reducer threads use the same mutex to access the alphabet stack
- the mapper threads use a different mutex to get the next file to be processed
- the mapper-reducer paradigm is respected by the implementation