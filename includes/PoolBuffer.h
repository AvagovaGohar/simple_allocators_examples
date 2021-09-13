#ifndef POOL_B
#define POOL_B

#include <iostream>
#include <forward_list>

class PoolBuffer {
public:
    PoolBuffer(std::size_t, std::size_t);
    ~PoolBuffer();
    int8_t* Allocate(const std::size_t size = 1);
    void Deallocate(int8_t*, const std::size_t size = 1);
    void Free();
private:
    int8_t* start;
    int8_t* end;
    std::size_t block_size;
    std::forward_list<int8_t*> free_blocks;
    std::size_t blocks_count;
};

#endif // POOL_B
