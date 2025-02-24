#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <pthread.h>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <stack>

using namespace std;

// struct to hold information about a file
struct FileInfo {
    std::string filename;
    int id;
    size_t size;
};

// custom file queue class
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

// struct to hold arguments for the threads
struct ThreadArgs {
    FileQueue *queue{};
    vector<unordered_map<string, set<int>>> *results{};
    pthread_mutex_t *mutex{};
    pthread_barrier_t *barrier_threads{};
    stack<char> *alphabet{};
};

// functions for the threads
void *mapperThread(void *args);
void *reducerThread(void *args);