#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

#include "queue"
#include "block.h"
#include <condition_variable>
#include <mutex>

// Cola que maneja el encolado y el desencolado con condition_variables
class BlockingQueue {
    private:
    std::queue<Block> q;
    std::mutex m;
    std::condition_variable pop_cv;
    std::condition_variable push_cv;
    const size_t queue_limit;

    public:
    explicit BlockingQueue(size_t queue_limit);
    // Encola si hay menos de 3 elementos, de lo contrario espera
    void push(Block b);
    // Desencola si hay elementos para desencolar, de lo contrario espera
    Block pop();
    // Devuelve true si la cola está vacía
    bool empty();
    ~BlockingQueue();
};

#endif
