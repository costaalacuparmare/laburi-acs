#include "header.h"

using namespace std;

// constructor for the FileQueue class
FileQueue::FileQueue(const string &file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        throw runtime_error("Error opening input file");
    }

    int num_files;
    file >> num_files;
    files.reserve(num_files);


    // get each file name and size and store it in the files vector
    for (int i = 0; i < num_files; i++) {
        string filename;
        file >> filename;

        ifstream f(filename);
        if (!f.is_open()) {
            throw runtime_error("Error opening file: " + filename);
        }
        size_t size = f.tellg();
        files.push_back({filename, i + 1, size});
    }

    // sort files by size in descending order
    sort(files.begin(), files.end(),
         [](const FileInfo &a, const FileInfo &b) {
             return a.size > b.size;
         });

    pthread_mutex_init(&mutex, nullptr);
}

FileQueue::~FileQueue() {
    pthread_mutex_destroy(&mutex);
}

// get the next file from the queue
bool FileQueue::getNextFile(FileInfo &file) {
    pthread_mutex_lock(&mutex);
    if (next_file >= files.size()) {
        pthread_mutex_unlock(&mutex);
        return false;
    }
    file = files[next_file++];
    pthread_mutex_unlock(&mutex);
    return true;
}

