#ifndef __DATA_WRITER_H__
#define __DATA_WRITER_H__

#include "thread.h"
#include "file_writer.h"
#include "block.h"
#include "blocking_queue.h"
#include "vector"
#include <bitset>

#define BYTE 8

class DataWriter {
    private:
    FileWriter *fw;
    std::vector<BlockingQueue*> queues;

    void write_byte(std::bitset<BYTE> &byte);

    public:
    explicit DataWriter(FileWriter *rw);
    void start();
    void write(Block &b);
    void add_queue(BlockingQueue *queue);
    ~DataWriter();
};

#endif
