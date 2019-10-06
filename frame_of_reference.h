#ifndef __FRAME_OF_REFERENCE_H__
#define __FRAME_OF_REFERENCE_H__

#include "file_reader.h"
#include "file_writer.h"
#include "block.h"
#include "compress_data.h"
#include "blocking_queue.h"
#include <stdio.h>
#include <string>
#include "vector"

class FrameOfReference {
    private:
    FileReader fr;
    FileWriter fw;
    CompressData cd;
    std::vector<BlockingQueue*> queues;

    public:
    FrameOfReference(const std::string infilename,
        const std::string outfilename, CompressData cd);
    void start();
    ~FrameOfReference();
};

#endif
