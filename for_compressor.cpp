#include "for_compressor.h"
#include "file_reader.h"
#include "utils.h"
#include "compress_data.h"
#include "blocking_queue.h"
#include "block.h"
#include <stdlib.h>
#include <arpa/inet.h>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>

#define BYTES_NUMBER 4

FORCompressor::FORCompressor(FileReader *fr, BlockingQueue *queue,
    CompressData &cd, size_t tnumber): Thread(tnumber), fr(fr), cd(cd) {
    blocks_queue = queue;
}

std::vector<bool> FORCompressor::create_and_fill_bits_vector(
    uint32_t *differences, uint8_t bits) {
    std::vector<bool> bits_buff;

    for (size_t i = 0; i < cd.block_size; i++) {
        uint32_t dif = differences[i];
        std::vector<bool> bits_current_dif;
        for (size_t j = 0; j < bits; j++) {
            bits_current_dif.push_back(dif % 2);
            dif = dif >> 1;
        }
        std::reverse(bits_current_dif.begin(), bits_current_dif.end());
        bits_buff.insert(bits_buff.end(), bits_current_dif.begin(),
            bits_current_dif.end());
    }
    
    return bits_buff;
}

void FORCompressor::compress_block(uint32_t *block) {
    Block block_data;
    block_data.reference = minimum_in_array(block, cd.block_size);
    uint32_t *difs = new uint32_t[cd.block_size];
    uint32_t max_dif = 0;

    for (size_t i = 0; i < cd.block_size; i++) {
        difs[i] = block[i] - block_data.reference;
        max_dif = maximum(max_dif, difs[i]);
    }
    
    block_data.bits = number_of_bits(max_dif);
    block_data.differences = create_and_fill_bits_vector(difs,
        block_data.bits);

    block_data.is_null_block = false;
    blocks_queue->push(block_data);

    delete[] difs;
}

void FORCompressor::to_host_endian(uint32_t *block) {
    for (size_t i = 0; i < cd.block_size; i++) {
        block[i] = ntohl(block[i]);
    }
}

void FORCompressor::run() {
    uint32_t *block = new uint32_t[cd.block_size];
    int data_size = BYTES_NUMBER * cd.block_size;
    size_t next_pos = tnumber * BYTES_NUMBER * cd.block_size;
    size_t file_size = fr->glength();

    while (true) {
        if (next_pos >= file_size) break;
        int count = fr->seekg_read_and_gcount((char*)block, data_size,
            next_pos);
        int dif = data_size - count;
        if (dif > 0) {
            for (size_t i = cd.block_size - dif / BYTES_NUMBER;
                i < cd.block_size; i++) {
                block[i] = block[i - 1];
            }
        }
        to_host_endian(block);
        compress_block(block);
        next_pos = next_pos + data_size * cd.threads;
    }

    Block b;
    b.is_null_block = true;
    blocks_queue->push(b);

    delete[] block;
}

FORCompressor::~FORCompressor() {}
