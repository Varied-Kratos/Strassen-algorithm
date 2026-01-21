#include "Consumer.h"

using namespace std;

Consumer::Consumer(BlockingQueue<Task>& tasks, BlockingQueue<pair<int, Matrix>>& results, int threadCount) : taskQueue(tasks), queue_result(results)
{
    workers.reserve(threadCount);
}

void Consumer::start() {
    for (size_t i = 0; i < workers.capacity(); ++i) {
        workers.emplace_back(&Consumer::workerLoop, this);
    }
}

void Consumer::workerLoop() {
    Task task;

    while (taskQueue.pop(task)) {
        Matrix result = task.A * task.B;
        queue_result.push({task.M_id, result});
    }
}

void Consumer::join() {
    for (auto& t : workers) {
        if (t.joinable())
            t.join();
    }
}