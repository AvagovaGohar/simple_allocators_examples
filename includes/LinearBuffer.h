#ifndef LINEAR_B
#define LINEAR_B

#include <iostream>

class LinearBuffer {
public:
    LinearBuffer(const std::size_t);
    ~LinearBuffer();
    template<typename T>
    T* Allocate(const std::size_t size = 1);
    void Reset(const std::size_t);
    void Free();
private:
    void* memory;
    std::size_t total_size;
    std::size_t used;
};

#endif // LINEAR_B
