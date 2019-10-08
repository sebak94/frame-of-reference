#ifndef __FOR_COMPRESSOR_H__
#define __FOR_COMPRESSOR_H__

#include "file_reader.h"
#include "thread.h"
#include "block.h"
#include "compress_data.h"
#include "blocking_queue.h"
#include <stdio.h>
#include "vector"
#include "queue"

// Corre en un hilo distinto. Esta clase tiene el algoritmo de compresión.
class FORCompressor: public Thread {
    private:
    FileReader *fr;
    CompressData cd;
    BlockingQueue *blocks_queue;

    void compress_block(uint32_t *block);
    void to_host_endian(uint32_t *block);
    std::vector<bool> create_and_fill_bits_vector(uint32_t *differences,
        uint8_t bits);

    public:
    FORCompressor(FileReader *fr, BlockingQueue *queue, CompressData &cd,
        size_t tnumber);
    // Se encarga de llamar al read de FileReader y de llamar a los métodos
    // que comprimen el bloque. Lee la porción del archivo que le corresponde
    // de acuerdo al número de hilo que es.
    virtual void run() override;
    ~FORCompressor();
};

#endif
