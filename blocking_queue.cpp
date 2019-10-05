#include "blocking_queue.h"
#include "block.h"
#include <condition_variable>
#include <mutex>

BlockingQueue::BlockingQueue(size_t queue_limit): queue_limit(queue_limit) {}

void BlockingQueue::push(Block b) {
    std::unique_lock<std::mutex> lock(m);
    while (q.size() == queue_limit) {
        push_cv.wait(lock);
    }
    q.push(b);
    pop_cv.notify_all();
}

Block BlockingQueue::pop() {
    Block b;
    std::unique_lock<std::mutex> lock(m);

    while (q.empty()) {
        pop_cv.wait(lock);
    }
    b = q.front();
    q.pop();
    push_cv.notify_all();
    return b;
}

bool BlockingQueue::empty() {
    return q.empty();
}

BlockingQueue::~BlockingQueue() {}
