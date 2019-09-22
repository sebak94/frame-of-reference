#include "compressor.h"
#include "utils.h"
#include <stdlib.h>
#include <arpa/inet.h>
#include <algorithm>
#include <bitset>

#define BYTE 8

Compressor::Compressor(const std::string infilename,
    const std::string outfilename, size_t block_size):
    fr(infilename, std::ios_base::in | std::ios_base::binary),
    fw(outfilename, std::ios_base::out | std::ios_base::binary ),
    block_size(block_size) {}

std::vector<bool> Compressor::create_and_fill_bits_vector(
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

void Compressor::write_compressed_data(uint32_t reference, uint8_t bits,
    std::vector<bool> differences) {
    std::bitset<BYTE> byte;

    uint32_t _reference = htonl(reference);

    this->fw.write((char*) &_reference, sizeof(_reference));
    this->fw.write((char*) &bits, sizeof(bits));

    size_t j = 0;
    for (size_t i = 0; i < differences.size(); i++) {
        byte.set((BYTE - 1) - j, differences.at(i));
        if ((j + 1) % BYTE == 0) {
            j = 0;
            uint64_t sbyte = byte.to_ulong();
            this->fw.write((char*) &sbyte, 1);
        } else {
            j++;
        }
    }
}

void Compressor::compress_block(uint32_t *block) {
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

void Compressor::to_host_endian(uint32_t *block) {
    for (size_t i = 0; i < block_size; i++) {
        block[i] = ntohl(block[i]);
    }
}

void Compressor::read_until_eof(uint32_t *block, int *counter, int length,
    size_t bytes_to_read) {
    while (true) {
        if (*counter == length) break;
        fr.read((char*)block, bytes_to_read);
        *counter += fr.gcount();
        int dif = bytes_to_read - fr.gcount();
        if (dif > 0) {
            for (size_t i = block_size - dif / sizeof(uint32_t);
                i < block_size; i++) {
                block[i] = block[i - 1];
                *counter += sizeof(uint32_t);
            }
        }
        to_host_endian(block);
        compress_block(block);
    }
}

void Compressor::start() {
    uint32_t *block = new uint32_t[block_size];

    int counter = 0;
    int length = fr.glength();
    size_t bytes_to_read = sizeof(uint32_t) * block_size;
    if (length % bytes_to_read != 0) {
        length += 2 * bytes_to_read - length;
    }

    read_until_eof(block, &counter, length, bytes_to_read);

    delete[] block;
}

Compressor::~Compressor() {}
