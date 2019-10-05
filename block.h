#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <stdint.h>
#include "vector"

struct Block {
    bool is_null_block;
    uint32_t reference;
    uint8_t bits;
    std::vector<bool> differences;
};

#endif
