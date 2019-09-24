#include "for-compressor.h"
#include "file.h"
#include "utils.h"
#include <stdlib.h>
#include <arpa/inet.h>
#include <algorithm>
#include <bitset>
#include <string>
#include <vector>

#define BYTE 8
#define BYTES_NUMBER 4

FORCompressor::FORCompressor(File *fr, File *fw, size_t block_size,
    size_t max_in_queue, size_t tnumber, size_t threads): Thread(tnumber),
    fr(fr), fw(fw), block_size(block_size), max_in_queue(max_in_queue),
    threads(threads) {}

std::vector<bool> FORCompressor::create_and_fill_bits_vector(
    uint32_t *differences, uint8_t bits) {
    std::vector<bool> bits_buff;

    for (size_t i = 0; i < block_size; i++) {
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

void FORCompressor::write_compressed_data(uint32_t reference, uint8_t bits,
    std::vector<bool> differences) {
    std::bitset<BYTE> byte;
    uint32_t _reference = htonl(reference);

    fw->write((char*) &_reference, sizeof(_reference));
    fw->write((char*) &bits, sizeof(bits));

    size_t j = 0;
    for (size_t i = 0; i < differences.size(); i++) {
        byte.set((BYTE - 1) - j, differences.at(i));
        if ((j + 1) % BYTE == 0) {
            j = 0;
            uint64_t sbyte = byte.to_ulong();
            fw->write((char*) &sbyte, 1);
        } else {
            j++;
        }
    }
}

void FORCompressor::compress_block(uint32_t *block) {
    uint32_t min = minimum_in_array(block, block_size);
    uint32_t *difs = new uint32_t[block_size];
    uint32_t max_dif = 0;

    for (size_t i = 0; i < block_size; i++) {
        difs[i] = block[i] - min;
        max_dif = maximum(max_dif, difs[i]);
    }

    uint8_t bits = number_of_bits(max_dif);
    std::vector<bool> differences = create_and_fill_bits_vector(difs, bits);

    write_compressed_data(min, bits, differences);

    delete[] difs;
}

void FORCompressor::to_host_endian(uint32_t *block) {
    for (size_t i = 0; i < block_size; i++) {
        block[i] = ntohl(block[i]);
    }
}

void FORCompressor::run() {
    uint32_t *block = new uint32_t[block_size];
    int data_size = BYTES_NUMBER * block_size;
    size_t next_pos = tnumber * BYTES_NUMBER * block_size;
    size_t file_size = fr->glength();
    
    while (true) {
        if (next_pos >= file_size) break;
        int count = fr->seekg_read_and_gcount((char*)block, data_size, next_pos);
        int dif = data_size - count;
        if (dif > 0) {
            for (size_t i = block_size - dif / BYTES_NUMBER;
                i < block_size; i++) {
                block[i] = block[i - 1];
            }
        }
        to_host_endian(block);
        compress_block(block);
        next_pos = next_pos + data_size * threads;
    }

    delete[] block;
}

FORCompressor::~FORCompressor() {}
