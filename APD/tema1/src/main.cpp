#include "header.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0]
             << " <num mappers> <num reducers> <input file>\n";
        return 1;
    }

    // get the number of mappers and reducers
    int num_mappers = stoi(argv[1]);
    int num_reducers = stoi(argv[2]);
    string file_path = argv[3];

    // create custom file queue
    FileQueue file_queue = FileQueue(file_path);

    // create mutex and barrier for synchronization
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, nullptr);

    pthread_barrier_t barrier;
    pthread_barrier_init(&barrier, nullptr, num_mappers + num_reducers);

    // create results vector for results from mappers
    vector<unordered_map<string, set<int>>> results;

    // create alphabet queue for reducers
    stack<char> alphabet;
    for (char c = 'a'; c <= 'z'; c++) {
        alphabet.push(c);
    }

    // create threads
    vector<pthread_t> threads(num_mappers + num_reducers);
    ThreadArgs args[num_mappers + num_reducers];

    for (int i = 0; i < num_mappers + num_reducers; i++) {
        // pass thread arguments
        args[i] = {&file_queue, &results, &mutex, &barrier, &alphabet};

        // based on the thread id, call the appropriate thread function
        void *(*threadFunction)(void *) = i < num_mappers ? mapperThread
                                                          : reducerThread;
        int ret = pthread_create(&threads[i], nullptr, threadFunction,
                                 &args[i]);
        if (ret) {
            cerr << "Error creating thread: " << ret << "\n";
            return 1;
        }
    }

    // join threads
    for (auto &thread: threads) {
        int ret = pthread_join(thread, nullptr);
        if (ret) {
            cerr << "Error joining thread: " << ret << "\n";
            return 1;
        }
    }

    // destroy mutex and barrier
    pthread_barrier_destroy(&barrier);
    pthread_mutex_destroy(&mutex);

    return 0;
}
