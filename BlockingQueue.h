#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <cstddef>
#include <stdexcept>

template<typename T>
class BlockingQueue {
private:
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable notEmpty;
    std::condition_variable notFull;

    size_t capacity;
    bool closed;

public:
    explicit BlockingQueue(size_t capacity = 0)
        : capacity(capacity), closed(false) {}

    void push(const T& item) {
        std::unique_lock<std::mutex> lock(mtx);

        if (closed)
            throw std::runtime_error("Queue is closed");

        if (capacity > 0) {
            notFull.wait(lock, [this]() {
                return queue.size() < capacity || closed;
            });
        }

        if (closed)
            throw std::runtime_error("Queue is closed");

        queue.push(item);
        notEmpty.notify_one();
    }

    bool pop(T& item) {
        std::unique_lock<std::mutex> lock(mtx);

        notEmpty.wait(lock, [this]() {
            return !queue.empty() || closed;
        });

        if (queue.empty() && closed)
            return false;

        item = std::move(queue.front());
        queue.pop();

        if (capacity > 0)
            notFull.notify_one();

        return true;
    }

    void close() {
        std::lock_guard<std::mutex> lock(mtx);
        closed = true;
        notEmpty.notify_all();
        notFull.notify_all();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(mtx);
        return queue.size();
    }
};

#endif
