#include "frame-of-reference.h"
#include "for-compressor.h"
#include <stdio.h>
#include <string>

FrameOfReference::FrameOfReference(const std::string infilename,
    const std::string outfilename,
    size_t block_size,
    size_t threads,
    size_t max_in_queue):
    fr(infilename, std::ios_base::in | std::ios_base::binary),
    fw(outfilename, std::ios_base::out | std::ios_base::binary),
    block_size(block_size),
    threads_count(threads),
    max_in_queue(max_in_queue) {}

void FrameOfReference::start() {
    std::vector<Thread*> threads;

    for (size_t i = 0; i < threads_count; i++) {
        Thread *t = new FORCompressor(&fr, &fw, block_size, max_in_queue);
        t->start();
        threads.push_back(t);
    }

    for (size_t i = 0; i < threads_count; i++) {
        threads[i]->join();
        delete threads[i];
    }
}

FrameOfReference::~FrameOfReference() {}
