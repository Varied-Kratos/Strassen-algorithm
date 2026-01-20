#ifndef PRODUCER_H
#define PRODUCER_H

#include "BlockingQueue.h"
#include "Task.h"
#include "matrix.h"
#include <vector>

class Producer {
private:
    BlockingQueue<Task>& taskQueue;

public:
    explicit Producer(BlockingQueue<Task>& q) : taskQueue(q) {}

    void generateFirstLevelTasks(const Matrix& A, const Matrix& B) {
        auto a = A.split();
        auto b = B.split();

        std::vector<Task> tasks;

        tasks.push_back(Task{a[0] + a[3], b[0] + b[3], 1});
        tasks.push_back(Task{a[2] + a[3], b[0], 2});
        tasks.push_back(Task{a[0], b[1] - b[3], 3});
        tasks.push_back(Task{a[3], b[2] - b[0], 4});
        tasks.push_back(Task{a[0] + a[1], b[3], 5});
        tasks.push_back(Task{a[2] - a[0], b[0] + b[1], 6});
        tasks.push_back(Task{a[1] - a[3], b[2] + b[3], 7});

        
        for (auto& t : tasks) {
            taskQueue.push(std::move(t));
        }
    }
};

#endif
