#ifndef CONSUMER_H
#define CONSUMER_H

#include "BlockingQueue.h"
#include "Task.h"
#include <thread>
#include <vector>


class Consumer {
private:
    BlockingQueue<Task>& taskQueue;
    BlockingQueue<std::pair<int, Matrix>>& queue_result;
    std::vector<std::thread> workers;

    void workerLoop();

public:
    Consumer(BlockingQueue<Task>& tasks, BlockingQueue<std::pair<int, Matrix>>& results, int threadCount);

    void start();
    void join();
};

#endif