#include <iostream>
#include<thread>

// Settings
const static size_t SAMPLE_SIZE = 1000000000;
const static size_t RANGE_OF_RANDOM = 10;

void threadWork(size_t amount, size_t id, size_t arr[RANGE_OF_RANDOM]) {
    for(int i = 0; i < RANGE_OF_RANDOM; i++){
    }
    for (size_t i = 0; i < amount; i++){
        size_t random = rand() % RANGE_OF_RANDOM + 1;
        arr[random - 1]++;
    }
}

int main(int argc, char** argv) {
    size_t numberOfThreads = 5;
    // Validate arguments
    if (argc > 2) {
        std::cout << "Too many args" << std::endl;
        std::cout << "Usage: " << argv[0] << " <number of threads>" << std::endl;
        return 0;
    }
    if (argc == 2) {
        numberOfThreads = atoi(argv[1]);
        if (numberOfThreads < 1) {
            std::cout << "Number of threads must be at least 1" << std::endl;
            return 0;
        }
    }

    // Creating threads
    size_t results[numberOfThreads][RANGE_OF_RANDOM];
    for(size_t i = 0; i < numberOfThreads; i++){
        for(size_t j = 0; j < RANGE_OF_RANDOM; j++){
            results[i][j] = 0;
        }
    }
    std::thread threads[numberOfThreads];
    auto start = std::chrono::system_clock::now();
    for(size_t i = 0; i < numberOfThreads; i++){
        threads[i] = std::thread(threadWork, SAMPLE_SIZE/numberOfThreads, i, results[i]);
    }
    std::cout << "Threads started" << std::endl;
    // Joining threads
    for(size_t i = 0; i < numberOfThreads; i++){
        threads[i].join();
    }
    auto end = std::chrono::system_clock::now();
    std::cout << "Threads finished" << std::endl;

    // Displaying results
    size_t minIndex = 0;
    size_t maxIndex = 0;
    size_t tally[RANGE_OF_RANDOM] = {0};
    size_t total = 0;
    for(size_t i = 0; i < numberOfThreads; i++){
        std::cout << "Thread#" << i << std::endl;
        for(size_t j = 0; j < RANGE_OF_RANDOM; j++){
            std::cout << j + 1 << ":\t" << results[i][j] << "\n";
            tally[j] += results[i][j];
            total += results[i][j];
            minIndex = tally[j] < tally[minIndex] ? j : minIndex;
            maxIndex = tally[j] > tally[maxIndex] ? j : maxIndex;
        }
        std::cout << std::endl;
    }
    for(size_t i = 0; i < RANGE_OF_RANDOM; i++){
        std::cout << i + 1 << ":\t" << tally[i] << "\t%" << tally[i] * 100 / total << std::endl;
    }
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "Duration: " << elapsed_seconds.count() << " seconds" << std::endl;
    std::cout << "Least picked number: " << minIndex + 1 << std::endl;
    std::cout << "Most picked number: " << maxIndex + 1 << std::endl;
    std::cout << "Difference between most and least picked numbers: " << tally[maxIndex] - tally[minIndex] << std::endl;
    return 0;
}


