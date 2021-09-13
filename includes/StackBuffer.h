#ifndef STACK_B
#define STACK_B

#include <iostream>

struct Header {
    int bytes;
    Header(int size) :bytes{ size } {}
};

class StackBuffer {
public:
    StackBuffer(std::size_t);
    ~StackBuffer();
    template<typename T>
    T* Allocate(const std::size_t t = 1);
    void Deallocate(std::size_t = 1);
    void Free();
private:
    int8_t* memory;
    int total_size;
    int used;
    int header_count;
};

#endif // STACK_B
