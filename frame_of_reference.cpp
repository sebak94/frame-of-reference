#include "frame_of_reference.h"
#include "for_compressor.h"
#include "data_writer.h"
#include "blocking_queue.h"
#include <stdio.h>
#include <string>
#include "vector"
#include <condition_variable>
#include <mutex>

#define BYTES_NUMBER 4

FrameOfReference::FrameOfReference(const std::string infilename,
    const std::string outfilename, CompressData cd):
    fr(infilename), fw(outfilename), cd(cd) {
    for (size_t i = 0; i < cd.threads; i++) {
        queues.push_back(new BlockingQueue(cd.queue_limit));
    }
}

void FrameOfReference::start() {
    std::vector<Thread*> reader_threads;
    DataWriter *writer = new DataWriter(&fw);

    for (size_t i = 0; i < cd.threads; i++) {
        Thread *t = new FORCompressor(&fr, queues[i], cd, i);
        writer->add_queue(queues[i]);
        reader_threads.push_back(t);
        t->start();
    }

    writer->start();

    for (size_t i = 0; i < cd.threads; i++) {
        reader_threads[i]->join();
        delete reader_threads[i];
    }

    delete writer;
}

FrameOfReference::~FrameOfReference() {
    for (size_t i = 0; i < queues.size(); i++) {
        delete queues[i];
    }
}
