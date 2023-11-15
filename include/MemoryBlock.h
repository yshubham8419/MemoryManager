#ifndef MEMORY_BLOCK_H
#define MEMORY_BLOCK_H

#include <cstddef>

struct MemoryBlock {
    bool highlighted; // for highlighting the block after a change is made to it;
    int id;
    int size;    // Size of the memory block
    bool allocated;      // Indicates whether the block is allocated or free

    MemoryBlock(int block_size, bool is_allocated = false) :
        size(block_size),
        allocated(is_allocated),
        id(-1),
        highlighted(false) {}
};
#endif