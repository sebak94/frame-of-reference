#include "data_writer.h"
#include "file.h"
#include "block.h"
#include "blocking_queue.h"
#include <bitset>
#include <arpa/inet.h>

DataWriter::DataWriter(File *fw): fw(fw) {}

void DataWriter::start() {
    bool writing = true;

    while (writing) {
        for (BlockingQueue *queue: queues) {
            Block b = queue->pop();
            if (!b.is_null_block) {
                write(b);
            } else {
                writing = false;
            }
        }
    }
}

void DataWriter::write(Block &b) {
    std::bitset<BYTE> byte;
    uint32_t _reference = htonl(b.reference);

    fw->write((char*) &_reference, sizeof(_reference));
    fw->write((char*) &b.bits, sizeof(b.bits));

    size_t j = 0;
    for (size_t i = 0; i < b.differences.size(); i++) {
        byte.set((BYTE - 1) - j, b.differences.at(i));
        if ((j + 1) % BYTE == 0) {
            j = 0;
            write_byte(byte);
        } else {
            j++;
        }
    }

    if (j != 0) {
        for (size_t i = j; i < BYTE; i++) {
            byte.set((BYTE - 1) - i, 0);
        }
        write_byte(byte);
    }
}

void DataWriter::write_byte(std::bitset<BYTE> &byte) {
    uint64_t sbyte = byte.to_ulong();
    fw->write((char*) &sbyte, 1);
}

void DataWriter::add_queue(BlockingQueue *queue) {
    queues.push_back(queue);
}

DataWriter::~DataWriter() {}
