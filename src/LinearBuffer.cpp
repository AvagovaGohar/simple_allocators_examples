#include "LinearBuffer.h"

#inclide <iostream>

LinearBuffer::~LinearBuffer() {
    free(memory);
    memory = nullptr;
}

LinearBuffer::LinearBuffer(const std::size_t size) {
    total_size = size;
    used = 0;
    memory = malloc(total_size);
}

void LinearBuffer::Reset(const std::size_t size) {
    free(memory);
    memory = malloc(size);
    total_size = size;
    used = 0;
}

void LinearBuffer::Free() {
    total_size = 0;
    used = 0;
}

template<typename T>
T* LinearBuffer::Allocate(const std::size_t size) {
    if (sizeof(T) * size + used <= total_size) {
        T* tmp = (T*)memory + (used/sizeof(T));
        used += sizeof(T) * size;
        return tmp;
    }
    return nullptr;
}
