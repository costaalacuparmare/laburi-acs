#include "header.h"

using namespace std;

// comparator function for sorting results
// if the number of file ids is the same, sort alphabetically
bool compareResults(const pair<string, set<int>> &a,
                    const pair<string,set<int>> &b) {
    if (a.second.size() == b.second.size()) {
        return a.first < b.first;
    } else {
        return a.second.size() > b.second.size();
    }
}

void *reducerThread(void *args) {
    // get pointer to thread arguments
    auto *reducer_args = (ThreadArgs *) args;

    // wait for all mapper threads to finish
    pthread_barrier_wait(reducer_args->barrier_threads);

    char letter;

    // if the alphabet queue is empty, the reducer thread is done
    while (!reducer_args->alphabet->empty()) {

        // get the next letter from the alphabet queue
        // if a reducer thread finishes before the others, it will
        // continue to get letters from the queue until it is empty
        pthread_mutex_lock(reducer_args->mutex);
        letter = reducer_args->alphabet->top();
        reducer_args->alphabet->pop();
        pthread_mutex_unlock(reducer_args->mutex);

        // local results for each letter
        unordered_map<string, set<int>> local_results;

        // combine the results from all mappers for the current letter
        for (auto &result: *reducer_args->results) {
            for (const auto &entry: result) {
                if (entry.first[0] == letter) {
                    auto &file_ids = local_results[entry.first];
                    for (int file_id: entry.second) {
                        file_ids.insert(file_id);
                    }
                } else {
                    continue;
                }
            }
        }

        // sort the results by number of file ids
        vector<pair<string, set<int>>> sorted_results(local_results.begin(),
                                                      local_results.end());
        sort(sorted_results.begin(), sorted_results.end(), compareResults);

        // write the results to the output file
        ofstream out(string(1, letter) + ".txt");
        for (const auto &entry: sorted_results) {
            out << entry.first << ":[";
            for (int file_id: entry.second) {
                out << file_id;
                if (file_id != *entry.second.rbegin()) {
                    out << " ";
                }
            }
            out << "]\n";
        }
        out.close();
    }

    return nullptr;
}
