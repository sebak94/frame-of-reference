#ifndef __DATA_WRITER_H__
#define __DATA_WRITER_H__

#include "thread.h"
#include "file.h"
#include "block.h"
#include "blocking_queue.h"
#include "vector"

class DataWriter {
    private:
    File *fw;
    std::vector<BlockingQueue*> queues;

    public:
    explicit DataWriter(File *rw);
    void start();
    void write(Block &b);
    void add_queue(BlockingQueue *queue);
    ~DataWriter();
};

#endif
