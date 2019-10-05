#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

#include "queue"
#include "block.h"
#include <condition_variable>
#include <mutex>

class BlockingQueue {
    private:
    std::queue<Block> q;
    std::mutex m;
    std::condition_variable pop_cv;
    std::condition_variable push_cv;
    const size_t queue_limit;

    public:
    explicit BlockingQueue(size_t queue_limit);
    void push(Block b);
    Block pop();
    bool empty();
    ~BlockingQueue();
};

#endif
