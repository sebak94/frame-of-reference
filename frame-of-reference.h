#ifndef __FRAME_OF_REFERENCE_H__
#define __FRAME_OF_REFERENCE_H__

#include "file.h"
#include <stdio.h>
#include <string>

class FrameOfReference {
    private:
    File fr;
    File fw;
    const size_t block_size;
    const size_t threads_count;
    const size_t max_in_queue;

    public:
    FrameOfReference(const std::string infilename,
        const std::string outfilename,
        size_t block_size,
        size_t threads,
        size_t max_in_queue);
    void start();
    ~FrameOfReference();
};

#endif
