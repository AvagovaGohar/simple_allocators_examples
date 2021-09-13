#include "PoolBuffer.h"

#include <iostream>
#include <forward_list>

PoolBuffer::PoolBuffer(std::size_t all_size, std::size_t b_size) {
    block_size = b_size;
    all_size = all_size / block_size * block_size;
    start = (int8_t*)malloc(all_size);
    end = start + all_size;
    int8_t* tmp = start;
    blocks_count = 0;
    while (tmp != end) {
        ++blocks_count;
        free_blocks.push_front(tmp);
        tmp += block_size;
    }
}

PoolBuffer::~PoolBuffer() {
    free_blocks.clear();
    free(start);
    start = nullptr;
    end = nullptr;
}

int8_t* PoolBuffer::Allocate(const std::size_t size) {
    if (size && blocks_count >= size ) {
        if (size == 1) {
            int8_t* tmp = *free_blocks.begin();
            free_blocks.pop_front();
            --blocks_count;
            return tmp;
        }
        int8_t* tmp = *(++free_blocks.begin());
        int8_t* return_value = *free_blocks.begin();
        int tmp_count = 0;
        for (auto it : free_blocks) {
            if (tmp_count == size)
                return return_value;
            if (tmp + block_size == it)
                ++tmp_count;
            else {
                return_value = tmp;
                tmp_count = 0;
            }
            tmp -=block_size;
        }

        if (tmp_count == size) {
            blocks_count -= size;
            return return_value;
        }
    }
    return nullptr;
}

void PoolBuffer::Deallocate(int8_t* ptr, const std::size_t size) {
    if (ptr + (size * block_size) >= start && ptr + (size * block_size) < end) {
        int8_t* tmp_end = ptr + (size * block_size);
        while (ptr != tmp_end) {
            free_blocks.push_front(ptr);
            ptr += block_size;
        }
    }
}

void PoolBuffer::Free() {
    int8_t* tmp = start;
    blocks_count = 0;
    free_blocks.clear();
    while (tmp != end) {
        ++blocks_count;
        free_blocks.push_front(tmp);
        tmp += block_size;
    }
}
