#ifndef __FOR_COMPRESSOR_H__
#define __FOR_COMPRESSOR_H__

#include "file.h"
#include "thread.h"
#include "block.h"
#include "compress_data.h"
#include "blocking_queue.h"
#include <stdio.h>
#include "vector"
#include "queue"

class FORCompressor: public Thread {
    private:
    File *fr;
    CompressData cd;
    BlockingQueue *blocks_queue;

    void compress_block(uint32_t *block);
    void to_host_endian(uint32_t *block);
    std::vector<bool> create_and_fill_bits_vector(uint32_t *differences,
        uint8_t bits);

    public:
    FORCompressor(File *fr, BlockingQueue *queue, CompressData &cd,
        size_t tnumber);
    virtual void run() override;
    ~FORCompressor();
};

#endif
