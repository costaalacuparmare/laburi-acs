#include "header.h"

using namespace std;

void *mapperThread(void *args) {
    // get pointer to thread arguments
    auto *mapper_args = (ThreadArgs *) args;

    // local results for each mapper
    unordered_map <string, set<int>> local_results;

    FileInfo file;

    while (mapper_args->queue->getNextFile(file)) {
        // open file
        ifstream f(file.filename);
        if (!f.is_open()) {
            cerr << "Error reading file: " << file.filename << "\n";
            continue;
        }

        // normalize each word in the file
        // (remove punctuation and convert to lowercase)
        string word;
        while (f >> word) {
            string norm_word;
            for (char ch: word) {
                if (isalpha(ch)) {
                    norm_word += (char) tolower(ch);
                }
            }

            // if the normalized word is not empty, add the file id
            if (!norm_word.empty()) {
                auto &file_ids = local_results[norm_word];
                if (find(file_ids.begin(), file_ids.end(), file.id) ==
                    file_ids.end()) {
                    file_ids.insert(file.id);
                }
            }
        }
    }

    // lock the mutex and push the local results to the results vector
    pthread_mutex_lock(mapper_args->mutex);
    mapper_args->results->push_back(local_results);
    pthread_mutex_unlock(mapper_args->mutex);

    // wait for all mapper threads to finish and reducer threads to start
    pthread_barrier_wait(mapper_args->barrier_threads);

    return nullptr;
}
