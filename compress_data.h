#ifndef __COMPRESS_DATA_H__
#define __COMPRESS_DATA_H__

#include <stdio.h>

struct CompressData {
    size_t block_size;
    size_t threads;
    size_t queue_limit;
};

#endif
