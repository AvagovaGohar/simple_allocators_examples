#include "StackBuffer.h"

#include <iostream>

StackBuffer::StackBuffer(std::size_t size) {
    total_size = size;
    memory =(int8_t*)malloc(total_size);
    used = 0;
    header_count = 0;
}

StackBuffer::~StackBuffer() {
    free(memory);
    memory = nullptr;
}

template<typename T>
T* StackBuffer::Allocate(const std::size_t size) {
    if (used + sizeof(Header) + sizeof(T) * size <= total_size) {
        int8_t* tmp = memory + used;
        used += sizeof(Header) + sizeof(T) * size;
        Header* head = (Header*)(memory + (used - sizeof(Header)));
        *head = Header(sizeof(T) * size);
        ++header_count;
        return (T*)tmp;
    }
    return nullptr;
}

void StackBuffer::Deallocate(std::size_t count) {
    if (count <= header_count) {
        header_count -= count;
        Header* tmp;
        while (count != 0) {
            tmp = (Header*)(memory + used - sizeof(Header));
            used -= (tmp->bytes + sizeof(Header));
            --count;
        }
    }
}

void StackBuffer::Free() {
    used = 0;
    header_count = 0;
}
