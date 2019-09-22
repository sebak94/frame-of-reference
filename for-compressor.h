#ifndef __FOR_COMPRESSOR_H__
#define __FOR_COMPRESSOR_H__

#include "file.h"
#include "thread.h"
#include <stdio.h>
#include "vector"

class FORCompressor: public Thread {
    private:
    File *fr;
    File *fw;
    const size_t block_size;
    const size_t max_in_queue;
    void compress_block(uint32_t *block);
    void write_compressed_data(uint32_t reference, uint8_t bits,
        std::vector<bool> differences);
    void to_host_endian(uint32_t *block);
    std::vector<bool> create_and_fill_bits_vector(uint32_t *differences,
        uint8_t bits);
    void read_until_eof(uint32_t *block, int *counter, int length,
        size_t bytes_to_read);

    public:
    FORCompressor(File *fr, File *fw, size_t block_size, size_t max_in_queue);
    virtual void run() override;
    ~FORCompressor();
};

#endif
